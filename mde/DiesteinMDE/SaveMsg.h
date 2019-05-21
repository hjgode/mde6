#pragma once

/////////////////////////////////////////////////////////////////////////////
// CSaveMsg dialog

class CSaveMsg : public CDialog
{
	DECLARE_DYNAMIC(CSaveMsg)

// Construction
public:
	CSaveMsg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSaveMsg(){};

    CString m_strText;

// Dialog Data
	enum { IDD = IDD_DIALOG_SAVEMSG };
	CStatic	m_ctrlStaticText;

    CString m_strFileName;
    CSteinSaetze *m_pSteinSaetze;

// Overrides
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();

// Implementation
protected:

	// Generated message map functions
	afx_msg void OnTimer(UINT nIDEvent);
    bool SpeicherAuf3mal();

	DECLARE_MESSAGE_MAP()
};

