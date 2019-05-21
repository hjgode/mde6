#pragma once

/////////////////////////////////////////////////////////////////////////////
// COberflaecheBuchungen dialog

class COberflaecheBuchungen : public CDialog
{
// Construction
public:
	COberflaecheBuchungen(CWnd* pParent = NULL);   // standard constructor
	~COberflaecheBuchungen(){};

    CSteinSaetze *m_pSteinSaetze;
    CAuftraege *m_pAuftraege;

    COberflTabelle              m_tabAlleOberflaechen;
    COberflTabelle              m_tabGruppeOberflaechen;
    CFehlerbezeichnungTabelle   m_TabFehlerbezeichnung;
    int m_curSel;

    void SetListe(const CAuftrag& auf);

// Dialog Data
	enum { IDD = IDD_DIALOG_OBERFLBUCH };
	CStatic	m_ctrlStaticSteinnummer;
	CStatic	m_ctrlStaticAltNeuFehler;
	CStatic	m_ctrlStaticBuchungen;
	CButton	m_ctrlButtonErase;
	CListBox	m_ctrlListOberfl;


// Overrides
	// ClassWizard generated virtual function overrides
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

// Implementation
protected:

	// Generated message map functions
	afx_msg void OnSelchangeListOberfl();
	afx_msg void OnButtonErase();

	DECLARE_MESSAGE_MAP()
};
