// DlgMasseAendern.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "DlgMasseAendern.h"


// CDlgMasseAendern-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgMasseAendern, CDialog)

CDlgMasseAendern::CDlgMasseAendern(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMasseAendern::IDD, pParent)
{

}

CDlgMasseAendern::~CDlgMasseAendern()
{
}

void CDlgMasseAendern::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_STEINNR, m_ctrlComboSteinnr);
	DDX_Control(pDX, IDC_STATIC_STEINNR, m_ctrlStaticSteinnummer);
	DDX_Control(pDX, IDC_EDIT_LAENGE_NEU, m_ctrlEditLaenge_neu);
	DDX_Control(pDX, IDC_EDIT_BREITE_NEU, m_ctrlEditBreite_neu);
	DDX_Control(pDX, IDC_EDIT_DICKE_NEU, m_ctrlEditDicke_neu);
	DDX_Control(pDX, IDC_BUTTON_AENDERN, m_ctrlButtonAendern);
	DDX_Control(pDX, IDC_EDIT_LAENGE_ALT, m_ctrlEditLaenge_alt);
	DDX_Control(pDX, IDC_EDIT_BREITE_ALT, m_ctrlEditBreite_alt);
	DDX_Control(pDX, IDC_EDIT_DICKE_ALT, m_ctrlEditDicke_alt);
	DDX_Control(pDX, IDC_STATIC_LAGERORT, m_ctrlStaticLagerort);
	DDX_Control(pDX, IDC_EDIT_LAGERORT_ALT, m_ctrlEditLagerort_alt);
	DDX_Control(pDX, IDC_COMBO_LAGERORT_NEU, m_ctrlComboLagerort_neu);
}


BEGIN_MESSAGE_MAP(CDlgMasseAendern, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_STEINNR, &CDlgMasseAendern::OnCbnSelchangeComboSteinnr)
	ON_BN_CLICKED(IDC_BUTTON_AENDERN, &CDlgMasseAendern::OnBnClickedButtonAendern)
	ON_CBN_SETFOCUS(IDC_COMBO_STEINNR, &CDlgMasseAendern::OnCbnSetfocusComboSteinnr)
	ON_CBN_SETFOCUS(IDC_COMBO_LAGERORT_NEU, &CDlgMasseAendern::OnCbnSetfocusComboLagerortNeu)
END_MESSAGE_MAP()

// CDlgMasseAendern-Meldungshandler

BOOL CDlgMasseAendern::OnInitDialog()
{
CDialog::OnInitDialog();

CenterWindow(GetDesktopWindow());	// center to the hpc screen

TranslateStatic(m_ctrlStaticSteinnummer);


m_tabLagerOrte.Read();
m_tabFehlerbezeichnung.Read();

// m_ctrlComboSteinnr.ResetContent ();
for (int i = 0; i < m_pSteinSaetze->Anzahl(); i++)
{
	m_ctrlComboSteinnr.AddString (m_pSteinSaetze->SteinSatz (i).Nummer () );
}
if (m_pSteinSaetze->Anzahl () > 0)
{
	if (m_pSteinSaetze->Anzahl () > 2)
	{
		m_ctrlComboSteinnr.SetCurSel (2);
		AnzeigeDaten(2);
	}
	else
	{
		m_ctrlComboSteinnr.SetCurSel (0);
		AnzeigeDaten(0);
	}
	// m_ctrlComboSteinnr.SetWindowText(m_pSteinSaetze->SteinSatz (i).Nummer () );
}

// Laden Lagerorte-ComboBox
for (int i = 0; i < m_tabLagerOrte.GetCount() ; i++)
{
	m_ctrlComboLagerort_neu.AddString (m_tabLagerOrte.GetAt (i).m_bez);
}

return TRUE;  // return TRUE  unless you set the focus to a control
}
void CDlgMasseAendern::OnCbnSelchangeComboSteinnr()
{
	int ix = m_ctrlComboSteinnr.GetCurSel ();
	/*SSatz satz(m_pSteinSaetze->SteinSatz (ix));
	m_ctrlEditLaenge_alt.SetWindowText( satz.m_Laenge );
	m_ctrlEditBreite_alt.SetWindowText( satz.m_Breite );
	m_ctrlEditDicke_alt.SetWindowText( satz.m_Dicke );*/
	AnzeigeDaten(ix);
}

void CDlgMasseAendern::AnzeigeDaten(int ix)
{
	SSatz satz(m_pSteinSaetze->SteinSatz (ix));
	m_ctrlEditLaenge_alt.SetWindowText( satz.m_Laenge );
	m_ctrlEditBreite_alt.SetWindowText( satz.m_Breite );
	m_ctrlEditDicke_alt.SetWindowText( satz.m_Dicke );

	C2String lager(m_tabLagerOrte.GetItemByKey (satz.m_Lager) );
	m_ctrlEditLagerort_alt.SetWindowText( lager.m_bez );
}

void CDlgMasseAendern::OnBnClickedButtonAendern()
{
	// neue Inhalte prüfen
	CString laenge_neu;
	m_ctrlEditLaenge_neu.GetWindowTextW( laenge_neu );
	if (NoValueSetFocus(laenge_neu, m_ctrlEditLaenge_neu))
	{
		AfxMessageBox( _T("Länge ungültig"),0,0);
		return ;
	}

	CString breite_neu;
	m_ctrlEditBreite_neu.GetWindowTextW( breite_neu );
	if (NoValueSetFocus(breite_neu, m_ctrlEditBreite_neu))
	{
		AfxMessageBox( _T("Breite ungültig"),0,0);
		return ;
	}

	CString dicke_neu;
	m_ctrlEditDicke_neu.GetWindowTextW( dicke_neu );
	if (NoValueSetFocus(dicke_neu, m_ctrlEditDicke_neu))
	{
		AfxMessageBox( _T("Dicke ungültig"),0,0);
		return ;
	}

	
	// Änderungen im Datensatz 
	int ix = m_ctrlComboSteinnr.GetCurSel ();
	SSatz satz(m_pSteinSaetze->SteinSatz (ix));
	if (!laenge_neu.IsEmpty())
		satz.m_Laenge = laenge_neu;
	if (!breite_neu.IsEmpty ())
		satz.m_Breite = breite_neu;
	if (!dicke_neu.IsEmpty ())
		satz.m_Dicke  = dicke_neu;

	int ix_lager = m_ctrlComboLagerort_neu.GetCurSel ();
	C2String lager( m_tabLagerOrte .GetAt (ix_lager) );
	satz.m_Lager = lager.m_key ;	

	CSteinSatz s;
	s.Set(satz);
	s.SetMenge2 (0. );
	s.SetMenge2Verfuegbar (0.);
	s.SetDatumZeit();
	s.m_buchungsNummer = m_pAuftraege->NaechsteBuchungsnummer ();
	
	m_pAuftraege->Auftrag(0).AddPosition (s );
	m_pSteinSaetze->SteinSatz(ix) = s;
	m_pSteinSaetze->m_modified = TRUE;
}


BOOL CDlgMasseAendern::PreTranslateMessage(MSG* pMsg) 
{
CString errMsg;

CString barCode = m_pScanner->WaitForDecode(2000,errMsg);

if(!barCode.IsEmpty())
    {
    if(m_curFocus == NUMMER)
        {
        if(CheckNummer(barCode))
            {
            m_ctrlComboLagerort_neu.SetFocus();
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
    if(m_curFocus == LAGER)
        {
        if(CheckLager(barCode))
			m_ctrlEditLaenge_neu.SetFocus ();
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

void CDlgMasseAendern::OnCbnSetfocusComboSteinnr()
{
	m_curFocus = NUMMER;
}


void CDlgMasseAendern::OnCbnSetfocusComboLagerortNeu()
{
	m_curFocus = LAGER;
}

BOOL CDlgMasseAendern::CheckNummer(const CString& barCode)
{
int index;
if(m_pSteinSaetze->FoundAt(barCode,index))
    {
    PlaySoundScan();
    AnzeigeDaten(index);
    return TRUE;
    }
return FALSE;
}
//---------------------------------------------------------------------------------------
// Zuerst auf Nummer dann auf Lager prüfen
BOOL CDlgMasseAendern::CheckLager(const CString& barCode)
{
int index = m_tabLagerOrte.GetIndexByKey(barCode);
if(index >= 0)
    {
    PlaySoundScan();
	m_ctrlComboLagerort_neu.SetCurSel (index);
    return TRUE;
    }
return FALSE;
}
