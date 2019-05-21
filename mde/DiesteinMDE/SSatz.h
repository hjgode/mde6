// SSatz.h: interface for the SSatz class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

class CSteinSatz;
class SSatz  
{
public:
	SSatz();
    SSatz(const CSteinSatz& s);
	virtual ~SSatz(){};

    CString NextValue(const CSteinSatz& sts,char ch,int& next);

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
    CString m_FehlString;   // nicht verwenden
    CString m_FehlLaenge;
    CString m_FehlBreite;
    CString m_FehlNummer;
    CString m_Menge1;
    CString m_ME1;
    CString m_Menge2;
    CString m_ME2;
    CString m_Lager;
    CString m_Hinweis;
    CString m_Lieferant;    //Bis hier nicht ändern (lagerbestandsdaten)
//------------------------------------------------
// folgende Daten müssen bei SteinSatz.Set(ss) und ss(SteinSatz&) gleiche Reihenfolge haben

    CString m_Preis;
    CString m_ArtikelGr;
    CString m_ArtikelGrBez;
    CString m_BestellNr;
    CString m_BestellPos;
    CString m_ProduktionVerkauf; // 
    CString m_Datum;
    CString m_Zeit;
    CString m_Ende;     // Auftrag-Ende Kennzeichen 

    CString m_Menge1Verfuegbar;
    CString m_Menge2Verfuegbar;
    CString m_LagerAlt;

    CString m_LieferscheinNummer;
    CString m_LieferscheinDatum;

//-----------------------------------------------------
// Preisauskunft, Artikelanzeige für Fa. Böse, Werte werden nur gelesen, nicht geschrieben
    CString m_GR_Preis[10]; // Anzahl 10, darf nicht geändert werden!!!
    CString m_ResTyp;       // Typ der Reservierung 1 = Angebot, 2 = Auftrag
    CString m_Gewicht;
    CString m_dummy3;
    CString m_dummy4;
    CString m_dummy5;
    CString m_dummy6;
    CString m_dummy7;
    CString m_dummy8;
    CString m_dummy9;
    CString m_dummy10;
    CString m_dummy11[10]; // Anzahl 10, darf nicht geändert werden!!!

    CString m_TextFeld;

    CString m_ResFuerAuftrag;       // Stein ist reserviert für die Angebots/Auftragsnummer
    CString m_AuftragsKundenname;   // Name des Auftraggebers
    CString m_AuftragsPos;          // Position im Auftrag
    CString m_AuftragsTeilpos;
    CString m_TypKennung;           // Erkennung für Sonderbehandlung (Keile)
    CString m_HerstellArt;

    CString m_OberNrAlt;
    CString m_Container;
    CString m_FehlNummerAlt;
    CString m_NummerParent;         // Bei 2. od. weiterer Rückbuchung Nummer der Ursprünglichen Platte 
    CString m_UserName;             // nur beim Schreiben relevant
    CString m_Schicht;              // Leer oder Nummer bis 2 Stellen (Steinbruch)
    CString m_LaengeBrutto;         // Brutto-Blockmaß (Steinbruch)
    CString m_BreiteBrutto;         // Brutto-Blockmaß (Steinbruch)
    CString m_DickeBrutto;          // Brutto-Blockmaß (Steinbruch)

	// für Gatterdaten
	CString m_GatterDatumAnfang;
	CString m_GatterDatumEnde;
	CString m_GatterZeitAnfang;
	CString m_GatterZeitEnde;
	CString m_GatterZaehlerstandAnfang;
	CString m_GatterZaehlerstandEnde;
	CString m_GatterSandverbrauch;
	CString m_GatterKalkverbrauch;
	CString m_GatterBlockhoehe;
	CString m_GatterBlattart;
	CString m_GatterNeueBlaetter;
	CString m_GatterAnzahlSchnitte;

	// Felder Maß/Fehlecken-Änderung
	CString m_LaengeAlt;
    CString m_BreiteAlt;
	CString m_FehlLaengeAlt;
    CString m_FehlBreiteAlt;
	CString m_RestKz;
	//

	};
