#pragma once
#include "afxwin.h"


// CDlgMasseAendern-Dialogfeld

class CDlgMasseAendern : public CDialog
{
	DECLARE_DYNAMIC(CDlgMasseAendern)

public:
	CDlgMasseAendern(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgMasseAendern();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG_MASSE };

	CLagerTabelle m_tabLagerOrte;
	CFehlerbezeichnungTabelle m_tabFehlerbezeichnung;
	CSteinSaetze *m_pSteinSaetze;
	CAuftraege *m_pAuftraege;
	CBarcodeScanner *m_pScanner;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

// Implementation
protected:
    enum{NUMMER = 1,LAGER = 2};

protected:
    int m_curFocus;
	BOOL CDlgMasseAendern::PreTranslateMessage(MSG* pMsg) ;
	BOOL CDlgMasseAendern::CheckLager(const CString& barCode);
	BOOL CDlgMasseAendern::CheckNummer(const CString& barCode);

public:
	CComboBox m_ctrlComboSteinnr;
	CStatic m_ctrlStaticSteinnummer;
	CEdit m_ctrlEditLaenge_neu;
	CEdit m_ctrlEditBreite_neu;
	CEdit m_ctrlEditDicke_neu;
	CButton m_ctrlButtonAendern;
	afx_msg void OnCbnSelchangeComboSteinnr();
	CEdit m_ctrlEditLaenge_alt;
	CEdit m_ctrlEditBreite_alt;
	CEdit m_ctrlEditDicke_alt;

	void AnzeigeDaten(int ix);
	afx_msg void OnBnClickedButtonAendern();
	CStatic m_ctrlStaticLagerort;
	CEdit m_ctrlEditLagerort_alt;
	CComboBox m_ctrlComboLagerort_neu;
	afx_msg void OnCbnSetfocusComboSteinnr();
	afx_msg void OnCbnSetfocusComboLagerortNeu();
};
