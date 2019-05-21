#pragma once
#include "afxwin.h"


// CGatterOffeneAuftraege-Dialogfeld

class CGatterOffeneAuftraege : public CDialog
{
	DECLARE_DYNAMIC(CGatterOffeneAuftraege)

public:
	CGatterOffeneAuftraege(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CGatterOffeneAuftraege();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG_GATTEROFFENEAUFTRAEGE };

// Variablen:
public:
	CSteinSaetze *m_pSteinSaetze;
	CBarcodeScanner *m_pScanner;
	CGatterdatenTabelle m_tabGatter;
	int m_nModus; 
	CString *m_pstrLetzterGatterAuftrag;
	CString *m_pstrLetzterBlock;
	//
	CAuftraege *m_pPlatten;
	CAuftraege *m_pGatterDaten;
	CAuftraege *m_pGatterBloecke;
	CAuftraege *m_pInformationen;
	CAuftraege *m_pOffeneAuftraege;
	CString m_strAktuellerGatterAuftrag;
	CString m_strAktuellerBlock;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	void FuellenComboBoxGatter(CString strAuftrag);
	void FuellenComboBoxBloecke(CString strBlocknr);
	void SetPositionenListe();
	void SetBlockListe();
	BOOL CheckBlocknr(const CString& barCode);
	void AnzeigeButtons();
	virtual BOOL PreTranslateMessage(MSG* pMsg) ;
public:
	CStatic m_ctrlStaticGatterLadung;
	CComboBox m_ctrlComboGatter;
	CComboBox m_ctrlComboBloecke;
	afx_msg void OnCbnSelchangeComboGatter();
	CStatic m_ctrlStaticPlatten;
	CListBox m_ctrlListPositionen;
	CButton m_ctrlButtonPlatten;
	CButton m_ctrlButtonGatterdaten;
	afx_msg void OnBnClickedButtonPlatten();
	afx_msg void OnBnClickedButtonPosanzeigen();
	afx_msg void OnBnClickedButtonLoeschposition();
	afx_msg void OnCbnSelchangeComboBloecke();
	afx_msg void OnBnClickedButtonGatterdaten();
	CButton m_ctrlButtonStandfuge;
	afx_msg void OnBnClickedButtonStandfuge();
	CStatic m_ctrlStaticBlock;
	CButton m_ctrlButtonLoeschPosition;
	CStatic m_ctrlStaticLoeschPosition;
	CButton m_ctrlButtonPosAnzeigen;
	CStatic m_ctrlStaticRestbloecke;
	CListBox m_ctrlListRestbloecke;
	CButton m_ctrlButtonBlockAnzeigen;
	afx_msg void OnBnClickedButtonBlockanzeigen();
	CStatic m_ctrlStaticLoeschRestblock;
	CButton m_ctrlButtonLoeschRestblock;
	afx_msg void OnBnClickedButtonLoeschrestblock();
	CButton m_ctrlButtonRestbloecke;
	afx_msg void OnBnClickedButtonRestbloecke();
};
