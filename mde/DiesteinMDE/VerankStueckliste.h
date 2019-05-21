#pragma once
#include "afxwin.h"


// CVerankStueckliste-Dialogfeld

class CVerankStueckliste : public CDialog
{
	DECLARE_DYNAMIC(CVerankStueckliste)

public:
	CVerankStueckliste(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CVerankStueckliste();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG_VERANKSTKL };

    CSteinSaetze *m_pSteinSaetze;
    CSteinSaetze m_VerankerungsSaetze;
    CVerankerung *m_pCurVerank;
    CVerankerungen *m_pVerankerungen;

    CBarcodeScanner *m_pScanner;

    int m_startSteinSatzIx;     // Index des aktuellen Steins in der SteinSatz-Liste
    CString m_backSteinNummer;  // eingescannte Steinnummer oder von Einzelansicht für Preisansicht zurückgegebene Steinnumer

    int m_zeilen;

    CLagerTabelle m_tabLagerOrte;
    CPreislistenTabelle m_tabPreislisten;

protected:
    CListBox m_ctrlListSaetze;
    CStatic m_ctrlStaticVerankerung;
    CStatic m_ctrlStaticSaetze;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();
    BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

    afx_msg void OnBnClickedButtonDetails();
    afx_msg void OnLbnSelchangeListSaetze();
};
