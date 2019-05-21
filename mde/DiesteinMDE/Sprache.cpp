// Sprache.cpp: implementation of the CSprache class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------------------
CSprache::CSprache()
{
m_pathFileName.Format(_T("%s\\%s"),FOLDER_DOCU,DATEI_SPRACHE);
m_germanKey = _T("D  ");
}
//-----------------------------------------------------------------------------------------
void CSprache::Reset()
{
m_arrGerman.RemoveAll();
m_arrStrange.RemoveAll();
}
//-----------------------------------------------------------------------------------------
// Dateiname mit Erweiterung
// Erstellt 2 StringArrays mit je deutschen und fremdsprachigen Strings
// Wird keine Übersetzung gefunden, wird der deusche String in der Fremdsprache eingetragen
BOOL CSprache::Read()
{
m_arrGerman.RemoveAll();
m_arrStrange.RemoveAll();

MDEFile inFile;
MDEStringArray arrAll;

if(inFile.Open(m_pathFileName,CFile::modeRead))
    {
    inFile.ReadStringArray(arrAll);
    inFile.Close();
    }
else
    {
    CString str;
    str.Format(_T("Datei %s konnte nicht geöffnet werden!"),m_pathFileName); // nicht übersetzten(rekursiv)
    AfxMessageBox(str);
    return FALSE;
    }
// Spracheinstellung aus Sprachkopf (1.Zeile Fremdspr., 2. Zeile Defaultsprache)
if(arrAll.GetCount() < 2)
    return FALSE;
m_strangeKey = arrAll.GetAt(0);
while(m_strangeKey.GetLength() < 3)
    m_strangeKey += _T(" ");
m_strangeKey = m_strangeKey.Left(3);
if(!m_strangeKey.Compare(m_germanKey))
    return FALSE;

m_defaultKey = arrAll.GetAt(1);
while(m_defaultKey.GetLength() < 3)
    m_defaultKey += _T(" ");
m_defaultKey = m_defaultKey.Left(3);

for(int i = 1; i < arrAll.GetCount(); i++)
    {
    if(!m_germanKey.Compare(arrAll.GetAt(i).Left(3)))
        {
        m_arrGerman.Add(arrAll.GetAt(i).Mid(3));
        m_arrStrange.Add(arrAll.GetAt(i).Mid(3));
        int lastIx = m_arrGerman.GetCount()-1;
        BOOL foundStrange = FALSE;
        BOOL foundDefault = FALSE;
        CString strDefault;
        while(i < (arrAll.GetCount()-1))
            {
            i++;
            if(!m_germanKey.Compare(arrAll.GetAt(i).Left(3))) // Nächster Text, keine Übersetzung gefunden
                {
                i--;
                break;
                }
            if(!m_strangeKey.Compare(arrAll.GetAt(i).Left(3))) // Übers. gefunden
                {
                m_arrStrange.SetAt(lastIx,arrAll.GetAt(i).Mid(3));
                foundStrange = TRUE;
                break;
                }
            if(m_defaultKey.IsEmpty())  // wenn kein default definiert, weiter
                break;
            else
                {
                if(!m_defaultKey.Compare(arrAll.GetAt(i).Left(3))) // Default Übers. gefunden
                    {
                    strDefault = arrAll.GetAt(i).Mid(3);
                    foundDefault = TRUE;    // Weiter nach strange suchen
                    }
                }
            }
        if(foundDefault && !foundStrange)
            m_arrStrange.SetAt(lastIx,strDefault);
        }
    }
return TRUE;
}
//-----------------------------------------------------------------------------------------
void CSprache::Debug(int i) const
{
if(i < m_arrGerman.GetCount())
    {
    CString str;
    str.Format(_T("%s\n%s"),m_arrGerman.GetAt(i),m_arrStrange.GetAt(i));
    AfxMessageBox(str);
    }
}

//-----------------------------------------------------------------------------------------
// Nicht zu übersetzende Zeichen am Anfang
BOOL CSprache::BorderSignLeft(TCHAR sign)
{
if(sign == _T('\n')) return TRUE;
if(sign == _T('\r')) return TRUE;
return FALSE;
}
//-----------------------------------------------------------------------------------------
// Nicht zu übersetzende Zeichen am Ende: blank
BOOL CSprache::BorderSignRight(TCHAR sign)
{
if(sign == _T(' ')) return TRUE;
if(sign == _T(':')) return TRUE;
if(sign == _T('\n')) return TRUE;
if(sign == _T('\r')) return TRUE;
return FALSE;
}
//-----------------------------------------------------------------------------------------
CString CSprache::TranslateSub(const CString& german)
{
if(!m_arrGerman.GetCount()) return german;  // Hier kommen alle vorbei

for(int i = 0; i < m_arrGerman.GetCount(); i++)
    {
    if(!german.Compare(m_arrGerman.GetAt(i)))
        return m_arrStrange.GetAt(i);
    }

// --- Wenn String nicht existiert, eintragen
MDEFile file;
if(!file.Open(m_pathFileName,CFile::modeReadWrite))
    {
/*
    CString str;
    str.Format(_T("Datei %s konnte nicht geöffnet werden!"),m_pathFileName);
    AfxMessageBox(str);
*/
    return german;
    }

file.SeekToEnd();

CString str(m_germanKey);
str += german;

file.WriteString(_T(""));
file.WriteString(str);

file.Close();

// ---Zum eingelesenen Array hinzunehmen
m_arrGerman.Add(german);
m_arrStrange.Add(german);

return german;
}
//-----------------------------------------------------------------------------------------
// Einzelstring, Sonderzeichen am Anfang und Ende werden vor dem Ubersetzen entfernt
CString CSprache::Translate(const CString &german)
{
int i = 0;
while((i < german.GetLength()) && BorderSignLeft(german.GetAt(i))) // Satzzeichen vor dem String
    i++;
CString strAnf = german.Left(i);

int j = german.GetLength() - 1;
while((j > 0) && BorderSignRight(german.GetAt(j)))
    j--;
CString strEnd = german.Mid(j+1);

if((j-i+1) < 2) // Weniger als 2 zeichen zum Übersetzten
    return german;

CString trans = TranslateSub(german.Mid(i,j-i+1));
CString strRet = strAnf;
strRet += trans;
strRet += strEnd;

return strRet;
}
//-----------------------------------------------------------------------------------------
// Text mit keys
CString CSprache::TranslateSK(const CString &german,const CString& keys,CString& keyRet)
{
CString str;
str.Format(_T("%s\\%s"),german,keys);

str = TranslateSub(str);

int found = str.Find(_T("\\"),0);
if(found >= 0)
    {
    keyRet = str.Mid(found+1);
    return str.Left(found);
    }
// Sollte eigentlich nicht sein, dann ist in der Übersetzung ein Fehler (\ fehlt), deutsch wird zurückgegeben

keyRet = keys;
return german;
}
//-----------------------------------------------------------------------------------------
// String mit Textkonstante dazwischen
CString CSprache::Translate(const CString &german1,const CString& c1,const CString& german2)
{
CString str;
str.Format(_T("%s\\%s"),german1,german2);

str = TranslateSub(str);

CString strRet;
int found = str.Find(_T("\\"),0);
if(found >= 0)
    {
    strRet.Format(_T("%s%s%s"),str.Left(found),c1,str.Mid(found+1));
    }
else    // Sollte eigentlich nicht sein, dann ist in der Übersetzung ein Fehler (\ fehlt), deutsch wird zurückgegeben
    {
    strRet.Format(_T("%s%s%s"),german1,c1,german2);
    }
return strRet;
}
//-----------------------------------------------------------------------------------------
// String mit Zahl dazwischen
CString CSprache::Translate(const CString &german1,int zahl,const CString& german2)
{
CString str;
str.Format(_T("%d"),zahl);
return Translate(german1,str,german2);
}
//-----------------------------------------------------------------------------------------
// String mit 2 Textkonstante dazwischen
CString CSprache::Translate(const CString &german1,const CString& c1,const CString& german2,
                            const CString& c2,const CString& german3)
{
CString str;
str.Format(_T("%s\\%s\\%s"),german1,german2,german3);

str = TranslateSub(str);

CString strRet;
int start = 0;
int found1 = str.Find(_T("\\"),start);
if(found1 >= 0)
    {
    start = found1+1;
    int found2 = str.Find(_T("\\"),start);
    if(found2 >= 0)
        {
        strRet.Format(_T("%s%s%s%s%s"),str.Left(found1),c1,str.Mid(found1+1,found2-found1),c2,str.Mid(found2+1));
        return strRet;
        }
    }
// Sollte eigentlich nicht sein, dann ist in der Übersetzung ein Fehler (\ fehlt), deutsch wird zurückgegeben
strRet.Format(_T("%s%s%s%s%s"),german1,c1,german2,c2,german3);
return strRet;
}
//-----------------------------------------------------------------------------------------
// String mit 2 Zahlen dazwischen
CString CSprache::Translate(const CString &german1,int zahl1,const CString& german2,
                            int zahl2,const CString& german3)
{
CString str1,str2;
str1.Format(_T("%d"),zahl1);
str2.Format(_T("%d"),zahl2);

return Translate(german1,str1,german2,str2,german3);

}
