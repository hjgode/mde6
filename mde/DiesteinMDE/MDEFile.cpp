// MDEFile.cpp: implementation of the MDEFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MDEFile::MDEFile() : CFile()
{
}
//--------------------------------------------------------------------
// Komplette Textdatei in String-Array lesen
//--------------------------------------------------------------------
int MDEFile::ReadStringArray(MDEStringArray& strArr)
{
int lang = (int)CFile::GetLength()+2;
char *buffer = new char[lang];
CString cstr;

strArr.RemoveAll();
int l;
while((l = CFile::Read(buffer,lang-1)) > 0)
    {
    *(buffer+l) = 0;
    cstr += buffer;
    }

int start = 0;
int next = 0;
while(1)
    {
    next = cstr.Find(0x0A,start);
    if(next <= start) break;
    strArr.Add(cstr.Mid(start,next-start-1));
    start = next+1;
    }
delete [] buffer;
return strArr.GetCount();
}
//--------------------------------------------------------------------
int MDEFile::ReadSteinSatzArray(CSteinSaetze& strArr)
{
strArr.arr.RemoveAll();
strArr.m_modified = false;

int lang = (int)GetLength()+2;
char *buffer = new char[lang];
if(buffer == 0)
    {
    AlertString(Sprache(_T("Zu wenig Speicherplatz! (Datei lesen)")));
    return 0;
    }

CString cstr(_T("X"),200);

int l;
l = CFile::Read(buffer,lang-1);
int i = 0;
int maxcnt=0;
for(i = 0; i < l; i++)
    {
    if(*(buffer+i) == 0x0A) // Sätze zählen
        maxcnt++;
    }

strArr.arr.SetSize(maxcnt);
int start = 0;
int n = 0;
i = 0;
while(i < l)
    {
    char c = *(buffer+i);
    if(c == 0x0D)
        {
        *(buffer+i) = 0;
        *(buffer+i+1) = 0;
        cstr = buffer+start;
        strArr.arr.SetAtGrow(n,cstr);
        i += 2;
        start = i;
        n++;
        continue;
        }
    i++;
    }
strArr.arr.FreeExtra();
delete[] buffer;
return strArr.Anzahl();
}
//--------------------------------------------------------------------
void MDEFile::WriteString(const CString& str)
{
char *buffer = new char[str.GetLength()+8];
ToBuffer(str,"\r\n",buffer);
Write(buffer,strlen(buffer));
delete buffer;
}
