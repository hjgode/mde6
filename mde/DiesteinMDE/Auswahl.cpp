// Auswahl.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "Verankerung.h"
#include "Auswahl.h"
#include "Einkauf.h"
#include "Preise.h"
#include "Info.h"
#include "OberflaecheAendern.h"
#include "AuftragsBearbeitung.h"
#include "Bestelleingang.h"
#include "LagerUm.h"
#include "Benutzer.h"
#include "Steinbruch.h"
#include "GatterAuswahl.h"

// CAuswahl-Dialogfeld

IMPLEMENT_DYNAMIC(CAuswahl, CDialog)


// Auswahl.cpp : implementation file
//

void KopiereBestandsDaten(CSteinSaetze *pSteinSaetze,const CString& BestandsDateiUr,const CString& BestandsDatei,
                          const CString& Statusdatei);
/////////////////////////////////////////////////////////////////////////////
// CAuswahl dialog
extern CString g_UserName;

CAuswahl::CAuswahl(CWnd* pParent /*=NULL*/)
	: CDialog(CAuswahl::IDD, pParent)
{

// Wenn am Computer eine neue Lagerbestandsdatei (Lagerbestand.csv) verfügbar ist, wird die Datei 
// Lagerbestand.csv nach Lagerbestandkopie.csv kopiert, in der Datei Lagerstatus wird Datum und Uhrzeit eingetragen (zur Kontrolle)
// Zum Vergleich werden jedoch die Datei-Statusdaten der Statusdatei verwendet, die bei der Ausführung der Kopie auf den Wert der
// Lagerbestandsdatei gesetzt werden.

// 1. Prüfen ob Lagerbestand oder Statusdatei neuer sind
// 2. wenn ja wird Lagerbestandkopie.csv erstellt
// 3. Der Dateistatus der Datei Lagerstatus.txt wird auf den gleichen Status wie Lagerbestand.csv gesetzt

KopiereBestandsDaten(&m_SteinSaetze,DATEI_LAGERBESTAND_UR,DATEI_LAGERBESTAND,DATEI_LAGERSTATUS);

m_SteinSaetze.ReadFile(); // Lagerbestand
m_Verankerungen.Read();

}

//----------------------------------------------------------------------------------------
void CAuswahl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTON_BESTELLEINGANG, m_ctrlButtonBestelleingang);
	DDX_Control(pDX, IDC_BUTTON_OBERFLAENDERN, m_ctrlButtonOberflAendern);
	DDX_Control(pDX, IDC_BUTTON_RESERVIERUNG, m_ctrlButtonReservierung);
	DDX_Control(pDX, IDC_BUTTON_LIEFERUNG, m_ctrlButtonLieferung);
	DDX_Control(pDX, IDC_BUTTON_PREISINFO, m_ctrlButtonPreisinfo);
	DDX_Control(pDX, IDC_STATIC_MOBILEDE, m_ctrlStaticMobileDE);
	DDX_Control(pDX, IDC_STATIC_DIESTEINMDE, m_ctrlStaticDiesteinMDE);
	DDX_Control(pDX, IDC_BUTTON_EINKAUF, m_ctrlButtonEinkauf);
	DDX_Control(pDX, IDC_BUTTON_INFO, m_ctrlButtonInfo);
	DDX_Control(pDX, IDC_BUTTON_VERKAUF, m_ctrlButtonVerkauf);
	DDX_Control(pDX, IDC_BUTTON_PRODUKTION, m_ctrlButtonProduktion);
	DDX_Control(pDX, IDC_BUTTON_LAGERUM, m_ctrlButtonLagerUm);
	DDX_Control(pDX, IDC_BUTTON_ZUGANG, m_ctrlButtonZugang);
	DDX_Control(pDX, IDC_BUTTON_INVENTUR, m_ctrlButtonInventur);
	DDX_Control(pDX, IDC_BUTTON_STEINBRUCH, m_ctrlButtonSteinbruch);
	DDX_Control(pDX, IDC_BUTTON_GATTERN, m_ctrlButtonGattern);
	DDX_Control(pDX, IDC_STATIC_LAGERDATUM, m_ctrlStaticLagerdatenDatum);
}
//----------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CAuswahl, CDialog)
	//{{AFX_MSG_MAP(CAuswahl)
	ON_BN_CLICKED(IDC_BUTTON_INFO, OnButtonInfo)
	ON_BN_CLICKED(IDC_BUTTON_PREISINFO, OnButtonPreisinfo)
	ON_BN_CLICKED(IDC_BUTTON_VERKAUF, OnButtonVerkauf)
	ON_BN_CLICKED(IDC_BUTTON_PRODUKTION, OnButtonProduktion)
	ON_BN_CLICKED(IDC_BUTTON_LAGERUM, OnButtonLagerum)
	ON_BN_CLICKED(IDC_BUTTON_ZUGANG, OnButtonZugang)
	ON_BN_CLICKED(IDC_BUTTON_INVENTUR, OnButtonInventur)
	ON_BN_CLICKED(IDC_BUTTON_EINKAUF, OnButtonEinkauf)
	ON_BN_CLICKED(IDC_BUTTON_LIEFERUNG, OnButtonLieferung)
	ON_BN_CLICKED(IDC_BUTTON_RESERVIERUNG, OnButtonReservierung)
	ON_BN_CLICKED(IDC_BUTTON_OBERFLAENDERN, OnButtonOberflaendern)
	ON_BN_CLICKED(IDC_BUTTON_BESTELLEINGANG, OnButtonBestelleingang)
    ON_BN_CLICKED(IDC_BUTTON_STEINBRUCH, OnBnClickedButtonSteinbruch)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_GATTERN, &CAuswahl::OnBnClickedButtonGattern)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
BOOL CAuswahl::OnInitDialog()
{
CDialog::OnInitDialog();

// Set the icon for this dialog.  The framework does this automatically
//  when the application's main window is not a dialog
//SetIcon(m_hIcon, TRUE);			// Set big icon
//SetIcon(m_hIcon, FALSE);		// Set small icon

CenterWindow(GetDesktopWindow());	// center to the hpc screen

TranslateStatic(m_ctrlStaticMobileDE);
TranslateStatic(m_ctrlStaticDiesteinMDE);
TranslateButton(m_ctrlButtonInfo);
TranslateButton(m_ctrlButtonPreisinfo);
TranslateButton(m_ctrlButtonVerkauf);
TranslateButton(m_ctrlButtonLieferung);
TranslateButton(m_ctrlButtonReservierung);
TranslateButton(m_ctrlButtonProduktion);
TranslateButton(m_ctrlButtonLagerUm);
TranslateButton(m_ctrlButtonEinkauf);
TranslateButton(m_ctrlButtonZugang);
TranslateButton(m_ctrlButtonOberflAendern);
TranslateButton(m_ctrlButtonInventur);
TranslateButton(m_ctrlButtonBestelleingang);
TranslateButton(m_ctrlButtonSteinbruch);
TranslateButton(m_ctrlButtonGattern);

CLagerOriginalStatusTabelle LagerStatus;
LagerStatus.Read();

// Anzeige der Dateiversion in kleinerer Schrift
CFont *m_Font1 = new CFont;
m_Font1->CreatePointFont(80, _T("MS Shell Dlg"));
m_ctrlStaticLagerdatenDatum.SetFont(m_Font1);
CString tempDatum = _T("???");
if (LagerStatus.GetIndexByKey(_T("Datum")) >= 0)
	tempDatum = LagerStatus.GetItemByKey(_T("Datum")).m_bez;
else
	if (m_SteinSaetze.m_Dateidatum != 0)
		tempDatum = m_SteinSaetze.m_Dateidatum.Format(_T("%d")) + _T(".") + m_SteinSaetze.m_Dateidatum.Format(_T("%m")) + _T(".") + m_SteinSaetze.m_Dateidatum.Format(_T("%Y")) + _T(" ") + m_SteinSaetze.m_Dateidatum.Format(_T("%H"))+ _T(":") + m_SteinSaetze.m_Dateidatum.Format(_T("%M"));
m_ctrlStaticLagerdatenDatum.SetWindowText(Sprache(_T("Lagerbestand vom")) + _T(" ") + tempDatum);


CString errMsg;
m_Scanner.Init(errMsg);
if(!errMsg.IsEmpty())
    AfxMessageBox(errMsg);


g_UserName = _T("");
if(g_Optionen.BenutzerEnabled())
    {
    CBenutzer userdlg;
    userdlg.m_pScanner = &m_Scanner;
    m_Scanner.setEnableScanner(TRUE);

    if(userdlg.DoModal() != IDOK)
        {
        m_Scanner.setEnableScanner(FALSE);//m_scanEnable = FALSE;
        OnCancel();
        return FALSE;
        }
    g_UserName = userdlg.m_userName;
    m_Scanner.setEnableScanner(FALSE);
    }

#ifndef _DEBUG
if(!g_Optionen.InfoEnabled())
    m_ctrlButtonInfo.EnableWindow(FALSE);

if(!g_Optionen.PreisinfoEnabled())
    m_ctrlButtonPreisinfo.EnableWindow(FALSE);

if(!g_Optionen.VerkaufEnabled())
    m_ctrlButtonVerkauf.EnableWindow(FALSE);

if(!g_Optionen.LieferungEnabled())
    m_ctrlButtonLieferung.EnableWindow(FALSE);

if(!g_Optionen.ProduktionEnabled())
    m_ctrlButtonProduktion.EnableWindow(FALSE);

if(!g_Optionen.ReservierungEnabled())
    m_ctrlButtonReservierung.EnableWindow(FALSE);

if(!g_Optionen.LagerUmEnabled())
    m_ctrlButtonLagerUm.EnableWindow(FALSE);

if(!g_Optionen.EinkaufEnabled())
    m_ctrlButtonEinkauf.EnableWindow(FALSE);

if(!g_Optionen.ZugangEnabled())
    m_ctrlButtonZugang.EnableWindow(FALSE);

if(!g_Optionen.InventurEnabled())
    m_ctrlButtonInventur.EnableWindow(FALSE);

if(!g_Optionen.OberflAendernEnabled())
    m_ctrlButtonOberflAendern.EnableWindow(FALSE);

if(!g_Optionen.ContainerEnabled())
    m_ctrlButtonBestelleingang.EnableWindow(FALSE);

if(!g_Optionen.SteinbruchEnabled())
    m_ctrlButtonSteinbruch.EnableWindow(FALSE);

if(!g_Optionen.GatternEnabled())
    m_ctrlButtonGattern.EnableWindow(FALSE);

#endif

UpdateData(FALSE);

//void SprachTest();
//SprachTest();
//CPreislistenTabelle tab;
//tab.Read();
//tab.Debug();

return TRUE;  // return TRUE  unless you set the focus to a control
}
//****************************************************************************
//****************************************************************************
// CAuswahl message handlers

//****************************************************************************
void CAuswahl::OnButtonInfo() 
{
CInfo info;
info.m_pSteinSaetze = &m_SteinSaetze;

info.m_pScanner = &m_Scanner;
m_Scanner.setEnableScanner(TRUE);

info.DoModal();	

m_Scanner.setEnableScanner(FALSE);
}
//****************************************************************************
void CAuswahl::OnButtonPreisinfo() 
{
CPreise preise;
preise.m_pSteinSaetze = &m_SteinSaetze;
preise.m_pVerankerungen = &m_Verankerungen;

preise.m_pScanner = &m_Scanner;
m_Scanner.setEnableScanner(TRUE);

preise.DoModal();	

m_Scanner.setEnableScanner(FALSE);
}
//****************************************************************************
void CAuswahl::OnButtonVerkauf() 
{
m_Auftraege.m_strName = NAME_VERKAUF;
m_Auftraege.ReadFile();
	
if(m_Auftraege.Anzahl())
    {
    if(m_strLetzterVerkauf.IsEmpty())
        m_strLetzterVerkauf = m_Auftraege.Auftrag(0).m_strIdent;
    }
// Hier Rück abschalten
CAuftragsBearbeitung aufBearbeitung(this);  // Dialogbox Auftragsbearbeitung

aufBearbeitung.m_nModus = ID_VERKAUF;    // Verkauf
m_SteinSaetze.m_modified = false;
aufBearbeitung.m_pSteinSaetze = &m_SteinSaetze;
aufBearbeitung.m_pAuftraege = &m_Auftraege;
aufBearbeitung.m_pstrLetzterAuftrag = &m_strLetzterVerkauf;

aufBearbeitung.m_pScanner = &m_Scanner;

m_Scanner.setEnableScanner(TRUE);

aufBearbeitung.DoModal();	

m_Scanner.setEnableScanner(FALSE);
	
m_Auftraege.Save();
if(m_SteinSaetze.m_modified)
    m_SteinSaetze.Save();
}
//****************************************************************************
void CAuswahl::OnButtonLieferung() 
{
m_Auftraege.m_strName = NAME_VERKAUF;
m_Auftraege.ReadFile();
	
if(m_Auftraege.Anzahl())
    {
    if(m_strLetzterVerkauf.IsEmpty())
        m_strLetzterVerkauf = m_Auftraege.Auftrag(0).m_strIdent;
    }
// Hier Rück abschalten
CAuftragsBearbeitung aufBearbeitung(this);  // Dialogbox Auftragsbearbeitung

aufBearbeitung.m_nModus = ID_LIEFERUNG;    // Verkauf reservierter Sätze
aufBearbeitung.m_pSteinSaetze = &m_SteinSaetze;
aufBearbeitung.m_pAuftraege = &m_Auftraege;
aufBearbeitung.m_pstrLetzterAuftrag = &m_strLetzterVerkauf;

aufBearbeitung.m_pScanner = &m_Scanner;

m_Scanner.setEnableScanner(TRUE);// m_scanEnable = TRUE;

aufBearbeitung.DoModal();	

m_Scanner.setEnableScanner(FALSE);//m_scanEnable = FALSE;
	
m_Auftraege.Save();
if(m_SteinSaetze.m_modified)
    m_SteinSaetze.Save();
}
//****************************************************************************
void CAuswahl::OnButtonProduktion() 
{
m_Auftraege.m_strName = NAME_PRODUKTION;
m_Auftraege.ReadFile();

if(m_Auftraege.Anzahl())
    {
    if(m_strLetzterProduktion.IsEmpty())
        m_strLetzterProduktion = m_Auftraege.Auftrag(0).m_strIdent;
    }

CAuftragsBearbeitung aufBearbeitung(this);  // Dialogbox Auftragsbearbeitung

aufBearbeitung.m_nModus = ID_PRODUKTION;
aufBearbeitung.m_pSteinSaetze = &m_SteinSaetze;
aufBearbeitung.m_pAuftraege = &m_Auftraege;
aufBearbeitung.m_pstrLetzterAuftrag = &m_strLetzterProduktion;

aufBearbeitung.m_pScanner = &m_Scanner;

m_Scanner.setEnableScanner(TRUE);

aufBearbeitung.DoModal();	

m_Scanner.setEnableScanner(FALSE);
	
m_Auftraege.Save();
if(m_SteinSaetze.m_modified)
    m_SteinSaetze.Save();
}
//****************************************************************************
void CAuswahl::OnButtonReservierung() 
{
m_Auftraege.m_strName = NAME_RESERVIERUNG;
m_Auftraege.ReadFile();
	
if(m_Auftraege.Anzahl())
    {
    if(m_strLetzterReservierung.IsEmpty())
        m_strLetzterReservierung = m_Auftraege.Auftrag(0).m_strIdent;
    }
// Hier Rück abschalten
CAuftragsBearbeitung aufBearbeitung(this);  // Dialogbox Auftragsbearbeitung

aufBearbeitung.m_nModus = ID_RESERVIERUNG;
aufBearbeitung.m_pSteinSaetze = &m_SteinSaetze;
aufBearbeitung.m_pAuftraege = &m_Auftraege;
aufBearbeitung.m_pstrLetzterAuftrag = &m_strLetzterReservierung;

aufBearbeitung.m_pScanner = &m_Scanner;

m_Scanner.setEnableScanner(TRUE);

aufBearbeitung.DoModal();	

m_Scanner.setEnableScanner(FALSE);
	
m_Auftraege.Save();
if(m_SteinSaetze.m_modified)
    m_SteinSaetze.Save();
}
//****************************************************************************
void CAuswahl::OnButtonEinkauf()
{
m_Auftraege.m_strName = NAME_BESTELLUNGENEINGANG;
m_Auftraege.ReadFile();

if(m_Auftraege.Exist(NAME_BESTELLUNGENEINGANG) < 0)
    {
    CAuftrag auf(NAME_BESTELLUNGENEINGANG);
    m_Auftraege.Add(auf);
    }
m_Auftraege.Auftrag(0).m_strIdent = NAME_BESTELLUNGENEINGANG; // vorsichtshalber, falls existierende Datei korrupt

CEinkauf einkauf;

einkauf.m_pSteinSaetze = &m_SteinSaetze;
einkauf.m_pScanner = &m_Scanner;
einkauf.m_pAuftraege = &m_Auftraege;

m_Scanner.setEnableScanner(TRUE);

einkauf.DoModal();	

m_Scanner.setEnableScanner(FALSE);
}
//****************************************************************************
void CAuswahl::OnButtonZugang() 
{
m_Auftraege.m_strName = NAME_ZUGANG;
m_Auftraege.ReadFile();
	
if(m_Auftraege.Exist(NAME_ZUGANG) < 0)
    {
    CAuftrag auf(NAME_ZUGANG);
    m_Auftraege.Add(auf);
    }
m_Auftraege.Auftrag(0).m_strIdent = NAME_ZUGANG; // vorsichtshalber, falls existierende Datei korrupt

CAuftragsBearbeitung aufBearbeitung(this);  // Dialogbox Auftragsbearbeitung

aufBearbeitung.m_nModus = ID_ZUGANG;
aufBearbeitung.m_pSteinSaetze = &m_SteinSaetze;
aufBearbeitung.m_pAuftraege = &m_Auftraege;
CString str = NAME_ZUGANG;
aufBearbeitung.m_pstrLetzterAuftrag = &str; //dummy

aufBearbeitung.m_pScanner = &m_Scanner;

m_Scanner.setEnableScanner(TRUE);

aufBearbeitung.DoModal();

if(m_SteinSaetze.m_modified)
    m_SteinSaetze.Save();		

m_Scanner.setEnableScanner(FALSE);

}
//****************************************************************************
void CAuswahl::OnButtonLagerum() 
{
if(!m_SteinSaetze.Anzahl())
    {
    AfxMessageBox(Sprache(_T("Kein Lagerbestand vorhanden!")));
    return;
    }
m_Auftraege.m_strName = NAME_LAGERUM;
m_Auftraege.ReadFile();

if(m_Auftraege.Exist(NAME_LAGERUM) < 0)
    {
    CAuftrag auf(NAME_LAGERUM);
    m_Auftraege.Add(auf);
    }

m_Auftraege.Auftrag(0).m_strIdent = NAME_LAGERUM; // vorsichtshalber, falls existierende Datei korrupt

CLagerUm lagerUmbuchung;
lagerUmbuchung.m_pSteinSaetze = &m_SteinSaetze;

lagerUmbuchung.m_pScanner = &m_Scanner;
lagerUmbuchung.m_pAuftraege = &m_Auftraege;

lagerUmbuchung.m_pVerankerungen = &m_Verankerungen;

m_Scanner.setEnableScanner(TRUE);

lagerUmbuchung.DoModal();	

m_Auftraege.Save();
if(m_SteinSaetze.m_modified)
    m_SteinSaetze.Save();

m_Scanner.setEnableScanner(FALSE);
}
//****************************************************************************
void CAuswahl::OnButtonOberflaendern() 
{
if(!m_SteinSaetze.Anzahl())
    {
    AfxMessageBox(Sprache(_T("Kein Lagerbestand vorhanden!")));
    return;
    }
m_Auftraege.m_strName = NAME_OBERFLAENDERN;
m_Auftraege.ReadFile();

if(m_Auftraege.Exist(NAME_OBERFLAENDERN) < 0)
    {
    CAuftrag auf(NAME_OBERFLAENDERN);
    m_Auftraege.Add(auf);
    }

m_Auftraege.Auftrag(0).m_strIdent = NAME_OBERFLAENDERN; // vorsichtshalber, falls existierende Datei korrupt

COberflaecheAendern oberflAendern;
oberflAendern.m_pSteinSaetze = &m_SteinSaetze;

oberflAendern.m_pScanner = &m_Scanner;
oberflAendern.m_pAuftraege = &m_Auftraege;

m_Scanner.setEnableScanner(TRUE);

oberflAendern.DoModal();	

m_Auftraege.Save();
if(m_SteinSaetze.m_modified)
    m_SteinSaetze.Save();

m_Scanner.setEnableScanner(FALSE);
}
//****************************************************************************
void CAuswahl::OnButtonInventur() 
{
m_Auftraege.m_strName = NAME_INVENTUR;
m_Auftraege.ReadFile();

if(m_Auftraege.Exist(NAME_INVENTUR) < 0)
    {
    CAuftrag auf(NAME_INVENTUR);
    m_Auftraege.Add(auf);
    }
m_Auftraege.Auftrag(0).m_strIdent = NAME_INVENTUR; // vorsichtshalber, falls existierende Datei korrupt

CAuftragsBearbeitung aufBearbeitung(this);  // Dialogbox Auftragsbearbeitung

aufBearbeitung.m_nModus = ID_INVENTUR;    // Verkauf
aufBearbeitung.m_pSteinSaetze = &m_SteinSaetze;
aufBearbeitung.m_pAuftraege = &m_Auftraege;

CString str = NAME_INVENTUR;
aufBearbeitung.m_pstrLetzterAuftrag = &str; //dummy

aufBearbeitung.m_pScanner = &m_Scanner;

m_Scanner.setEnableScanner(FALSE);

aufBearbeitung.DoModal();	

m_Scanner.setEnableScanner(FALSE);

}
//****************************************************************************
void CAuswahl::OnButtonBestelleingang() 
{

CSteinSaetze ContainerSteinSaetze;

KopiereBestandsDaten(&m_SteinSaetze,DATEI_CONTAINERBESTAND_UR,DATEI_CONTAINERBESTAND,DATEI_CONTAINERSTATUS);

ContainerSteinSaetze.ReadFile(DATEI_CONTAINERBESTAND); // Containerbestand

if(!ContainerSteinSaetze.Anzahl())
    {
    AfxMessageBox(Sprache(_T("Kein Containerbestand vorhanden!")));
    return;
    }
m_Auftraege.m_strName = NAME_CONTAINERBUCHUNG;
m_Auftraege.ReadFile();

if(m_Auftraege.Exist(NAME_CONTAINERBUCHUNG) < 0)
    {
    CAuftrag auf(NAME_CONTAINERBUCHUNG);
    m_Auftraege.Add(auf);
    }

m_Auftraege.Auftrag(0).m_strIdent = NAME_CONTAINERBUCHUNG; // vorsichtshalber, falls existierende Datei korrupt

CBestelleingang bestellEingang;
bestellEingang.m_pContSteinSaetze = &ContainerSteinSaetze;

bestellEingang.m_pScanner = &m_Scanner;
bestellEingang.m_pAuftraege = &m_Auftraege;

m_Scanner.setEnableScanner(TRUE);

bestellEingang.DoModal();	

m_Auftraege.Save();
if(ContainerSteinSaetze.m_modified)
    ContainerSteinSaetze.Save(DATEI_CONTAINERBESTAND);

m_Scanner.setEnableScanner(FALSE);
}
//****************************************************************************
void CAuswahl::OnBnClickedButtonSteinbruch()
{
m_Auftraege.m_strName = NAME_BLOECKE;
m_Auftraege.ReadFile();
	
if(m_Auftraege.Exist(NAME_BLOECKE) < 0)
    {
    CAuftrag auf(NAME_BLOECKE);
    m_Auftraege.Add(auf);
    }
m_Auftraege.Auftrag(0).m_strIdent = NAME_BLOECKE; // vorsichtshalber, falls existierende Datei korrupt

// zusätzlich die Änderungen in einer zweiten Datei abspeichern
m_AuftragBlockKorr.m_strName = NAME_BLOCKAENDERUNGEN;
m_AuftragBlockKorr.ReadFile();
if(m_AuftragBlockKorr.Exist(NAME_BLOCKAENDERUNGEN) < 0)
    {
    CAuftrag auf(NAME_BLOCKAENDERUNGEN);
    m_AuftragBlockKorr.Add(auf);
    }
m_AuftragBlockKorr.Auftrag(0).m_strIdent = NAME_BLOCKAENDERUNGEN; // vorsichtshalber, falls existierende Datei korrupt


CSteinbruch steinbruch;

steinbruch.m_pAuftraege = &m_Auftraege;
steinbruch.m_pSteinSaetze = &m_SteinSaetze;
steinbruch.m_pAuftragBlockKorr = &m_AuftragBlockKorr;
steinbruch.m_modifiedAuftraege = FALSE;

steinbruch.m_pScanner = &m_Scanner;

m_Scanner.setEnableScanner(TRUE);
// Rohbloecke erfassen
steinbruch.DoModal();

if (steinbruch.m_modifiedAuftraege == TRUE)
{
	m_Auftraege.Save();
	m_AuftragBlockKorr.Save();
}

if(m_SteinSaetze.m_modified)
    m_SteinSaetze.Save();

m_Scanner.setEnableScanner(FALSE);
}
//****************************************************************************
void CAuswahl::OnBnClickedButtonGattern()
{
	// Hier Rück abschalten
	CGatterAuswahl gatterAuswahl(this);  // Dialogbox Gatterauftraege

	m_SteinSaetze.m_modified = false;
	gatterAuswahl.m_pSteinSaetze = &m_SteinSaetze;
	gatterAuswahl.m_pAuftraege = &m_Auftraege;
	gatterAuswahl.m_pstrLetzterGatterAuftrag = &m_strLetzterGatterAuftrag ;
	gatterAuswahl.m_pstrLetzterBlock = &m_strLetzterBlock;

	gatterAuswahl.m_pScanner = &m_Scanner;

	gatterAuswahl.DoModal();
}

//****************************************************************************
void KopiereBestandsDaten(CSteinSaetze *pSteinSaetze,const CString& BestandsDateiUr,const CString& BestandsDatei,
                          const CString& StatusDatei)
{
BOOL flagCopy = FALSE;   // Soll Lagerbestand kopiert werden (

MDEFile fileUr;
CString pathFileUr;
pathFileUr.Format(_T("%s\\%s"),FOLDER_DOCU,BestandsDateiUr);
CFileStatus statusUr;

MDEFile file;
CString pathFileName;
pathFileName.Format(_T("%s\\%s"),FOLDER_DOCU,BestandsDatei);
CFileStatus status;

MDEFile fileStatus;
CString pathFileStatus;
pathFileStatus.Format(_T("%s\\%s"),FOLDER_DOCU,StatusDatei);
CFileStatus statusStatus;

if(fileStatus.GetStatus(pathFileStatus,statusStatus)) // Wenn Statusdatei vorhanden, prüfen ob neuer Lagerbestand oder Statusdatei zuletzt geändert
    {
    if(fileUr.GetStatus(pathFileUr,statusUr))
        {
        if(statusUr.m_mtime > statusStatus.m_mtime)
            {
            flagCopy = TRUE;
            }
        }
    else
        flagCopy = TRUE;
    }
else
    flagCopy = TRUE;

if(!flagCopy)
    {
    if(!file.GetStatus(pathFileName,status)) // wenn Datei nicht vorhanden
        flagCopy = TRUE;
	else
		if (status.m_size == 0 )
			flagCopy = TRUE;
    }

if(flagCopy)
    {
    fileStatus.Open(pathFileStatus,CFile::modeWrite|CFile::modeCreate);
    CString timestr;
    fileUr.GetStatus(pathFileUr,statusUr);
    timestr.Format(_T("%02d.%02d.%04d %02d:%02d:%02d\r\n%s"),statusUr.m_mtime.GetDay(),statusUr.m_mtime.GetMonth(),
                                                       statusUr.m_mtime.GetYear(),statusUr.m_mtime.GetHour(),
                                                       statusUr.m_mtime.GetMinute(),statusUr.m_mtime.GetSecond(),
                                                       _T("Letztes Änderungsdatum der verwendeten Original-Lagerbestandsdatei"));
    fileStatus.WriteString(timestr);
    //fileStatus.GetStatus(statusStatus);
    //statusStatus.m_mtime = statusUr.m_mtime;
    //fileStatus.Close();
// statt kommentiert
    fileStatus.Close();
    CFile::GetStatus(pathFileStatus,statusStatus);
    statusStatus.m_mtime = statusUr.m_mtime;
//------------------

    fileStatus.SetStatus(pathFileStatus,statusStatus); // Letzet Änderungszeit auf Änderungszeit der Lager-Originaldatei setzten

    pSteinSaetze->ReadFile(BestandsDateiUr);
    pSteinSaetze->Save(BestandsDatei);    //Auf LagerbestandCopy kopieren und nur diese datei verwenden
    }
}
//****************************************************************************
//****************************************************************************
//#include "Sprache.h"
//void SprachTest()
//{
////return;
//
////CSprache sprache;
//
////sprache.Read(_T("IT "),_T("US "));
//
////AlertInt(sprache.m_arrGerman.GetCount());
//
////AfxMessageBox(sprache.Translate(_T("Lagerumbuchung")));
////AfxMessageBox(sprache.Translate(_T("Inventur")));
////AfxMessageBox(sprache.Translate(_T("Diestein MDE")));
////AfxMessageBox(sprache.Translate(_T("..Lagerumbuchung??::")));
////AfxMessageBox(sprache.Translate(_T("   Inventur:")));
////AfxMessageBox(sprache.Translate(_T("Neues Gerät "),_T("Dolphin"),_T(" ist schön")));
////AfxMessageBox(sprache.Translate(_T("Altes"),_T("(alles)"),_T(" ist häßlich")));
////AfxMessageBox(sprache.Translate(_T("Ganz Altes noch häßlicher"),_T("(fast alles)"),_T("")));
////AfxMessageBox(sprache.Translate(_T(""),_T("(fast alles)"),_T(" Neues gut")));
////AfxMessageBox(sprache.Translate(_T("Sonst alles OK!!")));
////sprache.Sprache(_T("2!!Lagerumbuchung,,"));
////sprache.Sprache(_T("\"Inventur\""));
//}

