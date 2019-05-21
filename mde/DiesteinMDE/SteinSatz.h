// SteinSatz.h: interface for the CSteinSatz class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "SSatz.h"

class CSteinSatz  
{
public:
    CString m_value;    // Kopie aus der Datei
    int m_buchungsNummer;

	CSteinSatz();
	CSteinSatz(const CString& inCSVStr);
	CSteinSatz(const CSteinSatz& satz);
	virtual ~CSteinSatz(){};

    void operator=(const CSteinSatz& satz);
    
    // Menge ausnahme: handling als double
	double Menge1() const;
	double Menge2() const;
	double Menge1Verfuegbar() const;
	double Menge2Verfuegbar() const;
	CSteinSatz& SetMenge1(double wert);
	CSteinSatz& SetMenge2(double wert);
	CSteinSatz& SetMenge1Verfuegbar(double wert);
	CSteinSatz& SetMenge2Verfuegbar(double wert);

    // Handling als String
    CString Nummer() const;
    CString Artikel() const;
    CString ArtikelGr() const;
    CString StrMenge1() const;
    CString LieferscheinNummer() const;
    CString LieferscheinDatum() const;
    CString Lager() const;

    CSteinSatz& SetNummer(CString nr);
    CSteinSatz& SetArtikelGr(CString ar);
    CSteinSatz& SetMaterial(const CString& gruppe,const CString& key,const CString& bez);
    CSteinSatz& SetOberflaeche(const CString& key,const CString& bez);
    CSteinSatz& SetLieferscheinNummer(const CString& str);
    CSteinSatz& SetLieferscheinDatum(const CString& str);
    CSteinSatz& SetLager(const CString& str);

    CSteinSatz& SetDatumZeit();
    CSteinSatz& SetProduktionVerkauf(const CString& pv);

    // Nur Böse: Auftragsnummer reservierter Platten ermittel (mögl. schnell)
    CString ResFuerAuftrag() const;
    void LieferungReservierungRemove();
    //////////////////////////////////
    CSteinSatz& Set(const SSatz& s);

    void WriteToFile(CFile& fileSave);


    static double StringToDouble(const CString& menge);
    static CString DoubleToString(double wert);

/*
    CString m_Nummer;
    CString m_ArtNr;
    CString m_Artikel;
    CString m_MatGr;
    CString m_MatNr;
    CString m_Material;
    CString m_OberNr;
    CString m_Oberflaeche;
    CString m_Laenge;
    CString m_Breite;
    CString m_Dicke;
    CString m_FehlString;
    CString m_FehlLaenge;
    CString m_FehlBreite;
    CString m_FehlNummer;
    CString m_Menge1;
    CString m_ME1;
    CString m_Menge2;
    CString m_ME2;
    CString m_Lager;
    CString m_Hinweis;
    CString m_Lieferant;
    CString m_Preis;
    CString m_ArtikelGr;
    CString m_ArtikelGrBez;
    CString m_BestellNr;
    CString m_BestellPos;
    CString m_ProduktionVerkauf;
    CString m_Datum;
    CString m_Zeit;
    CString m_Ende;
    CString m_Menge1Verfuegbar;
    CString m_Menge2Verfuegbar;
    CString m_LagerAlt;
    CString m_LieferscheinNummer;
    CString m_LieferscheinDatum;
*/
};
