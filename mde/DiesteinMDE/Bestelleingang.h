#pragma once

/////////////////////////////////////////////////////////////////////////////
// CBestelleingang dialog

class CBestelleingang : public CDialog
{
	DECLARE_DYNAMIC(CBestelleingang)

// Construction
public:
	CBestelleingang(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBestelleingang(){};

    CSteinSaetze *m_pContSteinSaetze;   // Steinsätze im Container
    CAuftraege *m_pAuftraege;

    CLagerTabelle m_tabLager;

    CBarcodeScanner *m_pScanner;

// Dialog Data
	enum { IDD = IDD_DIALOG_BESTELLEINGANG };
	CStatic	m_ctrlStaticSteinSaetze;
	CStatic	m_ctrlStaticSteinnummer;
	CStatic	m_ctrlStaticMenge;
	CStatic	m_ctrlStaticME1;
	CStatic	m_ctrlStaticMaterialText;
	CStatic	m_ctrlStaticLBD;
	CStatic	m_ctrlStaticLager;
	CStatic	m_ctrlStaticLaengeText;
	CStatic	m_ctrlStaticDickeText;
	CStatic	m_ctrlStaticContainerText;
	CStatic	m_ctrlStaticContainer;
	CStatic	m_ctrlStaticBreiteText;
	CStatic	m_ctrlStaticBestPosText;
	CStatic	m_ctrlStaticBestPos;
	CStatic	m_ctrlStaticBestNrText;
	CStatic	m_ctrlStaticBestNr;
	CStatic	m_ctrlStaticBestelleingang;
	CStatic	m_ctrlStaticArtikelText;
	CComboBox	m_ctrlComboSteinnummern;
	CComboBox	m_ctrlComboLager;
	CButton	m_ctrlButtonHinzu;
	CButton	m_ctrlButtonBuchungen;

public:
    void AnzeigePlattenDaten(int index);
    void SetTexte(const SSatz& ss);
    void SetComboLager(int ix);

// Overrides
	// ClassWizard generated virtual function overrides
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Implementation
protected:

	// Generated message map functions
	afx_msg void OnButtonHinzu();
	afx_msg void OnSelchangeComboSteinnummern();
	afx_msg void OnEditchangeComboSteinnummern();
	afx_msg void OnButtonBuchungen();
	afx_msg void OnStaticArtikeltext();
	DECLARE_MESSAGE_MAP()
};
