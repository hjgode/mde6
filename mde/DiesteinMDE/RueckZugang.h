#pragma once
#include "afxwin.h"


// CRueckZugang-Dialogfeld

class CRueckZugang : public CDialog
{
	DECLARE_DYNAMIC(CRueckZugang)

public:
	CRueckZugang(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CRueckZugang();

public:
    CSteinSatz *m_pSatz;

    CSteinSaetze *m_pSteinSaetze;       // Original-Steinsatztabelle
    CAuftraege *m_pAuftraege;
    CAuftrag *m_pAuftrag;               // Auftrag der zu bearbeiten ist
    CBarcodeScanner *m_pScanner;

    CFehlerbezeichnungTabelle m_FehlerTabelle;

    int m_nModus;   // Verkauf,Verkauf(reserviert),Produktion,Inventur




// Dialogfelddaten
	enum { IDD = IDD_DIALOG_RUECKZUGANG };

public:
    CStatic m_ctrlStaticSteinNrAlt;
    CEdit m_ctrlEditSteinNrAlt;

    CStatic m_ctrlStaticSteinNr;
    CEdit m_ctrlEditSteinNr;

    CStatic m_ctrlStaticArtikel;
    CStatic m_ctrlStaticArtikelText;
    CStatic m_ctrlStaticMaterial;
    CStatic m_ctrlStaticMaterialText;
    CStatic m_ctrlStaticOberflaeche;
    CStatic m_ctrlStaticOberflText;
    CStatic m_ctrlStaticLager;
    CStatic m_ctrlStaticLagerText;
    CStatic m_ctrlStaticDicke;
    CStatic m_ctrlStaticDickeText;

    CStatic m_ctrlStaticHinweis;
    CEdit m_ctrlEditHinweis;

    CStatic m_ctrlStaticLaenge;
    CEdit m_ctrlEditLaenge;

    CStatic m_ctrlStaticBreite;
    CEdit m_ctrlEditBreite;

    CStatic m_ctrlStaticFehlecke;
    CEdit m_ctrlEditFehlLaenge;
    CEdit m_ctrlEditFehlBreite;
    CComboBox m_ctrlComboFehler1;

    CButton m_ctrlButtonCancel;
    CButton m_ctrlButtonOk;


// Overrides
	// ClassWizard generated virtual function overrides
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();

    void AnzeigePlattenDaten();
    void SetComboFehlecke(const CString& fehlnr);


	DECLARE_MESSAGE_MAP()
public:
    CStatic m_ctrlStaticTitelText;
    afx_msg void OnEnKillfocusEditLaenge();
    afx_msg void OnEnKillfocusEditBreite();
    afx_msg void OnEnKillfocusEditFehllaenge();
    afx_msg void OnEnKillfocusEditFehlbreite();
};
