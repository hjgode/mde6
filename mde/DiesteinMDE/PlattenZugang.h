#pragma once
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CPlattenZugang dialog

class CPlattenZugang : public CDialog
{
	DECLARE_DYNAMIC(CPlattenZugang)

// Construction
public:
	CPlattenZugang(CWnd* pParent=NULL);   // standard constructor
	virtual ~CPlattenZugang(){};

    CSteinSaetze *m_pSteinSaetze;       // Original-Steinsatztabelle
    CAuftraege *m_pAuftraege;
    CAuftrag *m_pAuftrag;               // Auftrag der zu bearbeiten ist

    CSteinSaetze  *m_pBestellungen;

    CBarcodeScanner *m_pScanner;
 
    BOOL m_nModus;  // ID_ZUGANG, ID_BESTELLUNGENEINGANG, ID_INVENTUR

    CArtikelGruppen     m_tabArtikelGruppen;
    CMaterialGruppen    m_tabMaterialGruppen;
    CMaterialTabelle    m_tabAlleMaterialArten;
    COberflTabelle      m_tabAlleOberflaechen;
    CLagerTabelle       m_tabLagerOrte;
    CLieferantenTabelle m_tabLieferanten;
    CEinheitenTabelle   m_tabEinheiten;
    CFehlerbezeichnungTabelle   m_tabFehlerbezeichnung;

    CStringArray        m_me1Tab;

    int m_curFocus;
	CSteinSaetze m_Vorabdaten;

    enum{NUMMER = 1,LIEFERSCHEIN=2,BESTELLNR=3,BESTELLPOS=4,LAGERORT=5,NUMMERBIS=6};

// Dialog Data
	//{{AFX_DATA(CPlattenZugang)
	enum { IDD = IDD_DIALOG_PLATTENZUGANG };
	CButton	m_ctrlButtonHinzu;
	CButton	m_ctrlButtonEigenschaften;
	CStatic	m_ctrlStaticSteinnr;
	CStatic m_ctrlStaticBis;
	CStatic	m_ctrlStaticPreis;
	CStatic	m_ctrlStaticPosition;
	CStatic	m_ctrlStaticMenge;
	CStatic	m_ctrlStaticMasse;
	CStatic	m_ctrlStaticLieferschein;
	CStatic	m_ctrlStaticHinweis;
	CStatic	m_ctrlStaticFehlecke;
	CStatic	m_ctrlStaticDatum;
	CStatic	m_ctrlStaticBestellnr;
	CEdit	m_ctrlEditDatum;
	CComboBox	m_ctrlComboLager;
	CComboBox	m_ctrlComboME2;
	CButton	m_ctrlCheckEnde;
	CButton	m_ctrlCancel;
	CEdit	m_ctrlBestellPos;
	CEdit	m_ctrlBestellNr;
	CEdit	m_ctrlSteinnummer;
	CEdit	m_ctrlSteinnummerBis;
	CEdit	m_ctrlFehlbreite;
	CEdit	m_ctrlFehllaenge;
    CComboBox m_ctrlComboFehler;
	CEdit	m_ctrlLaenge;
	CEdit	m_ctrlDicke;
	CEdit	m_ctrlBreite;
	CEdit	m_ctrlMenge1;
	CComboBox	m_comboME1;
	CString	m_strArtikelGruppe;
	CString	m_strBestellNr;
	CString	m_strBestellPos;
	CString	m_strBreite;
	CString	m_strDicke;
	CString	m_strFehlbreite;
	CString	m_strFehllaenge;
//	CString	m_strFehlnummer;
	CString	m_strHinweis;
	CString	m_strLaenge;
	CString	m_strMenge1;
	CString	m_strPreis;
	CString	m_strSteinnummer;
	CString m_strSteinnummerBis;
	CString	m_strLieferant;
	CString	m_strMaterialArt;
	CString	m_strOberflaeche;
	CString	m_strME1;
	BOOL	m_bCheckEnde;
	CString	m_strRest;
	CString	m_strComboME2;
	CString	m_strComboLager;
	CString	m_strEditLieferschein;
	CString	m_strEditDatum;
	//}}AFX_DATA

//    CSteinSatz m_steinSatz;     // tmporärer Steinsatz, enthält aktuelle bzw. letzte Daten

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlattenZugang)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
    static double MengeSS(const SSatz& ss,double menge,const CString& ME1,const CString& ME);
    static CString CalcRest(CSteinSaetze *pBestellungen,CAuftrag *pAuftrag,
                            const CString& strBestellNr,const CString& strBestellPos);
    BOOL AddEnde();

protected:
    void StartZugang();
    void StartElse();
    void StartEinkauf();

    void SetComboME1(const TCHAR *ME1);
    void SetComboME2(const TCHAR *ME2);
    void SetComboLager(const CString& strLagerKey);
    void SetComboFehler(const CString& strKey);
    CString GetComboFehler();

    BOOL WerteOk();
    BOOL WertOk(CString& str,CEdit& edit); // nicht leer und eine Zahl
    int NaechsteBuchungsnummer() const;
    virtual void OnOK();
    BOOL OnHinzuInventur();
    BOOL OnHinzuZugang();
    BOOL OnHinzuEinkauf();
    BOOL CheckDatum(CString& strDatum,CString& strResult); // 5.7.07 od. 05.7.2007... -> 05072007

    BOOL Einkauf(); // Bestelleingang
    BOOL Zugang();
    BOOL Inventur();

	void VorabDatenUebernehmen(const CString& nummer);
	void CPlattenZugang::SperrenEntsperrenFelderBeiBisSteinnr();

	// Generated message map functions
	//{{AFX_MSG(CPlattenZugang)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboMe1();
	afx_msg void OnButtonEigenschaften();
	afx_msg void OnKillfocusEditBestellnr();
	afx_msg void OnKillfocusEditBestellpos();
	afx_msg void OnSetfocusEditLieferschein();
	afx_msg void OnSetfocusEditSteinnr();
	afx_msg void OnSetfocusEditBestellnr();
	afx_msg void OnKillfocusEditSteinnr();
	afx_msg void OnSetfocusEditBestellpos();
	afx_msg void OnKillfocusEditLieferschein();
	afx_msg void OnSetfocusComboLager();
	afx_msg void OnKillfocusComboLager();
	afx_msg void OnButtonHinzu();
	afx_msg void OnSelchangeComboLager();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEnKillfocusEditLaenge();
    afx_msg void OnEnKillfocusEditBreite();
    afx_msg void OnEnKillfocusEditFehllaenge();
    afx_msg void OnEnKillfocusEditFehlbreite();
	CButton m_ctrlButtonInfoVorab;
	afx_msg void OnEnChangeEditSteinnr();
	afx_msg void OnBnClickedButtonInfovorabdaten();
	CEdit m_ctrlEditLieferschein;
	afx_msg void OnEnKillfocusEditHinweis();
	CEdit m_ctrlEditHinweis;
	CEdit m_ctrlEditLagerort;
	afx_msg void OnEnChangeEditLagerort();
	CEdit m_ctrlEditPreis;
	CStatic m_ctrlStaticArtikelgruppe;
	CButton m_ctrlNeu;
	afx_msg void OnButtonNeu();
	afx_msg void OnEnSetfocusEditSteinnrbis();
	afx_msg void OnEnKillfocusEditSteinnrbis();

	BOOL bGeaendertLager;
	afx_msg void OnEnChangeEditSteinnrbis();
};
