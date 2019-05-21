// PositionenInfo.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "PositionenInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CPositionenInfo dialog
IMPLEMENT_DYNAMIC(CPositionenInfo, CDialog)

CPositionenInfo::CPositionenInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CPositionenInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPositionenInfo)
	//}}AFX_DATA_INIT
m_pSaetze = NULL;
}


void CPositionenInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPositionenInfo)
	DDX_Control(pDX, IDC_BUTTON_VORHER, m_ctrlButtonVorher);
	DDX_Control(pDX, IDC_BUTTON_NAECHSTER, m_ctrlButtonNaechster);
	DDX_Control(pDX, IDC_LIST_POSINFO, m_ctrlListPosInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPositionenInfo, CDialog)
	//{{AFX_MSG_MAP(CPositionenInfo)
	ON_BN_CLICKED(IDC_BUTTON_NAECHSTER, OnButtonNaechster)
	ON_BN_CLICKED(IDC_BUTTON_VORHER, OnButtonVorher)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPositionenInfo message handlers

BOOL CPositionenInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();

TranslateButton(m_ctrlButtonVorher);
TranslateButton(m_ctrlButtonNaechster);

m_tabLagerOrte.Read();
m_tabLieferanten.Read();
m_tabFehlerbezeichnung.Read();

int iarr[]={50};
m_ctrlListPosInfo.SetTabStops(1,iarr);

ShowSatz(m_pSaetze->SteinSatz(m_index));

m_ctrlButtonNaechster.SetFocus();

return FALSE;  // return TRUE unless you set the focus to a control
              // EXCEPTION: OCX Property Pages should return FALSE
}
//----------------------------------------------------------------------------------------
void CPositionenInfo::Add2String(const CString& str1,const CString& str2)
{
CString str;
str.Format(_T("%s\t%s"),Sprache(str1),str2);
m_ctrlListPosInfo.AddString(str);
}
//----------------------------------------------------------------------------------------
void CPositionenInfo::OnButtonNaechster() 
{
int topIx = m_ctrlListPosInfo.GetTopIndex();
m_index = (m_index+1) % m_pSaetze->Anzahl();
if(!m_index)
    PlaySoundOther();
ShowSatz(m_pSaetze->SteinSatz(m_index));
m_ctrlListPosInfo.SetTopIndex(topIx);
}
//----------------------------------------------------------------------------------------
void CPositionenInfo::OnButtonVorher() 
{
int topIx = m_ctrlListPosInfo.GetTopIndex();
m_index = (m_pSaetze->Anzahl() + m_index - 1) % m_pSaetze->Anzahl();
if(m_index == m_pSaetze->Anzahl()-1)
    PlaySoundOther();
ShowSatz(m_pSaetze->SteinSatz(m_index));
m_ctrlListPosInfo.SetTopIndex(topIx);
}
//----------------------------------------------------------------------------------------
void CPositionenInfo::ShowSatz(const CSteinSatz& satz)
{
SSatz ss(satz);

m_ctrlListPosInfo.ResetContent();

CString str1;
Add2String(_T("Stein-Nr.:"),ss.m_Nummer);
Add2String(_T("Artikel:"),ss.m_Artikel);
Add2String(_T("Material:"),ss.m_Material);
Add2String(_T("Oberfläche:"),ss.m_Oberflaeche);
if(!ss.m_Schicht.IsEmpty())
    Add2String(_T("Schicht:"),ss.m_Schicht);
Add2String(_T("Länge:"),ss.m_Laenge);
Add2String(_T("Breite:"),ss.m_Breite);
Add2String(_T("Dicke:"),ss.m_Dicke);
Add2String(_T("Gewicht:"),ss.m_Gewicht);
if(!ss.m_LaengeBrutto.IsEmpty())
    Add2String(_T("Länge-Brutto:"),ss.m_LaengeBrutto);
if(!ss.m_BreiteBrutto.IsEmpty())
    Add2String(_T("Breite-Brutto:"),ss.m_BreiteBrutto);
if(!ss.m_DickeBrutto.IsEmpty())
    Add2String(_T("Dicke-Brutto:"),ss.m_DickeBrutto);
Add2String(_T("Fehllänge:"),ss.m_FehlLaenge);
Add2String(_T("Fehlbreite:"),ss.m_FehlBreite);
Add2String(_T("Fehler:"),ss.m_FehlNummer+_T("|")+m_tabFehlerbezeichnung.GetItemByKey(ss.m_FehlNummer).m_bez);
CString menge;
menge = ss.m_Menge1 + _T(" ") + ss.m_ME1;
Add2String(_T("Menge:"),menge);
menge = ss.m_Menge1Verfuegbar + _T(" ") + ss.m_ME1;
Add2String(_T("M.(verfügbar):"),menge);

CString str;
if(!ss.m_Lager.IsEmpty())
    str.Format(_T("%s%s%s"),ss.m_Lager,_T("|"),m_tabLagerOrte.GetItemByKey(ss.m_Lager).m_bez);
Add2String(_T("Lager:"),str);
Add2String(_T("Hinweis:"),ss.m_Hinweis);

str.Empty();
if(!ss.m_Lieferant.IsEmpty())
    str.Format(_T("%s%s%s"),ss.m_Lieferant,_T("|"),m_tabLieferanten.GetItemByKey(ss.m_Lieferant).m_bez);
Add2String(_T("Lieferant:"),str);

// Preisfeld vorerst einmal komplett sperren, da die Mitarbeiter den Preis nicht sehen sollen ch 30.10.2012
// vielleicht später einmal durch einen Schalter freigeben.
//Add2String(_T("Preis:"),ss.m_Preis);

Add2String(_T("Artikelgruppe:"),ss.m_ArtikelGrBez);
CString bes(ss.m_BestellNr);
bes += _T("/");
bes += ss.m_BestellPos;
Add2String(_T("Bes.-Nr./Pos.:"),bes);

CString strPV(ss.m_ProduktionVerkauf);
strPV += _T(" ");
CString strBnr;
strBnr.Format(_T("%s %d"),Sprache(_T("Buchungs-Nr.")),satz.m_buchungsNummer);
strPV += strBnr;
Add2String(_T("Prod./Verk./A.:"),strPV);

CString dattime;
dattime.Format(_T("%s.%s.%s %s:%s:%s %s"),ss.m_Datum.Left(2),ss.m_Datum.Mid(2,2),ss.m_Datum.Mid(4,4),
                                       ss.m_Zeit.Left(2),ss.m_Zeit.Mid(2,2),ss.m_Zeit.Mid(4,2),ss.m_Ende);
Add2String(_T("Datum/Zeit/E:"),dattime);

//if(g_Optionen.BoeseAuftragEnabled())
    {
    Add2String(_T("Auftrag:"),ss.m_ResFuerAuftrag);
    Add2String(_T("Kunde:"),ss.m_AuftragsKundenname);
    Add2String(_T("Position:"),ss.m_AuftragsPos);
    Add2String(_T("Teilpos:"),ss.m_AuftragsTeilpos);
    Add2String(_T("Typkennung:"),ss.m_TypKennung);
    Add2String(_T("Herstellart:"),ss.m_HerstellArt);
    Add2String(_T("Stein-Nr.-Alt:"),ss.m_NummerParent);
    }

UpdateData(FALSE);
}
