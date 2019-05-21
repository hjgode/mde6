#pragma once
#include "afxwin.h"


// CBloeckeVorabInfo-Dialogfeld

class CBloeckeVorabInfo : public CDialog
{
	DECLARE_DYNAMIC(CBloeckeVorabInfo)

public:
	CBloeckeVorabInfo(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CBloeckeVorabInfo();

public:
    CSteinSaetze *m_pSaetze;
	CString *m_pBlocknr;
    int *m_pUebernehmen;
    CLagerTabelle m_tabLagerOrte;
    CLieferantenTabelle m_tabLieferanten;
    CFehlerbezeichnungTabelle m_tabFehlerbezeichnung;

// Dialogfelddaten
	enum { IDD = IDD_DIALOG_BLOCKVORABINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

// Implementation
protected:
    void ShowSatz(const CSteinSatz& satz);
    void Add2String(const CString& str1,const CString& str2);

public:
	CListBox m_ctrlListPosInfo;
	CButton m_ctrlButtonUebernehmen;
	afx_msg void OnBnClickedButtonUebernehmen();
	CButton m_ctrlButtonAbbruch;
	afx_msg void OnBnClickedButtonAbbruch();
};
