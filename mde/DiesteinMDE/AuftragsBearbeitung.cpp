// AuftragsBearbeitung.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "PlattenZugang.h"
#include "Positionen.h"
#include "PositionenInfo.h"
#include "AuftragsBearbeitung.h"

/////////////////////////////////////////////////////////////////////////////
// CAuftrag dialog

IMPLEMENT_DYNAMIC(CAuftragsBearbeitung, CDialog)

CAuftragsBearbeitung::CAuftragsBearbeitung(CWnd* pParent /*=NULL*/)
	: CDialog(CAuftragsBearbeitung::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAuftragsBearbeitung)
	m_strAktuellerAuftrag = _T("");
	m_strPosition = _T("");
	//}}AFX_DATA_INIT
m_nModus = 0;
}


void CAuftragsBearbeitung::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAuftragsBearbeitung)
    DDX_Control(pDX, IDC_STATIC_LOESCHAUFTRAG, m_ctrlStaticLoeschAuftrag);
    DDX_Control(pDX, IDC_STATIC_LOESCHPOSITION, m_ctrlStaticLoeschPosition);
    DDX_Control(pDX, IDC_BUTTON_LOESCHPOSITION, m_ctrlLoeschPosition);
    DDX_Control(pDX, IDC_BUTTON_POSANZEIGEN, m_ctrlPosAnzeigen);
    DDX_Control(pDX, IDC_BUTTON_LOESCHAUFTRAG, m_ctrlLoeschAuftrag);
    DDX_Control(pDX, IDC_BUTTON_ADDAUFTRAG, m_AddAuftrag);
    DDX_Control(pDX, IDC_LIST_POSITIONEN, m_ctrlPositionen);
    DDX_Control(pDX, IDC_BUTTON_BEARBEITEN, m_ctrlBearbeiten);
    DDX_Control(pDX, IDC_COMBO_AUFTRAEGE, m_ctrlComboAuftraege);
    //	DDX_CBString(pDX, IDC_COMBO_AUFTRAEGE, m_strAktuellerAuftrag);
    //	DDX_LBString(pDX, IDC_LIST_POSITIONEN, m_strPosition);
    //DDX_Text(pDX, IDC_STATIC_AUFTRAEGE, m_strStaticAuftraege);
    //DDX_Text(pDX, IDC_STATIC_POSITIONEN, m_strStaticPositionen);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_STATIC_AUFTRAEGE, m_ctrlStaticAuftraege);
    DDX_Control(pDX, IDC_STATIC_POSITIONEN, m_ctrlStaticPositionen);
}


BEGIN_MESSAGE_MAP(CAuftragsBearbeitung, CDialog)
	//{{AFX_MSG_MAP(CAuftragsBearbeitung)
	ON_CBN_KILLFOCUS(IDC_COMBO_AUFTRAEGE, OnKillfocusComboAuftraege)
	ON_BN_CLICKED(IDC_BUTTON_ADDAUFTRAG, OnButtonAddauftrag)
	ON_BN_CLICKED(IDC_BUTTON_LOESCHAUFTRAG, OnButtonLoeschauftrag)
	ON_BN_CLICKED(IDC_BUTTON_BEARBEITEN, OnButtonBearbeiten)
	ON_CBN_SELCHANGE(IDC_COMBO_AUFTRAEGE, OnSelchangeComboAuftraege)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_LOESCHPOSITION, OnButtonLoeschposition)
	ON_BN_CLICKED(IDC_BUTTON_POSANZEIGEN, OnButtonPosanzeigen)
	//}}AFX_MSG_MAP
    ON_LBN_SELCHANGE(IDC_LIST_POSITIONEN, &CAuftragsBearbeitung::OnLbnSelchangeListPositionen)
	ON_CBN_SETFOCUS(IDC_COMBO_AUFTRAEGE, &CAuftragsBearbeitung::OnCbnSetfocusComboAuftraege)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------------
BOOL CAuftragsBearbeitung::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
TranslateStatic(m_ctrlStaticLoeschAuftrag);
TranslateStatic(m_ctrlStaticLoeschPosition);
TranslateButton(m_AddAuftrag);
TranslateButton(m_ctrlBearbeiten);
TranslateButton(m_ctrlPosAnzeigen);

m_strAktuellerAuftrag = *m_pstrLetzterAuftrag;
if(!m_strAktuellerAuftrag.IsEmpty())
    {
    if(m_pAuftraege->Exist(m_strAktuellerAuftrag) < 0)
        {
        CAuftrag auf(m_strAktuellerAuftrag);
        m_pAuftraege->Add(auf);
        }
    }

SetComboBox(m_strAktuellerAuftrag);
SetPositionenListe(m_strAktuellerAuftrag);

/*
if(!CAuftragsBearbeitung::m_pAuftraege->m_strName.Compare(NAME_ZUGANG))
    m_nModus = ID_ZUGANG;

if(!CAuftragsBearbeitung::m_pAuftraege->m_strName.Compare(NAME_INVENTUR))
    m_nModus = ID_INVENTUR;
*/
if(m_nModus == ID_BESTELLUNGENEINGANG)
    {
    CAuftragsBearbeitung::m_AddAuftrag.EnableWindow(FALSE);
    CAuftragsBearbeitung::m_ctrlBearbeiten.EnableWindow(FALSE);
    }
if((m_nModus == ID_INVENTUR) || (m_nModus == ID_ZUGANG))
    {
    CAuftragsBearbeitung::m_AddAuftrag.EnableWindow(FALSE);
    }
CString strauf;
m_ctrlStaticAuftraege.GetWindowText(strauf);

if(m_nModus == ID_BESTELLUNGENEINGANG)
    strauf = Sprache(_T("Bestellnummer: "));
else
    strauf = Sprache(strauf) + _T(" ");
strauf += Sprache(m_pAuftraege->m_strName);
m_ctrlStaticAuftraege.SetWindowText(strauf);

TranslateStatic(m_ctrlStaticPositionen);

	
return TRUE;  // return TRUE unless you set the focus to a control
	          // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CAuftragsBearbeitung message handlers

void CAuftragsBearbeitung::OnKillfocusComboAuftraege() 
{
//OnButtonAddauftrag();
}
//-----------------------------------------------------------------------------------
void CAuftragsBearbeitung::OnSelchangeComboAuftraege() 
{
int aufix = m_ctrlComboAuftraege.GetCurSel();
if(aufix < 0)
    return;
m_strAktuellerAuftrag = m_pAuftraege->Auftrag(aufix).m_strIdent;
SetPositionenListe(m_pAuftraege->Auftrag(aufix).m_strIdent);
}
//-----------------------------------------------------------------------------------
void CAuftragsBearbeitung::SetComboBox(CString strAuftrag)
{
m_ctrlComboAuftraege.ResetContent();
for(int i = 0; i < m_pAuftraege->Anzahl(); i++)
    m_ctrlComboAuftraege.AddString(m_pAuftraege->Auftrag(i).m_strIdent);
//int index = m_ctrlAuftraege.FindStringExact(0,strAuftrag);
int index = FindNumber(strAuftrag);
if(index >= 0)
    {
    m_ctrlComboAuftraege.SetCurSel(index);
    }
else
    m_ctrlComboAuftraege.SetCurSel(0);
}
//-----------------------------------------------------------------------------------
void CAuftragsBearbeitung::SetPositionenListe(CString strAuftrag)
{
m_ctrlPositionen.ResetContent();
int index = m_pAuftraege->Exist(strAuftrag);
if(index >= 0)
    {
    CAuftrag auf = m_pAuftraege->Auftrag(index);
    for(int i = 0; i < auf.m_Positionen.Anzahl(); i++)
        {
        if(auf.Position(i).Menge1() < 0)
            m_ctrlPositionen.AddString(auf.Position(i).Nummer() + _T("->"));
        else
            m_ctrlPositionen.AddString(auf.Position(i).Nummer());
        }
    *m_pstrLetzterAuftrag = m_pAuftraege->Auftrag(index).m_strIdent;
    }
}
//-----------------------------------------------------------------------------------
void CAuftragsBearbeitung::OnButtonAddauftrag() 
{
m_ctrlComboAuftraege.GetWindowText(m_strAktuellerAuftrag);
m_strAktuellerAuftrag.TrimLeft();
m_strAktuellerAuftrag.TrimRight();
if(m_strAktuellerAuftrag.IsEmpty())
    {
    m_ctrlComboAuftraege.SetFocus();
    return;
    }
if(m_pAuftraege->Exist(m_strAktuellerAuftrag) < 0)
    {
    CAuftrag auf(m_strAktuellerAuftrag);
    m_pAuftraege->Add(auf);
    }
SetComboBox(m_strAktuellerAuftrag);
SetPositionenListe(m_strAktuellerAuftrag);
m_ctrlComboAuftraege.SetFocus();
}
//-----------------------------------------------------------------------------------
void CAuftragsBearbeitung::OnButtonLoeschauftrag() 
{
m_ctrlComboAuftraege.GetWindowText(m_strAktuellerAuftrag);
int index = m_pAuftraege->Exist(m_strAktuellerAuftrag);
if(index >= 0)
    {
    if(AfxMessageBox(Sprache(_T("Wollen Sie den Auftrag wirklich löschen?")),MB_YESNO|MB_ICONQUESTION)
                     == IDYES)
        {
        // Alle Gespeicherten Steine zurückschreiben
        CAuftrag *pRefAuf;
        pRefAuf = &m_pAuftraege->arr[index];
        if(!m_strAktuellerAuftrag.CompareNoCase(NAME_ZUGANG))
            {
            for(int i = 0; i < pRefAuf->m_Positionen.Anzahl(); i++)
				{	
				int steinix;
				m_pSteinSaetze->FoundAt (pRefAuf->m_Positionen.arr[i].Nummer(), steinix);
				if (steinix >= 0)
					{
					if(fabs(pRefAuf->Position(i).Menge1()-m_pSteinSaetze->SteinSatz(steinix).Menge1()) < 0.01)
						m_pSteinSaetze->RemoveAt(steinix);
					else
						m_pSteinSaetze->SubSatz(pRefAuf->m_Positionen.arr[i]); // Menge wieder aus Steinliste entfernen
					}
				}
            }
        else
            {
            if(m_nModus != ID_BESTELLUNGENEINGANG)
                {
                for(int i = 0; i < pRefAuf->m_Positionen.Anzahl(); i++)
                    m_pSteinSaetze->AddSatz(pRefAuf->m_Positionen.arr[i]); // Wieder in Steinliste zurückschreiben
                }
            }
        if((m_nModus == ID_ZUGANG) || (m_nModus == ID_INVENTUR))
            {
            m_pAuftraege->Auftrag(0).m_Positionen.arr.RemoveAll();
            }
        else
            {
            if(m_nModus == ID_BESTELLUNGENEINGANG)
                {
                *m_pAufLoesch = m_pAuftraege->Auftrag(0);   // Alle steine in Löschliste
                m_pAuftraege->Auftrag(0).m_Positionen.arr.RemoveAll();
                }
            else
                {
                m_pAuftraege->Remove(m_strAktuellerAuftrag);
                index = max(index-1,0);
                }
            }
        }
    }

m_strAktuellerAuftrag = _T("");
if(m_pAuftraege->Anzahl())
    m_strAktuellerAuftrag = m_pAuftraege->Auftrag(index).m_strIdent;

m_pAuftraege->Save();
if((m_nModus == ID_INVENTUR))
	m_pSteinSaetze->Save();
if((m_nModus == ID_ZUGANG))
	m_pSteinSaetze->m_modified = TRUE;

SetComboBox(m_strAktuellerAuftrag);
SetPositionenListe(m_strAktuellerAuftrag);
}
//-----------------------------------------------------------------------------------
void CAuftragsBearbeitung::OnButtonBearbeiten() 
{
m_ctrlComboAuftraege.GetWindowText(m_strAktuellerAuftrag);
int index = m_pAuftraege->Exist(m_strAktuellerAuftrag);
if(index < 0)
    return;     // Kein Auftrag vorgegeben
if(!m_strAktuellerAuftrag.CompareNoCase(NAME_ZUGANG))
    {
    CPlattenZugang zugang(this);
    zugang.m_nModus = ID_ZUGANG;

    g_baseSteinSatz.m_value.Empty();
    zugang.m_pSteinSaetze = m_pSteinSaetze;       // Original-Steinsatztabelle
    zugang.m_pAuftraege = m_pAuftraege;
    zugang.m_pAuftrag = &m_pAuftraege->Auftrag(index);
    zugang.m_pScanner = m_pScanner;

	m_pScanner->setEnableScanner(FALSE);
    zugang.DoModal();
    }
else
    {
    CPositionen	positionenDialog(this);

    positionenDialog.m_nModus = m_nModus;   // Verkauf,Lieferung,Produktion,Reservierung,Zugang,Inventur
    positionenDialog.m_pSteinSaetze = m_pSteinSaetze;       // Original-Steinsatztabelle
    positionenDialog.m_pAuftraege = m_pAuftraege;
    positionenDialog.m_pAuftrag = &m_pAuftraege->Auftrag(index);
    positionenDialog.m_pScanner = m_pScanner;

	m_pScanner->setEnableScanner(FALSE);
    positionenDialog.DoModal();
    }
m_pScanner->setEnableScanner(TRUE);

SetComboBox(m_strAktuellerAuftrag);
SetPositionenListe(m_pAuftraege->Auftrag(index).m_strIdent);

CString strButt;

//CAuftragsBearbeitung::m_ctrlBearbeiten.GetWindowText(strButt);
//CAuftragsBearbeitung::m_ctrlBearbeiten.SetWindowText(_T("Speichern.."));
//CSaveMsg msg;
//msg.m_pAuftraege = m_pAuftraege;
//msg.m_pSteinSaetze = m_pSteinSaetze;
//msg.DoModal();
m_pAuftraege->Save();
if (m_pAuftraege->m_bSpeichernOk )
	{
	if((m_nModus == ID_ZUGANG))
		m_pSteinSaetze->m_modified = TRUE;
	else
		m_pSteinSaetze->Save();
	}
else
	{
	AfxMessageBox(Sprache(_T("Daten wurden NICHT gespeichert!")));	
	SetPositionenListe(m_strAktuellerAuftrag);
	}

//CAuftragsBearbeitung::m_ctrlBearbeiten.SetWindowText(strButt);
}
//-----------------------------------------------------------------------------------
// geht nicht
void CAuftragsBearbeitung::OnClose() 
{
CDialog::OnClose();
}
//-----------------------------------------------------------------------------------
void CAuftragsBearbeitung::OnButtonLoeschposition() 
{
CString errMsg;
int posix = m_ctrlPositionen.GetCurSel();
SetComboBox(m_strAktuellerAuftrag); // den letzten offiziellen
int aufix = m_ctrlComboAuftraege.GetCurSel();
if(posix >= 0)
    {
    if(m_strAktuellerAuftrag == m_pAuftraege->Auftrag(aufix).m_strIdent)
        {
        CAuftrag *pCurAuf;
        pCurAuf = &m_pAuftraege->arr[aufix];
        if(!m_strAktuellerAuftrag.CompareNoCase(NAME_ZUGANG)) // Bei bestelleingang wird erst nach Beenigung der Funkt. aus Steinliste gel.
		{	
			int steinix;
			m_pSteinSaetze->FoundAt (pCurAuf->m_Positionen.arr[posix].Nummer(), steinix);
			if (steinix >= 0)
			{
				if(fabs(pCurAuf->Position(posix).Menge1()-m_pSteinSaetze->SteinSatz(steinix).Menge1()) < 0.01)
					m_pSteinSaetze->RemoveAt(steinix);
				else
					m_pSteinSaetze->SubSatz(pCurAuf->m_Positionen.arr[posix]); // Menge wieder aus Steinliste entfernen
			}
		}
        else
        {
            if(m_nModus != ID_BESTELLUNGENEINGANG)
                m_pSteinSaetze->AddSatz(pCurAuf->m_Positionen.arr[posix]); // Wieder in Steinliste zurückschreiben
        }

        if(m_nModus == ID_BESTELLUNGENEINGANG)
            m_pAufLoesch->AddPosition(pCurAuf->Position(posix));

        pCurAuf->m_Positionen.RemoveAt(posix);
        SetPositionenListe(m_strAktuellerAuftrag);
        if(posix >= m_ctrlPositionen.GetCount())
            posix--;
        if(m_ctrlPositionen.GetCount() > 0)
            m_ctrlPositionen.SetCurSel(posix);

        if(m_nModus != ID_BESTELLUNGENEINGANG)  // Bei bestelleingang wird erst nach beeden aus den Auftröägen gelöscht
            m_pAuftraege->Save();
			if (m_nModus == ID_ZUGANG)
				m_pSteinSaetze->m_modified = TRUE;
        }
    }
}
//-----------------------------------------------------------------------------------
void CAuftragsBearbeitung::OnButtonPosanzeigen() 
{
if(!m_pAuftraege->Anzahl())
    return;
int aufix = m_ctrlComboAuftraege.GetCurSel();
if(aufix < 0) return;
if(!m_pAuftraege->Auftrag(aufix).m_Positionen.Anzahl())
    return;
int posix = m_ctrlPositionen.GetCurSel();
if(posix < 0) posix = 0;

CPositionenInfo info(this);
info.m_pSaetze = &(m_pAuftraege->Auftrag(aufix).m_Positionen);
info.m_index = posix;

//info.m_pSatz = 	&(m_pAuftraege->Auftrag(aufix).m_Positionen.SteinSatz(posix));

m_pScanner->setEnableScanner(FALSE);
info.DoModal();
m_pScanner->setEnableScanner(TRUE);
}
//-----------------------------------------------------------------------------------
// Auftrag über Barcode einscannen
BOOL CAuftragsBearbeitung::PreTranslateMessage(MSG* pMsg) 
{
CString errMsg;

//!!!!!!!!!
//return CDialog::PreTranslateMessage(pMsg); //!!! löschen um Auftragseingabe über Scanner zu aktivieren
//!!!!!!!!!

	CString barCode;// = m_pScanner->WaitForDecode(2000,errMsg);
	if(pMsg->message==WM_KEYDOWN)
		if(pMsg->wParam==SCAN_KEY)
			barCode = m_pScanner->WaitForDecode(2000,errMsg);
	if(pMsg->message==WM_SCANDATA){
		TCHAR data[2048];
		wsprintf(data,L"%s",pMsg->wParam);
		barCode=data;
		DEBUGMSG(1, (L"Benutzer: Barcode Daten='%s'\n", barCode));
	}

if(!barCode.IsEmpty())
    {
    PlaySoundScan();
    CString frage;

    int aufLaenge = g_Optionen.LastAufNrSupress(); // Anzahl Zeichen im Auftrag
    if(aufLaenge)
        barCode = barCode.Left(aufLaenge);

    frage = Sprache(_T("Auftrag "),barCode,_T(" hinzufügen?"));

    if((m_pAuftraege->Exist(barCode) >= 0) || AfxMessageBox(frage,MB_YESNO|MB_ICONQUESTION) == IDYES)
        {
        m_strAktuellerAuftrag = barCode;
        m_ctrlComboAuftraege.SetWindowText(m_strAktuellerAuftrag);
        OnButtonAddauftrag();
        }
	}
else
    {
    if(!errMsg.IsEmpty())
        AfxMessageBox(errMsg);
    }

return CDialog::PreTranslateMessage(pMsg);	
}
//-----------------------------------------------------------------------------------
int CAuftragsBearbeitung::FindNumber(const CString& strAuf) const
{
for(int i = 0; i < m_ctrlComboAuftraege.GetCount(); i++)
    {
    CString strNum;
    m_ctrlComboAuftraege.GetLBText(i,strNum);
    if(!strAuf.CompareNoCase(strNum))
        return i;
    }
return -1;
}
//-----------------------------------------------------------------------------------
void CAuftragsBearbeitung::OnLbnSelchangeListPositionen()
{
SetComboBox(m_strAktuellerAuftrag);
}

void CAuftragsBearbeitung::OnCbnSetfocusComboAuftraege()
{
	if (m_nModus == ID_ZUGANG )
		if (m_pAuftraege->Auftrag(0).m_Positionen.Anzahl() == 0)
			OnButtonBearbeiten();
}
