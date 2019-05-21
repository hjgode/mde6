// SaveMsg.cpp : implementation file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CSaveMsg dialog
IMPLEMENT_DYNAMIC(CSaveMsg,CDialog)

CSaveMsg::CSaveMsg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveMsg::IDD, pParent)
{
m_pSteinSaetze = NULL;
}
//-------------------------------------------------------------------------------
void CSaveMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_TEXT, m_ctrlStaticText);
}


BEGIN_MESSAGE_MAP(CSaveMsg, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()

char *ToBuffer(CString str,char *z,char *buffer);
//----------------------------------------------------------------------------------------------
BOOL CSaveMsg::OnInitDialog()
{
CDialog::OnInitDialog();

//MoveWindow(0,0,180,50);
CenterWindow(GetDesktopWindow());	// center to the hpc screen

m_ctrlStaticText.SetWindowText(m_strText);

SetTimer(11,200,NULL);

return TRUE;
}
//----------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
// CSaveMsg message handlers

void CSaveMsg::OnTimer(UINT nIDEvent) 
{
CDialog::OnTimer(nIDEvent);

KillTimer(11);

if(m_pSteinSaetze != NULL)
    {
    int lang = 0;
    for(int i = 0; i < m_pSteinSaetze->Anzahl(); i++)
        {
        lang += m_pSteinSaetze->arr.GetAt(i).m_value.GetLength()+2;
        }
SpeicherAuf3mal();
    //char *buffer = new char[lang+2];
    //if(buffer == 0)
    //    {
    //    if(!SpeicherAuf3mal())
    //        AlertString(Sprache(_T("Zu wenig Speicherplatz (Datei schreiben)!")));
    //    }
    //else    // Lagerbestand schreiben
    //    {
    //    CFile fileSave;
    //    fileSave.Open(m_strFileName,CFile::modeWrite|CFile::modeCreate);
    //    int j = 0;
    //    for(int i = 0; i < m_pSteinSaetze->Anzahl(); i++)
    //        {
    //        int l = m_pSteinSaetze->arr.GetAt(i).m_value.GetLength();
    //        for(int k = 0; k < l; k++)
    //            {
    //            *(buffer+j++) = (char)m_pSteinSaetze->arr.GetAt(i).m_value.GetAt(k);
    //            }
    //        *(buffer+j++) = (char)_T('\r');
    //        *(buffer+j++) = (char)_T('\n');
    //        }
    //        
    //    *(buffer+j) = 0;
    //    fileSave.Write(buffer,strlen(buffer));
    //    fileSave.Close();
    //    delete[] buffer;
    //    }
	}

OnCancel();
}
//-------------------------------------------------------------------------------
bool CSaveMsg::SpeicherAuf3mal()
{
int index[4];
int lang[3];
index[0] = 0;
index[1] = m_pSteinSaetze->Anzahl()/3;
index[2] = (2*m_pSteinSaetze->Anzahl())/3;
index[3] = m_pSteinSaetze->Anzahl();

char *buffer = 0;
int maxlang = 0;
for(int n = 0; n < 3; n++)
    {
    lang[n] = 0;
    for(int i = index[n]; i < index[n+1]; i++)
        {
        lang[n] += m_pSteinSaetze->arr.GetAt(i).m_value.GetLength()+2;
        }
    if(lang[n] > maxlang)
        maxlang = lang[n];
    }
buffer = new char[maxlang+2];
if(buffer == 0)
    return false;

CFile fileSave;
CFileException e;
try
	{
	if(!fileSave.Open(m_strFileName,CFile::modeWrite|CFile::modeCreate,&e))
		{
		CString str;
		str.Format(_T("%s \"%s\": %d"),Sprache(_T("Fehler beim Öffnen von")),m_strFileName,e.m_cause);
		AfxMessageBox(str);
		return false;
		}
	for(int n = 0; n < 3; n++)
		{
		int j = 0;
		for(int i = index[n]; i < index[n+1]; i++)
			{
			int l = m_pSteinSaetze->arr.GetAt(i).m_value.GetLength();
			for(int k = 0; k < l; k++)
				{
				*(buffer+j++) = (char)m_pSteinSaetze->arr.GetAt(i).m_value.GetAt(k);
				}
			*(buffer+j++) = (char)_T('\r');
			*(buffer+j++) = (char)_T('\n');
			}
        
		*(buffer+j) = 0;
		fileSave.Write(buffer,strlen(buffer));
		}
	fileSave.Close();
	delete[] buffer;
	return true;
	}
catch (...)
	{
	fileSave.Close();
	delete[] buffer;
	return false;
	}
}