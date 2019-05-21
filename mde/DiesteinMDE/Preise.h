#pragma once
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CPreise dialog

class CPreise : public CDialog
{

DECLARE_DYNAMIC(CPreise)

// Construction
public:
	CPreise(CWnd* pParent = NULL);   // standard constructor
    ~CPreise(){};

    CSteinSaetze *m_pSteinSaetze;
    CVerankerungen *m_pVerankerungen;
    int m_CurIndex;             // aktueller Steinindex, -1 = ungültig
    CVerankerung m_CurVerank;

    CLagerTabelle m_tabLagerOrte;
    CPreislistenTabelle m_tabPreislisten;

    CBarcodeScanner *m_pScanner;

    BOOL m_bIsVerankStein;    // Stein gehört zu einer Verankerung
    BOOL m_bBlink;

    CString m_strEinzelAnsicht; 
   
	enum { IDD = IDD_DIALOG_PREISE };

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

    CButton m_ctrlButtonEinzel;

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
    BOOL PreTranslateMessage(MSG* pMsg);
    int FindNumber(const CString& strNumber) const;
    void ShowPreise(CString Preise[]);

// Implementation
protected:

	afx_msg void OnSelchangeComboSatznummern();
	afx_msg void OnEditchangeComboSatznummern();
	afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnStnClickedStaticLagerTx();
    afx_msg void OnBnClickedButtonEinzel();

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnStnClickedStaticHinweisTx();
    CStatic m_ctrlStaticGewicht;
    CStatic m_ctrlStaticGewichtText;
};
