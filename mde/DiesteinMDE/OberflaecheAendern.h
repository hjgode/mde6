#pragma once
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// COberflaecheAendern dialog

class COberflaecheAendern : public CDialog
{
// Construction
public:
	COberflaecheAendern(CWnd* pParent = NULL);   // standard constructor
	~COberflaecheAendern(){};

    CSteinSaetze *m_pSteinSaetze;
    CAuftraege *m_pAuftraege;

    COberflTabelle              m_tabAlleOberflaechen;
    COberflTabelle              m_tabGruppeOberflaechen;
    CFehlerbezeichnungTabelle   m_tabFehlerbezeichnung;

    CBarcodeScanner *m_pScanner;

    int m_lastOberflIx;
    CString m_lastMatGr;
    BOOL m_zurueckEnable;

// Dialog Data
	enum { IDD = IDD_DIALOG_OBERFLAENDERN };
	CStatic	m_ctrlStaticSteinnummer;
	CStatic	m_ctrlStaticOberflaecheNeu;
	CStatic	m_ctrlStaticOberflaecheAlt;
	CStatic	m_ctrlStaticMenge;
	CStatic	m_ctrlStaticMaterial;
	CStatic	m_ctrlStaticDicke;
	CStatic	m_ctrlStaticArtikel;
	CButton	m_ctrlButtonBuchungen;
	CStatic	m_ctrlStaticSteinsaetze;
	CStatic	m_ctrlStaticDickeText;
	CStatic	m_ctrlStaticME2;
	CStatic	m_ctrlStaticME1;
	CStatic	m_ctrlStaticMaterialText;
	CStatic	m_ctrlStaticArtikelText;
	CButton	m_ctrlButtonAuto;
	CButton	m_ctrlButtonZurueck;
	CEdit	m_ctrlEditOberflAlt;
    CEdit   m_ctrlEditFehlerAlt;
	CComboBox	m_ctrlComboOberflNeu;
	CComboBox	m_ctrlComboSteinnummern;
    CComboBox   m_ctrlComboFehlerNeu;

protected:

// Overrides
	// ClassWizard generated virtual function overrides
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Implementation
protected:

    void AnzeigePlattenDaten(int index);
    void SetTexte(const SSatz& ss);
    void SetComboOberflNeu(const CString& matGr);
    void SetComboFehlerNeu(const CString& key);
	void SetMasseNeu(const CString& laenge, const CString& breite);
	void SetFehleckeNeu(const CString& fehlLaenge, const CString& fehlBreite);
	void CheckBisSteinnummer(const CString& str);

//    BOOL SetComboOberflNeu(int index);
    BOOL CheckNummer(const CString& barCode);
	BOOL CheckOberflaeche(const CString& barCode);
    void AusfuehreOberflAenderung(int ix);
    void AusfuehreFehlerAenderung(int ix);
	void AusfuehreMassAenderung(int ix);
	void AusfuehreFehleckeAenderung(int ix);
    void EnableZurueck();
    void DisableZurueck();
    void EnableAutoaus();
    void DisableAutoaus();

	// Generated message map functions
	afx_msg void OnSelchangeComboSteinnummern();
	afx_msg void OnButtonBuchungen();
	afx_msg void OnEditchangeComboSteinnummern();
	afx_msg void OnSelendokComboOberflNeu();
	afx_msg void OnCloseupComboOberflNeu();
	afx_msg void OnButtonUndo();
	afx_msg void OnButtonAuto();

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnCbnSelendokComboFehlerNeu();
	CStatic m_ctrlStaticOberflaeche;
	CStatic m_ctrlStaticFehler;
	CStatic m_ctrlStaticMasse;
	CStatic m_ctrlStaticFehlecke;
	CStatic m_ctrlStaticMasseAlt;
	CStatic m_ctrlStaticMasseNeu;
	CEdit m_ctrlEditLaengeAlt;
	CEdit m_ctrlEditBreiteAlt;
	CEdit m_ctrlEditFehlLaengeAlt;
	CEdit m_ctrlEditFehlBreiteAlt;
	CEdit m_ctrlEditLaengeNeu;
	CEdit m_ctrlEditBreiteNeu;
	CEdit m_ctrlEditFehlLaengeNeu;
	CEdit m_ctrlEditFehlBreiteNeu;
	afx_msg void OnEnKillfocusEditLaengeNeu2();
	afx_msg void OnEnKillfocusEditBreiteNeu2();
	afx_msg void OnEnKillfocusEditFehllaengeNeu2();
	afx_msg void OnEnKillfocusEditFehlbreiteNeu2();
	CStatic m_ctrlStatic_BisSteinnummer;
	CComboBox m_ctrlComboBisSteinnummer;
	afx_msg void OnCbnSelchangeComboBissteinnummern();
	afx_msg void OnCbnEditchangeComboBissteinnummern();
};
