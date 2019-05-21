#pragma once
#include "afxwin.h"


// CGatterDatenJeBlock-Dialogfeld

class CGatterDatenJeBlock : public CDialog
{
	DECLARE_DYNAMIC(CGatterDatenJeBlock)

public:
	CGatterDatenJeBlock(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CGatterDatenJeBlock();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG_SCHNITTEJEBLOCK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
public:
	CString *m_pAnzSchnitteJeBlock;
	CAuftrag *m_pAuftrag;
	CBarcodeScanner *m_pScanner;

	C3StringTabelle Schnitte;

public:
	void AnzeigeBlockDaten();


public:
	CStatic m_ctrlStatic_Block;
	CComboBox m_ctrlComboBloecke;
	CStatic m_ctrlStaticMaterial;
	CStatic m_ctrlStaticMasse;
	CStatic m_ctrlStaticAnzSchnitte;
	CEdit m_ctrlEditAnzSchnitte;
	CStatic m_ctrlStaticSchnittflaeche;
	CComboBox m_ctrlComboSchnittflaeche;
	CButton m_ctrlButtonLoeschen;
	CButton m_ctrlButtonSpeichern;
	CButton m_ctrlButtonAbbrechen;
	afx_msg void OnEnChangeEditAnzschnitte();
	afx_msg void OnCbnSelchangeComboSchnittflaeche();
	afx_msg void OnBnClickedButtonAbbrechen();
	afx_msg void OnBnClickedButtonLoeschen();
	afx_msg void OnBnClickedButtonSpeichern();
	afx_msg void OnCbnSelchangeComboBloecke();
};
