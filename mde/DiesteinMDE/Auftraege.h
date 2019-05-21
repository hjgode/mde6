#pragma once

// Auftraege.h: interface for the CAuftraege class.
//
//////////////////////////////////////////////////////////////////////
class SteinSaetze;
class CAuftrag;

class CAuftraege  
{
public:

	CAuftraege();
	virtual ~CAuftraege(){};

    CArray<class CAuftrag,const class CAuftrag&> arr;

    CString m_strName;   // Je nach Typ (Verkauf,Produktion,Inventur,Zugang)
	BOOL m_bSpeichernOk;

    int Anzahl() const {return arr.GetSize();}

	BOOL ReadFile();
	CAuftraege& Create(const CString& inFileStr);

    CAuftrag& Auftrag(int index);
    CAuftrag AuftragConst(int index) const;
    CAuftrag& Auftrag(CString auftragsName);
    CAuftrag AuftragConst(CString auftragsName) const;
    int Exist(CString auftragsName) const;
    CAuftraege& Add(CAuftrag& auftrag);
    CAuftraege& Remove(CString auftragsName);
    int NaechsteBuchungsnummer() const;
	void Save();
    void SaveSubAuftrag(const CString& pathFileName);
    BOOL FindeBuchungsnummer(int *pn,int maxBuNr,int *pi,int *pj);
};
