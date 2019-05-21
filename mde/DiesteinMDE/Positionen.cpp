// Positionen.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "Positionen.h"
#include "PlattenZugang.h"
#include "RueckZugang.h"
#include "Blockdaten.h"


IMPLEMENT_DYNAMIC(CPositionen, CDialog)

/////////////////////////////////////////////////////////////////////////////
extern CSteinSatz g_baseSteinSatz;
/////////////////////////////////////////////////////////////////////////////
// CPositionen dialog

CPositionen::CPositionen(CWnd* pParent /*=NULL*/)
	: CDialog(CPositionen::IDD, pParent)
{
	m_strAktuelleNummer = _T("");
	m_bCheckRueck = FALSE;
	m_bCheckRest = FALSE;
    m_ProduktionVerkauf = _T("");
    m_curFocus = NUMMER;
    m_bBlink = FALSE;
	m_curAnzahl = 0;
	// Kennzeichen von Blockänderungen grundsätzlich auf FALSE setzen. Kann dann nur bei "INVENTUR" geändert werden. ch 16.12.2013
	m_bGeaendertBlockDaten = FALSE;
	
m_nSetHinzu = 0;
}


void CPositionen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_STEINNUMMER, m_ctrlComboSteinSaetze);
	DDX_Control(pDX, IDC_STATIC_FEHLER, m_ctrlStaticFehler);
	DDX_Control(pDX, IDC_STATIC_FEHLECKE, m_ctrlStaticFehlEcke);
	DDX_Control(pDX, IDC_STATIC_FEHLLAENGE, m_ctrlStaticFehlLaenge);
	DDX_Control(pDX, IDC_STATIC_FEHLBREITE, m_ctrlStaticFehlBreite);
	//	DDX_Control(pDX, IDC_EDIT_FEHLNUMMER, m_ctrlEditFehlNummer);
	DDX_Control(pDX, IDC_EDIT_FEHLLAENGE, m_ctrlEditFehlLaenge);
	DDX_Control(pDX, IDC_EDIT_FEHLBREITE, m_ctrlEditFehlBreite);
	DDX_Control(pDX, IDC_EDIT_BUCHMENGE, m_ctrlEditBuchungsMenge);
	DDX_Control(pDX, IDC_BUTTON_POSHINZU, m_ctrlButtonPosHinzu);
	DDX_Control(pDX, IDC_EDIT_LAENGE, m_ctrlEditLaenge);
	DDX_Control(pDX, IDC_EDIT_BREITE, m_ctrlEditBreite);
	DDX_Control(pDX, IDC_STATIC_MATERIAL_TEXT, m_ctrlStaticMaterialText);
	DDX_Control(pDX, IDC_STATIC_STEINNUMMER, m_ctrlStaticSteinnummer);
	DDX_Control(pDX, IDC_STATIC_POSITIONENZAHL, m_ctrlStaticPositionenZahl);
	DDX_Control(pDX, IDC_STATIC_OBERFLAECHE_TEXT, m_ctrlStaticOberflaecheText);
	DDX_Control(pDX, IDC_STATIC_ME2, m_ctrlStaticME2);
	DDX_Control(pDX, IDC_STATIC_ME1, m_ctrlStaticME1);
	DDX_Control(pDX, IDC_STATIC_DICKE_TEXT, m_ctrlStaticDickeText);
	DDX_Control(pDX, IDC_STATIC_AUFTRAGSNAME, m_ctrlStaticAuftragsName);
	DDX_Control(pDX, IDC_STATIC_ARTIKEL_TEXT, m_ctrlStaticArtikelText);
	DDX_Control(pDX, IDC_COMBO_LAGER, m_ctrlComboLager);
	DDX_Control(pDX, IDC_STATIC_LAGER, m_ctrlStaticLager);
	DDX_Control(pDX, IDC_STATIC_BREITE, m_ctrlStaticBreite);
	DDX_Control(pDX, IDC_STATIC_LAENGE, m_ctrlStaticLaenge);
	DDX_Control(pDX, IDC_STATIC_DICKE, m_ctrlStaticDicke);
	DDX_Control(pDX, IDC_STATIC_OBERFLAECHE, m_ctrlStaticOberflaeche);
	DDX_Control(pDX, IDC_STATIC_MATERIAL, m_ctrlStaticMaterial);
	DDX_Control(pDX, IDC_STATIC_ARTIKEL, m_ctrlStaticArtikel);
	DDX_Control(pDX, IDC_STATIC_MENGE, m_ctrlStaticMenge);
	DDX_Control(pDX, IDC_CHECK_RUECK, m_ctrlCheckRueck);
	DDX_Check(pDX, IDC_CHECK_RUECK, m_bCheckRueck);
	DDX_Control(pDX, IDC_COMBO_FEHLER, m_ctrlComboFehler);
	DDX_Control(pDX, IDC_STATIC_HINWEIS2, m_ctrlStaticHinweis);
	DDX_Control(pDX, IDC_STATIC_HINWEIS2_TEXT, m_ctrlStaticHinweisText);
	DDX_Control(pDX, IDC_STATIC_RESERVIERT1, m_ctrlStaticReserviert);
	DDX_Control(pDX, IDC_EDIT_POSLAGERORT, m_ctrlEditLagerort);
	DDX_Control(pDX, IDC_BUTTON_BLOCKMASSE, m_ctrlButtonBlockDaten);
	DDX_Control(pDX, IDC_CHECK_REST, m_ctrlCheckRest);
	DDX_Check(pDX, IDC_CHECK_REST, m_bCheckRest);
}


BEGIN_MESSAGE_MAP(CPositionen, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_POSHINZU, OnButtonPoshinzu)
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_COMBO_STEINNUMMER, OnSelchangeComboSteinnummer)
	ON_BN_CLICKED(IDC_CHECK_RUECK, OnCheckRueck)
	ON_BN_CLICKED(IDC_STATIC_ARTIKEL_TEXT, OnStaticArtikelText)
	ON_CBN_SETFOCUS(IDC_COMBO_LAGER, OnSetfocusComboLager)
	ON_CBN_KILLFOCUS(IDC_COMBO_LAGER, OnKillfocusComboLager)
	ON_CBN_EDITCHANGE(IDC_COMBO_STEINNUMMER, OnEditchangeComboSteinnummer)
	ON_WM_TIMER()
    ON_EN_KILLFOCUS(IDC_EDIT_LAENGE, &CPositionen::OnEnKillfocusEditLaenge)
    ON_EN_KILLFOCUS(IDC_EDIT_BREITE, &CPositionen::OnEnKillfocusEditBreite)
    ON_EN_KILLFOCUS(IDC_EDIT_FEHLLAENGE, &CPositionen::OnEnKillfocusEditFehllaenge)
    ON_EN_KILLFOCUS(IDC_EDIT_FEHLBREITE, &CPositionen::OnEnKillfocusEditFehlbreite)
	ON_EN_CHANGE(IDC_EDIT_POSLAGERORT, &CPositionen::OnEnChangeEditPoslagerort)
	ON_BN_CLICKED(IDC_BUTTON_BLOCKMASSE, &CPositionen::OnBnClickedButtonBlockmasse)
	ON_EN_KILLFOCUS(IDC_EDIT_BUCHMENGE, &CPositionen::OnEnKillfocusEditBuchmenge)
	ON_BN_CLICKED(IDC_CHECK_REST, OnCheckRest)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
BOOL CPositionen::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
TranslateStatic(m_ctrlStaticMenge);
TranslateStatic(m_ctrlStaticArtikel);
TranslateStatic(m_ctrlStaticMaterial);
TranslateStatic(m_ctrlStaticOberflaeche);
TranslateStatic(m_ctrlStaticDicke);
TranslateStatic(m_ctrlStaticLaenge);
TranslateStatic(m_ctrlStaticBreite);
TranslateStatic(m_ctrlStaticFehlEcke);
TranslateStatic(m_ctrlStaticFehlLaenge);
TranslateStatic(m_ctrlStaticFehlBreite);
TranslateStatic(m_ctrlStaticFehler);
TranslateStatic(m_ctrlStaticLager);
TranslateStatic(m_ctrlStaticHinweis);

TranslateButton(m_ctrlButtonPosHinzu);
TranslateButton(m_ctrlButtonBlockDaten);	// ch 16.12.2013
TranslateButton(m_ctrlCheckRueck);
TranslateButton(m_ctrlCheckRest);

m_ctrlButtonBlockDaten.ShowWindow(FALSE);   // ch 16.12.2013

// folgenden Befehl hierhin kopiert, damit die Artikelgruppen in der Funktion SetComboSteinsaetze eingelesen sind
m_ArtikelGruppen.Read();

SetComboSteinSaetze();

m_LagerTabelle.Read();
int i;
for(i = 0; i < m_LagerTabelle.GetSize(); i++)
    {
    CString str;
    str.Format(_T("%s %s"),m_LagerTabelle.GetAt(i).m_key,m_LagerTabelle.GetAt(i).m_bez);
    m_ctrlComboLager.AddString(str);
    }

m_FehlerTabelle.Read();
C2String s2;
m_FehlerTabelle.InsertAt(0,s2); // Leerauswahl an den Anfang

for(i = 0; i < m_FehlerTabelle.GetSize(); i++)
    {
    m_ctrlComboFehler.AddString(m_FehlerTabelle.GetAt(i).m_bez);
    }

// Nach oben kopiert wegen Einlesen nur Blöcke
//m_ArtikelGruppen.Read();

SetComboLager(_T(""));

SetComboFehler(_T(""));

m_hinzEnable = TRUE;


if(m_nModus == ID_GATTERN )
{
	CString nummer;
	int index = 0;
	m_ctrlComboSteinSaetze.SetCurSel(index);
	if (m_ctrlComboSteinSaetze.GetCount() > 0)
	{
		m_ctrlComboSteinSaetze.GetLBText(index ,nummer);
		m_pSteinSaetze->FoundAt(nummer, index);
		AnzeigePlattenDaten(index);
	}
}
// Bei diesen Vorgängen wird die erste Platte NICHT ausgewählt ch 07.02.2013
else if ((m_nModus == ID_VERKAUF) || (m_nModus == ID_PRODUKTION) || (m_nModus == ID_RESERVIERUNG ) || (m_nModus == ID_LIEFERUNG ))
	AnzeigePlattenDaten(-1);
else
	AnzeigePlattenDaten(0);

CString str;
if (!(m_nModus == ID_GATTERN))
	str.Format(_T("%s: %s"),Sprache(_T("Auftrag")),m_pAuftrag->m_strIdent);
else
	str.Format(_T("%s"),m_pAuftrag->m_strIdent);
m_ctrlStaticAuftragsName.SetWindowText(str);

str.Format(_T("%-3d %s"),m_pAuftrag->m_Positionen.Anzahl(),Sprache(_T("Positionen")));
m_ctrlStaticPositionenZahl.SetWindowText(str);

if(g_Optionen.MasseAendEnabled() && !(m_nModus == ID_GATTERN) )
    {
    m_ctrlEditLaenge.EnableWindow(TRUE);
    m_ctrlEditBreite.EnableWindow(TRUE);
    m_ctrlEditFehlLaenge.EnableWindow(TRUE);
    m_ctrlEditFehlBreite.EnableWindow(TRUE);
    m_ctrlComboFehler.EnableWindow(TRUE);
//    m_ctrlEditFehlNummer.EnableWindow(TRUE);
    }


if(g_Optionen.RueckEnabled() && !m_pAuftraege->m_strName.Compare(NAME_PRODUKTION))
	{    
	m_ctrlCheckRueck.EnableWindow(TRUE);
	m_ctrlCheckRest.EnableWindow(TRUE);
	}
else
	{
    m_ctrlCheckRueck.EnableWindow(FALSE);
	m_ctrlCheckRest.EnableWindow(FALSE);
	}

m_ctrlEditBuchungsMenge.SetFocus();

if(m_nModus == ID_INVENTUR)
    m_ctrlEditBuchungsMenge.SetWindowText(m_pSteinSaetze->SteinSatz(0).StrMenge1());
else
    m_ctrlEditBuchungsMenge.SetWindowText(_T("1,00"));
// Bei diesen Vorgängen sitzt der Cursor am Anfang auf der ComboBox für die Steinsätze  ch 07.02.2013
if(!(((m_nModus == ID_VERKAUF) || (m_nModus == ID_PRODUKTION) || (m_nModus == ID_RESERVIERUNG ) || (m_nModus == ID_LIEFERUNG ))))
	m_ctrlEditBuchungsMenge.SetSel(0,-1,FALSE);  // Alles selektieren
else
	m_ctrlComboSteinSaetze.SetFocus();

m_pScanner->setEnableScanner(TRUE);   // Hier scannen erlauben

if(m_nModus == ID_PRODUKTION)
    m_ProduktionVerkauf = Sprache(_T("Produktion")).Left(1); // nichts "" oder Produktion "P" oder Verkauf "V"

if((m_nModus == ID_VERKAUF) || (m_nModus == ID_LIEFERUNG))
    m_ProduktionVerkauf = Sprache(_T("Verkauf")).Left(1); // nichts "" oder Produktion "P" oder Verkauf "V"

//m_ProduktionVerkauf = g_Optionen.PVEnabled(); // nichts "" oder Produktion "P" oder Verkauf "V"

//SetPVButtons(m_ProduktionVerkauf);


return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//-----------------------------------------------------------------------------
void CPositionen::SetComboSteinSaetze()
{
//int sel = m_ctrlComboSteinSaetze.GetCurSel();
m_ctrlComboSteinSaetze.ResetContent();

CString sRohblockAgr = _T(";");
if (m_nModus == ID_GATTERN)
{
	for(int x = 0; x < m_ArtikelGruppen.GetCount(); x++)
	{
		CString key = m_ArtikelGruppen.GetAt(x).m_key;
		if(key.IsEmpty())
			continue;
	    if(key.GetAt(key.GetLength()-1) == _T('B'))
			sRohblockAgr = sRohblockAgr + key.Left(key.GetLength() - 1) + _T(";");
    }
}


int i;
for(i = 0; i < m_pSteinSaetze->Anzahl(); i++)
    {
		if (!(m_nModus == ID_GATTERN))
			m_ctrlComboSteinSaetze.AddString(m_pSteinSaetze->arr[i].Nummer());
		else
		{
		/*	BOOL bResult;
			bResult = m_ArtikelGruppen.IsRohBlockGruppe(m_pSteinSaetze->arr[i].ArtikelGr());
			if (m_ArtikelGruppen.IsRohBlockGruppe(m_pSteinSaetze->arr[i].ArtikelGr()))
				m_ctrlComboSteinSaetze.AddString(m_pSteinSaetze->arr[i].Nummer()); */
		/*if ( sRohblockAgr.Find(_T(";") + m_pSteinSaetze->arr[i].ArtikelGr() + _T(";")) >= 0)
				m_ctrlComboSteinSaetze.AddString(m_pSteinSaetze->arr[i].Nummer()); */
			if (m_pSteinSaetze->arr[i].Artikel() == _T("Block") )
				m_ctrlComboSteinSaetze.AddString(m_pSteinSaetze->arr[i].Nummer());
			
		}	
    }
//if((sel >= 0) && (sel < m_ctrlComboSteinSaetze.GetCount()))
//    m_ctrlComboSteinSaetze.SetCurSel(sel);
}
//-----------------------------------------------------------------------------
void CPositionen::AnzeigePlattenDaten(int index)
{
CSteinSatz satz;    // Alle Felder leer

if((index >= 0) && (index < m_pSteinSaetze->Anzahl()))
    {
    satz = m_pSteinSaetze->arr[index];
	if(m_nModus == ID_GATTERN)
		m_ctrlComboSteinSaetze.SetCurSel(m_ctrlComboSteinSaetze.FindStringExact(0,satz.Nummer()));
	else
		m_ctrlComboSteinSaetze.SetCurSel(index);
    if(m_nModus == ID_INVENTUR)
		{
        m_ctrlComboLager.EnableWindow();
		m_ctrlEditLagerort.EnableWindow();
		if (satz.Artikel() == _T("Block"))
			m_ctrlButtonBlockDaten.ShowWindow (TRUE);
		else
			m_ctrlButtonBlockDaten.ShowWindow (FALSE);

		// Kennzeichen bzw. Daten für geänderte BlockDaten zurücksetzen
		m_bGeaendertBlockDaten = FALSE;
		SSatz s;
		m_GeaenderteBlockDaten.Set(s);
		}
    else
        {
        if(m_ctrlCheckRueck.GetCheck())
			{
            m_ctrlComboLager.EnableWindow();
			m_ctrlEditLagerort.EnableWindow();
			}
		else
			{
            m_ctrlComboLager.EnableWindow(FALSE);
			m_ctrlEditLagerort.EnableWindow(FALSE);
			}
        }
    }
else
	{
    m_ctrlComboLager.EnableWindow();    // Damit unbekannte Steinnummer mit Lager rückgebucht werden kann
	m_ctrlEditLagerort.EnableWindow();
	}

AnzeigeTexte(satz);
}
//---------------------------------------------------------------------------
void CPositionen::AnzeigeTexte(const CSteinSatz& satz)
{
SSatz ss(satz);

m_strAktuelleNummer = ss.m_Nummer;
m_ctrlEditLaenge.SetWindowText(ss.m_Laenge);
m_ctrlEditBreite.SetWindowText(ss.m_Breite);
m_ctrlStaticME1.SetWindowText(ss.m_Menge1 + _T(" ") + ss.m_ME1);
if(satz.Menge2() != 0.)
    m_ctrlStaticME2.SetWindowText(ss.m_Menge2 + _T(" ") + ss.m_ME2);
else
    m_ctrlStaticME2.SetWindowText(_T(""));
m_ctrlEditFehlLaenge.SetWindowText(ss.m_FehlLaenge);
m_ctrlEditFehlBreite.SetWindowText(ss.m_FehlBreite);
SetComboFehler(ss.m_FehlNummer);

m_ctrlStaticArtikelText.SetWindowText(ss.m_Artikel);
//if(g_Optionen.BoeseEnabled() && (m_nModus == ID_VERKAUF))
//    {
//    if(m_strAktuelleNummer == _T('X'))
//        m_ctrlStaticArtikelText.SetWindowText(ss.m_GA_Artikel);
//    }

m_ctrlStaticMaterialText.SetWindowText(ss.m_Material);
m_ctrlStaticOberflaecheText.SetWindowText(ss.m_Oberflaeche);
m_ctrlStaticDickeText.SetWindowText(ss.m_Dicke);
m_ctrlStaticHinweisText.SetWindowText(ss.m_Hinweis);

m_ctrlStaticSteinnummer.SetWindowText(Sprache(_T("Steinnummer")));
if(!satz.Nummer().IsEmpty())
    {
    for(int i = 0; i < m_pAuftrag->m_Positionen.Anzahl(); i++)
        {
        if(    (satz.Nummer() == m_pAuftrag->Position(i).Nummer()) 
            && (satz.Artikel() == m_pAuftrag->Position(i).Artikel()))
            {
            m_ctrlStaticSteinnummer.SetWindowText(Sprache(_T("Steinnummer *")));
            break;
            }
        }
    }

KillTimer(12);
m_bBlink = FALSE;
m_ctrlStaticReserviert.SetWindowText(_T(""));
if(!g_Optionen.BoeseEnabled())
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

SetComboLager(ss.m_Lager);
}
//------------------------------------------------------------------------------------
void CPositionen::OnTimer(UINT nIDEvent) 
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
//---------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
// CPositionen message handlers
void CPositionen::OnButtonPoshinzu() 
{
m_ctrlComboSteinSaetze.GetWindowText(m_strAktuelleNummer);
if(m_strAktuelleNummer.IsEmpty())
    return;

// Böse /////////////////
m_nSetHinzu = 0;
//m_strAktuelleNummer.MakeUpper();

if(g_Optionen.BoeseEnabled() && (m_nModus == ID_VERKAUF))
    {
    if(m_strAktuelleNummer.GetAt(0) == _T('X'))
        m_nSetHinzu = 1;
    }

if(m_nSetHinzu)
    {
    m_strAktuelleNummer = m_strAktuelleNummer.Mid(1);
    }
//////////////////////////////

if(m_strAktuelleNummer.Compare(m_strLetzteNummer)) // Damit nicht 2mal aus versehen hinzugefügt wird
    m_hinzEnable = TRUE;

if(!m_hinzEnable)
    return;

m_ctrlComboSteinSaetze.SetWindowText(m_strAktuelleNummer);

m_strLetzteNummer = m_strAktuelleNummer;

int index = FindNumber(m_strAktuelleNummer);

if((index < 0) && (m_bCheckRueck == FALSE))
    {
    if((m_nModus == ID_VERKAUF) || (m_nModus == ID_LIEFERUNG))
        {
        AfxMessageBox(Sprache(_T("Steinnummer nicht im Lagerbestand!")));
        return;
        }

    if(m_nModus == ID_INVENTUR)  // Auftrag heißt Inventur
        {
		m_pScanner->setEnableScanner(FALSE);
		int ret = DialogPlattenDefinition();
		m_pScanner->setEnableScanner(TRUE);
		if(ret)
			HinzuEnd(index);
		return;
        }
    if(g_Optionen.RueckEnabled())
        {
        if(AfxMessageBox(Sprache(_T("Steinnummer nicht im Lagerbestand!"))+Sprache(_T("\nSoll eine Rückbuchung durchgeführt werden?")),MB_YESNO)
            == IDNO)
            return;
        RueckEnable(TRUE);  // setzt m_bCheckRueck = TRUE
        AnzeigePlattenDaten(-1);
        }
    else
        {
        AfxMessageBox(Sprache(_T("Steinnummer nicht im Lagerbestand!")));
        return;
        }
    }
if((index >= 0) && ((m_nModus == ID_VERKAUF) || (m_nModus == ID_PRODUKTION && g_Optionen.ProduktionMehrereAuftraegeEnabled() == FALSE) || (m_nModus == ID_RESERVIERUNG ) || (m_nModus == ID_LIEFERUNG )) )
    {
    if(m_pSteinSaetze->SteinSatz(index).Menge1() == 0 && m_bCheckRueck == FALSE )
        {
        AfxMessageBox(Sprache(_T("Platte nicht verfügbar!")));
        return;
        }
	}
// bei Inventur prüfen, ob die Steinnr bereits gescannt wurde, wenn ja, dann Meldung ch 18.12.2018 (für Just)
if ( (index >= 0) && (m_nModus == ID_INVENTUR && g_Optionen.InventurRohplattenNichtDoppeltErfassenEnabled() == TRUE) )
	{
	 if(m_ArtikelGruppen.IsRohPlattenGruppe(m_pSteinSaetze->SteinSatz(index).ArtikelGr()) && (m_pSteinSaetze->SteinSatz(index).Menge1() == 0) )
		{
		for (int i = 0; i < m_pAuftraege->Anzahl(); i++)
			{
			int ix;		
			m_pAuftraege->Auftrag (i).m_Positionen.FoundAt (m_strAktuelleNummer, ix);
			if (ix >= 0)
				{
					AfxMessageBox(Sprache(_T("Platte bereits gescannt!")));
					return;
				}
			}
		}
	} 

// Prüfen, ob Block schon gescannt wurde
if (m_nModus == ID_GATTERN )
	{
	// erst mal in den neu Angelegten Gatteraufträgen schauen
	for (int i = 0; i < m_pAuftraege->Anzahl(); i++)
		{
			if (m_pAuftraege->Auftrag(i).m_strIdent.Right(2) != _T("-S"))
			{
				int ix;		
				m_pAuftraege->Auftrag (i).m_Positionen.FoundAt (m_strAktuelleNummer, ix);
				if (ix >= 0)
				{
					AfxMessageBox(Sprache(_T("Block bereits anderem Gatter zugeordnet!")));
					return;
				}
			}
		}
	// im zweiten Schritt noch in den offenenGatterAuftägen prüfen
	for (int i = 0; i < m_pOffeneAuftraege->Anzahl(); i++)
		{
			if (m_pOffeneAuftraege->Auftrag(i).m_strIdent.Right(2) != _T("-S"))
			{
				int ix;		
				m_pOffeneAuftraege->Auftrag (i).m_Positionen.FoundAt (m_strAktuelleNummer, ix);
				if (ix >= 0)
				{
					AfxMessageBox(Sprache(_T("Block bereits anderem Gatter zugeordnet!")));
					return;
				}
			}
		}
	}

if(m_bCheckRueck == FALSE)    // Normal hinzubuchen
    {
    if(!NormalHinzubuchen(index))   // index muss gültig sein
        return;
    }
else    // Rückbuchung, d.h. negative Menge
    {
    if(!NormalRueckbuchen())
        return;
    }

HinzuEnd(index);
}
//-------------------------------------------------------------------------------
void CPositionen::HinzuEnd(int index)
{
PlaySoundAdd();

m_hinzEnable = FALSE;

CString str;
str.Format(_T("%-3d %s"),m_pAuftrag->m_Positionen.Anzahl(),Sprache(_T("Positionen")));
m_ctrlStaticPositionenZahl.SetWindowText(str);

m_ctrlEditBuchungsMenge.SetFocus();
if(index >= 0)
    AnzeigePlattenDaten(index);
//SetDlgItemText(IDC_EDIT_BUCHMENGE,m_strBuchungsMenge);
m_ctrlEditBuchungsMenge.SetSel(0,-1,FALSE);  // Alles selektieren

if(m_nSetHinzu)
    {
    m_nSetHinzu = 0;
    m_strAktuelleNummer = _T("X") + m_strAktuelleNummer;
    }

m_ctrlComboSteinSaetze.SetWindowText(m_strAktuelleNummer);
if (m_nModus == ID_VERKAUF)
	m_ctrlComboSteinSaetze.SetFocus();

// Im Inventurmodus soll nach der Erfassung von 100 Platten eine Speicherung erfolgen  ch 18.11.2013
if (m_nModus == ID_INVENTUR )
	{
		m_curAnzahl = m_curAnzahl + 1;
		if (m_curAnzahl >= 100 )
			{
				m_pAuftraege->Save();
				m_pSteinSaetze->Save();
				m_curAnzahl = 0;
			}
	}
}
//-------------------------------------------------------------------------------
BOOL CPositionen::NormalHinzubuchen(int index)
{
if(index < 0) return FALSE; // kann eigentlich nicht sein

// Falls irgendwo Unsinn steht (nur prüfen wenn enabled, Leere felder erlaubt)
if(!WerteOk())return FALSE;

if(m_nModus == ID_LIEFERUNG) // Reservierte Platten(oder vergleichbare) für Lieferung zusammenstellen
    return LieferungNormalHinzubuchen(index);

CSteinSatz satz0(m_pSteinSaetze->SteinSatz(index));

SSatz ss(satz0);

if(m_nModus == ID_RESERVIERUNG) // Prüfen ob bei reservierten Platten genügend Verfügbare Menge da ist
    {
    if(!ss.m_ResFuerAuftrag.IsEmpty())
        {
        double mverfueg = satz0.Menge1Verfuegbar();
        if(mverfueg <= 0.)
            {
            MessageBox(_T("Artikel ist vollständig reserviert"),_T("Reservierter Artikel"),MB_OK);
            return false;
            }
        CString strb;
        m_ctrlEditBuchungsMenge.GetWindowText(strb);
        if((mverfueg > 0.) && (mverfueg < satz0.StringToDouble(strb)))
            {
            if(MessageBox(_T("Restmenge hinzufügen"),_T("Reservierter Artikel"),MB_YESNO) == IDNO)
                return false;
            m_ctrlEditBuchungsMenge.SetWindowText(satz0.DoubleToString(mverfueg));
            }
        }
    }

if(g_Optionen.BoeseEnabled() && (m_nModus == ID_VERKAUF)) // bei Böse auf Reservierung prüfen
    {
    if(!ss.m_ResFuerAuftrag.IsEmpty())
        {
        MessageBox(_T("Der Artikel ist reserviert"));
        return false;
        }
    else
        {
        if(satz0.Menge1() <= 0.01)
            {
            MessageBox(_T("Keine Artikelmenge vorhanden"),MB_OK);
            return false;
            }
        }
    }

m_ctrlEditBuchungsMenge.GetWindowText(ss.m_Menge1);
if (ss.m_Menge1.GetLength() == 0 )
	{
	ss.m_Menge1 = _T("0");
	}


satz0.Set(ss);
if((satz0.Menge1() < 0) || ((m_nModus != ID_INVENTUR) && (satz0.Menge1() == 0)) )
    {
    CString str;
    m_ctrlEditBuchungsMenge.GetWindowText(str);
    m_ctrlEditBuchungsMenge.SetWindowText(str.Mid(1));
    m_ctrlEditBuchungsMenge.SetFocus();
    m_ctrlEditBuchungsMenge.SetSel(0,-1);  // Alles selektieren
    PlaySoundOther();
    return FALSE;
    }


m_ctrlEditLaenge.GetWindowText(ss.m_Laenge);
m_ctrlEditBreite.GetWindowText(ss.m_Breite);
m_ctrlEditFehlLaenge.GetWindowText(ss.m_FehlLaenge);
m_ctrlEditFehlBreite.GetWindowText(ss.m_FehlBreite);

ss.m_FehlNummer = GetComboFehler();
//m_ctrlEditFehlNummer.GetWindowText(ss.m_FehlNummer);

ss.m_Ende.Empty();

if(m_nModus == ID_INVENTUR)
    {
    int lcurs = m_ctrlComboLager.GetCurSel();
    if((lcurs >= 0) && lcurs < m_LagerTabelle.GetSize())
        {
        if(ss.m_Lager.Compare(m_LagerTabelle.GetAt(lcurs).m_key))
            {
            ss.m_LagerAlt = ss.m_Lager;
            ss.m_Lager = m_LagerTabelle.GetAt(lcurs).m_key;
            }
        }
	// Bei Inventur könnten auch die Blockdaten verändert worden sein. Diese jetzt beim Hinzufügen in den Steinsatz übernehmen. ch 16.12.2013
	if (m_bGeaendertBlockDaten && (m_GeaenderteBlockDaten.Artikel() != _T("")) )
		{
			SSatz sBlockdaten(m_GeaenderteBlockDaten);
			// Länge/Breite wurden oben bereits korrigiert  ch 16.12.2013
			ss.m_Dicke = sBlockdaten.m_Dicke ;
			ss.m_LaengeBrutto = sBlockdaten.m_LaengeBrutto ;
			ss.m_BreiteBrutto = sBlockdaten.m_BreiteBrutto ;
			ss.m_DickeBrutto = sBlockdaten.m_DickeBrutto ;
			// und jetzt gleich noch die Daten wieder zurücksetzen ch 16.12.2013
			m_bGeaendertBlockDaten = FALSE;
			m_GeaenderteBlockDaten.Artikel() = _T("");
		}
    }

satz0.Set(ss);

satz0.m_buchungsNummer = NaechsteBuchungsnummer();
satz0.SetProduktionVerkauf(m_ProduktionVerkauf);
satz0.SetDatumZeit();

//CString strx;
//strx.Format(_T("Rueck %d"),satz0.m_buchungsNummer);
//AfxMessageBox(strx);
//////////////////////////////////////// neu 15.3.06
m_pSteinSaetze->SubSatz(satz0); // Menge 1 in Steinsätze verringern
////////////////////////////////////////
if(m_nSetHinzu)
    {
    satz0.SetNummer(_T("X")+satz0.Nummer());
    }

m_pAuftrag->AddPosition(satz0); // Muss zuletzt stehen

return TRUE;
}
//-------------------------------------------------------------------------------
BOOL CPositionen::LieferungFindePassendenSteinsatz(const CString& strAuftrag,const CSteinSatz& satz0,CSteinSaetze& Steinsaetze,int& i)
{
SSatz s0(satz0);
for(i = 0; i < Steinsaetze.Anzahl(); i++)
    {
    if(strAuftrag.CompareNoCase(Steinsaetze.SteinSatz(i).ResFuerAuftrag()))
        continue;
    CSteinSatz& satz = Steinsaetze.SteinSatz(i);
    SSatz s(satz);
    if(     !strAuftrag.CompareNoCase(s.m_ResFuerAuftrag)
        &&  !s0.m_ArtNr.CompareNoCase(s.m_ArtNr)
        &&  !s0.m_MatGr.CompareNoCase(s.m_MatGr)
        &&  !s0.m_MatNr.CompareNoCase(s.m_MatNr)
        &&  !s0.m_OberNr.CompareNoCase(s.m_OberNr)
        &&  !s0.m_Laenge.CompareNoCase(s.m_Laenge)
        &&  !s0.m_Breite.CompareNoCase(s.m_Breite)
        &&  !s0.m_Dicke.CompareNoCase(s.m_Dicke)
        &&  !s0.m_Hinweis.CompareNoCase(s.m_Hinweis)
        )
        return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------
BOOL CPositionen::LieferungNormalHinzubuchen(int index)
{
CSteinSatz satz0(m_pSteinSaetze->SteinSatz(index)); // gewählter Satz

CString resAuftrag = satz0.ResFuerAuftrag();

if(!resAuftrag.IsEmpty() && resAuftrag.CompareNoCase(m_pAuftrag->m_strIdent))
    {
    MessageBox(_T("Artikel ist für einen anderen Auftrag reserviert!"));
    return FALSE;
    }

SSatz ss0(satz0);
if(!ss0.m_TypKennung.CompareNoCase(_T("K"))) // Keile immer dazunehmen
    {
    }
else
    {
    if(satz0.ResFuerAuftrag().IsEmpty()) // satz0 ist ohne Reservierung
        {
        int iResFound;
        if(LieferungFindePassendenSteinsatz(m_pAuftrag->m_strIdent,satz0,*m_pSteinSaetze,iResFound))
            {
            CSteinSatz& passenderSatz = m_pSteinSaetze->SteinSatz(iResFound);
            int nix;
            if(m_pAuftrag->m_Positionen.FoundAt(passenderSatz.Nummer(),nix))
                {
                MessageBox(_T("Der Artikel ist bereits gebucht!"));
                return FALSE;
                }
            if(MessageBox(_T("Diesen identischen Artikel hinzubuchen?"),_T("Nicht reservierter Artikel"),MB_YESNO) == IDNO)
                return FALSE;

            CSteinSatz& gewaehlterSatz = m_pSteinSaetze->SteinSatz(index); // Referenz auf gewählten Satz
            SSatz s0(satz0); // ist ebenfalls gewählter satz
            SSatz spass(passenderSatz);
            s0.m_ResFuerAuftrag = spass.m_ResFuerAuftrag;
            s0.m_AuftragsKundenname = spass.m_AuftragsKundenname;
            s0.m_AuftragsPos = spass.m_AuftragsPos;
            s0.m_AuftragsTeilpos = spass.m_AuftragsTeilpos;
            satz0.Set(s0);
            gewaehlterSatz.Set(s0);                     // Reservierung in den gewählten Satz schreiben
            passenderSatz.LieferungReservierungRemove();    // Aus dem Originalsatz Reservierung entfernen
            }
        else
            {
            MessageBox(_T("Keinen vergleichbaren reservierten Artikel gefunden!"));
            return FALSE;
            }
        }
    else
        {
        CSteinSatz& remSatz = m_pSteinSaetze->SteinSatz(index);
    //    remSatz.BoeseReservierungRemove();
        int nix;
        if(m_pAuftrag->m_Positionen.FoundAt(remSatz.Nummer(),nix))
            {
            MessageBox(_T("Der Artikel ist bereits gebucht!"));
            return FALSE;
            }
        }
    }

SSatz ss(satz0);

CString strBuch;
m_ctrlEditBuchungsMenge.GetWindowText(strBuch);

ss.m_Menge1 = strBuch;
satz0.Set(ss);
if(satz0.Menge1() <= 0)
    {
    strBuch = strBuch.Mid(1);
    m_ctrlEditBuchungsMenge.SetWindowText(strBuch);
    m_ctrlEditBuchungsMenge.SetFocus();
    m_ctrlEditBuchungsMenge.SetSel(0,-1);  // Alles selektieren
    PlaySoundOther();
    return FALSE;
    }

m_ctrlEditLaenge.GetWindowText(ss.m_Laenge);
m_ctrlEditBreite.GetWindowText(ss.m_Breite);
m_ctrlEditFehlLaenge.GetWindowText(ss.m_FehlLaenge);
m_ctrlEditFehlBreite.GetWindowText(ss.m_FehlBreite);

ss.m_FehlNummer = GetComboFehler();
//m_ctrlEditFehlNummer.GetWindowText(ss.m_FehlNummer);

ss.m_Ende.Empty();

satz0.Set(ss);

satz0.m_buchungsNummer = NaechsteBuchungsnummer();
satz0.SetProduktionVerkauf(m_ProduktionVerkauf);
satz0.SetDatumZeit();

m_pAuftrag->AddPosition(satz0);
//CString strx;
//strx.Format(_T("Rueck %d"),satz0.m_buchungsNummer);
//AfxMessageBox(strx);
//////////////////////////////////////// neu 15.3.06
m_pSteinSaetze->SubSatz(satz0); // Menge 1 in Steinsätze verringern
////////////////////////////////////////
return TRUE;
}
//-----------------------------------------------------------------------------
BOOL CPositionen::NormalRueckbuchen() // nur produktion
{
if(!WerteOk())return FALSE;


CSteinSatz satz0;
int index = FindNumber(m_strAktuelleNummer);

if(index >= 0)
    satz0 = m_pSteinSaetze->SteinSatz(index);
else    // Neuen Satz erstellen (immer Rohplatte, da Rückbuchen nur bei Produktion mit Rohplatten vorkommt) 
    {
    satz0.SetNummer(m_strAktuelleNummer);
    for(int i = 0; i < m_ArtikelGruppen.GetCount(); i++)
        {
        if(m_ArtikelGruppen.IsRohPlattenGruppe(m_ArtikelGruppen.GetAt(i).m_key))
            {
            SSatz sx(satz0);
            sx.m_ArtikelGr = m_ArtikelGruppen.GetAt(i).m_key;
            satz0.Set(sx);
            break;
            }
        }
    }
SSatz ss(satz0);

m_ctrlEditLaenge.GetWindowText(ss.m_Laenge);
m_ctrlEditBreite.GetWindowText(ss.m_Breite);
m_ctrlEditFehlLaenge.GetWindowText(ss.m_FehlLaenge);
m_ctrlEditFehlBreite.GetWindowText(ss.m_FehlBreite);

//if(index < 0)   // Steinsatz nicht mehr im Bestand, Lager mit abfragen // bei Rückbuchen immer abfragen
//    {
    int lcurs = m_ctrlComboLager.GetCurSel();
    if((lcurs >= 0) && lcurs < m_LagerTabelle.GetSize())
        ss.m_Lager = m_LagerTabelle.GetAt(lcurs).m_key;
//    }

ss.m_FehlNummer = GetComboFehler();
//m_ctrlEditFehlNummer.GetWindowText(ss.m_FehlNummer);

CString strBuch;
m_ctrlEditBuchungsMenge.GetWindowText(strBuch);
if(m_ArtikelGruppen.IsRohPlattenGruppe(satz0.ArtikelGr()))  // Bei Rohplatten darf Rückbuchungsmenge nur 1 sein
    {
    if(CSteinSatz::StringToDouble(strBuch) != 1.0)
        {
        m_ctrlEditBuchungsMenge.SetFocus();
        PlaySoundError();
        return FALSE;
        }
    }
ss.m_Menge1 = _T("-") + strBuch;
if (m_bCheckRueck == TRUE )
	{
	if (m_bCheckRest == TRUE )
		{
		ss.m_RestKz = _T("1");
		}
	else
		{
		ss.m_RestKz = _T("0");
		}
	}
else
	{
	ss.m_RestKz = _T("");
	}
satz0.Set(ss);

if(NoValueSetFocus(strBuch,m_ctrlEditBuchungsMenge))
    return FALSE;
if(NoValueSetFocus(ss.m_Laenge,m_ctrlEditLaenge))
    return FALSE;
if(NoValueSetFocus(ss.m_Breite,m_ctrlEditBreite))
    return FALSE;
if(ss.m_Laenge.IsEmpty())
    {
    m_ctrlEditLaenge.SetFocus();
    m_ctrlEditLaenge.SetSel(0,-1);  // Alles selektieren
    PlaySoundOther();
    return FALSE;
    }
if(ss.m_Breite.IsEmpty())
    {
    m_ctrlEditBreite.SetFocus();
    m_ctrlEditBreite.SetSel(0,-1);  // Alles selektieren
    PlaySoundOther();
    return FALSE;
    }
if(satz0.Menge1() == 0 )
    {
    m_ctrlEditBuchungsMenge.SetFocus();
    m_ctrlEditBuchungsMenge.SetSel(0,-1);  // Alles selektieren
    PlaySoundOther();
    return FALSE;
    }
satz0.m_buchungsNummer = NaechsteBuchungsnummer();
satz0.SetProduktionVerkauf(m_ProduktionVerkauf);
satz0.SetDatumZeit();
//CString strx;
//strx.Format(_T("Rueck %d"),satz0.m_buchungsNummer);
//AfxMessageBox(strx);
///////////////////////////////////// ab 15.3.06
// ab 15.1.10
if((index >= 0) && m_ArtikelGruppen.IsRohPlattenGruppe(ss.m_ArtikelGr))
    {
    if(m_pSteinSaetze->SteinSatz(index).Menge1() <= 0)
        {
        m_pAuftrag->AddPosition(satz0); // hier ist menge negativ
        satz0.SetMenge1(-satz0.Menge1());   // bei Rückbuchen wird negative Masse im Auftrag verwendet
        m_pSteinSaetze->AddSatz(satz0); // Menge 1 in Steinsätze erhöhen oder Satz anfügen
        }
    else // Wenn Schon mit Menge vorhanden, muss beim Rückbuchen neuer satz angelegt werden
        {
        PlaySoundOther();
        CRueckZugang zug;
        zug.m_pSteinSaetze = m_pSteinSaetze;       // Original-Steinsatztabelle
        zug.m_pAuftraege = m_pAuftraege;
        zug.m_pAuftrag = m_pAuftrag;               // Auftrag der zu bearbeiten ist
        zug.m_pScanner = m_pScanner;
        zug.m_pSatz = &satz0;
        if(zug.DoModal() == IDOK)
            {
            m_pAuftrag->AddPosition(satz0);
            satz0.SetMenge1(-satz0.Menge1());   // bei Rückbuchen wird negative Masse im Auftrag verwendet
            m_pSteinSaetze->AddSatz(satz0); // Menge 1 in Steinsätze erhöhen oder Satz anfügen
            }
        else
            return FALSE;
        }
    }
else
    {
    m_pAuftrag->AddPosition(satz0);
    satz0.SetMenge1(-satz0.Menge1());   // bei Rückbuchen wird negative Masse verwendet
    m_pSteinSaetze->AddSatz(satz0); // Menge 1 in Steinsätze erhöhen oder Satz anfügen
    }

if(index < 0)           // Neuer Satz wurde hinzugefügt
    SetComboSteinSaetze();
///////////////////////////////////// 

m_ctrlComboLager.EnableWindow(FALSE);
m_ctrlEditLagerort.EnableWindow(FALSE);

RueckEnable(FALSE);

return TRUE;
}
//-----------------------------------------------------------------------------
int CPositionen::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
//-----------------------------------------------------------------------------
void CPositionen::OnSelchangeComboSteinnummer() 
{
m_nSetHinzu = 0;

int index = m_ctrlComboSteinSaetze.GetCurSel();

if(m_nModus == ID_GATTERN )
{
	CString nummer;
	m_ctrlComboSteinSaetze.GetLBText(index ,nummer);
	m_pSteinSaetze->FoundAt(nummer, index);
}

AnzeigePlattenDaten(index);	
m_hinzEnable = TRUE;

if(m_nModus == ID_INVENTUR)
{
	m_ctrlEditBuchungsMenge.SetWindowText(m_pSteinSaetze->SteinSatz(index).StrMenge1());
}	
else
    m_ctrlEditBuchungsMenge.SetWindowText(_T("1,00"));

m_ctrlEditBuchungsMenge.SetSel(0,-1,FALSE);  // Alles selektieren

}
//-----------------------------------------------------------------------------
// Alle Aufträge durchsuchen wegen höchster Nummer
int CPositionen::NaechsteBuchungsnummer() const
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
BOOL CPositionen::CheckLager(const CString& barCode)
{
int index = m_LagerTabelle.GetIndexByKey(barCode);
if(index >= 0)
    {
    PlaySoundScan();
    SetComboLager(barCode);
    return TRUE;
    }
return FALSE;
}
//-----------------------------------------------------------------------------
BOOL CPositionen::PreTranslateMessage(MSG* pMsg) 
{
CString errMsg;
m_nSetHinzu = 0;

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
    if(m_curFocus == LAGER)
        {
        if(CheckLager(barCode))
            return CDialog::PreTranslateMessage(pMsg);
        }

//    barCode.MakeUpper();

    if(g_Optionen.BoeseEnabled() && (m_nModus == ID_VERKAUF))
        {
        if(barCode.GetAt(0) == _T('X'))
            {
            barCode = barCode.Mid(1);
            m_nSetHinzu = 1;
            }
        }

    int index = FindNumber(barCode);
	
	// bei Inventur -  wenn nicht gefunden, prüfen, ob es den Eintrag mit Präfix "G" gibt. wenn ja, dann Steinnr um G ergänzen ch 28.11.2017
	if ((index < 0) && (m_nModus == ID_INVENTUR ) )
		{
		CString testGrabmal = _T("G") + barCode;
		index = FindNumber(testGrabmal);
		if (index >= 0)
			barCode = testGrabmal;
		}
 
    if(index >= 0)
        PlaySoundScan();
    else
        PlaySoundOther();
    m_hinzEnable = TRUE;


    AnzeigePlattenDaten(index);       // Wenn index < 0 oder ungültig, werden alle Felder geleert
                                  // und der gelesene Barcode wird angezeigt

    m_strAktuelleNummer = barCode;

    if(m_nSetHinzu)
        m_strAktuelleNummer = _T("X") + m_strAktuelleNummer;

    SetDlgItemText(IDC_COMBO_STEINNUMMER,m_strAktuelleNummer);

    m_ctrlEditBuchungsMenge.SetFocus();
    if((index >= 0) && (m_nModus == ID_INVENTUR))
        m_ctrlEditBuchungsMenge.SetWindowText(m_pSteinSaetze->SteinSatz(index).StrMenge1());
    else
        m_ctrlEditBuchungsMenge.SetWindowText(_T("1,00"));

    m_ctrlEditBuchungsMenge.SetSel(0,-1,FALSE);  // Alles selektieren

    if((index < 0) && (m_nModus == ID_INVENTUR))
        {
//      PlaySoundAdd();
//      m_hinzEnable = FALSE;
//      UpdateData(FALSE);
		m_pScanner->setEnableScanner(FALSE);
		int ret = DialogPlattenDefinition();
		m_pScanner->setEnableScanner(TRUE);
		if(ret)
			HinzuEnd(index);
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
int CPositionen::FindNumber(const CString& strAktuelleNummer) const
{
int index = -1;
CPositionen::m_pSteinSaetze->FoundAt(strAktuelleNummer,index);
if ((index > -1) && (m_nModus == ID_GATTERN))
//	if (!(m_ArtikelGruppen.IsRohBlockGruppe(m_pSteinSaetze->arr[index].ArtikelGr() )))
	if (m_pSteinSaetze->arr[index].Artikel() != _T("Block"))
		index = -1;
return index;
/*
for(int i = 0; i < m_ctrlComboSteinSaetze.GetCount(); i++)
    {
    CString strNum;
    m_ctrlComboSteinSaetze.GetLBText(i,strNum);
    if(!strAktuelleNummer.CompareNoCase(strNum))
        return i;
    }
return -1;
*/
}
//-----------------------------------------------------------------------------------
void CPositionen::RueckEnable(BOOL set)
{
if(set == TRUE)
    {
    m_bCheckRueck = TRUE;
    m_ctrlEditLaenge.EnableWindow(TRUE);
    m_ctrlEditBreite.EnableWindow(TRUE);
    m_ctrlEditLaenge.SetFocus();
    //int cursel;
    //GetDlgItemText(IDC_COMBO_STEINNUMMER,m_strAktuelleNummer);  // UpdateData(TRUE) reicht nicht
    //if(m_pSteinSaetze->FoundAt(m_strAktuelleNummer,cursel))
    //    {
    //    if(m_pSteinSaetze->SteinSatz(cursel).Menge1() > 0)  // Dann wird neue Nummer erfragt
    //        m_ctrlComboLager.EnableWindow();
    //    else
    //        m_ctrlComboLager.EnableWindow(FALSE);
    //    }
    //else
        m_ctrlComboLager.EnableWindow();
		m_ctrlEditLagerort.EnableWindow();
	m_ctrlCheckRest.EnableWindow(TRUE);
	m_bCheckRest = FALSE;
    }
else
    {
    m_bCheckRueck = FALSE;
    m_ctrlEditLaenge.EnableWindow(FALSE);
    m_ctrlEditBreite.EnableWindow(FALSE);
	m_ctrlCheckRest.EnableWindow(FALSE);
	m_bCheckRest = FALSE;
    }
m_ctrlCheckRueck.SetCheck(m_bCheckRueck);
m_ctrlCheckRest.SetCheck(m_bCheckRest);

}
//-----------------------------------------------------------------------------------
void CPositionen::OnCheckRueck() 
{
if(m_ctrlCheckRueck.GetCheck())
    RueckEnable(TRUE);
else
	RueckEnable(FALSE);
m_hinzEnable = TRUE;
}
//-----------------------------------------------------------------------------------
void CPositionen::OnCheckRest() 
{
	m_bCheckRest = m_ctrlCheckRest.GetCheck();
}
//------------------------------------------------------------------------------------------
void CPositionen::OnStaticArtikelText()
{
CString str;
m_ctrlStaticArtikelText.GetWindowText(str);
MessageBox(str);
}
//------------------------------------------------------------------------------------------
BOOL CPositionen::WerteOk()
{
CString str;
m_ctrlEditBuchungsMenge.GetWindowText(str);
if(NoValueSetFocus(str,m_ctrlEditBuchungsMenge))
    return FALSE;
m_ctrlEditLaenge.GetWindowText(str);
if(NoValueSetFocus(str,m_ctrlEditLaenge))
    return FALSE;
m_ctrlEditBreite.GetWindowText(str);
if(NoValueSetFocus(str,m_ctrlEditBreite))
    return FALSE;
m_ctrlEditFehlLaenge.GetWindowText(str);
if(NoValueSetFocus(str,m_ctrlEditFehlLaenge))
    return FALSE;
m_ctrlEditFehlBreite.GetWindowText(str);
if(NoValueSetFocus(str,m_ctrlEditFehlBreite))
    return FALSE;
// prüfen, ob FehlLae UND FehlBreite gefüllt sind. Wenn nur eines der Felder gefüllt ist, dann Focus auf entsprechende Feld  ch 14.02.2013
BOOL bFehlLae = FALSE;
BOOL bFehlBr = FALSE;
m_ctrlEditFehlLaenge.GetWindowText(str);
if (!str.IsEmpty() || str.GetLength() > 0)
	bFehlLae = TRUE;
m_ctrlEditFehlBreite.GetWindowText(str);
if (!str.IsEmpty() || str.GetLength() > 0)
	bFehlBr = TRUE;
if (bFehlLae && !bFehlBr)
{
	m_ctrlEditFehlBreite.SetFocus();
    PlaySoundError();
	return FALSE;
}
if (!bFehlLae && bFehlBr)
{
	m_ctrlEditFehlLaenge.SetFocus();
    PlaySoundError();
	return FALSE;
}

return TRUE;
}
//------------------------------------------------------------------------------------------
void CPositionen::SetComboLager(const CString& strLagerKey)
{
//m_ctrlComboLager.EnableWindow();

int index = -1;
if(!strLagerKey.IsEmpty())
    index = m_LagerTabelle.GetIndexByKey(strLagerKey);

if(index >= 0)
    {
    m_ctrlComboLager.SetCurSel(index);
    CString str;
    str.Format(_T("%s %s"),m_LagerTabelle.GetAt(index).m_key,m_LagerTabelle.GetAt(index).m_bez);
    m_ctrlComboLager.SetWindowText(str);
    }
else
    {
    m_ctrlComboLager.SetCurSel(-1);
//    m_ctrlComboLager.SetWindowText(_T(""));
    }
}
//------------------------------------------------------------------------------------------
void CPositionen::SetComboFehler(const CString& strKey)
{
int index = -1;
index = m_FehlerTabelle.GetIndexByKey(strKey);

if((index < 0) || (index >= m_ctrlComboFehler.GetCount()))
    return;   // kann nicht sein

m_ctrlComboFehler.SetCurSel(index);
}
//------------------------------------------------------------------------------------------
CString CPositionen::GetComboFehler()
{
CString strf;
int ix = m_ctrlComboFehler.GetCurSel();
if((ix >= 0) && (ix < m_FehlerTabelle.GetCount()))
    return m_FehlerTabelle.GetAt(ix).m_key;
return _T("");
}
//------------------------------------------------------------------------------------------
// Zugang-Dialog
BOOL CPositionen::DialogPlattenDefinition()
{

CPlattenZugang zugang(this);

zugang.m_nModus = m_nModus;
zugang.m_pSteinSaetze = m_pSteinSaetze;       // Original-Steinsatztabelle
zugang.m_pAuftraege = m_pAuftraege;
zugang.m_pAuftrag = m_pAuftrag;
zugang.m_pScanner = m_pScanner;

SSatz ss;
m_ctrlComboSteinSaetze.GetWindowText(ss.m_Nummer);
ss.m_ME1 = _T("Stk");
ss.m_Menge1 = _T("1,00");
ss.m_Laenge = _T("100,0");
ss.m_Breite = _T("100,0");
ss.m_Dicke = _T("3,0");

g_baseSteinSatz.Set(ss);

// ch 12.11.2018 - Neues Kennzeichen für die Erfassung von Inventur-Platten ohne angabe von Material, Ofl, usw - mit Standard-Werten
if ( !g_Optionen.InventurPlattenOhneZusatzdatenErfassenEnabled () ) 
	{
	if(zugang.DoModal() != IDOK)
		return FALSE;
	}
else 
	{
	if(AfxMessageBox(Sprache(_T("Unbekannte Steinnnummer - Hinzufügen?")),MB_YESNO|MB_ICONQUESTION)
                     == IDNO)
		return FALSE;
	}
g_baseSteinSatz.SetDatumZeit();
g_baseSteinSatz.m_buchungsNummer = NaechsteBuchungsnummer();


m_pAuftrag->AddPosition(g_baseSteinSatz);

SSatz s(g_baseSteinSatz);

m_ctrlEditLaenge.SetWindowText(s.m_Laenge);
m_ctrlEditBreite.SetWindowText(s.m_Breite);
m_ctrlStaticDickeText.SetWindowText(s.m_Dicke);
m_ctrlStaticHinweisText.SetWindowText(s.m_Hinweis);
m_ctrlEditFehlLaenge.SetWindowText(s.m_FehlLaenge);
m_ctrlEditFehlBreite.SetWindowText(s.m_FehlBreite);
SetComboFehler(s.m_FehlNummer);
//m_ctrlEditFehlNummer.SetWindowText(s.m_FehlNummer);
m_ctrlEditBuchungsMenge.SetWindowText(s.m_Menge1);
m_ctrlStaticME1.SetWindowText(s.m_ME1);
m_ctrlStaticME2.SetWindowText(_T(""));
m_ctrlStaticArtikelText.SetWindowText(_T(""));
m_ctrlStaticMaterialText.SetWindowText(s.m_Material);
m_ctrlStaticOberflaecheText.SetWindowText(s.m_Oberflaeche);

return TRUE;
}
//-------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
/*
void CPositionen::SetPVButtons(const CString& strPV)
{
CButton *pBtnP = (CButton*)GetDlgItem(IDC_RADIO_P);
CButton *pBtnV = (CButton*)GetDlgItem(IDC_RADIO_V);
CButton *pBtnA = (CButton*)GetDlgItem(IDC_RADIO_A);
if(!pBtnP || !pBtnV || !pBtnA)
    {
    AfxMessageBox(_T("Radiobuttons fehlen!"));
    return;
    }
if(strPV == _T("P"))
    {
    pBtnP->SetCheck(1);
    pBtnV->SetCheck(0);
    pBtnA->SetCheck(0);
    return;
    }
if(strPV == _T("V"))
    {
    pBtnP->SetCheck(0);
    pBtnV->SetCheck(1);
    pBtnA->SetCheck(0);
    return;
    }
if(strPV == _T("A"))
    {
    pBtnP->SetCheck(0);
    pBtnV->SetCheck(0);
    pBtnA->SetCheck(1);
    return;
    }
pBtnP->DestroyWindow(); // Radiobuttons ausblenden
pBtnV->DestroyWindow();
pBtnA->DestroyWindow();
}
//-----------------------------------------------------------------------------------------
void CPositionen::OnRadioP() 
{
m_ProduktionVerkauf = _T("P"); // nichts oder Produktion"P" oder Verkauf "V"
}
//-----------------------------------------------------------------------------------------
void CPositionen::OnRadioV() 
{
m_ProduktionVerkauf = _T("V");
}
//-----------------------------------------------------------------------------------------
void CPositionen::OnRadioA() 
{
m_ProduktionVerkauf = _T("A");
}
*/


//-----------------------------------------------------------------------------------------
void CPositionen::OnSetfocusComboLager() 
{
m_curFocus = LAGER;
}
//-----------------------------------------------------------------------------------------
void CPositionen::OnKillfocusComboLager() 
{
m_curFocus = NUMMER;
}
//-----------------------------------------------------------------------------------------
// Wenn Steinnummer manuell geändert wird, sofort die Daten aktualisieren (falls Nummer nicht im Lagerbestand, Datenfelder leeren)
void CPositionen::OnEditchangeComboSteinnummer() 
{
int cursel = -1;
m_ctrlComboSteinSaetze.GetWindowText(m_strAktuelleNummer);
if(m_pSteinSaetze->FoundAt(m_strAktuelleNummer,cursel))
    {
    AnzeigePlattenDaten(cursel);
	if(m_nModus == ID_INVENTUR)
        m_ctrlEditBuchungsMenge.SetWindowText(m_pSteinSaetze->SteinSatz(cursel).StrMenge1());
    else
        m_ctrlEditBuchungsMenge.SetWindowText(_T("1,00"));
    }
else
    {
	CSteinSatz satz;
	AnzeigeTexte(satz);
	}
m_ctrlComboSteinSaetze.SetEditSel(-1,0);

}
//-------------------------------------------------------------------------------------
void CPositionen::OnEnKillfocusEditLaenge()
{
ValueExeed400(m_ctrlEditLaenge);
}
//-------------------------------------------------------------------------------------
void CPositionen::OnEnKillfocusEditBreite()
{
ValueExeed400(m_ctrlEditBreite);
}
//-------------------------------------------------------------------------------------
void CPositionen::OnEnKillfocusEditFehllaenge()
{
ValueExeed400(m_ctrlEditFehlLaenge);
}
//-------------------------------------------------------------------------------------
void CPositionen::OnEnKillfocusEditFehlbreite()
{
ValueExeed400(m_ctrlEditFehlBreite);
}

//-------------------------------------------------------------------------------------
void CPositionen::OnEnChangeEditPoslagerort()
{
	CString str;
	m_ctrlEditLagerort.GetWindowText(str);
	int ix_Lager;
	ix_Lager = m_LagerTabelle.GetIndexByKey (str);
	if (ix_Lager >= 0)
	{
		m_ctrlComboLager.SetCurSel(ix_Lager);
		m_ctrlEditLagerort.SetWindowText(_T(""));
		PlaySoundAdd();
	}
}

//-------------------------------------------------------------------------------------
void CPositionen::OnBnClickedButtonBlockmasse()
{
	// Erstellt ch 16.12.2013
	int cursel = -1;
	CString strAktuelleNummer;
	m_ctrlComboSteinSaetze.GetWindowText(strAktuelleNummer);
	
	if(m_pSteinSaetze->FoundAt(strAktuelleNummer,cursel))
    {
		CBlockdaten AnzBlockdaten(this);
	
		AnzBlockdaten.m_pSteinSatz = m_pSteinSaetze->arr[cursel];

		m_pScanner->setEnableScanner(FALSE);
		AnzBlockdaten.DoModal();	
		m_pScanner->setEnableScanner(TRUE);

		if (AnzBlockdaten.m_modified)
		{
			SSatz s(AnzBlockdaten.m_pSteinSatz);
			m_ctrlEditLaenge.SetWindowText(s.m_Laenge);
			m_ctrlEditBreite.SetWindowText(s.m_Breite);
			m_ctrlStaticDickeText.SetWindowText(s.m_Dicke);

			m_bGeaendertBlockDaten = TRUE;
			m_GeaenderteBlockDaten.Set(s);
		}
	}

}
//-------------------------------------------------------------------------------------
void CPositionen::OnEnKillfocusEditBuchmenge()
{
	// Bei Inventur abfragem, ob die Menge korrekt ist, wenn sie mehr als 10x so hoch wie die ursprüngliche Menge ist.
	if (m_nModus == ID_INVENTUR )
	{
		CString sText;
		m_ctrlEditBuchungsMenge.GetWindowText(sText);
		if (!NoValue(sText) )
		{
			CString sText;
			m_ctrlEditBuchungsMenge.GetWindowText(sText);
			double dBuchMenge(CSteinSatz::StringToDouble (sText));

			m_ctrlStaticME1.GetWindowText(sText);
			double dBestMenge(CSteinSatz::StringToDouble (sText));

			if ( dBestMenge != 0 && dBuchMenge > dBestMenge * 10)
				if ( AfxMessageBox(Sprache(_T("Menge korrekt?")),MB_YESNO|MB_ICONQUESTION) == IDNO )
				{
					m_ctrlEditBuchungsMenge.SetWindowText( CSteinSatz::DoubleToString (dBestMenge) );
					m_ctrlEditBuchungsMenge.SetFocus();
					m_ctrlEditBuchungsMenge.SetSel(0,-1,FALSE);
				}	
	
		}
	}

}
