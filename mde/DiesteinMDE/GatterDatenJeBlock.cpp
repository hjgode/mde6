// GatterDatenJeBlock.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "GatterDatenJeBlock.h"


// CGatterDatenJeBlock-Dialogfeld

IMPLEMENT_DYNAMIC(CGatterDatenJeBlock, CDialog)

CGatterDatenJeBlock::CGatterDatenJeBlock(CWnd* pParent /*=NULL*/)
	: CDialog(CGatterDatenJeBlock::IDD, pParent)
{

}

CGatterDatenJeBlock::~CGatterDatenJeBlock()
{
}

void CGatterDatenJeBlock::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_BLOck, m_ctrlStatic_Block);
	DDX_Control(pDX, IDC_COMBO_BLOECKE, m_ctrlComboBloecke);
	DDX_Control(pDX, IDC_STATIC_MATERIAL, m_ctrlStaticMaterial);
	DDX_Control(pDX, IDC_STATIC_MASSE, m_ctrlStaticMasse);
	DDX_Control(pDX, IDC_STATIC_ANZSCHNITTE, m_ctrlStaticAnzSchnitte);
	DDX_Control(pDX, IDC_EDIT_ANZSCHNITTE, m_ctrlEditAnzSchnitte);
	DDX_Control(pDX, IDC_STATIC_SCHNITTFLAECHE, m_ctrlStaticSchnittflaeche);
	DDX_Control(pDX, IDC_COMBO_SCHNITTFLAECHE, m_ctrlComboSchnittflaeche);
	DDX_Control(pDX, IDC_BUTTON_LOESCHEN, m_ctrlButtonLoeschen);
	DDX_Control(pDX, IDC_BUTTON_SPEICHERN, m_ctrlButtonSpeichern);
	DDX_Control(pDX, IDC_BUTTON_ABBRECHEN, m_ctrlButtonAbbrechen);
}


BEGIN_MESSAGE_MAP(CGatterDatenJeBlock, CDialog)
	ON_EN_CHANGE(IDC_EDIT_ANZSCHNITTE, &CGatterDatenJeBlock::OnEnChangeEditAnzschnitte)
	ON_CBN_SELCHANGE(IDC_COMBO_SCHNITTFLAECHE, &CGatterDatenJeBlock::OnCbnSelchangeComboSchnittflaeche)
	ON_BN_CLICKED(IDC_BUTTON_ABBRECHEN, &CGatterDatenJeBlock::OnBnClickedButtonAbbrechen)
	ON_BN_CLICKED(IDC_BUTTON_LOESCHEN, &CGatterDatenJeBlock::OnBnClickedButtonLoeschen)
	ON_BN_CLICKED(IDC_BUTTON_SPEICHERN, &CGatterDatenJeBlock::OnBnClickedButtonSpeichern)
	ON_CBN_SELCHANGE(IDC_COMBO_BLOECKE, &CGatterDatenJeBlock::OnCbnSelchangeComboBloecke)
END_MESSAGE_MAP()
//-----------------------------------------------------------------------------------
BOOL CGatterDatenJeBlock::OnInitDialog()
{			
	CDialog::OnInitDialog();

	CenterWindow(GetDesktopWindow());	// center to the hpc screen

	TranslateStatic(m_ctrlStatic_Block );
	TranslateStatic(m_ctrlStaticAnzSchnitte );
	TranslateStatic(m_ctrlStaticSchnittflaeche );
	TranslateButton(m_ctrlButtonLoeschen);
	TranslateButton(m_ctrlButtonSpeichern);
	TranslateButton(m_ctrlButtonAbbrechen );

	// füllen der Combo für die Schnittfläche
	m_ctrlComboSchnittflaeche.AddString(Sprache(_T("Länge/Dicke")));
	m_ctrlComboSchnittflaeche.AddString(Sprache(_T("Breite/Dicke")));
	m_ctrlComboSchnittflaeche.AddString(Sprache(_T("Länge/Breite")));
	
	// Einlesen der Daten je Block	
	Schnitte.Reset();
	int pos_Trennzeichen = 0;
	int pos_Start = 0;
	CString AnzSchnitteJeBlock = *m_pAnzSchnitteJeBlock;
	if (!(AnzSchnitteJeBlock.IsEmpty()))
	{
		while( pos_Trennzeichen >= 0)
		{
			pos_Trennzeichen = AnzSchnitteJeBlock.Find(_T("@@"), pos_Start);
			if (pos_Trennzeichen >= 0)
			{
				C3String temp;
				temp.m_key = AnzSchnitteJeBlock.Mid(pos_Start,pos_Trennzeichen - pos_Start);
				pos_Start = pos_Trennzeichen + 2;
				pos_Trennzeichen = AnzSchnitteJeBlock.Find(_T("@@"), pos_Start);
				temp.m_value1 = AnzSchnitteJeBlock.Mid(pos_Start, pos_Trennzeichen - pos_Start);
				pos_Start = pos_Trennzeichen + 2;
				pos_Trennzeichen = AnzSchnitteJeBlock.Find(_T("@@"), pos_Start);
				temp.m_value2 = AnzSchnitteJeBlock.Mid(pos_Start, pos_Trennzeichen - pos_Start);
				pos_Start = pos_Trennzeichen + 2;
				Schnitte.Add (temp);

				if (pos_Start > AnzSchnitteJeBlock.GetLength())
					pos_Trennzeichen = -99;
			}
		}
	}
	else
	{
		for(int i = 0; i < m_pAuftrag->m_Positionen.Anzahl(); i++)
		{
			C3String temp;
			temp.m_key = m_pAuftrag->Position(i).Nummer();
			temp.m_value2 = _T("2");
			Schnitte.Add(temp);
		}
	}


	// füllen der ComboBox mit den Blöcken
	for(int i = 0; i < m_pAuftrag->m_Positionen.Anzahl(); i++)
	{
		m_ctrlComboBloecke.AddString(m_pAuftrag->Position(i).Nummer());
	}
	
	// und jetzt den ersten Block auswählen und die Daten anzeigen
	m_ctrlComboBloecke.SetCurSel (0);
	AnzeigeBlockDaten();
	

	m_ctrlEditAnzSchnitte.SetFocus();

	return TRUE;  // return TRUE  unless you set the focus to a control
}
//-----------------------------------------------------------------------------------
void CGatterDatenJeBlock::AnzeigeBlockDaten()
{
	int pos = m_ctrlComboBloecke.GetCurSel();
	m_ctrlEditAnzSchnitte.SetWindowText( Schnitte[pos].m_value1 );
	if (Schnitte[pos].m_value2.IsEmpty())
		m_ctrlComboSchnittflaeche.SetCurSel(3);
	else
		m_ctrlComboSchnittflaeche.SetCurSel( _ttoi(Schnitte[pos].m_value2) );

	SSatz s(m_pAuftrag->Position(pos));
	m_ctrlStaticMaterial.SetWindowText(s.m_Material);
	m_ctrlStaticMasse.SetWindowText(s.m_Laenge + _T("x") + s.m_Breite + _T("x") + s.m_Dicke);
}

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
// CGatterDatenJeBlock-Meldungshandler

void CGatterDatenJeBlock::OnCbnSelchangeComboBloecke()
{
	AnzeigeBlockDaten();
}

void CGatterDatenJeBlock::OnEnChangeEditAnzschnitte()
{
	// Einfügen der Änderung in die C3STringtabelle
	int pos = m_ctrlComboBloecke.GetCurSel();
	CString AnzSchnitte;
	m_ctrlEditAnzSchnitte.GetWindowText(AnzSchnitte);
	Schnitte[pos].m_value1 = AnzSchnitte;
}

void CGatterDatenJeBlock::OnCbnSelchangeComboSchnittflaeche()
{
	// Einfügen der Änderung in die C3STringtabelle
	int pos = m_ctrlComboBloecke.GetCurSel();
	int auswahl = m_ctrlComboSchnittflaeche.GetCurSel();
	CString temp;
	Schnitte[pos].m_value2.Format(_T("%d"), auswahl);
}

void CGatterDatenJeBlock::OnBnClickedButtonAbbrechen()
{
	EndDialog (0);
}

void CGatterDatenJeBlock::OnBnClickedButtonLoeschen()
{
	*m_pAnzSchnitteJeBlock = _T("");
	EndDialog(0);
}

void CGatterDatenJeBlock::OnBnClickedButtonSpeichern()
{
	// prüfen, ob für alle Blöcke Daten erfasst wurden
	for(int s = 0; s < Schnitte.GetCount(); s++)
	{
		if (Schnitte[s].m_value1.IsEmpty())
		{
			m_ctrlComboBloecke.SetCurSel(s);
			AnzeigeBlockDaten();
			m_ctrlEditAnzSchnitte.SetFocus();
			return;
		}
	}

	// für jeden Block sind die Daten gespeichert, also geht es weiter
	CString AnzSchnitteJeBlock = _T("");
	
	for(int i = 0; i < m_pAuftrag->m_Positionen.Anzahl(); i++)
	{
		AnzSchnitteJeBlock = AnzSchnitteJeBlock + m_pAuftrag->Position(i).Nummer();
		AnzSchnitteJeBlock = AnzSchnitteJeBlock + _T("@@");

		AnzSchnitteJeBlock = AnzSchnitteJeBlock + Schnitte[i].m_value1 ;
		AnzSchnitteJeBlock = AnzSchnitteJeBlock + _T("@@");

		AnzSchnitteJeBlock = AnzSchnitteJeBlock + Schnitte[i].m_value2 ;
		AnzSchnitteJeBlock = AnzSchnitteJeBlock + _T("@@");
	}
	*m_pAnzSchnitteJeBlock = AnzSchnitteJeBlock;
	EndDialog(0);
	
}


void CGatterDatenJeBlock::OnOK()
{
	OnBnClickedButtonSpeichern();
}