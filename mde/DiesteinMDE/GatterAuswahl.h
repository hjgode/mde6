#pragma once
#include "afxwin.h"
// use FOR_CK75 define to compile for CK75
#define FOR_CK75
#ifndef FOR_CK75
#include ".\Scanner6\BarcodeScanner.h"
#else
#include ".\ScannerITC\BarcodeScanner.h"
#endif

// CGatterAuswahl-Dialogfeld

class CGatterAuswahl : public CDialog
{
	DECLARE_DYNAMIC(CGatterAuswahl)

public:
	CGatterAuswahl(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CGatterAuswahl();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG_GATTERAUSWAHL };

public:
// Variablen/Pointer usw.
	CSteinSaetze *m_pSteinSaetze;
	CAuftraege *m_pAuftraege;
	CBarcodeScanner *m_pScanner;
	CGatterdatenTabelle m_tabGatter;
	int m_nModus; 
	CString *m_pstrLetzterGatterAuftrag;
	CString *m_pstrLetzterBlock;
	//
	CAuftraege m_Platten;
	CAuftraege m_GatterDaten;
	CAuftraege m_GatterBloecke;
	CAuftraege m_offeneAuftraege;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonGattern();
	CButton m_ctrlButtonPlattenzugang;
	afx_msg void OnBnClickedButtonPlattenzugang();
	CButton m_ctrlButtonGattern;
};
