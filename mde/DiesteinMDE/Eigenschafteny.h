#pragma once


// CEigenschaften-Dialogfeld

class CEigenschaften : public CDialog
{
	DECLARE_DYNAMIC(CEigenschaften)

public:
	CEigenschaften(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CEigenschaften();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG_EIGENSCHAFTEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung

	DECLARE_MESSAGE_MAP()
};
