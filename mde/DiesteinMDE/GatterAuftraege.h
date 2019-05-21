#pragma once
#include "afxwin.h"


// CGatterAuftrage-Dialogfeld

class CGatterAuftraege : public CDialog
{
	DECLARE_DYNAMIC(CGatterAuftraege)

public:
	CGatterAuftraege(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CGatterAuftraege();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG_GATTERAUFTRAEGE };

public:
// Variablen/Pointer usw.
	CSteinSaetze *m_pSteinSaetze;
	CAuftraege *m_pAuftraege;
	CAuftraege *m_pOffeneAuftraege;
	CAuftraege *m_pGatterDaten;
	CBarcodeScanner *m_pScanner;
	CGatterdatenTabelle m_tabGatter;
	int m_nModus; 
	CString *m_pstrLetzterGatterAuftrag;
	CString m_strGatterPosition;
	CString m_strAktuellerGatterAuftrag;
	CString m_strAktuellesGatter;
	CString m_strAktuelleLadung;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:

	void AnzeigeDaten(int ix);
	void SetPositionenListe(CString strAuftrag);
	static CString GetGatter(CString strAuftrag);
	static CString GetLadung(CString strAuftrag);
	int FindeLetztenGatterAuftrag(CString gatter);
	void FuellenComboBox(CString strAuftrag);
		
	CStatic m_ctrlStaticGatter;
	CComboBox m_ctrlComboGatter;
	afx_msg void OnCbnSelchangeComboGatter();
	afx_msg void OnBnClickedButtonHinzu();
	CStatic m_ctrlStaticPositionen;
	CListBox m_ctrlListPositionen;
	afx_msg void OnBnClickedButtonBearbeiten();
	afx_msg void OnBnClickedButtonPosanzeigen();
	CButton m_ctrlButtonPosAnzeigen;
	CButton m_ctrlButtonPosLoeschen;
	CStatic m_ctrlStaticPosLoeschen;
	afx_msg void OnBnClickedButtonLoeschposition2();
	CButton m_ctrlButtonAufLoeschen;
	CStatic m_ctrlStaticAufLoeschen;
	afx_msg void OnBnClickedButtonLoeschauftrag();
	CButton m_ctrlButtonHinzu;
	CButton m_ctrlButtonBearbeiten;
};
