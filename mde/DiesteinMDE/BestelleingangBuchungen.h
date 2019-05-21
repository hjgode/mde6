#pragma once

/////////////////////////////////////////////////////////////////////////////
// CBestelleingangBuchungen dialog

class CBestelleingangBuchungen : public CDialog
{
	DECLARE_DYNAMIC(CBestelleingangBuchungen)

// Construction
public:
	CBestelleingangBuchungen(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBestelleingangBuchungen(){};

    CSteinSaetze *m_pContSteinSaetze;

    CLagerTabelle *m_pTabLager;

    CAuftraege *m_pAuftraege;

    int m_curSel;

// Dialog Data
	enum { IDD = IDD_DIALOG_BESTELLBUCH };
	CListBox	m_ctrlListBestelleingang;
	CStatic	m_ctrlStaticSteinnummer;
	CStatic	m_ctrlStaticLager;
	CStatic	m_ctrlStaticBuchungen;
	CButton	m_ctrlButtonErase;

protected:
    void SetListe(CAuftrag *pAuftrag);

// Overrides
	// ClassWizard generated virtual function overrides
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();

// Implementation
protected:

	// Generated message map functions
	afx_msg void OnButtonErase();

	DECLARE_MESSAGE_MAP()
};
