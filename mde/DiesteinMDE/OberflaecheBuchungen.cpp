// OberflaecheBuchungen.cpp : implementation file
//

#include "stdafx.h"
#include "OberflaecheBuchungen.h"

/////////////////////////////////////////////////////////////////////////////
// COberflaecheBuchungen dialog


COberflaecheBuchungen::COberflaecheBuchungen(CWnd* pParent /*=NULL*/)
	: CDialog(COberflaecheBuchungen::IDD, pParent)
{
m_curSel = -1;
}


void COberflaecheBuchungen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_STEINNUMMER, m_ctrlStaticSteinnummer);
	DDX_Control(pDX, IDC_STATIC_ALTNEUFEHLER, m_ctrlStaticAltNeuFehler);
	DDX_Control(pDX, IDC_STATIC_BUCHUNGEN, m_ctrlStaticBuchungen);
	DDX_Control(pDX, IDC_BUTTON_ERASE, m_ctrlButtonErase);
	DDX_Control(pDX, IDC_LIST_OBERFL, m_ctrlListOberfl);
}


BEGIN_MESSAGE_MAP(COberflaecheBuchungen, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST_OBERFL, OnSelchangeListOberfl)
	ON_BN_CLICKED(IDC_BUTTON_ERASE, OnButtonErase)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COberflaecheBuchungen message handlers
//---------------------------------------------------------------------------------------
BOOL COberflaecheBuchungen::OnInitDialog()
{
CDialog::OnInitDialog();

CenterWindow(GetDesktopWindow());	// center to the hpc screen

TranslateStatic(m_ctrlStaticBuchungen);
TranslateStatic(m_ctrlStaticAltNeuFehler);
TranslateStatic(m_ctrlStaticSteinnummer);
TranslateButton(m_ctrlButtonErase);

m_tabAlleOberflaechen.Read();

int iarr[]={60,100};
m_ctrlListOberfl.SetTabStops(2,iarr);

SetListe(m_pAuftraege->Auftrag(0));

m_ctrlButtonErase.EnableWindow(FALSE);
    
return TRUE;
}
//----------------------------------------------------------------------------------
void COberflaecheBuchungen::SetListe(const CAuftrag& auf)
{
	CDC *dc = m_ctrlListOberfl.GetDC(); 
	CSize size = dc->GetTextExtent(_T("100	Oberfl. 10/50	Fehler: -/1		Maße: 200x100/220x150	Fehlecke: 10x10/20x20"));
	if (size.cx > m_ctrlListOberfl.GetHorizontalExtent())
		m_ctrlListOberfl.SetHorizontalExtent (size.cx + 60);
	m_ctrlListOberfl.ReleaseDC(dc); 


	m_ctrlListOberfl.ResetContent();
for(int i = 0; i < auf.m_Positionen.Anzahl(); i++)
    {
    CString str;
    SSatz ss(auf.m_Positionen.SteinSatzConst(i));
    CString falt(ss.m_FehlNummerAlt);
    CString fneu(ss.m_FehlNummer);
    if(falt.IsEmpty())
        falt = _T("-");
    if(fneu.IsEmpty())
        fneu = _T("-");

	CString MasseAlt;
	CString MasseNeu = ss.m_Laenge + _T("x") + ss.m_Breite ;
	if (ss.m_LaengeAlt.IsEmpty() && ss.m_BreiteAlt.IsEmpty())
		MasseAlt = _T("-");
	else
		MasseAlt = ss.m_LaengeAlt + _T("x") + ss.m_BreiteAlt ;
	CString FehleckeAlt;
	CString FehleckeNeu;
	if (ss.m_FehlLaengeAlt.IsEmpty() && ss.m_FehlBreiteAlt.IsEmpty())
		FehleckeAlt = _T("-");
	else
		FehleckeAlt = ss.m_FehlLaengeAlt + _T("x") + ss.m_FehlBreiteAlt ;
	if (ss.m_FehlLaenge.IsEmpty() && ss.m_FehlBreite.IsEmpty())
		FehleckeNeu = _T("-");
	else
		FehleckeNeu = ss.m_FehlLaenge + _T("x") + ss.m_FehlBreite ;
	

	//str.Format(_T("%s\t%s/%s\t%s/%s"),ss.m_Nummer,ss.m_OberNrAlt,ss.m_OberNr,falt,fneu);
	
	str.Format(_T("%s   Oberfl.: %s/%s   Fehler: %s/%s   Maße: %s/%s   Fehlecke: %s/%s"),ss.m_Nummer,ss.m_OberNrAlt,ss.m_OberNr,falt,fneu,MasseAlt, MasseNeu, FehleckeAlt, FehleckeNeu);
	
    m_ctrlListOberfl.AddString(str);
    }

}
//----------------------------------------------------------------------------------
void COberflaecheBuchungen::OnSelchangeListOberfl() 
{
m_curSel = m_ctrlListOberfl.GetCurSel();
if(m_curSel >= 0)
    m_ctrlButtonErase.EnableWindow(TRUE);	
}
//----------------------------------------------------------------------------------
void COberflaecheBuchungen::OnButtonErase() 
{
m_curSel = m_ctrlListOberfl.GetCurSel();

if(m_curSel < 0)
    return;

CAuftrag& auf = m_pAuftraege->Auftrag(0);

//SSatz ss(auf.m_Positionen.SteinSatz(m_curSel));    // Zu löschender Satz
SSatz as(auf.m_Positionen.SteinSatz(m_curSel));

m_tabGruppeOberflaechen.SetGruppe(m_tabAlleOberflaechen,as.m_MatGr);   // Oberfl-Tabelle nach MatGr erstellen

// In der Steinsatztabelle wieder richtigstellen
int ix;
if(m_pSteinSaetze->FoundAt(as.m_Nummer,ix))
	{
		SSatz ssUr(m_pSteinSaetze->SteinSatzConst(ix));
		ssUr.m_OberNr = as.m_OberNrAlt;
		ssUr.m_FehlNummer = as.m_FehlNummerAlt;
		ssUr.m_Laenge = as.m_LaengeAlt;
		ssUr.m_Breite = as.m_BreiteAlt;
		if (as.m_FehlLaengeAlt == _T("0"))
			ssUr.m_FehlLaenge = _T("");
		else
			ssUr.m_FehlLaenge = as.m_FehlLaengeAlt;
		if (ssUr.m_FehlBreiteAlt == _T("0"))
			ssUr.m_FehlBreite = _T("");
		else
			ssUr.m_FehlBreite = as.m_FehlBreiteAlt;
        int ixo = m_tabGruppeOberflaechen.GetIndexByKey(ssUr.m_MatGr,ssUr.m_OberNr);
        if(ixo >= 0)
            ssUr.m_Oberflaeche = m_tabGruppeOberflaechen.GetAt(ixo).m_bez;
        m_pSteinSaetze->SteinSatz(ix).Set(ssUr);
        m_pSteinSaetze->m_modified = TRUE;
    }


m_ctrlListOberfl.DeleteString(m_curSel);            // Aus Liste entfernen
auf.m_Positionen.RemoveAt(m_curSel);                // Aus Auftrag entfernen

if(m_curSel >= auf.m_Positionen.Anzahl())
    m_curSel--;

if(m_curSel >= 0)
    m_ctrlListOberfl.SetCurSel(m_curSel);
}

// alte Version 
//void COberflaecheBuchungen::OnButtonErase() 
//{
//m_curSel = m_ctrlListOberfl.GetCurSel();
//
//if(m_curSel < 0)
//    return;
//
//CAuftrag& auf = m_pAuftraege->Auftrag(0);
//
//int naechster = 0;
//SSatz ss(auf.m_Positionen.SteinSatz(m_curSel));    // Zu löschender Satz
//for(int i = m_curSel+1; i < auf.m_Positionen.Anzahl(); i++) // prüfen ob dahinter noch Sätze
//    {
//    if(ss.m_Nummer.CompareNoCase(auf.Position(i).Nummer()) == 0)
//        {
//        naechster = i;
//        }
//    }
//
//m_tabGruppeOberflaechen.SetGruppe(m_tabAlleOberflaechen,ss.m_MatGr);   // Oberfl-Tabelle nach MatGr erstellen
//
//if(naechster == 0) // nur dann muss im Lagerbestand richtiggestellt werden
//    {
//    // In der Steinsatztabelle wieder richtigstellen
//    int ix;
//    if(m_pSteinSaetze->FoundAt(ss.m_Nummer,ix))
//        {
//        SSatz ssUr(m_pSteinSaetze->SteinSatzConst(ix));
//        ssUr.m_OberNr = ss.m_OberNrAlt;
//        ssUr.m_FehlNummer = ss.m_FehlNummerAlt;
//        int ixo = m_tabGruppeOberflaechen.GetIndexByKey(ssUr.m_MatGr,ssUr.m_OberNr);
//        if(ixo >= 0)
//            ssUr.m_Oberflaeche = m_tabGruppeOberflaechen.GetAt(ixo).m_bez;
//        m_pSteinSaetze->SteinSatz(ix).Set(ssUr);
//        m_pSteinSaetze->m_modified = TRUE;
//        }
//    }
//else // nächsten alt auf gelöschten alt
//    {
//    SSatz ssNae(auf.m_Positionen.SteinSatzConst(naechster));
//    ssNae.m_OberNrAlt = ss.m_OberNrAlt;
//    ssNae.m_FehlNummerAlt = ss.m_FehlNummerAlt;
//    auf.m_Positionen.SteinSatz(naechster).Set(ssNae);
//    SetListe(auf);
//    }
//
//
//m_ctrlListOberfl.DeleteString(m_curSel);            // Aus Liste entfernen
//auf.m_Positionen.RemoveAt(m_curSel);                // Aus Auftrag entfernen
//
//if(m_curSel >= auf.m_Positionen.Anzahl())
//    m_curSel--;
//
//if(m_curSel >= 0)
//    m_ctrlListOberfl.SetCurSel(m_curSel);
//}
