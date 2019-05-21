#pragma once
// BarcodeScanner.h: interface for the CBarcodeScanner class.
//
//////////////////////////////////////////////////////////////////////
#define SCAN_KEY 0x7B
// F12 key
#define WM_SCANDATA	WM_USER + 0x0815

#include "properties.h"

class CBarcodeScanner  
{
private:
	int _scanEnabled;
	BOOL m_scanEnable;
public:
	CBarcodeScanner();
	virtual ~CBarcodeScanner();

	//pointer to hold Barcode reader
	INT32 m_BarcodeReader;
    TCHAR *ptcDecodeBuffer;
    WORD m_maxMessageChars;

	BOOL Init(CString& errMsg);
    CString WaitForDecode(int msDelay,CString& errMsg);
	int setEnableScanner(BOOL bEnable);
};
