#pragma once


// CSaveMsg-Dialogfeld

class CSaveMsg : public CDialog
{
	DECLARE_DYNAMIC(CSaveMsg)

public:
	CSaveMsg(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CSaveMsg();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG_SAVEMSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
};
