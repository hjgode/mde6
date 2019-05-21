// BarcodeScanner.cpp: implementation of the CBarcodeScanner class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

BOOL CheckOnSCAN(void);

// include additional dir: C:\Program Files (x86)\Intermec\Developer Library\Include
#include <itcscan.h>
// include additional lib directory: C:\Program Files (x86)\Intermec\Developer Library\Lib\WCE600\WM6\Armv4i
// instead of C:\Program Files (x86)\Honeywell\SDK for Windows Mobile 6.0\Lib
#pragma comment(lib, "ITCSCAN.LIB")

#include "Symbologyconfig.h"

//scanner thread
HANDLE hThread=NULL;
DWORD hThreadId=0;
volatile BOOL bRunThread=TRUE;
volatile BOOL bScanEnabled=FALSE;

//HGO: we do not have that 
#define MAX_MESSAGE_LENGTH              8192
#define RESULT_SUCCESS 0				// Operation was successful
static BOOL mySingleMutex=FALSE;

/*
As intermec based devices use a named event for scanning but this engine makes use of a key,
we remap the scan button to a normal key.
For example F12
But currently we cannot remap center scan button

so we use workaround and change the event names from StateLeftScan and DeltaLeftScan to StateLeftScan1 and DeltaLeftScan1

but this also not works on CK75

can only use non Center Scan Buttons
*/

/*
REMARK
 A dialog gets very slugish if the scanner decodeWait is called from within PreTranslateMessage as this is 
 called for every Window Message

*/

#undef _FOUND_FIX_FOR_CENTERSCAN_MAPPING_

void changeEventNames(BOOL bRevert){
#ifndef _FOUND_FIX_FOR_CENTERSCAN_MAPPING_
	return;
#endif
	DEBUGMSG(1, (L"+++ changeEventNames called with %i\n", bRevert));
	HKEY hKey;
	TCHAR valueState[MAX_PATH];
	TCHAR valueDelta[MAX_PATH];
	DWORD dwLen=0;
	if(bRevert){
		wsprintf(valueState, L"StateLeftScan");
		wsprintf(valueDelta, L"DeltaLeftScan");
	}
	else{
		wsprintf(valueState, L"StateLeftScan1");
		wsprintf(valueDelta, L"DeltaLeftScan1");
	}
	LONG lRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
		L"Drivers\\HID\\ClientDrivers\\ITCKeyboard\\Layout\\CK75AA6-AlphaNumeric\\0001\\Events\\State", 
		0,
		KEY_ALL_ACCESS,
		&hKey);
	dwLen=wcslen(valueState);
	if(lRes==ERROR_SUCCESS){
		DEBUGMSG(1, (L"changeEventNames:RegOpenKeyEx State\n"));
		lRes=RegSetValue(hKey, L"Event1", REG_SZ, valueState, dwLen*sizeof(TCHAR));
		DEBUGMSG(1, (L"changeEventNames:RegOpenKeyEx State = %i\n", lRes));
	}
	lRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
		L"Drivers\\HID\\ClientDrivers\\ITCKeyboard\\Layout\\CK75AA6-AlphaNumeric\\0001\\Events\\Delta", 
		0,
		KEY_ALL_ACCESS,
		&hKey);
	dwLen=wcslen(valueDelta);
	if(lRes==ERROR_SUCCESS){
		lRes=RegSetValue(hKey, L"Event1", REG_SZ, valueDelta, dwLen*sizeof(TCHAR));
		DEBUGMSG(1, (L"changeEventNames:RegOpenKeyEx Delta = %i\n", lRes));
	}
	else{
		DEBUGMSG(1, (L"changeEventNames:RegOpenKeyEx Delta failed: %i\n", lRes));
	}
	RegCloseKey(hKey);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CBarcodeScanner::CBarcodeScanner()
{
	DEBUGMSG(1,(L"### CBarcodeScanner() ### called ...\n"));
	CoInitializeEx( NULL, COINIT_MULTITHREADED );

	changeEventNames(FALSE);

	ptcDecodeBuffer = new TCHAR[MAX_MESSAGE_LENGTH];
	m_scanEnable = TRUE;
	CString err;
}

//###################### Scanner thread ######################
DWORD WINAPI scannerThread(LPVOID lpParam){
	DEBUGMSG(1,(L"### scannerThread() ### called ...\n"));
	HRESULT hResult;
	INT32 m_barcodeReader=(INT32)lpParam;
	DEBUGMSG(1,(L"### scannerThread() m_barcodeReader=%i\n", m_barcodeReader));

	DWORD msDelay=2000;

	BYTE rgbDataBuffer[2048];
	READ_DATA_STRUCT readDataBlock;
	TCHAR szMessageString[ITCSCAN_MAX_ERROR_STRING_LENGTH];

	memset(rgbDataBuffer, 0, sizeof(rgbDataBuffer));
	memset(&readDataBlock, 0, sizeof(readDataBlock));
	memset(szMessageString, 0, sizeof(szMessageString));

	//store data
	readDataBlock.rgbDataBuffer = rgbDataBuffer;
	readDataBlock.dwDataBufferSize = sizeof(rgbDataBuffer);
	readDataBlock.dwTimeout = msDelay;
	readDataBlock.dwBytesReturned = 0;

	while(bRunThread){
		if(m_barcodeReader!=NULL && bScanEnabled){
			DEBUGMSG(1,(L"scannerThread() ITCSCAN_SyncRead ...\n"));
			hResult = ITCSCAN_SyncRead(m_barcodeReader, &readDataBlock);
			if(SUCCEEDED(hResult)){
				DEBUGMSG(1,(L"scannerThread() ITCSCAN_SyncRead SUCCESS\n"));
				rgbDataBuffer[readDataBlock.dwBytesReturned] = 0;
				
				CString wDataBuffer = (CString)rgbDataBuffer;
				DEBUGMSG(1,(L"scannerThread() PostMessage wDataBuffer='%s'\n", wDataBuffer));
				
				TCHAR data[2048];
				_stprintf(data, _T("%hs"), rgbDataBuffer);
				//wsprintf(data, L"%s", wDataBuffer);
				DEBUGMSG(1,(L"scannerThread() PostMessage '%s'\n", data));
				::PostMessage(GetForegroundWindow(), WM_SCANDATA, (WPARAM)data, NULL);
			}
			else{
				DEBUGMSG(1,(L"scannerThread() ITCSCAN_SyncRead failed\n"));
			}
		}
	}
	DEBUGMSG(1,(L"### scannerThread() ### END\n"));
	return 0;
}

//----------------------------------------------------------------------------
BOOL CBarcodeScanner::Init(CString& errMsg)
{

	DEBUGMSG(1,(L"### CBarcodeScanner::Init ### called ...\n"));
	if(ITCSCAN_Open(&m_BarcodeReader, L"default")!=ITCSCAN_SUCCESS) //if(decConnect() != RESULT_SUCCESS)
	{
		errMsg = _T("    ITCSCAN_Open: Error\r\n");
		DEBUGMSG(1, (errMsg));
		return(FALSE);
	}

	DEBUGMSG(1,(L"CBarcodeScanner calling decEnableDisableSymbology...\n"));
	decEnableDisableSymbology(SYM_ALL,FALSE);

	for (int nSymId = GID_POSTNET; nSymId < NUM_SYMBOLOGIES; nSymId++)
	{
		/* set symbology defaults */
		decSetSymbologyDefaults(nSymId);

		switch(nSymId)
		{
		case SYM_CODE39 :
		case SYM_DATAMATRIX :
		case SYM_EAN13 :
		case SYM_QR :

			/* enable symbology */
			decEnableDisableSymbology(nSymId, TRUE);
			break;

		default:
			//decEnableDisableSymbology(nSymId, FALSE); wenn aktiv geht überhaupt nichts
			break;
		}
		//SYM_AZTEC = 0,
		//   SYM_CODABAR,
		//   SYM_CODE11,
		//   SYM_CODE128,
		//   SYM_CODE39,
		//   SYM_CODE49,
		//   SYM_CODE93,
		//   SYM_COMPOSITE,
		//   SYM_DATAMATRIX,
		//   SYM_EAN8,
		//   SYM_EAN13,
		//   SYM_INT25,
		//   SYM_MAXICODE,
		//   SYM_MICROPDF,
		//   SYM_OCR,
		//   SYM_PDF417,
		//   SYM_POSTNET,
		//   SYM_QR,
		//   SYM_RSS,
		//   SYM_UPCA,
		//   SYM_UPCE0,
		//   SYM_UPCE1,
		//   SYM_ISBT,
		//   SYM_BPO,
		//   SYM_CANPOST,
		//   SYM_AUSPOST,
		//   SYM_IATA25,
		//   SYM_CODABLOCK,
		//   SYM_JAPOST,
		//   SYM_PLANET,
		//   SYM_DUTCHPOST,
		//   SYM_MSI,
		//   SYM_TLCODE39,
		//   SYM_TRIOPTIC,
		//SYM_CODE32,
		//SYM_STRT25,
		//SYM_MATRIX25,
		//SYM_PLESSEY,
		//SYM_CHINAPOST,
		//SYM_KOREAPOST,
		//SYM_TELEPEN,
		//SYM_CODE16K,
		//SYM_POSICODE,
		//SYM_COUPONCODE,
		//   SYM_USPS4CB,
		//SYM_IDTAG,
		//SYM_LABEL,
		//SYM_GS1_128,
		//   SYM_HANXIN,
		//SYM_GRIDMATRIX,
		//   NUM_SYMBOLOGIES,
		//   SYM_ALL=100
	}

	//create background thread
#ifdef USE_SCANKEY_ENABLED
	#pragma message ("### CBarcodeScanner::Init no scanning background thread created as USE_SCANKEY_ENABLED is defined")
	DEBUGMSG(1,(L"### CBarcodeScanner::Init no scanning background thread created as USE_SCANKEY_ENABLED is defined\n"));
#else
	#pragma message ("### CBarcodeScanner::Init will use scanning background thread as USE_SCANKEY_ENABLED is not defined")
	DEBUGMSG(1,(L"### CreateThread() m_barcodeReader=%i\n", m_BarcodeReader));
	hThread=::CreateThread(NULL, 0, &scannerThread, (LPVOID)m_BarcodeReader, 0, &hThreadId);
#endif
	DEBUGMSG(1,(L"### CBarcodeScanner::Init ### END\n"));
	return TRUE;
}
//--------------------------------------------------------------------------------------
CBarcodeScanner::~CBarcodeScanner()
{
	DEBUGMSG(1, (L"~CBarcodeScanner()...\n"));
	bRunThread=false;
	Sleep(1000);
	delete ptcDecodeBuffer;
	ITCSCAN_Close(m_BarcodeReader);

	changeEventNames(TRUE);

	mySingleMutex=FALSE;
	CoUninitialize();
}

int CBarcodeScanner::setEnableScanner(BOOL bEnable){
	if(m_BarcodeReader!=NULL)
		ITCSCAN_SetScannerEnable(m_BarcodeReader, bEnable);
	bScanEnabled=bEnable;//local static
	_scanEnabled=bEnable;//private class
	DEBUGMSG(1, (L"setEnableScanner: %s !\n", bEnable?L"ENABLED":L"DISABLED")); 
	return (int)bScanEnabled;
}
//--------------------------------------------------------------------------------------
BOOL CheckOnSCAN(void)
{
	//this will not work as the Intermec based devices do not use a key event
	//but we can remap keys to different values
	//unfortunately currently not for the Center Scan Button
	//tested with side scan button mapped to F12

	//GetAsyncKeyState will not work correctly with simulated keyb_event!?
	if(GetAsyncKeyState(SCAN_KEY) < 0)
		return true;
	else 
		return false;
}

//--------------------------------------------------------------------------------------
CString CBarcodeScanner::WaitForDecode(int msDelay, CString& errMsg)
{

	DEBUGMSG(1, (L"WaitForDecode...\n"));

#ifndef USE_SCANKEY_ENABLED
	DEBUGMSG(1, (L"WaitForDecode disabled as USE_SCANKEY_ENABLED is not defined\n"));
	CString cStr;
	return cStr;
#endif

	if(mySingleMutex){
		DEBUGMSG(1, (L"---already scanning. Return\n"));
	}
	else{
		mySingleMutex=TRUE;
	}
//	TCHAR   tcCodeID;
//	TCHAR   tcSymLetter;
//	TCHAR   tcSymModifier;
//	WORD    uBarcodeLen;
//	TCHAR   tcStr[MAX_MESSAGE_LENGTH];

	try
	{
		if(m_scanEnable)
		{
			DEBUGMSG(1, (L"WaitForDecode: m_scanEnable=TRUE\nTesting Scan Button...\n"));
			if(CheckOnSCAN()){
				ITCSCAN_SetScannerEnable(m_BarcodeReader, TRUE);
				DEBUGMSG(1, (L"WaitForDecode: check scan button OK\n"));
				//test for scan key press? already in CheckOnSCAN()
				//if(GetAsyncKeyState(SCAN_KEY) < 0)
				//	{
				BYTE rgbDataBuffer[2048];
				HRESULT hResult = 0;
				READ_DATA_STRUCT readDataBlock;
				TCHAR szMessageString[ITCSCAN_MAX_ERROR_STRING_LENGTH];

				memset(rgbDataBuffer, 0, sizeof(rgbDataBuffer));
				memset(&readDataBlock, 0, sizeof(readDataBlock));
				memset(szMessageString, 0, sizeof(szMessageString));

				//store data
				readDataBlock.rgbDataBuffer = rgbDataBuffer;
				readDataBlock.dwDataBufferSize = sizeof(rgbDataBuffer);
				readDataBlock.dwTimeout = msDelay;
				readDataBlock.dwBytesReturned = 0;

				DEBUGMSG(1, (L"WaitForDecode: calling ITCSCAN_SyncRead with %i timeout\n", msDelay));
				
				//toggle the scan trigger, this is what honeywell decWaitForDecode function does to
				hResult = ITCSCAN_SetTriggerScanner(m_BarcodeReader, TRUE);
				DEBUGMSG(1, (L"WaitForDecode: ITCSCAN_SetTriggerScanner TRUE=0x%x\n", hResult));

				hResult = ITCSCAN_SyncRead(m_BarcodeReader, &readDataBlock);
				//Result_t nResult = decWaitForDecode(msDelay,
				//                                          (BYTE *)ptcDecodeBuffer,
				//                                          (BYTE *)&tcCodeID,
				//                                          (BYTE *)&tcSymLetter,
				//								    (BYTE *)&tcSymModifier,
				//                                          &uBarcodeLen,
				//                                          CheckOnSCAN);
				if(SUCCEEDED(hResult))
				{
					DEBUGMSG(1, (L"WaitForDecode: ITCSCAN_SyncRead OK\n"));
					TCHAR dataBuf[2048] = {0};
					//get data scanned
					rgbDataBuffer[readDataBlock.dwBytesReturned] = 0;
					CString wDataBuffer = (CString)rgbDataBuffer;
					wsprintf(dataBuf, _T("%s"),wDataBuffer);
					DEBUGMSG(1, (L"WaitForDecode: ITCSCAN_SyncRead data=%s\n",dataBuf));
					return dataBuf;

					//// convert ASCII decode data to unicode
					//_stprintf(tcStr, _T("%hs"), readDataBlock.rgbDataBuffer);
					//return tcStr;
				}
				else{
					if(hResult == /* E_ITCADC_OPERATION_TIMED_OUT = */0xC1600004)
						DEBUGMSG(1,(L"WaitForDecode: no scan within time\n"));
					else
						DEBUGMSG(1, (L"WaitForDecode: ITCSCAN_SyncRead failed: 0x%08x\n", hResult )); 
				}
			    //toggle the scan trigger, this is what honeywell decWaitForDecode function does to
				hResult = ITCSCAN_SetTriggerScanner(m_BarcodeReader, FALSE);
				DEBUGMSG(1, (L"WaitForDecode: ITCSCAN_SetTriggerScanner TRUE=0x%x\n", hResult));
			}
			else{
				Sleep(msDelay);
				DEBUGMSG(1, (L"WaitForDecode: check scan button failed\n"));
			}
		}else{
			ITCSCAN_SetScannerEnable(m_BarcodeReader, FALSE);
			DEBUGMSG(1, (L"WaitForDecode: m_scanEnable=FALSE"));
		}
	}
	catch(...)
	{
		CString tmp;
		return tmp;
	}
	mySingleMutex=FALSE;

	CString tmp;
	return tmp;
}

