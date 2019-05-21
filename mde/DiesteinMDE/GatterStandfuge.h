#pragma once
#include "afxwin.h"


// CGatterStandfuge-Dialogfeld

class CGatterStandfuge : public CDialog
{
	DECLARE_DYNAMIC(CGatterStandfuge)

public:
	CGatterStandfuge(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CGatterStandfuge();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG_GATTERSTANDFUGE };

public:
	CBarcodeScanner *m_pScanner;
	CAuftraege *m_pOffeneAuftraege;
	CAuftraege *m_pGatterDaten;
	CString *m_pAktuellerGatterAuftrag;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	CString m_strGatterAuftrag;
	CString m_strLaenge;
	CString m_strBreite;

	void AnzeigeGatterDaten(CString strAuftrag);
	void BildschirmLoeschen();
	BOOL WerteOk();
	BOOL WertOk(CString& str,CEdit& edit);
	int NaechsteBuchungsnummer() const;

public:
	CStatic m_ctrlStaticGatter;
	CStatic m_ctrlStaticMasse;
	CEdit m_ctrlEditLaenge;
	CEdit m_ctrlEditBreite;
	CButton m_ctrlButtonSpeichern;
	afx_msg void OnBnClickedButtonSpeichern();
	CButton m_ctrlButtonLoeschen;
	afx_msg void OnBnClickedButtonLoeschen();
};
