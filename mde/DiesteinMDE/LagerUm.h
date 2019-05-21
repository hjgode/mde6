#pragma once
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////

class CLagerUm : public CDialog
{
	DECLARE_DYNAMIC(CLagerUm)

// Construction
public:
	CLagerUm(CWnd* pParent = NULL);   // standard constructor
    ~CLagerUm(){};

    CSteinSaetze *m_pSteinSaetze;
    CAuftraege *m_pAuftraege;
    CVerankerungen *m_pVerankerungen;

    CLagerTabelle m_tabLagerOrte;

    CBarcodeScanner *m_pScanner;

    int m_CurIndex;             // aktueller Steinindex, -1 = ungültig
    CVerankerung m_CurVerank;
    BOOL m_bIsVerankStein;    // Stein gehört zu einer Verankerung
    BOOL m_bBlink;
    CString m_strEinzelAnsicht;

protected:
    int m_curFocus;

public:
// Dialog Data

	enum { IDD = IDD_DIALOG_LAGERUM };
	CStatic	m_ctrlStaticSteinsaetze;
	CStatic	m_ctrlStaticOberflaecheText;
	CStatic	m_ctrlStaticME2V;
	CStatic	m_ctrlStaticME2;
	CStatic	m_ctrlStaticME1V;
	CStatic	m_ctrlStaticME1;
	CStatic	m_ctrlStaticMaterialText;
	CStatic	m_ctrlStaticLaengeText;
	CStatic	m_ctrlStaticDickeText;
	CStatic	m_ctrlStaticBreiteText;
	CStatic	m_ctrlStaticArtikelText;
    CStatic m_ctrlStaticHinweisText;

	CStatic	m_ctrlStaticLagerumbuchung;
	CStatic	m_ctrlStaticArtikel;
	CStatic	m_ctrlStaticSteinnummer;
	CStatic	m_ctrlStaticMenge;
	CStatic	m_ctrlStaticVerfuegbar;
	CStatic	m_ctrlStaticLagerAlt;
	CStatic	m_ctrlStaticLagerNeu;
	CStatic	m_ctrlStaticMaterial;
	CStatic	m_ctrlStaticOberflaeche;
	CStatic	m_ctrlStaticDicke;
	CStatic	m_ctrlStaticLaenge;
	CStatic	m_ctrlStaticBreite;
    CStatic m_ctrlStaticHinweis;

	CEdit	m_ctrlEditLagerAlt;
	CComboBox	m_ctrlComboLagerNeu;
	CComboBox	m_ctrlComboSteinnummern;


public:
    void AnzeigePlattenDaten(int index);
    void SetTexte(const CSteinSatz& satz);
    BOOL AnzeigeLager(int index);
    BOOL CheckNummer(const CString& barCode);
	BOOL CheckBisNummer(const CString& barCode);
    BOOL CheckLager(const CString& barCode);

// Overrides
    protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Implementation
protected:
    enum{NUMMER = 1,LAGER = 2,BIS_NUMMER = 3};

	afx_msg void OnSelchangeComboSteinnummer();
	afx_msg void OnKillfocusComboSteinnummer();
	afx_msg void OnSetfocusComboSteinnummer();
	afx_msg void OnSetfocusComboLagerNeu();
	afx_msg void OnSelendokComboLagerNeu();
	afx_msg void OnEditchangeComboSteinnummer();
	afx_msg void OnTimer(UINT nIDEvent);

	DECLARE_MESSAGE_MAP()
public:
    CButton m_ctrlButtonEinzel;
    afx_msg void OnBnClickedButtonEinzel();
    afx_msg void OnStnClickedStaticHinweis1Text();
	CEdit m_ctrlEditLagerort;
	afx_msg void OnEnChangeEditLagerort();
	CStatic m_ctrlStaticBisSteinnummer;
	CComboBox m_ctrlComboBisSteinnummern;
	afx_msg void OnCbnSetfocusComboBissteinnummer();
};
