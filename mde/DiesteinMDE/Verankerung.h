#pragma once
#include "afxtempl.h"

#define MAX_VAZAHL  12      // Maximale Anzahl von Steinsätzen in einer Verankerung
//---------------------------------------------------------------------------
// Eine Verankerung (Böse) ist eine Gruppe von maximal 12 Objekten, die z.B. gemeinsam
// verkauft werden, für die ein gemeinsamer Preis existiert
// Gespeichert wird nur die Steinnummer, die Position im Array 0..12 entspricht der
// Satzposition
// In der Preisinfo und beim Lagerumbuchen Blinkt ein Button Einzalansicht, wenn
// ein Steinsatzn zu einer Verankerung gehört. Nach betätigen erscheint eine
// Listbox mit den Steinen einer Verankerung, jeweils 4 Zeilen. wird auf eine der
// Zeilen gepickt wird in eine Ansicht ähnlich Preisinfo verzweigt, wo nur die Platten der
// verankerung ausgewählt werden können.

class CVerankerung 
{
public:

    CVerankerung(){};
    CVerankerung(const CVerankerung& v){};
    ~CVerankerung(){};

    CString m_Name;
    CString m_Hinweis;
    CString m_Preise[4];
    CString arr[MAX_VAZAHL];

    CString SteinNummer(int ix) const {return arr[ix];}
    void operator=(const CVerankerung& v);

    BOOL SetStr(CString str);    // Aus string erzeugen, mindestens Name muss da sein
    CString AsString();
private:
    CString NextValue(const CString& str,char ch,int& next);
};
//---------------------------------------------------------------------------
// Index im Array entspricht Lfd. Nr (ix 0 -> lfd 1), wenn Position fehlt, wird leerer satz eingefügt
class CVerankerungen : public CArray<CVerankerung,const CVerankerung&>
{
public:
    CVerankerungen(){};
    ~CVerankerungen(){};

    int Read();
    CVerankerung& Verankerung(int ix){return GetAt(ix);}
    BOOL ExistName(CString name,int &ix);

    // Wenn Steinnumer in einer Verankerung enthalten ist, wird diese zurückgegeben mit Index in der Verankerung
    BOOL FindeSteinNummer(const CString& strNr,CVerankerung& v,int& ix);
private:
    void CreateFromStrArray(MDEStringArray& strarr);

};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
