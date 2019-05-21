#pragma once
#include "afxwin.h"


// CBlockdaten-Dialogfeld

class CBlockdaten : public CDialog
{
	DECLARE_DYNAMIC(CBlockdaten)

public:
	CBlockdaten(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CBlockdaten();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG_BLOCKDATEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
		virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_ctrlStaticBlocknummer;
	CStatic m_ctrlStaticMaterial;
	CStatic m_ctrlStaticLaenge;
	CStatic m_ctrlStaticBreite;
	CStatic m_ctrlStaticDicke;
	CStatic m_ctrlStaticBrutto;
	CStatic m_ctrlStaticNetto;
	CEdit m_ctrlEditLaengeBrutto;
	CEdit m_ctrlEditBreiteBrutto;
	CEdit m_ctrlEditDickeBrutto;
	CEdit m_ctrlEditLaengeNetto;
	CEdit m_ctrlEditBreiteNetto;
	CEdit m_ctrlEditDickeNetto;

	afx_msg void OnEnKillfocusEditLaengebrutto();
	afx_msg void OnEnKillfocusEditBreitebrutto();
	afx_msg void OnEnKillfocusEditDickebrutto();
	afx_msg void OnEnKillfocusEditLaengenetto();
	afx_msg void OnEnKillfocusEditBreitenetto();
	afx_msg void OnEnKillfocusEditDickenetto();
	
public:
	CSteinSatz m_pSteinSatz;
	BOOL m_modified;

	CMaterialGruppen    m_tabMaterialGruppen;
    CMaterialTabelle    m_tabAlleMaterialArten;

public:
	void AnzeigeBlockdaten();

};
