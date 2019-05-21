// GatterOffeneAuftraege.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "GatterOffeneAuftraege.h"
#include "GatterPlatten.h"
#include "GatterDaten.h"
#include "GatterStandfuge.h"
#include "PositionenInfo.h"


// CGatterOffeneAuftraege-Dialogfeld

IMPLEMENT_DYNAMIC(CGatterOffeneAuftraege, CDialog)

CGatterOffeneAuftraege::CGatterOffeneAuftraege(CWnd* pParent /*=NULL*/)
	: CDialog(CGatterOffeneAuftraege::IDD, pParent)
{

}

CGatterOffeneAuftraege::~CGatterOffeneAuftraege()
{
}

void CGatterOffeneAuftraege::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_GATTERLADUNG, m_ctrlStaticGatterLadung);
	DDX_Control(pDX, IDC_COMBO_GATTER, m_ctrlComboGatter);
	DDX_Control(pDX, IDC_COMBO_BLOECKE, m_ctrlComboBloecke);
	DDX_Control(pDX, IDC_STATIC_PLATTEN, m_ctrlStaticPlatten);
	DDX_Control(pDX, IDC_LIST_POSITIONEN, m_ctrlListPositionen);
	DDX_Control(pDX, IDC_BUTTON_PLATTEN, m_ctrlButtonPlatten);
	DDX_Control(pDX, IDC_BUTTON_GATTERDATEN, m_ctrlButtonGatterdaten);
	DDX_Control(pDX, IDC_BUTTON_STANDFUGE, m_ctrlButtonStandfuge);
	DDX_Control(pDX, IDC_STATIC_BLOECKE, m_ctrlStaticBlock);
	DDX_Control(pDX, IDC_BUTTON_LOESCHPOSITION, m_ctrlButtonLoeschPosition);
	DDX_Control(pDX, IDC_STATIC_LOESCHPOSITION, m_ctrlStaticLoeschPosition);
	DDX_Control(pDX, IDC_BUTTON_POSANZEIGEN, m_ctrlButtonPosAnzeigen);
	DDX_Control(pDX, IDC_STATIC_RESTBLOCK, m_ctrlStaticRestbloecke);
	DDX_Control(pDX, IDC_LIST_RESTBLOCK, m_ctrlListRestbloecke);
	DDX_Control(pDX, IDC_BUTTON_BLOCKANZEIGEN, m_ctrlButtonBlockAnzeigen);
	DDX_Control(pDX, IDC_STATIC_LOESCHRESTBLOCK, m_ctrlStaticLoeschRestblock);
	DDX_Control(pDX, IDC_BUTTON_LOESCHRESTBLOCK, m_ctrlButtonLoeschRestblock);
	DDX_Control(pDX, IDC_BUTTON_RESTBLOECKE, m_ctrlButtonRestbloecke);
}


BEGIN_MESSAGE_MAP(CGatterOffeneAuftraege, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_GATTER, &CGatterOffeneAuftraege::OnCbnSelchangeComboGatter)
	ON_BN_CLICKED(IDC_BUTTON_PLATTEN, &CGatterOffeneAuftraege::OnBnClickedButtonPlatten)
	ON_BN_CLICKED(IDC_BUTTON_POSANZEIGEN, &CGatterOffeneAuftraege::OnBnClickedButtonPosanzeigen)
	ON_BN_CLICKED(IDC_BUTTON_LOESCHPOSITION, &CGatterOffeneAuftraege::OnBnClickedButtonLoeschposition)
	ON_CBN_SELCHANGE(IDC_COMBO_BLOECKE, &CGatterOffeneAuftraege::OnCbnSelchangeComboBloecke)
	ON_BN_CLICKED(IDC_BUTTON_GATTERDATEN, &CGatterOffeneAuftraege::OnBnClickedButtonGatterdaten)
	ON_BN_CLICKED(IDC_BUTTON_STANDFUGE, &CGatterOffeneAuftraege::OnBnClickedButtonStandfuge)
	ON_BN_CLICKED(IDC_BUTTON_BLOCKANZEIGEN, &CGatterOffeneAuftraege::OnBnClickedButtonBlockanzeigen)
	ON_BN_CLICKED(IDC_BUTTON_LOESCHRESTBLOCK, &CGatterOffeneAuftraege::OnBnClickedButtonLoeschrestblock)
	ON_BN_CLICKED(IDC_BUTTON_RESTBLOECKE, &CGatterOffeneAuftraege::OnBnClickedButtonRestbloecke)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------------
BOOL CGatterOffeneAuftraege::OnInitDialog()
{
	CDialog::OnInitDialog();

	CenterWindow(GetDesktopWindow());	// center to the hpc screen

	TranslateStatic(m_ctrlStaticGatterLadung );
	TranslateStatic(m_ctrlStaticBlock);
	TranslateStatic(m_ctrlStaticPlatten);
	TranslateStatic(m_ctrlStaticLoeschPosition);
	TranslateStatic(m_ctrlStaticRestbloecke);
	TranslateStatic(m_ctrlStaticLoeschRestblock);
	TranslateButton(m_ctrlButtonStandfuge);
	TranslateButton(m_ctrlButtonPlatten);
	TranslateButton(m_ctrlButtonPosAnzeigen);
	TranslateButton(m_ctrlButtonGatterdaten);
	TranslateButton(m_ctrlButtonRestbloecke);
	TranslateButton(m_ctrlButtonBlockAnzeigen);
	

	// Wenn Gatterdaten vorhanden wird entweder das erste oder das zuletzt verwendete ausgewählt
	if (m_pOffeneAuftraege->Anzahl() > 0)
	{
		if (m_pstrLetzterGatterAuftrag->GetLength() > 0)
		{
			int ix = m_pOffeneAuftraege->Exist (*m_pstrLetzterGatterAuftrag );
			if (ix >= 0)
			{
				FuellenComboBoxGatter(*m_pstrLetzterGatterAuftrag);
				SetPositionenListe();
				SetBlockListe();
				AnzeigeButtons();
			}
			else
			{
				FuellenComboBoxGatter(_T(""));
				SetPositionenListe();
				SetBlockListe();
				AnzeigeButtons();
			}
		}
		else
		{
			FuellenComboBoxGatter(_T(""));
			SetPositionenListe();
			SetBlockListe();
			AnzeigeButtons();
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}
//-----------------------------------------------------------------------------------
void CGatterOffeneAuftraege::FuellenComboBoxGatter (CString strAuftrag)
{
	m_ctrlComboGatter.ResetContent ();
	for (int i = 0; i < m_pOffeneAuftraege->Anzahl(); i++)
	{
		m_ctrlComboGatter.AddString (m_pOffeneAuftraege->Auftrag (i).m_strIdent);
	}
	
	if (m_ctrlComboGatter.GetCount () > 0)
	{
		int index = m_pOffeneAuftraege->Exist (strAuftrag);
		if (index >= 0)
		{
			m_ctrlComboGatter.SetCurSel (index);
			FuellenComboBoxBloecke(*m_pstrLetzterBlock);
		}
		else
		{
			m_ctrlComboGatter.SetCurSel (0);
			FuellenComboBoxBloecke(_T(""));
		}
	}
}
void CGatterOffeneAuftraege::FuellenComboBoxBloecke(CString strBlocknr)
{
	m_ctrlComboBloecke.ResetContent ();
	int ix = m_ctrlComboGatter.GetCurSel();
	CAuftrag auftrag = m_pOffeneAuftraege->Auftrag (ix);

	int ix_blocknr = 0;

	for (int i = 0; i < auftrag.m_Positionen.Anzahl(); i++)
	{
		m_ctrlComboBloecke.AddString (auftrag.Position(i).Nummer());
		// wenn die Blocknummer dem Parmeter der Funktion entspricht, dann den Index merken, um den Eintrag später zu selektieren
		if (strBlocknr.GetLength() > 0 && auftrag.Position (i).Nummer () == strBlocknr)
			ix_blocknr = i;
	}
	
	if (m_ctrlComboBloecke.GetCount () > 0)
		m_ctrlComboBloecke.SetCurSel (ix_blocknr);
}
//-----------------------------------------------------------------------------------
BOOL CGatterOffeneAuftraege::CheckBlocknr(const CString& barCode)
{
int index = m_ctrlComboBloecke.FindString (-1,barCode);
if(index >= 0)
    {
    PlaySoundScan();
	m_ctrlComboBloecke.SetCurSel (index);
	SetPositionenListe();
	SetBlockListe();
    return TRUE;
    }
return FALSE;
}
//-----------------------------------------------------------------------------------
void CGatterOffeneAuftraege::SetPositionenListe()
{
	m_ctrlListPositionen.ResetContent();

	int aufix = m_ctrlComboGatter.GetCurSel();
	CAuftrag auftrag = m_pOffeneAuftraege->Auftrag (aufix);
	*m_pstrLetzterGatterAuftrag = auftrag.m_strIdent;
	if (auftrag.m_strIdent.Right(2) == _T("-S") || auftrag.m_strIdent.Right(2) == _T("-T"))
		return;

	int blockix;
	CString blocknr;
	blockix = m_ctrlComboBloecke.GetCurSel();
	blocknr = auftrag.Position (blockix).Nummer ();
	*m_pstrLetzterBlock = blocknr ;
	
	int index;
	index = m_pPlatten->Exist(blocknr);
	if(index >= 0)
    {
		CAuftrag auf = m_pPlatten->Auftrag(index);
		for(int i = 0; i < auf.m_Positionen.Anzahl(); i++)
		{
			CString strMenge1;
			strMenge1.Format (_T("%.0f"), auf.Position(i).Menge1());
			strMenge1 = _T(" (") + strMenge1 + _T("Stk)");
			if(auf.Position(i).Menge1() < 0)
				m_ctrlListPositionen.AddString(auf.Position(i).Nummer() + strMenge1 + _T("->"));
			else
				m_ctrlListPositionen.AddString( auf.Position(i).Nummer() + strMenge1);
        }
	}
}
//-----------------------------------------------------------------------------------
void CGatterOffeneAuftraege::SetBlockListe()
{
	m_ctrlListRestbloecke.ResetContent();

	int aufix = m_ctrlComboGatter.GetCurSel();
	CAuftrag auftrag = m_pOffeneAuftraege->Auftrag (aufix);
	*m_pstrLetzterGatterAuftrag = auftrag.m_strIdent;
	if (auftrag.m_strIdent.Right(2) == _T("-S"))
		return;

	int blockix;
	CString blocknr;
	blockix = m_ctrlComboBloecke.GetCurSel();
	blocknr = auftrag.Position (blockix).Nummer ();
	*m_pstrLetzterBlock = blocknr ;
	
	int index;
	index = m_pGatterBloecke->Exist(blocknr);
	if(index >= 0)
    {
		CAuftrag auf = m_pGatterBloecke->Auftrag(index);
		for(int i = 0; i < auf.m_Positionen.Anzahl(); i++)
		{
			if(auf.Position(i).Menge1() < 0)
				m_ctrlListRestbloecke.AddString(auf.Position(i).Nummer() + _T("->"));
			else
				m_ctrlListRestbloecke.AddString( auf.Position(i).Nummer());
        }
	}
}
//-----------------------------------------------------------------------------------
void CGatterOffeneAuftraege::AnzeigeButtons()
{
		// anhand der Art des Gatterauftrags die verschiedenen Buttons anzeigen
	int aufix = m_ctrlComboGatter.GetCurSel();
	CString strAuftrag = m_pOffeneAuftraege->Auftrag (aufix).m_strIdent;
	if (strAuftrag.Right(2) == _T("-S"))
	{
		m_ctrlButtonStandfuge.ShowWindow(TRUE);
		m_ctrlButtonPlatten.ShowWindow(FALSE);
		m_ctrlButtonPosAnzeigen.ShowWindow(FALSE);
		m_ctrlButtonRestbloecke.ShowWindow(FALSE);
		m_ctrlButtonBlockAnzeigen.ShowWindow(FALSE);
	}
	else
	{
		if (strAuftrag.Right(2) == _T("-T"))
		{
			m_ctrlButtonStandfuge.ShowWindow(TRUE);
			m_ctrlButtonPlatten.ShowWindow(FALSE);
			m_ctrlButtonPosAnzeigen.ShowWindow(FALSE);
			m_ctrlButtonRestbloecke.ShowWindow(TRUE);
			m_ctrlButtonBlockAnzeigen.ShowWindow(TRUE);
		}
		else
		{
			m_ctrlButtonStandfuge.ShowWindow(FALSE);
			m_ctrlButtonPlatten.ShowWindow(TRUE);
			m_ctrlButtonPosAnzeigen.ShowWindow(TRUE);
			m_ctrlButtonRestbloecke.ShowWindow(TRUE);
			m_ctrlButtonBlockAnzeigen.ShowWindow(TRUE);
		}
	}
}
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
// CGatterOffeneAuftraege-Meldungshandler

void CGatterOffeneAuftraege::OnCbnSelchangeComboGatter()
{
	FuellenComboBoxBloecke(_T(""));
	SetPositionenListe();
	SetBlockListe();

	// anhand der Art des Gatterauftrags die verschiedenen Buttons anzeigen
	AnzeigeButtons();	
}
void CGatterOffeneAuftraege::OnCbnSelchangeComboBloecke()
{
	SetPositionenListe();
	SetBlockListe();
}

//-----------------------------------------------------------------------------------
void CGatterOffeneAuftraege::OnBnClickedButtonPlatten()
{
	m_ctrlComboGatter.GetWindowText(m_strAktuellerGatterAuftrag);
	int index = m_pOffeneAuftraege->Exist(m_strAktuellerGatterAuftrag);
	if(index < 0)
	    return;     // Kein Auftrag vorgegeben

	// zuerst müssen die Gatterdaten erfasst werden, damit sie nicht vergessen werden! ch 25.09.2012
	if (m_pGatterDaten->Exist(m_strAktuellerGatterAuftrag ) < 0)
	{
		AfxMessageBox(Sprache(_T("Bitte zuerst Gatterdaten erfassen!")), 0, 0);
		return;
	}
	
	int index_block;
	m_ctrlComboBloecke.GetWindowText(m_strAktuellerBlock);
	if (!(m_pOffeneAuftraege->Auftrag(index).m_Positionen.FoundAt (m_strAktuellerBlock, index_block)) )
		return;

    CGatterPlatten positionenDialog(this);

    positionenDialog.m_pSteinSaetze = m_pSteinSaetze;       // Original-Steinsatztabelle
    positionenDialog.m_pOffeneAuftraege = m_pOffeneAuftraege;
	positionenDialog.m_pPlatten= m_pPlatten ;
    positionenDialog.m_pAuftrag = &m_pOffeneAuftraege->Auftrag(index);
    positionenDialog.m_pScanner = m_pScanner;
	positionenDialog.m_pAktuellerGatterAuftrag = &m_strAktuellerGatterAuftrag;
	positionenDialog.m_pAktuellerBlock = &m_strAktuellerBlock;
	positionenDialog.m_Art = _T("Platten");
	
	m_pScanner->setEnableScanner(TRUE);
    positionenDialog.DoModal();
    m_pScanner->setEnableScanner(TRUE);

	SetPositionenListe();

	CString strButt;

	m_pPlatten->Save();
	// ist nicht mehr nötig, da die Platten nicht mehr in den Lagerbestand kommen ch 04.10.2012
	//m_pSteinSaetze->m_modified = TRUE;

	// Hinweis, das die Gatterdaten erfasst werden (damit es nicht vergessen wird! ch 25.09.2012
	if (m_pGatterDaten->Exist(m_strAktuellerGatterAuftrag ) < 0)
	{
		AfxMessageBox(Sprache(_T("Bitte Gatterdaten erfassen!")), 0, 0);
	}
}

void CGatterOffeneAuftraege::OnBnClickedButtonPosanzeigen()
{
	int index;
	//index = m_ctrlComboBloecke.GetCurSel();
	CString blocknr;
	m_ctrlComboBloecke.GetWindowText(blocknr );
	index = m_pPlatten->Exist(blocknr);
	if(index < 0)
		return;
	if(!m_pPlatten->Auftrag(index).m_Positionen.Anzahl())
	    return;
	int posix = m_ctrlListPositionen .GetCurSel();
	if(posix < 0) posix = 0;
	
	CPositionenInfo info(this);
	info.m_pSaetze = &(m_pPlatten->Auftrag(index).m_Positionen);
	info.m_index = posix;
	
	m_pScanner->setEnableScanner(FALSE);
	info.DoModal();
	m_pScanner->setEnableScanner(TRUE);
}

void CGatterOffeneAuftraege::OnBnClickedButtonLoeschposition()
{
	CString errMsg;
	int posix = m_ctrlListPositionen.GetCurSel();

	CString blocknr;
	m_ctrlComboBloecke.GetWindowText(blocknr );
	int aufix = m_pPlatten->Exist(blocknr );

	if(posix >= 0)
	{
		if(AfxMessageBox(Sprache(_T("Wollen Sie die Zuordnung wirklich löschen?")),MB_YESNO|MB_ICONQUESTION)
                     == IDYES)
		{
			CAuftrag *pCurAuf;
			pCurAuf = &m_pPlatten->arr[aufix];
			
			// ch 04.10.2012: die zugebuchten Platten werden ab jetzt nicht mehr im Lagerbestand gespeichert (wegen evtl. Fehler bei der Weiterbearbeitung)
			// Damit entfällt hier auch das Löschen!
			/*int steinix;
			m_pSteinSaetze->FoundAt (pCurAuf->m_Positionen.arr[posix].Nummer(), steinix);
			if (steinix >= 0)
			{
				if(fabs(pCurAuf->Position(posix).Menge1()-m_pSteinSaetze->SteinSatz(steinix).Menge1()) < 0.01)
					m_pSteinSaetze->RemoveAt(steinix);
				else
					m_pSteinSaetze->SubSatz(pCurAuf->m_Positionen.arr[posix]); // Menge wieder aus Steinliste entfernen
			}*/
			       
			pCurAuf->m_Positionen.RemoveAt(posix);
			SetPositionenListe();
		    if(posix >= m_ctrlListPositionen.GetCount())
				posix--;
			if(m_ctrlListPositionen.GetCount() > 0)
				m_ctrlListPositionen.SetCurSel(posix);
      
		    m_pPlatten->Save();
			// nicht mehr nötig - siehe oben
			// m_pSteinSaetze->m_modified = TRUE;
		}
	}
}


//-----------------------------------------------------------------------------------
void CGatterOffeneAuftraege::OnBnClickedButtonGatterdaten()
{
	m_ctrlComboGatter.GetWindowText(m_strAktuellerGatterAuftrag);
	int index = m_pOffeneAuftraege->Exist(m_strAktuellerGatterAuftrag);
	if(index < 0)
	    return;     // Kein Auftrag vorgegeben
	
	CGatterDaten erfassenDaten(this);

	erfassenDaten.m_pOffeneAuftraege = m_pOffeneAuftraege;
	erfassenDaten.m_pGatterDaten = m_pGatterDaten;
	erfassenDaten.m_pScanner = m_pScanner;
	erfassenDaten.m_pAktuellerGatterAuftrag = &m_strAktuellerGatterAuftrag;

	m_pScanner->setEnableScanner(TRUE);
    erfassenDaten.DoModal();
	m_pScanner->setEnableScanner(TRUE);

	m_pGatterDaten->Save();

	if (m_strAktuellerGatterAuftrag.Right(2) != _T("-S") && m_strAktuellerGatterAuftrag.Right(2) != _T("-T") )
	{
		for (int i = 0; i < m_pOffeneAuftraege->Auftrag(index).m_Positionen.Anzahl(); i++)
		{
			if (m_pPlatten->Exist(m_pOffeneAuftraege->Auftrag(index).Position(i).Nummer()) < 0)
			{
				AfxMessageBox(Sprache(_T("Es wurden nicht für alle Blöcke Platten erfasst. Bitte Platten erfassen!")),0, 0);
				i = m_pOffeneAuftraege->Auftrag(index).m_Positionen.Anzahl();
			}
		}
	}
}

//-----------------------------------------------------------------------------------
void CGatterOffeneAuftraege::OnBnClickedButtonStandfuge()
{
	m_ctrlComboGatter.GetWindowText(m_strAktuellerGatterAuftrag);
	int index = m_pOffeneAuftraege->Exist(m_strAktuellerGatterAuftrag);
	if(index < 0)
	    return;     // Kein Auftrag vorgegeben
	
	// zuerst müssen die Gatterdaten erfasst werden, damit sie nicht vergessen werden! ch 17.01.2013
	if (m_pGatterDaten->Exist(m_strAktuellerGatterAuftrag ) < 0)
	{
		AfxMessageBox(Sprache(_T("Bitte zuerst Gatterdaten erfassen!")), 0, 0);
		return;
	}

	CGatterStandfuge erfassenDaten(this);

	erfassenDaten.m_pOffeneAuftraege = m_pOffeneAuftraege;
	erfassenDaten.m_pGatterDaten = m_pGatterDaten;
	erfassenDaten.m_pScanner = m_pScanner;
	erfassenDaten.m_pAktuellerGatterAuftrag = &m_strAktuellerGatterAuftrag;

	m_pScanner->setEnableScanner(FALSE);
    erfassenDaten.DoModal();
	m_pScanner->setEnableScanner(TRUE);

	m_pGatterDaten->Save();
}


//-----------------------------------------------------------------------------------
void CGatterOffeneAuftraege::OnBnClickedButtonRestbloecke()
{
	m_ctrlComboGatter.GetWindowText(m_strAktuellerGatterAuftrag);
	int index = m_pOffeneAuftraege->Exist(m_strAktuellerGatterAuftrag);
	if(index < 0)
	    return;     // Kein Auftrag vorgegeben
	
	// zuerst müssen die Gatterdaten erfasst werden, damit sie nicht vergessen werden! ch 25.09.2012
	if (m_pGatterDaten->Exist(m_strAktuellerGatterAuftrag ) < 0)
	{
		AfxMessageBox(Sprache(_T("Bitte zuerst Gatterdaten erfassen!")), 0, 0);
		return;
	}

	int index_block;
	m_ctrlComboBloecke.GetWindowText(m_strAktuellerBlock);
	if (!(m_pOffeneAuftraege->Auftrag(index).m_Positionen.FoundAt (m_strAktuellerBlock, index_block)) )
		return;

    CGatterPlatten positionenDialog(this);

    positionenDialog.m_pSteinSaetze = m_pSteinSaetze;       // Original-Steinsatztabelle
    positionenDialog.m_pOffeneAuftraege = m_pOffeneAuftraege;
	positionenDialog.m_pPlatten= m_pPlatten ;
	positionenDialog.m_pGatterBloecke = m_pGatterBloecke;
    positionenDialog.m_pAuftrag = &m_pOffeneAuftraege->Auftrag(index);
    positionenDialog.m_pScanner = m_pScanner;
	positionenDialog.m_pAktuellerGatterAuftrag = &m_strAktuellerGatterAuftrag;
	positionenDialog.m_pAktuellerBlock = &m_strAktuellerBlock;
	positionenDialog.m_Art = _T("Bloecke");
	
	m_pScanner->setEnableScanner(FALSE);
    positionenDialog.DoModal();
    m_pScanner->setEnableScanner(TRUE);

	SetBlockListe();

	CString strButt;

	m_pGatterBloecke->Save();
	m_pSteinSaetze->m_modified = TRUE;

	// Hinweis, das die Gatterdaten erfasst werden (damit es nicht vergessen wird! ch 25.09.2012
	if (m_pGatterDaten->Exist(m_strAktuellerGatterAuftrag ) < 0)
	{
		AfxMessageBox(Sprache(_T("Bitte Gatterdaten erfassen!")), 0, 0);
	}
}

void CGatterOffeneAuftraege::OnBnClickedButtonBlockanzeigen()
{
	int index;

	CString blocknr;
	m_ctrlComboBloecke.GetWindowText(blocknr );
	index = m_pGatterBloecke->Exist(blocknr);
	if(index < 0)
		return;
	if(!m_pGatterBloecke->Auftrag(index).m_Positionen.Anzahl())
	    return;
	int posix = m_ctrlListRestbloecke.GetCurSel();
	if(posix < 0) posix = 0;
	
	CPositionenInfo info(this);
	info.m_pSaetze = &(m_pGatterBloecke->Auftrag(index).m_Positionen);
	info.m_index = posix;
	
	m_pScanner->setEnableScanner(FALSE);
	info.DoModal();
	m_pScanner->setEnableScanner(TRUE);
}


void CGatterOffeneAuftraege::OnBnClickedButtonLoeschrestblock()
{
	CString errMsg;
	int posix = m_ctrlListRestbloecke.GetCurSel();

	CString blocknr;
	m_ctrlComboBloecke.GetWindowText(blocknr );
	int aufix = m_pGatterBloecke->Exist(blocknr );

	if(posix >= 0)
	{
		if(AfxMessageBox(Sprache(_T("Wollen Sie die Zuordnung wirklich löschen?")),MB_YESNO|MB_ICONQUESTION)
                     == IDYES)
		{
			CAuftrag *pCurAuf;
			pCurAuf = &m_pGatterBloecke->arr[aufix];

			int steinix;
			m_pSteinSaetze->FoundAt (pCurAuf->m_Positionen.arr[posix].Nummer(), steinix);
			if (steinix >= 0)
			{
				if(fabs(pCurAuf->Position(posix).Menge1()-m_pSteinSaetze->SteinSatz(steinix).Menge1()) < 0.01)
				    m_pSteinSaetze->RemoveAt(steinix);
				else
					m_pSteinSaetze->SubSatz(pCurAuf->m_Positionen.arr[posix]); // Menge wieder aus Steinliste entfernen
			}
			       
			pCurAuf->m_Positionen.RemoveAt(posix);
			SetBlockListe();
			if(posix >= m_ctrlListRestbloecke.GetCount())
				posix--;
			if(m_ctrlListRestbloecke.GetCount() > 0)
				m_ctrlListRestbloecke.SetCurSel(posix);
      
			m_pGatterBloecke->Save();
			m_pSteinSaetze->m_modified = TRUE;
		}
	}
}
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
BOOL CGatterOffeneAuftraege::PreTranslateMessage(MSG* pMsg) 
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
		
		if (currId_ComboBox == m_ctrlComboBloecke.GetDlgCtrlID())
		{
		    if(CheckBlocknr(barCode))
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
