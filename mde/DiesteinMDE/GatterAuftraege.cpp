// GatterAuftrage.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "Positionen.h"
#include "PositionenInfo.h"
#include "GatterAuftraege.h"
#include "GatterNeu.h"



// CGatterAuftrage-Dialogfeld

IMPLEMENT_DYNAMIC(CGatterAuftraege, CDialog)

CGatterAuftraege::CGatterAuftraege(CWnd* pParent /*=NULL*/)
	: CDialog(CGatterAuftraege::IDD, pParent)
{
	m_strAktuellerGatterAuftrag = _T("");
	m_strGatterPosition = _T("");
	m_nModus = ID_GATTERN;
}

CGatterAuftraege::~CGatterAuftraege()
{
}

void CGatterAuftraege::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_GATTER, m_ctrlStaticGatter);
	DDX_Control(pDX, IDC_COMBO_GATTER, m_ctrlComboGatter);
	DDX_Control(pDX, IDC_STATIC_POSITIONEN, m_ctrlStaticPositionen);
	DDX_Control(pDX, IDC_LIST_POSITIONEN, m_ctrlListPositionen);
	DDX_Control(pDX, IDC_BUTTON_POSANZEIGEN, m_ctrlButtonPosAnzeigen);
	DDX_Control(pDX, IDC_BUTTON_LOESCHPOSITION2, m_ctrlButtonPosLoeschen);
	DDX_Control(pDX, IDC_STATIC_LOESCHPOSITION2, m_ctrlStaticPosLoeschen);
	DDX_Control(pDX, IDC_BUTTON_LOESCHAUFTRAG, m_ctrlButtonAufLoeschen);
	DDX_Control(pDX, IDC_STATIC_LOESCHAUFTRAG, m_ctrlStaticAufLoeschen);
	DDX_Control(pDX, IDC_BUTTON_HINZU, m_ctrlButtonHinzu);
	DDX_Control(pDX, IDC_BUTTON_BEARBEITEN, m_ctrlButtonBearbeiten);
}


BEGIN_MESSAGE_MAP(CGatterAuftraege, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_GATTER, &CGatterAuftraege::OnCbnSelchangeComboGatter)
	ON_BN_CLICKED(IDC_BUTTON_HINZU, &CGatterAuftraege::OnBnClickedButtonHinzu)
	ON_BN_CLICKED(IDC_BUTTON_BEARBEITEN, &CGatterAuftraege::OnBnClickedButtonBearbeiten)
	ON_BN_CLICKED(IDC_BUTTON_POSANZEIGEN, &CGatterAuftraege::OnBnClickedButtonPosanzeigen)
	ON_BN_CLICKED(IDC_BUTTON_LOESCHPOSITION2, &CGatterAuftraege::OnBnClickedButtonLoeschposition2)
	ON_BN_CLICKED(IDC_BUTTON_LOESCHAUFTRAG, &CGatterAuftraege::OnBnClickedButtonLoeschauftrag)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------------
BOOL CGatterAuftraege::OnInitDialog()
{
	CDialog::OnInitDialog();

	CenterWindow(GetDesktopWindow());	// center to the hpc screen

	TranslateStatic(m_ctrlStaticGatter );
	TranslateStatic(m_ctrlStaticAufLoeschen);
	TranslateStatic(m_ctrlStaticPositionen);
	TranslateStatic(m_ctrlStaticPosLoeschen);
	TranslateButton(m_ctrlButtonHinzu);
	TranslateButton(m_ctrlButtonBearbeiten);
	TranslateButton(m_ctrlButtonPosAnzeigen);


	// Wenn Gatterdaten vorhanden wird entweder das erste oder das zuletzt verwendete ausgewählt
	if (m_pAuftraege->Anzahl() > 0)
	{
		if (m_pstrLetzterGatterAuftrag->GetLength() > 0)
		{
			int ix = m_pAuftraege->Exist (*m_pstrLetzterGatterAuftrag );
			if (ix >= 0)
			{
				FuellenComboBox(*m_pstrLetzterGatterAuftrag);
				SetPositionenListe(*m_pstrLetzterGatterAuftrag);
			}
			else
			{
				FuellenComboBox(_T(""));
				SetPositionenListe(m_pAuftraege->Auftrag (0).m_strIdent );
			}
		}
		else
		{
			FuellenComboBox(_T(""));
			SetPositionenListe(m_pAuftraege->Auftrag (0).m_strIdent );
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}
//-----------------------------------------------------------------------------------
void CGatterAuftraege::FuellenComboBox(CString strAuftrag)
{
	m_ctrlComboGatter.ResetContent ();
	for (int i = 0; i < m_pAuftraege->Anzahl(); i++)
	{
		m_ctrlComboGatter.AddString (m_pAuftraege->Auftrag (i).m_strIdent);
	}
	
	if (m_ctrlComboGatter.GetCount () > 0)
	{
		int index = m_pAuftraege->Exist (strAuftrag);
		if (index >= 0)
			m_ctrlComboGatter.SetCurSel (index);
		else
			m_ctrlComboGatter.SetCurSel (0);
	}
}
//-----------------------------------------------------------------------------------
CString CGatterAuftraege::GetGatter (CString strAuftrag)
{
	CString gatter;
	int pos = strAuftrag.Find (_T("@"),0);
	if (pos > 0)
		gatter = strAuftrag.Left (pos);
	return gatter;
}

CString CGatterAuftraege::GetLadung (CString strAuftrag)
{
	CString ladung;
	int pos = strAuftrag.Find (_T("@"),0);
	pos += 1;
	if (pos > 0 && pos < strAuftrag.GetLength())
	{
		ladung = strAuftrag.Right(strAuftrag.GetLength() - pos);
		if (ladung.Right(2) == _T("-S"))
			ladung = ladung.Left(ladung.GetLength() - 2);
	}
	return ladung;
}

//-----------------------------------------------------------------------------------
void CGatterAuftraege::AnzeigeDaten(int ix)
{
	/*C4String gatter(m_tabGatter.GetAt (ix));
	int ladung =  _ttoi(gatter.m_value2);
	ladung += 1;
	TCHAR temp[20];
	_itot(ladung,temp, 10);
	m_ctrlEditLadung.SetWindowText( temp );*/
}
//-----------------------------------------------------------------------------------
void CGatterAuftraege::SetPositionenListe(CString strAuftrag)
{
m_ctrlListPositionen.ResetContent();
int index = m_pAuftraege->Exist(strAuftrag);
if(index >= 0)
    {
    CAuftrag auf = m_pAuftraege->Auftrag(index);
    for(int i = 0; i < auf.m_Positionen.Anzahl(); i++)
        {
        if(auf.Position(i).Menge1() < 0)
            m_ctrlListPositionen.AddString(auf.Position(i).Nummer() + _T("->"));
        else
            m_ctrlListPositionen.AddString(auf.Position(i).Nummer());
        }
   	*m_pstrLetzterGatterAuftrag = m_pAuftraege->Auftrag(index).m_strIdent;
    }
}
//-----------------------------------------------------------------------------------
int CGatterAuftraege::FindeLetztenGatterAuftrag (const CString gatter)
{
	int erg = -1;
	if (m_pAuftraege->Anzahl() > 0)
	{
		for( int i = 0; i < m_pAuftraege->Anzahl(); i++)
		{
			CString temp;
			temp = GetGatter( m_pAuftraege->Auftrag (i).m_strIdent );
			if (temp == gatter)
				erg = i;
		}
	}
	return erg;
}

//-----------------------------------------------------------------------------------
// CGatterAuftrage-Meldungshandler
//-----------------------------------------------------------------------------------
void CGatterAuftraege::OnCbnSelchangeComboGatter()
{
	int ix = m_ctrlComboGatter.GetCurSel ();
	SetPositionenListe(m_pAuftraege->Auftrag(ix).m_strIdent );
}

//-----------------------------------------------------------------------------------
void CGatterAuftraege::OnBnClickedButtonHinzu()
{
	CGatterNeu dlgGatterNeu;
	dlgGatterNeu.m_pAuftraege = m_pAuftraege;
	dlgGatterNeu.DoModal();

	int x = m_pAuftraege->Anzahl();
	if (m_pAuftraege->Anzahl() > 0)
	{
		CString temp = m_pAuftraege->Auftrag (m_pAuftraege->Anzahl() - 1).m_strIdent ;
		FuellenComboBox(temp);
		SetPositionenListe(temp);
	}
	
}
//-----------------------------------------------------------------------------------
void CGatterAuftraege::OnBnClickedButtonBearbeiten()
{
	m_ctrlComboGatter.GetWindowText(m_strAktuellerGatterAuftrag);
	int index = m_pAuftraege->Exist(m_strAktuellerGatterAuftrag);
	if(index < 0)
	    return;     // Kein Auftrag vorgegeben

    CPositionen	positionenDialog(this);

    positionenDialog.m_nModus = m_nModus;   // Verkauf,Lieferung,Produktion,Reservierung,Zugang,Inventur
    positionenDialog.m_pSteinSaetze = m_pSteinSaetze;       // Original-Steinsatztabelle
    positionenDialog.m_pAuftraege = m_pAuftraege;
    positionenDialog.m_pAuftrag = &m_pAuftraege->Auftrag(index);
	positionenDialog.m_pOffeneAuftraege = m_pOffeneAuftraege;
    positionenDialog.m_pScanner = m_pScanner;

    positionenDialog.DoModal();
    
	m_pScanner->setEnableScanner(TRUE);

//	SetComboBox(m_strAktuellerGatterAuftrag);
	SetPositionenListe(m_pAuftraege->Auftrag(index).m_strIdent);

	CString strButt;

	m_pAuftraege->Save();
	m_pSteinSaetze->m_modified = TRUE;
}

//-----------------------------------------------------------------------------------
void CGatterAuftraege::OnBnClickedButtonPosanzeigen()
{
	if(!m_pAuftraege->Anzahl())
		return;
	m_ctrlComboGatter.GetWindowText(m_strAktuellerGatterAuftrag);
	int aufix = m_pAuftraege->Exist(m_strAktuellerGatterAuftrag);
	if(aufix < 0) return;
	if(!m_pAuftraege->Auftrag(aufix).m_Positionen.Anzahl())
	    return;
	int posix = m_ctrlListPositionen .GetCurSel();
	if(posix < 0) posix = 0;
	
	CPositionenInfo info(this);
	info.m_pSaetze = &(m_pAuftraege->Auftrag(aufix).m_Positionen);
	info.m_index = posix;
	
	m_pScanner->setEnableScanner(FALSE);
	info.DoModal();
	m_pScanner->setEnableScanner(TRUE);
}


//-----------------------------------------------------------------------------------
void CGatterAuftraege::OnBnClickedButtonLoeschposition2()
{
	CString errMsg;
	int posix = m_ctrlListPositionen.GetCurSel();
	m_ctrlComboGatter.GetWindowText(m_strAktuellerGatterAuftrag);
	int aufix = m_pAuftraege->Exist(m_strAktuellerGatterAuftrag );
	if(posix >= 0)
	{
		int gatterdaten_index = m_pGatterDaten->Exist(m_strAktuellerGatterAuftrag);
		if (gatterdaten_index < 0)
		{
			if(AfxMessageBox(Sprache(_T("Wollen Sie die Zuordnung wirklich löschen?")),MB_YESNO|MB_ICONQUESTION)
				         == IDYES)
			{
				CAuftrag *pCurAuf;
				pCurAuf = &m_pAuftraege->arr[aufix];
				m_pSteinSaetze->SubSatz(pCurAuf->m_Positionen.arr[posix]); // Menge wieder aus Steinliste entfernen
				       
				pCurAuf->m_Positionen.RemoveAt(posix);
				SetPositionenListe(m_strAktuellerGatterAuftrag);
				if(posix >= m_ctrlListPositionen.GetCount())
					posix--;
				if(m_ctrlListPositionen.GetCount() > 0)
					m_ctrlListPositionen.SetCurSel(posix);
      
				m_pAuftraege->Save();
			}
		}
		else
		{
			AfxMessageBox(Sprache(_T("Es sind bereits Gatterdaten vorhanden. Löschen der Zuordnung nicht möglich!")),0);
		}
    }
}

//-----------------------------------------------------------------------------------
void CGatterAuftraege::OnBnClickedButtonLoeschauftrag()
{
	m_ctrlComboGatter.GetWindowText(m_strAktuellerGatterAuftrag);
	int index = m_pAuftraege->Exist(m_strAktuellerGatterAuftrag);
	if(index >= 0)
	{
		int gatterdaten_index = m_pGatterDaten->Exist(m_strAktuellerGatterAuftrag);
		if (gatterdaten_index < 0)
		{
			if(AfxMessageBox(Sprache(_T("Wollen Sie den Auftrag wirklich löschen?")),MB_YESNO|MB_ICONQUESTION)
				         == IDYES)
			{
				// Alle Gespeicherten Steine zurückschreiben
				CAuftrag *pRefAuf;
				pRefAuf = &m_pAuftraege->arr[index];
				
				for(int i = 0; i < pRefAuf->m_Positionen.Anzahl(); i++)
						m_pSteinSaetze->SubSatz(pRefAuf->m_Positionen.arr[i]); // Wieder aus Steinliste entfernen
			
				m_pAuftraege->Auftrag(index).m_Positionen.arr.RemoveAll();
				m_pAuftraege->Remove(m_strAktuellerGatterAuftrag);
				index = max(index-1,0); 
			}
			
			m_strAktuellerGatterAuftrag = _T("");
			if(m_pAuftraege->Anzahl())
				m_strAktuellerGatterAuftrag = m_pAuftraege->Auftrag(index).m_strIdent;

			m_pAuftraege->Save();
		}
		else
		{
			AfxMessageBox(Sprache(_T("Es sind bereits Gatterdaten vorhanden. Löschen des Auftrags nicht möglich!")),0);
		}
    }

	FuellenComboBox(m_strAktuellerGatterAuftrag);
	SetPositionenListe(m_strAktuellerGatterAuftrag);
}
