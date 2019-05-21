#pragma once
#include "afxwin.h"


// CBenutzer-Dialogfeld

class CBenutzer : public CDialog
{
	DECLARE_DYNAMIC(CBenutzer)

public:
	CBenutzer(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CBenutzer();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG_BENUTZER };

    CBarcodeScanner *m_pScanner;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();
	virtual void OnOK();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

    C2StringTabelle m_userTab;
    CString m_userName;


	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnCbnSelchangeComboName();
    CStatic m_ctrlStaticName;
    CStatic m_ctrlStaticPasswort;
    CComboBox m_ctrlComboName;
    CEdit m_ctrlEditPasswort;
    afx_msg void OnBnClickedOk();
};
