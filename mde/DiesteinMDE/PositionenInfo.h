#pragma once

/////////////////////////////////////////////////////////////////////////////
// CPositionenInfo dialog

class CPositionenInfo : public CDialog
{
	DECLARE_DYNAMIC(CPositionenInfo)

// Construction
public:
	CPositionenInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPositionenInfo(){};

public:
    CSteinSaetze *m_pSaetze;
    int m_index;
    CLagerTabelle m_tabLagerOrte;
    CLieferantenTabelle m_tabLieferanten;
    CFehlerbezeichnungTabelle m_tabFehlerbezeichnung;

// Dialog Data
	enum { IDD = IDD_DIALOG_POSINFO };

	CButton	m_ctrlButtonVorher;
	CButton	m_ctrlButtonNaechster;
	CListBox	m_ctrlListPosInfo;
 

// Overrides
	// ClassWizard generated virtual function overrides
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

// Implementation
protected:
    void ShowSatz(const CSteinSatz& satz);
    void Add2String(const CString& str1,const CString& str2);

	// Generated message map functions
	afx_msg void OnButtonNaechster();
	afx_msg void OnButtonVorher();

	DECLARE_MESSAGE_MAP()
};
