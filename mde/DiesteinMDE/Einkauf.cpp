// Einkauf.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "PlattenZugang.h"
#include "Einkauf.h"
#include "AuftragsBearbeitung.h"

/////////////////////////////////////////////////////////////////////////////
// CEinkauf dialog

IMPLEMENT_DYNAMIC(CEinkauf, CDialog)

CEinkauf::CEinkauf(CWnd* pParent /*=NULL*/)
	: CDialog(CEinkauf::IDD, pParent)
{
	m_nListPositionen = -1;
	m_strComboBestellnr = _T("");
	m_strStaticPosInfo = _T("");
	m_strStaticLieferant = _T("");
    m_bNoSelect = FALSE;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CEinkauf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_INFO, m_ctrlButtonInfo);
	DDX_Control(pDX, IDC_STATIC_BESTELLNR, m_ctrlStaticBestellnummer);
	DDX_Control(pDX, IDC_COMBO_BESTELLNR, m_ctrlComboBestellnr);
	DDX_Control(pDX, IDC_LIST_POSITIONEN, m_ctrlListPositionen);
	DDX_LBIndex(pDX, IDC_LIST_POSITIONEN, m_nListPositionen);
	DDX_CBString(pDX, IDC_COMBO_BESTELLNR, m_strComboBestellnr);
	DDX_Text(pDX, IDC_STATIC_POSINFO, m_strStaticPosInfo);
	DDX_Text(pDX, IDC_STATIC_LIEFERANT, m_strStaticLieferant);
}


BEGIN_MESSAGE_MAP(CEinkauf, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST_POSITIONEN, OnSelchangeListPositionen)
	ON_CBN_SELCHANGE(IDC_COMBO_BESTELLNR, OnSelchangeComboBestellnr)
	ON_BN_CLICKED(IDC_BUTTON_INFO, OnButtonInfo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------------------
BOOL CEinkauf::OnInitDialog()
{
CDialog::OnInitDialog();

CenterWindow(GetDesktopWindow());	// center to the hpc screen

TranslateButton(m_ctrlButtonInfo);
TranslateStatic(m_ctrlStaticBestellnummer);

m_tabMaterialien.Read();
m_tabOberflaechen.Read();

m_pAuftrag = &m_pAuftraege->Auftrag(0);            // Bestellungseingang

m_Bestellungen.ReadFile(DATEI_BESTELLUNGEN);

m_tabLieferanten.Read();

m_tabArtikelGruppen.Read();

//!!! mit R gekennzeichnete Artikelgruppe: ..;10R;..
//
// Typ == Rohplatte: Nummer muss eindeutig sein
// Bei anderen Artikeln kann Nummer mehrfach verwendet
// werden, Mengen werden dann aufsummiert auf eine Nummer
for(int i = 0; i < m_Bestellungen.Anzahl(); i++)
    {
    SSatz ss(m_Bestellungen.SteinSatz(i));
    if(m_ctrlComboBestellnr.FindStringExact(0,ss.m_BestellNr) < 0)      // Rohplattenkennung in Bestellungen löschen
        m_ctrlComboBestellnr.AddString(ss.m_BestellNr);
    }
if(!m_strComboBestellnr.IsEmpty())	
	m_ctrlComboBestellnr.GetLBText(0,m_strComboBestellnr);

SetBestellung(m_strComboBestellnr);

int iarr[]={30,46};
m_ctrlListPositionen.SetTabStops(2,iarr);

AnzeigeBestellPositionen(0);

UpdateData(FALSE);
return TRUE;  // return TRUE  unless you set the focus to a control
}
//---------------------------------------------------------------------------------------
void CEinkauf::AnzeigeBestellPositionen(int posix)
{
if(m_Bestellung.Anzahl())
    {
    SSatz ss(m_Bestellung.SteinSatzConst(0));
    m_strStaticLieferant.Format(_T("%s: %s"),Sprache(_T("Lieferant")),m_tabLieferanten.GetItemByKey(ss.m_Lieferant).m_bez);
    }
m_strStaticPosInfo.Format(_T("%d %s"),m_Bestellung.Anzahl(),Sprache(_T("Positionen")));
m_ctrlListPositionen.ResetContent();
int i;
for(i = 0; i < m_Bestellung.Anzahl(); i++)
    {
    SSatz ss(m_Bestellung.SteinSatz(i));
    CString str;
    CString strRest = CPlattenZugang::CalcRest(&m_Bestellung,&m_pAuftraege->Auftrag(0),ss.m_BestellNr,ss.m_BestellPos);
    str.Format(_T("%s\t%s\t%s"),strRest,ss.m_ME2,ss.m_Artikel); // noch offene Restmenge
    m_ctrlListPositionen.AddString(str);

    str.Format(_T("%s %s\t%s"),Sprache(_T("Position")).Left(1),ss.m_BestellPos,ss.m_Material);
    m_ctrlListPositionen.AddString(str);

    CString strEnd(_T(" "));
    if(EndeChecked(&m_pAuftraege->Auftrag(0),ss.m_BestellNr,ss.m_BestellPos))
        strEnd = Sprache(_T("Ende")).Left(1);
    
    str.Format(_T("%s\t%s cm, %s"),strEnd,ss.m_Dicke,ss.m_Oberflaeche);
    m_ctrlListPositionen.AddString(str);
    }
}
//-----------------------------------------------------------------------------
// Zum Bestellposition Ende-Kennzeichen suchen
BOOL CEinkauf::EndeChecked(CAuftrag *pAuftrag,const CString& strBestellNr,const CString& strBestellPos)
{
int i;
for(i = 0; i < pAuftrag->m_Positionen.Anzahl(); i++)
    {
    SSatz ss(pAuftrag->Position(i));
    if(!ss.m_BestellNr.Compare(strBestellNr) && !ss.m_BestellPos.Compare(strBestellPos))
        {
        if(!ss.m_Ende.IsEmpty())
            return TRUE;
        }
    }
return FALSE;
}
//---------------------------------------------------------------------------------------
// Positionen zur Bestellnummer von Bestellungen nach Bestellung
int CEinkauf::SetBestellung(const CString& bestellNr)
{
m_Bestellung.arr.RemoveAll();
int i;
for(i = 0; i < m_Bestellungen.Anzahl(); i++)
    {
    SSatz ss(m_Bestellungen.SteinSatz(i));
    if(!ss.m_BestellNr.Compare(bestellNr))
        m_Bestellung.Add(m_Bestellungen.SteinSatz(i));
    }
return m_Bestellung.Anzahl();
}
//---------------------------------------------------------------------------------------
// Satz ist Ausgewählt(eine von 3 Zeilen) -> Dialog PlattenZugang
void CEinkauf::OnSelchangeListPositionen() 
{
/*
if(m_bNoSelect) // scheinbar nicht notwendig
    {
    m_bNoSelect = FALSE;
    return;
    }
*/
g_baseSteinSatz.m_value = _T(""); 
int sel = m_ctrlListPositionen.GetCurSel()/3;
if((sel >= 0) && (sel < m_Bestellung.Anzahl()))
    g_baseSteinSatz = m_Bestellung.arr[sel];
else
    sel = 0;

g_baseSteinSatz.SetLieferscheinNummer(m_strLastLieferschein);
g_baseSteinSatz.SetLieferscheinDatum(m_strLastLieferscheinDatum);
g_baseSteinSatz.SetLager(m_strLastLagerort);

CPlattenZugang eingang;
eingang.m_nModus = ID_BESTELLUNGENEINGANG;
eingang.m_pSteinSaetze = m_pSteinSaetze;
eingang.m_pAuftraege = m_pAuftraege;
eingang.m_pAuftrag = &m_pAuftraege->Auftrag(0);
eingang.m_pBestellungen = &m_Bestellungen;
eingang.m_pScanner = m_pScanner;

eingang.DoModal();

m_pAuftraege->Save();
m_pSteinSaetze->Save();

SetBestellung(m_strComboBestellnr);

AnzeigeBestellPositionen(sel);

m_strLastLieferschein = g_baseSteinSatz.LieferscheinNummer();
m_strLastLieferscheinDatum = g_baseSteinSatz.LieferscheinDatum();
m_strLastLagerort = g_baseSteinSatz.Lager();

UpdateData(FALSE);

m_bNoSelect = TRUE;
m_ctrlListPositionen.SetCurSel(sel*3);
//m_ctrlListPositionen.ScrollWindow(0,1000); // geht nicht ???
//m_ctrlListPositionen.UpdateWindow();

}
//---------------------------------------------------------------------------------------
void CEinkauf::OnSelchangeComboBestellnr() 
{
int sel = m_ctrlComboBestellnr.GetCurSel();
m_ctrlComboBestellnr.GetLBText(sel,m_strComboBestellnr);

SetBestellung(m_strComboBestellnr);

AnzeigeBestellPositionen(0);

UpdateData(FALSE);
}
//---------------------------------------------------------------------------------------
// Bestellnummer entspricht Auftragstyp
// Position zur auswahl der Steinnummern
BOOL CEinkauf::CreateBestellungFuerInfo(const CString& strBestellNr,CAuftraege& m_BestellungFuerInfo)
{
CAuftrag& rAuf = m_pAuftraege->Auftrag(0); // BestellungEingang
m_BestellungFuerInfo.arr.RemoveAll();
m_BestellungFuerInfo.m_strName = strBestellNr;

for(int i = 0; i < rAuf.m_Positionen.Anzahl(); i++)
    {
    SSatz ss(rAuf.Position(i));
    if(!ss.m_BestellNr.Compare(strBestellNr))
        {
        int aufix = m_BestellungFuerInfo.Exist(ss.m_BestellPos);
        if(aufix < 0)
            {
            CAuftrag auf(ss.m_BestellPos);
            m_BestellungFuerInfo.Add(auf);
            aufix = m_BestellungFuerInfo.Anzahl()-1;
            }
        m_BestellungFuerInfo.Auftrag(aufix).AddPosition(rAuf.Position(i));
        }
    }
if(m_BestellungFuerInfo.Anzahl())
    return TRUE;
return FALSE;
}
//---------------------------------------------------------------------------------------
// Löschen im Moment nicht möglich, Sperren von Funtkionen (mögl eigenes Dialogfeld)
void CEinkauf::OnButtonInfo() 
{
CAuftragsBearbeitung aufBearbeitung(this);  // Dialogbox Auftragsbearbeitung für Info

aufBearbeitung.m_pSteinSaetze = m_pSteinSaetze;

CAuftraege aufeBestellungFuerInfo;
aufeBestellungFuerInfo.m_strName = NAME_BESTELLUNGENEINGANG;

if(!CreateBestellungFuerInfo(m_strComboBestellnr,aufeBestellungFuerInfo))
    return;

aufBearbeitung.m_pAuftraege = &aufeBestellungFuerInfo;
aufBearbeitung.m_nModus = ID_BESTELLUNGENEINGANG;

CAuftrag aufLoesch(NAME_BESTELLUNGENEINGANG);    // Auftrag mit zu löschenden Positionen
aufBearbeitung.m_pAufLoesch = &aufLoesch;

CString str = aufeBestellungFuerInfo.Auftrag(0).m_strIdent;
aufBearbeitung.m_pstrLetzterAuftrag = &str;
aufBearbeitung.m_pScanner = m_pScanner;

m_pScanner->setEnableScanner(FALSE);

aufBearbeitung.DoModal();	

m_pScanner->setEnableScanner(TRUE);

int i,j;
for(i = 0; i < aufLoesch.m_Positionen.Anzahl(); i++)
    {
    SSatz ss(aufLoesch.Position(i));
    for(j = 0; j < m_pAuftraege->Auftrag(0).m_Positionen.Anzahl(); j++)
        {
        SSatz s(m_pAuftraege->Auftrag(0).Position(j));
        if(!ss.m_BestellNr.Compare(s.m_BestellNr) && !ss.m_BestellPos.Compare(s.m_BestellPos)
           && !ss.m_Nummer.Compare(s.m_Nummer))
            {
            if(!ss.m_Nummer.CompareNoCase(_T("OHNE")))
                {
                if(!ss.m_Zeit.Compare(s.m_Zeit)) // Ohne kann mehrfach vorkommen
                    {
                    m_pAuftraege->Auftrag(0).m_Positionen.RemoveAt(j);
                    break;
                    }
                }
            else
                {
                m_pAuftraege->Auftrag(0).m_Positionen.RemoveAt(j);
                break;
                }
            }
        }
    for(j = 0; j < m_pSteinSaetze->Anzahl(); j++)   // Platten aus den Steinsätzen wieder entfernen
        {
        SSatz s(m_pSteinSaetze->SteinSatz(j));
        if(!ss.m_Nummer.Compare(s.m_Nummer))
            {
//            AfxMessageBox(ss.m_Nummer);
//            AlertReal(aufLoesch.Position(i).Menge1());
//            AlertReal(m_pSteinSaetze->SteinSatz(j).Menge1());
            if(fabs(aufLoesch.Position(i).Menge1()-m_pSteinSaetze->SteinSatz(j).Menge1()) < 0.01)
                m_pSteinSaetze->RemoveAt(j);
            else
                m_pSteinSaetze->SubSatz(aufLoesch.Position(i));
            break;
            }
        }
    }
//AlertInt(m_pAuftraege->Anzahl());
//AlertInt(m_pAuftraege->Auftrag(0).m_Positionen.Anzahl());
if(aufLoesch.m_Positionen.Anzahl())
    {
    m_pAuftraege->Save();
    m_pSteinSaetze->Save();
    }

AnzeigeBestellPositionen(0);
}
//---------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------
BOOL CEinkauf::PreTranslateMessage(MSG* pMsg) 
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
    PlaySoundScan();
    CEinkauf::m_strComboBestellnr = barCode;
    SetBestellung(m_strComboBestellnr);

    AnzeigeBestellPositionen(0);

    UpdateData(FALSE);
	}
else
    {
    if(!errMsg.IsEmpty())
        AfxMessageBox(errMsg);
    }
return CDialog::PreTranslateMessage(pMsg);
}
//*********************************************************************************************
//*********************************************************************************************
//*********************************************************************************************
//*********************************************************************************************
