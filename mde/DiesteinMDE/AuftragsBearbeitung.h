#pragma once
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CAuftragsBearbeitung dialog

class CAuftragsBearbeitung : public CDialog
{
	DECLARE_DYNAMIC(CAuftragsBearbeitung)

// Construction
public:
	CAuftragsBearbeitung(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAuftragsBearbeitung(){};

public:

    CSteinSaetze *m_pSteinSaetze;
    CAuftraege *m_pAuftraege;
    CString *m_pstrLetzterAuftrag;
    CBarcodeScanner *m_pScanner;
    CAuftrag *m_pAufLoesch; // Wird im Modus Bestelleingang genutzt

    int m_nModus;   // Verkauf,Verkauf(reserviert),Produktion,Inventur, Bestelleingang


    void SetComboBox(CString strAuftrag);
    void SetPositionenListe(CString strAuftrag);
    int FindNumber(const CString& strAuf) const;

// Dialog Data
	enum { IDD = IDD_DIALOG_AUFTRAGSBEARB };
	CStatic	m_ctrlStaticLoeschAuftrag;
	CStatic	m_ctrlStaticLoeschPosition;
	CButton	m_ctrlLoeschPosition;
	CButton	m_ctrlPosAnzeigen;
	CButton	m_ctrlLoeschAuftrag;
	CButton	m_AddAuftrag;
	CListBox	m_ctrlPositionen;
	CButton	m_ctrlBearbeiten;
	CComboBox	m_ctrlComboAuftraege;
	CString	m_strAktuellerAuftrag;
	CString	m_strPosition;
    CStatic m_ctrlStaticAuftraege;
    CStatic m_ctrlStaticPositionen;

// Overrides
	// ClassWizard generated virtual function overrides
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:

	// Generated message map functions
	afx_msg void OnKillfocusComboAuftraege();
	afx_msg void OnButtonAddauftrag();
	afx_msg void OnButtonLoeschauftrag();
	afx_msg void OnButtonBearbeiten();
	afx_msg void OnSelchangeComboAuftraege();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnButtonLoeschposition();
	afx_msg void OnButtonPosanzeigen();

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnLbnSelchangeListPositionen();
	afx_msg void OnCbnSetfocusComboAuftraege();
};
