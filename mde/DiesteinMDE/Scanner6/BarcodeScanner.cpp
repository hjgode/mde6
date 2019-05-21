// BarcodeScanner.cpp: implementation of the CBarcodeScanner class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#ifndef _DEBUG
BOOL CheckOnSCAN(void);
#endif
// include additional dir: C:\Program Files (x86)\Honeywell\SDK for Windows Embedded (7800 99EX)\Include
#include <Decoder.h>
#include "Symbologyconfig.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CBarcodeScanner::CBarcodeScanner()
{
#ifndef _DEBUG
ptcDecodeBuffer = new TCHAR[MAX_MESSAGE_LENGTH];
m_scanEnable = TRUE;
#endif
}
//----------------------------------------------------------------------------
BOOL CBarcodeScanner::Init(CString& errMsg)
{
#ifndef _DEBUG
if(decConnect() != RESULT_SUCCESS)
    {
    errMsg = _T("    decConnect: Error\r\n");
    return(FALSE);
    }
    
decEnableDisableSymbology(SYM_ALL,FALSE);
for (int nSymId = 0; nSymId < NUM_SYMBOLOGIES; nSymId++)
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

#endif
return TRUE;
}
//--------------------------------------------------------------------------------------
CBarcodeScanner::~CBarcodeScanner()
{
#ifndef _DEBUG
delete ptcDecodeBuffer;
decDisconnect();
#endif
}
//--------------------------------------------------------------------------------------
#ifndef _DEBUG
BOOL CheckOnSCAN(void)
{
	if(GetAsyncKeyState(SCAN_KEY) < 0)
		return true;
	else 
	return false;
}
#endif
//--------------------------------------------------------------------------------------
CString CBarcodeScanner::WaitForDecode(int msDelay,CString& errMsg)
{
#ifndef _DEBUG
TCHAR   tcCodeID;
TCHAR   tcSymLetter;
TCHAR   tcSymModifier;
WORD    uBarcodeLen;
TCHAR   tcStr[MAX_MESSAGE_LENGTH];

try
{
	if(m_scanEnable)
		{
		if(GetAsyncKeyState(SCAN_KEY) < 0)
			{
			Result_t nResult = decWaitForDecode(msDelay,
                                            (BYTE *)ptcDecodeBuffer,
                                            (BYTE *)&tcCodeID,
                                            (BYTE *)&tcSymLetter,
										    (BYTE *)&tcSymModifier,
                                            &uBarcodeLen,
                                            CheckOnSCAN);
			if(nResult == RESULT_SUCCESS)
    			{
				ptcDecodeBuffer[uBarcodeLen] = 0;
    			// convert ASCII decode data to unicode
    			_stprintf(tcStr, _T("%hs"), ptcDecodeBuffer);
				return tcStr;
				}
			}
		}
}
catch(...)
{
	CString tmp;
	return tmp;
}

#endif
CString tmp;
return tmp;
}

