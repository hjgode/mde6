// PreiseVerank.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "Verankerung.h"
#include "PreiseVerank.h"

/////////////////////////////////////////////////////////////////////////////
// Funktion existiert ist nur für Böse
// Die Sätze einer Verankerung werden ähnlich wie bei Preisen mit
// alle Eigenschaften angezeigt
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CPreiseVerank dialog

IMPLEMENT_DYNAMIC(CPreiseVerank, CDialog)

CPreiseVerank::CPreiseVerank(CWnd* pParent /*=NULL*/)
	: CDialog(CPreiseVerank::IDD, pParent)
{
    m_pSteinSaetze = NULL;
    m_pCurVerank = NULL;
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
	ON_CBN_EDITCHANGE(IDC_COMBO_SATZNUMMERN, OnEditchangeComboSatznummern)
	ON_WM_TIMER()
    ON_STN_CLICKED(IDC_STATIC_LAGER_TX, &CPreiseVerank::OnStnClickedStaticLagerTx)
    ON_STN_CLICKED(IDC_STATIC_HINWEIS_TX, &CPreiseVerank::OnStnClickedStaticHinweisTx)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreiseVerank message handlers
/////////////////////////////////////////////////////////////////////////////
// CInfo message handlers

BOOL CPreiseVerank::OnInitDialog()
{
CDialog::OnInitDialog();

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


for(int i = 0; i < MAX_VAZAHL; i++)
    {
    if(m_pCurVerank->SteinNummer(i).IsEmpty())
        continue;
    int ix;
    if(m_pSteinSaetze->FoundAt(m_pCurVerank->SteinNummer(i),ix))
        m_VerankerungsSaetze.Add(m_pSteinSaetze->SteinSatz(ix));
    }


CString str;
m_ctrlStaticSatznummer.GetWindowText(str);  // Anzeige der Verankerung anstelle "Satznummer"
str.Format(_T("%s %s"),Sprache(str),m_pCurVerank->m_Name);
m_ctrlStaticSatznummer.SetWindowText(str);

str.Format(_T("%d %s"),m_VerankerungsSaetze.Anzahl(),Sprache(_T("Sätze")));
m_ctrlStaticPositionen.SetWindowText(str);

for(int i = 0; i < m_VerankerungsSaetze.Anzahl(); i++)
    {
    m_ctrlComboSatznummern.AddString(m_VerankerungsSaetze.SteinSatz(i).Nummer());
    }

// Aktuelle Nummer zurest anzeigen
int startIx = -1;
CString nr = m_pSteinSaetze->SteinSatz(m_startSteinSatzIx).Nummer();
m_VerankerungsSaetze.FoundAt(nr,startIx);

AnzeigePlattenDaten(startIx);
    
return TRUE;  // return TRUE  unless you set the focus to a control
}
//---------------------------------------------------------------------------------------
void CPreiseVerank::AnzeigePlattenDaten(int index)
{
CSteinSatz satz;    // Alle Felder leer

if((index >= 0) && (index < m_VerankerungsSaetze.Anzahl()))
    {
    satz = m_VerankerungsSaetze.arr[index];
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

CString resstr;
if(ss.m_ResTyp.IsEmpty())
    resstr = "Ja";
else if(ss.m_ResTyp == _T("1"))
    resstr = "Angebot";
else if(ss.m_ResTyp == _T("2"))
    resstr = "Auftrag";if(ss.m_ResFuerAuftrag.IsEmpty())
    m_ctrlStaticResjanein.SetWindowText(Sprache(_T("Nein")));
else
    m_ctrlStaticResjanein.SetWindowText(Sprache(resstr));

ShowPreise(ss.m_GR_Preis);
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
//-----------------------------------------------------------------------------------
void CPreiseVerank::OnSelchangeComboSatznummern() 
{
int index = m_ctrlComboSatznummern.GetCurSel();
AnzeigePlattenDaten(index);
}
//------------------------------------------------------------------------------------
void CPreiseVerank::OnEditchangeComboSatznummern() 
{
int cursel;

CString nrstr;
m_ctrlComboSatznummern.GetWindowText(nrstr);

if(m_VerankerungsSaetze.FoundAt(nrstr,cursel))
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
void CPreiseVerank::OnStnClickedStaticLagerTx()
{
CString str;
m_ctrlStaticLagerText.GetWindowText(str);
AfxMessageBox(str,MB_OK);
}
//---------------------------------------------------------------------------------------
BOOL CPreiseVerank::PreTranslateMessage(MSG* pMsg) 
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
    m_backSteinNummer = barCode;
    CDialog::OnOK();
	}
else
    {
    if(!errMsg.IsEmpty())
        AfxMessageBox(errMsg);
    }
return CDialog::PreTranslateMessage(pMsg);
}
//-------------------------------------------------------------------------------
void CPreiseVerank::OnStnClickedStaticHinweisTx()
{
CString str;
m_ctrlStaticHinweisText.GetWindowText(str);
AfxMessageBox(str,MB_ICONINFORMATION);
}
