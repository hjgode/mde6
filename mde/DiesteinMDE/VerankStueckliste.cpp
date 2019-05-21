// VerankStueckliste.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "Verankerung.h"
#include "PreiseVerank.h"
#include "VerankStueckliste.h"


// CVerankStueckliste-Dialogfeld

IMPLEMENT_DYNAMIC(CVerankStueckliste, CDialog)

CVerankStueckliste::CVerankStueckliste(CWnd* pParent /*=NULL*/)
	: CDialog(CVerankStueckliste::IDD, pParent)
{
m_pSteinSaetze = NULL;
m_pCurVerank = NULL;
m_pVerankerungen = NULL;
m_startSteinSatzIx = -1;     // Index des aktuellen Steins in der SteinSatz-Liste
m_zeilen = 0;
}
//---------------------------------------------------------------------------------------
CVerankStueckliste::~CVerankStueckliste()
{
}
//---------------------------------------------------------------------------------------
void CVerankStueckliste::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_SAETZE, m_ctrlListSaetze);
    DDX_Control(pDX, IDC_STATIC_VERANKERUNG, m_ctrlStaticVerankerung);
    DDX_Control(pDX, IDC_STATIC_SAETZE, m_ctrlStaticSaetze);
}
//---------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CVerankStueckliste, CDialog)
    ON_LBN_SELCHANGE(IDC_LIST_SAETZE, &CVerankStueckliste::OnLbnSelchangeListSaetze)
END_MESSAGE_MAP()
//---------------------------------------------------------------------------------------
// CVerankStueckliste-Meldungshandler
/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------------------
BOOL CVerankStueckliste::OnInitDialog()
{
CDialog::OnInitDialog();

m_tabLagerOrte.Read();
m_tabPreislisten.Read();

for(int i = 0; i < MAX_VAZAHL; i++)
    {
    if(m_pCurVerank->SteinNummer(i).IsEmpty())
        continue;
    int ix;
    if(m_pSteinSaetze->FoundAt(m_pCurVerank->SteinNummer(i),ix))
        m_VerankerungsSaetze.Add(m_pSteinSaetze->SteinSatz(ix));
    }
//AlertInt(m_VerankerungsSaetze.Anzahl());

CString str;
m_ctrlStaticVerankerung.GetWindowText(str);  // Anzeige der Verankerung
str.Format(_T("%s %s"),Sprache(str),m_pCurVerank->m_Name);
m_ctrlStaticVerankerung.SetWindowText(str);
m_ctrlStaticSaetze.GetWindowText(str);  // Anzeige der Verankerung
str.Format(_T("%d %s"),m_VerankerungsSaetze.Anzahl(),Sprache(str));
m_ctrlStaticSaetze.SetWindowText(str);

// 5 Zeilen pro satz

for(int i = 0; i < m_VerankerungsSaetze.Anzahl(); i++)
    {
    SSatz ss(m_VerankerungsSaetze.SteinSatz(i));
//    AlertString(ss.m_Nummer);
    CString strh;
    if(!ss.m_Hinweis.IsEmpty())
        strh = _T("H");
    CString str;
    str.Format(_T("%-10s %s"),ss.m_Nummer,strh);
    m_ctrlListSaetze.AddString(str);
    m_ctrlListSaetze.AddString(ss.m_Artikel);
    str.Format(_T("%s %s"),ss.m_Lager,m_tabLagerOrte.GetItemByKey(ss.m_Lager).m_bez);
    m_ctrlListSaetze.AddString(str);

    CString strpr;
    CString strpr1;
    if(m_tabPreislisten.GetCount())  // von 10 möglichen Preislisten können max. 4 aktiviert sein
        {
        int j = 0;
        int k = 0;
        while(j < min(10,m_tabPreislisten.GetSize()))
            {
            if(g_Optionen.PreislisteEnabled(j))
                {
                str.Format(_T("%s: %s %s"),
                m_tabPreislisten.GetAt(j).m_value1,ss.m_GR_Preis[j],m_tabPreislisten.GetAt(j).m_value2);
                if(k < 2)
                    {
                    strpr += str;
                    strpr += _T(" ");
                    }
                else
                    {
                    strpr1 += str;
                    strpr1 += _T(" ");
                    }
                k++;
                if(k > 3) break;
                }
            j++;
            }
        }
    m_zeilen = 4;
    strpr.Trim();
    strpr1.Trim();
    if(!strpr.IsEmpty())
        {
        m_ctrlListSaetze.AddString(strpr);
        m_zeilen = 5;
        }
    if(!strpr1.IsEmpty())
        {
        m_ctrlListSaetze.AddString(strpr1);
        m_zeilen = 6;
        }
    m_ctrlListSaetze.AddString(_T(""));
    }
UpdateData(FALSE);
return TRUE;  // return TRUE  unless you set the focus to a control
}
//---------------------------------------------------------------------------------------
void CVerankStueckliste::OnBnClickedButtonDetails()
{
CPreiseVerank dlg;

dlg.m_pSteinSaetze = m_pSteinSaetze;
dlg.m_pCurVerank = m_pCurVerank;
dlg.m_startSteinSatzIx = m_startSteinSatzIx;

dlg.DoModal();	

}
//---------------------------------------------------------------------------------------
BOOL CVerankStueckliste::PreTranslateMessage(MSG* pMsg) 
{
CString errMsg;

	CString barCode;// = m_pScanner->WaitForDecode(2000,errMsg);
	//if(GetAsyncKeyState(SCAN_KEY) < 0)
	if(pMsg->message==WM_KEYDOWN)
		if(pMsg->wParam==SCAN_KEY)
			{ barCode = m_pScanner->WaitForDecode(2000,errMsg); return TRUE; }
	if(pMsg->message==WM_SCANDATA){
		TCHAR data[2048];
		wsprintf(data,L"%s",pMsg->wParam);
		barCode=data;
		DEBUGMSG(1, (L"Benutzer: Barcode Daten='%s'\n", barCode));
	}

if(!barCode.IsEmpty())
    {
    m_backSteinNummer = barCode;
    CDialog::OnOK();
	}
else
    {
    if(!errMsg.IsEmpty())
        AfxMessageBox(errMsg);
    }
return CDialog::PreTranslateMessage(pMsg);
}
//---------------------------------------------------------------------------------------
void CVerankStueckliste::OnLbnSelchangeListSaetze()
{
int ix = m_ctrlListSaetze.GetCurSel();
ix = (int)(ix/m_zeilen);

CPreiseVerank dlg;

dlg.m_pSteinSaetze = m_pSteinSaetze;
dlg.m_pCurVerank = m_pCurVerank;
dlg.m_pScanner = m_pScanner;
int isx;
if(m_pSteinSaetze->FoundAt(m_pCurVerank->arr[ix],isx))
    dlg.m_startSteinSatzIx = isx;

dlg.DoModal();
if(!dlg.m_backSteinNummer.IsEmpty())
    {
    m_backSteinNummer = dlg.m_backSteinNummer;
    CDialog::OnOK();
    }
}
