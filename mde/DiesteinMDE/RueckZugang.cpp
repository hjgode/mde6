// RueckZugang.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "RueckZugang.h"


// CRueckZugang-Dialogfeld

IMPLEMENT_DYNAMIC(CRueckZugang, CDialog)

CRueckZugang::CRueckZugang(CWnd* pParent /*=NULL*/)
	: CDialog(CRueckZugang::IDD, pParent)
{

}

CRueckZugang::~CRueckZugang()
{
}

void CRueckZugang::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_STEINNRALT, m_ctrlStaticSteinNrAlt);
    DDX_Control(pDX, IDC_STATIC_STEINNR, m_ctrlStaticSteinNr);
    DDX_Control(pDX, IDC_STATIC_ARTIKEL, m_ctrlStaticArtikel);
    DDX_Control(pDX, IDC_STATIC_MATERIAL, m_ctrlStaticMaterial);
    DDX_Control(pDX, IDC_STATIC_OBERFLAECHE, m_ctrlStaticOberflaeche);
    DDX_Control(pDX, IDC_STATIC_LAGER, m_ctrlStaticLager);
    DDX_Control(pDX, IDC_STATIC_FEHLECKE, m_ctrlStaticFehlecke);
    DDX_Control(pDX, IDC_EDIT_STEINNRALT, m_ctrlEditSteinNrAlt);
    DDX_Control(pDX, IDC_EDIT_STEINNR, m_ctrlEditSteinNr);
    DDX_Control(pDX, IDC_EDIT_LAENGE, m_ctrlEditLaenge);
    DDX_Control(pDX, IDC_EDIT_BREITE, m_ctrlEditBreite);
    DDX_Control(pDX, IDC_EDIT_FEHLLAENGE, m_ctrlEditFehlLaenge);
    DDX_Control(pDX, IDC_EDIT_FEHLBREITE, m_ctrlEditFehlBreite);
    DDX_Control(pDX, IDC_COMBO_FEHLER1, m_ctrlComboFehler1);
    DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
    DDX_Control(pDX, IDOK, m_ctrlButtonOk);
    DDX_Control(pDX, IDC_STATIC_ARTIKELTEXT, m_ctrlStaticArtikelText);
    DDX_Control(pDX, IDC_STATIC_MATERIALTEXT, m_ctrlStaticMaterialText);
    DDX_Control(pDX, IDC_STATIC_OBERFLTEXT, m_ctrlStaticOberflText);
    DDX_Control(pDX, IDC_STATIC_LAGERTEXT, m_ctrlStaticLagerText);
    DDX_Control(pDX, IDC_STATIC_DICKE, m_ctrlStaticDicke);
    DDX_Control(pDX, IDC_STATIC_DICKETEXT, m_ctrlStaticDickeText);
    DDX_Control(pDX, IDC_STATIC_HINWEIS, m_ctrlStaticHinweis);
    DDX_Control(pDX, IDC_EDIT_HINWEIS, m_ctrlEditHinweis);
    DDX_Control(pDX, IDC_STATIC_LAENGE, m_ctrlStaticLaenge);
    DDX_Control(pDX, IDC_STATIC_BREITE, m_ctrlStaticBreite);
    DDX_Control(pDX, IDC_STATIC_TITELTEXT, m_ctrlStaticTitelText);
}


BEGIN_MESSAGE_MAP(CRueckZugang, CDialog)
    ON_BN_CLICKED(IDOK, &CRueckZugang::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CRueckZugang::OnBnClickedCancel)
    ON_EN_KILLFOCUS(IDC_EDIT_LAENGE, &CRueckZugang::OnEnKillfocusEditLaenge)
    ON_EN_KILLFOCUS(IDC_EDIT_BREITE, &CRueckZugang::OnEnKillfocusEditBreite)
    ON_EN_KILLFOCUS(IDC_EDIT_FEHLLAENGE, &CRueckZugang::OnEnKillfocusEditFehllaenge)
    ON_EN_KILLFOCUS(IDC_EDIT_FEHLBREITE, &CRueckZugang::OnEnKillfocusEditFehlbreite)
END_MESSAGE_MAP()


//-----------------------------------------------------------------------------
BOOL CRueckZugang::OnInitDialog() 
{
	CDialog::OnInitDialog();

TranslateStatic(m_ctrlStaticTitelText);
TranslateStatic(m_ctrlStaticSteinNrAlt);
TranslateStatic(m_ctrlStaticSteinNr);
TranslateStatic(m_ctrlStaticArtikel);
TranslateStatic(m_ctrlStaticMaterial);
TranslateStatic(m_ctrlStaticOberflaeche);
TranslateStatic(m_ctrlStaticLager);
TranslateStatic(m_ctrlStaticDicke);
TranslateStatic(m_ctrlStaticHinweis);
TranslateStatic(m_ctrlStaticLaenge);
TranslateStatic(m_ctrlStaticBreite);
TranslateStatic(m_ctrlStaticFehlecke);

TranslateButton(m_ctrlButtonOk);
TranslateButton(m_ctrlButtonCancel);

m_FehlerTabelle.Read();
C2String s2;
m_FehlerTabelle.InsertAt(0,s2); // Leerauswahl an den Anfang

for(int i = 0; i < m_FehlerTabelle.GetSize(); i++)
    {
    m_ctrlComboFehler1.AddString(m_FehlerTabelle.GetAt(i).m_bez);
    }
m_ctrlComboFehler1.SetCurSel(0);

AnzeigePlattenDaten();

m_ctrlEditSteinNr.SetFocus();
return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//-----------------------------------------------------------------------------
void CRueckZugang::AnzeigePlattenDaten()
{
SSatz s(*m_pSatz);
m_ctrlEditSteinNrAlt.SetWindowText(s.m_Nummer);
m_ctrlStaticArtikelText.SetWindowText(s.m_Artikel);
m_ctrlStaticMaterialText.SetWindowText(s.m_Material);
m_ctrlStaticOberflText.SetWindowText(s.m_Oberflaeche);
m_ctrlStaticLagerText.SetWindowText(s.m_Lager);
m_ctrlStaticDickeText.SetWindowText(s.m_Dicke);
m_ctrlEditHinweis.SetWindowText(s.m_Hinweis);
m_ctrlEditLaenge.SetWindowText(s.m_Laenge);
m_ctrlEditBreite.SetWindowText(s.m_Breite);
m_ctrlEditFehlLaenge.SetWindowText(s.m_FehlLaenge);
m_ctrlEditFehlBreite.SetWindowText(s.m_FehlBreite);
SetComboFehlecke(s.m_FehlNummer);
}
//-----------------------------------------------------------------------------
void CRueckZugang::SetComboFehlecke(const CString& strnum)
{
int ix = m_FehlerTabelle.GetIndexByKey(strnum);
if(ix >= 0)
    m_ctrlComboFehler1.SetCurSel(ix);
else
    m_ctrlComboFehler1.SetCurSel(-1);
}
//-----------------------------------------------------------------------------
// Ok oder Hinzufügen
void CRueckZugang::OnBnClickedOk()
{
CString str;

m_ctrlEditLaenge.GetWindowText(str);
if(NoValueSetFocus(str,m_ctrlEditLaenge))
    return;
m_ctrlEditBreite.GetWindowText(str);
if(NoValueSetFocus(str,m_ctrlEditBreite))
    return;
m_ctrlEditFehlLaenge.GetWindowText(str);
if(NoValueSetFocus(str,m_ctrlEditFehlLaenge))
    return;
m_ctrlEditFehlBreite.GetWindowText(str);
if(NoValueSetFocus(str,m_ctrlEditFehlBreite))
    return;

SSatz ss(*m_pSatz);

// Neue Nummer abfragen
m_ctrlEditSteinNr.GetWindowText(str);
str.Trim();
int ix;
if(str.IsEmpty())// Nummer leer
    {
    m_ctrlEditSteinNr.SetFocus();
    m_ctrlEditSteinNr.SetSel(0,-1,FALSE);  // Alles selektieren
    return;
    }
if(m_pAuftrag->m_Positionen.FoundAt(str,ix) || m_pSteinSaetze->FoundAt(str,ix))   // Nummer bereits verwendet
    {
    PlaySoundOther();
    AfxMessageBox(Sprache(_T("Die Nummer ist bereits vergeben!")),MB_OK);
    m_ctrlEditSteinNr.SetFocus();
    m_ctrlEditSteinNr.SetSel(0,-1,FALSE);  // Alles selektieren
    return;
    }

ss.m_NummerParent = ss.m_Nummer;            // alte Nummer sichern
ss.m_Nummer = str;                          // Neue Numer

m_ctrlEditHinweis.GetWindowText(ss.m_Hinweis);
m_ctrlEditLaenge.GetWindowText(ss.m_Laenge);
m_ctrlEditBreite.GetWindowText(ss.m_Breite);
m_ctrlEditFehlLaenge.GetWindowText(ss.m_FehlLaenge);
m_ctrlEditFehlBreite.GetWindowText(ss.m_FehlBreite);
ix = m_ctrlComboFehler1.GetCurSel();
if(ix >= 0)
    {
    ss.m_FehlNummer = m_FehlerTabelle.GetAt(ix).m_key;
    }
m_pSatz->Set(ss);

OnOK();
}
//-----------------------------------------------------------------------------
void CRueckZugang::OnBnClickedCancel()
{
OnCancel();
}
//-----------------------------------------------------------------------------
BOOL CRueckZugang::PreTranslateMessage(MSG* pMsg) 
{
CString errMsg;

	CString barCode;// = m_pScanner->WaitForDecode(2000,errMsg);
	if(pMsg->message==WM_KEYDOWN)
		if(pMsg->wParam==SCAN_KEY)
			barCode = m_pScanner->WaitForDecode(2000,errMsg);
	if(pMsg->message==WM_SCANDATA){
		TCHAR data[2048];
		wsprintf(data,L"%s",pMsg->wParam);
		barCode=data;
		DEBUGMSG(1, (L"Benutzer: Barcode Daten='%s'\n", barCode));
	}

if(!barCode.IsEmpty())
    {
    int ix;
    if(m_pSteinSaetze->FoundAt(barCode,ix))
        {
        PlaySoundOther();
        AfxMessageBox(Sprache(_T("Die Nummer ist bereits vergeben!")),MB_OK);
        return CDialog::PreTranslateMessage(pMsg);;
        }
    else
        {
        PlaySoundScan();
        m_ctrlEditSteinNr.SetWindowText(barCode);
        }
    }
else
    {
    if(!errMsg.IsEmpty())
        AfxMessageBox(errMsg);
    }
return CDialog::PreTranslateMessage(pMsg);
}
//-----------------------------------------------------------------------------
void CRueckZugang::OnEnKillfocusEditLaenge()
{
ValueExeed400(m_ctrlEditLaenge);
}
//-----------------------------------------------------------------------------
void CRueckZugang::OnEnKillfocusEditBreite()
{
ValueExeed400(m_ctrlEditBreite);
}
//-----------------------------------------------------------------------------
void CRueckZugang::OnEnKillfocusEditFehllaenge()
{
ValueExeed400(m_ctrlEditFehlLaenge);
}
//-----------------------------------------------------------------------------
void CRueckZugang::OnEnKillfocusEditFehlbreite()
{
ValueExeed400(m_ctrlEditFehlBreite);
}
