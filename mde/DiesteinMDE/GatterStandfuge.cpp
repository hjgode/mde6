// GatterStandfuge.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "GatterStandfuge.h"


// CGatterStandfuge-Dialogfeld

IMPLEMENT_DYNAMIC(CGatterStandfuge, CDialog)

CGatterStandfuge::CGatterStandfuge(CWnd* pParent /*=NULL*/)
	: CDialog(CGatterStandfuge::IDD, pParent)
{

}

CGatterStandfuge::~CGatterStandfuge()
{
}

void CGatterStandfuge::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_GATTER, m_ctrlStaticGatter);
	DDX_Control(pDX, IDC_STATIC_MASSE, m_ctrlStaticMasse);
	DDX_Control(pDX, IDC_EDIT_LAENGE, m_ctrlEditLaenge);
	DDX_Control(pDX, IDC_EDIT_BREITE, m_ctrlEditBreite);
	DDX_Control(pDX, IDC_BUTTON_SPEICHERN, m_ctrlButtonSpeichern);
	DDX_Control(pDX, IDC_BUTTON_LOESCHEN, m_ctrlButtonLoeschen);
}


BEGIN_MESSAGE_MAP(CGatterStandfuge, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SPEICHERN, &CGatterStandfuge::OnBnClickedButtonSpeichern)
	ON_BN_CLICKED(IDC_BUTTON_LOESCHEN, &CGatterStandfuge::OnBnClickedButtonLoeschen)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------------
BOOL CGatterStandfuge::OnInitDialog()
{			
	CDialog::OnInitDialog();

	CenterWindow(GetDesktopWindow());	// center to the hpc screen

	TranslateStatic(m_ctrlStaticGatter);
	TranslateStatic(m_ctrlStaticMasse);
	TranslateButton(m_ctrlButtonLoeschen);
	TranslateButton(m_ctrlButtonSpeichern);

	
	m_ctrlStaticGatter.SetWindowText(Sprache(_T("Gatter/Ladung:")) + _T(" ") + *m_pAktuellerGatterAuftrag);
	// Wenn Gatterdaten vorhanden wird entweder das erste oder das zuletzt verwendete ausgewählt
	if (m_pGatterDaten->Anzahl() > 0)
	{
		if (m_pAktuellerGatterAuftrag->GetLength() > 0)
			AnzeigeGatterDaten(*m_pAktuellerGatterAuftrag);			
		else
		{
			BildschirmLoeschen();
		}
	}
	m_ctrlEditLaenge.SetFocus();

	return TRUE;  // return TRUE  unless you set the focus to a control
}
//-----------------------------------------------------------------------------------
void CGatterStandfuge::AnzeigeGatterDaten(CString strAuftrag)
{
	int ix = m_pGatterDaten->Exist(strAuftrag);
	if (ix >= 0 && m_pGatterDaten->Auftrag(ix).m_Positionen.Anzahl() > 0)
	{
		SSatz s(m_pGatterDaten->Auftrag(ix).Position(0));
			
		m_ctrlEditLaenge.SetWindowText(s.m_Laenge);
		m_ctrlEditBreite.SetWindowText(s.m_Breite);
	}	
	else
	{
		BildschirmLoeschen();
	}
}
void CGatterStandfuge::BildschirmLoeschen ()
{
	m_ctrlEditLaenge.SetWindowText(_T(""));
	m_ctrlEditBreite.SetWindowText(_T(""));
}
//-----------------------------------------------------------------------------------
BOOL CGatterStandfuge::WerteOk()
{
	if(!WertOk(m_strLaenge,m_ctrlEditLaenge )) // leer oder ungültiges format
		return FALSE;
	if(!WertOk(m_strBreite,m_ctrlEditBreite )) // leer oder ungültiges format
		return FALSE;
	
	return TRUE;
}
//-----------------------------------------------------------------------------------
BOOL CGatterStandfuge::WertOk(CString& str,CEdit& edit)
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
int CGatterStandfuge::NaechsteBuchungsnummer() const
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
// CGatterStandfuge-Meldungshandler

void CGatterStandfuge::OnBnClickedButtonSpeichern()
{
	UpdateData(TRUE);

	m_ctrlStaticGatter.GetWindowText(m_strGatterAuftrag);
	m_strGatterAuftrag.Replace(Sprache(_T("Gatter/Ladung:")) + _T(" "), _T(""));

	m_ctrlEditLaenge.GetWindowText(m_strLaenge);
	m_ctrlEditBreite.GetWindowText(m_strBreite);

	if(!WerteOk()) return;
	
	int ix_daten = m_pGatterDaten->Exist(m_strGatterAuftrag);
	if (ix_daten < 0)
	{
		CAuftrag gatter;
		gatter.m_strIdent = m_strGatterAuftrag;
		m_pGatterDaten->Add(gatter);
		ix_daten = m_pGatterDaten->Exist (m_strGatterAuftrag);
	}
	
	if (m_pGatterDaten->Auftrag(ix_daten).m_Positionen.Anzahl() == 0)
	{

		SSatz ss;
		ss.m_Laenge = m_strLaenge;
		ss.m_Breite = m_strBreite;
		
		CSteinSatz satz;
		satz.Set(ss);	
		satz.SetDatumZeit();
		satz.m_buchungsNummer = NaechsteBuchungsnummer();
		m_pGatterDaten->Auftrag(ix_daten).AddPosition(satz);
	}
	else
	{
		// Wenn der Satz schon existiert müssen die Maße für die Standfuge übernommen werden.
		SSatz ss(m_pGatterDaten->Auftrag(ix_daten).Position(0));
		ss.m_Laenge = m_strLaenge;
		ss.m_Breite = m_strBreite;
		m_pGatterDaten->Auftrag(ix_daten).Position(0).Set(ss);
	}

	PlaySoundAdd();

	UpdateData(FALSE);

	EndDialog (0);
}

void CGatterStandfuge::OnBnClickedButtonLoeschen()
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
				if (ss.m_GatterDatumAnfang.GetLength() == 0 && ss.m_GatterDatumEnde.GetLength() == 0 )
					//m_pGatterDaten->Auftrag(ix_daten).m_Positionen.RemoveAt(0);
					m_pGatterDaten->Remove(m_strGatterAuftrag);
				else
				{
					ss.m_Laenge = _T("");
					ss.m_Breite = _T("");
					m_pGatterDaten->Auftrag(ix_daten).Position(0).Set(ss);
				}
			}
			// Bildschirm wieder leeren
			BildschirmLoeschen();
		}
	}
	else
		// Bildschirm wieder leeren
		BildschirmLoeschen();

	// Focus auf jeden Fall wieder auf die Länge setzen
	m_ctrlEditLaenge.SetFocus();
}
