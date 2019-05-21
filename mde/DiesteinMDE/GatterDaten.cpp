// GatterDaten.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "GatterDaten.h"
#include "GatterDatenJeBlock.h"


// CGatterDaten-Dialogfeld

IMPLEMENT_DYNAMIC(CGatterDaten, CDialog)

CGatterDaten::CGatterDaten(CWnd* pParent /*=NULL*/)
	: CDialog(CGatterDaten::IDD, pParent)
{

}

CGatterDaten::~CGatterDaten()
{
}

void CGatterDaten::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_GATTER, m_ctrlStaticGatter);
	DDX_Control(pDX, IDC_STATIC_ANFANG, m_ctrlStaticAnfang);
	DDX_Control(pDX, IDC_STATIC_ENDE, m_ctrlStaticEnde);
	DDX_Control(pDX, IDC_STATIC_ZEIT, m_ctrlStaticZeit);
	DDX_Control(pDX, IDC_STATIC_ZAEHLERSTAND, m_ctrlStaticZaehlerstand);
	DDX_Control(pDX, IDC_STATIC_SANDVERBRAUCH, m_ctrlStaticSandverbrauch);
	DDX_Control(pDX, IDC_SPIN_NUMBER, m_ctrlStaticBlockhoehe);
	DDX_Control(pDX, IDC_STATIC_BLATTART, m_ctrlStaticBlattart);
	DDX_Control(pDX, IDC_STATIC_ANZSCHNITTE, m_ctrlStaticAnzSchnitte);
	DDX_Control(pDX, IDC_EDIT_DATUMANFANG, m_ctrlEditDatumAnfang);
	DDX_Control(pDX, IDC_EDIT_DATUMENDE, m_ctrlEditDatumEnde);
	DDX_Control(pDX, IDC_EDIT_ZEITANFANG, m_ctrlEditZeitAnfang);
	DDX_Control(pDX, IDC_EDIT_ZEITENDE, m_ctrlEditZeitEnde);
	DDX_Control(pDX, IDC_EDIT_ZAEHLERANFANG, m_ctrlEditZaehlerstandAnfang);
	DDX_Control(pDX, IDC_EDIT_ZAEHLERENDE, m_ctrlEditZaehlerstandEnde);
	DDX_Control(pDX, IDC_EDIT_SANDVERBRAUCH, m_ctrlEditSandverbrauch);
	DDX_Control(pDX, IDC_EDIT_BLOCKHOEHE, m_ctrlEditBlockhoehe);
	DDX_Control(pDX, IDC_EDIT_BLATTART, m_ctrlEditBlattart);
	DDX_Control(pDX, IDC_CHECK_NEUEBLAETTER, m_ctrlCheckNeueBlaetter);
	DDX_Control(pDX, IDC_EDIT_ANZSCHNITTE, m_ctrlEditAnzSchnitte);
	DDX_Control(pDX, IDC_BUTTON_SPEICHERN, m_ctrlButtonSpeichern);
	DDX_Control(pDX, IDC_BUTTON_LOESCHEN, m_ctrlButtonLoeschen);
	DDX_Control(pDX, IDC_STATIC_DATUM, m_ctrlStaticDatum);
	DDX_Control(pDX, IDC_STATIC_SAND, m_ctrlStaticSand);
	DDX_Control(pDX, IDC_STATIC_KALK, m_ctrlStaticKalk);
	DDX_Control(pDX, IDC_EDIT_KALKVERBRAUCH, m_ctrlEditKalkverbrauch);
	DDX_Control(pDX, IDC_BUTTON_JEBLOCK, m_ctrlButtonJeBlock);
	DDX_Control(pDX, IDC_BUTTON_ABBRECHEN, m_ctrlButtonAbbrechen);
	DDX_Control(pDX, IDC_BUTTON_ANFANG, m_ctrlButtonAnfang);
}


BEGIN_MESSAGE_MAP(CGatterDaten, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SPEICHERN, &CGatterDaten::OnBnClickedButtonSpeichern)
	ON_BN_CLICKED(IDC_BUTTON_LOESCHEN, &CGatterDaten::OnBnClickedButtonLoeschen)
	ON_EN_CHANGE(IDC_EDIT_ANZSCHNITTE, &CGatterDaten::OnEnChangeEditAnzschnitte)
	ON_BN_CLICKED(IDC_BUTTON_JEBLOCK, &CGatterDaten::OnBnClickedButtonJeblock)
	ON_BN_CLICKED(IDC_BUTTON_ABBRECHEN, &CGatterDaten::OnBnClickedButtonAbbrechen)
	ON_BN_CLICKED(IDC_BUTTON_ANFANG, &CGatterDaten::OnBnClickedButtonAnfang)
	ON_BN_CLICKED(IDC_BUTTON_ENDE, &CGatterDaten::OnBnClickedButtonEnde)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------------
BOOL CGatterDaten::OnInitDialog()
{			
	CDialog::OnInitDialog();

	CenterWindow(GetDesktopWindow());	// center to the hpc screen

	TranslateStatic(m_ctrlStaticGatter);
	TranslateStatic(m_ctrlStaticAnfang);
	TranslateStatic(m_ctrlStaticEnde);
	TranslateStatic(m_ctrlStaticDatum);
	TranslateStatic(m_ctrlStaticZeit);
	TranslateStatic(m_ctrlStaticZaehlerstand);
	TranslateStatic(m_ctrlStaticSandverbrauch);
	TranslateStatic(m_ctrlStaticSand);
	TranslateStatic(m_ctrlStaticKalk);
	TranslateStatic(m_ctrlStaticBlockhoehe);
	TranslateStatic(m_ctrlStaticBlattart);
	TranslateStatic(m_ctrlStaticAnzSchnitte);
	TranslateButton(m_ctrlButtonLoeschen);
	TranslateButton(m_ctrlButtonSpeichern);
	TranslateButton(m_ctrlButtonJeBlock);
	TranslateButton(m_ctrlCheckNeueBlaetter);

	m_ctrlButtonAnfang.SetButtonStyle(BS_FLAT);


	m_tabGatter.Read();
	
	m_ctrlStaticGatter.SetWindowText(Sprache(_T("Gatter/Ladung:")) + _T(" ") + *m_pAktuellerGatterAuftrag);
	// Wenn Gatterdaten vorhanden wird entweder das erste oder das zuletzt verwendete ausgewählt
	if (m_pGatterDaten->Anzahl() > 0)
	{
		AnzeigeGatterDaten(*m_pAktuellerGatterAuftrag);			
	}
	else
	{
		BildschirmLoeschen();
		LetztenZaehlerstandErmitteln(*m_pAktuellerGatterAuftrag);
	}
	m_ctrlEditDatumAnfang.SetFocus();

	return TRUE;  // return TRUE  unless you set the focus to a control
}
//-----------------------------------------------------------------------------------
void CGatterDaten::AnzeigeGatterDaten(CString strAuftrag)
{
	SSatz s; 

	int ix = m_pGatterDaten->Exist(strAuftrag);
	if (ix >= 0 && m_pGatterDaten->Auftrag(ix).m_Positionen.Anzahl() > 0  )
	{
		SSatz s(m_pGatterDaten->Auftrag(ix).Position(0));

		if (s.m_GatterDatumAnfang.GetLength() > 0)
		{
			m_ctrlEditDatumAnfang.SetWindowText(s.m_GatterDatumAnfang );
			m_ctrlEditDatumEnde.SetWindowText(s.m_GatterDatumEnde);
			m_ctrlEditZeitAnfang.SetWindowText(s.m_GatterZeitAnfang);
			m_ctrlEditZeitEnde.SetWindowText(s.m_GatterZeitEnde);
			m_ctrlEditZaehlerstandAnfang.SetWindowText(s.m_GatterZaehlerstandAnfang);
			m_ctrlEditZaehlerstandEnde.SetWindowText(s.m_GatterZaehlerstandEnde);
			m_ctrlEditSandverbrauch.SetWindowText(s.m_GatterSandverbrauch);
			m_ctrlEditKalkverbrauch.SetWindowText(s.m_GatterKalkverbrauch);
			m_ctrlEditBlockhoehe.SetWindowText(s.m_GatterBlockhoehe);
			m_ctrlEditBlattart.SetWindowText(s.m_GatterBlattart);
			if (s.m_GatterNeueBlaetter == _T("X"))
				m_ctrlCheckNeueBlaetter.SetCheck (TRUE);
			else
				m_ctrlCheckNeueBlaetter.SetCheck (FALSE);
			
			if (s.m_GatterAnzahlSchnitte.IsEmpty() )
			{
				m_ctrlEditAnzSchnitte.ShowWindow(TRUE);
				m_ctrlButtonJeBlock.ShowWindow(TRUE);
			}
			else
			{
				m_ctrlEditAnzSchnitte.SetWindowText(s.m_GatterAnzahlSchnitte);
				if (s.m_GatterAnzahlSchnitte.Find(_T("@@")) > 0 )
				{
					m_ctrlEditAnzSchnitte.ShowWindow(FALSE);
					m_ctrlButtonJeBlock.ShowWindow(TRUE);
				}
				else
				{
					m_ctrlEditAnzSchnitte.ShowWindow(TRUE);
					m_ctrlButtonJeBlock.ShowWindow(FALSE);
				}
			}
		}
		else
		{
			BildschirmLoeschen();
			LetztenZaehlerstandErmitteln(strAuftrag);
		}
	}	
	else
	{
		BildschirmLoeschen();
		LetztenZaehlerstandErmitteln(strAuftrag);
	}
}
void CGatterDaten::BildschirmLoeschen ()
{
	m_ctrlEditDatumAnfang.SetWindowText(_T(""));
	m_ctrlEditDatumEnde.SetWindowText(_T(""));
	m_ctrlEditZeitAnfang.SetWindowText(_T(""));
	m_ctrlEditZeitEnde.SetWindowText(_T(""));
	m_ctrlEditZaehlerstandAnfang.SetWindowText(_T(""));
	m_ctrlEditZaehlerstandEnde.SetWindowText(_T(""));
	m_ctrlEditSandverbrauch.SetWindowText(_T(""));
	m_ctrlEditKalkverbrauch.SetWindowText(_T(""));
	m_ctrlEditBlockhoehe.SetWindowText(_T(""));
	m_ctrlEditBlattart.SetWindowText(_T(""));
	m_ctrlCheckNeueBlaetter.SetCheck (FALSE);
	m_ctrlEditAnzSchnitte.SetWindowText(_T(""));
}
//-----------------------------------------------------------------------------------
CString CGatterDaten::GetGatter (CString strAuftrag)
{
	CString gatter = _T("");
	int pos = strAuftrag.Find (_T("@"),0);
	if (pos > 0)
		gatter = strAuftrag.Left (pos);
	return gatter;
}
//-----------------------------------------------------------------------------------
void CGatterDaten::LetztenZaehlerstandErmitteln(CString strAuftrag)
{
	CString strGatter = GetGatter(strAuftrag);
	if (strGatter.GetLength() == 0)
		return;

	double zaehler = 0;

	C4String gatter = m_tabGatter.GetItemByKey (strGatter);
	if (gatter.m_value1.GetLength() > 0)
		zaehler = CSteinSatz::StringToDouble(gatter.m_value1);

	//Prüfen, ob es noch einen neu erfassten Eintrag für dieses Gatter gibt.
	if (m_pGatterDaten->Anzahl() > 0)
		for (int i = 0; i < m_pGatterDaten->Anzahl(); i++)
		{
			CString strTemp = GetGatter(m_pGatterDaten->Auftrag(i).m_strIdent );
			if (strTemp == strGatter && m_pGatterDaten->Auftrag(i).m_Positionen.Anzahl() > 0)
			{
				SSatz s(m_pGatterDaten->Auftrag(i).Position(0));
				if (CSteinSatz::StringToDouble(s.m_GatterZaehlerstandEnde) > zaehler)
					zaehler = CSteinSatz::StringToDouble(s.m_GatterZaehlerstandEnde);
			}
		}

	// zaehler jetzt ins Dialogfeld eintragen
	if (zaehler > 0)
		m_ctrlEditZaehlerstandAnfang.SetWindowText(CSteinSatz::DoubleToString(zaehler));
}
//-----------------------------------------------------------------------------------
void CGatterDaten::WerteAusDialogUebernehmen()
{
	m_ctrlStaticGatter.GetWindowText(m_strGatterAuftrag);
	m_strGatterAuftrag.Replace(Sprache(_T("Gatter/Ladung:")) + _T(" "), _T(""));
	m_ctrlEditDatumAnfang.GetWindowText(m_strDatumAnfang);
	m_ctrlEditDatumEnde.GetWindowText(m_strDatumEnde);
	m_ctrlEditZeitAnfang.GetWindowText(m_strZeitAnfang);
	m_ctrlEditZeitEnde.GetWindowText(m_strZeitEnde);
	m_ctrlEditZaehlerstandAnfang.GetWindowText(m_strZaehlerstandAnfang);
	m_ctrlEditZaehlerstandEnde.GetWindowText(m_strZaehlerstandEnde);
	m_ctrlEditSandverbrauch.GetWindowText(m_strSandverbrauch);
	m_ctrlEditKalkverbrauch.GetWindowText(m_strKalkverbrauch);
	m_ctrlEditBlockhoehe.GetWindowText(m_strBlockhoehe);
	m_ctrlEditBlattart.GetWindowText(m_strBlattart);
	if (m_ctrlCheckNeueBlaetter.GetCheck())
		m_strNeueBlaetter = _T("X");
	else
		m_strNeueBlaetter = _T("");	
	m_ctrlEditAnzSchnitte.GetWindowText(m_strAnzahlSchnitte);
}
//-----------------------------------------------------------------------------------
BOOL CGatterDaten::WerteOk()
{

if (!PruefeDatum(m_strDatumAnfang, m_ctrlEditDatumAnfang))
	return FALSE;
if(!PruefeDatum(m_strDatumEnde,m_ctrlEditDatumEnde)) // leer oder ungültiges format
    return FALSE;
if(!PruefeUhrzeit(m_strZeitAnfang,m_ctrlEditZeitAnfang )) // leer oder ungültiges format
    return FALSE;
if(!PruefeUhrzeit(m_strZeitEnde,m_ctrlEditZeitEnde)) // leer oder ungültiges format
    return FALSE;

// Prüfen, ob die Datumsangaben richtig sind
CTime ADatum(_ttoi(m_strDatumAnfang.Right(4)), _ttoi(m_strDatumAnfang.Mid(3,2)), _ttoi(m_strDatumAnfang.Left(2)), _ttoi(m_strZeitAnfang.Left(2)), _ttoi(m_strZeitAnfang.Right(2)), 0);
CTime EDatum(_ttoi(m_strDatumEnde.Right(4)), _ttoi(m_strDatumEnde.Mid(3,2)), _ttoi(m_strDatumEnde.Left(2)), _ttoi(m_strZeitEnde.Left(2)), _ttoi(m_strZeitEnde.Right(2)), 0);
if (EDatum < ADatum)
{
	AfxMessageBox(Sprache(_T("Endedatum liegt vor Anfangsdatum!")));
	m_ctrlEditDatumEnde.SetFocus();
	m_ctrlEditDatumEnde.SetSel(0,m_strDatumEnde.GetLength(),0);
	return FALSE;
}

if(!WertOk(m_strZaehlerstandAnfang,m_ctrlEditZaehlerstandAnfang )) // leer oder ungültiges format
    return FALSE;
if(!WertOk(m_strZaehlerstandEnde,m_ctrlEditZaehlerstandEnde )) // leer oder ungültiges format
    return FALSE;
if (CSteinSatz::StringToDouble(m_strZaehlerstandAnfang) >= CSteinSatz::StringToDouble(m_strZaehlerstandEnde))
{
	AfxMessageBox(Sprache(_T("Zaehlerstand nicht korrekt!")));
	m_ctrlEditZaehlerstandEnde.SetFocus();
	m_ctrlEditZaehlerstandEnde.SetSel (0,m_strZaehlerstandEnde.GetLength(),0);
	return FALSE;
}

// Prüfen, ob die Zählerabstand nicht größer ist als der Zeitabstand(Datum/Uhrzeit)
CTimeSpan differenzDatum = EDatum - ADatum;
long long zeitInMinuten = differenzDatum.GetTotalMinutes ();
double zaehlerInMinuten = (CSteinSatz::StringToDouble(m_strZaehlerstandEnde) - CSteinSatz::StringToDouble(m_strZaehlerstandAnfang)) * 60;

if (zeitInMinuten < zaehlerInMinuten)
{
	AfxMessageBox(Sprache(_T("Zeit oder Zählerstand nicht korrekt!")));
	m_ctrlEditZeitAnfang.SetFocus();
	m_ctrlEditZeitAnfang.SetSel (0,m_strZeitAnfang.GetLength(),0);
	return FALSE;
}


if(m_strGatterAuftrag.Right(2) != _T("-S"))
   if(!WertOk(m_strBlockhoehe,m_ctrlEditBlockhoehe ))
	return FALSE;
else
	if(NoValueSetFocus(m_strBlockhoehe,m_ctrlEditBlockhoehe))// leer erlaubt
		return FALSE;

if (m_strAnzahlSchnitte.Find(_T("@@")) < 0)
	if(!WertOk(m_strAnzahlSchnitte,m_ctrlEditAnzSchnitte))
		return FALSE;


if(NoValueSetFocus(m_strSandverbrauch,m_ctrlEditSandverbrauch)) // leer erlaubt
    return FALSE;
if (m_strSandverbrauch.GetLength() > 0)
	if (!(_wtoi(m_strSandverbrauch) == CSteinSatz::StringToDouble(m_strSandverbrauch)))
	{
		AfxMessageBox(Sprache(_T("Sandverbrauch nicht korrekt!")));
		m_ctrlEditSandverbrauch.SetFocus();
		return FALSE;
	}

if(NoValueSetFocus(m_strKalkverbrauch,m_ctrlEditKalkverbrauch)) // leer erlaubt
    return FALSE;
if (m_strKalkverbrauch.GetLength() > 0)
	if (!(_wtoi(m_strKalkverbrauch) == CSteinSatz::StringToDouble(m_strKalkverbrauch)))
	{
		AfxMessageBox(Sprache(_T("Kalkverbrauch nicht korrekt!")));
		m_ctrlEditKalkverbrauch.SetFocus();
		m_ctrlEditKalkverbrauch.SetSel(0,m_strKalkverbrauch.GetLength(),0);
		return FALSE;
	}

return TRUE;
}
//-----------------------------------------------------------------------------------
BOOL CGatterDaten::WertOk(CString& str,CEdit& edit)
{
if(str.IsEmpty())
    {
    edit.SetFocus();
    PlaySoundError();
    return FALSE;
    }
return !NoValueSetFocus(str,edit);

}
//-----------------------------------------------------------------------------------
BOOL CGatterDaten::PruefeDatum (CString& strDatum, CEdit& edit)
{
	CString strDay;
	CString strMonth;
	CString strYear;
	CString str(strDatum);
	CString strTren = _T(".");
	int ix = str.Find(strTren);
	if (ix < 0)
	{
		strTren = _T(",");
		ix = str.Find(strTren);
	}
	
	if(ix > 0)
		strDay = str.Left(ix);
	else
	{
		edit.SetFocus();
		return FALSE;
	}
	str = str.Mid(ix+1);
	ix = str.Find(strTren);
	if(ix > 0)
		strMonth = str.Left(ix);
	else
	{
		edit.SetFocus();
		return FALSE;
	}
	strYear = str.Mid(ix+1);
	int	day = _ttoi(strDay);
	if((day < 1) || (day > 31))
	{
		edit.SetFocus();
		return FALSE;
	}
	int month = _ttoi(strMonth);
	if((month < 1) || (month > 12))
	{
		edit.SetFocus();
		return FALSE;
	}
	int year = _ttoi(strYear);	
	if(year < 1) 
	{
		edit.SetFocus();
		return FALSE;
	}
	if(year < 100) year += 2000;
	if(year > 9999) 
	{
		edit.SetFocus();
		return FALSE;
	}
	strDatum.Format(_T("%02d.%02d.%02d"),day,month,year);
	edit.SetWindowText(strDatum);
return TRUE;

}
//-----------------------------------------------------------------------------------
BOOL CGatterDaten::PruefeUhrzeit(CString& strUhrzeit, CEdit& edit)
{
	CString strStd;
	CString strMin;
	
	CString str(strUhrzeit);
	
	int ix;
	ix = str.Find(_T(":"));
	if (ix > 0)
		str.Replace(_T(":"), _T(""));
	ix = str.Find(_T("."));
	if (ix > 0)
		str.Replace( _T("."), _T(""));
	ix = str.Find(_T(","));
	if (ix > 0)
		str.Replace(_T(","), _T(""));
	

	if (str.GetLength() != 4)
	{
		edit.SetFocus();
		return FALSE;
	}
	if ( CSteinSatz::StringToDouble(str) == 0)
	{
		edit.SetFocus();
		return FALSE;
	}

	strStd = str.Left(2);
	strMin = str.Right(2);

	int	std = _ttoi(strStd);
	if((std < 0) || (std > 24))
	{
		edit.SetFocus();
		return FALSE;
	}
	int min = _ttoi(strMin);
	if((min < 0) || (min > 59))
	{
		edit.SetFocus();
		return FALSE;
	}
	strUhrzeit.Format(_T("%02d:%02d"),std,min);
	edit.SetWindowText(strUhrzeit);
return TRUE;

}//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
// Alle Aufträge durchsuchen wegen höchster Nummer
int CGatterDaten::NaechsteBuchungsnummer() const
{
int maxnum = 0;
for(int i = 0; i < m_pGatterDaten->Anzahl(); i++)
    {
    CAuftrag *pAuf = &(m_pGatterDaten->Auftrag(i));
    for(int j = 0; j < pAuf->m_Positionen.Anzahl(); j++)
        {
        if(pAuf->m_Positionen.SteinSatz(j).m_buchungsNummer > maxnum)
            maxnum = pAuf->m_Positionen.SteinSatz(j).m_buchungsNummer;
        }
    }
return maxnum+1;
}
 //-----------------------------------------------------------------------------------
// CGatterDaten-Meldungshandler
void CGatterDaten::OnOK()
{

	OnBnClickedButtonSpeichern();
}
void CGatterDaten::OnBnClickedButtonAbbrechen()
{
	EndDialog (0);
}

void CGatterDaten::OnBnClickedButtonSpeichern()
{
	UpdateData(TRUE);

	WerteAusDialogUebernehmen();

	if(!WerteOk()) return;
	
	int ix_daten = m_pGatterDaten->Exist(m_strGatterAuftrag);
	if (ix_daten < 0)
	{
		CAuftrag gatter;
		gatter.m_strIdent = m_strGatterAuftrag;
		m_pGatterDaten->Add(gatter);
		ix_daten = m_pGatterDaten->Exist (m_strGatterAuftrag);
	}


	SSatz ss;
	
	ss.m_GatterDatumAnfang = m_strDatumAnfang;
	ss.m_GatterDatumEnde = m_strDatumEnde;
	ss.m_GatterZeitAnfang = m_strZeitAnfang;
	ss.m_GatterZeitEnde = m_strZeitEnde;
	ss.m_GatterZaehlerstandAnfang = m_strZaehlerstandAnfang;
	ss.m_GatterZaehlerstandEnde = m_strZaehlerstandEnde;
	ss.m_GatterSandverbrauch = m_strSandverbrauch;
	ss.m_GatterKalkverbrauch = m_strKalkverbrauch;
	ss.m_GatterBlockhoehe = m_strBlockhoehe;
	ss.m_GatterBlattart = m_strBlattart;
	ss.m_GatterNeueBlaetter = m_strNeueBlaetter;
	ss.m_GatterAnzahlSchnitte = m_strAnzahlSchnitte;
	
	CSteinSatz satz;
	satz.Set(ss);

	satz.SetDatumZeit();
	satz.m_buchungsNummer = NaechsteBuchungsnummer();
	
	if (m_pGatterDaten->Auftrag(ix_daten).m_Positionen.Anzahl() == 0)
		m_pGatterDaten->Auftrag(ix_daten).AddPosition(satz);
	else
	{
		// Wenn der Satz schon existiert müssen die Maße für die Standfuge übernommen werden.
		SSatz temp(m_pGatterDaten->Auftrag(ix_daten).Position(0));
		ss.m_Laenge = temp.m_Laenge;
		ss.m_Breite = temp.m_Breite;
		m_pGatterDaten->Auftrag(ix_daten).Position(0).Set(ss);
	}

	PlaySoundAdd();

	UpdateData(FALSE);

	EndDialog (0);
}

void CGatterDaten::OnBnClickedButtonLoeschen()
{
	m_ctrlStaticGatter.GetWindowText(m_strGatterAuftrag);
	m_strGatterAuftrag.Replace(Sprache(_T("Gatter/Ladung:")) + _T(" "), _T(""));

	int ix_daten = m_pGatterDaten->Exist(m_strGatterAuftrag);
	if (ix_daten >= 0)
	{
		if(AfxMessageBox(Sprache(_T("Wollen Sie die Daten wirklich löschen?")),MB_YESNO|MB_ICONQUESTION)
                     == IDYES)
		{
			if (m_pGatterDaten->Auftrag(ix_daten).m_Positionen.Anzahl() >= 0)
			{
				SSatz ss(m_pGatterDaten->Auftrag(ix_daten).Position(0));
				if (ss.m_Laenge.GetLength() == 0 && ss.m_Breite.GetLength() == 0 )
					m_pGatterDaten->Remove(m_strGatterAuftrag);
				else
				{
					ss.m_GatterDatumAnfang = _T("");
					ss.m_GatterDatumEnde = _T("");
					ss.m_GatterZeitAnfang = _T("");
					ss.m_GatterZeitEnde = _T("");
					ss.m_GatterZaehlerstandAnfang = _T("");
					ss.m_GatterZaehlerstandEnde = _T("");
					ss.m_GatterSandverbrauch = _T("");
					ss.m_GatterKalkverbrauch = _T("");
					ss.m_GatterBlockhoehe = _T("");
					ss.m_GatterBlattart = _T("");
					ss.m_GatterNeueBlaetter = _T("");
					ss.m_GatterAnzahlSchnitte = _T("");
					m_pGatterDaten->Auftrag(ix_daten).Position(0).Set(ss);
				}
			}
			// Bildschirm wieder leeren
			BildschirmLoeschen();
			LetztenZaehlerstandErmitteln(m_strGatterAuftrag);
		}
	}
	else
	{
		// Bildschirm wieder leeren
		BildschirmLoeschen();
		LetztenZaehlerstandErmitteln(m_strGatterAuftrag);
	}
	m_ctrlEditDatumAnfang.SetFocus();
}
//-------------------------------------------------------------------------------------
void CGatterDaten::OnEnChangeEditAnzschnitte()
{
	CString inhalt;

	m_ctrlEditAnzSchnitte.GetWindowText(inhalt);
	if (inhalt.IsEmpty())
	{
		m_ctrlEditAnzSchnitte.ShowWindow(TRUE);
		m_ctrlButtonJeBlock.ShowWindow(TRUE);
	}
	else
	{
		m_ctrlButtonJeBlock.ShowWindow(FALSE);
	}
}
//-------------------------------------------------------------------------------------
void CGatterDaten::OnBnClickedButtonJeblock()
{
	CAuftrag gatterAuftrag;
	gatterAuftrag = m_pOffeneAuftraege->Auftrag(*m_pAktuellerGatterAuftrag);
	CString AnzSchnitte;
	m_ctrlEditAnzSchnitte.GetWindowText(AnzSchnitte);

	CGatterDatenJeBlock dialogAnzSchnitte(this);

	dialogAnzSchnitte.m_pAuftrag = &gatterAuftrag;
	dialogAnzSchnitte.m_pAnzSchnitteJeBlock = &AnzSchnitte;
	dialogAnzSchnitte.m_pScanner = m_pScanner;

	m_pScanner->setEnableScanner(FALSE);
	dialogAnzSchnitte.DoModal();
    m_pScanner->setEnableScanner(TRUE);

	m_ctrlEditAnzSchnitte.SetWindowText( AnzSchnitte);
	if (AnzSchnitte.IsEmpty() )
	{
		m_ctrlEditAnzSchnitte.ShowWindow(TRUE);
		m_ctrlButtonJeBlock.ShowWindow(TRUE);
	}
	else
	{
		if (AnzSchnitte.Find(_T("@@")) > 0 )
		{
			m_ctrlEditAnzSchnitte.ShowWindow(FALSE);
			m_ctrlButtonJeBlock.ShowWindow(TRUE);
		}
		else
		{
			m_ctrlEditAnzSchnitte.ShowWindow(TRUE);
			m_ctrlButtonJeBlock.ShowWindow(FALSE);
		}
	}




}

//-------------------------------------------------------------------------------------
void CGatterDaten::OnBnClickedButtonAnfang()
{
	CString temp = _T("");
	m_ctrlEditDatumAnfang.GetWindowText(temp);
	if (temp.GetLength() == 0)
	{
		CTime time;
		time = time.GetCurrentTime();
		temp.Format(_T("%02d.%02d.%04d"),time.GetDay(), time.GetMonth(), time.GetYear());
		m_ctrlEditDatumAnfang.SetWindowText(temp);
	}
}
//-------------------------------------------------------------------------------------
void CGatterDaten::OnBnClickedButtonEnde()
{
	CString temp = _T("");
	m_ctrlEditDatumEnde.GetWindowText(temp);
	if (temp.GetLength() == 0)
	{
		CTime time;
		time = time.GetCurrentTime();
		temp.Format(_T("%02d.%02d.%04d"),time.GetDay(), time.GetMonth(), time.GetYear());
		m_ctrlEditDatumEnde.SetWindowText(temp);
	}
}
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
BOOL CGatterDaten::PreTranslateMessage(MSG* pMsg) 
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
		
		if (currId == m_ctrlEditBlattart.GetDlgCtrlID())
		{
			m_ctrlEditBlattart.SetWindowText(barCode);
			PlaySoundScan();
			return CDialog::PreTranslateMessage(pMsg);
		}

		PlaySoundOther();

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

/*
void CGatterDaten::OnStnDblclickStaticAnfang()
{
	CString temp = _T("");
	m_ctrlEditDatumAnfang.GetWindowText(temp);
	if (temp.GetLength() == 0)
	{
		CTime time;
		time.GetCurrentTime();
		temp.Format(_T("%02d.%02d.%04d"),time.GetDay(), time.GetMonth(), time.GetYear());
	}
}
*/
