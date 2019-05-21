#pragma once
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CInfo dialog


class CInfo : public CDialog
{
DECLARE_DYNAMIC(CInfo)

public:
	CInfo(CWnd* pParent = NULL);	// standard constructor
    ~CInfo(){};

public:
    CSteinSaetze *m_pSteinSaetze;

    CBarcodeScanner *m_pScanner;

    CLagerTabelle m_tabLagerOrte;
    CLieferantenTabelle m_tabLieferanten;
    CFehlerbezeichnungTabelle m_tabFehlerbezeichnung;

    BOOL m_bBlink;  // um RESERVIERT blinken zu lassen

// Construction
public:

// Dialog Data
	enum { IDD = IDD_DIALOG_INFO };

	CStatic	m_ctrlStaticLagerortTx;
	CStatic	m_ctrlStaticHinweisTx;
	CStatic	m_ctrlStaticSteinsaetze;
	CStatic	m_ctrlStaticReserviert;
	CStatic	m_ctrlStaticOberflaecheTx;
	CStatic	m_ctrlStaticMenge2V;
	CStatic	m_ctrlStaticMenge2;
	CStatic	m_ctrlStaticMenge1V;
	CStatic	m_ctrlStaticMenge1;
	CStatic	m_ctrlStaticMaterialTx;
	CStatic	m_ctrlStaticLieferantTx;
	CStatic	m_ctrlStaticArtikelTx;
	CEdit	m_ctrlEditLaenge;
	CEdit	m_ctrlEditFehlnummer;
	CEdit	m_ctrlEditFehllaenge;
	CEdit	m_ctrlEditFehlbreite;
	CEdit	m_ctrlEditDicke;
	CEdit	m_ctrlEditBreite;
    CEdit m_ctrlEditGewicht;
	CStatic	m_ctrlStaticFehlnummer;
	CStatic	m_ctrlStaticFehlbreite;
	CStatic	m_ctrlStaticFehllaenge;
	CStatic	m_ctrlStaticFehlecke;
	CStatic	m_ctrlStaticDicke;
	CStatic	m_ctrlStaticBreite;
	CStatic	m_ctrlStaticLaenge;
	CStatic	m_ctrlStaticHinweis;
	CStatic	m_ctrlStaticLieferant;
	CStatic	m_ctrlStaticLagerort;
	CStatic	m_ctrlStaticOberflaeche;
	CStatic	m_ctrlStaticMaterial;
	CStatic	m_ctrlStaticArtikel;
	CStatic	m_ctrlStaticVerfuegbar;
	CStatic	m_ctrlStaticMenge;
	CStatic	m_ctrlStaticSteinnummer;
    CStatic m_ctrlStaticGewicht;
	CComboBox	m_ctrlNummernListe;
	int		m_nEigenschaften;

protected:

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();

//Funktionen

    int FindNumber(const CString& strNumber) const;
	void AnzeigePlattenDaten(int index);
    void AnzeigeTexte(const CSteinSatz& ss);

// Implementation
protected:

	afx_msg void OnSelchangeComboSteinnummer();
	afx_msg void OnEditchangeComboSteinnummer();
	afx_msg void OnTimer(UINT nIDEvent);

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_ctrlStaticBruttomasse;
};
