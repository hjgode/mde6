#pragma once
#include "afxwin.h"


// CGatterNeu-Dialogfeld

class CGatterNeu : public CDialog
{
	DECLARE_DYNAMIC(CGatterNeu)

public:
	CGatterNeu(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CGatterNeu();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG_GATTER_NEU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ctrlComboGatter;
	CStatic m_ctrlStaticGatter;
	CStatic m_ctrlStaticLadung;
	CEdit m_ctrlEditLadung;
	CButton m_ctrlButtonHinzu;
	afx_msg void OnCbnSelchangeComboGatter();
	void AnzeigeDaten(int ix);
	CGatterdatenTabelle m_tabGatter;
	afx_msg void OnBnClickedButtonHinzu();
	CAuftraege *m_pAuftraege;
	CButton m_ctrlCheckStandfuge;
	CButton m_ctrlCheckTeilung;
};
