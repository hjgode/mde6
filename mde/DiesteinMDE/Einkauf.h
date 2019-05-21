#pragma once

/////////////////////////////////////////////////////////////////////////////
// CEinkauf dialog

class CEinkauf : public CDialog
{
	DECLARE_DYNAMIC(CEinkauf)

// Construction
public:
	CEinkauf(CWnd* pParent = NULL);     // standard constructor
	virtual ~CEinkauf(){};

    CSteinSaetze  *m_pSteinSaetze;      // Original-Steinsätze

    CSteinSaetze  m_Bestellungen;
    CSteinSaetze  m_Bestellung;         // aktuelle Bestellung

    CAuftraege *m_pAuftraege;           // Bestellungseingang
    CAuftrag *m_pAuftrag;

    CMaterialTabelle    m_tabMaterialien;
    COberflTabelle      m_tabOberflaechen;
    CLieferantenTabelle m_tabLieferanten;
    CArtikelGruppen     m_tabArtikelGruppen;

    CBarcodeScanner *m_pScanner;

// Dialog Data
	enum { IDD = IDD_DIALOG_EINKAUF };
	CButton	m_ctrlButtonInfo;
	CStatic	m_ctrlStaticBestellnummer;
	CComboBox	m_ctrlComboBestellnr;
	CListBox	m_ctrlListPositionen;
	int		m_nListPositionen;
	CString	m_strComboBestellnr;
	CString	m_strStaticPosInfo;
	CString	m_strStaticLieferant;

    CString	m_strLastLieferschein;
    CString	m_strLastLieferscheinDatum;
    CString	m_strLastLagerort;

    BOOL m_bNoSelect;

public:
    int SetBestellung(const CString& bestellNr);
    void AnzeigeBestellPositionen(int posix);
    BOOL EndeChecked(CAuftrag *pAuftrag,const CString& strBestellNr,const CString& strBestellPos);
    BOOL CreateBestellungFuerInfo(const CString& strBestellNr,CAuftraege& m_BestellungFuerInfo);

// Overrides
	// ClassWizard generated virtual function overrides
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	afx_msg void OnSelchangeListPositionen();
	afx_msg void OnSelchangeComboBestellnr();
	afx_msg void OnButtonInfo();

	DECLARE_MESSAGE_MAP()
};
