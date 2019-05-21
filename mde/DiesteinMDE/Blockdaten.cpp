// Blockdaten.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "Blockdaten.h"


// CBlockdaten-Dialogfeld

IMPLEMENT_DYNAMIC(CBlockdaten, CDialog)

CBlockdaten::CBlockdaten(CWnd* pParent /*=NULL*/)
	: CDialog(CBlockdaten::IDD, pParent)
{

}

CBlockdaten::~CBlockdaten()
{
}

void CBlockdaten::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_BLOCKNUMMER, m_ctrlStaticBlocknummer);
	DDX_Control(pDX, IDC_STATIC_MATERIAL, m_ctrlStaticMaterial);
	DDX_Control(pDX, IDC_STATIC_LAENGE, m_ctrlStaticLaenge);
	DDX_Control(pDX, IDC_STATIC_BREITE, m_ctrlStaticBreite);
	DDX_Control(pDX, IDC_STATIC_DICKE, m_ctrlStaticDicke);
	DDX_Control(pDX, IDC_STATIC_BRUTTO, m_ctrlStaticBrutto);
	DDX_Control(pDX, IDC_STATIC_NETTO, m_ctrlStaticNetto);
	DDX_Control(pDX, IDC_EDIT_LAENGEBRUTTO, m_ctrlEditLaengeBrutto);
	DDX_Control(pDX, IDC_EDIT_BREITEBRUTTO, m_ctrlEditBreiteBrutto);
	DDX_Control(pDX, IDC_EDIT_DICKEBRUTTO, m_ctrlEditDickeBrutto);
	DDX_Control(pDX, IDC_EDIT_LAENGENETTO, m_ctrlEditLaengeNetto);
	DDX_Control(pDX, IDC_EDIT_BREITENETTO, m_ctrlEditBreiteNetto);
	DDX_Control(pDX, IDC_EDIT_DICKENETTO, m_ctrlEditDickeNetto);
}


BEGIN_MESSAGE_MAP(CBlockdaten, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT_LAENGEBRUTTO, &CBlockdaten::OnEnKillfocusEditLaengebrutto)
	ON_EN_KILLFOCUS(IDC_EDIT_BREITEBRUTTO, &CBlockdaten::OnEnKillfocusEditBreitebrutto)
	ON_EN_KILLFOCUS(IDC_EDIT_DICKEBRUTTO, &CBlockdaten::OnEnKillfocusEditDickebrutto)
	ON_EN_KILLFOCUS(IDC_EDIT_LAENGENETTO, &CBlockdaten::OnEnKillfocusEditLaengenetto)
	ON_EN_KILLFOCUS(IDC_EDIT_BREITENETTO, &CBlockdaten::OnEnKillfocusEditBreitenetto)
	ON_EN_KILLFOCUS(IDC_EDIT_DICKENETTO, &CBlockdaten::OnEnKillfocusEditDickenetto)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------------
BOOL CBlockdaten::OnInitDialog()
{			
	CDialog::OnInitDialog();

	CenterWindow(GetDesktopWindow());	// center to the hpc screen

	TranslateStatic(m_ctrlStaticBlocknummer );
	TranslateStatic(m_ctrlStaticLaenge );
	TranslateStatic(m_ctrlStaticBreite );
	TranslateStatic(m_ctrlStaticDicke);
	TranslateStatic(m_ctrlStaticBrutto );
	TranslateStatic(m_ctrlStaticNetto);
	
		

	// Einlesen der zusätzlichen Daten
	m_tabMaterialGruppen.Read();
	m_tabAlleMaterialArten.Read();

	// Prüfen, ob Masse geändert werden dürfen
	if(g_Optionen.MasseAendEnabled() )
    {
		m_ctrlEditLaengeBrutto.EnableWindow (TRUE);
		m_ctrlEditBreiteBrutto.EnableWindow(TRUE);
		m_ctrlEditDickeBrutto.EnableWindow(TRUE);
		m_ctrlEditLaengeNetto.EnableWindow(TRUE);
		m_ctrlEditBreiteNetto.EnableWindow(TRUE);
		m_ctrlEditDickeNetto.EnableWindow(TRUE);
    }
	else
	{
		m_ctrlEditLaengeBrutto.EnableWindow (FALSE);
		m_ctrlEditBreiteBrutto.EnableWindow(FALSE);
		m_ctrlEditDickeBrutto.EnableWindow(FALSE);
		m_ctrlEditLaengeNetto.EnableWindow(FALSE);
		m_ctrlEditBreiteNetto.EnableWindow(FALSE);
		m_ctrlEditDickeNetto.EnableWindow(FALSE);
    }

	// Anzeigen der Blockdaten
	AnzeigeBlockdaten();

	m_modified = FALSE;

	return TRUE;  // return TRUE  unless you set the focus to a control
}
//-----------------------------------------------------------------------------------
void CBlockdaten::AnzeigeBlockdaten()
{
	if (m_pSteinSatz.Artikel() != _T("") )
	{
		SSatz s(m_pSteinSatz);
		m_ctrlStaticBlocknummer.SetWindowText(s.m_Nummer);
		m_ctrlStaticMaterial.SetWindowText(s.m_Material);

		m_ctrlEditLaengeBrutto.SetWindowText(s.m_LaengeBrutto);
		m_ctrlEditBreiteBrutto.SetWindowText(s.m_BreiteBrutto);
		m_ctrlEditDickeBrutto.SetWindowText(s.m_DickeBrutto);

		m_ctrlEditLaengeNetto.SetWindowText(s.m_Laenge);
		m_ctrlEditBreiteNetto.SetWindowText(s.m_Breite);
		m_ctrlEditDickeNetto.SetWindowText(s.m_Dicke);
	}
}
//-----------------------------------------------------------------------------------


// CBlockdaten-Meldungshandler

void CBlockdaten::OnEnKillfocusEditLaengebrutto()
{
	if (!(ValueExeed400(m_ctrlEditLaengeBrutto)))
	{
		CString sInhalt;
		m_ctrlEditLaengeBrutto.GetWindowText(sInhalt);

		if (m_pSteinSatz.Artikel() != _T("") && (sInhalt.GetLength() > 0 ) )
		{
			SSatz s(m_pSteinSatz);
			if (s.m_LaengeBrutto != sInhalt)
			{
				s.m_LaengeBrutto = sInhalt;
				m_modified = TRUE;
				m_pSteinSatz.Set(s);
			}
		}
	}
}

void CBlockdaten::OnEnKillfocusEditBreitebrutto()
{
	if (!(ValueExeed400(m_ctrlEditBreiteBrutto)))
	{
		CString sInhalt;
		m_ctrlEditBreiteBrutto.GetWindowText(sInhalt);

		if (m_pSteinSatz.Artikel() != _T("") && (sInhalt.GetLength() > 0 ) )
		{
			SSatz s(m_pSteinSatz);
			if (s.m_BreiteBrutto != sInhalt)
			{
				s.m_BreiteBrutto = sInhalt;
				m_modified = TRUE;
				m_pSteinSatz.Set(s);
			}
		}
	}
}

void CBlockdaten::OnEnKillfocusEditDickebrutto()
{
	if (!(ValueExeed400(m_ctrlEditDickeBrutto)))
	{
		CString sInhalt;
		m_ctrlEditDickeBrutto.GetWindowText(sInhalt);

		if (m_pSteinSatz.Artikel() != _T("") && (sInhalt.GetLength() > 0 ) )
		{
			SSatz s(m_pSteinSatz);
			if (s.m_DickeBrutto != sInhalt)
			{
				s.m_DickeBrutto = sInhalt;
				m_modified = TRUE;
				m_pSteinSatz.Set(s);
			}
		}
	}
}

void CBlockdaten::OnEnKillfocusEditLaengenetto()
{
	if (!(ValueExeed400(m_ctrlEditLaengeNetto)))
	{
		CString sInhalt;
		m_ctrlEditLaengeNetto.GetWindowText(sInhalt);

		if (m_pSteinSatz.Artikel() != _T("") && (sInhalt.GetLength() > 0 ) )
		{
			SSatz s(m_pSteinSatz);
			if (s.m_Laenge != sInhalt)
			{
				s.m_Laenge = sInhalt;
				m_modified = TRUE;
				m_pSteinSatz.Set(s);

			}
		}
	}
}

void CBlockdaten::OnEnKillfocusEditBreitenetto()
{
	if (!(ValueExeed400(m_ctrlEditBreiteNetto)))
	{
		CString sInhalt;
		m_ctrlEditBreiteNetto.GetWindowText(sInhalt);

		if (m_pSteinSatz.Artikel() != _T("") && (sInhalt.GetLength() > 0 ) )
		{
			SSatz s(m_pSteinSatz);
			if (s.m_Breite != sInhalt)
			{
				s.m_Breite = sInhalt;
				m_modified = TRUE;
				m_pSteinSatz.Set(s);
			}
		}
	}
}

void CBlockdaten::OnEnKillfocusEditDickenetto()
{
	if (!(ValueExeed400(m_ctrlEditDickeNetto)))
	{
		CString sInhalt;
		m_ctrlEditDickeNetto.GetWindowText(sInhalt);

		if (m_pSteinSatz.Artikel() != _T("") && (sInhalt.GetLength() > 0 ) )
		{
			SSatz s(m_pSteinSatz);
			if (s.m_Dicke != sInhalt)
			{
				s.m_Dicke = sInhalt;
				m_modified = TRUE;
				m_pSteinSatz.Set(s);
			}
		}
	}
}
