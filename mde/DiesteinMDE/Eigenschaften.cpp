// Eigenschaften.cpp : implementation file
//

#include "stdafx.h"
#include "Eigenschaften.h"

/////////////////////////////////////////////////////////////////////////////
extern CSteinSatz g_baseSteinSatz;
/////////////////////////////////////////////////////////////////////////////
// CEigenschaften dialog
IMPLEMENT_DYNAMIC(CEigenschaften, CDialog)


CEigenschaften::CEigenschaften(CWnd* pParent /*=NULL*/)
	: CDialog(CEigenschaften::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEigenschaften)
	m_strArtikelGruppe = _T("");
	m_strMaterialGruppe = _T("");
	m_strMaterialArt = _T("");
	m_strLagerOrt = _T("");
	m_strLieferant = _T("");
	m_strOberflaeche = _T("");
	m_strEditTextFeld = _T("");
	//}}AFX_DATA_INIT
}

void CEigenschaften::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEigenschaften)
	DDX_Control(pDX, IDC_STATIC_TEXTFELD, m_ctrlStaticTextFeld);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
	DDX_Control(pDX, IDC_STATIC_LIEFERANT_E, m_ctrlStaticLieferant);
	DDX_Control(pDX, IDC_STATIC_LAGERORT_E, m_ctrlStaticLagerort);
	DDX_Control(pDX, IDC_STATIC_OBERFLAECHE, m_ctrlStaticOberflaeche);
	DDX_Control(pDX, IDC_STATIC_MATERIALART, m_ctrlStaticMaterialart);
	DDX_Control(pDX, IDC_STATIC_MATERIALGRUPPE, m_ctrlStaticMaterialgruppe);
	DDX_Control(pDX, IDC_STATIC_ARTIKELGRUPPE, m_ctrlStaticArtikelgruppe);
	DDX_Control(pDX, IDC_COMBO_ARTIKELGRUPPE, m_comboArtikelGruppen);
	DDX_Control(pDX, IDC_COMBO_MATERIALGRUPPE, m_comboMaterialGruppen);
	DDX_Control(pDX, IDC_COMBO_MATERIALART, m_comboMaterialArten);
	DDX_Control(pDX, IDC_COMBO_OBERFLAECHE, m_comboOberflaechen);
	DDX_Control(pDX, IDC_COMBO_LAGERORT, m_comboLagerOrte);
	DDX_Control(pDX, IDC_COMBO_LIEFERANT, m_comboLieferanten);
	DDX_CBString(pDX, IDC_COMBO_ARTIKELGRUPPE, m_strArtikelGruppe);
	DDX_CBString(pDX, IDC_COMBO_MATERIALGRUPPE, m_strMaterialGruppe);
	DDX_CBString(pDX, IDC_COMBO_MATERIALART, m_strMaterialArt);
	DDX_CBString(pDX, IDC_COMBO_LAGERORT, m_strLagerOrt);
	DDX_CBString(pDX, IDC_COMBO_LIEFERANT, m_strLieferant);
	DDX_CBString(pDX, IDC_COMBO_OBERFLAECHE, m_strOberflaeche);
	DDX_Text(pDX, IDC_EDIT_TEXTFELD, m_strEditTextFeld);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EDIT_LAGERORT, m_ctrlEditLagerort);
}


BEGIN_MESSAGE_MAP(CEigenschaften, CDialog)
	//{{AFX_MSG_MAP(CEigenschaften)
	ON_CBN_SELCHANGE(IDC_COMBO_MATERIALGRUPPE, OnSelchangeComboMaterialgruppe)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT_LAGERORT, &CEigenschaften::OnEnChangeEditLagerort)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
BOOL CEigenschaften::OnInitDialog() 
{
CDialog::OnInitDialog();

TranslateButton(m_ctrlButtonOK);
TranslateButton(m_ctrlButtonCancel);
TranslateStatic(m_ctrlStaticLieferant);
TranslateStatic(m_ctrlStaticLagerort);
TranslateStatic(m_ctrlStaticOberflaeche);
TranslateStatic(m_ctrlStaticMaterialart);
TranslateStatic(m_ctrlStaticMaterialgruppe);
TranslateStatic(m_ctrlStaticArtikelgruppe);
TranslateStatic(m_ctrlStaticTextFeld);

SSatz ss(g_baseSteinSatz);  // Eigenschaften aus globalem Steinsatz lesen

m_tabArtikelGruppen.m_curSelected = m_tabArtikelGruppen.GetIndexByKey(ss.m_ArtikelGr);
m_tabArtikelGruppen.SetCombo(m_comboArtikelGruppen,m_strArtikelGruppe);

m_tabMaterialGruppen.m_curSelected = m_tabMaterialGruppen.GetIndexByKey(ss.m_MatGr);
m_tabMaterialGruppen.SetCombo(m_comboMaterialGruppen,m_strMaterialGruppe);

if(m_tabMaterialGruppen.m_curSelected >= 0)
    {
    m_tabGruppeMaterialArten.SetGruppe(m_tabAlleMaterialArten,m_tabMaterialGruppen.Selected().m_key);
    m_tabGruppeMaterialArten.m_curSelected = m_tabGruppeMaterialArten.GetIndexByKey(ss.m_MatGr,ss.m_MatNr);
    m_tabGruppeMaterialArten.SetCombo(m_comboMaterialArten,m_strMaterialArt);

    m_tabGruppeOberflaechen.SetGruppe(m_tabAlleOberflaechen,m_tabMaterialGruppen.Selected().m_key);
    m_tabGruppeOberflaechen.m_curSelected = m_tabGruppeOberflaechen.GetIndexByKey(ss.m_MatGr,ss.m_OberNr);
    m_tabGruppeOberflaechen.SetCombo(m_comboOberflaechen,m_strOberflaeche);
    }

SetComboLager(ss.m_Lager); // Ausnahme: key wird mit angezeigt
//m_tabLagerOrte.m_curSelected = m_tabLagerOrte.GetIndexByKey(ss.m_Lager);
//m_tabLagerOrte.SetCombo(m_comboLagerOrte,m_strLagerOrt);

m_tabLieferanten.m_curSelected = m_tabLieferanten.GetIndexByKey(ss.m_Lieferant);
m_tabLieferanten.SetCombo(m_comboLieferanten,m_strLieferant);

m_strEditTextFeld = ss.m_TextFeld;

UpdateData(FALSE);

return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CEigenschaften message handlers

void CEigenschaften::OnOK() 
{
UpdateData(TRUE);

CString str;
m_tabArtikelGruppen.m_curSelected = CEigenschaften::m_comboArtikelGruppen.GetCurSel();
m_strArtikelGruppe.TrimLeft();
m_strArtikelGruppe.TrimRight();
if(!m_strArtikelGruppe.IsEmpty() && CEigenschaften::m_strArtikelGruppe.CompareNoCase(m_tabArtikelGruppen.Selected().m_bez))
    {
    str = Sprache(_T("Artikelgruppe"));
    }
	
m_tabMaterialGruppen.m_curSelected = CEigenschaften::m_comboMaterialGruppen.GetCurSel();
m_strMaterialGruppe.TrimLeft();
m_strMaterialGruppe.TrimRight();
if(!m_strMaterialGruppe.IsEmpty() && CEigenschaften::m_strMaterialGruppe.CompareNoCase(m_tabMaterialGruppen.Selected().m_bez))
    {
    str = Sprache(_T("Materialgruppe"));
    }

m_tabGruppeMaterialArten.m_curSelected = CEigenschaften::m_comboMaterialArten.GetCurSel();
m_strMaterialArt.TrimLeft();
m_strMaterialArt.TrimRight();
if(!m_strMaterialArt.IsEmpty() && CEigenschaften::m_strMaterialArt.CompareNoCase(m_tabGruppeMaterialArten.Selected().m_bez))
    {
    str = Sprache(_T("Materialart"));
    }

m_tabGruppeOberflaechen.m_curSelected = CEigenschaften::m_comboOberflaechen.GetCurSel();
m_strOberflaeche.TrimLeft();
m_strOberflaeche.TrimRight();
if(!m_strOberflaeche.IsEmpty() && CEigenschaften::m_strOberflaeche.CompareNoCase(m_tabGruppeOberflaechen.Selected().m_bez))
    {
    str = Sprache(_T("Oberfläche"));
    }

m_tabLagerOrte.m_curSelected = CEigenschaften::m_comboLagerOrte.GetCurSel();

/* Nicht Prüfen weil Angezeiger String nicht tab.bez ist
m_strLagerOrt.TrimLeft();
m_strLagerOrt.TrimRight();
if(!m_strLagerOrt.IsEmpty() && CEigenschaften::m_strLagerOrt.CompareNoCase(m_tabLagerOrte.Selected().m_bez))
    {
    str = Sprache(_T("Lagerort"));
    }
*/
m_tabLieferanten.m_curSelected = CEigenschaften::m_comboLieferanten.GetCurSel();
m_strLieferant.TrimLeft();
m_strLieferant.TrimRight();
if(!m_strLieferant.IsEmpty() && CEigenschaften::m_strLieferant.CompareNoCase(m_tabLieferanten.Selected().m_bez))
    {
    str = Sprache(_T("Lieferant"));
    }

if(!str.IsEmpty())
    {
    str += Sprache(_T(" ungültig!"));
    AfxMessageBox(str);
    return;
    }

SSatz ss(g_baseSteinSatz);
// Vor dem Ändern der Eigenschaften, die Artikelgruppe sichern. Wurde diese geändert, müssen die Artikelfelder geleert werden.
CString Sicherung_ArtikelGr(ss.m_ArtikelGr);

ss.m_MatGr = _T("");
ss.m_MatNr = _T("");
ss.m_Material = _T("");
ss.m_OberNr = _T("");
ss.m_Oberflaeche = _T("");
ss.m_ArtikelGr = _T("");
ss.m_ArtikelGrBez = _T("");
ss.m_Lager = _T("");
ss.m_Lieferant = _T("");

if(!CEigenschaften::m_strMaterialGruppe.IsEmpty())
    ss.m_MatGr = m_tabMaterialGruppen.Selected().m_key;
if(!CEigenschaften::m_strMaterialArt.IsEmpty())
    {
    ss.m_MatNr = m_tabGruppeMaterialArten.Selected().Key2();
    ss.m_Material = m_tabGruppeMaterialArten.Selected().m_bez;
    }
if(!CEigenschaften::m_strOberflaeche.IsEmpty())
    {
    ss.m_OberNr = m_tabGruppeOberflaechen.Selected().Key2();
    ss.m_Oberflaeche = m_tabGruppeOberflaechen.Selected().m_bez;
    }
if(!CEigenschaften::m_strArtikelGruppe.IsEmpty())
    {
    ss.m_ArtikelGr = m_tabArtikelGruppen.Selected().m_key;
    ss.m_ArtikelGrBez = m_tabArtikelGruppen.Selected().m_bez;
	if (ss.m_ArtikelGr.CompareNoCase( Sicherung_ArtikelGr ) != 0)
		{
		ss.m_Artikel = _T("");
		ss.m_ArtNr = _T("");
		}
    }
if(!CEigenschaften::m_strLagerOrt.IsEmpty())
    ss.m_Lager = m_tabLagerOrte.Selected().m_key;
if(!CEigenschaften::m_strLieferant.IsEmpty())
    ss.m_Lieferant = m_tabLieferanten.Selected().m_key;

ss.m_TextFeld = m_strEditTextFeld;

g_baseSteinSatz.Set(ss);

CDialog::OnOK();
}
//----------------------------------------------------------------------------
void CEigenschaften::OnSelchangeComboMaterialgruppe() 
{
UpdateData(TRUE);

m_tabMaterialGruppen.m_curSelected = CEigenschaften::m_comboMaterialGruppen.GetCurSel();
m_strMaterialGruppe = m_tabMaterialGruppen.Selected().m_bez;

CString key(CEigenschaften::m_tabMaterialGruppen.Selected().m_key);

m_tabGruppeMaterialArten.m_curSelected = 0;
CEigenschaften::m_tabGruppeMaterialArten.SetGruppe(CEigenschaften::m_tabAlleMaterialArten,key);
m_tabGruppeMaterialArten.SetCombo(m_comboMaterialArten,CEigenschaften::m_strMaterialArt);

m_tabGruppeOberflaechen.m_curSelected = 0;
CEigenschaften::m_tabGruppeOberflaechen.SetGruppe(CEigenschaften::m_tabAlleOberflaechen,key);
m_tabGruppeOberflaechen.SetCombo(m_comboOberflaechen,CEigenschaften::m_strOberflaeche);

UpdateData(FALSE);	
}
//---------------------------------------------------------------------------------------
void CEigenschaften::SetComboLager(const CString& strLagerKey)
{
m_comboLagerOrte.ResetContent();
for(int i = 0; i < m_tabLagerOrte.GetSize(); i++)
    {
    CString str;
    str.Format(_T("%s %s"),m_tabLagerOrte.GetAt(i).m_key,m_tabLagerOrte.GetAt(i).m_bez);
    m_comboLagerOrte.AddString(str);
    }

int index = m_tabLagerOrte.GetIndexByKey(strLagerKey);

if(index >= 0)
    {
    CString str;
    str.Format(_T("%s %s"),m_tabLagerOrte.GetAt(index).m_key,m_tabLagerOrte.GetAt(index).m_bez);
    m_comboLagerOrte.SetCurSel(index);
    m_strLagerOrt = str;
    }
else
    {
    m_comboLagerOrte.SetCurSel(0);
    m_strLagerOrt = _T("");
    }
}

void CEigenschaften::OnEnChangeEditLagerort()
{
	CString str;
	m_ctrlEditLagerort.GetWindowText(str);
	int ix_Lager;
	ix_Lager = m_tabLagerOrte.GetIndexByKey (str);
	if (ix_Lager >= 0)
	{
		m_comboLagerOrte.SetCurSel(ix_Lager);
		m_ctrlEditLagerort.SetWindowText(_T(""));
	}
}
