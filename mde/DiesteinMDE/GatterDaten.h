#pragma once
#include "afxwin.h"


// CGatterDaten-Dialogfeld

class CGatterDaten : public CDialog
{
	DECLARE_DYNAMIC(CGatterDaten)

public:
	CGatterDaten(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CGatterDaten();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG_GATTERDATEN };

public:
	CBarcodeScanner *m_pScanner;
	CAuftraege *m_pOffeneAuftraege;
	CAuftraege *m_pGatterDaten;
	CString *m_pAktuellerGatterAuftrag;

	CGatterdatenTabelle m_tabGatter;
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg) ;
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

public:
	CString m_strGatterAuftrag;
	CString m_strDatumAnfang;
	CString m_strDatumEnde;
	CString m_strZeitAnfang;
	CString m_strZeitEnde;
	CString m_strZaehlerstandAnfang;
	CString m_strZaehlerstandEnde;
	CString m_strSandverbrauch;
	CString m_strBlockhoehe;
	CString m_strBlattart;
	CString m_strNeueBlaetter;
	CString m_strAnzahlSchnitte;
	CString m_strKalkverbrauch;

	void AnzeigeGatterDaten(CString strAuftrag);
	void BildschirmLoeschen();
	void LetztenZaehlerstandErmitteln(CString strAuftrag);
	CString GetGatter (CString strAuftrag);
	void WerteAusDialogUebernehmen();
	BOOL WerteOk();
	BOOL WertOk(CString& str,CEdit& edit);
	BOOL PruefeDatum(CString& str,CEdit& edit);
	BOOL PruefeUhrzeit(CString& str,CEdit& edit);
	int NaechsteBuchungsnummer() const;
	
public:
	CStatic m_ctrlStaticGatter;
	CStatic m_ctrlStaticAnfang;
	CStatic m_ctrlStaticEnde;
	CStatic m_ctrlStaticZeit;
	CStatic m_ctrlStaticZaehlerstand;
	CStatic m_ctrlStaticSandverbrauch;
	CStatic m_ctrlStaticSaecke;
	CStatic m_ctrlStaticBlockhoehe;
	CStatic m_ctrlStaticBlattart;
	CStatic m_ctrlStaticAnzSchnitte;
	CEdit m_ctrlEditDatumAnfang;
	CEdit m_ctrlEditDatumEnde;
	CEdit m_ctrlEditZeitAnfang;
	CEdit m_ctrlEditZeitEnde;
	CEdit m_ctrlEditZaehlerstandAnfang;
	CEdit m_ctrlEditZaehlerstandEnde;
	CEdit m_ctrlEditSandverbrauch;
	CEdit m_ctrlEditBlockhoehe;
	CEdit m_ctrlEditBlattart;
	CButton m_ctrlCheckNeueBlaetter;
	CEdit m_ctrlEditAnzSchnitte;
	CButton m_ctrlButtonSpeichern;
	afx_msg void OnBnClickedButtonSpeichern();
	CButton m_ctrlButtonLoeschen;
	afx_msg void OnBnClickedButtonLoeschen();
	CStatic m_ctrlStaticDatum;
	CStatic m_ctrlStaticSand;
	CStatic m_ctrlStaticKalk;
	CEdit m_ctrlEditKalkverbrauch;
	afx_msg void OnEnChangeEditAnzschnitte();
	CButton m_ctrlButtonJeBlock;
	afx_msg void OnBnClickedButtonJeblock();
	CButton m_ctrlButtonAbbrechen;
	afx_msg void OnBnClickedButtonAbbrechen();
	afx_msg void OnStnClickedStaticAnfang();
	CButton m_ctrlButtonAnfang;
	afx_msg void OnBnClickedButtonAnfang();
	afx_msg void OnBnClickedButtonEnde();
};
