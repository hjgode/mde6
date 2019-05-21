// Auftraege.cpp: implementation of the CAuftraege class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAuftraege::CAuftraege()
{
}
//------------------------------------------------------------------------
// Zugriff auf Auftrag mit Index
CAuftrag& CAuftraege::Auftrag(int index)
{
return arr[index];
}
//------------------------------------------------------------------------
// Kopie des Auftrags mit Index
CAuftrag CAuftraege::AuftragConst(int index) const
{
return arr[index];
}
//------------------------------------------------------------------------
// Wenn Auftrag vorhanden, Zugriff auf diesen zurückgeben, sonst neuen erstellen
CAuftrag& CAuftraege::Auftrag(CString auftragsName)
{
int index = Exist(auftragsName);
if(index >=0)
    return Auftrag(index);
CAuftrag auf(auftragsName);
arr.Add(auf);
return Auftrag(Anzahl()-1);
}
//------------------------------------------------------------------------
// Kopie des Auftrags
CAuftrag CAuftraege::AuftragConst(CString auftragsName) const
{
int index = Exist(auftragsName);
if(index >=0)
    return arr[index];
CAuftrag auf;
return auf;
}
//------------------------------------------------------------------------
// Falls existiert, Index zurück, sonst -1
int CAuftraege::Exist(CString auftragsName) const
{
for(int i = 0; i < Anzahl(); i++)
    {
    if(arr.GetAt(i).m_strIdent == auftragsName)
        return i;
    }
return -1;
}
//------------------------------------------------------------------------
// Falls nicht vorhanden hinzufügen, ansonsten Positionen addieren
CAuftraege& CAuftraege::Add(CAuftrag& auftrag)
{
int index = Exist(auftrag.m_strIdent);
if(index < 0)
    arr.Add(auftrag);
else
    {
    for(int i = 0; i < auftrag.m_Positionen.Anzahl(); i++)
        {
        CSteinSatz satz(auftrag.PositionConst(i));
        Auftrag(index).AddPosition(satz);
        }
    }
return *this;
}
//------------------------------------------------------------------------
// Auftrag entfernen
CAuftraege& CAuftraege::Remove(CString auftragsName)
{
int index = Exist(auftragsName);
if(index >= 0)
    arr.RemoveAt(index);
return *this;
}
//------------------------------------------------------------------------
int CAuftraege::NaechsteBuchungsnummer() const
{
int maxnum = 0;
for(int i = 0; i < Anzahl(); i++)
    {
    for(int j = 0; j < AuftragConst(i).m_Positionen.Anzahl(); j++)
        {
        if(AuftragConst(i).m_Positionen.SteinSatz(j).m_buchungsNummer > maxnum)
            maxnum = AuftragConst(i).m_Positionen.SteinSatz(j).m_buchungsNummer;
        }
    }
return maxnum+1;
}
//------------------------------------------------------------------------
// Auftraege als CSV-Datei speichern, pro Zeile Auftragsnummer und eine Position,
// bei mehreren Positionen wird jeweils eine neue Zeile mit der gleichen Auftragsnummer
// erzeugt
void CAuftraege::Save()
{
m_bSpeichernOk = TRUE;
SaveSubAuftrag(m_strName+_T(".csv"));

/////////////////// Sicherung
SaveSubAuftrag(m_strName+_T("1.csv"));
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
void CAuftraege::SaveSubAuftrag(const CString& fileName)
{
CString pathFileName;
pathFileName.Format(_T("%s\\%s"),FOLDER_DOCU,fileName);

CFile fileSave;
CFileException e;
try
	{
	if(!fileSave.Open(pathFileName,CFile::modeWrite|CFile::modeCreate,&e))
		{
		CString str;
		str.Format(_T("%s \"%s\": %d"),Sprache(_T("Fehler beim Öffnen von")),fileName,e.m_cause);
		AfxMessageBox(str);
		m_bSpeichernOk = FALSE;
		return;
		}

	// Positionen zählen
	int i=0,j=0;
	int nn = 0;
	int maxBuNr = 0;
	for(i = 0; i < Anzahl(); i++)
		{
		int m = Auftrag(i).m_Positionen.Anzahl();
		for(j = 0; j < m; j++)   // größte Buchungsnummer suchen
	        {
		    if(Auftrag(i).m_Positionen.SteinSatz(j).m_buchungsNummer > maxBuNr)
			    maxBuNr = Auftrag(i).m_Positionen.SteinSatz(j).m_buchungsNummer;
			}
		nn += m;
		}
	int buNr = 0;
	for(int n = 0; n < nn; n++)
		{
		if(!FindeBuchungsnummer(&buNr,maxBuNr,&i,&j))  // Es können durch löschen Lücken in den Nummern sein
	        {
		    AfxMessageBox(_T("Buchungsnummer!!!"));
			break;
			}
		buNr++;

		char buffer[100];
		ToBuffer(Auftrag(i).m_strIdent,";",buffer);
		fileSave.Write(buffer,strlen(buffer));          // Auftagsname schreiben
		Auftrag(i).Position(j).WriteToFile(fileSave);   // Steinsatz schreiben
		}

	fileSave.Close();
	}
catch (...)
	{
		CString str;
		str.Format(_T("%s \"%s\": %d"),Sprache(_T("Fehler beim Speichern")),fileName,e.m_cause);
		AfxMessageBox(str);
		fileSave.Close();
		m_bSpeichernOk = FALSE;
		return;

	}
}
//------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
BOOL CAuftraege::FindeBuchungsnummer(int *pn,int maxBuNr,int *pi,int *pj)
{
while(*pn <= maxBuNr)
    {
    for(int i = 0; i < Anzahl(); i++)
        {
        for(int j = 0; j < Auftrag(i).m_Positionen.Anzahl(); j++)
            {
            if(Auftrag(i).m_Positionen.SteinSatz(j).m_buchungsNummer == *pn)
                {
                *pi = i;
                *pj = j;
                return TRUE;
                }
            }
        }
    (*pn)++;
    }
return FALSE;
}
//-----------------------------------------------------------------------------------------
BOOL CAuftraege::ReadFile()
{
CString pathFileName;
MDEFile inFile;

arr.RemoveAll();

// Auftraege.csv einlesen
pathFileName.Format(_T("%s\\%s"),FOLDER_DOCU,m_strName+_T(".csv"));
MDEStringArray arrAufs;
if(inFile.Open(pathFileName,CFile::modeRead))
    {
    inFile.ReadStringArray(arrAufs);
    inFile.Close();
    }
else
    {
    if(inFile.Open(pathFileName,CFile::modeRead|CFile::modeCreate))
        inFile.Close();
    else
        {
        AfxMessageBox(Sprache(_T("Auftragsdatei konnte nicht geöffnet werden!")));
        return FALSE;
        }
    }

int buchnr = 1;
for(int i = 0; i < arrAufs.GetCount(); i++)
    {
    CAuftrag auf;
    auf.Create(arrAufs.GetAt(i)); // Steinsatz erstellen
    auf.Position(0).m_buchungsNummer = buchnr; // in der gelesenen Reihenfolge durchnummerieren
    buchnr++;
    Add(auf);
    }
return TRUE;
}
//-----------------------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
