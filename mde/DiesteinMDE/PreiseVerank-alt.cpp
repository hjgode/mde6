// PreiseVerank.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "Verankerung.h"
#include "PreiseVerank.h"

/////////////////////////////////////////////////////////////////////////////
// Funktion existiert ist nur für Böse
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CPreiseVerank dialog

IMPLEMENT_DYNAMIC(CPreiseVerank, CDialog)

CPreiseVerank::CPreiseVerank(CWnd* pParent /*=NULL*/)
	: CDialog(CPreiseVerank::IDD, pParent)
{
    m_enableSetFunktion = FALSE;    // Set-Funktion deaktiviert
    m_bGAaktiv = FALSE;
    m_bBlink = FALSE;   // Blinkflag für Preisanzeige
    }
//---------------------------------------------------------------------------------------
void CPreiseVerank::DoDataExchange(CDataExchange* pDX)
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
    DDX_Control(pDX, IDC_BUTTON_SET, m_ctrlButtonSet);
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
}
//---------------------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CPreiseVerank, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_SATZNUMMERN, OnSelchangeComboSatznummern)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_CBN_EDITCHANGE(IDC_COMBO_SATZNUMMERN, OnEditchangeComboSatznummern)
	ON_WM_TIMER()
    ON_STN_CLICKED(IDC_STATIC_LAGER_TX, &CPreiseVerank::OnStnClickedStaticLagerTx)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreiseVerank message handlers
/////////////////////////////////////////////////////////////////////////////
// CInfo message handlers

BOOL CPreiseVerank::OnInitDialog()
{
CDialog::OnInitDialog();

TranslateButton(m_ctrlButtonSet);
TranslateStatic(m_ctrlStaticArtikelnummer);
TranslateStatic(m_ctrlStaticMaterial);
TranslateStatic(m_ctrlStaticOberflaeche);
TranslateStatic(m_ctrlStaticLaenge);
TranslateStatic(m_ctrlStaticBreite);
TranslateStatic(m_ctrlStaticDicke);
TranslateStatic(m_ctrlStaticLager);
TranslateStatic(m_ctrlStaticHinweis);

m_tabLagerOrte.Read();
m_tabPreislisten.Read();

m_ctrlButtonSet.ShowWindow(0);

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
CString strVera;
m_ctrlStaticSatznummer.GetWindowText(strVera);

CString str;
str.Format(_T("%s %s"),Sprache(strVera),m_pCurVerank->m_Name);
m_ctrlStaticSatznummer.SetWindowText(str);


str.Format(_T("%d %s"),m_pVerankerungsSaetze->Anzahl(),Sprache(_T("Sätze")));
m_ctrlStaticPositionen.SetWindowText(str);

for(int i = 0; i < m_pVerankerungsSaetze->Anzahl(); i++)
    {
    m_ctrlComboSatznummern.AddString(m_pVerankerungsSaetze->SteinSatz(i).Nummer());
    }

AnzeigePlattenDaten(m_startIx);
    
return TRUE;  // return TRUE  unless you set the focus to a control
}
//---------------------------------------------------------------------------------------
void CPreiseVerank::AnzeigePlattenDaten(int index)
{
CSteinSatz satz;    // Alle Felder leer

if((index >= 0) && (index < m_pVerankerungsSaetze->Anzahl()))
    {
    satz = m_pVerankerungsSaetze->arr[index];
    m_ctrlComboSatznummern.SetCurSel(index);
    }

AnzeigeTexte(satz);
}
//---------------------------------------------------------------------------------------
void CPreiseVerank::AnzeigeTexte(const CSteinSatz& satz)
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

m_ctrlStaticHinweisText.SetWindowText(ss.m_Hinweis);
m_ctrlStaticLaengeText.SetWindowText(ss.m_Laenge);
m_ctrlStaticDickeText.SetWindowText(ss.m_Dicke);
m_ctrlStaticBreiteText.SetWindowText(ss.m_Breite);

m_ctrlStaticPreisText[0].SetWindowText(_T(""));
m_ctrlStaticPreisText[1].SetWindowText(_T(""));
m_ctrlStaticPreisText[2].SetWindowText(_T(""));
m_ctrlStaticPreisText[3].SetWindowText(_T(""));

if(ss.m_ResFuerAuftrag.IsEmpty())
    m_ctrlStaticResjanein.SetWindowText(Sprache(_T("Nein")));
else
    m_ctrlStaticResjanein.SetWindowText(Sprache(_T("Ja")));

m_ctrlButtonEinzel.ShowWindow(0);
ShowPreise(ss.m_GR_Preis);

KillTimer(12);
if(m_enableSetFunktion)
    {
    if(!ss.m_GA_ArtNr.IsEmpty())
        {
        m_ctrlButtonSet.ShowWindow(1);
        SetTimer(12,500,NULL);
        }
    }
else
    m_ctrlButtonSet.ShowWindow(0);


m_ctrlButtonSet.SetWindowText(Sprache(_T("Set anzeigen")));

m_bGAaktiv = FALSE;

}
//---------------------------------------------------------------------------------------
void CPreiseVerank::ShowPreise(CString Preise[])
{
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
void CPreiseVerank::Anzeige_GA_PlattenDaten(int index)
{
CSteinSatz satz;    // Alle Felder leer

if((index >= 0) && (index < m_pVerankerungsSaetze->Anzahl()))
    {
    satz = m_pVerankerungsSaetze->arr[index];
    m_ctrlComboSatznummern.SetCurSel(index);
    }

Anzeige_GA_Texte(satz);
}
//---------------------------------------------------------------------------------------
void CPreiseVerank::Anzeige_GA_Texte(const CSteinSatz& satz)
{

KillTimer(12);

SSatz ss(satz);

m_ctrlStaticArtikelnummerText.SetWindowText(ss.m_GA_ArtNr);
m_ctrlStaticArtikelText.SetWindowText(ss.m_GA_Artikel);
m_ctrlStaticMaterialText.SetWindowText(ss.m_GA_Material);
m_ctrlStaticOberflaecheText.SetWindowText(ss.m_GA_Oberflaeche);

m_ctrlStaticLagerText.SetWindowText(_T(""));
m_ctrlStaticHinweisText.SetWindowText(_T(""));

m_ctrlStaticLaengeText.SetWindowText(ss.m_GA_Laenge);
m_ctrlStaticDickeText.SetWindowText(ss.m_GA_Dicke);
m_ctrlStaticBreiteText.SetWindowText(ss.m_GA_Breite);

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
            m_ctrlStaticPreisText[k].SetWindowText(ss.m_GA_Preis[j] + _T(" ") + m_strWaehrung[k]);
            k++;
            if(k > 3) break;
            }
        j++;
        }
    }

if(ss.m_ResFuerAuftrag.IsEmpty())
    m_ctrlStaticResjanein.SetWindowText(Sprache(_T("Nein")));
else
    m_ctrlStaticResjanein.SetWindowText(Sprache(_T("Ja")));

m_bGAaktiv = TRUE;

m_ctrlButtonSet.ShowWindow(1);
m_ctrlButtonSet.SetWindowText(Sprache(_T("Zurück")));
}
//---------------------------------------------------------------------------------------
BOOL CPreiseVerank::PreTranslateMessage(MSG* pMsg) 
{
CString errMsg;

CString barCode = m_pScanner->WaitForDecode(2000,errMsg);

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
        if(!barCode.Left(1).CompareNoCase(_T("X")))   // Fall Böse
            {
            int index = FindNumber(barCode.Mid(1)); // ohne x nochmal suchen
            if(index >= 0)
                {
                PlaySoundScan();
                Anzeige_GA_PlattenDaten(index);     // Set-Daten anzeigen
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
            PlaySoundOther();
            AnzeigePlattenDaten(-1);     // Wenn index < 0 oder ungültig, werden alle Felder geleert
            m_ctrlComboSatznummern.SetWindowText(barCode);  // und der gelesene Barcode wird angezeigt
            }
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
int CPreiseVerank::FindNumber(const CString& strNumber) const
{
int index = -1;
CPreiseVerank::m_pVerankerungsSaetze->FoundAt(strNumber,index);
return index;
}
//-----------------------------------------------------------------------------------
void CPreiseVerank::OnSelchangeComboSatznummern() 
{
int index = m_ctrlComboSatznummern.GetCurSel();
if(!m_bGAaktiv)
    AnzeigePlattenDaten(index);
else
    Anzeige_GA_PlattenDaten(index);
}
//-----------------------------------------------------------------------------------
void CPreiseVerank::OnButtonSet() 
{
m_ctrlComboSatznummern.SetFocus();

int index = m_ctrlComboSatznummern.GetCurSel();
if(index < 0)
    {
    int cursel;
    CString nrstr;
    m_ctrlComboSatznummern.GetWindowText(nrstr);
    if(m_pVerankerungsSaetze->FoundAt(nrstr,cursel))
        {
        m_ctrlComboSatznummern.SetCurSel(cursel);
        index = cursel;
        }
    }
if(m_bGAaktiv)
    {
    AnzeigePlattenDaten(index);
    }
else
    {
    Anzeige_GA_PlattenDaten(index);
    }
}
//------------------------------------------------------------------------------------
void CPreiseVerank::OnEditchangeComboSatznummern() 
{
int cursel;

CString nrstr;
m_ctrlComboSatznummern.GetWindowText(nrstr);

if(m_pVerankerungsSaetze->FoundAt(nrstr,cursel))
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
void CPreiseVerank::OnTimer(UINT nIDEvent) 
{
CDialog::OnTimer(nIDEvent);
if(!m_bGAaktiv)
    {
    if(m_bBlink)
        {
        m_ctrlStaticPreisText[0].ShowWindow(1);
        m_ctrlStaticPreisText[1].ShowWindow(1);
        m_ctrlStaticPreisText[2].ShowWindow(1);
        m_ctrlStaticPreisText[3].ShowWindow(1);
        m_bBlink = FALSE;
        }
    else
        {
        m_ctrlStaticPreisText[0].ShowWindow(0);
        m_ctrlStaticPreisText[1].ShowWindow(0);
        m_ctrlStaticPreisText[2].ShowWindow(0);
        m_ctrlStaticPreisText[3].ShowWindow(0);
        m_bBlink = TRUE;
        }
    }
}

void CPreiseVerank::OnStnClickedStaticLagerTx()
{
CString str;
m_ctrlStaticLagerText.GetWindowText(str);
AfxMessageBox(str,MB_OK);
}
