#pragma once
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CPositionen dialog

class CPositionen : public CDialog
{
	DECLARE_DYNAMIC(CPositionen)

public:
	CPositionen(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPositionen(){};

public:

    CSteinSaetze *m_pSteinSaetze;       // Original-Steinsatztabelle
    CAuftraege *m_pAuftraege;
    CAuftrag *m_pAuftrag;               // Auftrag der zu bearbeiten ist
	CAuftraege *m_pOffeneAuftraege;		// offene Gatteraufträge
    CBarcodeScanner *m_pScanner;

    CString m_ProduktionVerkauf; // nichts oder Produktion "P" oder Verkauf "V"
	BOOL m_hinzEnable;
	CString m_strLetzteNummer;

    CLagerTabelle m_LagerTabelle;
    CFehlerbezeichnungTabelle m_FehlerTabelle;
    CArtikelGruppen m_ArtikelGruppen;

    int m_curFocus;

    int m_nModus;   // Verkauf,Verkauf(reserviert),Produktion,Inventur

    int m_nSetHinzu;    // nur Böse, Wenn Satznummer mit X beginnt, ohne X auswählen und hinzugügen mit X

	int m_curAnzahl;

    BOOL m_bBlink;  // RESERVIERT blinken lassen
    // Für Böse
//    CSteinSaetze m_ReservierteSteinSaetze;    // Alle Sätze, die im Feld ResFuerAuftrag die aktuelle Auftragsnummer stehen haben
                                        // (wird nur bei Bedarf erzeugt)

// Construction

    void SetComboSteinSaetze();
	void AnzeigePlattenDaten(int index);
    void AnzeigeTexte(const CSteinSatz& satz);
    void RueckEnable(BOOL);
    BOOL NormalHinzubuchen(int index);
    BOOL NormalRueckbuchen();
    void HinzuEnd(int index);
    int FindNumber(const CString& strAktuelleNummer) const;
    int NaechsteBuchungsnummer() const;
    BOOL WerteOk();
    void SetPVButtons(const CString& strProduktionVerkauf);
    void SetComboLager(const CString& strLagerKey);
    void SetComboFehler(const CString& strKey);
    CString GetComboFehler();
    BOOL CheckLager(const CString& barCode);
    BOOL DialogPlattenDefinition();

// Spezialfunktionen für Böse
    BOOL LieferungNormalHinzubuchen(int index);    // Sonderversion für Böse
    BOOL LieferungFindePassendenSteinsatz(const CString& strAuftrag,const CSteinSatz& satz0,CSteinSaetze& m_Steinsaetze,int& i);
//--------------------------

// Dialog Data
	enum { IDD = IDD_DIALOG_POSITIONEN };
	CComboBox	m_ctrlComboSteinSaetze;
	CStatic	m_ctrlStaticFehler;
	CStatic	m_ctrlStaticFehlEcke;
	CStatic	m_ctrlStaticFehlLaenge;
	CStatic	m_ctrlStaticFehlBreite;
    CComboBox m_ctrlComboFehler;
//	CEdit	m_ctrlEditFehlNummer;
	CEdit	m_ctrlEditFehlLaenge;
	CEdit	m_ctrlEditFehlBreite;
	CEdit	m_ctrlEditBuchungsMenge;
	CButton	m_ctrlButtonPosHinzu;
	CEdit	m_ctrlEditLaenge;
	CEdit	m_ctrlEditBreite;
	CStatic	m_ctrlStaticMaterialText;
	CStatic	m_ctrlStaticSteinnummer;
	CStatic	m_ctrlStaticPositionenZahl;
	CStatic	m_ctrlStaticOberflaecheText;
	CStatic	m_ctrlStaticME2;
	CStatic	m_ctrlStaticME1;
	CStatic	m_ctrlStaticDickeText;
	CStatic	m_ctrlStaticAuftragsName;
	CStatic	m_ctrlStaticArtikelText;
    CStatic m_ctrlStaticHinweisText;
    CStatic m_ctrlStaticReserviert;

	CComboBox	m_ctrlComboLager;

	CStatic	m_ctrlStaticLager;
	CStatic	m_ctrlStaticBreite;
	CStatic	m_ctrlStaticLaenge;
	CStatic	m_ctrlStaticDicke;
    CStatic m_ctrlStaticHinweis;
	CStatic	m_ctrlStaticOberflaeche;
	CStatic	m_ctrlStaticMaterial;
	CStatic	m_ctrlStaticArtikel;
	CStatic	m_ctrlStaticMenge;
	CButton	m_ctrlCheckRueck;

	CString	m_strAktuelleNummer;
	BOOL	m_bCheckRueck;
	BOOL	m_bCheckRest;

	CSteinSatz m_GeaenderteBlockDaten;
	BOOL m_bGeaendertBlockDaten;

// Overrides
	// ClassWizard generated virtual function overrides
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    enum{NUMMER = 1,LAGER = 2};

	// Generated message map functions

	afx_msg void OnButtonPoshinzu();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboSteinnummer();
	afx_msg void OnCheckRueck();
	afx_msg void OnCheckRest();
	afx_msg void OnStaticArtikelText();
	afx_msg void OnSetfocusComboLager();
	afx_msg void OnKillfocusComboLager();
	afx_msg void OnEditchangeComboSteinnummer();
	afx_msg void OnTimer(UINT nIDEvent);

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEnKillfocusEditLaenge();
    afx_msg void OnEnKillfocusEditBreite();
    afx_msg void OnEnKillfocusEditFehllaenge();
    afx_msg void OnEnKillfocusEditFehlbreite();
	CEdit m_ctrlEditLagerort;
	afx_msg void OnEnChangeEditPoslagerort();
	CButton m_ctrlButtonBlockDaten;
	afx_msg void OnBnClickedButtonBlockmasse();
	afx_msg void OnEnKillfocusEditBuchmenge();
public:
	CButton m_ctrlCheckRest;
public:
	afx_msg void OnBnClickedCheckRest();
};
