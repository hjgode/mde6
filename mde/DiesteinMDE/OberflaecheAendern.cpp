// OberflaecheAendern1.cpp : implementation file
//

#include "stdafx.h"
#include "OberflaecheAendern.h"
#include "OberflaecheBuchungen.h"

/////////////////////////////////////////////////////////////////////////////
// COberflaecheAendern dialog


COberflaecheAendern::COberflaecheAendern(CWnd* pParent /*=NULL*/)
	: CDialog(COberflaecheAendern::IDD, pParent)
{
m_lastOberflIx = 0;
m_lastMatGr = _T("");
m_zurueckEnable = FALSE;
}


void COberflaecheAendern::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_STEINNUMMER, m_ctrlStaticSteinnummer);
	DDX_Control(pDX, IDC_STATIC_OBERFL_NEU, m_ctrlStaticOberflaecheNeu);
	DDX_Control(pDX, IDC_STATIC_OBERFL_ALT, m_ctrlStaticOberflaecheAlt);
	DDX_Control(pDX, IDC_STATIC_MENGE, m_ctrlStaticMenge);
	DDX_Control(pDX, IDC_STATIC_MATERIAL, m_ctrlStaticMaterial);
	DDX_Control(pDX, IDC_STATIC_DICKE, m_ctrlStaticDicke);
	DDX_Control(pDX, IDC_STATIC_ARTIKEL, m_ctrlStaticArtikel);
	DDX_Control(pDX, IDC_BUTTON_BUCHUNGEN, m_ctrlButtonBuchungen);
	DDX_Control(pDX, IDC_STATIC_STEINSAETZE, m_ctrlStaticSteinsaetze);
	DDX_Control(pDX, IDC_STATIC_DICKE_TEXT, m_ctrlStaticDickeText);
	DDX_Control(pDX, IDC_STATIC_ME2, m_ctrlStaticME2);
	DDX_Control(pDX, IDC_STATIC_ME1, m_ctrlStaticME1);
	DDX_Control(pDX, IDC_STATIC_MATERIAL_TEXT, m_ctrlStaticMaterialText);
	DDX_Control(pDX, IDC_STATIC_ARTIKEL_TEXT, m_ctrlStaticArtikelText);
	DDX_Control(pDX, IDC_BUTTON_AUTO, m_ctrlButtonAuto);
	DDX_Control(pDX, IDC_BUTTON_UNDO, m_ctrlButtonZurueck);
	DDX_Control(pDX, IDC_EDIT_OBERFL_ALT, m_ctrlEditOberflAlt);
	DDX_Control(pDX, IDC_COMBO_OBERFL_NEU, m_ctrlComboOberflNeu);
	DDX_Control(pDX, IDC_COMBO_STEINNUMMERN, m_ctrlComboSteinnummern);
	DDX_Control(pDX, IDC_EDIT_FEHLER_ALT, m_ctrlEditFehlerAlt);
	DDX_Control(pDX, IDC_COMBO_FEHLER_NEU, m_ctrlComboFehlerNeu);
	DDX_Control(pDX, IDC_STATIC_OBERFLAECHE, m_ctrlStaticOberflaeche);
	DDX_Control(pDX, IDC_STATIC_FEHLER, m_ctrlStaticFehler);
	DDX_Control(pDX, IDC_STATIC_MASSE3, m_ctrlStaticMasse);
	DDX_Control(pDX, IDC_STATIC_FEHLECKE, m_ctrlStaticFehlecke);
	DDX_Control(pDX, IDC_STATIC_MASSE_ALT, m_ctrlStaticMasseAlt);
	DDX_Control(pDX, IDC_STATIC_MASSE_NEU, m_ctrlStaticMasseNeu);
	DDX_Control(pDX, IDC_EDIT_LAENGE_ALT, m_ctrlEditLaengeAlt);
	DDX_Control(pDX, IDC_EDIT_BREITE_ALT, m_ctrlEditBreiteAlt);
	DDX_Control(pDX, IDC_EDIT_FEHLLAENGE_ALT, m_ctrlEditFehlLaengeAlt);
	DDX_Control(pDX, IDC_EDIT_FEHLBREITE_ALT, m_ctrlEditFehlBreiteAlt);
	DDX_Control(pDX, IDC_EDIT_LAENGE_NEU2, m_ctrlEditLaengeNeu);
	DDX_Control(pDX, IDC_EDIT_BREITE_NEU2, m_ctrlEditBreiteNeu);
	DDX_Control(pDX, IDC_EDIT_FEHLLAENGE_NEU2, m_ctrlEditFehlLaengeNeu);
	DDX_Control(pDX, IDC_EDIT_FEHLBREITE_NEU2, m_ctrlEditFehlBreiteNeu);
	DDX_Control(pDX, IDC_STATIC_BISSTEINNUMMER, m_ctrlStatic_BisSteinnummer);
	DDX_Control(pDX, IDC_COMBO_BISSTEINNUMMERN, m_ctrlComboBisSteinnummer);
}


BEGIN_MESSAGE_MAP(COberflaecheAendern, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_STEINNUMMERN, OnSelchangeComboSteinnummern)
	ON_BN_CLICKED(IDC_BUTTON_BUCHUNGEN, OnButtonBuchungen)
	ON_CBN_EDITCHANGE(IDC_COMBO_STEINNUMMERN, OnEditchangeComboSteinnummern)
	ON_CBN_SELENDOK(IDC_COMBO_OBERFL_NEU, OnSelendokComboOberflNeu)
	ON_CBN_CLOSEUP(IDC_COMBO_OBERFL_NEU, OnCloseupComboOberflNeu)
	ON_BN_CLICKED(IDC_BUTTON_UNDO, OnButtonUndo)
	ON_BN_CLICKED(IDC_BUTTON_AUTO, OnButtonAuto)
    ON_CBN_SELENDOK(IDC_COMBO_FEHLER_NEU, &COberflaecheAendern::OnCbnSelendokComboFehlerNeu)
	ON_EN_KILLFOCUS(IDC_EDIT_LAENGE_NEU2, &COberflaecheAendern::OnEnKillfocusEditLaengeNeu2)
	ON_EN_KILLFOCUS(IDC_EDIT_BREITE_NEU2, &COberflaecheAendern::OnEnKillfocusEditBreiteNeu2)
	ON_EN_KILLFOCUS(IDC_EDIT_FEHLLAENGE_NEU2, &COberflaecheAendern::OnEnKillfocusEditFehllaengeNeu2)
	ON_EN_KILLFOCUS(IDC_EDIT_FEHLBREITE_NEU2, &COberflaecheAendern::OnEnKillfocusEditFehlbreiteNeu2)
	ON_CBN_SELCHANGE(IDC_COMBO_BISSTEINNUMMERN, &COberflaecheAendern::OnCbnSelchangeComboBissteinnummern)
	ON_CBN_EDITCHANGE(IDC_COMBO_BISSTEINNUMMERN, &COberflaecheAendern::OnCbnEditchangeComboBissteinnummern)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COberflaecheAendern message handlers
//---------------------------------------------------------------------------------------
BOOL COberflaecheAendern::OnInitDialog()
{
CDialog::OnInitDialog();

CenterWindow(GetDesktopWindow());	// center to the hpc screen

TranslateStatic(m_ctrlStaticArtikel);
TranslateStatic(m_ctrlStaticDicke);
TranslateStatic(m_ctrlStaticMaterial);
TranslateStatic(m_ctrlStaticMenge);
TranslateStatic(m_ctrlStaticOberflaecheAlt);
TranslateStatic(m_ctrlStaticOberflaecheNeu);
TranslateStatic(m_ctrlStaticSteinnummer);
TranslateStatic(m_ctrlStatic_BisSteinnummer);
TranslateStatic(m_ctrlStaticSteinsaetze);
TranslateButton(m_ctrlButtonAuto);
TranslateButton(m_ctrlButtonBuchungen);
TranslateButton(m_ctrlButtonZurueck);

DisableZurueck();
DisableAutoaus();

m_tabAlleOberflaechen.Read();
m_tabFehlerbezeichnung.Read();
C2String s2;
m_tabFehlerbezeichnung.InsertAt(0,s2);  // 1. Eintrag Leerauswahl

CString str;
str.Format(_T("%d %s"),m_pSteinSaetze->Anzahl(),Sprache(_T("Steinsätze")));
m_ctrlStaticSteinsaetze.SetWindowText(str);

int i;
for(i = 0; i < m_pSteinSaetze->Anzahl(); i++)
    {
    m_ctrlComboSteinnummern.AddString(m_pSteinSaetze->SteinSatz(i).Nummer());
	m_ctrlComboBisSteinnummer.AddString(m_pSteinSaetze->SteinSatz(i).Nummer());
    }

for(i = 0; i < m_tabFehlerbezeichnung.GetCount(); i++)
    {
    m_ctrlComboFehlerNeu.AddString(m_tabFehlerbezeichnung.GetAt(i).m_bez);
    }

// die erste Platte soll NICHT mehr automatisch ausgewählt werden ch 06.03.2013
AnzeigePlattenDaten(-1);
//if(m_pSteinSaetze->Anzahl())
//    AnzeigePlattenDaten(0);

m_ctrlComboSteinnummern.SetFocus();

return TRUE;  // return TRUE  unless you set the focus to a control
}
//------------------------------------------------------------------------------
void COberflaecheAendern::AnzeigePlattenDaten(int index)
{
CSteinSatz satz;    // Alle Felder leer

if((index >= 0) && (index < m_pSteinSaetze->Anzahl()))
    {
    satz = m_pSteinSaetze->arr[index];
    }
SSatz ss(satz);
m_ctrlComboSteinnummern.SetWindowText(ss.m_Nummer);

SetTexte(ss);
SetComboOberflNeu(ss.m_MatGr);
SetComboFehlerNeu(_T(""));
SetMasseNeu(_T(""), _T(""));
SetFehleckeNeu(_T(""), _T(""));
m_ctrlComboBisSteinnummer.SetWindowText(_T(""));

}
//------------------------------------------------------------------------------
void COberflaecheAendern::SetTexte(const SSatz& ss)
{

m_ctrlEditLaengeAlt.SetWindowText(ss.m_Laenge);
m_ctrlStaticDickeText.SetWindowText(ss.m_Dicke);
m_ctrlEditBreiteAlt.SetWindowText(ss.m_Breite);

m_ctrlEditFehlLaengeAlt.SetWindowText(ss.m_FehlLaenge);
m_ctrlEditFehlBreiteAlt.SetWindowText(ss.m_FehlBreite);

m_ctrlStaticME1.SetWindowText(ss.m_Menge1 + _T(" ") + ss.m_ME1);

if(CSteinSatz::StringToDouble(ss.m_Menge2) != 0.)
    m_ctrlStaticME2.SetWindowText(ss.m_Menge2 + _T(" ") + ss.m_ME2);
else
    m_ctrlStaticME2.SetWindowText(_T(""));

m_ctrlStaticArtikelText.SetWindowText(ss.m_Artikel);
m_ctrlStaticMaterialText.SetWindowText(ss.m_Material);

CString str;
str.Format(_T("%s %s"),ss.m_OberNr,ss.m_Oberflaeche);
m_ctrlEditOberflAlt.SetWindowText(str);
if (ss.m_FehlNummer.IsEmpty() || ss.m_FehlNummer == _T("0"))
	m_ctrlEditFehlerAlt.SetWindowText(_T(""));
else
	m_ctrlEditFehlerAlt.SetWindowText(m_tabFehlerbezeichnung.GetItemByKey(ss.m_FehlNummer).m_bez);

DisableZurueck();
}
//---------------------------------------------------------------------------------------
void COberflaecheAendern::SetComboOberflNeu(const CString& matGr)
{
m_tabGruppeOberflaechen.SetGruppe(m_tabAlleOberflaechen,matGr);   // Oberfl-Tabelle nach MatGr erstellen
if(m_tabGruppeOberflaechen.GetSize() == 0)
    m_ctrlComboOberflNeu.ResetContent();
//AlertString(m_tabGruppeOberflaechen.GruppenKey(0)+matGr);
CString str;
if(    !m_lastMatGr.IsEmpty()
    && (m_lastMatGr.CompareNoCase(matGr) == 0)  // MatGr gleich, letzte Oberfläche an anfang
    && (m_lastOberflIx >= 0) 
    && (m_lastOberflIx < m_tabGruppeOberflaechen.GetSize()))
    {
    m_tabGruppeOberflaechen.m_curSelected = m_lastOberflIx;
    m_tabGruppeOberflaechen.SetComboKey2AndBez(m_ctrlComboOberflNeu,str);
 //   m_ctrlComboOberflNeu.SetCurSel(m_lastOberflIx);
    }
else
    {
    m_tabGruppeOberflaechen.m_curSelected = 0;
    m_tabGruppeOberflaechen.SetComboKey2AndBez(m_ctrlComboOberflNeu,str);
    m_ctrlComboOberflNeu.SetWindowText(_T("")); // leer anzeigen
    }
}
//---------------------------------------------------------------------------------------
void COberflaecheAendern::SetComboFehlerNeu(const CString& key)
{
int ix = m_tabFehlerbezeichnung.GetIndexByKey(key);
if((ix >= 0) && (ix < m_ctrlComboFehlerNeu.GetCount()))
    m_ctrlComboFehlerNeu.SetCurSel(ix);
}
//---------------------------------------------------------------------------------------
void COberflaecheAendern::SetMasseNeu(const CString &laenge, const CString &breite)
{
	m_ctrlEditLaengeNeu.SetWindowText(laenge);
	m_ctrlEditBreiteNeu.SetWindowText(breite);
}
//---------------------------------------------------------------------------------------
void COberflaecheAendern::SetFehleckeNeu(const CString &fehlLaenge, const CString &fehlBreite) 
{
	m_ctrlEditFehlLaengeNeu.SetWindowText(fehlLaenge);
	m_ctrlEditFehlBreiteNeu.SetWindowText(fehlBreite);
}
//---------------------------------------------------------------------------------------
// Oberflächen ändern message handlers

void COberflaecheAendern::OnSelchangeComboSteinnummern() 
{
int index = m_ctrlComboSteinnummern.GetCurSel();
AnzeigePlattenDaten(index);
}
//---------------------------------------------------------------------------------------
void COberflaecheAendern::OnSelendokComboOberflNeu() 
{
CString str;
m_ctrlComboSteinnummern.GetWindowText(str);

int ix;
if(!m_pSteinSaetze->FoundAt(str,ix))	
    {
    PlaySoundError();
    AfxMessageBox(Sprache(_T("Steinnummer ungültig!")),MB_OK|MB_ICONEXCLAMATION);
    m_ctrlComboSteinnummern.SetFocus();
    return;
    }

// Prüfen der bisSteinnummer  ch 14.02.2013
CString bisSteinnr;
m_ctrlComboBisSteinnummer.GetWindowText(bisSteinnr);
if (bisSteinnr.IsEmpty())
	bisSteinnr = str;	
int ix_bisSteinnr;
if(!m_pSteinSaetze->FoundAt(bisSteinnr,ix_bisSteinnr))	
    {
    PlaySoundError();
    AfxMessageBox(Sprache(_T("Bis Steinnummer ungültig!")),MB_OK|MB_ICONEXCLAMATION);
    m_ctrlComboBisSteinnummer.SetFocus();
    return;
    }

// Einrichten einer Schleife, so das alle Steinnr von/bis geändert werden ch 14.02.2013
BOOL bWeiter = TRUE;
int nVonNr = _wtoi(str);
int nBisNr = _wtoi(bisSteinnr);

if ( nBisNr < nVonNr)
			{
			PlaySoundError();
			AfxMessageBox(Sprache(_T("Bis Steinnummer nicht korrekt!")),MB_OK|MB_ICONEXCLAMATION);
			m_ctrlComboBisSteinnummer.SetFocus();
			return;
			}

if ((nBisNr - nVonNr) > 100)
	{
	PlaySoundError();
    AfxMessageBox(Sprache(_T("Max. 100 Platten änderbar!")),MB_OK|MB_ICONEXCLAMATION);
    m_ctrlComboBisSteinnummer.SetFocus();
    return;
	}

while( bWeiter )
{
	// mind. einmal wird die Änderung ja gemacht (für "Steinnr")
	AusfuehreOberflAenderung(ix);
	// Nächste Steinnr ermitteln
	if (nVonNr >= nBisNr)
		bWeiter = FALSE;
	else
	{
		BOOL bGefundenOderAbbruch = FALSE;
		while (!bGefundenOderAbbruch)
		{
			nVonNr = nVonNr + 1;
			ix = -1;
			if (nVonNr <= nBisNr)
			{
				//if(m_pSteinSaetze->FoundAt(CSteinSatz::DoubleToString(nVonNr),ix))	
				str.Format(_T("%d"),nVonNr);
				if(m_pSteinSaetze->FoundAt( str, ix))
					bGefundenOderAbbruch = TRUE;
			}
			else
				bGefundenOderAbbruch = TRUE;
		}
		if (ix == -1)
			bWeiter = FALSE;
	}			
}


// AusfuehreOberflAenderung(ix);
}
//---------------------------------------------------------------------------------------
void COberflaecheAendern::OnCbnSelendokComboFehlerNeu()
{
CString str;
m_ctrlComboSteinnummern.GetWindowText(str);

int ix;
if(!m_pSteinSaetze->FoundAt(str,ix))	
    {
    PlaySoundError();
    AfxMessageBox(Sprache(_T("Steinnummer ungültig!")),MB_OK|MB_ICONEXCLAMATION);
    m_ctrlComboSteinnummern.SetFocus();
    return;
    }

// Prüfen der bisSteinnummer  ch 14.02.2013
CString bisSteinnr;
m_ctrlComboBisSteinnummer.GetWindowText(bisSteinnr);
if (bisSteinnr.IsEmpty())
	bisSteinnr = str;	
int ix_bisSteinnr;
if(!m_pSteinSaetze->FoundAt(bisSteinnr,ix_bisSteinnr))	
    {
    PlaySoundError();
    AfxMessageBox(Sprache(_T("Bis Steinnummer ungültig!")),MB_OK|MB_ICONEXCLAMATION);
    m_ctrlComboBisSteinnummer.SetFocus();
    return;
    }

// Einrichten einer Schleife, so das alle Steinnr von/bis geändert werden ch 14.02.2013
BOOL bWeiter = TRUE;
int nVonNr = _wtoi(str);
int nBisNr = _wtoi(bisSteinnr);

if ( nBisNr < nVonNr)
			{
			PlaySoundError();
			AfxMessageBox(Sprache(_T("Bis Steinnummer nicht korrekt!")),MB_OK|MB_ICONEXCLAMATION);
			m_ctrlComboBisSteinnummer.SetFocus();
			return;
			}

if ((nBisNr - nVonNr) > 100)
	{
	PlaySoundError();
    AfxMessageBox(Sprache(_T("Max. 100 Platten änderbar!")),MB_OK|MB_ICONEXCLAMATION);
    m_ctrlComboBisSteinnummer.SetFocus();
    return;
	}
	
while( bWeiter )
{
	// mind. einmal wird die Änderung ja gemacht (für "Steinnr")
	AusfuehreFehlerAenderung(ix);
	// Nächste Steinnr ermitteln
	if (nVonNr >= nBisNr)
		bWeiter = FALSE;
	else
	{
		BOOL bGefundenOderAbbruch = FALSE;
		while (!bGefundenOderAbbruch)
		{
			nVonNr = nVonNr + 1;
			ix = -1;
			if (nVonNr <= nBisNr)
			{
				//if(m_pSteinSaetze->FoundAt(CSteinSatz::DoubleToString(nVonNr),ix))	
				str.Format(_T("%d"),nVonNr);
				if(m_pSteinSaetze->FoundAt( str, ix))
					bGefundenOderAbbruch = TRUE;
			}
			else
				bGefundenOderAbbruch = TRUE;
		}
		if (ix == -1)
			bWeiter = FALSE;
	}			
}


// AusfuehreFehlerAenderung(ix);
}
//---------------------------------------------------------------------------------------
void COberflaecheAendern::AusfuehreOberflAenderung(int ix)
{
CSteinSatz satz0(m_pSteinSaetze->arr[ix]);
SSatz ss(m_pSteinSaetze->arr[ix]);

m_tabGruppeOberflaechen.m_curSelected = m_ctrlComboOberflNeu.GetCurSel();
CString strOberflNeuKey(m_tabGruppeOberflaechen.GetAt(m_tabGruppeOberflaechen.m_curSelected).Key2());
CString strOberflNeuValue(m_tabGruppeOberflaechen.GetAt(m_tabGruppeOberflaechen.m_curSelected).m_bez);

if(strOberflNeuKey.IsEmpty()) //sollte eigentlich nicht sein
    return;

if(ss.m_OberNr.Compare(strOberflNeuKey)) // nur wenn sich ändert
    {
    CString strOberflAltKey = ss.m_OberNr;  // Alter key
    if(ss.m_OberNrAlt.IsEmpty())
        ss.m_OberNrAlt  = ss.m_OberNr;  // Im Lagerbestand ändern, nur beim ersten Mal im Original, dann ist Urzustand bekannt
                                        // Eigentlich nicht nötig, wird nicht mehr ausgewertet (nur zur progammtech. Kontrolle)
    ss.m_OberNr = strOberflNeuKey;
    ss.m_Oberflaeche = strOberflNeuValue;
    satz0.Set(ss);
    m_pSteinSaetze->arr[ix] = satz0;
    m_pSteinSaetze->m_modified = TRUE;

	// Auftrag suchen!! 
    CAuftrag& curAuftrag = m_pAuftraege->Auftrag(0);
	int ix_aufPos;
	curAuftrag.m_Positionen.FoundAt(ss.m_Nummer, ix_aufPos);

	if (ix_aufPos >= 0)
	{
		CSteinSatz& satzLast = curAuftrag.Position(ix_aufPos);
		SSatz ssl(satzLast);
		// wenn der satz vorhanden ist, dann immer in diesem Satz Ändern ch 05.11.2012
		/*if((!ssl.m_OberNr.Compare(ssl.m_OberNrAlt) || ssl.m_OberNrAlt.IsEmpty()))
		{
			ssl.m_OberNr = strOberflNeuKey;
			satzLast.Set(ssl);
            
			m_ctrlEditOberflAlt.SetWindowText(ss.m_OberNr + _T(" ") + ss.m_Oberflaeche);
			m_ctrlComboSteinnummern.SetFocus();
			PlaySoundAdd();
			return;
		}*/
		ssl.m_OberNr = strOberflNeuKey;
		
		// und hier noch einmal alle Änderbaren Werte in Alt kopieren, damit beim Löschen der Änderung nicht alle Daten weg sind. ch 14.02.2013
		if (ssl.m_FehlNummerAlt.IsEmpty())
			ssl.m_FehlNummerAlt = ssl.m_FehlNummer;
		if (ssl.m_LaengeAlt.IsEmpty())
			ssl.m_LaengeAlt = ssl.m_Laenge;
		if (ssl.m_BreiteAlt.IsEmpty())
			ssl.m_BreiteAlt = ssl.m_Breite;
		if (ssl.m_FehlLaengeAlt.IsEmpty())
			if (ssl.m_FehlLaenge.IsEmpty())
				ssl.m_FehlLaengeAlt = _T("0");
			else
				ssl.m_FehlLaengeAlt = ssl.m_FehlLaenge;
		if (ssl.m_FehlBreiteAlt.IsEmpty())
			if (ssl.m_FehlBreite.IsEmpty())
				ssl.m_FehlBreiteAlt = _T("0");
			else
				ssl.m_FehlBreiteAlt = ssl.m_FehlBreite;

		satzLast.Set(ssl);
        
		PlaySoundAdd();
		m_lastOberflIx = m_tabGruppeOberflaechen.m_curSelected; //Merken. wenn nächste Platte aus gleichem Material, Oberfläche an Anfang in Combobox
		m_lastMatGr = ssl.m_MatGr;

		m_ctrlEditOberflAlt.SetWindowText(ss.m_OberNr + _T(" ") + ss.m_Oberflaeche);
		m_ctrlComboSteinnummern.SetFocus();
		return;		
	}
	else
	{
		satz0.m_buchungsNummer = m_pAuftraege->NaechsteBuchungsnummer();    // im der Umbuchungsdatei eintragen
		satz0.SetDatumZeit();

		SSatz ssl(satz0);
		// und hier noch einmal alle Änderbaren Werte in Alt kopieren, damit beim Löschen der Änderung nicht alle Daten weg sind. ch 14.02.2013
		if (ssl.m_OberNrAlt.IsEmpty())
			ssl.m_OberNrAlt = ssl.m_OberNr;
		if (ssl.m_FehlNummerAlt.IsEmpty())
			if (ssl.m_FehlNummer.IsEmpty())
				ssl.m_FehlNummerAlt = _T("0");
			else
				ssl.m_FehlNummerAlt = ssl.m_FehlNummer;
		if (ssl.m_LaengeAlt.IsEmpty())
			ssl.m_LaengeAlt = ssl.m_Laenge;
		if (ssl.m_BreiteAlt.IsEmpty())
			ssl.m_BreiteAlt = ssl.m_Breite;
		if (ssl.m_FehlLaengeAlt.IsEmpty())
			if (ssl.m_FehlLaenge.IsEmpty())
				ssl.m_FehlLaengeAlt = _T("0");
			else
				ssl.m_FehlLaengeAlt = ssl.m_FehlLaenge;
		if (ssl.m_FehlBreiteAlt.IsEmpty())
			if (ssl.m_FehlBreite.IsEmpty())
				ssl.m_FehlBreiteAlt = _T("0");
			else
				ssl.m_FehlBreiteAlt = ssl.m_FehlBreite;
		satz0.Set(ssl);

		curAuftrag.AddPosition(satz0);    // es gibt nur einen Auftrag "OberflaecheAendern"
		PlaySoundAdd();

		m_lastOberflIx = m_tabGruppeOberflaechen.m_curSelected; //Merken. wenn nächste Platte aus gleichem Material, Oberfläche an Anfang in Combobox
		m_lastMatGr = ss.m_MatGr;

		m_ctrlEditOberflAlt.SetWindowText(ss.m_OberNr + _T(" ") + ss.m_Oberflaeche);

		EnableZurueck();
		EnableAutoaus();
	}
	
}
else
{
    m_lastOberflIx = m_tabGruppeOberflaechen.m_curSelected; //Merken. wenn nächste Platte aus gleichem Material, Oberfläche an Anfang in Combobox
    m_lastMatGr = ss.m_MatGr;
    EnableAutoaus();
}
m_ctrlComboSteinnummern.SetFocus();

//SetComboOberflNeu(lix);
}
//void COberflaecheAendern::AusfuehreOberflAenderung(int ix)			ALTE VERSION 
//{
//CSteinSatz satz0(m_pSteinSaetze->arr[ix]);
//SSatz ss(m_pSteinSaetze->arr[ix]);
//
//m_tabGruppeOberflaechen.m_curSelected = m_ctrlComboOberflNeu.GetCurSel();
//CString strOberflNeuKey(m_tabGruppeOberflaechen.GetAt(m_tabGruppeOberflaechen.m_curSelected).Key2());
//CString strOberflNeuValue(m_tabGruppeOberflaechen.GetAt(m_tabGruppeOberflaechen.m_curSelected).m_bez);
//
//if(strOberflNeuKey.IsEmpty()) //sollte eigentlich nicht sein
//    return;
//
//if(ss.m_OberNr.Compare(strOberflNeuKey)) // nur wenn sich ändert
//    {
//    CString strOberflAltKey = ss.m_OberNr;  // Alter key
//    if(ss.m_OberNrAlt.IsEmpty())
//        ss.m_OberNrAlt  = ss.m_OberNr;  // Im Lagerbestand ändern, nur beim ersten Mal im Original, dann ist Urzustand bekannt
//                                        // Eigentlich nicht nötig, wird nicht mehr ausgewertet (nur zur progammtech. Kontrolle)
//    ss.m_OberNr = strOberflNeuKey;
//    ss.m_Oberflaeche = strOberflNeuValue;
//    satz0.Set(ss);
//    m_pSteinSaetze->arr[ix] = satz0;
//    m_pSteinSaetze->m_modified = TRUE;
//
//    CAuftrag& curAuftrag = m_pAuftraege->Auftrag(0);
//	if(curAuftrag.m_Positionen.Anzahl()) // Wenn Buchungen vorhanden und aktuelle Nummer wie letzte gebuchte Nummer
//        {
//		CSteinSatz& satzLast = curAuftrag.m_Positionen.SteinSatz(curAuftrag.m_Positionen.Anzahl()-1);
//		SSatz ssl(satzLast);
//        // Wenn letzte Buchung gleiche Nummer und alte und neue Oberfläche gleich (Satz durch Fehler erstellt) 
//        if(!ssl.m_Nummer.Compare(ss.m_Nummer) && (!ssl.m_OberNr.Compare(ssl.m_OberNrAlt) || ssl.m_OberNrAlt.IsEmpty()))
//            {
//            ssl.m_OberNr = strOberflNeuKey;
//            satzLast.Set(ssl);
//            
//            m_ctrlEditOberflAlt.SetWindowText(ss.m_OberNr + _T(" ") + ss.m_Oberflaeche);
//            m_ctrlComboSteinnummern.SetFocus();
//            PlaySoundAdd();
//            return;
//            }
//        }
//
//    ss.m_OberNrAlt = strOberflAltKey;
//    ss.m_FehlNummerAlt = ss.m_FehlNummer;   // Nur beim Anlegen wird der Alt-Wert erstellt
//    satz0.Set(ss);
//    satz0.m_buchungsNummer = m_pAuftraege->NaechsteBuchungsnummer();    // im der Umbuchungsdatei eintragen
//    satz0.SetDatumZeit();
//
//    curAuftrag.AddPosition(satz0);    // es gibt nur einen Auftrag "OberflaecheAendern"
//    PlaySoundAdd();
//
//    m_lastOberflIx = m_tabGruppeOberflaechen.m_curSelected; //Merken. wenn nächste Platte aus gleichem Material, Oberfläche an Anfang in Combobox
//    m_lastMatGr = ss.m_MatGr;
//
//    m_ctrlEditOberflAlt.SetWindowText(ss.m_OberNr + _T(" ") + ss.m_Oberflaeche);
//
//    EnableZurueck();
//    EnableAutoaus();
//    }
//else
//    {
//    m_lastOberflIx = m_tabGruppeOberflaechen.m_curSelected; //Merken. wenn nächste Platte aus gleichem Material, Oberfläche an Anfang in Combobox
//    m_lastMatGr = ss.m_MatGr;
//    EnableAutoaus();
//    }
//m_ctrlComboSteinnummern.SetFocus();
//
////SetComboOberflNeu(lix);
//}
//---------------------------------------------------------------------------------------
void COberflaecheAendern::AusfuehreFehlerAenderung(int ix)
{
CSteinSatz satz0(m_pSteinSaetze->arr[ix]);
SSatz ss(m_pSteinSaetze->arr[ix]);

DisableZurueck();

// löschen erlaubt
int icur = m_ctrlComboFehlerNeu.GetCurSel();
if(icur < 0)
    {
    PlaySoundError();
    AfxMessageBox(_T("Intern::Fehleränderung!"),MB_OK|MB_ICONEXCLAMATION); // kann nicht sein
    return;
    }
CString strFehler = m_tabFehlerbezeichnung.GetAt(icur).m_key;

if(ss.m_FehlNummer.Compare(strFehler)) // nur wenn sich ändert
    {
    CString strFehlerAlt = ss.m_FehlNummer;  // Alter key
    if(ss.m_FehlNummerAlt.IsEmpty())
        ss.m_FehlNummerAlt  = ss.m_FehlNummer;  // Im Lagerbestand nur beim ersten Mal im Original, dann ist Urzustand bekannt
    ss.m_FehlNummer = strFehler;
    satz0.Set(ss);
    m_pSteinSaetze->arr[ix] = satz0;
    m_pSteinSaetze->m_modified = TRUE;


	CAuftrag& curAuftrag = m_pAuftraege->Auftrag(0);
	int ix_aufPos;
	curAuftrag.m_Positionen.FoundAt(ss.m_Nummer, ix_aufPos);

	if (ix_aufPos >= 0)
	{
		CSteinSatz& satzLast = curAuftrag.Position(ix_aufPos);
        SSatz ssl(satzLast);
		
		if (ssl.m_FehlNummerAlt.IsEmpty() )
			ssl.m_FehlNummerAlt = ssl.m_FehlNummer ;
		ssl.m_FehlNummer = strFehler;

		// und hier noch einmal alle Änderbaren Werte in Alt kopieren, damit beim Löschen der Änderung nicht alle Daten weg sind. ch 14.02.2013
		if (ssl.m_OberNrAlt.IsEmpty())
			ssl.m_OberNrAlt = ssl.m_OberNr;
		if (ssl.m_LaengeAlt.IsEmpty())
			ssl.m_LaengeAlt = ssl.m_Laenge;
		if (ssl.m_BreiteAlt.IsEmpty())
			ssl.m_BreiteAlt = ssl.m_Breite;
		if (ssl.m_FehlLaengeAlt.IsEmpty())
			if (ssl.m_FehlLaenge.IsEmpty())
				ssl.m_FehlLaengeAlt = _T("0");
			else
				ssl.m_FehlLaengeAlt = ssl.m_FehlLaenge;
		if (ssl.m_FehlBreiteAlt.IsEmpty())
			if (ssl.m_FehlBreite.IsEmpty())
				ssl.m_FehlBreiteAlt = _T("0");
			else
				ssl.m_FehlBreiteAlt = ssl.m_FehlBreite;

        satzLast.Set(ssl);
        m_ctrlEditFehlerAlt.SetWindowText(m_tabFehlerbezeichnung.GetItemByKey(ss.m_FehlNummer).m_bez);
        m_ctrlComboSteinnummern.SetFocus();
        PlaySoundAdd();
        return;
	}
	else
	{
		satz0.m_buchungsNummer = m_pAuftraege->NaechsteBuchungsnummer();    // im der Umbuchungsdatei eintragen
		satz0.SetDatumZeit();

		SSatz ssl(satz0);
		// und hier noch einmal alle Änderbaren Werte in Alt kopieren, damit beim Löschen der Änderung nicht alle Daten weg sind. ch 14.02.2013
		if (ssl.m_OberNrAlt.IsEmpty())
			ssl.m_OberNrAlt = ssl.m_OberNr;
		if (ssl.m_FehlNummerAlt.IsEmpty())
			ssl.m_FehlNummerAlt = ssl.m_FehlNummer;
		if (ssl.m_LaengeAlt.IsEmpty())
			ssl.m_LaengeAlt = ssl.m_Laenge;
		if (ssl.m_BreiteAlt.IsEmpty())
			ssl.m_BreiteAlt = ssl.m_Breite;
		if (ssl.m_FehlLaengeAlt.IsEmpty())
			if (ssl.m_FehlLaenge.IsEmpty())
				ssl.m_FehlLaengeAlt = _T("0");
			else
				ssl.m_FehlLaengeAlt = ssl.m_FehlLaenge;
		if (ssl.m_FehlBreiteAlt.IsEmpty())
			if (ssl.m_FehlBreite.IsEmpty())
				ssl.m_FehlBreiteAlt = _T("0");
			else
				ssl.m_FehlBreiteAlt = ssl.m_FehlBreite;
		satz0.Set(ssl);

		curAuftrag.AddPosition(satz0);    // es gibt nur einen Auftrag "OberflaecheAendern"
		PlaySoundAdd();

		m_ctrlEditFehlerAlt.SetWindowText(m_tabFehlerbezeichnung.GetItemByKey(ss.m_FehlNummer).m_bez);
	}
}

m_ctrlComboSteinnummern.SetFocus();
}
//void COberflaecheAendern::AusfuehreFehlerAenderung(int ix)
//{
//CSteinSatz satz0(m_pSteinSaetze->arr[ix]);
//SSatz ss(m_pSteinSaetze->arr[ix]);
//
//DisableZurueck();
//
//// löschen erlaubt
//int icur = m_ctrlComboFehlerNeu.GetCurSel();
//if(icur < 0)
//    {
//    PlaySoundError();
//    AfxMessageBox(_T("Intern::Fehleränderung!"),MB_OK|MB_ICONEXCLAMATION); // kann nicht sein
//    return;
//    }
//CString strFehler = m_tabFehlerbezeichnung.GetAt(icur).m_key;
//    
//// strFehler == FehlNummer
//CAuftrag& curAuftrag = m_pAuftraege->Auftrag(0);
//
//if(ss.m_FehlNummer.Compare(strFehler)) // nur wenn sich ändert
//    {
//    CString strFehlerAlt = ss.m_FehlNummer;  // Alter key
//    if(ss.m_FehlNummerAlt.IsEmpty())
//        ss.m_FehlNummerAlt  = ss.m_FehlNummer;  // Im Lagerbestand nur beim ersten Mal im Original, dann ist Urzustand bekannt
//    ss.m_FehlNummer = strFehler;
//    satz0.Set(ss);
//    m_pSteinSaetze->arr[ix] = satz0;
//    m_pSteinSaetze->m_modified = TRUE;
//
//    if(curAuftrag.m_Positionen.Anzahl()) // Wenn Buchungen vorhanden und aktuelle Nummer wie letzte gebuchte Nummer
//        {
//        CSteinSatz& satzLast = curAuftrag.m_Positionen.SteinSatz(curAuftrag.m_Positionen.Anzahl()-1);
//        SSatz ssl(satzLast);
//        if(!ssl.m_Nummer.Compare(ss.m_Nummer))  // Letzte Buchung gleicher Satz, Fehler in Buchung ändern 
//            {
//            ssl.m_FehlNummer = strFehler;
//            satzLast.Set(ssl);
//            
//            m_ctrlEditFehlerAlt.SetWindowText(m_tabFehlerbezeichnung.GetItemByKey(ss.m_FehlNummer).m_bez);
//            m_ctrlComboSteinnummern.SetFocus();
//            PlaySoundAdd();
//            return;
//            }        
//        }
//// Neuen Buchungssatz erstellen
//    //if(ss.m_OberNrAlt.IsEmpty())
//    //    ss.m_OberNrAlt = ss.m_Oberflaeche;
//    //satz0.Set(ss);  // hier immer noch mit dem ersten fehleralt
//    //m_pSteinSaetze->arr[ix] = satz0;
//
//    ss.m_FehlNummerAlt  = strFehlerAlt;  // Im Auftrag letzten Zustand eintragen (nur beim Anlegen des Satzes)
//    ss.m_OberNrAlt = ss.m_OberNr;        // Erst mal gleich, wenn über Fehler angelegt wird
//    satz0.Set(ss);
//    satz0.m_buchungsNummer = m_pAuftraege->NaechsteBuchungsnummer();    // im der Umbuchungsdatei eintragen
//    satz0.SetDatumZeit();
//    curAuftrag.AddPosition(satz0);    // es gibt nur einen Auftrag "OberflaecheAendern"
//    PlaySoundAdd();
//
//    m_ctrlEditFehlerAlt.SetWindowText(m_tabFehlerbezeichnung.GetItemByKey(ss.m_FehlNummer).m_bez);
//
//    }
//
//m_ctrlComboSteinnummern.SetFocus();
//}				Alte Version

//---------------------------------------------------------------------------------------
BOOL COberflaecheAendern::CheckNummer(const CString& barCode)
{
int index;
if(m_pSteinSaetze->FoundAt(barCode,index))
    {
    PlaySoundScan();
    AnzeigePlattenDaten(index);

    SSatz ss(m_pSteinSaetze->SteinSatzConst(index));
    if(ss.m_MatGr.CompareNoCase(m_lastMatGr) == 0)
        {
        CString str;
        m_ctrlComboOberflNeu.GetWindowText(str);
        if(!str.IsEmpty())
            AusfuehreOberflAenderung(index);
        }
    return TRUE;
    }
PlaySoundOther();
return FALSE;
}
//-----------------------------------------------------------------------------------
BOOL COberflaecheAendern::CheckOberflaeche(const CString& barCode)
{
	// erst mal den Steinsatz ermitteln (wegen der Materialgruppe !!!!! 
	CString str;
	m_ctrlComboSteinnummern.GetWindowText(str);

	int ix;
	if(!m_pSteinSaetze->FoundAt(str,ix))	
		{
		PlaySoundError();
		AfxMessageBox(Sprache(_T("Steinnummer ungültig!")),MB_OK|MB_ICONEXCLAMATION);
		m_ctrlComboSteinnummern.SetFocus();
		return FALSE;
		}	
	
	// der Steinsatz ist da, jetzt kann die Oberfläche geprüft werden!
	SSatz ss(m_pSteinSaetze->arr[ix]);

	int index = m_tabGruppeOberflaechen.GetIndexByKey(ss.m_MatGr, barCode);
	if(index >= 0)
	{
		PlaySoundScan();
		m_ctrlComboOberflNeu.SetCurSel(index);
		AusfuehreOberflAenderung(ix);
		return TRUE;
    }
PlaySoundOther();
return FALSE;
}
//-----------------------------------------------------------------------------
BOOL COberflaecheAendern::PreTranslateMessage(MSG* pMsg) 
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
	int currId = GetFocus()->GetDlgCtrlID();
	int currId_ComboBox = GetFocus()->GetParent()->GetDlgCtrlID();

	if (currId_ComboBox == m_ctrlComboSteinnummern.GetDlgCtrlID())
		{
		if(CheckNummer(barCode))
			return CDialog::PreTranslateMessage(pMsg);
		else
			{
			m_ctrlComboSteinnummern.SetWindowText(barCode);
			SSatz ss;
			SetTexte(ss);
			SetComboOberflNeu(_T(""));
			SetComboFehlerNeu(_T(""));
			SetMasseNeu(_T(""),_T(""));
			SetFehleckeNeu(_T(""),_T(""));
			m_ctrlComboBisSteinnummer.SetWindowText(_T(""));
			}
		}
	if (currId_ComboBox == m_ctrlComboBisSteinnummer.GetDlgCtrlID())
		{
		int index;
		if(m_pSteinSaetze->FoundAt(barCode,index))
			{
			PlaySoundScan();
			m_ctrlComboBisSteinnummer.SetWindowText(barCode);
			CheckBisSteinnummer(barCode);
			return CDialog::PreTranslateMessage(pMsg);
			}
		else
			{
			PlaySoundOther();
			m_ctrlComboBisSteinnummer.SetWindowText(_T(""));
			}
		}
	if (currId_ComboBox == m_ctrlComboOberflNeu.GetDlgCtrlID())
		{
		if(CheckOberflaeche(barCode))
			return CDialog::PreTranslateMessage(pMsg);
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
void COberflaecheAendern::OnButtonBuchungen() 
{

CString lastnr;
m_ctrlComboSteinnummern.GetWindowText(lastnr);

COberflaecheBuchungen dlg;
dlg.m_pAuftraege = m_pAuftraege;
dlg.m_pSteinSaetze = m_pSteinSaetze;

dlg.DoModal();

int index;
if(m_pSteinSaetze->FoundAt(lastnr,index))
    AnzeigePlattenDaten(index);

m_ctrlComboSteinnummern.SetFocus();
}
//-----------------------------------------------------------------------------
void COberflaecheAendern::OnEditchangeComboSteinnummern() 
{
DisableZurueck();

int ix;
CString nrstr;
m_ctrlComboSteinnummern.GetWindowText(nrstr);
if(m_pSteinSaetze->FoundAt(nrstr,ix))
    {
    SSatz ss(m_pSteinSaetze->SteinSatzConst(ix));
    SetTexte(ss);
    SetComboOberflNeu(ss.m_MatGr);
    SetComboFehlerNeu(_T(""));
	SetMasseNeu(_T(""),_T(""));
	SetFehleckeNeu(_T(""),_T(""));
	m_ctrlComboBisSteinnummer.SetWindowText(_T(""));
    }
else
    {
    SSatz ss;
    SetTexte(ss);
    SetComboOberflNeu(ss.m_MatGr);
    SetComboFehlerNeu(_T(""));
	SetMasseNeu(_T(""),_T(""));
	SetFehleckeNeu(_T(""),_T(""));
	m_ctrlComboBisSteinnummer.SetWindowText(_T(""));
    }

}
//-----------------------------------------------------------------------------
// Damit beim durchblättern nicht zugewiesen wird, damitm der Focus nicht auf Oberfl. stehen bleibt
void COberflaecheAendern::OnCloseupComboOberflNeu() 
{
m_ctrlComboSteinnummern.SetFocus();	
}
//-----------------------------------------------------------------------------
void COberflaecheAendern::OnButtonUndo() 
{
if(!m_zurueckEnable)
    return;
CAuftrag& auf = m_pAuftraege->Auftrag(0);

SSatz ss(auf.m_Positionen.SteinSatz(auf.m_Positionen.Anzahl()-1));    // Zu löschender Satz

auf.m_Positionen.RemoveAt(auf.m_Positionen.Anzahl()-1); // löschen

int ix;
if(m_pSteinSaetze->FoundAt(ss.m_Nummer,ix))
    {
    SSatz ssUr(m_pSteinSaetze->SteinSatzConst(ix));
	// Oberflächenänderung rückgängig machen
	if (!ss.m_OberNrAlt.IsEmpty() )
	{
		ssUr.m_OberNr = ss.m_OberNrAlt;
		int ixo = m_tabGruppeOberflaechen.GetIndexByKey(ssUr.m_MatGr,ssUr.m_OberNr);
		if(ixo >= 0)
			ssUr.m_Oberflaeche = m_tabGruppeOberflaechen.GetAt(ixo).m_bez;
		ssUr.m_OberNrAlt = _T("");
	}
	// Fehler zurücksetzen
	if (!ss.m_FehlNummerAlt.IsEmpty() )
	{
		ssUr.m_FehlNummer = ss.m_FehlNummerAlt;
		ssUr.m_FehlNummerAlt = _T("");
	}
	// Masse zurücksetzen
	if (!ss.m_LaengeAlt.IsEmpty() )
	{
		ssUr.m_Laenge = ss.m_LaengeAlt;
		ssUr.m_LaengeAlt = _T("");
	}
	if (!ss.m_BreiteAlt.IsEmpty() )
	{
		ssUr.m_Breite = ss.m_BreiteAlt;
		ssUr.m_BreiteAlt = _T("");
	}
	//Fehlecke zurücksetzten
	if (!ss.m_FehlLaengeAlt.IsEmpty() )
	{
		ssUr.m_FehlLaenge = ss.m_FehlLaengeAlt;
		ssUr.m_FehlLaengeAlt = _T("");
	}
	if (!ss.m_FehlBreiteAlt.IsEmpty() )
	{
		ssUr.m_FehlBreite = ss.m_FehlBreiteAlt;
		ssUr.m_FehlBreiteAlt = _T("");
	}
	
	m_pSteinSaetze->SteinSatz(ix).Set(ssUr);
    m_pSteinSaetze->m_modified = TRUE;
//    m_ctrlEditOberflAlt.SetWindowText(ssUr.m_OberNr + _T(" ") + ssUr.m_Oberflaeche);
    }

DisableZurueck();
AnzeigePlattenDaten(ix);

m_ctrlComboSteinnummern.SetFocus();
}
//-----------------------------------------------------------------------------
void COberflaecheAendern::EnableZurueck()
{
m_zurueckEnable = TRUE;
m_ctrlButtonZurueck.SetWindowText(_T("Zurück"));
m_ctrlButtonZurueck.ShowWindow(SW_SHOW);
}
//-----------------------------------------------------------------------------
void COberflaecheAendern::DisableZurueck()
{
m_zurueckEnable = FALSE;
m_ctrlButtonZurueck.SetWindowText(_T(""));
m_ctrlButtonZurueck.ShowWindow(SW_HIDE);
}
//-----------------------------------------------------------------------------
void COberflaecheAendern::OnButtonAuto() 
{
m_lastMatGr.Empty();

CString lastnr;
m_ctrlComboSteinnummern.GetWindowText(lastnr);

CSteinSatz satz;
int ix;
if(m_pSteinSaetze->FoundAt(lastnr,ix))
    satz = m_pSteinSaetze->SteinSatzConst(ix);

SSatz ss(satz);
SetComboOberflNeu(ss.m_MatGr);

DisableAutoaus();
m_ctrlComboSteinnummern.SetFocus();
}
//-----------------------------------------------------------------------------
void COberflaecheAendern::EnableAutoaus()
{
m_ctrlButtonAuto.SetWindowText(_T("Auto aus"));
m_ctrlButtonAuto.ShowWindow(SW_SHOW);
}
//-----------------------------------------------------------------------------
void COberflaecheAendern::DisableAutoaus()
{
m_ctrlButtonAuto.SetWindowText(_T(""));
m_ctrlButtonAuto.ShowWindow(SW_HIDE);
}
//-----------------------------------------------------------------------------
void COberflaecheAendern::OnEnKillfocusEditLaengeNeu2()
{
	CString str;
	m_ctrlComboSteinnummern.GetWindowText(str);

	int ix;
	if(!m_pSteinSaetze->FoundAt(str,ix))	
	{
		PlaySoundError();
		AfxMessageBox(Sprache(_T("Steinnummer ungültig!")),MB_OK|MB_ICONEXCLAMATION);
		m_ctrlComboSteinnummern.SetFocus();
		return;
    }

	AusfuehreMassAenderung(ix);
}
void COberflaecheAendern::OnEnKillfocusEditBreiteNeu2()
{
	CString str;
	m_ctrlComboSteinnummern.GetWindowText(str);

	int ix;
	if(!m_pSteinSaetze->FoundAt(str,ix))	
	{
		PlaySoundError();
		AfxMessageBox(Sprache(_T("Steinnummer ungültig!")),MB_OK|MB_ICONEXCLAMATION);
		m_ctrlComboSteinnummern.SetFocus();
		return;
    }

	AusfuehreMassAenderung(ix);
}

//-----------------------------------------------------------------------------
void COberflaecheAendern::AusfuehreMassAenderung(int ix)
{
CSteinSatz satz0(m_pSteinSaetze->arr[ix]);
SSatz ss(m_pSteinSaetze->arr[ix]);

DisableZurueck();

CString laengeNeu;
double numLaengeNeu;
CString breiteNeu;
double numBreiteNeu;

m_ctrlEditLaengeNeu.GetWindowText(laengeNeu);
numLaengeNeu = CSteinSatz::StringToDouble(laengeNeu);
m_ctrlEditBreiteNeu.GetWindowText(breiteNeu);
numBreiteNeu = CSteinSatz::StringToDouble(breiteNeu);

if (laengeNeu.IsEmpty() && breiteNeu.IsEmpty())
    return;
if (numLaengeNeu == 0 && numBreiteNeu == 0)
	return;

int nGeaendert = 0;
if (!laengeNeu.IsEmpty())
{
	if (ss.m_LaengeAlt.IsEmpty())
		ss.m_LaengeAlt = ss.m_Laenge ;
	ss.m_Laenge = laengeNeu;
	satz0.Set(ss);
    m_pSteinSaetze->arr[ix] = satz0;
    m_pSteinSaetze->m_modified = TRUE;
	nGeaendert = 1;
}
if (!breiteNeu.IsEmpty())
{
	if (ss.m_BreiteAlt.IsEmpty())
		ss.m_BreiteAlt = ss.m_Breite ;
	ss.m_Breite = breiteNeu;
	satz0.Set(ss);
    m_pSteinSaetze->arr[ix] = satz0;
    m_pSteinSaetze->m_modified = TRUE;
	nGeaendert = 2;
}

if (nGeaendert > 0)
{
	CAuftrag& curAuftrag = m_pAuftraege->Auftrag(0);
	int ix_aufPos;
	curAuftrag.m_Positionen.FoundAt(ss.m_Nummer, ix_aufPos);

	if (ix_aufPos >= 0)
	{
		CSteinSatz& satzLast = curAuftrag.Position(ix_aufPos);
        SSatz ssl(satzLast);
		if (nGeaendert == 1)
		{
			if (ssl.m_LaengeAlt.IsEmpty())
				ssl.m_LaengeAlt = ssl.m_Laenge ;
			ssl.m_Laenge = laengeNeu;
			m_ctrlEditLaengeAlt.SetWindowText(laengeNeu);
			m_ctrlEditLaengeNeu.SetWindowText(_T(""));
		}
		if (nGeaendert == 2)
		{
			if (ssl.m_BreiteAlt.IsEmpty())
				ssl.m_BreiteAlt = ssl.m_Breite ;
			ssl.m_Breite = breiteNeu;
			m_ctrlEditBreiteAlt.SetWindowText(breiteNeu);
			m_ctrlEditBreiteNeu.SetWindowText(_T(""));
		}
		// und hier noch einmal alle Änderbaren Werte in Alt kopieren, damit beim Löschen der Änderung nicht alle Daten weg sind. ch 14.02.2013
		if (ssl.m_OberNrAlt.IsEmpty())
			ssl.m_OberNrAlt = ssl.m_OberNr ;
		if (ssl.m_FehlNummerAlt.IsEmpty())
			if (ssl.m_FehlNummer.IsEmpty())
				ssl.m_FehlNummerAlt = _T("0");
			else
				ssl.m_FehlNummerAlt = ssl.m_FehlNummer;
		if (ssl.m_FehlLaengeAlt.IsEmpty())
			if (ssl.m_FehlLaenge.IsEmpty())
				ssl.m_FehlLaengeAlt = _T("0");
			else
				ssl.m_FehlLaengeAlt = ssl.m_FehlLaenge;
		if (ssl.m_FehlBreiteAlt.IsEmpty())
			if (ssl.m_FehlBreite.IsEmpty())
				ssl.m_FehlBreiteAlt = _T("0");
			else
				ssl.m_FehlBreiteAlt = ssl.m_FehlBreite;

		satzLast.Set(ssl);
		if (nGeaendert == 2)
			m_ctrlComboSteinnummern.SetFocus();
        PlaySoundAdd();
        return;
	}
	else
	{
		satz0.m_buchungsNummer = m_pAuftraege->NaechsteBuchungsnummer();    // im der Umbuchungsdatei eintragen
		satz0.SetDatumZeit();

		SSatz ssl(satz0);
		// und hier noch einmal alle Änderbaren Werte in Alt kopieren, damit beim Löschen der Änderung nicht alle Daten weg sind. ch 14.02.2013
		if (ssl.m_OberNrAlt.IsEmpty())
			ssl.m_OberNrAlt = ssl.m_OberNr;
		if (ssl.m_FehlNummerAlt.IsEmpty())
			if (ssl.m_FehlNummer.IsEmpty())
				ssl.m_FehlNummerAlt = _T("0");
			else
				ssl.m_FehlNummerAlt = ssl.m_FehlNummer;
		if (ssl.m_LaengeAlt.IsEmpty())
			ssl.m_LaengeAlt = ssl.m_Laenge;
		if (ssl.m_BreiteAlt.IsEmpty())
			ssl.m_BreiteAlt = ssl.m_Breite;
		if (ssl.m_FehlLaengeAlt.IsEmpty())
			if (ssl.m_FehlLaenge.IsEmpty())
				ssl.m_FehlLaengeAlt = _T("0");
			else
				ssl.m_FehlLaengeAlt = ssl.m_FehlLaenge;
		if (ssl.m_FehlBreiteAlt.IsEmpty())
			if (ssl.m_FehlBreite.IsEmpty())
				ssl.m_FehlBreiteAlt = _T("0");
			else
				ssl.m_FehlBreiteAlt = ssl.m_FehlBreite;
		satz0.Set(ssl);

		curAuftrag.AddPosition(satz0);    // es gibt nur einen Auftrag "OberflaecheAendern"
		PlaySoundAdd();
		if (nGeaendert = 1)
		{
			m_ctrlEditLaengeAlt.SetWindowText(laengeNeu);
			m_ctrlEditLaengeNeu.SetWindowText(_T(""));
		}
		if (nGeaendert = 2)
		{
			m_ctrlEditBreiteAlt.SetWindowText(breiteNeu);
			m_ctrlEditBreiteNeu.SetWindowText(_T(""));
		}
	}
}
if (nGeaendert == 0 || nGeaendert == 2)
	m_ctrlComboSteinnummern.SetFocus();
}
//-----------------------------------------------------------------------------
void COberflaecheAendern::OnEnKillfocusEditFehllaengeNeu2()
{
	CString str;
	m_ctrlComboSteinnummern.GetWindowText(str);

	int ix;
	if(!m_pSteinSaetze->FoundAt(str,ix))	
	{
		PlaySoundError();
		AfxMessageBox(Sprache(_T("Steinnummer ungültig!")),MB_OK|MB_ICONEXCLAMATION);
		m_ctrlComboSteinnummern.SetFocus();
		return;
    }

	AusfuehreFehleckeAenderung(ix);
}

void COberflaecheAendern::OnEnKillfocusEditFehlbreiteNeu2()
{
	CString str;
	m_ctrlComboSteinnummern.GetWindowText(str);

	int ix;
	if(!m_pSteinSaetze->FoundAt(str,ix))	
	{
		PlaySoundError();
		AfxMessageBox(Sprache(_T("Steinnummer ungültig!")),MB_OK|MB_ICONEXCLAMATION);
		m_ctrlComboSteinnummern.SetFocus();
		return;
    }

	AusfuehreFehleckeAenderung(ix);
}
//-----------------------------------------------------------------------------
void COberflaecheAendern::AusfuehreFehleckeAenderung(int ix)
{
CSteinSatz satz0(m_pSteinSaetze->arr[ix]);
SSatz ss(m_pSteinSaetze->arr[ix]);

DisableZurueck();

CString laengeNeu;
double numLaengeNeu;
CString breiteNeu;
double numBreiteNeu;

m_ctrlEditFehlLaengeNeu.GetWindowText(laengeNeu);
numLaengeNeu = CSteinSatz::StringToDouble(laengeNeu);
m_ctrlEditFehlBreiteNeu.GetWindowText(breiteNeu);
numBreiteNeu = CSteinSatz::StringToDouble(breiteNeu);

if (laengeNeu.IsEmpty() && breiteNeu.IsEmpty())
    return;
// ist eines der beiden Felder leer und das andere gefüllt, darf nichts passieren  ch 13.02.2013
if ( (laengeNeu.IsEmpty() && !breiteNeu.IsEmpty()) || (!laengeNeu.IsEmpty() && breiteNeu.IsEmpty()))
    return;


int nGeaendert = 0;
if (!laengeNeu.IsEmpty())
{
	if (ss.m_FehlLaengeAlt.IsEmpty())
		if (ss.m_FehlLaenge.IsEmpty())
			ss.m_FehlLaengeAlt = _T("0") ;
		else
			ss.m_FehlLaengeAlt = ss.m_FehlLaenge ;
	ss.m_FehlLaenge = laengeNeu;
	satz0.Set(ss);
    m_pSteinSaetze->arr[ix] = satz0;
    m_pSteinSaetze->m_modified = TRUE;
	nGeaendert = 1;
}
if (!breiteNeu.IsEmpty())
{
	if (ss.m_FehlBreiteAlt.IsEmpty())
		if(ss.m_FehlBreite.IsEmpty())
			ss.m_FehlBreiteAlt = _T("0");
		else
			ss.m_FehlBreiteAlt = ss.m_FehlBreite ;
	ss.m_FehlBreite = breiteNeu;
	satz0.Set(ss);
    m_pSteinSaetze->arr[ix] = satz0;
    m_pSteinSaetze->m_modified = TRUE;
	if (nGeaendert == 0)
		nGeaendert = 2;
	else
		nGeaendert = 3;			// wenn beide Felder geändert sind, dann auf 3 setzen. Eigentlich könnte man die Abfrage dann ganz wegmachen??!! ch 14.02.2013
}

if (nGeaendert > 0)
{
	CAuftrag& curAuftrag = m_pAuftraege->Auftrag(0);
	int ix_aufPos;
	curAuftrag.m_Positionen.FoundAt(ss.m_Nummer, ix_aufPos);

	if (ix_aufPos >= 0)
	{
		CSteinSatz& satzLast = curAuftrag.Position(ix_aufPos);
        SSatz ssl(satzLast);
		if (nGeaendert == 1 || nGeaendert == 3)
		{
			if (ssl.m_FehlLaengeAlt.IsEmpty())
				ssl.m_FehlLaengeAlt = ssl.m_FehlLaenge ;
			ssl.m_FehlLaenge = laengeNeu;
			m_ctrlEditFehlLaengeAlt.SetWindowText(laengeNeu);
			m_ctrlEditFehlLaengeNeu.SetWindowText(_T(""));
		}
		if (nGeaendert == 2 || nGeaendert == 3)
		{
			if (ssl.m_FehlBreiteAlt.IsEmpty())
				ssl.m_FehlBreiteAlt = ssl.m_FehlBreite ;
			ssl.m_FehlBreite = breiteNeu;
			m_ctrlEditFehlBreiteAlt.SetWindowText(breiteNeu);
			m_ctrlEditFehlBreiteNeu.SetWindowText(_T(""));
		}

		// und hier noch einmal alle Änderbaren Werte in Alt kopieren, damit beim Löschen der Änderung nicht alle Daten weg sind. ch 14.02.2013
		if (ssl.m_OberNrAlt.IsEmpty())
			ssl.m_OberNrAlt = ssl.m_OberNr;
		if (ssl.m_FehlNummerAlt.IsEmpty())
			if (ssl.m_FehlNummer.IsEmpty())
				ssl.m_FehlNummerAlt = _T("0");
			else
				ssl.m_FehlNummerAlt = ssl.m_FehlNummer;
		if (ssl.m_LaengeAlt.IsEmpty())
			ssl.m_LaengeAlt = ssl.m_Laenge;
		if (ssl.m_BreiteAlt.IsEmpty())
			ssl.m_BreiteAlt = ssl.m_Breite;
		
		satzLast.Set(ssl);
		if (nGeaendert == 2 || nGeaendert == 3)
			m_ctrlComboSteinnummern.SetFocus();
        PlaySoundAdd();
        return;
	}
	else
	{
		satz0.m_buchungsNummer = m_pAuftraege->NaechsteBuchungsnummer();    // im der Umbuchungsdatei eintragen
		satz0.SetDatumZeit();

		SSatz ssl(satz0);
		// und hier noch einmal alle Änderbaren Werte in Alt kopieren, damit beim Löschen der Änderung nicht alle Daten weg sind. ch 14.02.2013
		if (ssl.m_OberNrAlt.IsEmpty())
			ssl.m_OberNrAlt = ssl.m_OberNr;
		if (ssl.m_FehlNummerAlt.IsEmpty())
			if (ssl.m_FehlNummer.IsEmpty())
				ssl.m_FehlNummerAlt = _T("0");
			else
				ssl.m_FehlNummerAlt = ssl.m_FehlNummer;
		if (ssl.m_LaengeAlt.IsEmpty())
			ssl.m_LaengeAlt = ssl.m_Laenge;
		if (ssl.m_BreiteAlt.IsEmpty())
			ssl.m_BreiteAlt = ssl.m_Breite;
		if (ssl.m_FehlLaengeAlt.IsEmpty())
			if (ssl.m_FehlLaenge.IsEmpty())
				ssl.m_FehlLaengeAlt = _T("0");
			else
				ssl.m_FehlLaengeAlt = ssl.m_FehlLaenge;
		if (ssl.m_FehlBreiteAlt.IsEmpty())
			if (ssl.m_FehlBreite.IsEmpty())
				ssl.m_FehlBreiteAlt = _T("0");
			else
				ssl.m_FehlBreiteAlt = ssl.m_FehlBreite;
		satz0.Set(ssl);

		curAuftrag.AddPosition(satz0);    // es gibt nur einen Auftrag "OberflaecheAendern"
		PlaySoundAdd();
		if (nGeaendert = 1 || nGeaendert == 3)
		{
			m_ctrlEditFehlLaengeAlt.SetWindowText(laengeNeu);
			m_ctrlEditFehlLaengeNeu.SetWindowText(_T(""));
		}
		if (nGeaendert = 2 || nGeaendert == 3)
		{
			m_ctrlEditFehlBreiteAlt.SetWindowText(breiteNeu);
			m_ctrlEditFehlBreiteNeu.SetWindowText(_T(""));
		}
	}
}
if (nGeaendert == 0 || nGeaendert == 2 || nGeaendert == 3)
	m_ctrlComboSteinnummern.SetFocus();
}
void COberflaecheAendern::OnCbnSelchangeComboBissteinnummern()
{
	int index = m_ctrlComboBisSteinnummer.GetCurSel();
	CString str = _T("");
	if (index >= 0)
		str = m_pSteinSaetze->arr[index].Nummer();
	CheckBisSteinnummer(str);
}

void COberflaecheAendern::OnCbnEditchangeComboBissteinnummern()
{
	CString str;
	m_ctrlComboBisSteinnummer.GetWindowText(str);
	CheckBisSteinnummer(str);
}
void COberflaecheAendern::CheckBisSteinnummer(const CString &str)
{

	if (!str.IsEmpty() )	
	{
		// wenn die Bis-Nr gefüllt ist, können KEINE Maßänderungen vorgenommen werden ch 14.02.2013
		m_ctrlEditLaengeNeu.EnableWindow(FALSE);
		m_ctrlEditBreiteNeu.EnableWindow(FALSE);
		m_ctrlEditFehlLaengeNeu.EnableWindow(FALSE);
		m_ctrlEditFehlBreiteNeu.EnableWindow(FALSE);
		
	}
	else
	{
		// wenn die Bis-Nr leer ist, können wieder Maßänderungen vorgenommen werden ch 14.02.2013
		m_ctrlEditLaengeNeu.EnableWindow(TRUE);
		m_ctrlEditBreiteNeu.EnableWindow(TRUE);
		m_ctrlEditFehlLaengeNeu.EnableWindow(TRUE);
		m_ctrlEditFehlBreiteNeu.EnableWindow(TRUE);
	}
}