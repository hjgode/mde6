#pragma once
#include "afxwin.h"


// CSteinbruchEmail-Dialogfeld

class CSteinbruchEmail : public CDialog
{
	DECLARE_DYNAMIC(CSteinbruchEmail)

public:
	CSteinbruchEmail(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CSteinbruchEmail();
	virtual BOOL OnInitDialog();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG_STEINBRUCHENTRY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
    CAuftraege* m_pAuftraege;
    CAuftraege* m_pAuftragBlockKorr;
    CBarcodeScanner *m_pScanner;
    
    MDEStringArray m_arrEmpfaenger;
    CProgrammStatusTabelle m_tabProgrammStatus;
    
    CString m_dateiNameZumSenden;

    void SetComboEmpfaenger();
    void SetComboSicherung();
    void UpdateDateinameUndAnzahl();
    void CreateDateinameZumSenden();

    CStatic m_ctrlStaticEmpfaenger;
    CStatic m_ctrlStaticBetreff;
    CStatic m_ctrlStaticText;
    CStatic m_ctrlStaticSicherung;
    CComboBox m_ctrlComboEmpfaenger;
    CEdit m_ctrlEditBetreff;
    CEdit m_ctrlEditText;
    CButton m_ctrlButtonSenden;
    CComboBox m_ctrlComboSicherung;
    CButton m_ctrlButtonSendSicherung;
    afx_msg void OnBnClickedButtonSend();
    CStatic m_ctrlStaticDateiname;
    CStatic m_ctrlStaticBlockAnzahl;
    CStatic m_ctrlStaticBlockzahl2;
    afx_msg void OnCbnSelchangeComboSicherung();
    afx_msg void OnBnClickedButtonSendsich();
    afx_msg void OnEnKillfocusEditBetreff();
    afx_msg void OnCbnSelchangeComboRecepient();
    CStatic m_ctrlStaticEmail;
};
