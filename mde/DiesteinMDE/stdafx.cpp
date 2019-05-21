// stdafx.cpp : Quelldatei, die nur die Standard-Includes einbindet
// DiesteinMDE.pch ist der vorkompilierte Header
// stdafx.obj enthält die vorkompilierten Typinformationen

#include "stdafx.h"




//-------------------------------------------------------------------------------------
//--------------------------------------------------------------------------
void TranslateStatic(CStatic& ctrlStatic)
{
CString str;
ctrlStatic.GetWindowText(str);
if(str.IsEmpty()) return;
str = g_sprache.Translate(str);
ctrlStatic.SetWindowText(str);
}
//--------------------------------------------------------------------------
void TranslateButton(CButton& ctrlStatic)
{
CString str;
ctrlStatic.GetWindowText(str);
if(str.IsEmpty()) return;
str = g_sprache.Translate(str);
ctrlStatic.SetWindowText(str);
}
//-------------------------------------------------------------------------------------
CString Sprache(const CString& german)
{
return g_sprache.Translate(german);
}
//-------------------------------------------------------------------------------------
CString SpracheSK(const CString& german,const CString& keys,CString& keyRet)
{
return g_sprache.TranslateSK(german,keys,keyRet);
}
//-------------------------------------------------------------------------------------
CString Sprache(const CString& german1,const CString& c1,const CString& german2)
{
return g_sprache.Translate(german1,c1,german2);
}
//-------------------------------------------------------------------------------------
CString Sprache(const CString& german1,int zahl,const CString& german2)
{
return g_sprache.Translate(german1,zahl,german2);
}
//-------------------------------------------------------------------------------------
CString Sprache(const CString& german1,const CString& c1,const CString& german2,
                const CString& c2,const CString& german3)
{
return g_sprache.Translate(german1,c1,german2,c2,german3);
}
//-------------------------------------------------------------------------------------
CString Sprache(const CString& german1,int zahl1,const CString& german2,
                int zahl2,const CString& german3)
{
return g_sprache.Translate(german1,zahl1,german2,zahl2,german3);
}
//-------------------------------------------------------------------------------------
//--------------------------------------------------------------------
// Allgemeine Funktionen
void PlaySoundScan()
{
CString datei;
datei.Format(_T("%s\\%s"),FOLDER_PROGRAM,SOUND_SCAN);
PlaySound (datei, NULL, SND_SYNC);
}
//--------------------------------------------------------------------
void PlaySoundAdd()
{
CString datei;
datei.Format(_T("%s\\%s"),FOLDER_PROGRAM,SOUND_ADD);
PlaySound (datei, NULL, SND_SYNC);
}
//--------------------------------------------------------------------
void PlaySoundError()
{
CString datei;
datei.Format(_T("%s\\%s"),FOLDER_PROGRAM,SOUND_ERROR);
PlaySound (datei, NULL, SND_SYNC);
}
//--------------------------------------------------------------------
void PlaySoundOther()
{
CString datei;
datei.Format(_T("%s\\%s"),FOLDER_PROGRAM,SOUND_OTHER);
PlaySound (datei, NULL, SND_SYNC);
}
//--------------------------------------------------------------------
//------------------------------------------------------------------------
// String in char* speichern mit Abschlussstring z
char *ToBuffer(CString str,char *z,char *buffer)
{
int l = str.GetLength();
for(int k = 0; k < l; k++)
    {
    *(buffer+k) = (char)str.GetAt(k);
    }
*(buffer+l) = 0;
strcat(buffer,z);
return buffer;
}
/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------
// Falls editfeld kein ordentlicher Zahlenwert, focus auf feld setzten
BOOL NoValueSetFocus(CString& strValue,CEdit& ctrlEdit)
{
if(!ctrlEdit.IsWindowEnabled())
    return FALSE;

strValue.Trim();
for(int i = 0; i < strValue.GetLength(); i++)
    {
    TCHAR ch = strValue.GetAt(i);
    if(i == 0)  // - Zeichen erlaubt
        {
        if(ch == _T('-')) continue;
        }
    if(iswdigit(ch) || (ch == _T(',')) || (ch == _T('.')))
        continue;
    ctrlEdit.SetFocus();
    ctrlEdit.SetSel(0,-1,FALSE);  // Alles selektieren
    PlaySoundError();
    return TRUE;
    }
return FALSE;
}
//---------------------------------------------------------
// Falls editfeld kein ordentlicher Zahlenwert, TRUE zurückgeben
BOOL NoValue(CString& strValue)
{

strValue.Trim();
for(int i = 0; i < strValue.GetLength(); i++)
    {
    TCHAR ch = strValue.GetAt(i);
    if(i == 0)  // - Zeichen erlaubt
        {
        if(ch == _T('-')) continue;
        }
    if(iswdigit(ch) || (ch == _T(',')) || (ch == _T('.')))
        continue;
    PlaySoundError();
    return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL ValueExeed400(CEdit& edit)
{
CString str;
edit.GetWindowText(str);
if(NoValueSetFocus(str,edit))
    return TRUE;		// geändert auf TRUE, damit im Fehlerfall immer TRUE zurückkommt  ch 16.12.2013
if(CSteinSatz::StringToDouble(str) > 400.0)
    {
    PlaySoundError();
    edit.SetFocus();
    return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
void AlertString(const CString& str)
{
AfxMessageBox(str);
}
//-------------------------------------------------------------------------------------
void AlertInt(int i)
{
CString str;
str.Format(_T("%d"),i);
AfxMessageBox(str);
}
//-------------------------------------------------------------------------------------
void Alert2Int(int i,int j)
{
CString str;
str.Format(_T("%d   %d"),i,j);
AfxMessageBox(str);
}
//-------------------------------------------------------------------------------------
void AlertReal(double i)
{
CString str;
str.Format(_T("%f"),i);
AfxMessageBox(str);
}
