// Benutzer.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "Benutzer.h"
#include "EigenTabellen.h"

#define DATEI_BENUTZER          _T("Benutzer.txt")

// CBenutzer-Dialogfeld

IMPLEMENT_DYNAMIC(CBenutzer, CDialog)

void CBenutzer::OnOK() 
{ 
	m_pScanner->setEnableScanner(FALSE); //m_scanEnable=FALSE;

   if (!UpdateData(TRUE)) 
   {
      TRACE(_T("UpdateData failed during dialog termination\n"));
      // The UpdateData routine will set focus to correct item
      return;
   }
       EndDialog(IDOK);
   //else
   //    DestroyWindow();
}

CBenutzer::CBenutzer(CWnd* pParent /*=NULL*/)
: CDialog(CBenutzer::IDD, pParent)
{

}
//----------------------------------------------------------------------------------------
CBenutzer::~CBenutzer()
{
	m_pScanner->setEnableScanner(FALSE); //m_scanEnable=FALSE;
}
//----------------------------------------------------------------------------------------
void CBenutzer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_NAME, m_ctrlStaticName);
	DDX_Control(pDX, IDC_STATIC_PASSWORT, m_ctrlStaticPasswort);
	DDX_Control(pDX, IDC_COMBO_NAME, m_ctrlComboName);
	DDX_Control(pDX, IDC_EDIT_PASSWORT, m_ctrlEditPasswort);
}


BEGIN_MESSAGE_MAP(CBenutzer, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_NAME, &CBenutzer::OnCbnSelchangeComboName)
	ON_BN_CLICKED(IDOK, &CBenutzer::OnBnClickedOk)
END_MESSAGE_MAP()


// CBenutzer-Meldungshandler
//----------------------------------------------------------------------------------------
BOOL CBenutzer::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_userTab.Read(FOLDER_DOCU,DATEI_BENUTZER);
	if(!m_userTab.GetCount())
	{
		AfxMessageBox(Sprache(_T("Benutzerdatei ungültig!")));
		OnCancel();
		return TRUE;
	}

	for(int i = 0; i < m_userTab.GetCount(); i++)
		m_ctrlComboName.AddString(m_userTab.GetAt(i).m_key);

	m_ctrlComboName.SetCurSel(0);
	m_ctrlEditPasswort.SetFocus();
	return FALSE;
}
//----------------------------------------------------------------------------------------
void CBenutzer::OnCbnSelchangeComboName()
{
	m_ctrlEditPasswort.SetFocus();
	m_ctrlEditPasswort.SetWindowText(_T(""));
}
//----------------------------------------------------------------------------------------
void CBenutzer::OnBnClickedOk()
{
	int ix = m_ctrlComboName.GetCurSel();
	if(ix < 0)
	{
		OnCancel(); // kann eigentlich nicht sein
		return;
	}
	CString str;
	m_ctrlEditPasswort.GetWindowText(str);
	if(str.CompareNoCase(m_userTab.GetAt(ix).m_bez))
	{
		OnCancel();
		return;
	}

	m_userName = m_userTab.GetAt(ix).m_key;

	CDialog::OnOK();
}
//----------------------------------------------------------------------------------------
// Passwort über Barcode einscannen
BOOL CBenutzer::PreTranslateMessage(MSG* pMsg) 
{
	CString errMsg;

	CString barCode;// = m_pScanner->WaitForDecode(2000,errMsg);
	//if(GetAsyncKeyState(SCAN_KEY) < 0)
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
		int ix = m_ctrlComboName.GetCurSel();
		if(!m_userTab.GetAt(ix).m_bez.CompareNoCase(barCode))
		{
			m_userName = m_userTab.GetAt(ix).m_key;
			CDialog::OnOK();
			return CDialog::PreTranslateMessage(pMsg);
		}
		else
		{
			PlaySoundError();
			m_ctrlEditPasswort.SetWindowText(barCode);
		}
	}

	return CDialog::PreTranslateMessage(pMsg);	
}
