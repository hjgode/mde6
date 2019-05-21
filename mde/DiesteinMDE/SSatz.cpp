// SSatz.cpp: implementation of the SSatz class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SSatz::SSatz()
{
}
//--------------------------------------------------------------------
SSatz::SSatz(const CSteinSatz& sts)
{
int i = 0;
char ch = ';';
int start = 0;
int next = sts.m_value.Find(ch,start); if(next < 0) return;
m_Nummer = sts.m_value.Left(next);

start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_ArtNr = sts.m_value.Mid(start,next-start);

start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_Artikel = sts.m_value.Mid(start,next-start);

start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_MatGr = sts.m_value.Mid(start,next-start);

start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_MatNr = sts.m_value.Mid(start,next-start);

start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_Material = sts.m_value.Mid(start,next-start);

start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_OberNr = sts.m_value.Mid(start,next-start);

start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_Oberflaeche = sts.m_value.Mid(start,next-start);

start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_Laenge = sts.m_value.Mid(start,next-start);

start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_Breite = sts.m_value.Mid(start,next-start);

start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_Dicke = sts.m_value.Mid(start,next-start);

// Fehlecken
start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_FehlString = sts.m_value.Mid(start,next-start);

start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_FehlLaenge = sts.m_value.Mid(start,next-start);

start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_FehlBreite = sts.m_value.Mid(start,next-start);

start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_FehlNummer = sts.m_value.Mid(start,next-start);

// Menge1
start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_Menge1 = sts.m_value.Mid(start,next-start);

start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_ME1 = sts.m_value.Mid(start,next-start);

// Menge2
start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_Menge2 = sts.m_value.Mid(start,next-start);

start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_ME2 = sts.m_value.Mid(start,next-start);

// Lager
start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_Lager = sts.m_value.Mid(start,next-start);

// Hinweis
start = next+1;
next = sts.m_value.Find(ch,start); if(next < 0) return;
m_Hinweis = sts.m_value.Mid(start,next-start);

// Lieferant
start = next+1;
next = sts.m_value.Find(ch,start);
if(next < 0)
    {
    m_Lieferant = sts.m_value.Mid(start);
    return;
    }
else
    m_Lieferant = sts.m_value.Mid(start,next-start);
//!!!!!!!!!!!!!!!!! Bis hier nichts ändern

m_Preis =               NextValue(sts,ch,next);
m_ArtikelGr    =        NextValue(sts,ch,next);
m_ArtikelGrBez =        NextValue(sts,ch,next);
m_BestellNr =           NextValue(sts,ch,next);
m_BestellPos =          NextValue(sts,ch,next);
m_ProduktionVerkauf =   NextValue(sts,ch,next);
m_Datum =               NextValue(sts,ch,next);
m_Zeit =                NextValue(sts,ch,next);
m_Ende =                NextValue(sts,ch,next);

m_Menge1Verfuegbar =    NextValue(sts,ch,next);
m_Menge2Verfuegbar =    NextValue(sts,ch,next);
m_LagerAlt =            NextValue(sts,ch,next);

m_LieferscheinNummer =  NextValue(sts,ch,next);
m_LieferscheinDatum =   NextValue(sts,ch,next);

// Fa. Böse Preise
for(i = 0; i < EL(m_GR_Preis); i++)
    m_GR_Preis[i] = NextValue(sts,ch,next);
// Fa. Böse GA-Artikeldaten
m_ResTyp  =             NextValue(sts,ch,next);
m_Gewicht =             NextValue(sts,ch,next);
m_dummy3 =              NextValue(sts,ch,next);
m_dummy4 =              NextValue(sts,ch,next);
m_dummy5 =              NextValue(sts,ch,next);
m_dummy6 =              NextValue(sts,ch,next);
m_dummy7 =              NextValue(sts,ch,next);
m_dummy8 =              NextValue(sts,ch,next);
m_dummy9 =              NextValue(sts,ch,next);
m_dummy10 =             NextValue(sts,ch,next);
for(i = 0; i < EL(m_dummy11); i++)
    m_dummy11[i] = NextValue(sts,ch,next);

m_TextFeld =            NextValue(sts,ch,next);

m_ResFuerAuftrag =      NextValue(sts,ch,next);
m_AuftragsKundenname =  NextValue(sts,ch,next);
m_AuftragsPos =         NextValue(sts,ch,next);
m_AuftragsTeilpos =     NextValue(sts,ch,next);
m_TypKennung =          NextValue(sts,ch,next);
m_HerstellArt =         NextValue(sts,ch,next);

m_OberNrAlt =           NextValue(sts,ch,next);
m_Container =           NextValue(sts,ch,next);
m_FehlNummerAlt =       NextValue(sts,ch,next);
m_NummerParent =        NextValue(sts,ch,next);
m_UserName =            NextValue(sts,ch,next);
m_Schicht =             NextValue(sts,ch,next);
m_LaengeBrutto =        NextValue(sts,ch,next);
m_BreiteBrutto =        NextValue(sts,ch,next);
m_DickeBrutto =         NextValue(sts,ch,next);

// Gatterdaten
m_GatterDatumAnfang =		  NextValue(sts,ch,next);
m_GatterDatumEnde =		      NextValue(sts,ch,next);
m_GatterZeitAnfang =          NextValue(sts,ch,next);
m_GatterZeitEnde =			  NextValue(sts,ch,next);
m_GatterZaehlerstandAnfang =  NextValue(sts,ch,next);
m_GatterZaehlerstandEnde =    NextValue(sts,ch,next);
m_GatterSandverbrauch =       NextValue(sts,ch,next);
m_GatterKalkverbrauch =		  NextValue(sts,ch,next);
m_GatterBlockhoehe =          NextValue(sts,ch,next);
m_GatterBlattart =	          NextValue(sts,ch,next);
m_GatterNeueBlaetter =        NextValue(sts,ch,next);
m_GatterAnzahlSchnitte =      NextValue(sts,ch,next);

// Maß-/Fehlecke-Änderung
m_LaengeAlt =      NextValue(sts,ch,next);
m_BreiteAlt =      NextValue(sts,ch,next);
m_FehlLaengeAlt =      NextValue(sts,ch,next);
m_FehlBreiteAlt =      NextValue(sts,ch,next);
m_RestKz =         NextValue(sts,ch,next);

//
}
//--------------------------------------------------------------------------------------
CString SSatz::NextValue(const CSteinSatz& sts,char ch,int& next)
{
if(next < 0) return _T("");
int start = next+1;
next = sts.m_value.Find(ch,start);
if(next < 0)
    {
    return sts.m_value.Mid(start);
    }
return sts.m_value.Mid(start,next-start);
}