#pragma once
#include "afxwin.h"


// CGatterPlatten-Dialogfeld

class CGatterPlatten : public CDialog
{
	DECLARE_DYNAMIC(CGatterPlatten)

public:
	CGatterPlatten(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CGatterPlatten();
	virtual void OnOK();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG_GATTERPLATTEN };

// Variablen
public:
	CSteinSaetze *m_pSteinSaetze;
	CBarcodeScanner *m_pScanner;
	CAuftraege *m_pPlatten;
	CAuftraege *m_pGatterBloecke;
	CAuftraege *m_pOffeneAuftraege;
	CAuftrag *m_pAuftrag;
	CString *m_pAktuellerGatterAuftrag;
	CString *m_pAktuellerBlock;
	CString m_Art;

	CArtikelGruppen     m_tabArtikelGruppen;
    CMaterialGruppen    m_tabMaterialGruppen;
    CMaterialTabelle    m_tabAlleMaterialArten;
    COberflTabelle      m_tabAlleOberflaechen;
	CLagerTabelle       m_tabLagerOrte;
    CLieferantenTabelle m_tabLieferanten;
    CFehlerbezeichnungTabelle   m_tabFehlerbezeichnung;
	//CArray<class CString,const class CString&> zusatzRestbloecke;
	CString arrZusatzRestbloecke[30];
	BOOL m_modified;
	
// Hilfsvariablen für die Inhalte des Fensters
	CString m_strSteinnummer;
	CString m_strMenge;
	CString m_strLaenge;
	CString m_strBreite;
	CString m_strDicke;
	CString m_strLaengeBrutto;
	CString m_strBreiteBrutto;
	CString m_strDickeBrutto;
	CString m_strFehlLaenge;
	CString m_strFehlBreite;
	CString m_strFehler;
	CString m_strLager;
	CString m_strLieferant;
	CString m_strHinweis;
	CString m_strPreis;
	CString m_strArtikelGruppe;
	CString m_strMaterialArt;
	CString m_strOberflaeche;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	void AnzeigeBlockdaten(CString strAuftrag, CString strBlock);
	void AnzeigeNeuePlatte(CString strAuftrag, CString strBlock);
	void BildschirmLoeschen();
	void WerteAusDialogUebernehmen();
	BOOL WerteOk();
    BOOL WertOk(CString& str,CEdit& edit); // nicht leer und eine Zahl
    int NaechsteBuchungsnummer() const;
	BOOL Steinnummern_pruefen(int ix_platten, CString strSteinnummer, CString strMenge);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	BOOL CheckLager(const CString& barCode);
	void SetComboLager(const CString& strLagerKey);
	void FuellenRestblockZusatzArray();

public:
	CStatic m_ctrlStaticBlocknummer;
	CStatic m_ctrlStaticMaterial;
	CStatic m_ctrlStaticMasse;
	CEdit m_ctrlEditSteinnr;
	CEdit m_ctrlEditMenge;
	CStatic m_ctrlStaticMe;
	CStatic m_ctrlStaticMasse2;
	CEdit m_ctrlEditLaenge;
	CEdit m_ctrlEditBreite;
	CEdit m_ctrlEditDicke;
	CStatic m_ctrlStaticFehlecke;
	CEdit m_ctrlEditFehlLaenge;
	CEdit m_ctrlEditFehlBreite;
	CComboBox m_ctrlComboFehler;
	CComboBox m_ctrlComboLager;
	CStatic m_ctrlStaticLieferant;
	CStatic m_ctrlStaticLager;
	CComboBox m_ctrlComboLieferant;
	CStatic m_ctrlStaticHinweis;
	CEdit m_ctrlEditHinweis;
	CStatic m_ctrlStaticPreis;
	CEdit m_ctrlEditPreis;
	CButton m_ctrlButtonAbbruch;
	CButton m_ctrlButtonHinzufuegen;
	afx_msg void OnBnClickedButtonHinzu();
	CStatic m_ctrlStaticSteinnr;
	CStatic m_ctrlStaticMenge;
	CStatic m_ctrlStaticNettoMasse;
	CEdit m_ctrlEditNettoLaenge;
	CEdit m_ctrlEditNettoBreite;
	CEdit m_ctrlEditNettoDicke;
	afx_msg void OnEnKillfocusEditHinweis();
	CEdit m_ctrlEditLagerort;
	afx_msg void OnEnChangeEditLagerort();
	afx_msg void OnEnChangeEditMenge();
	afx_msg void OnEnChangeEditLaenge();
	afx_msg void OnEnChangeEditBreite();
	afx_msg void OnEnChangeEditDicke();
	afx_msg void OnEnChangeEditNettolaenge();
	afx_msg void OnEnChangeEditNettobreite();
	afx_msg void OnEnChangeEditNettodicke();
	afx_msg void OnEnChangeEditFehllaenge();
	afx_msg void OnEnChangeEditFehlbreite();
	afx_msg void OnCbnSelendokComboFehler();
	afx_msg void OnCbnSelendokComboLager();
	afx_msg void OnEnChangeEditHinweis();
	afx_msg void OnEnChangeEditPreis();
	afx_msg void OnEnChangeEditSteinnr();
};
