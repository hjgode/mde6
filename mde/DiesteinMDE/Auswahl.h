#pragma once

// use FOR_CK75 define to compile for CK75
#define FOR_CK75
#ifndef FOR_CK75
#include ".\Scanner6\BarcodeScanner.h"
#else
#include ".\ScannerITC\BarcodeScanner.h"
#endif

#include "Verankerung.h"
#include "afxwin.h"

// CAuswahl-Dialogfeld

class CAuswahl : public CDialog
{
	DECLARE_DYNAMIC(CAuswahl)

public:
	CAuswahl(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CAuswahl(){};

// Dialogfelddaten
	enum { IDD = IDD_DIALOG_AUSWAHL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

// Dialogfeldelemente
public:
	CButton	m_ctrlButtonBestelleingang;
	CButton	m_ctrlButtonOberflAendern;
	CButton	m_ctrlButtonReservierung;
	CButton	m_ctrlButtonLieferung;
	CButton	m_ctrlButtonPreisinfo;
	CStatic	m_ctrlStaticMobileDE;
	CStatic	m_ctrlStaticDiesteinMDE;
	CButton	m_ctrlButtonEinkauf;
	CButton	m_ctrlButtonInfo;
	CButton	m_ctrlButtonVerkauf;
	CButton	m_ctrlButtonProduktion;
	CButton	m_ctrlButtonLagerUm;
	CButton	m_ctrlButtonZugang;
	CButton	m_ctrlButtonInventur;
    CButton m_ctrlButtonSteinbruch;
	CButton m_ctrlButtonGattern;
	CStatic m_ctrlStaticLagerdatenDatum;


// Klassenvariable
    CSteinSaetze m_SteinSaetze;
    CAuftraege m_Auftraege;             // wird für jede Auswahl neu eingelesen
    CString m_strLetzterProduktion;
    CString m_strLetzterVerkauf;
    CString m_strLetzterReservierung;
    CBarcodeScanner m_Scanner;
    CVerankerungen m_Verankerungen;     // (Sätze von Steinsätzen), Nur Böse
	CString m_strLetzterGatterAuftrag ;
	CString m_strLetzterBlock;
	CAuftraege m_AuftragBlockKorr;		// wird bei "Steinbruch" zusätzliche gelesen bzw. gespeichert

protected:

	afx_msg void OnButtonInfo();
	afx_msg void OnButtonPreisinfo();
	afx_msg void OnButtonVerkauf();
	afx_msg void OnButtonProduktion();
	afx_msg void OnButtonLagerum();
	afx_msg void OnButtonEingang();
	afx_msg void OnButtonZugang();
	afx_msg void OnButtonInventur();
	afx_msg void OnButtonEinkauf();
	afx_msg void OnButtonVerkaufres();
	afx_msg void OnButtonLieferung();
	afx_msg void OnButtonReservierung();
	afx_msg void OnButtonOberflaendern();
	afx_msg void OnButtonBestelleingang();
    afx_msg void OnBnClickedButtonSteinbruch();
	afx_msg void OnBnClickedButtonGattern();

	DECLARE_MESSAGE_MAP()
};
