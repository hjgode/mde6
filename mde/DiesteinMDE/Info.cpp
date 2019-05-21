// Info.cpp : implementation file
//

#include "stdafx.h"

#include "Info.h"

/////////////////////////////////////////////////////////////////////////////
// CInfo dialog

IMPLEMENT_DYNAMIC(CInfo,CDialog)

CInfo::CInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CInfo::IDD, pParent)
{
	m_nEigenschaften = -1;
    m_bBlink = FALSE;
}

void CInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_LAGERORT_TX, m_ctrlStaticLagerortTx);
	DDX_Control(pDX, IDC_STATIC_HINWEIS_TX, m_ctrlStaticHinweisTx);
	DDX_Control(pDX, IDC_STATIC_STEINSAETZE, m_ctrlStaticSteinsaetze);
	DDX_Control(pDX, IDC_STATIC_RES, m_ctrlStaticReserviert);
	DDX_Control(pDX, IDC_STATIC_OBERFLAECHE_TX, m_ctrlStaticOberflaecheTx);
	DDX_Control(pDX, IDC_STATIC_MENGE2V, m_ctrlStaticMenge2V);
	DDX_Control(pDX, IDC_STATIC_MENGE2, m_ctrlStaticMenge2);
	DDX_Control(pDX, IDC_STATIC_MENGE1V, m_ctrlStaticMenge1V);
	DDX_Control(pDX, IDC_STATIC_MENGE1, m_ctrlStaticMenge1);
	DDX_Control(pDX, IDC_STATIC_MATERIAL_TX, m_ctrlStaticMaterialTx);
	DDX_Control(pDX, IDC_STATIC_LIEFERANT_TX, m_ctrlStaticLieferantTx);
	DDX_Control(pDX, IDC_STATIC_ARTIKEL_TX, m_ctrlStaticArtikelTx);
	DDX_Control(pDX, IDC_EDIT_LAENGE, m_ctrlEditLaenge);
	DDX_Control(pDX, IDC_EDIT_FEHLNUMMER, m_ctrlEditFehlnummer);
	DDX_Control(pDX, IDC_EDIT_FEHLLAENGE, m_ctrlEditFehllaenge);
	DDX_Control(pDX, IDC_EDIT_FEHLBREITE, m_ctrlEditFehlbreite);
	DDX_Control(pDX, IDC_EDIT_DICKE, m_ctrlEditDicke);
	DDX_Control(pDX, IDC_EDIT_BREITE, m_ctrlEditBreite);
	DDX_Control(pDX, IDC_STATIC_FEHLNUMMER, m_ctrlStaticFehlnummer);
	DDX_Control(pDX, IDC_STATIC_FEHLBREITE, m_ctrlStaticFehlbreite);
	DDX_Control(pDX, IDC_STATIC_FEHLLAENGE, m_ctrlStaticFehllaenge);
	DDX_Control(pDX, IDC_STATIC_FEHLECKE, m_ctrlStaticFehlecke);
	DDX_Control(pDX, IDC_STATIC_DICKE, m_ctrlStaticDicke);
	DDX_Control(pDX, IDC_STATIC_BREITE, m_ctrlStaticBreite);
	DDX_Control(pDX, IDC_STATIC_LAENGE, m_ctrlStaticLaenge);
	DDX_Control(pDX, IDC_STATIC_HINWEIS, m_ctrlStaticHinweis);
	DDX_Control(pDX, IDC_STATIC_LIEFERANT, m_ctrlStaticLieferant);
	DDX_Control(pDX, IDC_STATIC_LAGERORT, m_ctrlStaticLagerort);
	DDX_Control(pDX, IDC_STATIC_OBERFLAECHE, m_ctrlStaticOberflaeche);
	DDX_Control(pDX, IDC_STATIC_MATERIAL, m_ctrlStaticMaterial);
	DDX_Control(pDX, IDC_STATIC_ARTIKEL, m_ctrlStaticArtikel);
	DDX_Control(pDX, IDC_STATIC_VERFUEGBAR, m_ctrlStaticVerfuegbar);
	DDX_Control(pDX, IDC_STATIC_MENGE, m_ctrlStaticMenge);
	DDX_Control(pDX, IDC_STATIC_STEINNUMMER, m_ctrlStaticSteinnummer);
	DDX_Control(pDX, IDC_COMBO_STEINNUMMER, m_ctrlNummernListe);
	DDX_Control(pDX, IDC_EDIT_GEWICH, m_ctrlEditGewicht);
	DDX_Control(pDX, IDC_STATIC_GEWICH, m_ctrlStaticGewicht);
	DDX_Control(pDX, IDC_STATIC_BRUTTOMASSE, m_ctrlStaticBruttomasse);
}

BEGIN_MESSAGE_MAP(CInfo, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_STEINNUMMER, OnSelchangeComboSteinnummer)
	ON_CBN_EDITCHANGE(IDC_COMBO_STEINNUMMER, OnEditchangeComboSteinnummer)
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfo message handlers

BOOL CInfo::OnInitDialog()
{
CDialog::OnInitDialog();

CenterWindow(GetDesktopWindow());	// center to the hpc screen

TranslateStatic(m_ctrlStaticSteinnummer);
TranslateStatic(m_ctrlStaticMenge);
TranslateStatic(m_ctrlStaticVerfuegbar);
TranslateStatic(m_ctrlStaticArtikel);
TranslateStatic(m_ctrlStaticMaterial);
TranslateStatic(m_ctrlStaticOberflaeche);
TranslateStatic(m_ctrlStaticLagerort);
TranslateStatic(m_ctrlStaticLieferant);
TranslateStatic(m_ctrlStaticHinweis);

TranslateStatic(m_ctrlStaticLaenge);
TranslateStatic(m_ctrlStaticBreite);
TranslateStatic(m_ctrlStaticDicke);

TranslateStatic(m_ctrlStaticFehlecke);
TranslateStatic(m_ctrlStaticFehllaenge);
TranslateStatic(m_ctrlStaticFehlbreite);
TranslateStatic(m_ctrlStaticFehlnummer);
TranslateStatic(m_ctrlStaticGewicht);

//Schriftgröße für die Brutto-Maße festlegen
CFont *m_Font1 = new CFont;
m_Font1->CreatePointFont(85, _T("MS Shell Dlg"));
m_ctrlStaticBruttomasse.SetFont(m_Font1);

m_tabLagerOrte.Read();
m_tabLieferanten.Read();
m_tabFehlerbezeichnung.Read();

CString str;
str.Format(_T("%d %s"),m_pSteinSaetze->Anzahl(),Sprache(_T("Steinsätze")));
m_ctrlStaticSteinsaetze.SetWindowText(str);

for(int i = 0; i < m_pSteinSaetze->Anzahl(); i++)
    {
    m_ctrlNummernListe.AddString(m_pSteinSaetze->SteinSatz(i).Nummer());
    }

// die erste Platte soll NICHT mehr automatisch ausgewählt werden ch 06.03.2013
AnzeigePlattenDaten(-1);

return TRUE;  // return TRUE  unless you set the focus to a control
}
//---------------------------------------------------------------------------------------
void CInfo::AnzeigePlattenDaten(int index)
{
CSteinSatz satz;    // Alle Felder leer

if((index >= 0) && (index < m_pSteinSaetze->Anzahl()))
    {
    satz = m_pSteinSaetze->arr[index];
    m_ctrlNummernListe.SetCurSel(index);
    }

AnzeigeTexte(satz);
}
//---------------------------------------------------------------------------------------
void CInfo::AnzeigeTexte(const CSteinSatz& satz)
{
SSatz ss(satz);

CString str;

m_ctrlStaticMenge1.SetWindowText(ss.m_Menge1 + _T(" ") + ss.m_ME1);

if(satz.Menge2() != 0.)
    m_ctrlStaticMenge2.SetWindowText(ss.m_Menge2 + _T(" ") + ss.m_ME2);
else
    m_ctrlStaticMenge2.SetWindowText(_T(""));

if(!ss.m_Menge1Verfuegbar.IsEmpty()) // Wenn verwendet, immer anzeigen
    m_ctrlStaticMenge1V.SetWindowText(ss.m_Menge1Verfuegbar + _T(" ") + ss.m_ME1);
else
    m_ctrlStaticMenge1V.SetWindowText(_T(""));

if(!ss.m_Menge2Verfuegbar.IsEmpty())
    m_ctrlStaticMenge2V.SetWindowText(ss.m_Menge2Verfuegbar + _T(" ") + ss.m_ME2);
else
    m_ctrlStaticMenge2V.SetWindowText(_T(""));

m_ctrlStaticArtikelTx.SetWindowText(ss.m_Artikel);
m_ctrlStaticMaterialTx.SetWindowText(ss.m_Material);
m_ctrlStaticOberflaecheTx.SetWindowText(ss.m_Oberflaeche);

m_ctrlStaticLagerortTx.SetWindowText(_T(""));
int lix = m_tabLagerOrte.GetIndexByKey(ss.m_Lager);
if(lix >= 0 && (lix < m_tabLagerOrte.GetSize()))
    m_ctrlStaticLagerortTx.SetWindowText(m_tabLagerOrte.GetAt(lix).m_key + _T(" ") + m_tabLagerOrte.GetAt(lix).m_bez);

m_ctrlStaticLieferantTx.SetWindowText(_T(""));
lix = m_tabLieferanten.GetIndexByKey(ss.m_Lieferant);
if(lix >= 0 && (lix < m_tabLieferanten.GetSize()))
    m_ctrlStaticLieferantTx.SetWindowText(m_tabLieferanten.GetAt(lix).m_bez);

m_ctrlStaticHinweisTx.SetWindowText(ss.m_Hinweis);

m_ctrlEditLaenge.SetWindowText(ss.m_Laenge);
m_ctrlEditDicke.SetWindowText(ss.m_Dicke);
m_ctrlEditBreite.SetWindowText(ss.m_Breite);
m_ctrlEditGewicht.SetWindowText(ss.m_Gewicht);

CString brutto = _T("");
if (ss.m_Artikel == _T("Block") )
{
	if (ss.m_LaengeBrutto.GetLength() > 0)
		brutto = brutto + ss.m_LaengeBrutto + _T(" x ");
	if (ss.m_BreiteBrutto.GetLength() > 0)
		brutto = brutto + ss.m_BreiteBrutto + _T(" x ");	
	if (ss.m_DickeBrutto.GetLength() > 0)
		brutto = brutto + ss.m_DickeBrutto;
	if (brutto.GetLength() > 0)
		brutto = Sprache(_T("Brutto(L/B/D)")) + _T("   ") + brutto;
}
m_ctrlStaticBruttomasse.SetWindowText(brutto);

m_ctrlEditFehllaenge.SetWindowText(ss.m_FehlLaenge);
m_ctrlEditFehlbreite.SetWindowText(ss.m_FehlBreite);
CString strFehl = m_tabFehlerbezeichnung.GetItemByKey(ss.m_FehlNummer).m_bez;
m_ctrlEditFehlnummer.SetWindowText(strFehl);

KillTimer(12);
m_bBlink = FALSE;
m_ctrlStaticReserviert.SetWindowText(_T(""));
if(g_Optionen.BoeseEnabled())
    {
    if(!ss.m_ResFuerAuftrag.IsEmpty())
        m_ctrlStaticReserviert.SetWindowText(_T("RESERVIERT"));
    }
else
    {
    if(!ss.m_Menge1Verfuegbar.IsEmpty())
        {
        if(CSteinSatz::StringToDouble(ss.m_Menge1Verfuegbar) < CSteinSatz::StringToDouble(ss.m_Menge1))
            {
            m_ctrlStaticReserviert.SetWindowText(Sprache(_T("RESERVIERT")));
            SetTimer(12,500,NULL);
            m_bBlink = TRUE;
            }
        else
            m_ctrlStaticReserviert.SetWindowText(_T(""));
        }
    }
}
//------------------------------------------------------------------------------------
void CInfo::OnTimer(UINT nIDEvent) 
{
CDialog::OnTimer(nIDEvent);
if(m_bBlink)
    {
    m_ctrlStaticReserviert.ShowWindow(1);
    m_bBlink = FALSE;
    }
else
    {
    m_ctrlStaticReserviert.ShowWindow(0);
    m_bBlink = TRUE;
    }
}
//---------------------------------------------------------------------------------------
void CInfo::OnSelchangeComboSteinnummer() 
{
int index = m_ctrlNummernListe.GetCurSel();
AnzeigePlattenDaten(index);
}

//---------------------------------------------------------------------------------------
BOOL CInfo::PreTranslateMessage(MSG* pMsg) 
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

//    int index = m_ctrlNummernListe.FindStringExact(0,barCode);
    int index = FindNumber(barCode);
    if(index >= 0)
        PlaySoundScan();
    else
        PlaySoundOther();
    AnzeigePlattenDaten(index);     // Wenn index < 0 oder ungültig, werden alle Felder geleert

    m_ctrlNummernListe.SetWindowText(barCode);  // und der gelesene Barcode wird angezeigt
	}
else
    {
    if(!errMsg.IsEmpty())
        AfxMessageBox(errMsg);
    }

return CDialog::PreTranslateMessage(pMsg);
}
//-----------------------------------------------------------------------------------
int CInfo::FindNumber(const CString& strNumber) const
{
int index = -1;
CInfo::m_pSteinSaetze->FoundAt(strNumber,index);
return index;
}
//-----------------------------------------------------------------------------------
void CInfo::OnEditchangeComboSteinnummer() 
{
int cursel;

CString nrstr;
m_ctrlNummernListe.GetWindowText(nrstr);

if(m_pSteinSaetze->FoundAt(nrstr,cursel))
    {
    m_ctrlNummernListe.SetCurSel(cursel);
    AnzeigePlattenDaten(cursel);
    }
else
    {
    CSteinSatz satz;
    AnzeigeTexte(satz);
    }

m_ctrlNummernListe.SetEditSel(-1,0);
}
//-----------------------------------------------------------------------------------------
