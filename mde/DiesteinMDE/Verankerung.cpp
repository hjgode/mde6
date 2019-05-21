#include "Stdafx.h"
#include "Verankerung.h"

//------------------------------------------------------------------------
void CVerankerung::operator=(const CVerankerung& v)
{
m_Name = v.m_Name;
m_Hinweis = v.m_Hinweis;
for(int i = 0; i < 4; i++)
m_Preise[i] = v.m_Preise[i];
for(int i = 0; i < MAX_VAZAHL; i++)
    arr[i] = v.arr[i];
}
//------------------------------------------------------------------------
// Aus String Satz herstellen  Name;Preis1;Preis2;Preis3;Preis4;Num1;NUm2;Num3....max Num12
BOOL CVerankerung::SetStr(CString str)
{
str.Trim();
if(str.IsEmpty())
    return FALSE;

char ch = _T(';');
int start = 0;
int next = str.Find(ch,start);
if(next < 0)
    return FALSE;

m_Name = str.Mid(start,next-start);
if(m_Name.IsEmpty())
    return FALSE;
m_Hinweis = NextValue(str,ch,next);
m_Preise[0] = NextValue(str,ch,next);
m_Preise[1] = NextValue(str,ch,next);
m_Preise[2] = NextValue(str,ch,next);
m_Preise[3] = NextValue(str,ch,next);
int n = 0;
while(n < MAX_VAZAHL)
    {
    arr[n] = NextValue(str,ch,next);
    n++;
    }
return TRUE;
}
//--------------------------------------------------------------------------------------
CString CVerankerung::NextValue(const CString& str,char ch,int& next)
{
if(next < 0) return _T("");
int start = next+1;
next = str.Find(ch,start);
if(next < 0)
    {
    return str.Mid(start);
    }
return str.Mid(start,next-start);
}
//--------------------------------------------------------------------------------------
CString CVerankerung::AsString()
{
CString str(m_Name);
str += _T(";"); str += m_Hinweis;
str += _T(";"); str += m_Preise[0];
str += _T(";"); str += m_Preise[1];
str += _T(";"); str += m_Preise[2];
str += _T(";"); str += m_Preise[4];
for(int i = 0; i < MAX_VAZAHL; i++)
    {
    CString str1;
    str1.Format(_T(";%s"),arr[i]);
    str += str1;
    }
return str;
}
//*****************************************************************************************
//*****************************************************************************************
//-----------------------------------------------------------------------------------------
BOOL CVerankerungen::Read()
{
CString pathFileName;
MDEFile inFile;

RemoveAll();

// Auftraege.csv einlesen
pathFileName.Format(_T("%s\\%s"),FOLDER_DOCU,_T("Verankerungen.csv"));
MDEStringArray strarr;
if(!inFile.Open(pathFileName,CFile::modeRead))
    return FALSE;

inFile.ReadStringArray(strarr);
inFile.Close();

CreateFromStrArray(strarr);
return TRUE;
}
//--------------------------------------------------------------------------------------
void CVerankerungen::CreateFromStrArray(MDEStringArray& strarr)
{
CVerankerung v;
for(int i = 0; i < strarr.GetCount(); i++)
    {
    CString str(strarr.GetAt(i));
    str.Trim();
    if(str.IsEmpty())
        continue;
    if(v.SetStr(strarr[i]))
        Add(v);
    }
}
//------------------------------------------------------------------------
BOOL CVerankerungen::ExistName(CString name,int &ix)
{
ix = -1;
for(int i = 0; i < GetCount(); i++)
    {
    if(!name.Compare(GetAt(i).m_Name))
        {
        ix = i;
        return TRUE;
        }
    }
return FALSE;
}
//------------------------------------------------------------------------
BOOL CVerankerungen::FindeSteinNummer(const CString& strNr,CVerankerung& v,int& ix)
{
if(strNr.IsEmpty())
    return FALSE;
for(int i = 0; i < GetCount(); i++)
    {
    for(int j = 0; j < MAX_VAZAHL; j++)
        {
        if(!GetAt(i).arr[j].Compare(strNr))
            {
            v = GetAt(i);
            ix = j;
            return TRUE;
            }
        }
    }
return FALSE;
}
