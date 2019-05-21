#pragma once
// BarcodeScanner.h: interface for the CBarcodeScanner class.
//
//////////////////////////////////////////////////////////////////////
#define SCAN_KEY 0x2a

class CBarcodeScanner  
{
public:
	CBarcodeScanner();
	virtual ~CBarcodeScanner();

    TCHAR *ptcDecodeBuffer;
    WORD m_maxMessageChars;
    BOOL m_scanEnable;

    BOOL Init(CString& errMsg);
    CString WaitForDecode(int msDelay,CString& errMsg);

};
