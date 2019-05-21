#pragma once


// CPreiseVerank-Dialogfeld

class CPreiseVerank : public CDialog
{

    DECLARE_DYNAMIC(CPreiseVerank)

// Construction
public:
	CPreiseVerank(CWnd* pParent = NULL);   // standard constructor
    virtual ~CPreiseVerank(){};

    CSteinSaetze *m_pOrgSteinSaetze;
    CSteinSaetze *m_pSteinSaetze;
    CSteinSaetze m_VerankerungsSaetze;
    CVerankerung *m_pCurVerank;
    int m_startSteinSatzIx;     // Index des aktuellen Steins in der SteinSatz-Liste
    CString m_backSteinNummer;  // eingescannte Steinnummer oder von Einzelansicht für Preisansicht zurückgegebene Steinnumer

    CLagerTabelle m_tabLagerOrte;
    CPreislistenTabelle m_tabPreislisten;

    CBarcodeScanner *m_pScanner;

    BOOL m_bBlink;

	enum { IDD = IDD_DIALOG_PREISEVERANK };

	CComboBox	m_ctrlComboSatznummern;

	CStatic	m_ctrlStaticPositionen;
	CStatic	m_ctrlStaticArtikelnummerText;
	CStatic	m_ctrlStaticArtikelText;
	CStatic	m_ctrlStaticLaengeText;
	CStatic	m_ctrlStaticOberflaecheText;
	CStatic	m_ctrlStaticMaterialText;
	CStatic	m_ctrlStaticDickeText;
	CStatic	m_ctrlStaticBreiteText;
	CStatic	m_ctrlStaticLagerText;
    CStatic m_ctrlStaticHinweisText;
	CStatic	m_ctrlStaticReserviert;
	CStatic	m_ctrlStaticResjanein;

	CStatic	m_ctrlStaticSatznummer;
	CStatic	m_ctrlStaticArtikelnummer;
	CStatic	m_ctrlStaticMaterial;
	CStatic	m_ctrlStaticOberflaeche;
	CStatic	m_ctrlStaticLaenge;
	CStatic	m_ctrlStaticBreite;
	CStatic	m_ctrlStaticDicke;
	CStatic	m_ctrlStaticLager;
    CStatic m_ctrlStaticHinweis;

	CStatic	m_ctrlStaticPreis[4];
	CStatic	m_ctrlStaticPreisText[4];
	CString	m_strWaehrung[4];

// Overrides
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
    BOOL PreTranslateMessage(MSG* pMsg);
    void AnzeigePlattenDaten(int index);
    void AnzeigeTexte(const CSteinSatz& satz);
    void ShowPreise(CString Preise[]);

// Implementation
protected:

	afx_msg void OnSelchangeComboSatznummern();
	afx_msg void OnEditchangeComboSatznummern();

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnStnClickedStaticLagerTx();
    afx_msg void OnStnClickedStaticHinweisTx();
};
