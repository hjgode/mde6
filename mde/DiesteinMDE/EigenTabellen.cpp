
#include "stdafx.h"

//****************************************************************************
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
C2String& C2String::Set(const CString& strkey,const CString& strbez)
{
m_key = strkey;
m_bez = strbez;
return *this;
}
//---------------------------------------------------------------------------
void C2String::operator=(const C2String& s2)
{
m_key = s2.m_key;
m_bez = s2.m_bez;
}
//-----------------------------------------------------------------------------------------
void C2String::Reset()
{
m_key.Empty();
m_bez.Empty();
}
//-----------------------------------------------------------------------------------------
CString C2String::GruppenKey() const     // Erster Teil von key
{
CString str;
int ix = m_key.Find(_T(" "),0);
if(ix > 0)
    {
    str = m_key.Left(ix);
    str.TrimLeft();
    str.TrimRight();
    }
return str;
}
//-----------------------------------------------------------------------------------------
CString C2String::Key2() const           // Zweiter Teil von key
{
CString str;
int ix = m_key.Find(_T(" "),0);
if(ix > 0)
    {
    str = m_key.Mid(ix+1);
    str.TrimLeft();
    str.TrimRight();
    }
return str;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// C3String
//---------------------------------------------------------------------------
C3String& C3String::Set(const CString& strkey,const CString& strval1,const CString& strval2)
{
m_key = strkey;
m_value1 = strval1;
m_value2 = strval2;
return *this;
}
//---------------------------------------------------------------------------
void C3String::operator=(const C3String& s3)
{
m_key = s3.m_key;
m_value1 = s3.m_value1;
m_value2 = s3.m_value2;
}
//---------------------------------------------------------------------------
void C3String::Reset()
{
m_key.Empty();
m_value1.Empty();
m_value2.Empty();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// C4String
//---------------------------------------------------------------------------
C4String& C4String::Set(const CString& strkey,const CString& strval1,const CString& strval2,const CString& strval3)
{
m_key = strkey;
m_value1 = strval1;
m_value2 = strval2;
m_value3 = strval3;
return *this;
}
//---------------------------------------------------------------------------
void C4String::operator=(const C4String& s4)
{
m_key = s4.m_key;
m_value1 = s4.m_value1;
m_value2 = s4.m_value2;
m_value3 = s4.m_value3;
}
//---------------------------------------------------------------------------
void C4String::Reset()
{
m_key.Empty();
m_value1.Empty();
m_value2.Empty();
m_value3.Empty();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
C2StringTabelle::C2StringTabelle()
{
m_curSelected = 0;
}
//-----------------------------------------------------------------------------------------
void C2StringTabelle::operator=(const C2StringTabelle& s2)
{
Reset();
m_curSelected = s2.m_curSelected;
for(int i = 0; i < s2.GetSize(); i++)
    {
    Add(s2.GetAt(i));
    }
}
//-----------------------------------------------------------------------------------------
void C2StringTabelle::Reset()
{
m_curSelected = 0;
RemoveAll();
}
//-----------------------------------------------------------------------------------------
int C2StringTabelle::GetIndexByKey(const TCHAR *key) const
{
for(int i = 0; i < GetSize(); i++)
    {
    if(!GetAt(i).m_key.CompareNoCase(key))
        return i;
    }
return -1;
}
//-----------------------------------------------------------------------------------------
C2String C2StringTabelle::GetItemByKey(const TCHAR *key) const
{
int index = GetIndexByKey(key);
if(index >= 0)
    return GetAt(index);
C2String s;
return s;
}
//-----------------------------------------------------------------------------------------
int C2StringTabelle::GetIndexByValue(const TCHAR *value,bool compareCase) const
{
int i;
if(compareCase)
    {
    for(i = 0; i < GetSize(); i++)
        {
        if(!GetAt(i).m_bez.Compare(value))
            return i;
        }
    }
else
    {
    for(i = 0; i < GetSize(); i++)
        {
        if(!GetAt(i).m_bez.CompareNoCase(value))
            return i;
        }
    }
return -1;
}
//-----------------------------------------------------------------------------------------
C2String C2StringTabelle::GetItemByValue(const TCHAR *value,bool compareCase) const
{
int index = GetIndexByValue(value,compareCase);
if(index >= 0)
    return GetAt(index);
C2String s;
return s;
}
//-----------------------------------------------------------------------------------------
void C2StringTabelle::SetCombo(CComboBox& ctrlComboBox,CString& strCombo)
{
ctrlComboBox.ResetContent();
for(int i = 0; i < GetSize(); i++)
    ctrlComboBox.AddString(GetAt(i).m_bez);

if(m_curSelected >= GetSize())
     m_curSelected = GetSize()-1;
if(m_curSelected < 0)
    {
    strCombo = _T("");
    return;
    }
/////
ctrlComboBox.SetCurSel(m_curSelected);
strCombo = GetAt(m_curSelected).m_bez;
}
//-----------------------------------------------------------------------------------------
void C2StringTabelle::SetComboKey2AndBez(CComboBox& ctrlComboBox,CString& strRet)
{
ctrlComboBox.ResetContent();
if(GetSize() == 0)
    return;
for(int i = 0; i < GetSize(); i++)
    ctrlComboBox.AddString(GetAt(i).Key2() + _T(" ") + GetAt(i).m_bez);

if(m_curSelected >= GetSize())
     m_curSelected = -1;

if(m_curSelected < 0)
    {
    ctrlComboBox.SetCurSel(0);
    strRet = GetAt(0).Key2() + _T(" ") + GetAt(0).m_bez;
    }
else
    {
    ctrlComboBox.SetCurSel(m_curSelected);
    strRet = GetAt(m_curSelected).Key2() + _T(" ") + GetAt(m_curSelected).m_bez;
    }
}
//-----------------------------------------------------------------------------------------
BOOL C2StringTabelle::Read(const TCHAR *folder,const TCHAR *dateiname)
{
MDEFile inFile;
MDEStringArray arrAll;

CString pathFileName;
pathFileName.Format(_T("%s\\%s"),folder,dateiname);

if(inFile.Open(pathFileName,CFile::modeRead))
    {
    inFile.ReadStringArray(arrAll);
    inFile.Close();
    }
else
    {
    CString str;
    str = Sprache(_T("Datei "),dateiname,_T(" konnte nicht geöffnet werden!"));
    AfxMessageBox(str);
    return FALSE;
    }

Reset();

C2String satz;
int i = 0;
while(i < (arrAll.GetCount() - 1))
    {
    satz.m_key = arrAll.GetAt(i);
    satz.m_key.TrimRight();
    i++;
    satz.m_bez = arrAll.GetAt(i);
    satz.m_bez.TrimRight();
    i++;
    C2StringTabelle::Add(satz);
    }

return TRUE;
}
//-----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------
int C2StringTabelle::SetGruppe(const C2StringTabelle& src,const TCHAR *grKey)
{
Reset();
if(*grKey == 0)
    return 0;
for(int i = 0; i < src.GetSize(); i++)
    {
    if(!src.GruppenKey(i).CompareNoCase(grKey))
        Add(src.GetAt(i));
    }
return GetSize();
}
//----------------------------------------------------------------------------
// Erster Teil eines Schlüssels  01 002 -> 01
CString C2StringTabelle::GruppenKey(int index) const
{
if((index >= 0) && (index < C2StringTabelle::GetSize()))
    return GetAt(index).GruppenKey();
return _T("");
}
//----------------------------------------------------------------------------
// Zweiter Teil eines Schlüssels  01 002 -> 002
CString C2StringTabelle::Key2(int index) const
{
if((index >= 0) && (index < C2StringTabelle::GetSize()))
    return GetAt(index).Key2();
return _T("");
}
//---------------------------------------------------------------------------
void C2StringTabelle::Debug() const
{
CString str;

for(int i = 0; i < GetSize(); i++)
    {
    str.Format(_T("%s\n%s"),GetAt(i).m_key,GetAt(i).m_bez);
    AlertString(str);
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// C3StringTabelle
//---------------------------------------------------------------------------
C3StringTabelle::C3StringTabelle()
{
}
//-----------------------------------------------------------------------------------------
void C3StringTabelle::operator=(const C3StringTabelle& s3)
{
Reset();
for(int i = 0; i < s3.GetSize(); i++)
    {
    Add(s3.GetAt(i));
    }
}
//-----------------------------------------------------------------------------------------
void C3StringTabelle::Reset()
{
RemoveAll();
}
//-----------------------------------------------------------------------------------------
BOOL C3StringTabelle::Read(const TCHAR *folder,const TCHAR *dateiname)
{
MDEFile inFile;
MDEStringArray arrAll;

CString pathFileName;
pathFileName.Format(_T("%s\\%s"),folder,dateiname);

if(inFile.Open(pathFileName,CFile::modeRead))
    {
    inFile.ReadStringArray(arrAll);
    inFile.Close();
    }
else
    {
    CString str;
    str = Sprache(_T("Datei "),dateiname,_T(" konnte nicht geöffnet werden!"));
    AfxMessageBox(str);
    return FALSE;
    }

Reset();

C3String satz;
int i = 0;
while(i < (arrAll.GetCount() - 2))
    {
    satz.m_key = arrAll.GetAt(i);
    i++;
    satz.m_value1 = arrAll.GetAt(i);
    i++;
    satz.m_value2 = arrAll.GetAt(i);
    i++;
    C3StringTabelle::Add(satz);
    }

return FALSE;
}
//-----------------------------------------------------------------------------------------
void C3StringTabelle::Save(const TCHAR *folder,const TCHAR *dateiname)
{
CString pathFileName;
pathFileName.Format(_T("%s\\%s"),folder,dateiname);

MDEFile fileSave;
CFileException e;
if(!fileSave.Open(pathFileName,CFile::modeWrite|CFile::modeCreate,&e))
    {
    CString str;
    str.Format(_T("%s \"%s\": %d"),Sprache(_T("Fehler beim Öffnen von")),fileSave,e.m_cause);
    AfxMessageBox(str);
    return;
    }
for(int i = 0; i < GetCount(); i++)
    {
    fileSave.WriteString(GetAt(i).m_key);
    fileSave.WriteString(GetAt(i).m_value1);
    fileSave.WriteString(GetAt(i).m_value2);
    }

fileSave.Close();
}
//-----------------------------------------------------------------------------------------
int C3StringTabelle::GetIndexByKey(const TCHAR *key) const
{
for(int i = 0; i < GetSize(); i++)
    {
    if(!GetAt(i).m_key.CompareNoCase(key))
        return i;
    }
return -1;
}
//-----------------------------------------------------------------------------------------
C3String C3StringTabelle::GetItemByKey(const TCHAR *key) const
{
int index = GetIndexByKey(key);
if(index >= 0)
    return GetAt(index);
C3String s;
return s;
}
//---------------------------------------------------------------------------
void C3StringTabelle::Debug() const
{
CString str;

for(int i = 0; i < GetSize(); i++)
    {
    str.Format(_T("%s\n%s\n%s"),GetAt(i).m_key,GetAt(i).m_value1,GetAt(i).m_value2);
    AlertString(str);
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// C4StringTabelle
//---------------------------------------------------------------------------
C4StringTabelle::C4StringTabelle()
{
}
//-----------------------------------------------------------------------------------------
void C4StringTabelle::operator=(const C4StringTabelle& s4)
{
Reset();
for(int i = 0; i < s4.GetSize(); i++)
    {
    Add(s4.GetAt(i));
    }
}
//-----------------------------------------------------------------------------------------
void C4StringTabelle::Reset()
{
RemoveAll();
}
//-----------------------------------------------------------------------------------------
BOOL C4StringTabelle::Read(const TCHAR *folder,const TCHAR *dateiname)
{
MDEFile inFile;
MDEStringArray arrAll;

CString pathFileName;
pathFileName.Format(_T("%s\\%s"),folder,dateiname);

if(inFile.Open(pathFileName,CFile::modeRead))
    {
    inFile.ReadStringArray(arrAll);
    inFile.Close();
    }
else
    {
    CString str;
    str = Sprache(_T("Datei "),dateiname,_T(" konnte nicht geöffnet werden!"));
    AfxMessageBox(str);
    return FALSE;
    }

Reset();

C4String satz;
int i = 0;
while(i < (arrAll.GetCount() - 3))
    {
    satz.m_key = arrAll.GetAt(i);
    i++;
    satz.m_value1 = arrAll.GetAt(i);
    i++;
    satz.m_value2 = arrAll.GetAt(i);
    i++;
	satz.m_value3 = arrAll.GetAt(i);
    i++;
    C4StringTabelle::Add(satz);
    }

return FALSE;
}
//-----------------------------------------------------------------------------------------
void C4StringTabelle::Save(const TCHAR *folder,const TCHAR *dateiname)
{
CString pathFileName;
pathFileName.Format(_T("%s\\%s"),folder,dateiname);

MDEFile fileSave;
CFileException e;
if(!fileSave.Open(pathFileName,CFile::modeWrite|CFile::modeCreate,&e))
    {
    CString str;
    str.Format(_T("%s \"%s\": %d"),Sprache(_T("Fehler beim Öffnen von")),fileSave,e.m_cause);
    AfxMessageBox(str);
    return;
    }
for(int i = 0; i < GetCount(); i++)
    {
    fileSave.WriteString(GetAt(i).m_key);
    fileSave.WriteString(GetAt(i).m_value1);
    fileSave.WriteString(GetAt(i).m_value2);
	fileSave.WriteString(GetAt(i).m_value3);
    }

fileSave.Close();
}
//-----------------------------------------------------------------------------------------
int C4StringTabelle::GetIndexByKey(const TCHAR *key) const
{
for(int i = 0; i < GetSize(); i++)
    {
    if(!GetAt(i).m_key.CompareNoCase(key))
        return i;
    }
return -1;
}
//-----------------------------------------------------------------------------------------
C4String C4StringTabelle::GetItemByKey(const TCHAR *key) const
{
int index = GetIndexByKey(key);
if(index >= 0)
    return GetAt(index);
C4String s;
return s;
}
//---------------------------------------------------------------------------
void C4StringTabelle::Debug() const
{
CString str;

for(int i = 0; i < GetSize(); i++)
    {
    str.Format(_T("%s\n%s\n%s\n%s"),GetAt(i).m_key,GetAt(i).m_value1,GetAt(i).m_value2,GetAt(i).m_value3);
    AlertString(str);
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
BOOL CMaterialGruppen::Read()
{
return C2StringTabelle::Read(FOLDER_DOCU,DATEI_MATERIALGRUPPEN);
};
//-----------------------------------------------------------------------------------------
void CMaterialGruppen::operator=(const CMaterialGruppen& l2)
{
*dynamic_cast<C2StringTabelle*>(this) = l2;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
BOOL CArtikelGruppen::Read()
{
return C2StringTabelle::Read(FOLDER_DOCU,DATEI_ARTIKELGRUPPEN);
}
//-----------------------------------------------------------------------------------------
// Wenn in den artikelgruppen der Schlüssel mit R eingetragen ist.
// (Bsp. strGr = 10 oder 10R, 10R = Eintrag in Tabelle)
BOOL CArtikelGruppen::IsRohPlattenGruppe(const CString& strGr) const
{
if(strGr.IsEmpty())
    return FALSE;
for(int i = 0; i < CArtikelGruppen::GetCount(); i++)
    {
    CString key = CArtikelGruppen::GetAt(i).m_key;
    if(key.IsEmpty())
        continue;
    if(!key.Left(strGr.GetLength()).Compare(strGr))
        {
         if(key.GetAt(key.GetLength()-1) == _T('R') && !key.Left(key.GetLength()-1).Compare(strGr))
            return TRUE;
        }
    }
return FALSE;
}
BOOL CArtikelGruppen::IsRohBlockGruppe(const CString& strGr) const
{
if(strGr.IsEmpty())
    return FALSE;
for(int i = 0; i < CArtikelGruppen::GetCount(); i++)
    {
    CString key = CArtikelGruppen::GetAt(i).m_key;
    if(key.IsEmpty())
        continue;

	if(!key.Left(strGr.GetLength()).Compare(strGr))
        {
        if(key.GetAt(key.GetLength()-1) == _T('B') && !key.Left(key.GetLength()-1).Compare(strGr))
			return TRUE;
        }
    }
return FALSE;
}
//-----------------------------------------------------------------------------------------
void CArtikelGruppen::operator=(const CArtikelGruppen& l2)
{
*dynamic_cast<C2StringTabelle*>(this) = l2;
}
//----------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
void CMaterialTabelle::operator=(const CMaterialTabelle& l2)
{
*dynamic_cast<C2StringTabelle*>(this) = l2;
}
//----------------------------------------------------------------------------
BOOL CMaterialTabelle::Read()
{
return C2StringTabelle::Read(FOLDER_DOCU,DATEI_MATERIAL);
};
//-----------------------------------------------------------------------------------------
int CMaterialTabelle::GetIndexByKey(const TCHAR *art,const TCHAR *nr) const
{
CString key(art);
key += _T(" ");
key += nr;
for(int i = 0; i < GetSize(); i++)
    {
    if(!GetAt(i).m_key.CompareNoCase(key))
        return i;
    }
return -1;
}
//-----------------------------------------------------------------------------------------
C2String CMaterialTabelle::GetItemByKey(const TCHAR *art,const TCHAR *nr) const
{
int index = GetIndexByKey(art,nr);
if(index >= 0)
    return GetAt(index);
C2String s;
return s;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
BOOL COberflTabelle::Read()
{
return C2StringTabelle::Read(FOLDER_DOCU,DATEI_OBERFLAECHE);
};
//-----------------------------------------------------------------------------------------
void COberflTabelle::operator=(const COberflTabelle& l2)
{
*dynamic_cast<C2StringTabelle*>(this) = l2;
}
//-----------------------------------------------------------------------------------------
int COberflTabelle::GetIndexByKey(const TCHAR *art,const TCHAR *nr) const
{
CString key(art);
key += _T(" ");
key += nr;
for(int i = 0; i < GetSize(); i++)
    {
    if(!GetAt(i).m_key.CompareNoCase(key))
        return i;
    }
return -1;
}
//-----------------------------------------------------------------------------------------
C2String COberflTabelle::GetItemByKey(const TCHAR *art,const TCHAR *nr) const
{
int index = GetIndexByKey(art,nr);
if(index >= 0)
    return GetAt(index);
C2String s;
return s;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
BOOL CLagerTabelle::Read()
{
return C2StringTabelle::Read(FOLDER_DOCU,DATEI_LAGER);
};
//-----------------------------------------------------------------------------------------
void CLagerTabelle::operator=(const CLagerTabelle& l2)
{
*dynamic_cast<C2StringTabelle*>(this) = l2;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
BOOL CLagerMatTabelle::Read()
{
return C3StringTabelle::Read(FOLDER_DOCU,DATEI_LAGERMAT);
};
//-----------------------------------------------------------------------------------------
void CLagerMatTabelle::operator=(const CLagerMatTabelle& tab3)
{
*dynamic_cast<C3StringTabelle*>(this) = tab3;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
BOOL CLieferantenTabelle::Read()
{
return C2StringTabelle::Read(FOLDER_DOCU,DATEI_LIEFERANTEN);
};
//-----------------------------------------------------------------------------------------
void CLieferantenTabelle::operator=(const CLieferantenTabelle& l2)
{
*dynamic_cast<C2StringTabelle*>(this) = l2;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
BOOL CEinheitenTabelle::Read()
{
return C2StringTabelle::Read(FOLDER_DOCU,DATEI_EINHEITEN);
};
//----------------------------------------------------------------------------
void CEinheitenTabelle::operator=(const CEinheitenTabelle& l2)
{
*dynamic_cast<C2StringTabelle*>(this) = l2;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
BOOL CFehlerbezeichnungTabelle::Read()
{
return C2StringTabelle::Read(FOLDER_DOCU,DATEI_FEHLERBEZEICHNUNG);
};
//----------------------------------------------------------------------------
void CFehlerbezeichnungTabelle::operator=(const CFehlerbezeichnungTabelle& l2)
{
*dynamic_cast<C2StringTabelle*>(this) = l2;
}
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
BOOL CPreislistenTabelle::Read()
{
return C3StringTabelle::Read(FOLDER_DOCU,DATEI_PREISLISTEN);
};
//----------------------------------------------------------------------------
void CPreislistenTabelle::operator=(const CPreislistenTabelle& l3)
{
*dynamic_cast<C3StringTabelle*>(this) = l3;
}
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
BOOL CGatterdatenTabelle::Read()
{
return C4StringTabelle::Read(FOLDER_DOCU,DATEI_GATTERDATEN);
};
//----------------------------------------------------------------------------
void CGatterdatenTabelle::operator=(const CGatterdatenTabelle& l4)
{
*dynamic_cast<C4StringTabelle*>(this) = l4;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
BOOL CLagerOriginalStatusTabelle::Read()
{
return C2StringTabelle::Read(FOLDER_DOCU,DATEI_LAGERORIGINALSTATUS);
};
//----------------------------------------------------------------------------
void CLagerOriginalStatusTabelle::operator=(const CLagerOriginalStatusTabelle& l2)
{
*dynamic_cast<C2StringTabelle*>(this) = l2;
}
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
BOOL CProgrammStatusTabelle::Read()
{
return C3StringTabelle::Read(FOLDER_PROGRAM,DATEI_PROGSTATUS);
};
//-----------------------------------------------------------------------------------------
void CProgrammStatusTabelle::Save()
{
C3StringTabelle::Save(FOLDER_PROGRAM,DATEI_PROGSTATUS);
};
//-----------------------------------------------------------------------------------------
void CProgrammStatusTabelle::operator=(const CProgrammStatusTabelle& tab3)
{
*dynamic_cast<C3StringTabelle*>(this) = tab3;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
