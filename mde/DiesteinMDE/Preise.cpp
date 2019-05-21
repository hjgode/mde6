// Preise.cpp : implementation file
//

#include "stdafx.h"

#include "Verankerung.h"
#include "VerankStueckliste.h"
#include "Preise.h"
#include "PreiseVerank.h"

/////////////////////////////////////////////////////////////////////////////
// Funktion existiert ist nur für Böse
// Wenn GA-Artikel vorhanden, werden GA-Daten angezeigt, und es kann in Set anzeigen verzewigt werden
// im Set werden die GR-Preise angezeigt
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CPreise dialog

IMPLEMENT_DYNAMIC(CPreise, CDialog)

CPreise::CPreise(CWnd* pParent /*=NULL*/)
	: CDialog(CPreise::IDD, pParent)
{
    m_bIsVerankStein = FALSE;
    m_bBlink = FALSE;   // Blinkflag zum Wechsel
    m_CurIndex = -1;
    }
//---------------------------------------------------------------------------------------
void CPreise::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_STATIC_LAENGE_TX, m_ctrlStaticLaengeText);
    DDX_Control(pDX, IDC_STATIC_RESJANEIN, m_ctrlStaticResjanein);
    DDX_Control(pDX, IDC_STATIC_RESERVIERT, m_ctrlStaticReserviert);
    DDX_Control(pDX, IDC_STATIC_POSITIONEN1, m_ctrlStaticPositionen);
    DDX_Control(pDX, IDC_STATIC_OBERFLAECHE_TX, m_ctrlStaticOberflaecheText);
    DDX_Control(pDX, IDC_STATIC_MATERIAL_TX, m_ctrlStaticMaterialText);
    DDX_Control(pDX, IDC_STATIC_LAGER_TX, m_ctrlStaticLagerText);
    DDX_Control(pDX, IDC_STATIC_DICKE_TX, m_ctrlStaticDickeText);
    DDX_Control(pDX, IDC_STATIC_BREITE_TX, m_ctrlStaticBreiteText);
    DDX_Control(pDX, IDC_STATIC_ARTIKEL_TX, m_ctrlStaticArtikelText);
    DDX_Control(pDX, IDC_STATIC_ARTIKELNUMMER_TX, m_ctrlStaticArtikelnummerText);
    DDX_Control(pDX, IDC_COMBO_SATZNUMMERN, m_ctrlComboSatznummern);
    DDX_Control(pDX, IDC_STATIC_SATZNUMMER, m_ctrlStaticSatznummer);
    DDX_Control(pDX, IDC_STATIC_ARTIKELNUMMER, m_ctrlStaticArtikelnummer);
    DDX_Control(pDX, IDC_STATIC_MATERIAL, m_ctrlStaticMaterial);
    DDX_Control(pDX, IDC_STATIC_OBERFLAECHE, m_ctrlStaticOberflaeche);
    DDX_Control(pDX, IDC_STATIC_LAENGE, m_ctrlStaticLaenge);
    DDX_Control(pDX, IDC_STATIC_BREITE, m_ctrlStaticBreite);
    DDX_Control(pDX, IDC_STATIC_DICKE, m_ctrlStaticDicke);
    DDX_Control(pDX, IDC_STATIC_LAGER, m_ctrlStaticLager);
    DDX_Control(pDX, IDC_STATIC_PREIS1_TX, m_ctrlStaticPreisText[0]);
    DDX_Control(pDX, IDC_STATIC_PREIS2_TX, m_ctrlStaticPreisText[1]);
    DDX_Control(pDX, IDC_STATIC_PREIS3_TX, m_ctrlStaticPreisText[2]);
    DDX_Control(pDX, IDC_STATIC_PREIS4_TX, m_ctrlStaticPreisText[3]);
    DDX_Control(pDX, IDC_STATIC_PREIS1, m_ctrlStaticPreis[0]);
    DDX_Control(pDX, IDC_STATIC_PREIS2, m_ctrlStaticPreis[1]);
    DDX_Control(pDX, IDC_STATIC_PREIS3, m_ctrlStaticPreis[2]);
    DDX_Control(pDX, IDC_STATIC_PREIS4, m_ctrlStaticPreis[3]);
    DDX_Control(pDX, IDC_STATIC_HINWEIS, m_ctrlStaticHinweis);
    DDX_Control(pDX, IDC_STATIC_HINWEIS_TX, m_ctrlStaticHinweisText);
    DDX_Control(pDX, IDC_BUTTON_EINZEL, m_ctrlButtonEinzel);
    DDX_Control(pDX, IDC_STATIC_GEWI, m_ctrlStaticGewicht);
    DDX_Control(pDX, IDC_STATIC_GEWITEXT, m_ctrlStaticGewichtText);
}
//---------------------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CPreise, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_SATZNUMMERN, OnSelchangeComboSatznummern)
	ON_CBN_EDITCHANGE(IDC_COMBO_SATZNUMMERN, OnEditchangeComboSatznummern)
	ON_WM_TIMER()
    ON_STN_CLICKED(IDC_STATIC_LAGER_TX, &CPreise::OnStnClickedStaticLagerTx)
    ON_BN_CLICKED(IDC_BUTTON_EINZEL, &CPreise::OnBnClickedButtonEinzel)
    ON_STN_CLICKED(IDC_STATIC_HINWEIS_TX, &CPreise::OnStnClickedStaticHinweisTx)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreise message handlers
/////////////////////////////////////////////////////////////////////////////
// CInfo message handlers

BOOL CPreise::OnInitDialog()
{
CDialog::OnInitDialog();

TranslateStatic(m_ctrlStaticSatznummer);
TranslateButton(m_ctrlButtonEinzel);
TranslateStatic(m_ctrlStaticArtikelnummer);
TranslateStatic(m_ctrlStaticMaterial);
TranslateStatic(m_ctrlStaticOberflaeche);
TranslateStatic(m_ctrlStaticLaenge);
TranslateStatic(m_ctrlStaticBreite);
TranslateStatic(m_ctrlStaticDicke);
TranslateStatic(m_ctrlStaticLager);
TranslateStatic(m_ctrlStaticHinweis);
TranslateStatic(m_ctrlStaticGewicht);
TranslateStatic(m_ctrlStaticGewichtText);

m_tabLagerOrte.Read();
m_tabPreislisten.Read();

m_ctrlButtonEinzel.GetWindowText(m_strEinzelAnsicht);
m_ctrlButtonEinzel.ShowWindow(0);

m_ctrlStaticPreis[0].SetWindowText(_T(""));
m_ctrlStaticPreis[1].SetWindowText(_T(""));
m_ctrlStaticPreis[2].SetWindowText(_T(""));
m_ctrlStaticPreis[3].SetWindowText(_T(""));
if(m_tabPreislisten.GetSize())  // von 10 möglichen Preislisten können max. 4 aktiviert sein
    {
    int j = 0;
    int k = 0;
    while(j < min(10,m_tabPreislisten.GetSize()))
        {
        if(g_Optionen.PreislisteEnabled(j))
            {
            m_ctrlStaticPreis[k].SetWindowText(m_tabPreislisten.GetAt(j).m_value1 + _T(":"));
            m_strWaehrung[k] = m_tabPreislisten.GetAt(j).m_value2;
            k++;
            if(k > 3) break;
            }
        j++;
        }
    }

CString str;
str.Format(_T("%d %s"),m_pSteinSaetze->Anzahl(),Sprache(_T("Sätze")));
m_ctrlStaticPositionen.SetWindowText(str);

for(int i = 0; i < m_pSteinSaetze->Anzahl(); i++)
    {
    m_ctrlComboSatznummern.AddString(m_pSteinSaetze->SteinSatz(i).Nummer());
    }

AnzeigePlattenDaten(0);
    
return TRUE;  // return TRUE  unless you set the focus to a control
}
//---------------------------------------------------------------------------------------
void CPreise::AnzeigePlattenDaten(int index)
{
CSteinSatz satz;    // Alle Felder leer

if((index >= 0) && (index < m_pSteinSaetze->Anzahl()))
    {
    satz = m_pSteinSaetze->arr[index];
    m_ctrlComboSatznummern.SetCurSel(index);
    m_CurIndex = index;
    }
else
    m_CurIndex = -1;

AnzeigeTexte(satz);
}
//---------------------------------------------------------------------------------------
void CPreise::AnzeigeTexte(const CSteinSatz& satz)
{
SSatz ss(satz);

m_ctrlStaticArtikelnummerText.SetWindowText(ss.m_ArtNr);
m_ctrlStaticArtikelText.SetWindowText(ss.m_Artikel);
m_ctrlStaticMaterialText.SetWindowText(ss.m_Material);
m_ctrlStaticOberflaecheText.SetWindowText(ss.m_Oberflaeche);

m_ctrlStaticLagerText.SetWindowText(_T(""));
int lix = m_tabLagerOrte.GetIndexByKey(ss.m_Lager);
if(lix >= 0 && (lix < m_tabLagerOrte.GetSize()))
    m_ctrlStaticLagerText.SetWindowText(m_tabLagerOrte.GetAt(lix).m_key + _T(" ") + m_tabLagerOrte.GetAt(lix).m_bez);

m_ctrlStaticLaengeText.SetWindowText(ss.m_Laenge);
m_ctrlStaticDickeText.SetWindowText(ss.m_Dicke);
m_ctrlStaticBreiteText.SetWindowText(ss.m_Breite);
m_ctrlStaticGewichtText.SetWindowText(ss.m_Gewicht);
    
CString resstr;
if(ss.m_ResTyp.IsEmpty())
    resstr = "Ja";
else if(ss.m_ResTyp == _T("1"))
    resstr = "Angebot";
else if(ss.m_ResTyp == _T("2"))
    resstr = "Auftrag";

if(ss.m_ResFuerAuftrag.IsEmpty())
    m_ctrlStaticResjanein.SetWindowText(Sprache(_T("Nein")));
else
    m_ctrlStaticResjanein.SetWindowText(Sprache(resstr));

KillTimer(12);
m_bIsVerankStein = FALSE;
m_bBlink = FALSE;

BOOL startTimer = FALSE;
int ix = -1;
if(m_pVerankerungen->FindeSteinNummer(ss.m_Nummer,m_CurVerank,ix))  // Stein gehört zu einer verankerung
    {
    //CString st;
    //st.Format(_T("Verank: %s"),m_CurVerank.m_Name);
    m_ctrlButtonEinzel.SetWindowText(m_strEinzelAnsicht);
    m_ctrlButtonEinzel.ShowWindow(1);
    ShowPreise(m_CurVerank.m_Preise);
    m_ctrlStaticHinweisText.SetWindowText(m_CurVerank.m_Hinweis);
    m_bIsVerankStein = TRUE;
    startTimer = TRUE;
    }
else
    {
    m_ctrlStaticHinweisText.SetWindowText(ss.m_Hinweis);
    m_ctrlButtonEinzel.ShowWindow(0);
    ShowPreise(ss.m_GR_Preis);
    }

if(startTimer)
    SetTimer(12,500,NULL);
}
//---------------------------------------------------------------------------------------
void CPreise::ShowPreise(CString Preise[])
{
m_ctrlStaticPreisText[0].SetWindowText(_T(""));
m_ctrlStaticPreisText[1].SetWindowText(_T(""));
m_ctrlStaticPreisText[2].SetWindowText(_T(""));
m_ctrlStaticPreisText[3].SetWindowText(_T(""));
if(m_tabPreislisten.GetSize())  // von 10 möglichen Preislisten können max. 4 aktiviert sein
    {
    int j = 0;
    int k = 0;
    while(j < min(10,m_tabPreislisten.GetSize()))
        {
        if(g_Optionen.PreislisteEnabled(j))
            {
            m_ctrlStaticPreisText[k].ShowWindow(1); // Damit sofort Preis angezeigt wird
            m_ctrlStaticPreisText[k].SetWindowText(Preise[j] + _T(" ") + m_strWaehrung[k]);
            k++;
            if(k > 3) break;
            }
        j++;
        }
    }
}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
BOOL CPreise::PreTranslateMessage(MSG* pMsg) 
{
CString errMsg;

	CString barCode;// = m_pScanner->WaitForDecode(2000,errMsg);
	if(pMsg->message==WM_KEYDOWN)
		if(pMsg->wParam==SCAN_KEY)
			{ barCode = m_pScanner->WaitForDecode(2000,errMsg); return TRUE; }
	if(pMsg->message==WM_SCANDATA){
		TCHAR data[2048];
		wsprintf(data,L"%s",pMsg->wParam);
		barCode=data;
		DEBUGMSG(1, (L"Benutzer: Barcode Daten='%s'\n", barCode));
	}

if(!barCode.IsEmpty())
    {
    int index = FindNumber(barCode);
    if(index >= 0)
        {
        PlaySoundScan();
        AnzeigePlattenDaten(index);     // Wenn index < 0 oder ungültig, werden alle Felder geleert
        }
    else
        {
        PlaySoundOther();
        AnzeigePlattenDaten(-1);     // Wenn index < 0 oder ungültig, werden alle Felder geleert
        m_ctrlComboSatznummern.SetWindowText(barCode);  // und der gelesene Barcode wird angezeigt
        }
	}
else
    {
    if(!errMsg.IsEmpty())
        AfxMessageBox(errMsg);
    }
return CDialog::PreTranslateMessage(pMsg);
}
//-----------------------------------------------------------------------------------
int CPreise::FindNumber(const CString& strNumber) const
{
int index = -1;
CPreise::m_pSteinSaetze->FoundAt(strNumber,index);
return index;
}
//-----------------------------------------------------------------------------------
void CPreise::OnSelchangeComboSatznummern() 
{
int index = m_ctrlComboSatznummern.GetCurSel();
AnzeigePlattenDaten(index);
}
//------------------------------------------------------------------------------------
void CPreise::OnEditchangeComboSatznummern() 
{
int cursel;

CString nrstr;
m_ctrlComboSatznummern.GetWindowText(nrstr);

if(m_pSteinSaetze->FoundAt(nrstr,cursel))
    {
    m_ctrlComboSatznummern.SetCurSel(cursel);
    AnzeigePlattenDaten(cursel);
    }
else
    {
    CSteinSatz satz;
    AnzeigeTexte(satz);
    }
m_ctrlComboSatznummern.SetEditSel(-1,0); // Notwendig
}
//------------------------------------------------------------------------------------
void CPreise::OnTimer(UINT nIDEvent) 
{
CDialog::OnTimer(nIDEvent);

if(m_bBlink)    // Blinkwechsel-Flag
    {
    if(m_bIsVerankStein)
        {
        m_ctrlButtonEinzel.SetWindowText(m_strEinzelAnsicht);
        }
    m_bBlink = FALSE;
    }
else
    {
    if(m_bIsVerankStein)
        {
        m_ctrlButtonEinzel.SetWindowText(_T(""));
        }
    m_bBlink = TRUE;
    }
}
//-----------------------------------------------------------------------------
void CPreise::OnStnClickedStaticLagerTx()
{
CString str;
m_ctrlStaticLagerText.GetWindowText(str);
AfxMessageBox(str,MB_ICONINFORMATION);
}
//-----------------------------------------------------------------------------
void CPreise::OnStnClickedStaticHinweisTx()
{
CString str;
m_ctrlStaticHinweisText.GetWindowText(str);
AfxMessageBox(str,MB_ICONINFORMATION);
}
//-----------------------------------------------------------------------------
void CPreise::OnBnClickedButtonEinzel()
{
//CPreiseVerank dlg;
CVerankStueckliste dlg;

dlg.m_pSteinSaetze = m_pSteinSaetze;
dlg.m_pCurVerank = &m_CurVerank;
dlg.m_startSteinSatzIx = m_CurIndex;
dlg.m_pScanner = m_pScanner;

dlg.DoModal();	

if(!dlg.m_backSteinNummer.IsEmpty())
    {
    int index = FindNumber(dlg.m_backSteinNummer);
    if(index >= 0)
        {
        PlaySoundScan();
        AnzeigePlattenDaten(index);     // Wenn index < 0 oder ungültig, werden alle Felder geleert
        }
    else
        {
        PlaySoundOther();
        AnzeigePlattenDaten(-1);     // Wenn index < 0 oder ungültig, werden alle Felder geleert
        m_ctrlComboSatznummern.SetWindowText(dlg.m_backSteinNummer);  // und der gelesene Barcode wird angezeigt
        }
    }
m_ctrlComboSatznummern.SetFocus();
}

