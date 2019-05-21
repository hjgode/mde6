// SteinbruchStart.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "SteinbruchEmail.h"
#include "Steinbruch.h"
#include ".\VersionsConfig\_VersionsConfig.h"

//-----------------------------------------------------------------------------
int SendMailEntry(const CString& strSubject,const CString& strBody,const CString& attachName,const CString& attachString,
              const CString& strTo,const CString& strCC,const CString& strBcc);
//-----------------------------------------------------------------------------
void GetDirectoryContents(const CString& dir,const CString& ext,MDEStringArray& filearr)
{
WIN32_FIND_DATA findData;
HANDLE fileHandle;
CString dir1 = dir + CString(_T("\\*.")) + ext;
fileHandle = FindFirstFile(dir1, &findData);
if (fileHandle != INVALID_HANDLE_VALUE)
    {
    if(!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        filearr.Add(findData.cFileName);
    while(FindNextFile(fileHandle, &findData))
        {
        if(!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            filearr.Add(findData.cFileName);
        }
    }
if (fileHandle != INVALID_HANDLE_VALUE )
    FindClose(fileHandle);
}
//-----------------------------------------------------------------------------

// CSteinbruchEmail-Dialogfeld

IMPLEMENT_DYNAMIC(CSteinbruchEmail, CDialog)

CSteinbruchEmail::CSteinbruchEmail(CWnd* pParent /*=NULL*/)
	: CDialog(CSteinbruchEmail::IDD, pParent)
{

}

CSteinbruchEmail::~CSteinbruchEmail()
{
}

void CSteinbruchEmail::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_RECEPIENT, m_ctrlStaticEmpfaenger);
    DDX_Control(pDX, IDC_STATIC_BETREFF, m_ctrlStaticBetreff);
    DDX_Control(pDX, IDC_STATIC_TEXT, m_ctrlStaticText);
    DDX_Control(pDX, IDC_STATIC_SICHERUNG, m_ctrlStaticSicherung);
    DDX_Control(pDX, IDC_COMBO_RECEPIENT, m_ctrlComboEmpfaenger);
    DDX_Control(pDX, IDC_EDIT_BETREFF, m_ctrlEditBetreff);
    DDX_Control(pDX, IDC_EDIT_TEXT, m_ctrlEditText);
    DDX_Control(pDX, IDC_BUTTON_SEND, m_ctrlButtonSenden);
    DDX_Control(pDX, IDC_COMBO_SICHERUNG, m_ctrlComboSicherung);
    DDX_Control(pDX, IDC_BUTTON_SENDSICH, m_ctrlButtonSendSicherung);
    DDX_Control(pDX, IDC_STATIC_DATEINAME, m_ctrlStaticDateiname);
    DDX_Control(pDX, IDC_STATIC_BLOCKZAHL, m_ctrlStaticBlockAnzahl);
    DDX_Control(pDX, IDC_STATIC_BLOCKZAHL2, m_ctrlStaticBlockzahl2);
    DDX_Control(pDX, IDC_STATIC_EMAIL, m_ctrlStaticEmail);
}


BEGIN_MESSAGE_MAP(CSteinbruchEmail, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_SEND, &CSteinbruchEmail::OnBnClickedButtonSend)
    ON_CBN_SELCHANGE(IDC_COMBO_SICHERUNG, &CSteinbruchEmail::OnCbnSelchangeComboSicherung)
    ON_BN_CLICKED(IDC_BUTTON_SENDSICH, &CSteinbruchEmail::OnBnClickedButtonSendsich)
    ON_EN_KILLFOCUS(IDC_EDIT_BETREFF, &CSteinbruchEmail::OnEnKillfocusEditBetreff)
    ON_CBN_SELCHANGE(IDC_COMBO_RECEPIENT, &CSteinbruchEmail::OnCbnSelchangeComboRecepient)
END_MESSAGE_MAP()


// CSteinbruchEmail-Meldungshandler
//-----------------------------------------------------------------------------
BOOL CSteinbruchEmail::OnInitDialog() 
{
	CDialog::OnInitDialog();

TranslateStatic(m_ctrlStaticEmail);
TranslateStatic(m_ctrlStaticEmpfaenger);
TranslateStatic(m_ctrlStaticBetreff);
TranslateStatic(m_ctrlStaticText);
TranslateStatic(m_ctrlStaticSicherung);
TranslateButton(m_ctrlButtonSenden);
TranslateButton(m_ctrlButtonSendSicherung);

m_tabProgrammStatus.Read();

if((WIN_VERSION < 5) || (m_pAuftraege->Auftrag(0).m_Positionen.Anzahl() == 0))
    m_ctrlButtonSenden.EnableWindow(FALSE);

for(int i = 0; i < 10; i++)
    {
    CString key;
    key.Format(_T("EmailEmpfaenger%d"),i+1);
    int ix = m_tabProgrammStatus.GetIndexByKey(key);
    if(ix >= 0)
        m_arrEmpfaenger.Add(m_tabProgrammStatus.GetAt(ix).m_value1);
    }
SetComboEmpfaenger();

int ix = m_tabProgrammStatus.GetIndexByKey(_T("LetzterBetreff"));
if(ix >= 0)
    {
    m_ctrlEditBetreff.SetWindowText(m_tabProgrammStatus.GetAt(ix).m_value1);
    }

UpdateDateinameUndAnzahl();

SetComboSicherung();


return FALSE;  // return TRUE unless you set the focus to a control
}
//-----------------------------------------------------------------------------
void CSteinbruchEmail::SetComboEmpfaenger()
{
int lix = m_tabProgrammStatus.GetIndexByKey(_T("LetzterEmailEmpfaenger"));
int cursel = -1;
for(int i = 0; i < m_arrEmpfaenger.GetCount(); i++)
    {
    m_ctrlComboEmpfaenger.AddString(m_arrEmpfaenger.GetAt(i));
    if(lix >= 0)
        {
        if(!m_tabProgrammStatus.GetAt(lix).m_value1.CompareNoCase(m_arrEmpfaenger.GetAt(i)))
            cursel = i;
        }
    }
cursel = max(0,cursel);
m_ctrlComboEmpfaenger.SetCurSel(cursel);
}
//-----------------------------------------------------------------------------
void CSteinbruchEmail::SetComboSicherung()
{
CString sichdir;
sichdir.Format(_T("%s\\%s"),FOLDER_DOCU,FOLDER_BLOCKSICH);

MDEStringArray arr;
GetDirectoryContents(sichdir,_T("csv"),arr);  // Alle Dateien aus Sicherungsverzeichnis

arr.Sort(FALSE,TRUE);

m_ctrlComboSicherung.ResetContent();
for(int i = 0; i < arr.GetCount(); i++)
    m_ctrlComboSicherung.AddString(arr.GetAt(i));

int anz = 0;
if(arr.GetCount())
    {
    m_ctrlComboSicherung.SetCurSel(0);

    MDEFile file;
    CString pathfile;
    pathfile.Format(_T("%s\\%s"),sichdir,arr.GetAt(0));
    if(file.Open(pathfile,CFile::modeRead))
        {
        MDEStringArray strarr;
        file.ReadStringArray(strarr);
        file.Close();
        anz = strarr.GetCount();
        }
    }
CString str;
str.Format(_T("%d %s"),anz,Sprache(_T("Blöcke")));
m_ctrlStaticBlockzahl2.SetWindowTextW(str);
}
////-----------------------------------------------------------------------------
//void CSteinbruchEmail::OnBnClickedButtonBlockerfassung()
//{
//CSteinbruch steinbruch;
//
//steinbruch.m_pAuftraege = m_pAuftraege;
//
//steinbruch.m_pScanner = m_pScanner;
//
//m_pScanner->setEnableScanner(TRUE);
//// Rohbloecke erfassen
//steinbruch.DoModal();	
//
//m_pScanner->setEnableScanner(FALSE);
//
//if((WIN_VERSION > 5) && (m_pAuftraege->Auftrag(0).m_Positionen.Anzahl() > 0))
//    m_ctrlButtonSenden.EnableWindow();
//
////if(m_pAuftraege->Auftrag(0).m_Positionen.Anzahl() > 0)
////    m_ctrlButtonSenden.EnableWindow();
//
//
//UpdateDateinameUndAnzahl();
//}
//-----------------------------------------------------------------------------
void CSteinbruchEmail::OnBnClickedButtonSend()
{


CString betreff;
m_ctrlEditBetreff.GetWindowText(betreff);
CString text;
m_ctrlEditText.GetWindowText(text);
int cursel = m_ctrlComboEmpfaenger.GetCurSel();
if(cursel < 0)
    return;

CString pathFileName;
pathFileName.Format(_T("%s\\%s"),FOLDER_DOCU,DATEI_BLOECKE);
MDEFile file;

file.Open(pathFileName,CFile::modeRead);
int lang = (int)file.GetLength()+2;
char *buffer = new char[lang];
unsigned int l = file.Read(buffer,lang-2);
*(buffer+l) = 0;
CFileStatus fstatus;
file.GetStatus(pathFileName,fstatus);
file.Close();

CString cstr(buffer);

// Kopie mit Datum und Uhrzeit erstellen
CString sichdir;
sichdir.Format(_T("%s\\%s"),FOLDER_DOCU,FOLDER_BLOCKSICH);
CreateDirectory(sichdir,0);

MDEFile bakfile;
CString bakFileName;
bakFileName.Format(_T("%s\\%s"),sichdir,m_dateiNameZumSenden);

if(!bakfile.Open(bakFileName,CFile::modeWrite|CFile::modeCreate))
    {
    AlertString(Sprache(_T("Fehler bei Dateisicherung")));
    delete [] buffer;
    return;
    }
bakfile.Write(buffer,l);
bakfile.Close();

CFile::Remove(pathFileName);    // Blöcke.csv löschen
while(m_pAuftraege->Auftrag(0).m_Positionen.Anzahl())
    m_pAuftraege->Auftrag(0).m_Positionen.RemoveAt(0);
// Die Daten in der KorrekturDatei müssen auch gelöscht werden
CString pathFileNameKorr;
pathFileNameKorr.Format(_T("%s\\%s%s"),FOLDER_DOCU,NAME_BLOCKAENDERUNGEN,_T(".csv"));
CFile::Remove(pathFileNameKorr);    
while(m_pAuftragBlockKorr->Auftrag(0).m_Positionen.Anzahl())
    m_pAuftragBlockKorr->Auftrag(0).m_Positionen.RemoveAt(0);


delete [] buffer;

SendMailEntry(betreff,text,m_dateiNameZumSenden,cstr,m_arrEmpfaenger.GetAt(cursel),_T(""),_T(""));;

UpdateDateinameUndAnzahl();

SetComboSicherung();
}
//-----------------------------------------------------------------------------
void CSteinbruchEmail::UpdateDateinameUndAnzahl()
{

int anzahl = m_pAuftraege->Auftrag(0).m_Positionen.Anzahl();
CString str;
str.Format(_T("%d %s"),anzahl,Sprache(_T("Blöcke")));
m_ctrlStaticBlockAnzahl.SetWindowText(str);

CreateDateinameZumSenden();
if(anzahl)
    m_ctrlStaticDateiname.SetWindowText(m_dateiNameZumSenden);
else
    {
    m_ctrlStaticDateiname.SetWindowText(_T(""));
    m_ctrlButtonSenden.EnableWindow(FALSE);
    }
}
//-------------------------------------------------------------------------
// Aus Bloecke.csv Dateinamen, bestehend aus Bloecke%Y%m%d%H%M%S.csv machen
// Zeit ist letzte Änderung der Datei
void CSteinbruchEmail::CreateDateinameZumSenden()
{
m_dateiNameZumSenden.Empty();

CString pathFileName;
pathFileName.Format(_T("%s\\%s"),FOLDER_DOCU,DATEI_BLOECKE);
MDEFile file;
if(file.Open(pathFileName,CFile::modeRead))
    {
    CFileStatus fstatus;
    file.GetStatus(pathFileName,fstatus);
    file.Close();

    CTime atime(fstatus.m_mtime);   // letzter Schreibzugriff

    CString dname = DATEI_BLOECKE;
    CString name = dname.Left(dname.GetLength()-4);
    CString ext = dname.Right(3);
    m_dateiNameZumSenden.Format(_T("%s%02d%02d%02d%02d%02d%02d.%s"),name,atime.GetYear()-2000,
                                atime.GetMonth(),atime.GetDay(),atime.GetHour(),atime.GetMinute(),
                                atime.GetSecond(),ext);
    }
}
//-------------------------------------------------------------------------
void CSteinbruchEmail::OnCbnSelchangeComboSicherung()
{
int ix = m_ctrlComboSicherung.GetCurSel();

CString sichdir;
sichdir.Format(_T("%s\\%s"),FOLDER_DOCU,FOLDER_BLOCKSICH);

int anz = 0;
CString name;
m_ctrlComboSicherung.GetWindowText(name);

MDEFile file;
CString pathfile;
pathfile.Format(_T("%s\\%s"),sichdir,name);
if(file.Open(pathfile,CFile::modeRead))
    {
    MDEStringArray strarr;
    file.ReadStringArray(strarr);
    file.Close();
    anz = strarr.GetCount();
    }
CString str;
str.Format(_T("%d %s"),anz,Sprache(_T("Blöcke")));
m_ctrlStaticBlockzahl2.SetWindowTextW(str);

m_ctrlButtonSendSicherung.EnableWindow();

}
//-------------------------------------------------------------------------
void CSteinbruchEmail::OnBnClickedButtonSendsich()
{
CString betreff;
m_ctrlEditBetreff.GetWindowText(betreff);
CString text;
m_ctrlEditText.GetWindowText(text);

CString name;
m_ctrlComboSicherung.GetWindowText(name);

CString sichdir;
sichdir.Format(_T("%s\\%s"),FOLDER_DOCU,FOLDER_BLOCKSICH);
CString pathfile;
pathfile.Format(_T("%s\\%s"),sichdir,name);

MDEFile file;
file.Open(pathfile,CFile::modeRead);
int lang = (int)file.GetLength()+2;
char *buffer = new char[lang];
unsigned int l = file.Read(buffer,lang-1);
*(buffer+l) = 0;
file.Close();
CString cstr(buffer);
delete[] buffer;

//  ch 02.11.2016    cstr = _T('Hallo Claudia' );

int cursel = m_ctrlComboEmpfaenger.GetCurSel();

SendMailEntry(betreff,text,name,cstr,m_arrEmpfaenger.GetAt(cursel),_T(""),_T(""));

m_ctrlButtonSendSicherung.EnableWindow(FALSE);
}//-------------------------------------------------------------------------
void CSteinbruchEmail::OnEnKillfocusEditBetreff()
{
CString betreff;
m_ctrlEditBetreff.GetWindowText(betreff);
int ix = m_tabProgrammStatus.GetIndexByKey(_T("LetzterBetreff"));
if(ix >= 0)
    {
    C3String str3(m_tabProgrammStatus.GetAt(ix));
    str3.m_value1 = betreff;
    m_tabProgrammStatus.SetAt(ix,str3);
    }
else
    {
    C3String str3;
    str3.m_key = _T("LetzterBetreff");
    str3.m_value1 = betreff;
    m_tabProgrammStatus.Add(str3);
    }
m_tabProgrammStatus.Save();
}
//-------------------------------------------------------------------------
void CSteinbruchEmail::OnCbnSelchangeComboRecepient()
{
int cursel = m_ctrlComboEmpfaenger.GetCurSel();
C3String str3;
str3.m_key = _T("LetzterEmailEmpfaenger");
str3.m_value1 = m_arrEmpfaenger.GetAt(cursel);

int lix = m_tabProgrammStatus.GetIndexByKey(str3.m_key);
if(lix < 0)
    m_tabProgrammStatus.Add(str3);
else
    m_tabProgrammStatus.SetAt(lix,str3);
m_tabProgrammStatus.Save();

}
