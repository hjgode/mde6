// GatterAuswahl.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "GatterAuswahl.h"
#include "GatterAuftraege.h"
#include "GatterOffeneAuftraege.h"


// CGatterAuswahl-Dialogfeld

IMPLEMENT_DYNAMIC(CGatterAuswahl, CDialog)

CGatterAuswahl::CGatterAuswahl(CWnd* pParent /*=NULL*/)
	: CDialog(CGatterAuswahl::IDD, pParent)
{

}

CGatterAuswahl::~CGatterAuswahl()
{
}

void CGatterAuswahl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_PLATTENZUGANG, m_ctrlButtonPlattenzugang);
	DDX_Control(pDX, IDC_BUTTON_GATTERN, m_ctrlButtonGattern);
}


BEGIN_MESSAGE_MAP(CGatterAuswahl, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_GATTERN, &CGatterAuswahl::OnBnClickedButtonGattern)
	ON_BN_CLICKED(IDC_BUTTON_PLATTENZUGANG, &CGatterAuswahl::OnBnClickedButtonPlattenzugang)
END_MESSAGE_MAP()

//****************************************************************************
BOOL CGatterAuswahl::OnInitDialog()
{
	CDialog::OnInitDialog();

	CenterWindow(GetDesktopWindow());	// center to the hpc screen

	TranslateButton(m_ctrlButtonGattern);
	TranslateButton(m_ctrlButtonPlattenzugang);

	return TRUE;  // return TRUE  unless you set the focus to a control
}
//****************************************************************************
// CGatterAuswahl-Meldungshandler

void CGatterAuswahl::OnBnClickedButtonGattern()
{
m_pAuftraege->m_strName = NAME_GATTERAUFTRAEGE;
m_pAuftraege->ReadFile();

m_offeneAuftraege.m_strName = NAME_GATTEROFFENEAUFTRAEGE;
m_offeneAuftraege.ReadFile();

m_GatterDaten.m_strName = NAME_GATTERDATEN;
m_GatterDaten.ReadFile();

if(m_pAuftraege->Anzahl())
    {
    if(m_pstrLetzterGatterAuftrag->IsEmpty())
		*m_pstrLetzterGatterAuftrag = m_pAuftraege->Auftrag(0).m_strIdent;
    }
// Hier Rück abschalten
CGatterAuftraege gatterAuftraege(this);  // Dialogbox Gatterauftraege

m_pSteinSaetze->m_modified = false;
gatterAuftraege.m_pSteinSaetze = m_pSteinSaetze;
gatterAuftraege.m_pAuftraege = m_pAuftraege;
gatterAuftraege.m_pOffeneAuftraege = &m_offeneAuftraege;
gatterAuftraege.m_pstrLetzterGatterAuftrag = m_pstrLetzterGatterAuftrag ;
gatterAuftraege.m_pGatterDaten = &m_GatterDaten;

gatterAuftraege.m_pScanner = m_pScanner;

m_pScanner->setEnableScanner(TRUE);

gatterAuftraege.DoModal();	

m_pScanner->setEnableScanner(FALSE);
	
m_pAuftraege->Save();
if(m_pSteinSaetze->m_modified)
    m_pSteinSaetze->Save();		

}

void CGatterAuswahl::OnBnClickedButtonPlattenzugang()
{
m_offeneAuftraege.m_strName = NAME_GATTEROFFENEAUFTRAEGE;
m_offeneAuftraege.ReadFile();

m_pAuftraege->m_strName = NAME_GATTERAUFTRAEGE;
m_pAuftraege->ReadFile();

if (m_pAuftraege->Anzahl() > 0)
	for (int i = 0; i < m_pAuftraege->Anzahl(); i++)
		if(m_offeneAuftraege.Exist(m_pAuftraege->Auftrag(i).m_strIdent) < 0)
			m_offeneAuftraege.Add(m_pAuftraege->Auftrag(i));


m_Platten.m_strName = NAME_GATTERPLATTEN;
m_Platten.ReadFile();

m_GatterDaten.m_strName = NAME_GATTERDATEN;
m_GatterDaten.ReadFile();

m_GatterBloecke.m_strName = NAME_GATTERBLOECKE;
m_GatterBloecke.ReadFile();

if(m_offeneAuftraege.Anzahl())
    {
    if(m_pstrLetzterGatterAuftrag->IsEmpty())
		*m_pstrLetzterGatterAuftrag = m_offeneAuftraege.Auftrag(0).m_strIdent;
    }
// Hier Rück abschalten
CGatterOffeneAuftraege gatterOffeneAuftraege(this);  // Dialogbox Gatterauftraege

m_pSteinSaetze->m_modified = false;
gatterOffeneAuftraege.m_pSteinSaetze = m_pSteinSaetze;
gatterOffeneAuftraege.m_pOffeneAuftraege = &m_offeneAuftraege;
gatterOffeneAuftraege.m_pPlatten = &m_Platten;
gatterOffeneAuftraege.m_pGatterDaten = &m_GatterDaten;
gatterOffeneAuftraege.m_pGatterBloecke = &m_GatterBloecke;
gatterOffeneAuftraege.m_pstrLetzterGatterAuftrag = m_pstrLetzterGatterAuftrag ;
gatterOffeneAuftraege.m_pstrLetzterBlock = m_pstrLetzterBlock;

gatterOffeneAuftraege.m_pScanner = m_pScanner;

m_pScanner->setEnableScanner(TRUE);

gatterOffeneAuftraege.DoModal();	

m_pScanner->setEnableScanner(FALSE);
	
m_Platten.Save();
m_GatterDaten.Save();
m_GatterBloecke.Save();
if(m_pSteinSaetze->m_modified)
    m_pSteinSaetze->Save();		
}
