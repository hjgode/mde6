#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSteinbruch-Dialogfeld

class CSteinbruch : public CDialog
{
	DECLARE_DYNAMIC(CSteinbruch)

public:
	CSteinbruch(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CSteinbruch();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG_STEINBRUCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
public:
    CArtikelGruppen m_tabArtikelGruppen;
    CLagerMatTabelle m_tabLagerMat;             // LagerKey,LagerName,LagerMaterialkey
    CMaterialGruppen m_tabMaterialGruppen;
    CMaterialTabelle m_tabAlleMaterialArten;
    CMaterialTabelle m_tabGruppeMaterialArten;
    CFehlerbezeichnungTabelle m_tabFehler;
    CProgrammStatusTabelle m_tabProgrammStatus;
	int NaechsteBuchungsNummer;
	CSteinSaetze m_Vorabdaten;
    CString m_strStaticNummer;          // Static Nummer nach übersetzen
    CString m_strStaticBlaettern;       // Static Blättern nach übersetzen

    CAuftraege* m_pAuftraege;
	CSteinSaetze* m_pSteinSaetze;
    int m_curBlockIndex;
	CAuftraege* m_pAuftragBlockKorr;
	BOOL m_modifiedAuftraege;

    CBarcodeScanner *m_pScanner;
    BOOL m_modified;
    BOOL m_nummerSet;

    CStatic m_ctrlStaticArtikelgruppe;
    CStatic m_ctrlStaticLagerort;
    CStatic m_ctrlStaticMaterialgruppe;
    CStatic m_ctrlStaticMaterial;
    CStatic m_ctrlStaticNummer;
    CStatic m_ctrlStaticBlaettern;
    CStatic m_ctrlStaticSchicht;
    CStatic m_ctrlStaticMasseBrutto;
    CStatic m_ctrlStaticMasseNetto;
    CStatic m_ctrlStaticHinweis;
    CStatic m_ctrlStaticFehler;

    CComboBox m_ctrlComboArtikelgruppen;
    CComboBox m_ctrlComboLager;
    CComboBox m_ctrlComboGruppe;
    CComboBox m_ctrlComboMaterial;
    CComboBox m_ctrlComboFehler;

    CEdit m_ctrlEditNummer;
    CEdit m_ctrlEditSchicht;
    CEdit m_ctrlEditLaengeBrutto;
    CEdit m_ctrlEditBreiteBrutto;
    CEdit m_ctrlEditDickeBrutto;
    CEdit m_ctrlEditLaengeNetto;
    CEdit m_ctrlEditBreiteNetto;
    CEdit m_ctrlEditDickeNetto;
    CEdit m_ctrlEditHinweis;
    CButton m_ctrlButtonBack;
    CButton m_ctrlButtonNext;
    CButton m_ctrlButtonLoeschen;
    CButton m_ctrlButtonUebersicht;
    CButton m_ctrlButtonHinzu;
	CButton m_ctrlButtonSumme;

    void FillComboArtikelgruppen();
    void FillComboLager();
    void FillComboGruppen();
    void FillComboFehler();

    void SetComboArtikelgruppen(const CString& artikelkey);
    void SetComboLager(const CString& lagerkey);
    void SetComboMats(int lagerIx);
    void Neu(BOOL setNummer);
    void SetBlockDaten(const CSteinSatz& satz,BOOL setNummer);
    void EnaDisa();
    void SetNummerStern();
    void EraseNummerStern();
    void SetBlaettern();
    BOOL OnHinzu();
	void VorabDatenUebernehmen(const CString& blocknr);
	void MaterialAusSatzAnzeigen(const CString& MatGrp, const CString& MatId );
	BOOL CheckDatum(CString& strDatum,CString& strResult); // 5.7.07 od. 05.7.2007... -> 05072007
	CString FormatDatum(CString& strDatum);

    afx_msg void OnCbnSelchangeComboLagerort();
    afx_msg void OnCbnSelchangeComboMaterial();
    afx_msg void OnCbnSelchangeComboGruppe();
    afx_msg void OnBnClickedButtonHinzu();
    CButton m_ctrlButtonNeu;
    afx_msg void OnBnClickedButtonNeu();
    afx_msg void OnBnClickedButtonBack();
    afx_msg void OnBnClickedButtonNext();
    afx_msg void OnEnChangeEditNummer();
    afx_msg void OnBnClickedButtonLoeschen();
    afx_msg void OnBnClickedButtonUebersicht();
    afx_msg void OnEnChangeEditSchicht();
    afx_msg void OnEnChangeEditLaengebrutto();
    afx_msg void OnEnChangeEditBreitebrutto();
    afx_msg void OnEnChangeEditDickebrutto();
    afx_msg void OnEnChangeEditLaengenetto();
    afx_msg void OnEnChangeEditBreitenetto();
    afx_msg void OnEnChangeEditDickenetto();
    afx_msg void OnEnChangeEditHinweis();
    afx_msg void OnCbnSelchangeComboFehler();
    afx_msg void OnCbnSelchangeComboArtikelGr();
    afx_msg void OnDeltaposSpinNumber(NMHDR *pNMHDR, LRESULT *pResult);
    CSpinButtonCtrl m_ctrlSpinNumber;
    CEdit m_ctrlEditGewicht;
    CStatic m_ctrlStaticGewicht;
    CButton m_ctrlButtonEmail;
    afx_msg void OnBnClickedButtonEmail();
    afx_msg void OnEnChangeEditGewicht();
	CButton m_ctrlButtonVorabInfo;
	afx_msg void OnBnClickedButtonVorabinfo();
	CStatic m_ctrlStaticKosten;
	CEdit m_ctrlEditKosten;
	afx_msg void OnEnChangeEditKosten();
	CStatic m_ctrlStaticNrLieferant;
	CEdit m_ctrlEditNrLieferant;
	afx_msg void OnEnChangeEditLiefblocknr();
	CStatic m_ctrlStaticLieferschein;
	CEdit m_ctrlEditLieferschein;
	CStatic m_ctrlStaticLieferscheinDatum;
	CEdit m_ctrlEditLieferscheinDatum;
	CEdit m_ctrlEditLagerort;
	afx_msg void OnEnChangeEditLagerort();
    void SetNaechsteBlocknr();
	afx_msg void OnEnKillfocusEditLaengebrutto();
	afx_msg void OnEnKillfocusEditBreitebrutto();
	afx_msg void OnEnKillfocusEditDickebrutto();
	afx_msg void OnBnClickedButtonSumme();
};
