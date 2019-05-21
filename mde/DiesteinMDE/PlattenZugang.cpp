// PlattenZugang.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "PlattenZugang.h"
#include "Eigenschaften.h"
#include "BloeckeVorabInfo.h"

IMPLEMENT_DYNAMIC(CPlattenZugang, CDialog)

/////////////////////////////////////////////////////////////////////////////
// CPlattenZugang dialog
//-----------------------------------------------------------------------------------
extern CSteinSatz g_baseSteinSatz;
//-----------------------------------------------------------------------------------

CPlattenZugang::CPlattenZugang(CWnd* pParent)
	: CDialog(CPlattenZugang::IDD, pParent)
{
m_nModus = 0;
m_strArtikelGruppe = _T("");
m_strBestellNr = _T("");
m_strBestellPos = _T("");
m_strBreite = _T("");
m_strDicke = _T("");
m_strFehlbreite = _T("");
m_strFehllaenge = _T("");
m_strHinweis = _T("");
m_strLaenge = _T("");
m_strMenge1 = _T("");
m_strPreis = _T("");
m_strSteinnummer = _T("");
m_strLieferant = _T("");
m_strMaterialArt = _T("");
m_strOberflaeche = _T("");
m_strME1 = _T("");
m_bCheckEnde = FALSE;
m_strRest = _T("");
m_strComboME2 = _T("");
m_strComboLager = _T("");
m_strEditLieferschein = _T("");
m_strEditDatum = _T("");
}


void CPlattenZugang::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_HINZU, m_ctrlButtonHinzu);
	DDX_Control(pDX, IDC_BUTTON_EIGENSCHAFTEN, m_ctrlButtonEigenschaften);
	DDX_Control(pDX, IDC_STATIC_STEINNR, m_ctrlStaticSteinnr);
	DDX_Control(pDX, IDC_STATIC_BIS, m_ctrlStaticBis);
	DDX_Control(pDX, IDC_STATIC_PREIS, m_ctrlStaticPreis);
	DDX_Control(pDX, IDC_STATIC_POSITION, m_ctrlStaticPosition);
	DDX_Control(pDX, IDC_STATIC_MENGE, m_ctrlStaticMenge);
	DDX_Control(pDX, IDC_STATIC_MASSE, m_ctrlStaticMasse);
	DDX_Control(pDX, IDC_STATIC_LIEFERSCHEIN, m_ctrlStaticLieferschein);
	DDX_Control(pDX, IDC_STATIC_HINWEIS, m_ctrlStaticHinweis);
	DDX_Control(pDX, IDC_STATIC_FEHLECKE, m_ctrlStaticFehlecke);
	DDX_Control(pDX, IDC_STATIC_DATUM, m_ctrlStaticDatum);
	DDX_Control(pDX, IDC_STATIC_BESTELLNR, m_ctrlStaticBestellnr);
	DDX_Control(pDX, IDC_EDIT_DATUM, m_ctrlEditDatum);
	DDX_Control(pDX, IDC_COMBO_LAGER, m_ctrlComboLager);
	DDX_Control(pDX, IDC_COMBO_ME2, m_ctrlComboME2);
	DDX_Control(pDX, IDC_CHECK_ENDE, m_ctrlCheckEnde);
	DDX_Control(pDX, IDCANCEL, m_ctrlCancel);
	DDX_Control(pDX, IDC_EDIT_BESTELLPOS, m_ctrlBestellPos);
	DDX_Control(pDX, IDC_EDIT_BESTELLNR, m_ctrlBestellNr);
	DDX_Control(pDX, IDC_EDIT_STEINNR, m_ctrlSteinnummer);
	DDX_Control(pDX, IDC_EDIT_STEINNRBIS, m_ctrlSteinnummerBis);
	DDX_Control(pDX, IDC_EDIT_FEHLBREITE, m_ctrlFehlbreite);
	DDX_Control(pDX, IDC_EDIT_FEHLLAENGE, m_ctrlFehllaenge);
	DDX_Control(pDX, IDC_EDIT_LAENGE, m_ctrlLaenge);
	DDX_Control(pDX, IDC_EDIT_DICKE, m_ctrlDicke);
	DDX_Control(pDX, IDC_EDIT_BREITE, m_ctrlBreite);
	DDX_Control(pDX, IDC_EDIT_MENGE1, m_ctrlMenge1);
	DDX_Control(pDX, IDC_COMBO_ME1, m_comboME1);
	DDX_Text(pDX, IDC_STATIC_ARTIKELGRUPPE, m_strArtikelGruppe);
	DDX_Text(pDX, IDC_EDIT_BESTELLNR, m_strBestellNr);
	DDX_Text(pDX, IDC_EDIT_BESTELLPOS, m_strBestellPos);
	DDX_Text(pDX, IDC_EDIT_BREITE, m_strBreite);
	DDX_Text(pDX, IDC_EDIT_DICKE, m_strDicke);
	DDX_Text(pDX, IDC_EDIT_FEHLBREITE, m_strFehlbreite);
	DDX_Text(pDX, IDC_EDIT_FEHLLAENGE, m_strFehllaenge);
	//DDX_Text(pDX, IDC_EDIT_FEHLNUMMER, m_strFehlnummer);
	DDX_Text(pDX, IDC_EDIT_HINWEIS, m_strHinweis);
	DDX_Text(pDX, IDC_EDIT_LAENGE, m_strLaenge);
	DDX_Text(pDX, IDC_EDIT_MENGE1, m_strMenge1);
	DDX_Text(pDX, IDC_EDIT_PREIS, m_strPreis);
	DDX_Text(pDX, IDC_EDIT_STEINNR, m_strSteinnummer);
	DDX_Text(pDX, IDC_EDIT_STEINNRBIS, m_strSteinnummerBis);
	DDX_Text(pDX, IDC_STATIC_LIEFERANT, m_strLieferant);
	DDX_Text(pDX, IDC_STATIC_MATERIALART, m_strMaterialArt);
	DDX_Text(pDX, IDC_STATIC_OBERFLAECHE, m_strOberflaeche);
	//DDX_CBString(pDX, IDC_COMBO_ME1, m_strME1);
	DDX_Check(pDX, IDC_CHECK_ENDE, m_bCheckEnde);
	DDX_Text(pDX, IDC_EDIT_REST, m_strRest);
	//DDX_CBString(pDX, IDC_COMBO_ME2, m_strComboME2);
	DDX_CBString(pDX, IDC_COMBO_LAGER, m_strComboLager);
	DDX_Text(pDX, IDC_EDIT_LIEFERSCHEIN, m_strEditLieferschein);
	DDX_Text(pDX, IDC_EDIT_DATUM, m_strEditDatum);
	DDX_Control(pDX, IDC_COMBO_FEHLER1, m_ctrlComboFehler);
	DDX_Control(pDX, IDC_BUTTON_INFOVORABDATEN, m_ctrlButtonInfoVorab);
	DDX_Control(pDX, IDC_EDIT_LIEFERSCHEIN, m_ctrlEditLieferschein);
	DDX_Control(pDX, IDC_EDIT_HINWEIS, m_ctrlEditHinweis);
	DDX_Control(pDX, IDC_EDIT_LAGERORT, m_ctrlEditLagerort);
	DDX_Control(pDX, IDC_EDIT_PREIS, m_ctrlEditPreis);
	DDX_Control(pDX, IDC_STATIC_ARTIKELGRUPPE, m_ctrlStaticArtikelgruppe);
	DDX_Control(pDX, IDNEU, m_ctrlNeu);
}


BEGIN_MESSAGE_MAP(CPlattenZugang, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_ME1, OnSelchangeComboMe1)
	ON_BN_CLICKED(IDC_BUTTON_EIGENSCHAFTEN, OnButtonEigenschaften)
	ON_EN_KILLFOCUS(IDC_EDIT_BESTELLNR, OnKillfocusEditBestellnr)
	ON_EN_KILLFOCUS(IDC_EDIT_BESTELLPOS, OnKillfocusEditBestellpos)
	ON_EN_SETFOCUS(IDC_EDIT_LIEFERSCHEIN, OnSetfocusEditLieferschein)
	ON_EN_SETFOCUS(IDC_EDIT_STEINNR, OnSetfocusEditSteinnr)
	ON_EN_SETFOCUS(IDC_EDIT_BESTELLNR, OnSetfocusEditBestellnr)
	ON_EN_KILLFOCUS(IDC_EDIT_STEINNR, OnKillfocusEditSteinnr)
	ON_EN_SETFOCUS(IDC_EDIT_BESTELLPOS, OnSetfocusEditBestellpos)
	ON_EN_KILLFOCUS(IDC_EDIT_LIEFERSCHEIN, OnKillfocusEditLieferschein)
	ON_CBN_SETFOCUS(IDC_COMBO_LAGER, OnSetfocusComboLager)
	ON_CBN_KILLFOCUS(IDC_COMBO_LAGER, OnKillfocusComboLager)
	ON_BN_CLICKED(IDC_BUTTON_HINZU, OnButtonHinzu)
	ON_CBN_SELCHANGE(IDC_COMBO_LAGER, OnSelchangeComboLager)
    ON_EN_KILLFOCUS(IDC_EDIT_LAENGE, &CPlattenZugang::OnEnKillfocusEditLaenge)
    ON_EN_KILLFOCUS(IDC_EDIT_BREITE, &CPlattenZugang::OnEnKillfocusEditBreite)
    ON_EN_KILLFOCUS(IDC_EDIT_FEHLLAENGE, &CPlattenZugang::OnEnKillfocusEditFehllaenge)
    ON_EN_KILLFOCUS(IDC_EDIT_FEHLBREITE, &CPlattenZugang::OnEnKillfocusEditFehlbreite)
	ON_EN_CHANGE(IDC_EDIT_STEINNR, &CPlattenZugang::OnEnChangeEditSteinnr)
	ON_BN_CLICKED(IDC_BUTTON_INFOVORABDATEN, &CPlattenZugang::OnBnClickedButtonInfovorabdaten)
	ON_EN_KILLFOCUS(IDC_EDIT_HINWEIS, &CPlattenZugang::OnEnKillfocusEditHinweis)
	ON_EN_CHANGE(IDC_EDIT_LAGERORT, &CPlattenZugang::OnEnChangeEditLagerort)
	ON_BN_CLICKED(IDNEU, &CPlattenZugang::OnButtonNeu)
	ON_EN_SETFOCUS(IDC_EDIT_STEINNRBIS, &CPlattenZugang::OnEnSetfocusEditSteinnrbis)
	ON_EN_KILLFOCUS(IDC_EDIT_STEINNRBIS, &CPlattenZugang::OnEnKillfocusEditSteinnrbis)
	ON_EN_CHANGE(IDC_EDIT_STEINNRBIS, &CPlattenZugang::OnEnChangeEditSteinnrbis)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
BOOL CPlattenZugang::OnInitDialog() 
{
CDialog::OnInitDialog();

TranslateButton(m_ctrlButtonEigenschaften);
TranslateButton(m_ctrlCheckEnde);
TranslateButton(m_ctrlCancel);
TranslateButton(m_ctrlButtonHinzu);
TranslateButton(m_ctrlButtonInfoVorab);

TranslateStatic(m_ctrlStaticBestellnr);
TranslateStatic(m_ctrlStaticPosition);
TranslateStatic(m_ctrlStaticSteinnr);
TranslateStatic(m_ctrlStaticBis);
TranslateStatic(m_ctrlStaticLieferschein);
TranslateStatic(m_ctrlStaticDatum);
TranslateStatic(m_ctrlStaticMenge);
TranslateStatic(m_ctrlStaticMasse);
TranslateStatic(m_ctrlStaticFehlecke);
TranslateStatic(m_ctrlStaticHinweis);
TranslateStatic(m_ctrlStaticPreis);

// Preisfeld vorerst einmal komplett sperren, da die Mitarbeiter den Preis nicht sehen sollen ch 30.10.2012
// vielleicht später einmal durch einen Schalter freigeben.
m_ctrlStaticPreis.ShowWindow(FALSE);
m_ctrlEditPreis.ShowWindow(FALSE);

m_tabArtikelGruppen.Read();
m_tabMaterialGruppen.Read();
m_tabAlleMaterialArten.Read();
m_tabAlleOberflaechen.Read();
m_tabLagerOrte.Read();
m_tabLieferanten.Read();
m_tabEinheiten.Read();
m_tabFehlerbezeichnung.Read();
C2String s2;
m_tabFehlerbezeichnung.InsertAt(0,s2); // Leerauswahl ermöglichen

int i;
for(i = 0; i < m_tabEinheiten.GetSize(); i++)
    m_me1Tab.Add(m_tabEinheiten.GetAt(i).m_bez);
for(i = 0; i < m_tabLagerOrte.GetSize(); i++)
    {
    CString str;
    str.Format(_T("%s %s"),m_tabLagerOrte.GetAt(i).m_key,m_tabLagerOrte.GetAt(i).m_bez);
    m_ctrlComboLager.AddString(str);
    }
for(i = 0; i < m_tabFehlerbezeichnung.GetCount(); i++)
    m_ctrlComboFehler.AddString(m_tabFehlerbezeichnung.GetAt(i).m_bez);

if(Zugang())
    StartZugang();
else
    {
    if(Einkauf())
        StartEinkauf();
    else
        StartElse();
    }
//Button für die Vorabdaten erst einmal ausschalten
m_ctrlButtonInfoVorab.ShowWindow(FALSE);
m_ctrlSteinnummer.SetLimitText(10);

UpdateData(FALSE);

return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//---------------------------------------------------------------------------------------
void CPlattenZugang::SetComboLager(const CString& strLagerKey)
{
int index = m_tabLagerOrte.GetIndexByKey(strLagerKey);

if(index >= 0)
    {
    m_ctrlComboLager.SetCurSel(index);
    CString str;
    str.Format(_T("%s %s"),m_tabLagerOrte.GetAt(index).m_key,m_tabLagerOrte.GetAt(index).m_bez);
    m_strComboLager = str;
    }
else
    {
    m_ctrlComboLager.SetCurSel(0);
    m_strComboLager = _T("");
    }
}
//---------------------------------------------------------------------------------------
void CPlattenZugang::SetComboFehler(const CString& strKey)
{
int index = m_tabFehlerbezeichnung.GetIndexByKey(strKey);

if((index < 0) || (index >= m_ctrlComboFehler.GetCount()))
    index = 0;

m_ctrlComboFehler.SetCurSel(index);
}
//------------------------------------------------------------------------------------------
CString CPlattenZugang::GetComboFehler()
{
int index = m_ctrlComboFehler.GetCurSel();
if((index < 0) || (index >= m_tabFehlerbezeichnung.GetCount()))
    index = 0;

return m_tabFehlerbezeichnung.GetAt(index).m_key;
}
//---------------------------------------------------------------------------------------
void CPlattenZugang::StartZugang()
{


if(m_pAuftraege->Auftrag(0).m_Positionen.Anzahl())   // lezten hinzugefügten Steinsatz lesen
    g_baseSteinSatz = m_pAuftraege->Auftrag(0).Position(m_pAuftraege->Auftrag(0).m_Positionen.Anzahl()-1); 


// alte Daten sollen nicht mehr vorgeblendet werden		ch 11.09.2013
//SSatz s(g_baseSteinSatz);
CSteinSatz steinsatzLeer;
SSatz s(steinsatzLeer);

m_strBestellNr = s.m_BestellNr;
m_strBestellPos = s.m_BestellPos;
if (!s.m_Artikel.IsEmpty())
	m_strArtikelGruppe = s.m_Artikel;
else
	m_strArtikelGruppe = s.m_ArtikelGrBez;
m_strMaterialArt = s.m_Material;
m_strOberflaeche = s.m_Oberflaeche;
//m_strLagerOrt = m_tabLagerOrte.GetItemByKey(s.m_Lager).m_bez;
SetComboLager(s.m_Lager);
m_strLieferant = m_tabLieferanten.GetItemByKey(s.m_Lieferant).m_bez;
m_strMenge1 = s.m_Menge1;
m_strME1 = s.m_ME1;
m_strLaenge = s.m_Laenge;
m_strBreite = s.m_Breite;
m_strDicke = s.m_Dicke;
m_strFehllaenge = s.m_FehlLaenge;
m_strFehlbreite = s.m_FehlBreite;
//m_strFehlnummer = s.m_FehlNummer;
SetComboFehler(s.m_FehlNummer);
m_strHinweis = s.m_Hinweis;
m_strPreis = s.m_Preis;
m_strEditLieferschein = s.m_LieferscheinNummer;
if(s.m_LieferscheinDatum.IsEmpty())
    {
    CTime time;
    time = CTime::GetCurrentTime();
    m_strEditDatum.Format(_T("%02d.%02d.%4d"),time.GetDay(),time.GetMonth(),time.GetYear());
    }
else
    m_strEditDatum.Format(_T("%s.%s.%s"),s.m_LieferscheinDatum.Left(2),s.m_LieferscheinDatum.Mid(2,2),s.m_LieferscheinDatum.Mid(4,4));


SSatz ss;
ss.m_BestellNr = s.m_BestellNr;
ss.m_BestellPos = s.m_BestellPos;
ss.m_Artikel = s.m_Artikel;
ss.m_ArtNr = s.m_ArtNr;
ss.m_ArtikelGr = s.m_ArtikelGr;
ss.m_ArtikelGrBez = s.m_ArtikelGrBez;
ss.m_MatGr = s.m_MatGr;
ss.m_MatNr = s.m_MatNr;
ss.m_Material = s.m_Material;
ss.m_OberNr = s.m_OberNr;
ss.m_Oberflaeche = s.m_Oberflaeche;
ss.m_Lager = s.m_Lager;
ss.m_Lieferant = s.m_Lieferant;
ss.m_Menge1 = s.m_Menge1;
ss.m_ME1 = s.m_ME1;
ss.m_Laenge = s.m_Laenge;
ss.m_Breite = s.m_Breite;
ss.m_Dicke = s.m_Dicke;
ss.m_FehlLaenge = s.m_FehlLaenge;
ss.m_FehlBreite = s.m_FehlBreite;
ss.m_FehlNummer = s.m_FehlNummer;
ss.m_Hinweis = s.m_Hinweis;
ss.m_Preis = s.m_Preis;
ss.m_TextFeld = s.m_TextFeld;

g_baseSteinSatz.Set(ss);    // alles andere gelöscht

SetComboME1(s.m_ME1);

m_pScanner->setEnableScanner(TRUE);   // Hier scannen erlauben

m_ctrlSteinnummer.SetFocus();

// Lesen der Block-Vorabdaten (als CSteinsaetze)
m_Vorabdaten.ReadFile(DATEI_VORABDATEN);

//bestimmte Felder nicht anzeigen
m_ctrlStaticBestellnr.ShowWindow(FALSE);
m_ctrlBestellNr.ShowWindow(FALSE);
m_ctrlStaticPosition.ShowWindow(FALSE);
m_ctrlBestellPos.ShowWindow(FALSE);

if(!g_Optionen.ZugangSteinnrVonBisEnabled())
	{
	m_ctrlStaticBis.ShowWindow(FALSE);
	m_ctrlSteinnummerBis.ShowWindow(FALSE);
	}
}
//---------------------------------------------------------------------------------------
void CPlattenZugang::StartEinkauf()
{
m_ctrlBestellNr.EnableWindow(FALSE);
//m_ctrlBestellPos.EnableWindow(FALSE);
m_ctrlStaticBis.ShowWindow(FALSE);
m_ctrlSteinnummerBis.ShowWindow(FALSE);

SSatz s(g_baseSteinSatz);
m_strBestellNr = s.m_BestellNr;
m_strBestellPos = s.m_BestellPos;
m_strSteinnummer = s.m_Nummer;
if(m_strSteinnummer.CompareNoCase(_T("OHNE")))
    m_strSteinnummer.Empty();
m_strArtikelGruppe = s.m_Artikel;   // Statt Artikelgruppe Artikel anzeigen (nicht änderbar)
m_strMaterialArt = s.m_Material;
m_strOberflaeche = s.m_Oberflaeche;
m_strLieferant = m_tabLieferanten.GetItemByKey(s.m_Lieferant).m_bez;
m_strMenge1 = _T("1");
m_strLaenge = s.m_Laenge;
m_strBreite = s.m_Breite;
m_strDicke = s.m_Dicke;
m_strFehllaenge = s.m_FehlLaenge;
m_strFehlbreite = s.m_FehlBreite;
//m_strFehlnummer = s.m_FehlNummer;
SetComboFehler(s.m_FehlNummer);
m_strHinweis = s.m_Hinweis;
m_strPreis = s.m_Preis;
m_strEditLieferschein = s.m_LieferscheinNummer;

m_strRest = CalcRest(m_pBestellungen,&m_pAuftraege->Auftrag(0),m_strBestellNr,m_strBestellPos);

SetComboME1(s.m_ME1);
SetComboME2(s.m_ME2);
SetComboLager(s.m_Lager);

if(s.m_LieferscheinDatum.IsEmpty())
    {
    CTime time;
    time = CTime::GetCurrentTime();
    m_strEditDatum.Format(_T("%02d.%02d.%4d"),time.GetDay(),time.GetMonth(),time.GetYear());
    }
else
    m_strEditDatum.Format(_T("%s.%s.%s"),s.m_LieferscheinDatum.Left(2),s.m_LieferscheinDatum.Mid(2,2),s.m_LieferscheinDatum.Mid(4,4));

m_pScanner->setEnableScanner(TRUE);   // Hier scannen erlauben

if(m_strSteinnummer.CompareNoCase(_T("OHNE")))
    m_ctrlSteinnummer.SetFocus();
else
    {
    m_ctrlMenge1.SetSel(0,-1);
    m_ctrlMenge1.SetFocus();
    }
UpdateData(FALSE);
}
//---------------------------------------------------------------------------------------
void CPlattenZugang::StartElse()
{
m_ctrlSteinnummer.EnableWindow(FALSE);
m_ctrlStaticBis.ShowWindow(FALSE);
m_ctrlSteinnummerBis.ShowWindow(FALSE);

SSatz s(g_baseSteinSatz);
m_strSteinnummer = s.m_Nummer;
m_strBestellNr = s.m_BestellNr;
m_strBestellPos = s.m_BestellPos;
m_strArtikelGruppe = s.m_ArtikelGrBez;
m_strMaterialArt = s.m_Material;
m_strOberflaeche = s.m_Oberflaeche;
//m_strLagerOrt = m_tabLagerOrte.GetItemByKey(s.m_Lager).m_bez;
SetComboLager(s.m_Lager);
m_strLieferant = m_tabLieferanten.GetItemByKey(s.m_Lieferant).m_bez;
m_strMenge1 = s.m_Menge1;
m_strME1 = s.m_ME1;
m_strLaenge = s.m_Laenge;
m_strBreite = s.m_Breite;
m_strDicke = s.m_Dicke;
m_strFehllaenge = s.m_FehlLaenge;
m_strFehlbreite = s.m_FehlBreite;
//m_strFehlnummer = s.m_FehlNummer;
SetComboFehler(s.m_FehlNummer);
m_strHinweis = s.m_Hinweis;
m_strPreis = s.m_Preis;

SetComboME1(s.m_ME1);

m_pScanner->setEnableScanner(FALSE);   // Hier scannen verbieten

m_ctrlBestellNr.EnableWindow(FALSE);
m_ctrlBestellPos.EnableWindow(FALSE);
m_ctrlButtonHinzu.EnableWindow(FALSE);
//m_ctrlCancel.EnableWindow(FALSE);


m_ctrlMenge1.SetFocus();
}
/////////////////////////////////////////////////////////////////////////////
// CPlattenZugang message handlers

//--------------------------------------------------------------------------------------------
void CPlattenZugang::OnSelchangeComboMe1() 
{
	// TODO: Add your control notification handler code here
	
}
//--------------------------------------------------------------------------------------------
void CPlattenZugang::OnButtonEigenschaften() 
{
UpdateData(TRUE);

CEigenschaften eig(this);

eig.m_tabArtikelGruppen = m_tabArtikelGruppen;
eig.m_tabMaterialGruppen = m_tabMaterialGruppen;
eig.m_tabAlleMaterialArten = m_tabAlleMaterialArten;
eig.m_tabAlleOberflaechen = m_tabAlleOberflaechen;
eig.m_tabLagerOrte = m_tabLagerOrte;
eig.m_tabLieferanten = m_tabLieferanten;

if(eig.DoModal() != IDOK)
    return;

SSatz s(g_baseSteinSatz); // wurde in eig.modal aktualisiert

if(!Einkauf())  // Bei Einkauf ist Artikel eingetragen, das bleibt
	if (!s.m_Artikel.IsEmpty())
		m_strArtikelGruppe = s.m_Artikel;
	else
		m_strArtikelGruppe = s.m_ArtikelGrBez;
m_strMaterialArt = s.m_Material;
m_strOberflaeche = s.m_Oberflaeche;
//m_strLagerOrt = m_tabLagerOrte.GetItemByKey(s.m_Lager).m_bez;
SetComboLager(s.m_Lager);
m_strLieferant = m_tabLieferanten.GetItemByKey(s.m_Lieferant).m_bez;

/*
m_strLaenge.Empty();
m_strBreite.Empty();
m_strDicke.Empty();
m_strFehllaenge.Empty();
m_strFehlbreite.Empty();
m_strFehlnummer.Empty();
m_strHinweis.Empty();
m_strPreis.Empty();
*/
UpdateData(FALSE);
}
//--------------------------------------------------------------------------------------------
void CPlattenZugang::SetComboME1(const TCHAR *ME1)
{
m_comboME1.ResetContent();
int i;
for(i = 0; i < m_me1Tab.GetSize(); i++)
    {
    m_comboME1.AddString(m_me1Tab.GetAt(i));
    }
int ix = m_comboME1.FindStringExact(0,ME1);
if(ix < 0)
    ix = 0;
m_comboME1.SetCurSel(ix);
m_strME1 = m_me1Tab.GetAt(ix);

UpdateData(FALSE);
}
//--------------------------------------------------------------------------------------------
void CPlattenZugang::SetComboME2(const TCHAR *ME2)
{
m_ctrlComboME2.ResetContent();
int i;
for(i = 0; i < m_me1Tab.GetSize(); i++)
    {
    m_ctrlComboME2.AddString(m_me1Tab.GetAt(i));
    }
int ix = m_tabEinheiten.GetIndexByValue(ME2);
if(ix < 0)
    ix = 0;
m_ctrlComboME2.SetCurSel(ix);
//m_strComboME2 = m_me1Tab.GetAt(ix);
m_ctrlComboME2.GetLBText(ix,m_strComboME2);

UpdateData(FALSE);
}
//-------------------------------------------------------------------------------
// wird über Button "Hinzu" aufgerufen
void CPlattenZugang::OnButtonHinzu()
{
/* Inventur nur über OK */

if(Einkauf())
    {
    OnHinzuEinkauf();
    return;
    }
if(Zugang())
    {
    OnHinzuZugang();
    return;
    }
}
//-------------------------------------------------------------------------------
BOOL CPlattenZugang::OnHinzuZugang()
{
UpdateData(TRUE);

int index;
if(m_pAuftraege->Auftrag(0).m_Positionen.FoundAt(m_strSteinnummer,index))
    {
    AfxMessageBox(Sprache(_T("Steinnummer bereits im Zugang vorhanden!")));
    return FALSE;
    }
if(m_pSteinSaetze->FoundAt(m_strSteinnummer,index))
    {
    AfxMessageBox(Sprache(_T("Steinnummer bereits im Bestand vorhanden!")));
    return FALSE;
    }
if(!m_strSteinnummerBis.IsEmpty() )
	{
	if(m_pAuftraege->Auftrag(0).m_Positionen.FoundAt(m_strSteinnummerBis,index))
		{
		AfxMessageBox(Sprache(_T("Steinnummer-Bis bereits im Zugang vorhanden!")));
		return FALSE;
		}
	if(m_pSteinSaetze->FoundAt(m_strSteinnummerBis,index))
		{
		AfxMessageBox(Sprache(_T("Steinnummer-Bis bereits im Bestand vorhanden!")));
		return FALSE;
		}
	int ix_vorab;
	if (!m_Vorabdaten.FoundAt(m_strSteinnummerBis, ix_vorab) )
		{
		AfxMessageBox(Sprache(_T("Steinnummer-Bis nicht im Vorab-Bestand vorhanden!")));
		return FALSE;
		}
	}

if(!WerteOk()) return FALSE;

// Einrichten einer Schleife, so das alle Steinnr von/bis eingetragen werden ch 14.03.2017
if (m_strSteinnummerBis.IsEmpty())
	m_strSteinnummerBis = m_strSteinnummer ;
BOOL bWeiter = TRUE;
BOOL bErsteSteinnr = TRUE;
int nVonNr = _wtoi(m_strSteinnummer);
int nBisNr = _wtoi(m_strSteinnummerBis);
if ( nBisNr < nVonNr)
	{
	PlaySoundError();
	AfxMessageBox(Sprache(_T("Bis Steinnummer nicht korrekt!")),MB_OK|MB_ICONEXCLAMATION);
	m_ctrlSteinnummerBis.SetFocus();
	return FALSE;
	}
	if ((nBisNr - nVonNr) > 100)
	{
	PlaySoundError();
	AfxMessageBox(Sprache(_T("Max. 100 Platten buchbar!")),MB_OK|MB_ICONEXCLAMATION);
	m_ctrlSteinnummerBis.SetFocus();
	return FALSE;
	}
CString sLagerort = _T("");
BOOL bAenderungUebernehmen = FALSE;
if ( !(nVonNr == nBisNr) && bGeaendertLager)
	{
	int ret = AfxMessageBox(_T("Lagerort für alle Zugänge übernehmen?"),MB_YESNO);
	if (ret == IDYES )
		bAenderungUebernehmen = TRUE;
		sLagerort = m_tabLagerOrte.GetAt(m_ctrlComboLager.GetCurSel()).m_key;
	}

int AnzZugang = 0;
SSatz s;
while(bWeiter)
{

	SSatz ss(g_baseSteinSatz);
	// Falls irgendwo Unsinn steht (nur prüfen wenn enabled)

	ss.m_BestellNr = m_strBestellNr;
	ss.m_BestellPos = m_strBestellPos;
	ss.m_Nummer = m_strSteinnummer;

	ss.m_Menge1 = m_strMenge1;
	m_comboME1.GetLBText(m_comboME1.GetCurSel(),m_strME1);
	ss.m_ME1 = m_strME1;
	ss.m_Laenge = m_strLaenge;
	ss.m_Breite = m_strBreite;
	ss.m_Dicke = m_strDicke;
	ss.m_FehlLaenge = m_strFehllaenge;
	ss.m_FehlBreite = m_strFehlbreite;
	ss.m_FehlNummer = GetComboFehler();
	//ss.m_FehlNummer = m_strFehlnummer;
	ss.m_Hinweis = m_strHinweis;
	ss.m_Preis = m_strPreis;
	ss.m_LieferscheinNummer = CPlattenZugang::m_strEditLieferschein;
	if(!CheckDatum(m_strEditDatum,ss.m_LieferscheinDatum))
		{
		AfxMessageBox(Sprache(_T("Falsches Datumformat!")));
		m_ctrlEditDatum.SetFocus();
		return FALSE;
		}
	ss.m_Ende.Empty();
	if(CPlattenZugang::m_bCheckEnde)
		{
		ss.m_Ende = _T("E");
		CPlattenZugang::m_bCheckEnde = FALSE;
		}
	g_baseSteinSatz.Set(ss);

	g_baseSteinSatz.SetDatumZeit();
	g_baseSteinSatz.m_buchungsNummer = NaechsteBuchungsnummer();

	g_baseSteinSatz.SetMenge2(0.);  // immer auf 0.
	g_baseSteinSatz.SetMenge1Verfuegbar(g_baseSteinSatz.Menge1());

	m_pAuftraege->Auftrag(0).AddPosition(g_baseSteinSatz);

	//////////////////////////////////////// neu 15.3.06
	m_pSteinSaetze->AddSatz(g_baseSteinSatz); // Menge 1 zu Steinsätze hinzufügen
////////////////////////////////////////
	if (AnzZugang == 0 )
		PlaySoundAdd();
	AnzZugang = AnzZugang + 1; 

	if (bErsteSteinnr)
		{
		// m_hinzEnable = FALSE;
	
		//m_strFehllaenge.Empty();
		//m_strFehlbreite.Empty();
		//m_strFehlnummer.Empty();

		// nach dem Hinzufügen ALLE Felder wieder leer machen! auch den g_baseSteinSatz, damit nichts mehr vorgeblendet werden kann.

		g_baseSteinSatz.Set (s);
		bErsteSteinnr = FALSE;
		}

	// Nächste Steinnummer finden
	if (nVonNr >= nBisNr)
		bWeiter = FALSE;
	else
		{
		BOOL bGefundenOderAbbruch = FALSE;
		int ix;
		while (!bGefundenOderAbbruch)
			{
			nVonNr = nVonNr + 1;
			ix = -1;	
			if (nVonNr <= nBisNr)
				{
				m_strSteinnummer.Format(_T("%d"),nVonNr);
				if(m_Vorabdaten.FoundAt(m_strSteinnummer, ix))
					{
					bGefundenOderAbbruch = TRUE;
					int ix_auftrag;
					m_pAuftraege->Auftrag(0).m_Positionen.FoundAt(m_strSteinnummer, ix_auftrag);
					if (ix_auftrag < 0)
						{
						VorabDatenUebernehmen(m_strSteinnummer);
						m_strSteinnummer.Format(_T("%d"),nVonNr);
						if (bAenderungUebernehmen)
							{
							SSatz tempSS(g_baseSteinSatz);
							tempSS.m_Lager = sLagerort;
							g_baseSteinSatz.Set(tempSS);
							}
						}
					}
				}
			else
				bGefundenOderAbbruch = TRUE;
		}
		if (ix == -1)
			bWeiter = FALSE;
		}	
}

if (AnzZugang >= 2)
	{
	PlaySoundAdd();
	CString str;
	str.Format(_T("%d %s"), AnzZugang, Sprache( _T("Steinnummern zugebucht!")) );
	AfxMessageBox(str);
	}

// sicherung aus der ersten Steinnummer wieder eintragen
m_strBestellNr = s.m_BestellNr;
m_strBestellPos = s.m_BestellPos;
m_strArtikelGruppe = s.m_ArtikelGrBez;
m_strMaterialArt = s.m_Material;
m_strOberflaeche = s.m_Oberflaeche;
SetComboLager(s.m_Lager);
m_strLieferant = m_tabLieferanten.GetItemByKey(s.m_Lieferant).m_bez;
m_strMenge1 = s.m_Menge1;
m_strME1 = s.m_ME1;
m_strLaenge = s.m_Laenge;
m_strBreite = s.m_Breite;
m_strDicke = s.m_Dicke;
m_strFehllaenge = s.m_FehlLaenge;
m_strFehlbreite = s.m_FehlBreite;
SetComboFehler(s.m_FehlNummer);
m_strHinweis = s.m_Hinweis;
m_strPreis = s.m_Preis;
m_strEditLieferschein = s.m_LieferscheinNummer;
CTime time;
time = CTime::GetCurrentTime();
m_strEditDatum.Format(_T("%02d.%02d.%4d"),time.GetDay(),time.GetMonth(),time.GetYear());

m_ctrlSteinnummer.EnableWindow (TRUE);
m_ctrlButtonInfoVorab.ShowWindow(FALSE);
m_strSteinnummer.Empty();
m_ctrlSteinnummer.SetFocus();
m_ctrlSteinnummerBis.EnableWindow (TRUE);
m_strSteinnummerBis.Empty();

bGeaendertLager = FALSE;

UpdateData(FALSE);
SperrenEntsperrenFelderBeiBisSteinnr();
return TRUE;
}
//-------------------------------------------------------------------------------
BOOL CPlattenZugang::OnHinzuInventur()
{
UpdateData(TRUE);

if(!WerteOk()) return FALSE;

SSatz ss(g_baseSteinSatz);
// Falls irgendwo Unsinn steht (nur prüfen wenn enabled)

ss.m_BestellNr = m_strBestellNr;
ss.m_BestellPos = m_strBestellPos;
ss.m_Nummer = m_strSteinnummer;

ss.m_Menge1 = m_strMenge1;
m_comboME1.GetLBText(m_comboME1.GetCurSel(),m_strME1);
ss.m_ME1 = m_strME1;
ss.m_Laenge = m_strLaenge;
ss.m_Breite = m_strBreite;
ss.m_Dicke = m_strDicke;
ss.m_FehlLaenge = m_strFehllaenge;
ss.m_FehlBreite = m_strFehlbreite;
ss.m_FehlNummer = GetComboFehler();
//ss.m_FehlNummer = m_strFehlnummer;
ss.m_Hinweis = m_strHinweis;
ss.m_Preis = m_strPreis;

g_baseSteinSatz.Set(ss);

// Rest wird in Positionen erledigt
return TRUE;
}
//-------------------------------------------------------------------------------
BOOL CPlattenZugang::OnHinzuEinkauf()   //!! hier verwaltung von gleichen Nummern handlen
{
UpdateData(TRUE);

int index;
if(m_tabArtikelGruppen.IsRohPlattenGruppe(g_baseSteinSatz.ArtikelGr()))  // Nur bei Rohplatten auf Nummer prüfen
    {
    if(m_pAuftraege->Auftrag(0).m_Positionen.FoundAt(m_strSteinnummer,index))
        {
        AfxMessageBox(Sprache(_T("Steinnummer bereits im Eingang vorhanden!")));
        return FALSE;
        }
    if(m_pSteinSaetze->FoundAt(m_strSteinnummer,index))
        {
        AfxMessageBox(Sprache(_T("Steinnummer bereits im Bestand vorhanden!")));
        return FALSE;
        }
    }
if(m_bCheckEnde && 
    (m_strSteinnummer.IsEmpty() || (!m_strSteinnummer.CompareNoCase(_T("OHNE")) && m_strMenge1.IsEmpty())))
    {
    if(AddEnde())  // Ende-Kennzeichen wird im letzten Steinastz zur Bestellposition altiviert
        {
        PlaySoundAdd();
        return TRUE;
        }
    return FALSE;
    }

if(!WerteOk()) return FALSE;
// Falls irgendwo Unsinn steht (nur prüfen wenn enabled)

SSatz ss(g_baseSteinSatz);


ss.m_BestellNr = m_strBestellNr;
ss.m_BestellPos = m_strBestellPos;
ss.m_Nummer = m_strSteinnummer;

ss.m_Menge1 = m_strMenge1;
m_comboME1.GetLBText(m_comboME1.GetCurSel(),m_strME1);
ss.m_ME1 = m_strME1;
ss.m_Laenge = m_strLaenge;
ss.m_Breite = m_strBreite;
ss.m_Dicke = m_strDicke;
ss.m_FehlLaenge = m_strFehllaenge;
ss.m_FehlBreite = m_strFehlbreite;
ss.m_FehlNummer = GetComboFehler();
//ss.m_FehlNummer = m_strFehlnummer;
ss.m_Hinweis = m_strHinweis;
ss.m_Preis = m_strPreis;
ss.m_LieferscheinNummer = CPlattenZugang::m_strEditLieferschein;
if(!CheckDatum(m_strEditDatum,ss.m_LieferscheinDatum))
    {
    AfxMessageBox(Sprache(_T("Falsches Datumformat!")));
    m_ctrlEditDatum.SetFocus();
    return FALSE;
    }
ss.m_Preis = m_strPreis;
ss.m_Lager = _T("");
if((m_ctrlComboLager.GetCurSel() >= 0) && !m_strComboLager.IsEmpty())
    ss.m_Lager = CPlattenZugang::m_tabLagerOrte.GetAt(m_ctrlComboLager.GetCurSel()).m_key;
ss.m_Ende.Empty();
if(CPlattenZugang::m_bCheckEnde)
    {
    ss.m_Ende = _T("E");
    CPlattenZugang::m_bCheckEnde = FALSE;   // Wieder für nächsten Eintrag löschen
    }
g_baseSteinSatz.Set(ss);

g_baseSteinSatz.SetDatumZeit();
g_baseSteinSatz.m_buchungsNummer = NaechsteBuchungsnummer();

//AlertInt(g_baseSteinSatz.m_buchungsNummer);

g_baseSteinSatz.SetMenge2(0.);  // immer auf 0.
g_baseSteinSatz.SetMenge1Verfuegbar(g_baseSteinSatz.Menge1());

if(!ss.m_Nummer.CompareNoCase(_T("OHNE")))
    m_pAuftraege->Auftrag(0).m_Positionen.Add(g_baseSteinSatz);    // "Ohne" kann mehrfach vorkommen
else
    m_pAuftraege->Auftrag(0).m_Positionen.AddSatz(g_baseSteinSatz);// Wenn Nummer vorhanden, Mengen addieren, sonst hinzufügen

//////////////////////////////////////// 
if(ss.m_Nummer.CompareNoCase(_T("OHNE")))
    m_pSteinSaetze->AddSatz(g_baseSteinSatz); // Menge1 zu Steinsätze hinzufügen (nur wenn Steinnummer nicht OHNE)
////////////////////////////////////////

PlaySoundAdd();

m_strRest = CalcRest(m_pBestellungen,&m_pAuftraege->Auftrag(0),m_strBestellNr,m_strBestellPos);

StartEinkauf();

return TRUE;
}
//------------------------------------------------------------------------------------------
void CPlattenZugang::OnButtonNeu()
{
	UpdateData(TRUE);
	
	// ALLE Felder wieder leer machen! auch den g_baseSteinSatz, damit nichts mehr vorgeblendet werden kann.
	SSatz s;
	g_baseSteinSatz.Set (s);
	m_strBestellNr = s.m_BestellNr;
	m_strBestellPos = s.m_BestellPos;
	m_strArtikelGruppe = s.m_ArtikelGrBez;
	m_strMaterialArt = s.m_Material;
	m_strOberflaeche = s.m_Oberflaeche;
	SetComboLager(s.m_Lager);
	m_strLieferant = m_tabLieferanten.GetItemByKey(s.m_Lieferant).m_bez;
	m_strMenge1 = s.m_Menge1;
	m_strME1 = s.m_ME1;
	m_strLaenge = s.m_Laenge;
	m_strBreite = s.m_Breite;
	m_strDicke = s.m_Dicke;
	m_strFehllaenge = s.m_FehlLaenge;
	m_strFehlbreite = s.m_FehlBreite;
	SetComboFehler(s.m_FehlNummer);
	m_strHinweis = s.m_Hinweis;
	m_strPreis = s.m_Preis;
	m_strEditLieferschein = s.m_LieferscheinNummer;
	CTime time;
	time = CTime::GetCurrentTime();
	m_strEditDatum.Format(_T("%02d.%02d.%4d"),time.GetDay(),time.GetMonth(),time.GetYear());

	m_ctrlSteinnummer.EnableWindow (TRUE);
	m_ctrlButtonInfoVorab.ShowWindow(FALSE);
	m_strSteinnummer.Empty();
	m_strSteinnummerBis.Empty();
	m_ctrlSteinnummer.SetFocus();
	
	bGeaendertLager = FALSE;
	
	UpdateData(FALSE);
	SperrenEntsperrenFelderBeiBisSteinnr();
}

//------------------------------------------------------------------------------------------
BOOL CPlattenZugang::WerteOk()
{
if(m_strSteinnummer.CompareNoCase(_T("OHNE")))   // 
    {
    if(m_strSteinnummer.IsEmpty())
        {
        m_ctrlSteinnummer.SetFocus();
        PlaySoundError();
        return FALSE;
        }
    }
SSatz s(g_baseSteinSatz); // wurde in eig.modal aktualisiert
m_strArtikelGruppe = s.m_ArtikelGrBez;
m_strMaterialArt = s.m_Material;
m_strOberflaeche = s.m_Oberflaeche;

if(!Einkauf())  // Bei Einkauf nicht prüfen
    {
    if(m_strSteinnummer.CompareNoCase(_T("OHNE")))   // eigentlich unnötig, OHNE kommt nur bei Einkauf vor
        {
			CString suffix(_T(""));
			if (m_tabArtikelGruppen.IsRohPlattenGruppe(s.m_ArtikelGr))
				suffix = _T("R");
			else
				if (m_tabArtikelGruppen.IsRohBlockGruppe(s.m_ArtikelGr))
					suffix = _T("B");

			if((   m_tabArtikelGruppen.GetItemByKey(s.m_ArtikelGr + suffix).m_bez.IsEmpty())
				|| m_tabAlleMaterialArten.GetItemByKey(s.m_MatGr,s.m_MatNr).m_bez.IsEmpty()
				|| m_tabAlleOberflaechen.GetItemByKey(s.m_MatGr,s.m_OberNr).m_bez.IsEmpty())
            {
				AfxMessageBox(Sprache(_T("Eigenschaften definieren!")));
				return FALSE;
            }
        }
    }
if(Einkauf())
    {
    BOOL meOK = FALSE;

    if(!m_strComboME2.Compare(_T("m")))     // Stück- und m-Eingabe
        {
        if(!m_strME1.Compare(_T("Stk")) && WertOk(m_strLaenge,m_ctrlLaenge))
            meOK = TRUE;
        }
    else
        {
        if(!m_strComboME2.Compare(_T("m²")))    // Stück und m²-Eingabe
            {
            if(!m_strME1.Compare(_T("Stk")) && WertOk(m_strLaenge,m_ctrlLaenge) && WertOk(m_strBreite,m_ctrlBreite))
                meOK = TRUE;
            }
        }
    if(!meOK)
        {
        if(!m_strME1.Compare(m_strComboME2))    // Sonst müssen immer die Einheiten übereinstimmen
            meOK = TRUE;
        }

    if(!meOK)
        {
        AfxMessageBox(Sprache(_T("Mengeneinheit ungültig!")));
        return FALSE;
        }
    }

if(!WertOk(m_strMenge1,m_ctrlMenge1)) // leer oder ungültiges format
    return FALSE;
if(!Einkauf())  // Bei Einkauf nicht prüfen
    {
    if(m_strSteinnummer.CompareNoCase(_T("OHNE")) || !Einkauf())
        {
        if(!WertOk(m_strLaenge,m_ctrlLaenge))
            return FALSE;
        if(!WertOk(m_strBreite,m_ctrlBreite))
            return FALSE;
        if(!WertOk(m_strDicke,m_ctrlDicke))
            return FALSE;
        }
    }
if(NoValueSetFocus(m_strFehllaenge,m_ctrlFehllaenge)) // leer erlaubt
    return FALSE;
if(NoValueSetFocus(m_strFehlbreite,m_ctrlFehlbreite))
    return FALSE;
// prüfen, ob FehlLae UND FehlBreite gefüllt sind. Wenn nur eines der Felder gefüllt ist, dann Focus auf entsprechende Feld  ch 14.02.2013
BOOL bFehlLae = FALSE;
BOOL bFehlBr = FALSE;
if (!m_strFehllaenge.IsEmpty() || m_strFehllaenge.GetLength() > 0)
	bFehlLae = TRUE;
if (!m_strFehlbreite.IsEmpty() || m_strFehlbreite.GetLength() > 0)
	bFehlBr = TRUE;
if (bFehlLae && !bFehlBr)
{
	m_ctrlFehlbreite.SetFocus();
    PlaySoundError();
	return FALSE;
}
if (!bFehlLae && bFehlBr)
{
	m_ctrlFehllaenge.SetFocus();
    PlaySoundError();
	return FALSE;
}

return TRUE;
}
//------------------------------------------------------------------------------------------
BOOL CPlattenZugang::WertOk(CString& str,CEdit& edit)
{
if(str.IsEmpty())
    {
    edit.SetFocus();
    PlaySoundError();
    return FALSE;
    }
return !NoValueSetFocus(str,edit);

}
//-----------------------------------------------------------------------------
BOOL CPlattenZugang::PreTranslateMessage(MSG* pMsg) 
{
UpdateData(TRUE);

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
    PlaySoundScan();
    if((m_curFocus == NUMMER)|| (m_curFocus == LIEFERSCHEIN) || (m_curFocus == LAGERORT) || (m_curFocus == NUMMERBIS) )
        {
        if(m_curFocus == NUMMER)
			{
			m_ctrlSteinnummer.EnableWindow (TRUE);
			m_ctrlSteinnummer.SetWindowText(barCode);
            m_strSteinnummer = barCode;
			OnEnChangeEditSteinnr();
			}
        else
            {
            if(m_curFocus == LIEFERSCHEIN)
				{
				m_ctrlEditLieferschein.SetWindowText(barCode);
                m_strEditLieferschein = barCode;
				}
            else
                {
                if(m_curFocus == LAGERORT)
					SetComboLager(barCode);
				else
					{
					m_ctrlSteinnummerBis.SetWindowText(barCode);
					m_strSteinnummerBis = barCode;
					}
				}
			}
 
        UpdateData(FALSE);
        PlaySoundAdd();
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
// Alle Aufträge durchsuchen wegen höchster Nummer
int CPlattenZugang::NaechsteBuchungsnummer() const
{
int maxnum = 0;
for(int i = 0; i < m_pAuftraege->Anzahl(); i++)
    {
    CAuftrag *pAuf = &(m_pAuftraege->Auftrag(i));
    for(int j = 0; j < pAuf->m_Positionen.Anzahl(); j++)
        {
        if(pAuf->m_Positionen.SteinSatz(j).m_buchungsNummer > maxnum)
            maxnum = pAuf->m_Positionen.SteinSatz(j).m_buchungsNummer;
        }
    }
return maxnum+1;
}
//-----------------------------------------------------------------------------
// Menge menge[ME1] nach menge[ME]
double CPlattenZugang::MengeSS(const SSatz& ss,double menge,const CString& ME1,const CString& ME)
{
if(!ME1.Compare(ME))
    return menge;
if(!ME.Compare(_T("m²")))
    {
    if(!ME1.Compare(_T("Stk")))
       return (menge * (CSteinSatz::StringToDouble(ss.m_Laenge) * CSteinSatz::StringToDouble(ss.m_Breite) -
                        CSteinSatz::StringToDouble(ss.m_FehlLaenge) * CSteinSatz::StringToDouble(ss.m_FehlBreite)))/10000.;
    }
if(!ME.Compare(_T("m")))
    {
    if(!ME1.Compare(_T("Stk")))
        return (menge * (CSteinSatz::StringToDouble(ss.m_Laenge) - CSteinSatz::StringToDouble(ss.m_FehlLaenge)))/100.;
    }
return 0.;
// Alles andere gibt keinen Sinn
}
//-----------------------------------------------------------------------------
// Aus bereits gebuchten Platten einer position differenz zu Bestellungen berechnen
CString CPlattenZugang::CalcRest(CSteinSaetze *pBestellungen,CAuftrag *pAuftrag,
                                 const CString& strBestellNr,const CString& strBestellPos)
{
double mengeBestellt = 0.;
double mengeEingang = 0.;
CString MEBestellt;

int i;
for(i = 0; i < pBestellungen->Anzahl(); i++)
    {
    SSatz ss(pBestellungen->SteinSatz(i));
    if(!ss.m_BestellNr.Compare(strBestellNr) && !ss.m_BestellPos.Compare(strBestellPos))
        {
        mengeBestellt += CSteinSatz::StringToDouble(ss.m_Menge2);
        MEBestellt = ss.m_ME2;
        }
    }
for(i = 0; i < pAuftrag->m_Positionen.Anzahl(); i++)
    {
    SSatz ss(pAuftrag->m_Positionen.SteinSatz(i));
    if(!ss.m_BestellNr.Compare(strBestellNr) && !ss.m_BestellPos.Compare(strBestellPos))
        {
        // Eingangsmenge auf Einheit der Bestellmenge umrechnen
        mengeEingang += MengeSS(ss,CSteinSatz::StringToDouble(ss.m_Menge1),ss.m_ME1,MEBestellt);
        }
    }
return CSteinSatz::DoubleToString(mengeBestellt-mengeEingang);
}
//-----------------------------------------------------------------------------
// Ende-Kennzeichen wird im letzten Steinastz zur Bestellposition altiviert
BOOL CPlattenZugang::AddEnde()
{
for(int i = m_pAuftraege->Auftrag(0).m_Positionen.Anzahl()-1; i >= 0; i--)
    {
    SSatz ss(m_pAuftraege->Auftrag(0).Position(i));
    if(!ss.m_BestellNr.Compare(m_strBestellNr) && !ss.m_BestellPos.Compare(m_strBestellPos))
        {
        ss.m_Ende = _T("E");
        CSteinSatz satz;
        satz.Set(ss);
        m_pAuftraege->Auftrag(0).Position(i) = satz;
        return TRUE;
        }
    }
return FALSE;
}
//-----------------------------------------------------------------------------
// falls noch nicht eingetragen, fragen
void CPlattenZugang::OnOK() 
{
UpdateData(TRUE);

int index;
if(Zugang())
    {
    if(!m_strSteinnummer.IsEmpty() && !m_pAuftraege->Auftrag(0).m_Positionen.FoundAt(m_strSteinnummer,index))
        {
        int jn = AfxMessageBox(Sprache(_T("Soll die aktuelle Steinnummer zum Zugang hinzugefügt werden?")),MB_YESNO);
        if(jn == IDYES)
            {
            if(!OnHinzuZugang())
                return;
            }
        }
    }
if(Einkauf())
    {
    if(!m_strSteinnummer.IsEmpty() && !m_pAuftraege->Auftrag(0).m_Positionen.FoundAt(m_strSteinnummer,index))
        {
        int jn = AfxMessageBox(Sprache(_T("Soll die aktuelle Steinnummer hinzugefügt werden?")),MB_YESNO);
        if(jn == IDYES)
            {
            if(!OnHinzuEinkauf())
                return;
            }
        }
    }
if(Inventur())
    {
    if(!OnHinzuInventur())
        return;
    }

CDialog::OnOK();
}
//------------------------------------------------------------------------------------------
BOOL CPlattenZugang::Inventur()
{
if(m_nModus == ID_INVENTUR)
    return TRUE;
return FALSE;
}
//------------------------------------------------------------------------------------------
BOOL CPlattenZugang::Zugang()
{
if(m_nModus == ID_ZUGANG)
    return TRUE;
return FALSE;
}
//------------------------------------------------------------------------------------------
BOOL CPlattenZugang::Einkauf()
{
if(m_nModus == ID_BESTELLUNGENEINGANG)
    return TRUE;
return FALSE;
}
//------------------------------------------------------------------------------------------
void CPlattenZugang::OnSetfocusEditBestellnr() 
{
m_curFocus = BESTELLNR;
}
//-----------------------------------------------------------------------------
void CPlattenZugang::OnKillfocusEditBestellnr() 
{
m_curFocus = 0;
}
//-----------------------------------------------------------------------------
void CPlattenZugang::OnSetfocusEditBestellpos() 
{
m_curFocus = BESTELLPOS;
}
//-----------------------------------------------------------------------------
// Aktuellen Satz aus Bestellungen holen
void CPlattenZugang::OnKillfocusEditBestellpos() 
{
m_curFocus = 0;
CString str;
GetDlgItemText(IDC_EDIT_BESTELLPOS,str);
str.TrimLeft();str.TrimRight();
SSatz s(g_baseSteinSatz);
if(str.Compare(s.m_BestellPos))
    {
    BOOL ok = FALSE;
    for(int i = 0; i < m_pBestellungen->Anzahl(); i++)
        {
        SSatz ss(m_pBestellungen->SteinSatz(i));
        if(!ss.m_BestellNr.Compare(m_strBestellNr) && !ss.m_BestellPos.Compare(str))
            {
            g_baseSteinSatz = m_pBestellungen->SteinSatz(i);
            ok = TRUE;
            break;
            }
        }
    if(ok)
        StartEinkauf();
    else
        AfxMessageBox(Sprache(_T("Bestellposition ungültig!")));
    }
}
//-----------------------------------------------------------------------------
void CPlattenZugang::OnSetfocusEditSteinnr() 
{
m_curFocus = NUMMER;
}
//-----------------------------------------------------------------------------
void CPlattenZugang::OnKillfocusEditSteinnr() 
{
m_curFocus = 0;
}
//------------------------------------------------------------------------------------------
void CPlattenZugang::OnEnSetfocusEditSteinnrbis()
{
	m_curFocus = NUMMERBIS;
}
//------------------------------------------------------------------------------------------
void CPlattenZugang::OnEnKillfocusEditSteinnrbis()
{
	m_curFocus = 0;
}
//-----------------------------------------------------------------------------
void CPlattenZugang::OnSetfocusEditLieferschein() 
{
m_curFocus = LIEFERSCHEIN;
}
//-----------------------------------------------------------------------------
void CPlattenZugang::OnKillfocusEditLieferschein() 
{
m_curFocus = 0;
}
//-----------------------------------------------------------------------------
void CPlattenZugang::OnSetfocusComboLager() 
{
m_curFocus = LAGERORT;
}
//-----------------------------------------------------------------------------
void CPlattenZugang::OnKillfocusComboLager() 
{
m_curFocus = 0;
}
//-----------------------------------------------------------------------------
BOOL CPlattenZugang::CheckDatum(CString& strDatum,CString& strResult)
{
// das Datum kann auch leer bleiben
if (strDatum.IsEmpty())
	{
	strResult.Empty();
	return TRUE;
	}

CString strDay;
CString strMonth;
CString strYear;
CString str(strDatum);
int ix = str.Find(_T('.'));
if(ix > 0)
    strDay = str.Left(ix);
else
    return FALSE;
str = str.Mid(ix+1);
ix = str.Find(_T('.'));
if(ix > 0)
    strMonth = str.Left(ix);
else
    return FALSE;
strYear = str.Mid(ix+1);
int day = _ttoi(strDay);
if((day < 1) || (day > 31)) return FALSE;
int month = _ttoi(strMonth);
if((month < 1) || (month > 12)) return FALSE;
int year = _ttoi(strYear);
if(year < 1) return FALSE;
if(year < 100) year += 2000;
if(year > 9999) return FALSE;
strResult.Format(_T("%02d%02d%02d"),day,month,year);
strDatum.Format(_T("%02d.%02d.%02d"),day,month,year);
return TRUE;
}
//-----------------------------------------------------------------------------
void CPlattenZugang::OnSelchangeComboLager() 
{
SSatz s(g_baseSteinSatz);
s.m_Lager = m_tabLagerOrte.GetAt(m_ctrlComboLager.GetCurSel()).m_key;
g_baseSteinSatz.Set(s);
	
bGeaendertLager = TRUE;
}
//-----------------------------------------------------------------------------
void CPlattenZugang::OnEnKillfocusEditLaenge()
{
ValueExeed400(m_ctrlLaenge);
}
//-----------------------------------------------------------------------------
void CPlattenZugang::OnEnKillfocusEditBreite()
{
ValueExeed400(m_ctrlBreite);
}
//-----------------------------------------------------------------------------
void CPlattenZugang::OnEnKillfocusEditFehllaenge()
{
ValueExeed400(m_ctrlFehllaenge);
}
//-----------------------------------------------------------------------------
void CPlattenZugang::OnEnKillfocusEditFehlbreite()
{
ValueExeed400(m_ctrlFehlbreite);
}
//-----------------------------------------------------------------------------
void CPlattenZugang::OnEnChangeEditSteinnr()
{
	//wenn die Steinnr geändert wird, muss in den vorab-Daten geprüft werden, ob es Daten gibt
	if (m_nModus == ID_ZUGANG)
	{
		CString str;
		m_ctrlSteinnummer.GetWindowText(str);
		int ix_vorab;
		if (!str.IsEmpty() && m_Vorabdaten.FoundAt(str, ix_vorab))
		{
			int ix_auftrag;
			m_pAuftraege->Auftrag(0).m_Positionen.FoundAt(str, ix_auftrag);
			if (ix_auftrag < 0)
			{
				VorabDatenUebernehmen(str);
				m_ctrlButtonInfoVorab.ShowWindow(TRUE);	
				m_ctrlSteinnummer.EnableWindow (FALSE);
				if (g_Optionen.ZugangSteinnrVonBisEnabled () )
					m_ctrlSteinnummerBis.SetFocus();
				else
					m_ctrlComboLager.SetFocus();
			}
		}
		else
		{
			m_ctrlButtonInfoVorab.ShowWindow(FALSE);
			// sind keine Vorab-Daten da, dann darf auch der Artikel aus dem letzten Satz nicht verwendet, da das ja sonst zu falschen Buchungen kommen würde
			SSatz s(g_baseSteinSatz);
			if (!s.m_Artikel.IsEmpty())
			{
				m_ctrlStaticArtikelgruppe.SetWindowText( s.m_ArtikelGrBez );
				s.m_Artikel = _T("");
				s.m_ArtNr = _T("");
				g_baseSteinSatz.Set(s);
			}
		}
	}
}

//-------------------------------------------------------------------------------------
void CPlattenZugang::OnEnChangeEditSteinnrbis()
{
	SperrenEntsperrenFelderBeiBisSteinnr();
}

//-----------------------------------------------------------------------------
void CPlattenZugang::OnBnClickedButtonInfovorabdaten()
{
	int uebernehmen = 0;
	CString nummer;
	m_ctrlSteinnummer.GetWindowText(nummer);

	CBloeckeVorabInfo info(this);
	info.m_pSaetze = &m_Vorabdaten;
	info.m_pBlocknr = &nummer;
	info.m_pUebernehmen = &uebernehmen;
	
	m_pScanner->setEnableScanner(FALSE);
	info.DoModal();
	m_pScanner->setEnableScanner(TRUE);

	if (uebernehmen == 1)
	{
		VorabDatenUebernehmen(nummer);
	}
}
//------------------------------------------------------------------------------------------
void CPlattenZugang::VorabDatenUebernehmen(const CString& nummer)
{

	int index;
	m_Vorabdaten.FoundAt(nummer,index);
	if (index >= 0)
	{
		// keine Ahnung, was dieser Befehl soll, aber fehlt er, wird die letzte manuell erfasste Ziffer der Steinnr wieder entfernt!! 
		// (Vermutlich kommt das daher, weil in SetComboMe1() der Befehl mit dem Parameter FALSE aufgerufen wird?!?!)
		UpdateData(TRUE);

		SSatz s(m_Vorabdaten.arr[index]);
		m_strBestellNr = s.m_BestellNr;
		m_strBestellPos = s.m_BestellPos;
		if (!s.m_Artikel.IsEmpty())
			m_strArtikelGruppe = s.m_Artikel;
		else
			m_strArtikelGruppe = s.m_ArtikelGrBez;
		m_strMaterialArt = s.m_Material;
		m_strOberflaeche = s.m_Oberflaeche;
		//m_strLagerOrt = m_tabLagerOrte.GetItemByKey(s.m_Lager).m_bez;
		SetComboLager(s.m_Lager);
		m_strLieferant = m_tabLieferanten.GetItemByKey(s.m_Lieferant).m_bez;		
		m_strMenge1 = s.m_Menge1;
		m_strME1 = s.m_ME1;
		m_strLaenge = s.m_Laenge;
		m_strBreite = s.m_Breite;
		m_strDicke = s.m_Dicke;	
		m_strFehllaenge = s.m_FehlLaenge;
		m_strFehlbreite = s.m_FehlBreite;
		//m_strFehlnummer = s.m_FehlNummer;
		SetComboFehler(s.m_FehlNummer);
		m_strHinweis = s.m_Hinweis;
		m_strPreis = s.m_Preis;
		m_strEditLieferschein = s.m_LieferscheinNummer ;
		if (!s.m_LieferscheinDatum.IsEmpty() &&s.m_LieferscheinDatum.Find(_T("."),0)< 0)
			m_strEditDatum = s.m_LieferscheinDatum.Left(2) + _T(".") + s.m_LieferscheinDatum.Mid(2,2) + _T(".") + s.m_LieferscheinDatum.Right(4);
		else
			m_strEditDatum = s.m_LieferscheinDatum;
		

		SSatz ss;
		ss.m_BestellNr = s.m_BestellNr;
		ss.m_BestellPos = s.m_BestellPos;
		ss.m_Artikel = s.m_Artikel;
		ss.m_ArtNr = s.m_ArtNr;
		ss.m_ArtikelGr = s.m_ArtikelGr;
		ss.m_ArtikelGrBez = s.m_ArtikelGrBez;
		ss.m_MatGr = s.m_MatGr;
		ss.m_MatNr = s.m_MatNr;
		ss.m_Material = s.m_Material;
		ss.m_OberNr = s.m_OberNr;
		ss.m_Oberflaeche = s.m_Oberflaeche;
		ss.m_Lager = s.m_Lager;
		ss.m_Lieferant = s.m_Lieferant;
		ss.m_Menge1 = s.m_Menge1;
		ss.m_ME1 = s.m_ME1;
		ss.m_Laenge = s.m_Laenge;
		ss.m_Breite = s.m_Breite;
		ss.m_Dicke = s.m_Dicke;
		ss.m_FehlLaenge = s.m_FehlLaenge;
		ss.m_FehlBreite = s.m_FehlBreite;
		ss.m_FehlNummer = s.m_FehlNummer;
		ss.m_Hinweis = s.m_Hinweis;
		ss.m_Preis = s.m_Preis;
		ss.m_TextFeld = s.m_TextFeld;
		ss.m_LieferscheinNummer = s.m_LieferscheinNummer; 
		ss.m_LieferscheinDatum = s.m_LieferscheinDatum ;

		g_baseSteinSatz.Set(ss);    // alles andere gelöscht

		SetComboME1(s.m_ME1);

		CString temp;
		m_ctrlSteinnummer.GetWindowText(temp);
		temp = temp;
			
	}

}

//------------------------------------------------------------------------------------------
void CPlattenZugang::OnEnKillfocusEditHinweis()
{
	// Wenn das Feld verlassen wird, werden alle Semikolons im Text in # umgewandelt
	CString str;
	m_ctrlEditHinweis.GetWindowText(str);
	if (str.Find(_T(";"), 0)>= 0)
	{
		str.Replace(_T(";"), _T("#"));
		m_ctrlEditHinweis.SetWindowText(str);
	}
}

//------------------------------------------------------------------------------------------
void CPlattenZugang::OnEnChangeEditLagerort()
{
	CString str;
	m_ctrlEditLagerort.GetWindowText(str);
	int ix_Lager;
	ix_Lager = m_tabLagerOrte.GetIndexByKey (str);
	if (ix_Lager >= 0)
	{
		m_ctrlComboLager.SetCurSel(ix_Lager);
		OnSelchangeComboLager();
		m_ctrlEditLagerort.SetWindowText(_T(""));
		PlaySoundAdd();
	}
}




//-------------------------------------------------------------------------------------
void CPlattenZugang::SperrenEntsperrenFelderBeiBisSteinnr()
{
	CString str;
	m_ctrlSteinnummerBis.GetWindowText(str);
	if (!str.IsEmpty())
		{
		m_ctrlEditLieferschein.EnableWindow(FALSE);
		m_ctrlEditDatum.EnableWindow(FALSE);
		m_ctrlMenge1.EnableWindow(FALSE);
		m_comboME1.EnableWindow(FALSE);
		m_ctrlLaenge.EnableWindow(FALSE);
		m_ctrlBreite.EnableWindow(FALSE);
		m_ctrlDicke.EnableWindow(FALSE);
		m_ctrlFehlbreite.EnableWindow(FALSE);
		m_ctrlFehllaenge.EnableWindow(FALSE);
		m_ctrlComboFehler.EnableWindow(FALSE);
		m_ctrlEditHinweis.EnableWindow(FALSE);
		}
	else
		{
		m_ctrlEditLieferschein.EnableWindow(TRUE);
		m_ctrlEditDatum.EnableWindow(TRUE);
		m_ctrlMenge1.EnableWindow(TRUE);
		m_comboME1.EnableWindow(TRUE);
		m_ctrlLaenge.EnableWindow(TRUE);
		m_ctrlBreite.EnableWindow(TRUE);
		m_ctrlDicke.EnableWindow(TRUE);
		m_ctrlFehlbreite.EnableWindow(TRUE);
		m_ctrlFehllaenge.EnableWindow(TRUE);
		m_ctrlComboFehler.EnableWindow(TRUE);
		m_ctrlEditHinweis.EnableWindow(TRUE);
		}
}

//------------------------------------------------------------------------------------------

