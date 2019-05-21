// GatterPlatten.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "GatterPlatten.h"


// CGatterPlatten-Dialogfeld

IMPLEMENT_DYNAMIC(CGatterPlatten, CDialog)

CGatterPlatten::CGatterPlatten(CWnd* pParent /*=NULL*/)
	: CDialog(CGatterPlatten::IDD, pParent)
{
}

CGatterPlatten::~CGatterPlatten()
{
}

void CGatterPlatten::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_BLOCKNUMMER, m_ctrlStaticBlocknummer);
	DDX_Control(pDX, IDC_STATIC_MATERIAL, m_ctrlStaticMaterial);
	DDX_Control(pDX, IDC_STATIC_MASSE, m_ctrlStaticMasse);
	DDX_Control(pDX, IDC_EDIT_STEINNR, m_ctrlEditSteinnr);
	DDX_Control(pDX, IDC_EDIT_MENGE, m_ctrlEditMenge);
	DDX_Control(pDX, IDC_STATIC_ME, m_ctrlStaticMe);
	DDX_Control(pDX, IDC_STATIC_MASSE2, m_ctrlStaticMasse2);
	DDX_Control(pDX, IDC_EDIT_LAENGE, m_ctrlEditLaenge);
	DDX_Control(pDX, IDC_EDIT_BREITE, m_ctrlEditBreite);
	DDX_Control(pDX, IDC_EDIT_DICKE, m_ctrlEditDicke);
	DDX_Control(pDX, IDC_STATIC_FEHLECKE, m_ctrlStaticFehlecke);
	DDX_Control(pDX, IDC_EDIT_FEHLLAENGE, m_ctrlEditFehlLaenge);
	DDX_Control(pDX, IDC_EDIT_FEHLBREITE, m_ctrlEditFehlBreite);
	DDX_Control(pDX, IDC_COMBO_FEHLER, m_ctrlComboFehler);
	DDX_Control(pDX, IDC_COMBO_LAGER, m_ctrlComboLager);
	DDX_Control(pDX, IDC_STATIC_LIEFERANT, m_ctrlStaticLieferant);
	DDX_Control(pDX, IDC_STATIC_HINWEIS, m_ctrlStaticHinweis);
	DDX_Control(pDX, IDC_EDIT_HINWEIS, m_ctrlEditHinweis);
	DDX_Control(pDX, IDC_STATIC_PREIS, m_ctrlStaticPreis);
	DDX_Control(pDX, IDC_EDIT_PREIS, m_ctrlEditPreis);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonAbbruch);
	DDX_Control(pDX, IDC_BUTTON_HINZU, m_ctrlButtonHinzufuegen);
	DDX_Control(pDX, IDC_STATIC_LAGER, m_ctrlStaticLager);
	DDX_Control(pDX, IDC_COMBO_LIEFERAN, m_ctrlComboLieferant);
	DDX_Control(pDX, IDC_STATIC_STEINNR, m_ctrlStaticSteinnr);
	DDX_Control(pDX, IDC_STATIC_MENGE, m_ctrlStaticMenge);
	DDX_Control(pDX, IDC_STATIC_NETTOMASSE, m_ctrlStaticNettoMasse);
	DDX_Control(pDX, IDC_EDIT_NETTOLAENGE, m_ctrlEditNettoLaenge);
	DDX_Control(pDX, IDC_EDIT_NETTOBREITE, m_ctrlEditNettoBreite);
	DDX_Control(pDX, IDC_EDIT_NETTODICKE, m_ctrlEditNettoDicke);
	DDX_Control(pDX, IDC_EDIT_LAGERORT, m_ctrlEditLagerort);
}


BEGIN_MESSAGE_MAP(CGatterPlatten, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_HINZU, &CGatterPlatten::OnBnClickedButtonHinzu)
	ON_EN_KILLFOCUS(IDC_EDIT_HINWEIS, &CGatterPlatten::OnEnKillfocusEditHinweis)
	ON_EN_CHANGE(IDC_EDIT_LAGERORT, &CGatterPlatten::OnEnChangeEditLagerort)
	ON_EN_CHANGE(IDC_EDIT_MENGE, &CGatterPlatten::OnEnChangeEditMenge)
	ON_EN_CHANGE(IDC_EDIT_LAENGE, &CGatterPlatten::OnEnChangeEditLaenge)
	ON_EN_CHANGE(IDC_EDIT_BREITE, &CGatterPlatten::OnEnChangeEditBreite)
	ON_EN_CHANGE(IDC_EDIT_DICKE, &CGatterPlatten::OnEnChangeEditDicke)
	ON_EN_CHANGE(IDC_EDIT_NETTOLAENGE, &CGatterPlatten::OnEnChangeEditNettolaenge)
	ON_EN_CHANGE(IDC_EDIT_NETTOBREITE, &CGatterPlatten::OnEnChangeEditNettobreite)
	ON_EN_CHANGE(IDC_EDIT_NETTODICKE, &CGatterPlatten::OnEnChangeEditNettodicke)
	ON_EN_CHANGE(IDC_EDIT_FEHLLAENGE, &CGatterPlatten::OnEnChangeEditFehllaenge)
	ON_EN_CHANGE(IDC_EDIT_FEHLBREITE, &CGatterPlatten::OnEnChangeEditFehlbreite)
	ON_CBN_SELENDOK(IDC_COMBO_FEHLER, &CGatterPlatten::OnCbnSelendokComboFehler)
	ON_CBN_SELENDOK(IDC_COMBO_LAGER, &CGatterPlatten::OnCbnSelendokComboLager)
	ON_EN_CHANGE(IDC_EDIT_HINWEIS, &CGatterPlatten::OnEnChangeEditHinweis)
	ON_EN_CHANGE(IDC_EDIT_PREIS, &CGatterPlatten::OnEnChangeEditPreis)
	ON_EN_CHANGE(IDC_EDIT_STEINNR, &CGatterPlatten::OnEnChangeEditSteinnr)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------------
BOOL CGatterPlatten::OnInitDialog()
{			
	CDialog::OnInitDialog();

	CenterWindow(GetDesktopWindow());	// center to the hpc screen

	TranslateStatic(m_ctrlStaticSteinnr);
	TranslateStatic(m_ctrlStaticMenge);
	TranslateStatic(m_ctrlStaticMe);
	TranslateStatic(m_ctrlStaticMasse2);
	TranslateStatic(m_ctrlStaticFehlecke);
	TranslateStatic(m_ctrlStaticLager);
	TranslateStatic(m_ctrlStaticLieferant);
	TranslateStatic(m_ctrlStaticHinweis);
	TranslateStatic(m_ctrlStaticPreis);
	TranslateButton(m_ctrlButtonAbbruch);
	TranslateButton(m_ctrlButtonHinzufuegen);

	// Preisfeld vorerst einmal komplett sperren, da die Mitarbeiter den Preis nicht sehen sollen ch 30.10.2012
	// vielleicht später einmal durch einen Schalter freigeben.
	m_ctrlStaticPreis.ShowWindow(FALSE);
	m_ctrlEditPreis.ShowWindow(FALSE);
	

	// Einlesen der zusätzlichen Daten
	m_tabArtikelGruppen.Read();
	m_tabMaterialGruppen.Read();
	m_tabAlleMaterialArten.Read();
	m_tabAlleOberflaechen.Read();
	m_tabLagerOrte.Read();
	m_tabLieferanten.Read();
	m_tabFehlerbezeichnung.Read();
	C2String s2;
	m_tabFehlerbezeichnung.InsertAt(0,s2); // Leerauswahl ermöglichen
	// Füllen der ComboBoxen
	int i;
	for(i = 0; i < m_tabLagerOrte.GetSize(); i++)
	{
		CString str;
		str.Format(_T("%s %s"),m_tabLagerOrte.GetAt(i).m_key,m_tabLagerOrte.GetAt(i).m_bez);
		m_ctrlComboLager.AddString(str);
    }
	for(i = 0; i < m_tabFehlerbezeichnung.GetCount(); i++)
		m_ctrlComboFehler.AddString(m_tabFehlerbezeichnung.GetAt(i).m_bez);

	for(i = 0; i < m_tabLieferanten.GetCount(); i++)
		m_ctrlComboLieferant.AddString(m_tabLieferanten.GetAt(i).m_bez);

	FuellenRestblockZusatzArray();


	// Wenn Gatterdaten vorhanden wird entweder das erste oder das zuletzt verwendete ausgewählt
	if (m_pOffeneAuftraege->Anzahl() > 0)
	{
		if (m_pAktuellerGatterAuftrag->GetLength() > 0)
		{
			int ix = m_pOffeneAuftraege->Exist (*m_pAktuellerGatterAuftrag );
			if (ix >= 0)
			{
				if (m_pAktuellerBlock->GetLength() > 0)
					AnzeigeBlockdaten(*m_pAktuellerGatterAuftrag, *m_pAktuellerBlock);
					AnzeigeNeuePlatte(*m_pAktuellerGatterAuftrag, *m_pAktuellerBlock);
				//SetPositionenListe(*m_pstrLetzterGatterAuftrag);
			}
			else
			{
				AnzeigeBlockdaten(_T(""), _T(""));
				AnzeigeNeuePlatte(_T(""), _T(""));
				//SetPositionenListe(m_pAuftraege->Auftrag (0).m_strIdent );
			}
		}
		else
		{
			AnzeigeBlockdaten(_T(""), _T(""));
			AnzeigeNeuePlatte(_T(""), _T(""));
			//SetPositionenListe(m_pAuftraege->Auftrag (0).m_strIdent );
		}
	}

	if (m_Art == _T("Platten"))
		m_ctrlEditSteinnr.SetLimitText(10);
		m_ctrlStaticNettoMasse.ShowWindow(FALSE);
		m_ctrlEditNettoLaenge.ShowWindow(FALSE);
		m_ctrlEditNettoBreite.ShowWindow(FALSE);
		m_ctrlEditNettoDicke.ShowWindow(FALSE);

	if (m_Art == _T("Bloecke"))
	{
		m_ctrlStaticSteinnr.ShowWindow(FALSE);
		m_ctrlEditSteinnr.ShowWindow(FALSE);
		m_ctrlStaticMenge.ShowWindow(FALSE);
		m_ctrlEditMenge.ShowWindow(FALSE);
		m_ctrlStaticMe.ShowWindow(FALSE);
		m_ctrlStaticMasse2.SetWindowText(Sprache(_T("Brutto(L/B/D)")));
		m_ctrlStaticNettoMasse.ShowWindow(TRUE);
		m_ctrlEditNettoLaenge.ShowWindow(TRUE);
		m_ctrlEditNettoBreite.ShowWindow(TRUE);
		m_ctrlEditNettoDicke.ShowWindow(TRUE);
		m_ctrlStaticFehlecke.ShowWindow(FALSE);
		m_ctrlEditFehlLaenge.ShowWindow(FALSE);
		m_ctrlEditFehlBreite.ShowWindow(FALSE);
		m_ctrlComboFehler.ShowWindow(FALSE);
		m_ctrlEditMenge.SetWindowText(_T("1"));
	}	

	m_pScanner->setEnableScanner(TRUE);
	m_modified = FALSE;

	return TRUE;  // return TRUE  unless you set the focus to a control
}
//-----------------------------------------------------------------------------------
void CGatterPlatten::AnzeigeBlockdaten (CString strAuftrag, CString strBlock)
{
	CAuftrag auftrag;
	auftrag = m_pOffeneAuftraege->Auftrag (strAuftrag);
	int ix;
	auftrag.m_Positionen.FoundAt (strBlock, ix );
	if (ix >= 0)
	{
		SSatz s;
		s = auftrag.m_Positionen.arr[ix];
		m_ctrlStaticBlocknummer.SetWindowText(strBlock);
		m_ctrlStaticMaterial.SetWindowText(s.m_Material);
		m_ctrlStaticMasse.SetWindowText(s.m_Laenge + _T("x") + s.m_Breite + _T("x") + s.m_Dicke);
	}
	else
	{
		m_ctrlStaticBlocknummer.SetWindowText(_T(""));
		m_ctrlStaticMaterial.SetWindowText(_T(""));
		m_ctrlStaticMasse.SetWindowText(_T(""));
	}
}
//-----------------------------------------------------------------------------------
void CGatterPlatten::AnzeigeNeuePlatte (CString strAuftrag, CString strBlock)
{
	BildschirmLoeschen();
	CAuftrag auftrag;
	auftrag = m_pOffeneAuftraege->Auftrag (strAuftrag);
	int ix;
	int anzLaenge = 0;
	auftrag.m_Positionen.FoundAt (strBlock, ix );
	if (ix >= 0)
	{
		SSatz s;
		s = auftrag.m_Positionen.arr[ix];
		if (s.m_Lieferant.GetLength() > 0)
			m_ctrlComboLieferant.SetCurSel(m_tabLieferanten.GetIndexByKey (s.m_Lieferant ));

		// wenn Platten erfasst werden sollen
		if (m_Art == _T("Platten"))
		{
			m_ctrlEditLaenge.SetWindowText(s.m_Laenge);
			anzLaenge = s.m_Laenge.GetLength();
			m_ctrlEditBreite.SetWindowText(s.m_Breite);
			CTime time = CTime::GetCurrentTime();
			CString hinweis;
			// Datum ist hier falsch. Es muss die Blocknummer und die Gatternr eingetragen werden.
			//CString datum; 
			//datum.Format(_T("%02d.%02d.%4d"),time.GetDay(),time.GetMonth(),time.GetYear());
			strAuftrag.Replace( _T("@"), _T("/") );
			m_ctrlEditHinweis.SetWindowText(strBlock + _T("-") + strAuftrag);
		}

		// wenn Blöcke erfasst werden sollen
		if (m_Art == _T("Bloecke"))
		{
			m_ctrlEditNettoLaenge.SetWindowText(s.m_Laenge);
			anzLaenge = s.m_Laenge.GetLength();
			m_ctrlEditNettoBreite.SetWindowText(s.m_Breite);
			m_ctrlEditNettoDicke.SetWindowText(s.m_Dicke);
			m_ctrlEditLaenge.SetWindowText(s.m_LaengeBrutto );
			m_ctrlEditBreite.SetWindowText(s.m_BreiteBrutto);
			m_ctrlEditDicke.SetWindowText(s.m_DickeBrutto);
			m_ctrlEditPreis.SetWindowText(s.m_Preis);
			m_ctrlEditHinweis.SetWindowText(s.m_Hinweis);
			if (s.m_Lager.GetLength() > 0)
				m_ctrlComboLager.SetCurSel(m_tabLagerOrte.GetIndexByKey (s.m_Lager));

			m_ctrlEditMenge.SetWindowText(_T("1"));
			CString tempSteinnr = _T("A");
			int ix_bloecke = m_pGatterBloecke->Exist(strBlock);
			if (ix_bloecke >= 0 && m_pGatterBloecke->Auftrag(ix_bloecke).m_Positionen.Anzahl() > 0)
				// das war der erste Versuch!!! 
				//tempSteinnr = arrZusatzRestbloecke[m_pGatterBloecke->Auftrag(ix_bloecke).m_Positionen.Anzahl()+1];
				for(int z = 1; z < 27; z++)
				{
					int ix_restblock = -1;
					m_pGatterBloecke->Auftrag(ix_bloecke).m_Positionen.FoundAt(strBlock + _T(" ") + arrZusatzRestbloecke[z], ix_restblock);
					if (ix_restblock < 0 )
					{
						tempSteinnr = arrZusatzRestbloecke[z];
						z = 27;
					}
				}
			m_ctrlEditSteinnr.SetWindowText(strBlock + _T(" ") + tempSteinnr);			
		}
	}

	if (m_Art == _T("Platten"))
		m_ctrlEditSteinnr.SetFocus();

	if (m_Art == _T("Bloecke"))
	{
		m_ctrlEditLaenge.SetFocus();
		if (anzLaenge > 0)
			m_ctrlEditLaenge.SetSel(0,anzLaenge,0);
	}
}
//-----------------------------------------------------------------------------------
void CGatterPlatten::BildschirmLoeschen()
{
	m_ctrlEditSteinnr.SetWindowText(_T(""));
	m_ctrlEditMenge.SetWindowText(_T(""));
	m_ctrlEditLaenge.SetWindowText(_T(""));
	m_ctrlEditBreite.SetWindowText(_T(""));
	m_ctrlEditDicke.SetWindowText(_T(""));
	m_ctrlEditNettoLaenge.SetWindowText(_T(""));
	m_ctrlEditNettoBreite.SetWindowText(_T(""));
	m_ctrlEditNettoDicke.SetWindowText(_T(""));
	m_ctrlEditFehlLaenge.SetWindowText(_T(""));
	m_ctrlEditFehlBreite.SetWindowText(_T(""));
	m_ctrlComboFehler.SetCurSel(-1);
	m_ctrlComboLieferant.SetCurSel(-1);
	m_ctrlComboLager.SetCurSel(-1);
	m_ctrlEditHinweis.SetWindowText(_T(""));
	m_ctrlEditPreis.SetWindowText(_T(""));
}
//-----------------------------------------------------------------------------------
void CGatterPlatten::FuellenRestblockZusatzArray ()
{
	
	arrZusatzRestbloecke[0] = _T("");
	arrZusatzRestbloecke[1] = _T("A");
	arrZusatzRestbloecke[2] = _T("B");
	arrZusatzRestbloecke[3] = _T("C");
	arrZusatzRestbloecke[4] = _T("D");
	arrZusatzRestbloecke[5] = _T("E");
	arrZusatzRestbloecke[6] = _T("F");
	arrZusatzRestbloecke[7] = _T("G");
	arrZusatzRestbloecke[8] = _T("H");
	arrZusatzRestbloecke[9] = _T("I");
	arrZusatzRestbloecke[10] = _T("J");
	arrZusatzRestbloecke[11] = _T("K");
	arrZusatzRestbloecke[12] = _T("L");
	arrZusatzRestbloecke[13] = _T("M");
	arrZusatzRestbloecke[14] = _T("N");
	arrZusatzRestbloecke[15] = _T("O");
	arrZusatzRestbloecke[16] = _T("P");
	arrZusatzRestbloecke[17] = _T("Q");
	arrZusatzRestbloecke[18] = _T("R");
	arrZusatzRestbloecke[19] = _T("S");
	arrZusatzRestbloecke[20] = _T("T");
	arrZusatzRestbloecke[21] = _T("U");
	arrZusatzRestbloecke[22] = _T("V");
	arrZusatzRestbloecke[23] = _T("W");
	arrZusatzRestbloecke[24] = _T("X");
	arrZusatzRestbloecke[25] = _T("Y");
	arrZusatzRestbloecke[26] = _T("Z");
}
//-----------------------------------------------------------------------------------
void CGatterPlatten::WerteAusDialogUebernehmen()
{
	m_ctrlEditSteinnr.GetWindowText( m_strSteinnummer);
	m_ctrlEditMenge.GetWindowText(m_strMenge);
	if (m_Art == _T("Platten"))
	{
		m_ctrlEditLaenge.GetWindowText(m_strLaenge);
		m_ctrlEditBreite.GetWindowText(m_strBreite);
		m_ctrlEditDicke.GetWindowText(m_strDicke);
	}
	if (m_Art == _T("Bloecke"))
	{
		m_ctrlEditLaenge.GetWindowText(m_strLaengeBrutto);
		m_ctrlEditBreite.GetWindowText(m_strBreiteBrutto);
		m_ctrlEditDicke.GetWindowText(m_strDickeBrutto);
		m_ctrlEditNettoLaenge.GetWindowText(m_strLaenge);
		m_ctrlEditNettoBreite.GetWindowText(m_strBreite);
		m_ctrlEditNettoDicke.GetWindowText(m_strDicke);
	}
	m_ctrlEditFehlLaenge.GetWindowText(m_strFehlLaenge);
	m_ctrlEditFehlBreite.GetWindowText(m_strFehlBreite);
	int ix;
	ix = m_ctrlComboFehler.GetCurSel();
	if (ix >= 0)
		m_strFehler = m_tabFehlerbezeichnung.GetAt(ix).m_key ;
	ix = m_ctrlComboLieferant.GetCurSel();
	if (ix >= 0)
		m_strLieferant = m_tabLieferanten.GetAt(ix).m_key ;
	ix = m_ctrlComboLager.GetCurSel();
	if (ix >= 0)
		m_strLager = m_tabLagerOrte.GetAt(ix).m_key ;
	m_ctrlEditHinweis.GetWindowText(m_strHinweis);
	m_ctrlEditPreis.GetWindowText(m_strPreis);
}
//-----------------------------------------------------------------------------------
BOOL CGatterPlatten::WerteOk()
{
if(m_strSteinnummer.CompareNoCase(_T("OHNE")))   // 
    {
    if(m_strSteinnummer.IsEmpty())
        {
        m_ctrlEditSteinnr.SetFocus();
        PlaySoundError();
        return FALSE;
        }
    }

if(!WertOk(m_strMenge,m_ctrlEditMenge)) // leer oder ungültiges format
    return FALSE;
if (!(_wtoi(m_strMenge) == CSteinSatz::StringToDouble(m_strMenge)))
{
	AfxMessageBox(Sprache(_T("Menge nicht korrekt!")));
	return FALSE;
}
if(m_strSteinnummer.CompareNoCase(_T("OHNE")))
{
	if (m_Art == _T("Platten"))
	{
		if(!WertOk(m_strLaenge,m_ctrlEditLaenge))
			return FALSE;
		if(!WertOk(m_strBreite,m_ctrlEditBreite))
			return FALSE;
		if(!WertOk(m_strDicke,m_ctrlEditDicke))
			return FALSE;
	}
	if (m_Art == _T("Bloecke"))
	{
		if(!WertOk(m_strLaenge,m_ctrlEditNettoLaenge))
			return FALSE;
		if(!WertOk(m_strBreite,m_ctrlEditNettoBreite))
			return FALSE;
		if(!WertOk(m_strDicke,m_ctrlEditNettoDicke))
			return FALSE;
		if(!WertOk(m_strLaengeBrutto,m_ctrlEditLaenge))
			return FALSE;
		if(!WertOk(m_strBreiteBrutto,m_ctrlEditBreite))
			return FALSE;
		if(!WertOk(m_strDickeBrutto,m_ctrlEditDicke))
			return FALSE;
	}
}

if(NoValueSetFocus(m_strFehlLaenge,m_ctrlEditFehlLaenge)) // leer erlaubt
    return FALSE;
if(NoValueSetFocus(m_strFehlBreite,m_ctrlEditFehlBreite))
    return FALSE;
// prüfen, ob FehlLae UND FehlBreite gefüllt sind. Wenn nur eines der Felder gefüllt ist, dann Focus auf entsprechende Feld  ch 14.02.2013
BOOL bFehlLae = FALSE;
BOOL bFehlBr = FALSE;
if (!m_strFehlLaenge.IsEmpty() || m_strFehlLaenge.GetLength() > 0)
	bFehlLae = TRUE;
if (!m_strFehlBreite.IsEmpty() || m_strFehlBreite.GetLength() > 0)
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
//-----------------------------------------------------------------------------------
BOOL CGatterPlatten::WertOk(CString& str,CEdit& edit)
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
// Alle Aufträge durchsuchen wegen höchster Nummer
int CGatterPlatten::NaechsteBuchungsnummer() const
{
int maxnum = 0;
if (m_Art == _T("Platten"))
{
	for(int i = 0; i < m_pPlatten->Anzahl(); i++)
	{
		CAuftrag *pAuf = &(m_pPlatten->Auftrag(i));
		for(int j = 0; j < pAuf->m_Positionen.Anzahl(); j++)
        {
			if(pAuf->m_Positionen.SteinSatz(j).m_buchungsNummer > maxnum)
				maxnum = pAuf->m_Positionen.SteinSatz(j).m_buchungsNummer;
        }
    }
}
if (m_Art == _T("Bloecke"))
{
	for(int i = 0; i < m_pGatterBloecke->Anzahl(); i++)
	{
		CAuftrag *pAuf = &(m_pGatterBloecke->Auftrag(i));
		for(int j = 0; j < pAuf->m_Positionen.Anzahl(); j++)
		{
			if(pAuf->m_Positionen.SteinSatz(j).m_buchungsNummer > maxnum)
				maxnum = pAuf->m_Positionen.SteinSatz(j).m_buchungsNummer;
		}
	}
}

return maxnum+1;
}
//-----------------------------------------------------------------------------------
BOOL CGatterPlatten::Steinnummern_pruefen(int ix_platten, CString strSteinnummer, CString strMenge)
{
	// ist nur bei Plattenerfassung nötig!
	if (m_Art == _T("Bloecke"))
		return TRUE;

	int nZaehler;
	nZaehler = _wtoi(strMenge);
	
	int index;
	for (int i = 0; i < nZaehler; i++)
	{
		CString suchSteinnummer;
		suchSteinnummer.Format(_T("%d"),_wtoi(strSteinnummer) + i );
		// suchen in den aktuellen GatterAufträgen bzw. erfassten Platten
		int temp = m_pPlatten->Anzahl();
		for (int p = 0; p < m_pPlatten->Anzahl(); p++)
		{
			int tempPos = m_pPlatten->Auftrag(p).m_Positionen.Anzahl();
			for( int o = 0; o < m_pPlatten->Auftrag(p).m_Positionen.Anzahl(); o++)
			{
				int nAnzahl = _wtoi(CSteinSatz::DoubleToString(m_pPlatten->Auftrag(p).m_Positionen.SteinSatz(o).Menge1()));
				nAnzahl--;
				
				CString vonNummer = m_pPlatten->Auftrag(p).m_Positionen.SteinSatz(o).Nummer ();
				CString bisNummer;
				bisNummer.Format(_T("%d"),_wtoi(vonNummer) + nAnzahl);

				if(suchSteinnummer >= vonNummer && suchSteinnummer <= bisNummer)
					return FALSE;
			}
		}
		if(m_pSteinSaetze->FoundAt(suchSteinnummer,index))
			return FALSE;
	}
	return TRUE;
}
//-----------------------------------------------------------------------------------
BOOL CGatterPlatten::CheckLager(const CString& barCode)
{
int index = m_tabLagerOrte.GetIndexByKey(barCode);
if(index >= 0)
    {
    PlaySoundScan();
    SetComboLager(barCode);
    return TRUE;
    }
return FALSE;
}
//-----------------------------------------------------------------------------------
void CGatterPlatten::SetComboLager(const CString& strLagerKey)
{
	int index = -1;
	if(!strLagerKey.IsEmpty())
		index = m_tabLagerOrte.GetIndexByKey(strLagerKey);

	if(index >= 0)
	{
		m_ctrlComboLager.SetCurSel(index);
		CString str;
		str.Format(_T("%s %s"),m_tabLagerOrte.GetAt(index).m_key,m_tabLagerOrte.GetAt(index).m_bez);
		m_ctrlComboLager.SetWindowText(str);
    }
	else
    {
		m_ctrlComboLager.SetCurSel(-1);
    }
}
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

// CGatterPlatten-Meldungshandler

void CGatterPlatten::OnBnClickedButtonHinzu()
{
	if (!m_modified)
		return;

	UpdateData(TRUE);

	WerteAusDialogUebernehmen();

	m_ctrlEditSteinnr.GetWindowText(m_strSteinnummer);
	
	int ix_platten;
	// Bei Plattenerfassung
	if (m_Art == _T("Platten"))
	{
		ix_platten = m_pPlatten->Exist(*m_pAktuellerBlock );
		if (ix_platten < 0)
		{
			CAuftrag auftrag;
			auftrag.m_strIdent = *m_pAktuellerBlock;
			m_pPlatten->Add (auftrag);
			ix_platten = m_pPlatten->Exist(*m_pAktuellerBlock );
		}
	}
	// bei Blockerfassung
	if (m_Art == _T("Bloecke"))
	{
		ix_platten = m_pGatterBloecke->Exist(*m_pAktuellerBlock );
		if (ix_platten < 0)
		{
			CAuftrag auftrag;
			auftrag.m_strIdent = *m_pAktuellerBlock;
			m_pGatterBloecke->Add (auftrag);
			ix_platten = m_pGatterBloecke->Exist(*m_pAktuellerBlock );
		}
	}

	if (!Steinnummern_pruefen(ix_platten, m_strSteinnummer, m_strMenge))
	{
		AfxMessageBox(Sprache(_T("mindestens eine Steinnummer ist bereits vergeben!")));
		return;
	}

	if(!WerteOk()) return;

	SSatz ss(g_baseSteinSatz);
	// Falls irgendwo Unsinn steht (nur prüfen wenn enabled)

	ss.m_Nummer = m_strSteinnummer;
	int ix_block;
	m_pAuftrag->m_Positionen.FoundAt (*m_pAktuellerBlock , ix_block);
	if (ix_block >= 0)
	{
		SSatz block(m_pAuftrag->Position(ix_block));
		ss.m_Material = block.m_Material ;
		ss.m_MatGr = block.m_MatGr;
		ss.m_MatNr = block.m_MatNr;
	}
	
	ss.m_Menge1 = m_strMenge;
	ss.m_ME1 = _T("Stk");
	ss.m_Laenge = m_strLaenge;
	ss.m_Breite = m_strBreite;
	ss.m_Dicke = m_strDicke;
	ss.m_FehlLaenge = m_strFehlLaenge;
	ss.m_FehlBreite = m_strFehlBreite;
	ss.m_FehlNummer = m_strFehler;
	ss.m_Lager = m_strLager;
	ss.m_Lieferant = m_strLieferant;
	ss.m_Hinweis = m_strHinweis;
	ss.m_Preis = m_strPreis;
	ss.m_Ende.Empty();
	if (m_Art == _T("Platten"))
	{
		ss.m_Artikel = _T("");
		ss.m_LaengeBrutto = _T("");
		ss.m_BreiteBrutto = _T("");
		ss.m_DickeBrutto = _T("");
	}
	if (m_Art == _T("Bloecke"))
	{
		ss.m_Artikel = _T("Block");
		ss.m_LaengeBrutto = m_strLaengeBrutto;
		ss.m_BreiteBrutto = m_strBreiteBrutto;
		ss.m_DickeBrutto = m_strDickeBrutto;
	}

	
	g_baseSteinSatz.Set(ss);

	g_baseSteinSatz.SetDatumZeit();
	g_baseSteinSatz.m_buchungsNummer = NaechsteBuchungsnummer();

	g_baseSteinSatz.SetMenge2(0.);  // immer auf 0.
	g_baseSteinSatz.SetMenge1Verfuegbar(g_baseSteinSatz.Menge1());

	// Bei Plattenerfassung
	if (m_Art == _T("Platten"))
		m_pPlatten->Auftrag(ix_platten).AddPosition(g_baseSteinSatz);
	// Bei Blockerfassung
	if (m_Art == _T("Bloecke"))
		m_pGatterBloecke->Auftrag(ix_platten).AddPosition(g_baseSteinSatz);

	//////////////////////////////////////// neu 15.3.06
	// ch 04.10.2012 die Platten sollen nicht mehr in den Lagerbestand, um zu verhindern, das falsche Daten durch die Weiterbearbeitung entstehend 
	// Blöcke werden weiterhin in den Lagerbestand aufgenommen!!
	if (m_Art == _T("Bloecke"))
		m_pSteinSaetze->AddSatz(g_baseSteinSatz); // Menge 1 zu Steinsätze hinzufügen

	////////////////////////////////////////

	PlaySoundAdd();

	// für nächste Platten vorbereiten
	BildschirmLoeschen();
	AnzeigeBlockdaten(*m_pAktuellerGatterAuftrag, *m_pAktuellerBlock);
	AnzeigeNeuePlatte(*m_pAktuellerGatterAuftrag, *m_pAktuellerBlock);
	//m_ctrlEditSteinnr.SetFocus();
	m_modified = FALSE;
	
	UpdateData(FALSE);
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
BOOL CGatterPlatten::PreTranslateMessage(MSG* pMsg) 
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
		int currId = GetFocus()->GetDlgCtrlID();
		int currId_ComboBox = GetFocus()->GetParent()->GetDlgCtrlID();
		
		if (currId_ComboBox == m_ctrlComboLager.GetDlgCtrlID())
		{
			if(CheckLager(barCode))
				return CDialog::PreTranslateMessage(pMsg);
		}

		if (currId == m_ctrlEditSteinnr.GetDlgCtrlID())
		{
			m_ctrlEditSteinnr.SetWindowText(barCode);
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


void CGatterPlatten::OnEnKillfocusEditHinweis()
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

void CGatterPlatten::OnEnChangeEditLagerort()
{
	CString str;
	m_ctrlEditLagerort.GetWindowText(str);
	int ix_Lager;
	ix_Lager = m_tabLagerOrte.GetIndexByKey (str);
	if (ix_Lager >= 0)
	{
		m_ctrlComboLager.SetCurSel(ix_Lager);
		m_ctrlEditLagerort.SetWindowText(_T(""));
		OnCbnSelendokComboLager();
		PlaySoundAdd();
	}
}

//-----------------------------------------------------------------------------------
void CGatterPlatten::OnEnChangeEditSteinnr()
{
	m_modified = TRUE;
}
void CGatterPlatten::OnEnChangeEditMenge()
{
	m_modified = TRUE;
}

void CGatterPlatten::OnEnChangeEditLaenge()
{
	m_modified = TRUE;
}

void CGatterPlatten::OnEnChangeEditBreite()
{
	m_modified = TRUE;
}

void CGatterPlatten::OnEnChangeEditDicke()
{
	m_modified = TRUE;
}

void CGatterPlatten::OnEnChangeEditNettolaenge()
{
	m_modified = TRUE;
}

void CGatterPlatten::OnEnChangeEditNettobreite()
{
	m_modified = TRUE;
}

void CGatterPlatten::OnEnChangeEditNettodicke()
{
	m_modified = TRUE;
}

void CGatterPlatten::OnEnChangeEditFehllaenge()
{
	m_modified = TRUE;
}

void CGatterPlatten::OnEnChangeEditFehlbreite()
{
	m_modified = TRUE;
}

void CGatterPlatten::OnCbnSelendokComboFehler()
{
	m_modified = TRUE;
}

void CGatterPlatten::OnCbnSelendokComboLager()
{
	m_modified = TRUE;
}

void CGatterPlatten::OnEnChangeEditHinweis()
{
	m_modified = TRUE;
}

void CGatterPlatten::OnEnChangeEditPreis()
{
	m_modified = TRUE;
}

//-----------------------------------------------------------------------------------
void CGatterPlatten::OnOK() 
{

	if (m_modified == TRUE)
	{
		int jn;
		if (m_Art == _T("Platten"))
		{
			jn = AfxMessageBox(Sprache(_T("Soll die aktuelle Steinnummer hinzugefügt werden?")),MB_YESNO);
		}
		if (m_Art == _T("Bloecke"))
		{
			jn = AfxMessageBox(Sprache(_T("Soll der aktuelle Restblock hinzugefügt werden?")),MB_YESNO);
		}
		
		if(jn == IDYES)
        {
			OnBnClickedButtonHinzu();
			if (m_modified == TRUE)
				return;
        }
       
	}

CDialog::OnOK();
}
//------------------------------------------------------------------------------------------

