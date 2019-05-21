// Steinbruch.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "Steinbruch.h"
#include "EigenTabellen.h"
#include "PositionenInfo.h"
#include ".\VersionsConfig\_VersionsConfig.h"
#include "SteinbruchEmail.h"
#include "BloeckeVorabInfo.h"


// CSteinbruch-Dialogfeld

IMPLEMENT_DYNAMIC(CSteinbruch, CDialog)

CSteinbruch::CSteinbruch(CWnd* pParent /*=NULL*/)
	: CDialog(CSteinbruch::IDD, pParent)
{
m_modified = FALSE;
m_nummerSet = FALSE;
}

CSteinbruch::~CSteinbruch()
{
}

void CSteinbruch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_LAGERORT, m_ctrlStaticLagerort);
	DDX_Control(pDX, IDC_STATIC_GRUPPE, m_ctrlStaticMaterialgruppe);
	DDX_Control(pDX, IDC_STATIC_MATERIAL, m_ctrlStaticMaterial);
	DDX_Control(pDX, IDC_STATIC_NUMMER, m_ctrlStaticNummer);
	DDX_Control(pDX, IDC_STATIC_BLAETTERN, m_ctrlStaticBlaettern);
	DDX_Control(pDX, IDC_STATIC_SCHICHT, m_ctrlStaticSchicht);
	DDX_Control(pDX, IDC_STATIC_MASSEBRUTTO, m_ctrlStaticMasseBrutto);
	DDX_Control(pDX, IDC_STATIC_MASSENETTO, m_ctrlStaticMasseNetto);
	DDX_Control(pDX, IDC_STATIC_HINWEIS, m_ctrlStaticHinweis);
	DDX_Control(pDX, IDC_STATIC_FEHLER, m_ctrlStaticFehler);
	DDX_Control(pDX, IDC_COMBO_LAGERORT, m_ctrlComboLager);
	DDX_Control(pDX, IDC_COMBO_GRUPPE, m_ctrlComboGruppe);
	DDX_Control(pDX, IDC_COMBO_MATERIAL, m_ctrlComboMaterial);
	DDX_Control(pDX, IDC_COMBO_FEHLER, m_ctrlComboFehler);
	DDX_Control(pDX, IDC_EDIT_NUMMER, m_ctrlEditNummer);
	DDX_Control(pDX, IDC_EDIT_SCHICHT, m_ctrlEditSchicht);
	DDX_Control(pDX, IDC_EDIT_LAENGEBRUTTO, m_ctrlEditLaengeBrutto);
	DDX_Control(pDX, IDC_EDIT_BREITEBRUTTO, m_ctrlEditBreiteBrutto);
	DDX_Control(pDX, IDC_EDIT_DICKEBRUTTO, m_ctrlEditDickeBrutto);
	DDX_Control(pDX, IDC_EDIT_LAENGENETTO, m_ctrlEditLaengeNetto);
	DDX_Control(pDX, IDC_EDIT_BREITENETTO, m_ctrlEditBreiteNetto);
	DDX_Control(pDX, IDC_EDIT_DICKENETTO, m_ctrlEditDickeNetto);
	DDX_Control(pDX, IDC_EDIT_HINWEIS, m_ctrlEditHinweis);
	//DDX_Control(pDX, IDC_BUTTON_BACK, m_ctrlButtonBack);
	//DDX_Control(pDX, IDC_BUTTON_NEXT, m_ctrlButtonNext);
	DDX_Control(pDX, IDC_BUTTON_LOESCHEN, m_ctrlButtonLoeschen);
	DDX_Control(pDX, IDC_BUTTON_UEBERSICHT, m_ctrlButtonUebersicht);
	DDX_Control(pDX, IDC_BUTTON_HINZU, m_ctrlButtonHinzu);
	DDX_Control(pDX, IDC_BUTTON_NEU, m_ctrlButtonNeu);
	DDX_Control(pDX, IDC_STATIC_ARTIKEL2, m_ctrlStaticArtikelgruppe);
	DDX_Control(pDX, IDC_COMBO_ARTIKELGR, m_ctrlComboArtikelgruppen);
	DDX_Control(pDX, IDC_SPIN_NUMBER, m_ctrlSpinNumber);
	DDX_Control(pDX, IDC_EDIT_GEWICHT, m_ctrlEditGewicht);
	DDX_Control(pDX, IDC_STATIC_GEWICHT, m_ctrlStaticGewicht);
	DDX_Control(pDX, IDC_BUTTON_EMAIL, m_ctrlButtonEmail);
	DDX_Control(pDX, IDC_BUTTON_VORABINFO, m_ctrlButtonVorabInfo);
	DDX_Control(pDX, IDC_STATIC_KOSTEN, m_ctrlStaticKosten);
	DDX_Control(pDX, IDC_EDIT_KOSTEN, m_ctrlEditKosten);
	DDX_Control(pDX, IDC_STATIC_LIEFBLOCKNR, m_ctrlStaticNrLieferant);
	DDX_Control(pDX, IDC_EDIT_LIEFBLOCKNR, m_ctrlEditNrLieferant);
	DDX_Control(pDX, IDC_STATIC_LIEFERSCHEIN, m_ctrlStaticLieferschein);
	DDX_Control(pDX, IDC_EDIT_LIEFERSCHEIN, m_ctrlEditLieferschein);
	DDX_Control(pDX, IDC_STATIC_LIEFERSCHEINDATUM, m_ctrlStaticLieferscheinDatum);
	DDX_Control(pDX, IDC_EDIT_LIEFERSCHEINDATUM, m_ctrlEditLieferscheinDatum);
	DDX_Control(pDX, IDC_EDIT_LAGERORT, m_ctrlEditLagerort);
	DDX_Control(pDX, IDC_BUTTON_SUMME, m_ctrlButtonSumme);
}


BEGIN_MESSAGE_MAP(CSteinbruch, CDialog)
    ON_CBN_SELCHANGE(IDC_COMBO_LAGERORT, &CSteinbruch::OnCbnSelchangeComboLagerort)
    ON_CBN_SELCHANGE(IDC_COMBO_MATERIAL, &CSteinbruch::OnCbnSelchangeComboMaterial)
    ON_CBN_SELCHANGE(IDC_COMBO_GRUPPE, &CSteinbruch::OnCbnSelchangeComboGruppe)
    ON_BN_CLICKED(IDC_BUTTON_HINZU, &CSteinbruch::OnBnClickedButtonHinzu)
    ON_BN_CLICKED(IDC_BUTTON_NEU, &CSteinbruch::OnBnClickedButtonNeu)
    //ON_BN_CLICKED(IDC_BUTTON_BACK, &CSteinbruch::OnBnClickedButtonBack)
    //ON_BN_CLICKED(IDC_BUTTON_NEXT, &CSteinbruch::OnBnClickedButtonNext)
    ON_EN_CHANGE(IDC_EDIT_NUMMER, &CSteinbruch::OnEnChangeEditNummer)
    ON_BN_CLICKED(IDC_BUTTON_LOESCHEN, &CSteinbruch::OnBnClickedButtonLoeschen)
    ON_BN_CLICKED(IDC_BUTTON_UEBERSICHT, &CSteinbruch::OnBnClickedButtonUebersicht)
    ON_EN_CHANGE(IDC_EDIT_SCHICHT, &CSteinbruch::OnEnChangeEditSchicht)
    ON_EN_CHANGE(IDC_EDIT_LAENGEBRUTTO, &CSteinbruch::OnEnChangeEditLaengebrutto)
    ON_EN_CHANGE(IDC_EDIT_BREITEBRUTTO, &CSteinbruch::OnEnChangeEditBreitebrutto)
    ON_EN_CHANGE(IDC_EDIT_DICKEBRUTTO, &CSteinbruch::OnEnChangeEditDickebrutto)
    ON_EN_CHANGE(IDC_EDIT_LAENGENETTO, &CSteinbruch::OnEnChangeEditLaengenetto)
    ON_EN_CHANGE(IDC_EDIT_BREITENETTO, &CSteinbruch::OnEnChangeEditBreitenetto)
    ON_EN_CHANGE(IDC_EDIT_DICKENETTO, &CSteinbruch::OnEnChangeEditDickenetto)
    ON_EN_CHANGE(IDC_EDIT_HINWEIS, &CSteinbruch::OnEnChangeEditHinweis)
    ON_CBN_SELCHANGE(IDC_COMBO_FEHLER, &CSteinbruch::OnCbnSelchangeComboFehler)
    ON_CBN_SELCHANGE(IDC_COMBO_ARTIKELGR, &CSteinbruch::OnCbnSelchangeComboArtikelGr)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_NUMBER, &CSteinbruch::OnDeltaposSpinNumber)
    ON_BN_CLICKED(IDC_BUTTON_EMAIL, &CSteinbruch::OnBnClickedButtonEmail)
    ON_EN_CHANGE(IDC_EDIT_GEWICHT, &CSteinbruch::OnEnChangeEditGewicht)
	ON_BN_CLICKED(IDC_BUTTON_VORABINFO, &CSteinbruch::OnBnClickedButtonVorabinfo)
	ON_EN_CHANGE(IDC_EDIT_KOSTEN, &CSteinbruch::OnEnChangeEditKosten)
	ON_EN_CHANGE(IDC_EDIT_LIEFBLOCKNR, &CSteinbruch::OnEnChangeEditLiefblocknr)
	ON_EN_CHANGE(IDC_EDIT_LAGERORT, &CSteinbruch::OnEnChangeEditLagerort)
	ON_EN_KILLFOCUS(IDC_EDIT_LAENGEBRUTTO, &CSteinbruch::OnEnKillfocusEditLaengebrutto)
	ON_EN_KILLFOCUS(IDC_EDIT_BREITEBRUTTO, &CSteinbruch::OnEnKillfocusEditBreitebrutto)
	ON_EN_KILLFOCUS(IDC_EDIT_DICKEBRUTTO, &CSteinbruch::OnEnKillfocusEditDickebrutto)
	ON_BN_CLICKED(IDC_BUTTON_SUMME, &CSteinbruch::OnBnClickedButtonSumme)
END_MESSAGE_MAP()


// CSteinbruch-Meldungshandler
//-----------------------------------------------------------------------------
BOOL CSteinbruch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
TranslateStatic(m_ctrlStaticArtikelgruppe);
TranslateStatic(m_ctrlStaticLagerort);
TranslateStatic(m_ctrlStaticMaterialgruppe);
TranslateStatic(m_ctrlStaticMaterial);
TranslateStatic(m_ctrlStaticNummer);
m_ctrlStaticNummer.GetWindowText(m_strStaticNummer);
TranslateStatic(m_ctrlStaticBlaettern);
m_ctrlStaticBlaettern.GetWindowText(m_strStaticBlaettern);
TranslateStatic(m_ctrlStaticSchicht);
TranslateStatic(m_ctrlStaticMasseBrutto);
TranslateStatic(m_ctrlStaticMasseNetto);
TranslateStatic(m_ctrlStaticKosten);
TranslateStatic(m_ctrlStaticNrLieferant);
TranslateStatic(m_ctrlStaticHinweis);
TranslateStatic(m_ctrlStaticFehler);
TranslateStatic(m_ctrlStaticLieferschein);
TranslateStatic(m_ctrlStaticLieferscheinDatum);
TranslateButton(m_ctrlButtonNeu);
TranslateButton(m_ctrlButtonLoeschen);
TranslateButton(m_ctrlButtonUebersicht);
TranslateButton(m_ctrlButtonHinzu);
TranslateButton(m_ctrlButtonVorabInfo);

// Kostenfeld vorerst einmal komplett sperren, da die Mitarbeiter den Preis nicht sehen sollen ch 30.10.2012
// vielleicht später einmal durch einen Schalter freigeben.
m_ctrlStaticKosten.ShowWindow(FALSE);
m_ctrlEditKosten.ShowWindow(FALSE);


// einmal die nächste Buchungsnummer ermitteln und dann immer nur hochzählen
NaechsteBuchungsNummer = m_pAuftraege->NaechsteBuchungsnummer();

m_tabLagerMat.Read();
if(!m_tabLagerMat.GetCount())   // Lagertabelle muss sein
    {
    AfxMessageBox(Sprache(CString(_T("Lagertabelle ") + CString(DATEI_LAGERMAT) + _T("nicht vorhanden"))));
    return FALSE;
    }
m_tabArtikelGruppen.Read();
for(int i = m_tabArtikelGruppen.GetCount()-1; i >= 0; i--)  // Nur Blöcke (nachgestelltes B zulassen
    {
    CString key = m_tabArtikelGruppen.GetAt(i).m_key;
    if(key.GetAt(key.GetLength()-1) != _T('B'))
        m_tabArtikelGruppen.RemoveAt(i);
    }
m_tabMaterialGruppen.Read();
m_tabAlleMaterialArten.Read();
m_tabFehler.Read();
m_tabProgrammStatus.Read();

// Lesen der Block-Vorabdaten (als CSteinsaetze)
m_Vorabdaten.ReadFile(DATEI_VORABDATEN);

FillComboArtikelgruppen();      // einmalig
FillComboLager();       // einmalig
FillComboGruppen();     // einmalig

CString lastLagerKey = m_tabProgrammStatus.GetItemByKey(_T("LetzterSteinbruchKey")).m_value1;
SetComboLager(lastLagerKey);
//if(m_tabLagerMat.GetItemByKey(lastLagerKey).m_value2.IsEmpty())// Dem lager ist kein Material zugeordnet
//    {
//    C3String s3 = m_tabProgrammStatus.GetItemByKey(_T("LetzteMaterialGruppe"));
//    int ix = m_tabMaterialGruppen.GetIndexByKey(s3.m_value1);
//    if((ix > 0) && (ix < m_tabMaterialGruppen.GetCount()))
//        m_ctrlComboGruppe.SetCurSel(ix);
//    }

CString lastArtikelKey = m_tabProgrammStatus.GetItemByKey(_T("LetzterArtikelGruppenKey")).m_value1;
SetComboArtikelgruppen(lastArtikelKey);

FillComboFehler();

m_curBlockIndex = -1;

SetBlaettern();
m_ctrlSpinNumber.SetRange(0,1000);
//m_ctrlSpinNumber.SetBuddy(&m_ctrlEditNummer);

EnaDisa();

m_ctrlEditNummer.SetFocus();

if(g_Optionen.SteinbruchEmailDisabled())
    m_ctrlButtonEmail.ShowWindow(0);

if(g_Optionen.SteinbruchNettoGleichBruttoMasseEnabled() )
	{
	m_ctrlEditLaengeNetto.EnableWindow(FALSE);
	m_ctrlEditBreiteNetto.EnableWindow(FALSE);
	m_ctrlEditDickeNetto.EnableWindow(FALSE);
	}
if (!g_Optionen.SteinbruchTagessummeAnzeigenEnabled () ) 
	{
	m_ctrlButtonSumme.ShowWindow(0);
	}
else
	{
	CFont *m_Font1 = new CFont;
	m_Font1->CreatePointFont(85, _T("MS Shell Dlg"));
	m_ctrlButtonSumme.SetFont(m_Font1);
	}

return FALSE;  // return TRUE unless you set the focus to a control
}
//-----------------------------------------------------------------------------------
void CSteinbruch::FillComboArtikelgruppen()
{
for(int i = 0; i < m_tabArtikelGruppen.GetCount(); i++)
    {
    CString str;
    str.Format(_T("%s %s"),m_tabArtikelGruppen.GetAt(i).m_key,m_tabArtikelGruppen.GetAt(i).m_bez);
    m_ctrlComboArtikelgruppen.AddString(str);
    }
}
//-----------------------------------------------------------------------------------
void CSteinbruch::FillComboLager()
{
for(int i = 0; i < m_tabLagerMat.GetCount(); i++)
    {
    CString str;
    str.Format(_T("%s %s"),m_tabLagerMat.GetAt(i).m_key,m_tabLagerMat.GetAt(i).m_value1);
    m_ctrlComboLager.AddString(str);
	
	/* war nur mal ein Versuch - wird aber erstmal nicht realisiert ch 30.10.2012
	CString lager = m_tabLagerMat.GetAt(i).m_key;
	CString strAlpha = _T("");
	for(int x = 0; x < lager.GetLength(); x++)
		{
			if(iswalnum(lager.GetAt(x)))
				strAlpha = strAlpha + lager.GetAt(x);
			else
				x = lager.GetLength();
		}
	AfxMessageBox(strAlpha, 0,0);
	*/
    }
}
//-----------------------------------------------------------------------------------
void CSteinbruch::FillComboGruppen()
{
for(int i = 0; i < m_tabMaterialGruppen.GetCount(); i++)
    {
    CString str;
    str.Format(_T("%s %s"),m_tabMaterialGruppen.GetAt(i).m_key,m_tabMaterialGruppen.GetAt(i).m_bez);
    m_ctrlComboGruppe.AddString(str);
    }
}
//-----------------------------------------------------------------------------------
void CSteinbruch::FillComboFehler()
{
C2String s2;
m_tabFehler.InsertAt(0,s2); // Leerauswahl an den Anfang

for(int i = 0; i < m_tabFehler.GetSize(); i++)
    {
    m_ctrlComboFehler.AddString(m_tabFehler.GetAt(i).m_bez);
    }
m_ctrlComboFehler.SetCurSel(0);
}
//-----------------------------------------------------------------------------------
void CSteinbruch::SetComboArtikelgruppen(const CString& artikelkey)
{
int ix = m_tabArtikelGruppen.GetIndexByKey(artikelkey);
if(ix >= 0)
    {
    m_ctrlComboArtikelgruppen.SetCurSel(ix);
    }
}
//-----------------------------------------------------------------------------------
void CSteinbruch::SetComboLager(const CString& lagerkey)
{
int lagerIx = m_tabLagerMat.GetIndexByKey(lagerkey);
if(lagerIx >= 0)
    {
    m_ctrlComboLager.SetCurSel(lagerIx);
    SetComboMats(lagerIx);
    }
else
	m_ctrlComboLager.SetCurSel(-1);
}
//-----------------------------------------------------------------------------------
// Materialgruppe und Material nach Lageränderung setzen
void CSteinbruch::SetComboMats(int lagerIx)
{
CString groupKey;
if(lagerIx >= 0)
    groupKey = m_tabLagerMat.GetAt(lagerIx).m_value2;   // Gruppenkey, der dem Lager zugeordnet
int groupIx;
if(groupKey.IsEmpty())
    {
    m_ctrlComboGruppe.EnableWindow();
    // letzts verwendete Gruppe einstellen
    C3String s3 = m_tabProgrammStatus.GetItemByKey(_T("LetzteMaterialGruppe"));
    groupIx = m_tabMaterialGruppen.GetIndexByKey(s3.m_value1);
    groupIx = max(0,groupIx);
    }
else
    {   // Wenn Lager Materialgruppe zugeordnet, kann diese nicht in der Combobox geändert werden
    groupIx =  m_tabMaterialGruppen.GetIndexByKey(groupKey);
    m_ctrlComboGruppe.EnableWindow(FALSE);
    }
m_tabMaterialGruppen.m_curSelected = groupIx;
m_ctrlComboGruppe.SetCurSel(groupIx);

m_tabGruppeMaterialArten.SetGruppe(m_tabAlleMaterialArten,m_tabMaterialGruppen.Selected().m_key);

CString lastMatNr = m_tabProgrammStatus.GetItemByKey(_T("LetztesMaterialNr")).m_value1;
//AfxMessageBox(m_tabMaterialGruppen.Selected().m_key+lastMatKey);
m_tabGruppeMaterialArten.m_curSelected = m_tabGruppeMaterialArten.GetIndexByKey(m_tabMaterialGruppen.Selected().m_key,lastMatNr);

CString str;
m_tabGruppeMaterialArten.SetCombo(m_ctrlComboMaterial,str);

}
//------------------------------------------------------------------------------------------
void CSteinbruch::VorabDatenUebernehmen(const CString& blocknr)
{

	int index;
	m_Vorabdaten.FoundAt(blocknr,index);
	if (index >= 0)
	{
		
		SetBlockDaten(m_Vorabdaten.arr[index],FALSE);
		
		// Kennzeichen setzen, damit nach dem Speichern gefragt wird
		m_modified = TRUE;
	}

}
//------------------------------------------------------------------------------------------
void CSteinbruch::MaterialAusSatzAnzeigen(const CString& MatGrp, const CString& MatId)
{
	if (m_ctrlComboGruppe.IsWindowEnabled() )
	{
		int groupIx;
		groupIx = m_tabMaterialGruppen.GetIndexByKey(MatGrp);
		groupIx = max(0,groupIx);
		if (groupIx != m_tabMaterialGruppen.m_curSelected )
		{
			m_tabMaterialGruppen.m_curSelected = groupIx;
			m_ctrlComboGruppe.SetCurSel(groupIx);
		}
	}
			
	// Materialart richtig setzen
	m_tabGruppeMaterialArten.SetGruppe(m_tabAlleMaterialArten,m_tabMaterialGruppen.Selected().m_key);
	m_tabGruppeMaterialArten.m_curSelected = m_tabGruppeMaterialArten.GetIndexByKey(m_tabMaterialGruppen.Selected().m_key, MatId);
	CString str;
	m_tabGruppeMaterialArten.SetCombo(m_ctrlComboMaterial,str);
}
//------------------------------------------------------------------------------------------
void CSteinbruch::OnCbnSelchangeComboArtikelGr()
{
int cursel = m_ctrlComboArtikelgruppen.GetCurSel();

C3String s3;
s3.m_key = _T("LetzterArtikelGruppenKey");
int ix = m_tabProgrammStatus.GetIndexByKey(s3.m_key);
if(ix < 0)
    {
    s3.m_value1 = m_tabArtikelGruppen.GetAt(cursel).m_key; // Materialgruppe (key) des Lagers (Steinbruchs)
    m_tabProgrammStatus.Add(s3);
    }
else
    {
    m_tabProgrammStatus.GetAt(ix).m_value1 = m_tabArtikelGruppen.GetAt(cursel).m_key;
    }
m_tabProgrammStatus.Save();
m_modified = TRUE;
}
//------------------------------------------------------------------------------------------
void CSteinbruch::OnCbnSelchangeComboLagerort()
{
if(!g_Optionen.SteinbruchEmailDisabled())
{
	int cursel = m_ctrlComboLager.GetCurSel();
	SetComboMats(cursel);

	C3String s3;
	s3.m_key = _T("LetzterSteinbruchKey");
	int ix = m_tabProgrammStatus.GetIndexByKey(s3.m_key);
	if(ix < 0)
		{
		s3.m_value1 = m_tabLagerMat.GetAt(cursel).m_key; // Materialgruppe (key) des Lagers (Steinbruchs)
		m_tabProgrammStatus.Add(s3);
		}
	else
		{
		m_tabProgrammStatus.GetAt(ix).m_value1 = m_tabLagerMat.GetAt(cursel).m_key;
		}
	m_tabProgrammStatus.Save();
}
m_modified = TRUE;
}
//------------------------------------------------------------------------------------------
void CSteinbruch::OnCbnSelchangeComboMaterial()
{
C3String s3;
s3.m_key = _T("LetztesMaterialNr");
int ix = m_tabProgrammStatus.GetIndexByKey(s3.m_key);
int mix = max(m_ctrlComboMaterial.GetCurSel(),0);
if(ix < 0)
    {
    s3.m_value1 = m_tabGruppeMaterialArten.GetAt(mix).Key2(); // Materialnummer des Materials (ohne Gruppe)
    m_tabProgrammStatus.Add(s3);
    }
else
    {
    m_tabProgrammStatus.GetAt(ix).m_value1 = m_tabGruppeMaterialArten.GetAt(mix).Key2();
    }
m_tabProgrammStatus.Save();
m_modified = TRUE;
}
//------------------------------------------------------------------------------------------
void CSteinbruch::OnCbnSelchangeComboGruppe()
{
m_tabMaterialGruppen.m_curSelected = m_ctrlComboGruppe.GetCurSel();
C3String s3;
s3.m_key = _T("LetzteMaterialGruppe");
s3.m_value1 = m_tabMaterialGruppen.Selected().m_key;
int ptabix = m_tabProgrammStatus.GetIndexByKey(s3.m_key);
if(ptabix < 0)
    m_tabProgrammStatus.Add(s3);
else
    m_tabProgrammStatus.SetAt(ptabix,s3);

m_tabGruppeMaterialArten.SetGruppe(m_tabAlleMaterialArten,m_tabMaterialGruppen.Selected().m_key);

CString lastMatNr = m_tabProgrammStatus.GetItemByKey(_T("LetztesMaterialNr")).m_value1;
m_tabGruppeMaterialArten.m_curSelected = m_tabGruppeMaterialArten.GetIndexByKey(m_tabMaterialGruppen.Selected().m_key,lastMatNr);

CString str;
m_tabGruppeMaterialArten.SetCombo(m_ctrlComboMaterial,str);
m_modified = TRUE;
}
//------------------------------------------------------------------------------------------
BOOL CheckMasse(CString& str,CEdit& ctrlEdit,BOOL allowEmpty)
{
ctrlEdit.GetWindowText(str);
str.Trim();
if(str.IsEmpty())
    {
    if(allowEmpty)
        return TRUE;
    ctrlEdit.SetFocus();
    PlaySoundError();
    return FALSE;
    }
if(NoValueSetFocus(str,ctrlEdit))
    {
    PlaySoundError();
    return FALSE;
    }
return TRUE;
}
//------------------------------------------------------------------------------------------
void CSteinbruch::OnBnClickedButtonHinzu()
{
OnHinzu();
}
//------------------------------------------------------------------------------------------
BOOL CSteinbruch::OnHinzu()
{
SSatz ss;
int ueberIx = -1;
int oldBuchNr = -1;

CString str;
m_ctrlEditNummer.GetWindowText(str);
if(str.GetLength() > 15)
    {
    AfxMessageBox(Sprache(_T("Nummer darf max. 15 Zeichen lang sein!")));
    m_ctrlEditNummer.SetFocus();
    return FALSE;
    }
if(str.IsEmpty())
    {
    m_ctrlEditNummer.SetFocus();
    PlaySoundError();
    return FALSE;
    }
if(m_pAuftraege->Auftrag(0).m_Positionen.FoundAt(str,ueberIx))
    {
    if(AfxMessageBox(Sprache(_T("Nummer exisiert bereits, soll sie überschrieben werden?")),MB_YESNO) == IDNO)
        return FALSE;
    oldBuchNr = m_pAuftraege->Auftrag(0).m_Positionen.SteinSatz(ueberIx).m_buchungsNummer;
    }
ss.m_Nummer = str;

int artix = m_ctrlComboArtikelgruppen.GetCurSel();
if(artix < 0)
    {
    AfxMessageBox(Sprache(_T("Keine Artikelgruppe gewählt!")));
    return FALSE;
    }
C2String tempAgr = m_tabArtikelGruppen.GetAt(artix);
ss.m_ArtikelGr = tempAgr.m_key;
ss.m_ArtikelGrBez = tempAgr.m_bez;

if(m_ctrlComboLager.GetCurSel() < 0)
    {
    AfxMessageBox(Sprache(_T("Kein Lager gewählt!")));
    return FALSE;
    }
ss.m_Lager = m_tabLagerMat.GetAt(m_ctrlComboLager.GetCurSel()).m_key;
int mgix = m_ctrlComboGruppe.GetCurSel();
if(mgix >= 0)
    {
    ss.m_MatGr = m_tabMaterialGruppen.GetAt(mgix).m_key;
    int mix = m_ctrlComboMaterial.GetCurSel();
    if(mix >= 0)
        {
		C2String tempMat = m_tabGruppeMaterialArten.GetAt(mix);
        ss.m_MatNr = tempMat.Key2();
        ss.m_Material = tempMat.m_bez;
        }
    else
        {
        AfxMessageBox(Sprache(_T("Keine Material gewählt!")));
        return FALSE;
        }
    }
else
    {
    AfxMessageBox(Sprache(_T("Keine Materialgruppe gewählt!")));
    return FALSE;
    }
m_ctrlEditSchicht.GetWindowText(str);
str.Trim();
if(str.GetLength() > 2)
    {
    AfxMessageBox(Sprache(_T("Schicht ungültig (0..99)!")));
    m_ctrlEditSchicht.SetFocus();
    return FALSE;
    }
if(!str.IsEmpty())
    {
    TCHAR c = str.GetAt(0);
    TCHAR c1 = str.GetAt(str.GetLength()-1);
    if((c < 0x30) || (c > 0x39) || (c1 < 0x30) || (c1 > 0x39))
        {
        AfxMessageBox(Sprache(_T("Schicht ungültig (0..99)!")));
        m_ctrlEditSchicht.SetFocus();
        return FALSE;
        }
    }
ss.m_Schicht = str;

BOOL allowEmpt = FALSE;             // Bei Traco müssen Maße vorhanden sein
if(g_Optionen.SteinbruchMassCheckDisabled())   // Bei Sprimont können Maße weggelassen werden
    allowEmpt = TRUE;
    
if(!CheckMasse(str,m_ctrlEditLaengeNetto,allowEmpt))
    return FALSE;
ss.m_Laenge = str;
if(!CheckMasse(str,m_ctrlEditBreiteNetto,allowEmpt))
    return FALSE;
ss.m_Breite = str;
if(!CheckMasse(str,m_ctrlEditDickeNetto,allowEmpt))
    return FALSE;
ss.m_Dicke = str;

// Wenn Bruttowert da, dann prüfen
if(!CheckMasse(str,m_ctrlEditLaengeBrutto,TRUE))
    return FALSE;
ss.m_LaengeBrutto = str;
if(!CheckMasse(str,m_ctrlEditBreiteBrutto,TRUE))
    return FALSE;
ss.m_BreiteBrutto = str;
if(!CheckMasse(str,m_ctrlEditDickeBrutto,TRUE))
    return FALSE;
ss.m_DickeBrutto = str;
// Gewicht
if(!CheckMasse(str,m_ctrlEditGewicht,TRUE))
    return FALSE;
ss.m_Gewicht = str;

m_ctrlEditKosten.GetWindowText(str);
str.Trim();
ss.m_Preis = str;

m_ctrlEditNrLieferant.GetWindowText(str);
str.Trim();
ss.m_TextFeld = str;

int fix = m_ctrlComboFehler.GetCurSel();
C2String tempFehl = m_tabFehler.GetAt(fix);
ss.m_FehlNummer = tempFehl.m_key;
ss.m_FehlString = tempFehl.m_bez;

m_ctrlEditHinweis.GetWindowText(str);
ss.m_Hinweis = str;

m_ctrlEditLieferschein.GetWindowText(str);
ss.m_LieferscheinNummer = str;
m_ctrlEditLieferscheinDatum.GetWindowText(str);
if(!str.IsEmpty() && !CheckDatum(str ,ss.m_LieferscheinDatum))
   {
    AfxMessageBox(Sprache(_T("Falsches Datumformat!")));
    m_ctrlEditLieferscheinDatum.SetFocus();
    return FALSE;
    }

// Standard-Werte füllen für Lagerbestand (bei einem neuen Satz
if (ueberIx < 0)
{
	ss.m_Artikel = _T("Block");
	ss.m_ArtNr = _T("Block");
	ss.m_Menge1 = _T("1,00");
	ss.m_ME1 = Sprache(_T("Stk"));
}
// Kennzeichen, dass dieser Satz geändert wurde
ss.m_ResFuerAuftrag = _T("X");

CSteinSatz satz;
satz.Set(ss);
if(oldBuchNr >= 0)
    satz.m_buchungsNummer = oldBuchNr;
else
{
    satz.m_buchungsNummer = NaechsteBuchungsNummer;
	NaechsteBuchungsNummer = NaechsteBuchungsNummer + 1;
}

satz.SetDatumZeit();

if(ueberIx < 0)
    {
    m_pAuftraege->Auftrag(0).AddPosition(satz);
    m_curBlockIndex = m_pAuftraege->Auftrag(0).m_Positionen.Anzahl()-1;
    }
else
    {
    m_pAuftraege->Auftrag(0).m_Positionen.SteinSatz(ueberIx) = satz;
    m_curBlockIndex = ueberIx;
    }
// nur einmal beim Verlassen des Fensters speichern. Es wird nur ein entsprechender Schalter gesetzt. 
//m_pAuftraege->Save();
m_modifiedAuftraege = TRUE;

// Und jetzt noch prüfen, ob der Eintrag in der Korrektur-Datei schon vorhanden ist. Wenn nicht dazufügen ansonsten überschreiben.
int index_korr;
m_pAuftragBlockKorr->Auftrag(0).m_Positionen.FoundAt(satz.Nummer(),index_korr);
if (index_korr < 0)
	m_pAuftragBlockKorr->Auftrag(0).AddPosition(satz);
else
	m_pAuftragBlockKorr->Auftrag(0).m_Positionen.SteinSatz(index_korr) = satz;

PlaySoundAdd();

// zum Lagerbestand hinzufügen, damit der Block fürs Gattern wieder zur Verfügung steht ch 28.08.2012
// Bei Artikelgruppe muss das "B" (als Kennzeichen für "Block") entfernt werden.
CString artGrp = satz.ArtikelGr();
artGrp.Replace (_T("B"), _T(""));
satz.SetArtikelGr(artGrp);
m_pSteinSaetze->AddSatz(satz); // Menge 1 zu Steinsätze hinzufügen
m_pSteinSaetze->m_modified = TRUE;

SetNummerStern();
m_ctrlStaticNummer.SetFocus();
SetBlaettern();

EnaDisa();
m_modified = FALSE;

return TRUE;
}
//------------------------------------------------------------------------------------------#
BOOL CSteinbruch::CheckDatum(CString& strDatum,CString& strResult)
{
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
void CSteinbruch::OnBnClickedButtonNeu()
{
Neu(TRUE);
}
//------------------------------------------------------------------------------------------
void CSteinbruch::Neu(BOOL setNummer)
{
if(setNummer)
    {
    CString str;
    m_ctrlEditNummer.GetWindowText(str);
    if(!str.IsEmpty())
        {
        m_nummerSet = TRUE;
        m_ctrlEditNummer.SetWindowText(_T(""));
        }
    }
m_ctrlEditSchicht.SetWindowText(_T(""));
m_ctrlEditLaengeBrutto.SetWindowText(_T(""));
m_ctrlEditBreiteBrutto.SetWindowText(_T(""));
m_ctrlEditDickeBrutto.SetWindowText(_T(""));
m_ctrlEditLaengeNetto.SetWindowText(_T(""));
m_ctrlEditBreiteNetto.SetWindowText(_T(""));
m_ctrlEditDickeNetto.SetWindowText(_T(""));
m_ctrlEditGewicht.SetWindowText(_T(""));
m_ctrlEditKosten.SetWindowText(_T(""));
m_ctrlEditNrLieferant.SetWindowText(_T(""));
m_ctrlEditLieferschein.SetWindowText(_T(""));
m_ctrlEditLieferscheinDatum.SetWindowText(_T(""));
m_ctrlEditHinweis.SetWindowText(_T(""));
m_ctrlComboFehler.SetCurSel(0);

m_ctrlStaticNummer.SetWindowText(m_strStaticNummer);

//m_curBlockIndex = m_pAuftraege->Auftrag(0).m_Positionen.Anzahl();
m_curBlockIndex = -1;
SetBlaettern();
m_ctrlButtonHinzu.EnableWindow(FALSE);

if(!g_Optionen.SteinbruchEmailDisabled()&& setNummer)
	{
	CString strTest;
    m_ctrlEditNummer.GetWindowText(strTest);
	SetNaechsteBlocknr();
	}

EnaDisa();
m_ctrlEditNummer.SetFocus();
}
//------------------------------------------------------------------------------------------
void CSteinbruch::SetBlockDaten(const CSteinSatz& satz,BOOL setNummer)
{
SSatz ss(satz);
// Wenn der Satz aus den Vorabdaten kommt, dann hat die Artikelgruppe noch kein "B"
if(ss.m_ArtikelGr.Right(1) != _T("B"))
	ss.m_ArtikelGr = ss.m_ArtikelGr + _T("B");

SetComboArtikelgruppen(ss.m_ArtikelGr);
SetComboLager(ss.m_Lager);

// Prüfen bzw. Anzeige der Materialgruppe/Materialart aus dem anzuzeigenden Satz! ch 28.08.2012
MaterialAusSatzAnzeigen(ss.m_MatGr, ss.m_MatNr);

int matix = m_tabGruppeMaterialArten.GetIndexByKey(ss.m_MatGr,ss.m_MatNr);
m_ctrlComboMaterial.SetCurSel(matix);
int artix = m_tabArtikelGruppen.GetIndexByKey(ss.m_ArtikelGr);
m_ctrlComboArtikelgruppen.SetCurSel(artix);
if(setNummer)
    {
    CString st;
    m_ctrlEditNummer.GetWindowText(st);
    if(st.Compare(ss.m_Nummer))
        {
        m_nummerSet = TRUE;
        m_ctrlEditNummer.SetWindowText(ss.m_Nummer);
        }
    }
m_ctrlEditSchicht.SetWindowText(ss.m_Schicht);
m_ctrlEditLaengeBrutto.SetWindowText(ss.m_LaengeBrutto);
m_ctrlEditBreiteBrutto.SetWindowText(ss.m_BreiteBrutto);
m_ctrlEditDickeBrutto.SetWindowText(ss.m_DickeBrutto);
m_ctrlEditLaengeNetto.SetWindowText(ss.m_Laenge);
m_ctrlEditBreiteNetto.SetWindowText(ss.m_Breite);
m_ctrlEditDickeNetto.SetWindowText(ss.m_Dicke);
m_ctrlEditGewicht.SetWindowText(ss.m_Gewicht);
m_ctrlEditKosten.SetWindowText(ss.m_Preis);
m_ctrlEditNrLieferant.SetWindowText(ss.m_TextFeld);
m_ctrlEditHinweis.SetWindowText(ss.m_Hinweis);
int fix = m_tabFehler.GetIndexByKey(ss.m_FehlNummer);
fix = max(0,fix);
m_ctrlComboFehler.SetCurSel(fix);
m_ctrlEditLieferschein.SetWindowText(ss.m_LieferscheinNummer);
m_ctrlEditLieferscheinDatum.SetWindowText(FormatDatum(ss.m_LieferscheinDatum));
m_modified = FALSE;
}
//------------------------------------------------------------------------------------------
CString CSteinbruch::FormatDatum(CString &strDatum) 
{
	CString result = _T("");
	CString str(strDatum);

	if (!str.IsEmpty())
	{
		CString strDay;
		CString strMonth;
		CString strYear;
		int ix = str.Find(_T('.'));
		if(ix < 0)
			result = str.Left(2) + _T(".") + str.Mid(2,2) + _T(".") + str.Right(4);
		else
			result = str;
	}
	return result;
}

//------------------------------------------------------------------------------------------
void CSteinbruch::SetNummerStern()
{
m_ctrlStaticNummer.SetWindowText(m_strStaticNummer + _T("*"));
}
//------------------------------------------------------------------------------------------
void CSteinbruch::EraseNummerStern()
{
m_ctrlStaticNummer.SetWindowText(m_strStaticNummer);
}
//------------------------------------------------------------------------------------------
void CSteinbruch::SetBlaettern()
{
CString str;
if(m_curBlockIndex >= 0)
    str.Format(_T("%d/%d"),m_curBlockIndex+1,m_pAuftraege->Auftrag(0).m_Positionen.Anzahl());
else
    str.Format(_T("-/%d"),m_pAuftraege->Auftrag(0).m_Positionen.Anzahl());
if(!m_strStaticBlaettern.IsEmpty())
    str += _T(" ") + str;
m_ctrlStaticBlaettern.SetWindowText(m_strStaticBlaettern+str);
}
//------------------------------------------------------------------------------------------
void CSteinbruch::OnBnClickedButtonBack()
{
if(!m_pAuftraege->Auftrag(0).m_Positionen.Anzahl())
    return;
//if(m_curBlockIndex < 0)
//    return;
m_curBlockIndex--;
if(m_curBlockIndex < 0)
    m_curBlockIndex = m_pAuftraege->Auftrag(0).m_Positionen.Anzahl()-1;
m_curBlockIndex = max(0,m_curBlockIndex);
SetBlockDaten(m_pAuftraege->Auftrag(0).Position(m_curBlockIndex),TRUE);

SetNummerStern();
SetBlaettern();
EnaDisa();
}
//------------------------------------------------------------------------------------------
void CSteinbruch::OnBnClickedButtonNext()
{
if(!m_pAuftraege->Auftrag(0).m_Positionen.Anzahl())
    return;
m_curBlockIndex++;
if(m_curBlockIndex >  (m_pAuftraege->Auftrag(0).m_Positionen.Anzahl()-1))
    m_curBlockIndex = 0;
m_curBlockIndex = min(m_curBlockIndex,m_pAuftraege->Auftrag(0).m_Positionen.Anzahl()-1);
SetBlockDaten(m_pAuftraege->Auftrag(0).Position(m_curBlockIndex),TRUE);

SetNummerStern();
SetBlaettern();
EnaDisa();
}
//------------------------------------------------------------------------------------------
void CSteinbruch::EnaDisa()
{
CString str;
m_ctrlEditNummer.GetWindowText(str);
if(str.IsEmpty())
    {
    m_ctrlButtonLoeschen.EnableWindow(FALSE);
    m_ctrlButtonHinzu.EnableWindow(FALSE);
    }
else
    {
    m_ctrlButtonLoeschen.EnableWindow();
    m_ctrlButtonHinzu.EnableWindow();
    }
if(m_pAuftraege->Auftrag(0).m_Positionen.Anzahl())

    {
    m_ctrlButtonUebersicht.EnableWindow();
    //m_ctrlButtonBack.EnableWindow();
    //m_ctrlButtonNext.EnableWindow();
    }
else
    {
    m_ctrlButtonUebersicht.EnableWindow(FALSE);
    //m_ctrlButtonBack.EnableWindow(FALSE);
    //m_ctrlButtonNext.EnableWindow(FALSE);
    }
int ix_vorab;
if (!str.IsEmpty() && m_Vorabdaten.FoundAt(str, ix_vorab))
	{
	int ix_auftrag;
	m_pAuftraege->Auftrag(0).m_Positionen.FoundAt(str, ix_auftrag);
	if (ix_auftrag < 0)
		{
		VorabDatenUebernehmen(str);
		m_ctrlButtonVorabInfo.ShowWindow(TRUE);
		}
	}
else
	m_ctrlButtonVorabInfo.ShowWindow(FALSE);
}
//------------------------------------------------------------------------------------------
void CSteinbruch::OnEnChangeEditNummer()
{
if(m_nummerSet) // Nummer wurde durch Einstrag eines neuen Satzes geändert, dadurch wird Message ausgelöst
    {
    m_nummerSet = FALSE;
    return;
    }

CString str;
m_ctrlEditNummer.GetWindowText(str);
if(m_pAuftraege->Auftrag(0).m_Positionen.FoundAt(str,m_curBlockIndex))
    {
    SetBlockDaten(m_pAuftraege->Auftrag(0).m_Positionen.SteinSatz(m_curBlockIndex),FALSE);
    SetNummerStern();
    SetBlaettern();
    }
else
    {
    m_curBlockIndex = -1;
    EraseNummerStern();
    Neu(FALSE);
    }
EnaDisa();
m_modified = TRUE;
}
//------------------------------------------------------------------------------------------
void CSteinbruch::OnBnClickedButtonLoeschen()
{
int ix;
CString str;
m_ctrlEditNummer.GetWindowText(str);
if(m_pAuftraege->Auftrag(0).m_Positionen.FoundAt(str,ix))
    {
    if(AfxMessageBox(Sprache(_T("Satz wirklich löschen?")),MB_YESNO) == IDYES)
        {
		// In den Lagersätzen löschen  ch 28.08.2012
		int steinix;
		m_pSteinSaetze->FoundAt (str, steinix);
		if (steinix >= 0)
		{
			if(fabs(m_pAuftraege->Auftrag(0).Position(ix).Menge1() - m_pSteinSaetze->SteinSatz(steinix).Menge1()) < 0.01)
                m_pSteinSaetze->RemoveAt(steinix);
            else
                m_pSteinSaetze->SubSatz(m_pAuftraege->Auftrag(0).m_Positionen.arr[ix]); // Menge wieder aus Steinliste entfernen
			m_pSteinSaetze->m_modified = TRUE;
		}

		// und jetzt das eigentliche Löschen in den Blöcken
        m_pAuftraege->Auftrag(0).m_Positionen.RemoveAt(ix);
		// nur noch beim Verlassen des Fenster speichern. Es wird nur ein entsprechender Schalten gesetzt
        //m_pAuftraege->Save();
		m_modifiedAuftraege = TRUE;
		// und hier noch das löschen in der Korrektur-Datei (wenn er darin vorhanden ist)int index_korr;
		int index_korr;
		m_pAuftragBlockKorr->Auftrag(0).m_Positionen.FoundAt(str,index_korr);
		if (index_korr >= 0)
			m_pAuftragBlockKorr->Auftrag(0).m_Positionen.RemoveAt(index_korr) ;

        m_curBlockIndex = min(ix,m_pAuftraege->Auftrag(0).m_Positionen.Anzahl()-1);
        if(m_curBlockIndex >= 0)
            {
            EnaDisa();
            SetBlaettern();
            SetBlockDaten(m_pAuftraege->Auftrag(0).Position(m_curBlockIndex),TRUE);
            SetBlaettern();
            return;
            }
        Neu(TRUE);
        m_curBlockIndex = -1;
        SetBlaettern();
        }
    else
        return;
    }
}
//------------------------------------------------------------------------------------------
void CSteinbruch::OnBnClickedButtonUebersicht()
{
CPositionenInfo info(this);
info.m_pSaetze = &(m_pAuftraege->Auftrag(0).m_Positionen);
info.m_index = m_curBlockIndex;
info.m_index = max(0,min(m_curBlockIndex,m_pAuftraege->Auftrag(0).m_Positionen.Anzahl()-1));

m_pScanner->setEnableScanner(FALSE);
info.DoModal();
m_pScanner->setEnableScanner(TRUE);

}
//---------------------------------------------------------------------------------------
BOOL CSteinbruch::PreTranslateMessage(MSG* pMsg) 
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
    PlaySoundScan();

    m_ctrlEditNummer.SetWindowText(barCode);  // und der gelesene Barcode wird angezeigt
    m_ctrlEditNummer.SetFocus();
    int ix;
    if(m_pAuftraege->Auftrag(0).m_Positionen.FoundAt(barCode,ix))
        {
        m_curBlockIndex = ix;
        SetBlockDaten(m_pAuftraege->Auftrag(0).m_Positionen.SteinSatz(ix),TRUE);
        SetBlaettern();
        }
	EnaDisa();
    m_modified = TRUE;
	}
else
    {
    if(!errMsg.IsEmpty())
        AfxMessageBox(errMsg);
    }

return CDialog::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------------------
void CSteinbruch::OnOK()
{
CString str;
m_ctrlEditNummer.GetWindowText(str);
if(!str.IsEmpty())
    {
    int ix;
    if(!m_pAuftraege->Auftrag(0).m_Positionen.FoundAt(str,ix) || m_modified)
        {
        int retmsg = AfxMessageBox(Sprache(_T("Soll der aktuelle Eintrag gespeichert werden?")),MB_YESNOCANCEL);
        if(retmsg == IDYES)
            {
            if(!OnHinzu())
                return;
            }
        if(retmsg == IDCANCEL)
            return;
        }
    }

CDialog::OnOK();
}
//---------------------------------------------------------------------------------------
void CSteinbruch::OnEnChangeEditSchicht()
{
m_modified = TRUE;
}
//---------------------------------------------------------------------------------------
void CSteinbruch::OnEnChangeEditLaengebrutto()
{
m_modified = TRUE;			
}
//---------------------------------------------------------------------------------------
void CSteinbruch::OnEnChangeEditBreitebrutto()
{
m_modified = TRUE;
}
//---------------------------------------------------------------------------------------
void CSteinbruch::OnEnChangeEditDickebrutto()
{
m_modified = TRUE;
}
//---------------------------------------------------------------------------------------
void CSteinbruch::OnEnChangeEditLaengenetto()
{
m_modified = TRUE;
}
//---------------------------------------------------------------------------------------
void CSteinbruch::OnEnChangeEditBreitenetto()
{
m_modified = TRUE;
}
//---------------------------------------------------------------------------------------
void CSteinbruch::OnEnChangeEditDickenetto()
{
m_modified = TRUE;
}
//---------------------------------------------------------------------------------------
void CSteinbruch::OnEnChangeEditKosten()
{
	m_modified = TRUE;
}
//---------------------------------------------------------------------------------------
void CSteinbruch::OnEnChangeEditLiefblocknr()
{
	m_modified = TRUE;
}
//---------------------------------------------------------------------------------------
void CSteinbruch::OnEnChangeEditHinweis()
{
m_modified = TRUE;
}
//---------------------------------------------------------------------------------------
void CSteinbruch::OnCbnSelchangeComboFehler()
{
m_modified = TRUE;
}
//---------------------------------------------------------------------------------------
void CSteinbruch::OnEnChangeEditGewicht()
{
m_modified = TRUE;
}
//---------------------------------------------------------------------------------------
void CSteinbruch::OnDeltaposSpinNumber(NMHDR *pNMHDR, LRESULT *pResult)
{
LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

if(pNMUpDown->iDelta > 0)
    OnBnClickedButtonNext();
else
    OnBnClickedButtonBack();

*pResult = 0;
}
//---------------------------------------------------------------------------------------
void CSteinbruch::OnBnClickedButtonEmail()
{
CString str;
m_ctrlEditNummer.GetWindowText(str);
if(!str.IsEmpty())
    {
    int ix;
    if(!m_pAuftraege->Auftrag(0).m_Positionen.FoundAt(str,ix) || m_modified)
        {
        int retmsg = AfxMessageBox(Sprache(_T("Soll der aktuelle Eintrag gespeichert werden?")),MB_YESNOCANCEL);
        if(retmsg == IDYES)
            {
            if(!OnHinzu())
                return;
            }
        if(retmsg == IDCANCEL)
            return;
        }
    }
// Speichern der Blöcke vor Aufruf SteinbruchMail, da sonst die Datei leer ist.
if (m_modifiedAuftraege == TRUE)
{
	m_pAuftraege->Save();
	m_pAuftragBlockKorr->Save();
}

// Stand vormals vor und nach dem Erfassen
CSteinbruchEmail steinbruchemail;

steinbruchemail.m_pAuftraege = m_pAuftraege;
steinbruchemail.m_pAuftragBlockKorr = m_pAuftragBlockKorr;

steinbruchemail.m_pScanner = m_pScanner;

m_pScanner->setEnableScanner(TRUE);
// Email-Programm
steinbruchemail.DoModal();	

m_pScanner->setEnableScanner(TRUE);

// Beenden erzwingen
CDialog::OnOK();
}


//---------------------------------------------------------------------------------------
void CSteinbruch::OnBnClickedButtonVorabinfo()
{
	int uebernehmen = 0;
	CString blocknr;
	m_ctrlEditNummer.GetWindowText(blocknr);

	CBloeckeVorabInfo info(this);
	info.m_pSaetze = &m_Vorabdaten;
	info.m_pBlocknr = &blocknr;
	info.m_pUebernehmen = &uebernehmen;
	
	m_pScanner->setEnableScanner(FALSE);
	info.DoModal();
	m_pScanner->setEnableScanner(TRUE);

	if (uebernehmen == 1)
	{
		VorabDatenUebernehmen(blocknr);
	}
}

void CSteinbruch::OnEnChangeEditLagerort()
{
	CString str;
	m_ctrlEditLagerort.GetWindowText(str);
	int ix_Lager;
	ix_Lager = m_tabLagerMat.GetIndexByKey (str);
	if (ix_Lager >= 0)
	{
		m_ctrlComboLager.SetCurSel(ix_Lager);
		OnCbnSelchangeComboLagerort();
		m_ctrlEditLagerort.SetWindowText(_T(""));
		PlaySoundAdd();
	}
}

//------------------------------------------------------------------------------------------
void CSteinbruch::SetNaechsteBlocknr()
{

int anz = m_pAuftraege->Auftrag(0).m_Positionen.Anzahl();
if ( anz >= 1 )
	{
	int letzteNr = _wtoi(m_pAuftraege->Auftrag(0).m_Positionen.SteinSatz(anz - 1).Nummer());

	if (letzteNr > 0 )
		{
		CString naechsteNr;
		naechsteNr.Format( _T("%d"), letzteNr + 1);
		m_nummerSet = TRUE;
		m_ctrlEditNummer.SetWindowText( naechsteNr );
		// m_ctrlEditNummer.SetFocus ();
		m_ctrlEditNummer.SetSel(-1);
		}
	}
}
//------------------------------------------------------------------------------------------
void CSteinbruch::OnEnKillfocusEditLaengebrutto()
{
if(g_Optionen.SteinbruchNettoGleichBruttoMasseEnabled() )
	{
	CString str;
	m_ctrlEditLaengeBrutto.GetWindowText(str);
	m_ctrlEditLaengeNetto.SetWindowText(str);
	}
}

void CSteinbruch::OnEnKillfocusEditBreitebrutto()
{
if(g_Optionen.SteinbruchNettoGleichBruttoMasseEnabled() )
	{
	CString str;
	m_ctrlEditBreiteBrutto.GetWindowText(str);
	m_ctrlEditBreiteNetto.SetWindowText(str);
	}
}

void CSteinbruch::OnEnKillfocusEditDickebrutto()
{
if(g_Optionen.SteinbruchNettoGleichBruttoMasseEnabled() )
	{
	CString str;
	m_ctrlEditDickeBrutto.GetWindowText(str);
	m_ctrlEditDickeNetto.SetWindowText(str);
	}
}
//------------------------------------------------------------------------------------------
//void CSteinbruch::OnStnClickedStaticGewicht() - erster Test
//{
//if (g_Optionen.SteinbruchTagessummeAnzeigenEnabled () ) 
//	{
//	CTime time;
//	CString aktDatum;
//	time = CTime::GetCurrentTime();
//	aktDatum.Format(_T("%02d%02d%4d"),time.GetDay(),time.GetMonth(),time.GetYear());
//	CSteinSatz satz;    // Alle Felder leer
//	double men2 = 0;
//	int i;
//	for(i = 0; i < m_pAuftraege->Auftrag(0).m_Positionen.Anzahl(); i++)
//		{
//		satz = m_pAuftraege->Auftrag(0).m_Positionen.arr[i];
//		SSatz ss(m_pAuftraege->Auftrag(0).m_Positionen.arr[i]);
//		if (ss.m_Datum == aktDatum )
//			{
//			double l = satz.StringToDouble(ss.m_Laenge );
//			double b = satz.StringToDouble(ss.m_Breite );
//			double d = satz.StringToDouble(ss.m_Dicke );
//			men2 = men2 + ((l/100)*(b/100)*(d/100));
//			}
//		}
//	
//	CString str;
//	str.Format(_T("%.3f"),men2);
//	int n = str.Find(_T('.'));
//	if(n >= 0)
//		str.SetAt(n,_T(','));
//	AfxMessageBox(Sprache(_T("Summe der heute erfassten Blöcke:\n\n")) + str + _T(" m³"), MB_ICONASTERISK );
//	}
//}
void CSteinbruch::OnBnClickedButtonSumme()
{
CTime time;
CString aktDatum;
time = CTime::GetCurrentTime();
aktDatum.Format(_T("%02d%02d%4d"),time.GetDay(),time.GetMonth(),time.GetYear());
CSteinSatz satz;    // Alle Felder leer
double men2 = 0;
int i;
for(i = 0; i < m_pAuftraege->Auftrag(0).m_Positionen.Anzahl(); i++)
	{
	satz = m_pAuftraege->Auftrag(0).m_Positionen.arr[i];
	SSatz ss(m_pAuftraege->Auftrag(0).m_Positionen.arr[i]);
	if (ss.m_Datum == aktDatum )
		{
		double l = satz.StringToDouble(ss.m_Laenge );
		double b = satz.StringToDouble(ss.m_Breite );
		double d = satz.StringToDouble(ss.m_Dicke );
		men2 = men2 + ((l/100)*(b/100)*(d/100));
		}
	}

CString str;
str.Format(_T("%.3f"),men2);
int n = str.Find(_T('.'));
if(n >= 0)
	str.SetAt(n,_T(','));
AfxMessageBox(Sprache(_T("Summe der heute erfassten Blöcke:\n\n")) + str + _T(" m³"), MB_ICONASTERISK );
}
