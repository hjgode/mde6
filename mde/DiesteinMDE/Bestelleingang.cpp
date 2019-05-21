// Bestelleingang.cpp: Implementierungsdatei
//


#include "stdafx.h"
#include "Bestelleingang.h"
#include "BestelleingangBuchungen.h"

IMPLEMENT_DYNAMIC(CBestelleingang, CDialog)

/////////////////////////////////////////////////////////////////////////////
// CBestelleingang dialog

CBestelleingang::CBestelleingang(CWnd* pParent /*=NULL*/)
	: CDialog(CBestelleingang::IDD, pParent)
{
}


void CBestelleingang::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_STEINSAETZE, m_ctrlStaticSteinSaetze);
	DDX_Control(pDX, IDC_STATIC_STEINNUMMER, m_ctrlStaticSteinnummer);
	DDX_Control(pDX, IDC_STATIC_MENGE, m_ctrlStaticMenge);
	DDX_Control(pDX, IDC_STATIC_ME1, m_ctrlStaticME1);
	DDX_Control(pDX, IDC_STATIC_MATERIALTEXT, m_ctrlStaticMaterialText);
	DDX_Control(pDX, IDC_STATIC_LBD, m_ctrlStaticLBD);
	DDX_Control(pDX, IDC_STATIC_LAGER, m_ctrlStaticLager);
	DDX_Control(pDX, IDC_STATIC_LAENGETEXT, m_ctrlStaticLaengeText);
	DDX_Control(pDX, IDC_STATIC_DICKETEXT, m_ctrlStaticDickeText);
	DDX_Control(pDX, IDC_STATIC_CONTAINERTEXT, m_ctrlStaticContainerText);
	DDX_Control(pDX, IDC_STATIC_CONTAINER, m_ctrlStaticContainer);
	DDX_Control(pDX, IDC_STATIC_BREITETEXT, m_ctrlStaticBreiteText);
	DDX_Control(pDX, IDC_STATIC_BESTPOSTEXT, m_ctrlStaticBestPosText);
	DDX_Control(pDX, IDC_STATIC_BESTPOS, m_ctrlStaticBestPos);
	DDX_Control(pDX, IDC_STATIC_BESTNRTEXT, m_ctrlStaticBestNrText);
	DDX_Control(pDX, IDC_STATIC_BESTNR, m_ctrlStaticBestNr);
	DDX_Control(pDX, IDC_STATIC_BESTELLEINGANG, m_ctrlStaticBestelleingang);
	DDX_Control(pDX, IDC_STATIC_ARTIKELTEXT, m_ctrlStaticArtikelText);
	DDX_Control(pDX, IDC_COMBO_STEINNUMMERN, m_ctrlComboSteinnummern);
	DDX_Control(pDX, IDC_COMBO_LAGER1, m_ctrlComboLager);
	DDX_Control(pDX, IDC_BUTTON_HINZU, m_ctrlButtonHinzu);
	DDX_Control(pDX, IDC_BUTTON_BUCHUNGEN, m_ctrlButtonBuchungen);
}


BEGIN_MESSAGE_MAP(CBestelleingang, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_HINZU, OnButtonHinzu)
	ON_CBN_SELCHANGE(IDC_COMBO_STEINNUMMERN, OnSelchangeComboSteinnummern)
	ON_CBN_EDITCHANGE(IDC_COMBO_STEINNUMMERN, OnEditchangeComboSteinnummern)
	ON_BN_CLICKED(IDC_BUTTON_BUCHUNGEN, OnButtonBuchungen)
	ON_BN_CLICKED(IDC_STATIC_ARTIKELTEXT, OnStaticArtikeltext)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBestelleingang message handlers
//---------------------------------------------------------------------------------------
BOOL CBestelleingang::OnInitDialog()
{
CDialog::OnInitDialog();

CenterWindow(GetDesktopWindow());	// center to the hpc screen

TranslateStatic(m_ctrlStaticBestelleingang);
TranslateStatic(m_ctrlStaticSteinnummer);
TranslateStatic(m_ctrlStaticSteinSaetze);
TranslateButton(m_ctrlButtonHinzu);
TranslateStatic(m_ctrlStaticBestNr);
TranslateStatic(m_ctrlStaticBestPos);
TranslateStatic(m_ctrlStaticContainer);
TranslateStatic(m_ctrlStaticMenge);
TranslateStatic(m_ctrlStaticLBD);
TranslateStatic(m_ctrlStaticLager);
TranslateButton(m_ctrlButtonBuchungen);

int i;
m_tabLager.Read();

m_ctrlComboLager.AddString(_T("")); // Erstes Felde leer
for(i = 0; i < m_tabLager.GetSize(); i++)
    {
    CString str;
    str.Format(_T("%s %s"),m_tabLager.GetAt(i).m_key,m_tabLager.GetAt(i).m_bez);
    m_ctrlComboLager.AddString(str);
    }

CString str;
str.Format(_T("%d %s"),m_pContSteinSaetze->Anzahl(),Sprache(_T("Steinsätze")));
m_ctrlStaticSteinSaetze.SetWindowText(str);

for(i = 0; i < m_pContSteinSaetze->Anzahl(); i++)
    {
    m_ctrlComboSteinnummern.AddString(m_pContSteinSaetze->SteinSatz(i).Nummer());
    }

if(m_pContSteinSaetze->Anzahl())
    AnzeigePlattenDaten(0);

m_ctrlComboSteinnummern.SetCurSel(0);
m_ctrlComboSteinnummern.SetFocus();

return FALSE;  // return TRUE  unless you set the focus to a control
}
//-----------------------------------------------------------------------------
void CBestelleingang::AnzeigePlattenDaten(int index)
{
CSteinSatz satz;    // Alle Felder leer

if((index >= 0) && (index < m_pContSteinSaetze->Anzahl()))
    {
    satz = m_pContSteinSaetze->arr[index];
    }
SSatz ss(satz);
m_ctrlComboSteinnummern.SetWindowText(ss.m_Nummer);

SetTexte(ss);
SetComboLager(m_tabLager.GetIndexByKey(ss.m_Lager));
}
//-----------------------------------------------------------------------------
void CBestelleingang::SetTexte(const SSatz& ss)
{
if(!ss.m_ResFuerAuftrag.IsEmpty())
    {
    m_ctrlStaticBestNr.SetWindowText(_T("Auftrag:"));
    m_ctrlStaticBestNrText.SetWindowText(ss.m_ResFuerAuftrag);
    m_ctrlStaticBestPosText.SetWindowText(ss.m_AuftragsPos);
    }
else
    {
    m_ctrlStaticBestNr.SetWindowText(_T("Best.Nr.:"));
    m_ctrlStaticBestNrText.SetWindowText(ss.m_BestellNr);
    m_ctrlStaticBestPosText.SetWindowText(ss.m_BestellPos);
    }
m_ctrlStaticContainerText.SetWindowText(ss.m_Container);
m_ctrlStaticME1.SetWindowText(ss.m_Menge1 + _T(" ") + ss.m_ME1);

m_ctrlStaticArtikelText.SetWindowText(ss.m_Artikel);
if(!ss.m_Material.IsEmpty() || !ss.m_Oberflaeche.IsEmpty())
    m_ctrlStaticMaterialText.SetWindowText(ss.m_Material + _T(", ") + ss.m_Oberflaeche);
else
    m_ctrlStaticMaterialText.SetWindowText(_T(""));
m_ctrlStaticLaengeText.SetWindowText(ss.m_Laenge);
m_ctrlStaticBreiteText.SetWindowText(ss.m_Breite);
m_ctrlStaticDickeText.SetWindowText(ss.m_Dicke);

}
//-----------------------------------------------------------------------------
void CBestelleingang::SetComboLager(int ix) // Ix = index in der Lagertabelle
{
if((ix >= 0) && (ix < m_tabLager.GetSize()))
    m_ctrlComboLager.SetCurSel(ix+1);   // Erstes Feld ist blank
else
    m_ctrlComboLager.SetCurSel(0);   // Erstes Feld ist blank
}
//-----------------------------------------------------------------------------
BOOL CBestelleingang::PreTranslateMessage(MSG* pMsg) 
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
    int ix;
    if(m_pContSteinSaetze->FoundAt(barCode,ix))
        {
        AnzeigePlattenDaten(ix);
        PlaySoundScan();
        }
    else
        {
        ix = m_tabLager.GetIndexByKey(barCode);
        if(ix >= 0)
            {
            SetComboLager(ix);
            }
        else
            {
            if((barCode.GetAt(0) == _T('X')) || (barCode.GetAt(0) == _T('x')))
                AfxMessageBox(_T("Barcode ist Set-Nummer"));
            else
                {
                AnzeigePlattenDaten(-1);
                m_ctrlComboSteinnummern.SetWindowText(barCode);
                PlaySoundScan();
                PlaySoundOther();
                }
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
//-----------------------------------------------------------------------------
void CBestelleingang::OnButtonHinzu() 
{
int ix = m_ctrlComboSteinnummern.GetCurSel();
if(ix < 0) return;

int lagerIx = m_ctrlComboLager.GetCurSel()-1;

//prüfen ob Nummer im Contsteinsatz
CSteinSatz satz0;
CString strNr;
m_ctrlComboSteinnummern.GetWindowText(strNr);
if(m_pContSteinSaetze->FoundAt(strNr,ix))   // Normal hinzu
    {
    satz0 = m_pContSteinSaetze->arr[ix];
    SSatz ss(satz0);

    ss.m_Lager = _T("");
    if(lagerIx >= 0)
        ss.m_Lager = m_tabLager.GetAt(lagerIx).m_key;

    satz0.Set(ss);
    m_pContSteinSaetze->arr[ix] = satz0;    // neues Lager auch im Bestand eintragen
    }
else    // Nummer nicht im Bestand, trotzdenm hinzu?
    {
    int ret = AfxMessageBox(_T("Die Nummer ist nicht im Containerbestand vorhanden, trotzdem hinzubuchen?"),MB_YESNO);
    if(ret == IDNO)
        return;
    SSatz ss;
    ss.m_Nummer = strNr;

    ss.m_Lager = _T("");
    if(lagerIx >= 0)
        ss.m_Lager = m_tabLager.GetAt(lagerIx).m_key;

    satz0.Set(ss);
    }        

// prüfen ob schonmal hinzugebucht
int bix;
if(m_pAuftraege->Auftrag(0).m_Positionen.FoundAt(satz0.Nummer(),bix))
    {
    int ret = AfxMessageBox(_T("Die Nummer ist bereits gebucht. Soll der Eintrag ersetzt werden?"),MB_YESNO);
    if(ret == IDNO)
        return;
    m_pAuftraege->Auftrag(0).m_Positionen.RemoveAt(bix);
    }

satz0.m_buchungsNummer = m_pAuftraege->NaechsteBuchungsnummer();    // im der Umbuchungsdatei eintragen
satz0.SetDatumZeit();
m_pAuftraege->Auftrag(0).AddPosition(satz0);    // es gibt nur einen Auftrag "OberflaecheAendern"
PlaySoundAdd();

m_pContSteinSaetze->m_modified = TRUE;

m_ctrlComboSteinnummern.SetFocus();

}
//-----------------------------------------------------------------------------
void CBestelleingang::OnSelchangeComboSteinnummern() 
{
int index = m_ctrlComboSteinnummern.GetCurSel();
AnzeigePlattenDaten(index);
}
//-----------------------------------------------------------------------------
void CBestelleingang::OnEditchangeComboSteinnummern() 
{
int ix;
CString nrstr;
m_ctrlComboSteinnummern.GetWindowText(nrstr);
if(m_pContSteinSaetze->FoundAt(nrstr,ix))
    {
    SSatz ss(m_pContSteinSaetze->SteinSatzConst(ix));
    SetTexte(ss);
    SetComboLager(m_tabLager.GetIndexByKey(ss.m_Lager));
    }
else
    {
    SSatz ss;
    SetTexte(ss);
    SetComboLager(-1);
    }
}
//-----------------------------------------------------------------------------
void CBestelleingang::OnButtonBuchungen() 
{
CBestelleingangBuchungen dlg;

dlg.m_pContSteinSaetze = m_pContSteinSaetze;
dlg.m_pTabLager = &m_tabLager;
dlg.m_pAuftraege = m_pAuftraege;

dlg.DoModal();

m_ctrlComboSteinnummern.SetFocus();

int ix = m_ctrlComboSteinnummern.GetCurSel();
AnzeigePlattenDaten(ix);
}
//-----------------------------------------------------------------------------
void CBestelleingang::OnStaticArtikeltext() 
{
CString str;
m_ctrlStaticArtikelText.GetWindowText(str);
MessageBox(str);
}
