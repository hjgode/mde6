// GatterNeu.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "GatterNeu.h"
#include "GatterAuftraege.h"


// CGatterNeu-Dialogfeld

IMPLEMENT_DYNAMIC(CGatterNeu, CDialog)

CGatterNeu::CGatterNeu(CWnd* pParent /*=NULL*/)
	: CDialog(CGatterNeu::IDD, pParent)
{

}

CGatterNeu::~CGatterNeu()
{
}

void CGatterNeu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_GATTER, m_ctrlComboGatter);
	DDX_Control(pDX, IDC_STATIC_GATTER, m_ctrlStaticGatter);
	DDX_Control(pDX, IDC_STATIC_LADUNG, m_ctrlStaticLadung);
	DDX_Control(pDX, IDC_EDIT_LADUNG, m_ctrlEditLadung);
	DDX_Control(pDX, IDC_BUTTON_HINZU, m_ctrlButtonHinzu);
	DDX_Control(pDX, IDC_CHECK_STANDFUGE, m_ctrlCheckStandfuge);
	DDX_Control(pDX, IDC_CHECK_TEILUNG, m_ctrlCheckTeilung);
}


BEGIN_MESSAGE_MAP(CGatterNeu, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_GATTER, &CGatterNeu::OnCbnSelchangeComboGatter)
	ON_BN_CLICKED(IDC_BUTTON_HINZU, &CGatterNeu::OnBnClickedButtonHinzu)
END_MESSAGE_MAP()

BOOL CGatterNeu::OnInitDialog()
{
	CDialog::OnInitDialog();

	CenterWindow(GetDesktopWindow());	// center to the hpc screen

	TranslateStatic(m_ctrlStaticGatter );
	TranslateStatic(m_ctrlStaticLadung );
	TranslateButton(m_ctrlButtonHinzu);
	TranslateButton(m_ctrlCheckStandfuge);
	
	// Lesen der Gatterdaten
	m_tabGatter.Read();
	// Füllen der ComboBox
	m_ctrlComboGatter.ResetContent ();
	for (int i = 0; i < m_tabGatter.GetCount(); i++)
	{
		m_ctrlComboGatter.AddString (m_tabGatter.GetAt (i).m_key );
	}
	// Wenn Gatterdaten vorhanden wird entweder das erste oder das zuletzt verwendete ausgewählt
	if (m_tabGatter.GetCount() > 0)
	{
		m_ctrlComboGatter.SetCurSel (0);
		AnzeigeDaten(0);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGatterNeu::AnzeigeDaten(int ix)
{
	C4String Gatterwahl(m_tabGatter.GetAt (ix));
	CString Ladung;
	Ladung.Empty();

	for (int i = 0; i < m_pAuftraege->Anzahl(); i++)
	{
		CString Gatter = CGatterAuftraege::GetGatter(m_pAuftraege->Auftrag(i).m_strIdent);
		if ((Gatter == Gatterwahl.m_key) && (CSteinSatz::StringToDouble(Ladung) < CSteinSatz::StringToDouble(CGatterAuftraege::GetLadung(m_pAuftraege->Auftrag(i).m_strIdent))))
			Ladung = CGatterAuftraege::GetLadung(m_pAuftraege->Auftrag(i).m_strIdent);
	}
	int ladungnr;
	if (Ladung.IsEmpty())
	{
		// Ladung nicht in Aufträge vorhanden
		ladungnr =  _ttoi(Gatterwahl.m_value2);
	}
	else
	{
		// Ladung in Aufträge vorhanden
		// wenn die letzte Ladung aus den Gatterdaten höher ist als die zuletzt im Auftag verwendete, dann muss die Höhere genommen werden
		if( _ttoi(Ladung) >= _ttoi(Gatterwahl.m_value2))
			ladungnr =  _ttoi(Ladung);
		else
			ladungnr =  _ttoi(Gatterwahl.m_value2);
	}
	ladungnr += 1;
	TCHAR temp[20];
	_itot(ladungnr,temp, 10);
	m_ctrlEditLadung.SetWindowText( temp );
}

// CGatterNeu-Meldungshandler

void CGatterNeu::OnCbnSelchangeComboGatter()
{
	int i = m_ctrlComboGatter.GetCurSel();
	AnzeigeDaten(i);
}

void CGatterNeu::OnBnClickedButtonHinzu()
{
	CString strAktuellesGatter;
	CString strAktuelleLadung;

	m_ctrlComboGatter.GetWindowText(strAktuellesGatter);
	strAktuellesGatter.TrimLeft();
	strAktuellesGatter.TrimRight();
	if(strAktuellesGatter.IsEmpty())
    {
		m_ctrlComboGatter.SetFocus();
		return;
    }
	
	m_ctrlEditLadung.GetWindowText(strAktuelleLadung);
	strAktuelleLadung.TrimLeft();
	strAktuelleLadung.TrimRight();
	if(strAktuelleLadung.IsEmpty())
    {
		m_ctrlEditLadung.SetFocus();
		return;
    }

	int ladung_eingabe = _ttoi(strAktuelleLadung);
	int ix = m_ctrlComboGatter.GetCurSel ();
	C4String gatter(m_tabGatter.GetAt (ix));
	int ladung_gatter =  _ttoi(gatter.m_value2);
	ladung_gatter += 1;
	if (ladung_eingabe < ladung_gatter)
	{
		AfxMessageBox(Sprache(_T("Ladungsnummer muss größer als die zuletzt vergebenen Nummer sein")));
		m_ctrlEditLadung.SetFocus ();
		return;
	}

	if (m_ctrlCheckStandfuge.GetCheck() && m_ctrlCheckTeilung.GetCheck())
	{
		AfxMessageBox(Sprache(_T("Standfuge ODER Teilung auswählen")));
		m_ctrlCheckStandfuge.SetFocus();
		return;
	}
	
	CString temp;
	temp = strAktuellesGatter + _T("@") + strAktuelleLadung;
	if (m_ctrlCheckStandfuge.GetCheck())
		temp = temp + _T("-S");
	if (m_ctrlCheckTeilung.GetCheck())
		temp = temp + _T("-T");
	if (temp.IsEmpty() )
		return;

	if(m_pAuftraege->Exist(temp) < 0)
    {
		CAuftrag auf(temp);
		m_pAuftraege->Add(auf);
    }
	EndDialog (0);
}
