#pragma once


// CPreiseVerank-Dialogfeld

class CPreiseVerank : public CDialog
{

    DECLARE_DYNAMIC(CPreiseVerank)

// Construction
public:
	CPreiseVerank(CWnd* pParent = NULL);   // standard constructor
    virtual ~CPreiseVerank(){};

    CSteinSaetze *m_pVerankerungsSaetze;
    CVerankerung *m_pCurVerank;
    int m_startIx;

    CLagerTabelle m_tabLagerOrte;
    CPreislistenTabelle m_tabPreislisten;

    CBarcodeScanner *m_pScanner;

    BOOL m_enableSetFunktion;
    BOOL m_bGAaktiv;    // Set-Anzeige aktiv
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

	CButton	m_ctrlButtonSet;
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
    void AnzeigePlattenDaten(int index);
    void AnzeigeTexte(const CSteinSatz& satz);
    void Anzeige_GA_PlattenDaten(int index);
    void Anzeige_GA_Texte(const CSteinSatz& satz);
    BOOL PreTranslateMessage(MSG* pMsg);
    int FindNumber(const CString& strNumber) const;
    void ShowPreise(CString Preise[]);

// Implementation
protected:

	afx_msg void OnSelchangeComboSatznummern();
	afx_msg void OnButtonSet();
	afx_msg void OnEditchangeComboSatznummern();
	afx_msg void OnTimer(UINT nIDEvent);

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnStnClickedStaticLagerTx();
    afx_msg void OnBnClickedButtonEinzel();
    CButton m_ctrlButtonEinzel;
};
