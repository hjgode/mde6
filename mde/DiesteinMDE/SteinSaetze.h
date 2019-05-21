// SteinSaetze.h: interface for the CSteinSaetze class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

class CSteinSaetze  
{
public:
	CSteinSaetze();
	CSteinSaetze(const CSteinSaetze& saetze);
	virtual ~CSteinSaetze(){};

    CArray<class CSteinSatz,const class CSteinSatz&> arr;
    BOOL m_modified; // fängt nur die Änderungen über Klassenfunktionen ab
	CTime m_Dateidatum;

	void operator=(const CSteinSaetze& saetze);

    BOOL ReadFile(const CString& name = DATEI_LAGERBESTAND);
    int Anzahl() const {return arr.GetSize();}

    CSteinSatz& SteinSatz(int index) {return arr[index];}
    CSteinSatz SteinSatzConst(int index) const {return arr[index];}

    CSteinSaetze& Create(const CString& inFileStr);
    CSteinSaetze& Add(const CSteinSatz &satz);  // Anhängen, nicht addieren
    CSteinSaetze& RemoveAt(int index);
    CSteinSaetze& SubSatz(const CSteinSatz& satz); // Menge 1 in Steinsätze verringern, Menge2 auf 0
    CSteinSaetze& AddSatz(const CSteinSatz& satz); // Menge 1 in Steinsätze erhöhen oder Satz hinzufügen, Menge2 auf 0
    bool FoundNumberAt(const CSteinSatz& satz,int& ix); // Steinsatz mit Nummer satz.Nummer suchen
    bool FoundAt(const CString& strNr,int& ix);    // Steinsatz mit Nummer strNr suchen
#if(DEVICE == DOLPHIN)
    void Save(const CString& name = DATEI_LAGERBESTAND);
#endif

    // Sonderfunktionen für Böse
     int ErstelleReservierteSteinsaetze(const CString& resAuftrag,CSteinSaetze& resSteinSaetze) const;

};
