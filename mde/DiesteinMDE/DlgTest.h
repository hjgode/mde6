#pragma once
#include "afxwin.h"


// CDlgTest-Dialogfeld

class CDlgTest : public CDialog
{
	DECLARE_DYNAMIC(CDlgTest)

public:
	CDlgTest(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgTest();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG_TEST };

public:
	CSteinSaetze *m_pSaetze;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog ();

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ctrlListSteinSaetze;
};
