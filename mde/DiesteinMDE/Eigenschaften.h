#pragma once
#include "afxwin.h"

//#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CEigenschaften dialog
//----------------------------------------------------------------------------
class CEigenschaften : public CDialog
{
	DECLARE_DYNAMIC(CEigenschaften)

// Construction
public:
	CEigenschaften(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEigenschaften(){};

    CArtikelGruppen     m_tabArtikelGruppen;
    CMaterialGruppen    m_tabMaterialGruppen;

    CMaterialTabelle    m_tabAlleMaterialArten;
    CMaterialTabelle    m_tabGruppeMaterialArten;
    COberflTabelle      m_tabAlleOberflaechen;
    COberflTabelle      m_tabGruppeOberflaechen;
    CLagerTabelle       m_tabLagerOrte;
    CLieferantenTabelle m_tabLieferanten;

    void SetComboLager(const CString& strLagerKey);

// Dialog Data
	//{{AFX_DATA(CEigenschaften)
	enum { IDD = IDD_DIALOG_EIGENSCHAFTEN };
	CStatic	m_ctrlStaticTextFeld;
	CButton	m_ctrlButtonOK;
	CButton	m_ctrlButtonCancel;
	CStatic	m_ctrlStaticLieferant;
	CStatic	m_ctrlStaticLagerort;
	CStatic	m_ctrlStaticOberflaeche;
	CStatic	m_ctrlStaticMaterialart;
	CStatic	m_ctrlStaticMaterialgruppe;
	CStatic	m_ctrlStaticArtikelgruppe;
	CComboBox	m_comboArtikelGruppen;
	CComboBox	m_comboMaterialGruppen;
	CComboBox	m_comboMaterialArten;
	CComboBox	m_comboOberflaechen;
	CComboBox	m_comboLagerOrte;
	CComboBox	m_comboLieferanten;
	CString	m_strArtikelGruppe;
	CString	m_strMaterialGruppe;
	CString	m_strMaterialArt;
	CString	m_strLagerOrt;
	CString	m_strLieferant;
	CString	m_strOberflaeche;
	CString	m_strEditTextFeld;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEigenschaften)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEigenschaften)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboMaterialgruppe();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlEditLagerort;
	afx_msg void OnEnChangeEditLagerort();
};
