// LagerUm.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "Verankerung.h"
#include "PreiseVerank.h"
#include "VerankStueckliste.h"
#include "LagerUm.h"

/////////////////////////////////////////////////////////////////////////////
// CLagerUm dialog

IMPLEMENT_DYNAMIC(CLagerUm, CDialog)

CLagerUm::CLagerUm(CWnd* pParent /*=NULL*/)
	: CDialog(CLagerUm::IDD, pParent)
{
    m_curFocus = 0;
    m_CurIndex = -1;
    m_bIsVerankStein = FALSE;    // Stein gehört zu einer Verankerung
    m_bBlink = FALSE;

}


void CLagerUm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_STEINSAETZE, m_ctrlStaticSteinsaetze);
	DDX_Control(pDX, IDC_STATIC_OBERFLAECHE_TEXT, m_ctrlStaticOberflaecheText);
	DDX_Control(pDX, IDC_STATIC_ME2V, m_ctrlStaticME2V);
	DDX_Control(pDX, IDC_STATIC_ME2, m_ctrlStaticME2);
	DDX_Control(pDX, IDC_STATIC_ME1V, m_ctrlStaticME1V);
	DDX_Control(pDX, IDC_STATIC_ME1, m_ctrlStaticME1);
	DDX_Control(pDX, IDC_STATIC_MATERIAL_TEXT, m_ctrlStaticMaterialText);
	DDX_Control(pDX, IDC_STATIC_LAENGE_TEXT, m_ctrlStaticLaengeText);
	DDX_Control(pDX, IDC_STATIC_DICKE_TEXT, m_ctrlStaticDickeText);
	DDX_Control(pDX, IDC_STATIC_BREITE_TEXT, m_ctrlStaticBreiteText);
	DDX_Control(pDX, IDC_STATIC_ARTIKEL_TEXT, m_ctrlStaticArtikelText);
	DDX_Control(pDX, IDC_STATIC_LAGERUMBUCHUNG, m_ctrlStaticLagerumbuchung);
	DDX_Control(pDX, IDC_STATIC_ARTIKEL, m_ctrlStaticArtikel);
	DDX_Control(pDX, IDC_STATIC_STEINNUMMER, m_ctrlStaticSteinnummer);
	DDX_Control(pDX, IDC_STATIC_MENGE, m_ctrlStaticMenge);
	DDX_Control(pDX, IDC_STATIC_VERFUEGBAR, m_ctrlStaticVerfuegbar);
	DDX_Control(pDX, IDC_STATIC_LAGER_ALT, m_ctrlStaticLagerAlt);
	DDX_Control(pDX, IDC_STATIC_LAGER_NEU, m_ctrlStaticLagerNeu);
	DDX_Control(pDX, IDC_STATIC_MATERIAL, m_ctrlStaticMaterial);
	DDX_Control(pDX, IDC_STATIC_OBERFLAECHE, m_ctrlStaticOberflaeche);
	DDX_Control(pDX, IDC_STATIC_DICKE, m_ctrlStaticDicke);
	DDX_Control(pDX, IDC_STATIC_LAENGE, m_ctrlStaticLaenge);
	DDX_Control(pDX, IDC_STATIC_BREITE, m_ctrlStaticBreite);
	DDX_Control(pDX, IDC_EDIT_LAGER_ALT, m_ctrlEditLagerAlt);
	DDX_Control(pDX, IDC_COMBO_LAGER_NEU, m_ctrlComboLagerNeu);
	DDX_Control(pDX, IDC_COMBO_STEINNUMMER, m_ctrlComboSteinnummern);
	DDX_Control(pDX, IDC_STATIC_HINWEIS1, m_ctrlStaticHinweis);
	DDX_Control(pDX, IDC_STATIC_HINWEIS1_TEXT, m_ctrlStaticHinweisText);
	DDX_Control(pDX, IDC_BUTTON_EINZEL, m_ctrlButtonEinzel);
	DDX_Control(pDX, IDC_EDIT_LAGERORT, m_ctrlEditLagerort);
	DDX_Control(pDX, IDC_STATIC_BISSTEINNUMMER, m_ctrlStaticBisSteinnummer);
	DDX_Control(pDX, IDC_COMBO_BISSTEINNUMMER, m_ctrlComboBisSteinnummern);
}


BEGIN_MESSAGE_MAP(CLagerUm, CDialog)

	ON_CBN_SELCHANGE(IDC_COMBO_STEINNUMMER, OnSelchangeComboSteinnummer)
	ON_CBN_KILLFOCUS(IDC_COMBO_STEINNUMMER, OnKillfocusComboSteinnummer)
	ON_CBN_SETFOCUS(IDC_COMBO_STEINNUMMER, OnSetfocusComboSteinnummer)
	ON_CBN_SETFOCUS(IDC_COMBO_LAGER_NEU, OnSetfocusComboLagerNeu)
	ON_CBN_SELENDOK(IDC_COMBO_LAGER_NEU, OnSelendokComboLagerNeu)
	ON_CBN_EDITCHANGE(IDC_COMBO_STEINNUMMER, OnEditchangeComboSteinnummer)
	ON_WM_TIMER()
    ON_BN_CLICKED(IDC_BUTTON_EINZEL, &CLagerUm::OnBnClickedButtonEinzel)
    ON_STN_CLICKED(IDC_STATIC_HINWEIS1_TEXT, &CLagerUm::OnStnClickedStaticHinweis1Text)
	ON_EN_CHANGE(IDC_EDIT_LAGERORT, &CLagerUm::OnEnChangeEditLagerort)
	ON_CBN_SETFOCUS(IDC_COMBO_BISSTEINNUMMER, &CLagerUm::OnCbnSetfocusComboBissteinnummer)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------------------
BOOL CLagerUm::OnInitDialog()
{
CDialog::OnInitDialog();

CenterWindow(GetDesktopWindow());	// center to the hpc screen

TranslateStatic(m_ctrlStaticLagerumbuchung);
TranslateStatic(m_ctrlStaticArtikel);
TranslateStatic(m_ctrlStaticSteinnummer);
TranslateStatic(m_ctrlStaticBisSteinnummer);
TranslateStatic(m_ctrlStaticMenge);
TranslateStatic(m_ctrlStaticVerfuegbar);
TranslateStatic(m_ctrlStaticLagerAlt);
TranslateStatic(m_ctrlStaticLagerNeu);
TranslateStatic(m_ctrlStaticMaterial);
TranslateStatic(m_ctrlStaticOberflaeche);
TranslateStatic(m_ctrlStaticDicke);
TranslateStatic(m_ctrlStaticLaenge);
TranslateStatic(m_ctrlStaticBreite);
TranslateStatic(m_ctrlStaticHinweis);
TranslateButton(m_ctrlButtonEinzel);

m_tabLagerOrte.Read();

m_ctrlButtonEinzel.GetWindowText(m_strEinzelAnsicht);

CString str;
str.Format(_T("%d %s"),m_pSteinSaetze->Anzahl(),Sprache(_T("Steinsätze")));
m_ctrlStaticSteinsaetze.SetWindowText(str);

int i;
for(i = 0; i < m_pSteinSaetze->Anzahl(); i++)
    {
    m_ctrlComboSteinnummern.AddString(m_pSteinSaetze->SteinSatz(i).Nummer());
	m_ctrlComboBisSteinnummern.AddString(m_pSteinSaetze->SteinSatz(i).Nummer());
    }

for(i = 0; i < m_tabLagerOrte.GetSize(); i++)
    {
    CString str;
    str.Format(_T("%s %s"),m_tabLagerOrte.GetAt(i).m_key,m_tabLagerOrte.GetAt(i).m_bez);
    m_ctrlComboLagerNeu.AddString(str);
    }
//m_ctrlComboLagerNeu.AddString(_T(""));

m_ctrlButtonEinzel.ShowWindow(0);

// die erste Platte soll NICHT mehr automatisch ausgewählt werden ch 06.03.2013
AnzeigePlattenDaten(-1);
//if(m_pSteinSaetze->Anzahl())
//    AnzeigePlattenDaten(0); // Setzt Platte und Lager auf aktuelle Platte

// Kommentiert, da sonst eine Endlosschleife durch die Funktion "OnKillfocusComboSteinnummer" entsteht und der Focus eigentlich immer auf der Steinnr liegt ch 06.03.2013
// m_ctrlComboSteinnummern.SetFocus();

m_curFocus = NUMMER;

UpdateData(FALSE);
return TRUE;  // return TRUE  unless you set the focus to a control
}
//---------------------------------------------------------------------------------------
void CLagerUm::AnzeigePlattenDaten(int index)
{
CSteinSatz satz;    // Alle Felder leer

m_CurIndex = -1;
if((index >= 0) && (index < m_pSteinSaetze->Anzahl()))
    {
    satz = m_pSteinSaetze->arr[index];
    m_ctrlComboSteinnummern.SetCurSel(index);
    m_CurIndex = index;
    }

m_ctrlEditLagerAlt.SetWindowText(_T(""));
int lix = CLagerUm::m_tabLagerOrte.GetIndexByKey(satz.Lager());
if(lix >= 0)
    m_ctrlEditLagerAlt.SetWindowText(m_tabLagerOrte.GetAt(lix).m_key + _T(" ") + m_tabLagerOrte.GetAt(lix).m_bez);

AnzeigeLager(lix);


KillTimer(12);
m_bIsVerankStein = FALSE;
m_bBlink = FALSE;   // syncronisierung

int aix = -1;
if(m_pVerankerungen->FindeSteinNummer(satz.Nummer(),m_CurVerank,aix))  // Stein gehört zu einer verankerung
    {
    m_ctrlButtonEinzel.ShowWindow(1);
    //CString st;
    //st.Format(_T("Verank: %s"),m_CurVerank.m_Name);
    m_ctrlButtonEinzel.SetWindowText(m_strEinzelAnsicht);
    m_bIsVerankStein = TRUE;
    SetTimer(12,500,NULL);
	// bisSteinnr muss in diesem Fall ausgeschaltet werden
	m_ctrlComboBisSteinnummern.SetWindowText(_T(""));
	m_ctrlComboBisSteinnummern.ShowWindow(0);
	m_ctrlStaticBisSteinnummer.ShowWindow(0);
    }
else
	{
    m_ctrlButtonEinzel.ShowWindow(0);
	// bisSteinnr kann wieder angezeigt werden.
	m_ctrlComboBisSteinnummern.ShowWindow(1);
	m_ctrlStaticBisSteinnummer.ShowWindow(1);
	}
// muss nach Verankerungsprüfung stehen
SetTexte(satz);
}
//---------------------------------------------------------------------------------------
void CLagerUm::SetTexte(const CSteinSatz& satz)
{
SSatz ss(satz);

m_ctrlStaticLaengeText.SetWindowText(ss.m_Laenge);
m_ctrlStaticDickeText.SetWindowText(ss.m_Dicke);
m_ctrlStaticBreiteText.SetWindowText(ss.m_Breite);
if(m_bIsVerankStein)
    m_ctrlStaticHinweisText.SetWindowText(m_CurVerank.m_Hinweis);
else
    m_ctrlStaticHinweisText.SetWindowText(ss.m_Hinweis);

m_ctrlStaticME1.SetWindowText(ss.m_Menge1 + _T(" ") + ss.m_ME1);
if(satz.Menge2() != 0.)
    m_ctrlStaticME2.SetWindowText(ss.m_Menge2 + _T(" ") + ss.m_ME2);
else
    m_ctrlStaticME2.SetWindowText(_T(""));

m_ctrlStaticME1V.SetWindowText(ss.m_Menge1Verfuegbar + _T(" ") + ss.m_ME1);
if(satz.Menge2Verfuegbar() != 0.)
    m_ctrlStaticME2V.SetWindowText(ss.m_Menge2Verfuegbar + _T(" ") + ss.m_ME2);
else
    m_ctrlStaticME2V.SetWindowText(_T(""));

m_ctrlStaticArtikelText.SetWindowText(ss.m_Artikel);
m_ctrlStaticMaterialText.SetWindowText(ss.m_Material);
m_ctrlStaticOberflaecheText.SetWindowText(ss.m_Oberflaeche);
}
//---------------------------------------------------------------------------------------
BOOL CLagerUm::AnzeigeLager(int index)
{
if((index >= 0) && (index < m_tabLagerOrte.GetSize()))
    {
//    m_ctrlComboLagerNeu.SetWindowText(m_tabLagerOrte.GetAt(index).m_key + _T(" ") + m_tabLagerOrte.GetAt(index).m_bez);
    m_ctrlComboLagerNeu.SetCurSel(index);
    return TRUE;
    }
else
    m_ctrlComboLagerNeu.SetWindowText(_T(""));

return FALSE;
}
//---------------------------------------------------------------------------------------
// CLagerUm message handlers
void CLagerUm::OnSelchangeComboSteinnummer() 
{
int index = m_ctrlComboSteinnummern.GetCurSel();
AnzeigePlattenDaten(index);
}
//---------------------------------------------------------------------------------------
void CLagerUm::OnKillfocusComboSteinnummer() 
{
CString strSteinnummer;
m_ctrlComboSteinnummern.GetWindowText(strSteinnummer);

int ix;
if(!m_pSteinSaetze->FoundAt(strSteinnummer,ix))	
    {
    PlaySoundError();
    AfxMessageBox(Sprache(_T("Steinnummer ungültig!")),MB_OK|MB_ICONEXCLAMATION);
    m_ctrlComboSteinnummern.SetFocus();
    }
}
//---------------------------------------------------------------------------------------
void CLagerUm::OnSetfocusComboSteinnummer() 
{
m_curFocus = NUMMER;	
}
//---------------------------------------------------------------------------------------
void CLagerUm::OnSetfocusComboLagerNeu() 
{
m_curFocus = LAGER;	
}
//---------------------------------------------------------------------------------------
// Zuerst auf Nummer dann auf Lager prüfen
BOOL CLagerUm::CheckNummer(const CString& barCode)
{
int index;
if(m_pSteinSaetze->FoundAt(barCode,index))
    {
    PlaySoundScan();
    AnzeigePlattenDaten(index);
    return TRUE;
    }
return FALSE;
}
BOOL CLagerUm::CheckBisNummer(const CString& barCode)
{
int index;
if(m_pSteinSaetze->FoundAt(barCode,index))
    {
	 m_ctrlComboBisSteinnummern.SetCurSel(index);
    PlaySoundScan();
    return TRUE;
    }
return FALSE;
}
//---------------------------------------------------------------------------------------
// Zuerst auf Nummer dann auf Lager prüfen
BOOL CLagerUm::CheckLager(const CString& barCode)
{
int index = m_tabLagerOrte.GetIndexByKey(barCode);
if(index >= 0)
    {
    PlaySoundScan();
    CLagerUm::AnzeigeLager(index);
    return TRUE;
    }
return FALSE;
}
//-----------------------------------------------------------------------------
BOOL CLagerUm::PreTranslateMessage(MSG* pMsg) 
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
    if(m_curFocus == NUMMER)
        {
        if(CheckNummer(barCode))
            {
            m_ctrlComboLagerNeu.SetFocus();
            m_curFocus = LAGER;
            }
        else
            {
//            if(CheckLager(barCode))
//                OnSelchangeComboLagerNeu();	
//            else
                PlaySoundOther();
            }
        return CDialog::PreTranslateMessage(pMsg);
        }
	if(m_curFocus == BIS_NUMMER)
        {
        if(CheckBisNummer(barCode))
            {
            m_ctrlComboLagerNeu.SetFocus();
            m_curFocus = LAGER;
            }
        else
            {
            PlaySoundOther();
            }
        return CDialog::PreTranslateMessage(pMsg);
        }
    if(m_curFocus == LAGER)
        {
        if(CheckLager(barCode))
            OnSelendokComboLagerNeu();	
        else
            {
            if(!CheckNummer(barCode))
                PlaySoundOther();
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
void CLagerUm::OnSelendokComboLagerNeu() 
{

int lix = m_ctrlComboLagerNeu.GetCurSel();

//if(!AnzeigeLager(lix))
//    return;

CString strSteinnummer;
m_ctrlComboSteinnummern.GetWindowText(strSteinnummer);

int ix;
if(!m_pSteinSaetze->FoundAt(strSteinnummer,ix))	
    {
    PlaySoundError();
    AfxMessageBox(Sprache(_T("Steinnummer ungültig!")),MB_OK|MB_ICONEXCLAMATION);
    m_ctrlComboSteinnummern.SetFocus();
    return;
    }

CSteinSatz satz0(m_pSteinSaetze->arr[ix]);
SSatz ss(m_pSteinSaetze->arr[ix]);
CString strLagerNeu(m_tabLagerOrte.GetAt(lix).m_key);

if(ss.m_Lager.Compare(strLagerNeu)) // nur wenn sich ändert
    {
    CVerankerung vera;
    int vix;
    if(m_pVerankerungen->FindeSteinNummer(ss.m_Nummer,vera,vix)
        && (AfxMessageBox(Sprache(_T("Alle Steine der Verankerung auf neues Lager umbuchen?")),MB_YESNO) == IDYES))
        {
        for(int i = 0; i < MAX_VAZAHL; i++)
            {
            if(vera.arr[i].IsEmpty())
                continue;
            int six;
            if(m_pSteinSaetze->FoundAt(vera.arr[i],six))
                {
                SSatz ss1(m_pSteinSaetze->SteinSatz(six));
                ss1.m_LagerAlt = ss1.m_Lager;  // Im Lagerbestand ändern
                ss1.m_Lager = strLagerNeu;
                satz0.Set(ss1);
                m_pSteinSaetze->arr[six] = satz0;

                satz0.m_buchungsNummer = m_pAuftraege->NaechsteBuchungsnummer();    // im der Umbuchungsdatei eintragen
                satz0.SetDatumZeit();
                m_pAuftraege->Auftrag(0).AddPosition(satz0);    // es gibt nur einen Auftrag "Lagerumbuchung"
                PlaySoundAdd();
                m_ctrlComboSteinnummern.SetFocus();
                m_curFocus = NUMMER;
                m_pSteinSaetze->m_modified = TRUE;
                }
            }
        }
    else
        {
    // Normale Umbuchung

		// Prüfen der bisSteinnummer  ch 14.02.2013
		CString bisSteinnr;
		m_ctrlComboBisSteinnummern.GetWindowText(bisSteinnr);
		if (bisSteinnr.IsEmpty())
			bisSteinnr = strSteinnummer;	
		int ix_bisSteinnr;
		if(!m_pSteinSaetze->FoundAt(bisSteinnr,ix_bisSteinnr))	
			{
			PlaySoundError();
			AfxMessageBox(Sprache(_T("Bis Steinnummer ungültig!")),MB_OK|MB_ICONEXCLAMATION);
			m_ctrlComboBisSteinnummern.SetFocus();
			return;
			}

		// Einrichten einer Schleife, so das alle Steinnr von/bis geändert werden ch 14.02.2013
		BOOL bWeiter = TRUE;
		int nVonNr = _wtoi(strSteinnummer);
		int nBisNr = _wtoi(bisSteinnr);
		if ( nBisNr < nVonNr)
			{
			PlaySoundError();
			AfxMessageBox(Sprache(_T("Bis Steinnummer nicht korrekt!")),MB_OK|MB_ICONEXCLAMATION);
			m_ctrlComboBisSteinnummern.SetFocus();
			return;
			}

		if ((nBisNr - nVonNr) > 100)
			{
			PlaySoundError();
			AfxMessageBox(Sprache(_T("Max. 100 Platten änderbar!")),MB_OK|MB_ICONEXCLAMATION);
			m_ctrlComboBisSteinnummern.SetFocus();
			return;
			}

		while( bWeiter )
			{
			// mind. einmal wird die Änderung ja gemacht (für "Steinnr")
			satz0.Set(m_pSteinSaetze->arr[ix]);
			ss = m_pSteinSaetze->arr[ix];

			ss.m_LagerAlt = ss.m_Lager;  // Im Lagerbestand ändern
			ss.m_Lager = strLagerNeu;
			satz0.Set(ss);
			m_pSteinSaetze->arr[ix] = satz0;

			satz0.m_buchungsNummer = m_pAuftraege->NaechsteBuchungsnummer();    // im der Umbuchungsdatei eintragen
			satz0.SetDatumZeit();
			m_pAuftraege->Auftrag(0).AddPosition(satz0);    // es gibt nur einen Auftrag "Lagerumbuchung"
			PlaySoundAdd();
			m_ctrlComboSteinnummern.SetFocus();
			m_curFocus = NUMMER;
			m_pSteinSaetze->m_modified = TRUE;
			
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
						strSteinnummer.Format(_T("%d"),nVonNr);
						if(m_pSteinSaetze->FoundAt( strSteinnummer, ix))
							bGefundenOderAbbruch = TRUE;
						}
					else
						bGefundenOderAbbruch = TRUE;
				}
				if (ix == -1)
					bWeiter = FALSE;
				}			
			}

        }
    }

//AnzeigeLager(lix);
}
//------------------------------------------------------------------------------------
void CLagerUm::OnEditchangeComboSteinnummer() 
{
int ix;
CString nrstr;
m_ctrlComboSteinnummern.GetWindowText(nrstr);
if(m_pSteinSaetze->FoundAt(nrstr,ix))
    {
    AnzeigePlattenDaten(ix);
    SetTexte(m_pSteinSaetze->SteinSatzConst(ix));
    }
else
    {
    CSteinSatz satz;
    SetTexte(satz);
    }
m_ctrlComboSteinnummern.SetEditSel (-1,0);
}
//------------------------------------------------------------------------------------
void CLagerUm::OnTimer(UINT nIDEvent) 
{
CDialog::OnTimer(nIDEvent);

if(m_bBlink)    // Blinkwechsel-Flag
    {
    if(m_bIsVerankStein)
        m_ctrlButtonEinzel.SetWindowTextW(m_strEinzelAnsicht);
    m_bBlink = FALSE;
    }
else
    {
    if(m_bIsVerankStein)
        m_ctrlButtonEinzel.SetWindowTextW(_T(""));
    m_bBlink = TRUE;
    }
}
//------------------------------------------------------------------------------------
void CLagerUm::OnBnClickedButtonEinzel()
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
    int index = -1;
    m_pSteinSaetze->FoundAt(dlg.m_backSteinNummer,index);
    if(index >= 0)
        {
        PlaySoundScan();
        AnzeigePlattenDaten(index);     // Wenn index < 0 oder ungültig, werden alle Felder geleert
        }
    else
        {
        PlaySoundOther();
        AnzeigePlattenDaten(-1);     // Wenn index < 0 oder ungültig, werden alle Felder geleert
        m_ctrlComboSteinnummern.SetWindowText(dlg.m_backSteinNummer);  // und der gelesene Barcode wird angezeigt
        }
    }

m_ctrlComboSteinnummern.SetFocus();
m_curFocus = NUMMER;
}
//-------------------------------------------------------------------------------
void CLagerUm::OnStnClickedStaticHinweis1Text()
{
CString str;
m_ctrlStaticHinweisText.GetWindowText(str);
AfxMessageBox(str,MB_OK);
}

void CLagerUm::OnEnChangeEditLagerort()
{
	CString str;
	m_ctrlEditLagerort.GetWindowText(str);
	int ix_Lager;
	ix_Lager = m_tabLagerOrte.GetIndexByKey (str);
	if (ix_Lager >= 0)
	{
		m_ctrlComboLagerNeu.SetCurSel(ix_Lager);
		OnSelendokComboLagerNeu();
		m_ctrlEditLagerort.SetWindowText(_T(""));
	}
}


//-------------------------------------------------------------------------------
void CLagerUm::OnCbnSetfocusComboBissteinnummer()
{
	m_curFocus = BIS_NUMMER;	
}
