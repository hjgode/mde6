// SteinSaetze.cpp: implementation of the CSteinSaetze class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSteinSaetze::CSteinSaetze()
{
m_modified = FALSE;
}
//---------------------------------------------------------------------------
CSteinSaetze::CSteinSaetze(const CSteinSaetze& saetze)
{
*this = saetze;
m_modified = FALSE;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void CSteinSaetze::operator=(const CSteinSaetze& saetze)
{
if(this == &saetze)
    return;
arr.RemoveAll();
arr.Copy(saetze.arr);
m_modified = TRUE;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
BOOL CSteinSaetze::ReadFile(const CString& datei)
{
arr.RemoveAll();

CString pathFileName;
pathFileName.Format(_T("%s\\%s"),FOLDER_DOCU,datei);

MDEFile inFile;


if(inFile.Open(pathFileName,CStdioFile::modeRead))
    {
    inFile.ReadSteinSatzArray(*this);
    inFile.Close();
	// CreationDate/Time ermitteln
	CFileStatus status;
	CString originalFileName = pathFileName;
	originalFileName.Replace(_T("Kopie"),_T(""));
	inFile.GetStatus( originalFileName, status );
	m_Dateidatum = status.m_mtime;
    }
else
    return FALSE;

return TRUE;
}
//---------------------------------------------------------------------------
CSteinSaetze& CSteinSaetze::Add(const CSteinSatz& satz)
{
arr.Add(satz);
m_modified = TRUE;
return *this;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Satz entfernen
CSteinSaetze& CSteinSaetze::RemoveAt(int index)
{
if(index >= 0)
    arr.RemoveAt(index);
m_modified = TRUE;
return *this;
}
//---------------------------------------------------------------------------
CSteinSaetze& CSteinSaetze::SubSatz(const CSteinSatz& satz) // Menge 1 in Steinsätze verringern
{
int ix;
if(FoundNumberAt(satz,ix))
    {
    arr.ElementAt(ix).SetMenge1(max(arr.GetAt(ix).Menge1()-satz.Menge1(),0.));  // Menge kann nicht < 0 werden
    arr.ElementAt(ix).SetMenge2(0.);
    }
m_modified = TRUE;
return *this;
}
//---------------------------------------------------------------------------
CSteinSaetze& CSteinSaetze::AddSatz(const CSteinSatz& satz) // Menge 1 in Steinsätze erhöhen oder Satz hinzufügen
{
int ix;
if(FoundNumberAt(satz,ix))
    {
    double mengealt = arr.GetAt(ix).Menge1();
    CSteinSatz neuSatz(satz);
    neuSatz.SetMenge1(mengealt+satz.Menge1());
    arr.SetAt(ix,neuSatz);
    arr.ElementAt(ix).SetMenge2(0.);
    // Bei Böse Verkauf: gelöschte Reservierung zurückschreiben
    if(!satz.ResFuerAuftrag().IsEmpty())
        {
        CSteinSatz& sref = SteinSatz(ix);
        SSatz s(satz);
        SSatz ss(sref);
        ss.m_ResFuerAuftrag = s.m_ResFuerAuftrag;
        ss.m_AuftragsKundenname = s.m_AuftragsKundenname;
        ss.m_AuftragsPos = s.m_AuftragsPos;
        ss.m_AuftragsTeilpos = s.m_AuftragsTeilpos;
        sref.Set(ss);
        }
    }
else
    arr.Add(satz);
m_modified = TRUE;
return *this;
}
//---------------------------------------------------------------------------
// nicht benutzt
int CSteinSaetze::ErstelleReservierteSteinsaetze(const CString& resAuftrag,CSteinSaetze& resSteinSaetze) const
{
if(resSteinSaetze.Anzahl())
    return resSteinSaetze.Anzahl();
for(int i = 0; i < Anzahl(); i++)
    {
    if(!resAuftrag.CompareNoCase(SteinSatzConst(i).ResFuerAuftrag()))
        resSteinSaetze.Add(SteinSatzConst(i));
    }
return resSteinSaetze.Anzahl();
}
//---------------------------------------------------------------------------
bool CSteinSaetze::FoundNumberAt(const CSteinSatz& satz,int& ix) // Steinsatz mit Nummer satz.Nummer suchen
{
return FoundAt(satz.Nummer(),ix);
}
//---------------------------------------------------------------------------
bool CSteinSaetze::FoundAt(const CString& strNummer,int& ix) // Steinsatz mit Nummer strNummer suchen
{
ix = -1;
if(strNummer.IsEmpty())
    return false;
// Suchalgorithmus bei sortierten Nummern (als Strings sortiert)
int steps = 2 * (int)(log(Anzahl())/log(2));
int maxix = Anzahl();
int minix = 0;
int startix = (maxix+minix)/2;
int i = 0;
while(i++ < steps)
    {
    int ungleich = strNummer.Compare(arr.GetAt(startix).Nummer());
    if(!ungleich)
        {
        ix = startix;
        return true;
        }
    if((maxix == minix) || (maxix == minix+1)) break;
    if(ungleich > 0)
        minix = startix;
    else
        maxix = startix;
    startix = (maxix+minix)/2;
    }
// wenn bisher nicht erfolgreich, nochmals alles durcheiern
for(i = 0; i < Anzahl(); i++)
    {
    if(strNummer == arr.GetAt(i).Nummer())
        {
        ix = i;
        return true;
        }
    }
return false;
}
//------------------------------------------------------------------------
char *ToBuffer(CString str,char *z,char *buffer);
//------------------------------------------------------------------------
// Auftraegsbestand aktualisieren (wird nur am Gerät verwendet)
#if(DEVICE == DOLPHIN)
void CSteinSaetze::Save(const CString& name)
{

CString pathFileName;
pathFileName.Format(_T("%s\\%s"),FOLDER_DOCU,name);


CSaveMsg dlg;
dlg.m_strFileName = pathFileName;
dlg.m_pSteinSaetze = this;
dlg.m_strText = Sprache(_T("Speichere ")) + name;

dlg.DoModal();

/*
CFile fileSave;
fileSave.Open(pathFileName,CFile::modeWrite|CFile::modeCreate);

for(int i = 0; i < Anzahl(); i++)
    {
    char buffer[1000];
    ToBuffer(arr.GetAt(i).m_value,"\r\n",buffer);
    fileSave.Write(buffer,strlen(buffer));
    }
fileSave.Close();
*/
m_modified = FALSE;

}
#endif