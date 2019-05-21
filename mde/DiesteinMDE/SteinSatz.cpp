// SteinSatz.cpp: implementation of the CSteinSatz class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CString g_UserName;

//-----------------------------------------------------------
CSteinSatz::CSteinSatz()
{
m_buchungsNummer = 0;
}
//-----------------------------------------------------------
CSteinSatz::CSteinSatz(const CSteinSatz& satz)
{
*this = satz;
}
//-----------------------------------------------------------
CSteinSatz::CSteinSatz(const CString& inCSVStr)
{
m_value = inCSVStr;
m_buchungsNummer = 0;
}
//--------------------------------------------------------------------------------------
void CSteinSatz::operator=(const CSteinSatz& satz)
{
if(this == &satz) return;
m_value = satz.m_value;
m_buchungsNummer = satz.m_buchungsNummer;
}
//--------------------------------------------------------------------------------------
double CSteinSatz::StringToDouble(const CString& menge)
{
// Umrechnung Komma->Punkt
CString str(menge);
int n = str.Find(_T(','));
if(n >= 0)
    str.SetAt(n,_T('.'));
n = str.GetLength();
TCHAR *stop;
return wcstod(str.GetBuffer(n),&stop);
}
//--------------------------------------------------------------------------------------
double CSteinSatz::Menge1() const
{
SSatz s(*this);
return StringToDouble(s.m_Menge1);
}
//--------------------------------------------------------------------------------------
double CSteinSatz::Menge2() const
{
SSatz s(*this);
return StringToDouble(s.m_Menge2);
}
//--------------------------------------------------------------------------------------
double CSteinSatz::Menge1Verfuegbar() const
{
SSatz s(*this);
return StringToDouble(s.m_Menge1Verfuegbar);
}
//--------------------------------------------------------------------------------------
double CSteinSatz::Menge2Verfuegbar() const
{
SSatz s(*this);
return StringToDouble(s.m_Menge2Verfuegbar);
}
//--------------------------------------------------------------------------------------
CString CSteinSatz::DoubleToString(double wert)
{
CString str;
str.Format(_T("%.2f"),wert);
int n = str.Find(_T('.'));
if(n >= 0)
    str.SetAt(n,_T(','));
return str;
}
//--------------------------------------------------------------------------------------
CSteinSatz& CSteinSatz::SetMenge1(double wert)
{
SSatz s(*this);
s.m_Menge1 = DoubleToString(wert);
Set(s);
return *this;
}
//--------------------------------------------------------------------------------------
CSteinSatz& CSteinSatz::SetMenge2(double wert)
{
SSatz s(*this);
s.m_Menge2 = DoubleToString(wert);
Set(s);
return *this;
}
//--------------------------------------------------------------------------------------
CSteinSatz& CSteinSatz::SetMenge1Verfuegbar(double wert)
{
SSatz s(*this);
s.m_Menge1Verfuegbar = DoubleToString(wert);
Set(s);
return *this;
}
//--------------------------------------------------------------------------------------
CSteinSatz& CSteinSatz::SetMenge2Verfuegbar(double wert)
{
SSatz s(*this);
s.m_Menge2Verfuegbar = DoubleToString(wert);
Set(s);
return *this;
}
//--------------------------------
CString CSteinSatz::Nummer() const
{
char ch = ';';
int start = 0;
int next = m_value.Find(ch,start); if(next < 0) return _T("");
return m_value.Left(next);

//SSatz s(*this);
//return s.m_Nummer;
}
//--------------------------------
CString CSteinSatz::Artikel() const
{
char ch = ';';
int start = 0;
int next = m_value.Find(ch,start); if(next < 0) return _T("");
//m_Nummer = sts.m_value.Left(next);

start = next+1;
next = m_value.Find(ch,start); if(next < 0) return _T("");
//m_ArtNr = sts.m_value.Mid(start,next-start);

start = next+1;
next = m_value.Find(ch,start); if(next < 0) return _T("");
//m_Artikel = sts.m_value.Mid(start,next-start);
return m_value.Mid(start,next-start);

}
//--------------------------------
CString CSteinSatz::ArtikelGr() const
{
SSatz ss(*this);
return ss.m_ArtikelGr;
}
//--------------------------------
CString CSteinSatz::StrMenge1() const
{
SSatz ss(*this);
return ss.m_Menge1;
}
//--------------------------------
CString CSteinSatz::LieferscheinNummer() const
{
SSatz ss(*this);
return ss.m_LieferscheinNummer;
}
//--------------------------------
CString CSteinSatz::LieferscheinDatum() const
{
SSatz ss(*this);
return ss.m_LieferscheinDatum;
}
//--------------------------------
CString CSteinSatz::Lager() const
{
SSatz ss(*this);
return ss.m_Lager;
}
//--------------------------------
CSteinSatz& CSteinSatz::SetNummer(CString nr)
{
SSatz s(*this);
s.m_Nummer = nr;
Set(s);
return *this;
}
//--------------------------------
CSteinSatz& CSteinSatz::SetArtikelGr(CString ar)
{
SSatz s(*this);
s.m_ArtikelGr = ar;
Set(s);
return *this;
}
//--------------------------------
CSteinSatz& CSteinSatz::SetMaterial(const CString& gruppe,const CString& key,const CString& bez)
{
SSatz s(*this);
s.m_MatGr = gruppe;
s.m_MatNr = key;
s.m_Material = bez;
Set(s);
return *this;
}
//--------------------------------
CSteinSatz& CSteinSatz::SetLieferscheinNummer(const CString& str)
{
SSatz s(*this);
s.m_LieferscheinNummer = str;
Set(s);
return *this;
}
//--------------------------------
CSteinSatz& CSteinSatz::SetLieferscheinDatum(const CString& str)
{
SSatz s(*this);
s.m_LieferscheinDatum = str;
Set(s);
return *this;
}
//--------------------------------
CSteinSatz& CSteinSatz::SetLager(const CString& str)
{
SSatz s(*this);
s.m_Lager = str;
Set(s);
return *this;
}
//--------------------------------
CSteinSatz& CSteinSatz::SetOberflaeche(const CString& key,const CString& bez)
{
SSatz s(*this);
s.m_OberNr = key;
s.m_Oberflaeche = bez;
Set(s);
return *this;
}
//--------------------------------
CSteinSatz& CSteinSatz::SetDatumZeit()
{
SSatz s(*this);
CTime time;
time = CTime::GetCurrentTime();
s.m_Datum.Format(_T("%02d%02d%4d"),time.GetDay(),time.GetMonth(),time.GetYear());
s.m_Zeit.Format(_T("%02d%02d%02d"),time.GetHour(),time.GetMinute(),time.GetSecond());
Set(s);
return *this;
}
//--------------------------------
CSteinSatz& CSteinSatz::SetProduktionVerkauf(const CString& pv)
{
SSatz s(*this);
s.m_ProduktionVerkauf = pv;
Set(s);
return *this;
}
//--------------------------------
CString CSteinSatz::ResFuerAuftrag() const
{
char ch = ';';
int start = 0;
int next = 0;
int i = 0;
while(i++ < 68)
    {
    start = next+1;
    next = m_value.Find(ch,start); if(next < 0) return _T("");
    }
return m_value.Mid(start,next-start);
}
//--------------------------------
void CSteinSatz::LieferungReservierungRemove()
{
SSatz s0(*this);
s0.m_ResFuerAuftrag.Empty();
s0.m_AuftragsKundenname.Empty();
s0.m_AuftragsPos.Empty();
s0.m_AuftragsTeilpos.Empty();
Set(s0);
}
//--------------------------------
CSteinSatz& CSteinSatz::Set(const SSatz& s)
{
m_value = s.m_Nummer;         m_value += ";";
m_value += s.m_ArtNr;         m_value += ";";
m_value += s.m_Artikel;       m_value += ";";
m_value += s.m_MatGr;         m_value += ";";
m_value += s.m_MatNr;         m_value += ";";
m_value += s.m_Material;      m_value += ";";
m_value += s.m_OberNr;        m_value += ";";
m_value += s.m_Oberflaeche;   m_value += ";";
m_value += s.m_Laenge;        m_value += ";";
m_value += s.m_Breite;        m_value += ";";
m_value += s.m_Dicke;         m_value += ";";
m_value += s.m_FehlString;    m_value += ";";
m_value += s.m_FehlLaenge;    m_value += ";";
m_value += s.m_FehlBreite;    m_value += ";";
m_value += s.m_FehlNummer;    m_value += ";";
m_value += s.m_Menge1;        m_value += ";";
m_value += s.m_ME1;           m_value += ";";
m_value += s.m_Menge2;        m_value += ";";
m_value += s.m_ME2;           m_value += ";";
m_value += s.m_Lager;         m_value += ";";
m_value += s.m_Hinweis;       m_value += ";";
m_value += s.m_Lieferant;     m_value += ";";

m_value += s.m_Preis;         m_value += ";";   // Entspricht der Ausgabereihenfolge
m_value += s.m_ArtikelGr;     m_value += ";";
m_value += s.m_ArtikelGrBez;  m_value += ";";
m_value += s.m_BestellNr;     m_value += ";";
m_value += s.m_BestellPos;    m_value += ";";

m_value += s.m_ProduktionVerkauf;  m_value += ";";
m_value += s.m_Datum;         m_value += ";";
m_value += s.m_Zeit;          m_value += ";";
m_value += s.m_Ende;          m_value += ";";

m_value += s.m_Menge1Verfuegbar; m_value += ";";
m_value += s.m_Menge2Verfuegbar; m_value += ";";
m_value += s.m_LagerAlt;         m_value += ";";

m_value += s.m_LieferscheinNummer;  m_value += ";";
m_value += s.m_LieferscheinDatum;   m_value += ";";

int i;
for(i = 0; i < EL(s.m_GR_Preis); i++)
    {
    m_value += s.m_GR_Preis[i];
    m_value += ";";
    }
m_value += s.m_ResTyp;          m_value += ";";
m_value += s.m_Gewicht;         m_value += ";";
m_value += s.m_dummy3;          m_value += ";";
m_value += s.m_dummy4;          m_value += ";";
m_value += s.m_dummy5;          m_value += ";";
m_value += s.m_dummy6;          m_value += ";";
m_value += s.m_dummy7;          m_value += ";";
m_value += s.m_dummy8;          m_value += ";";
m_value += s.m_dummy9;          m_value += ";";
m_value += s.m_dummy10;         m_value += ";";
for(i = 0; i < EL(s.m_dummy11); i++)
    {
    m_value += s.m_dummy11[i];
    m_value += ";";
    }
m_value += s.m_TextFeld;        m_value += ";";

m_value += s.m_ResFuerAuftrag;  m_value += ";";
m_value += s.m_AuftragsKundenname;  m_value += ";";
m_value += s.m_AuftragsPos;     m_value += ";";
m_value += s.m_AuftragsTeilpos; m_value += ";";
m_value += s.m_TypKennung;      m_value += ";";
m_value += s.m_HerstellArt;     m_value += ";";

m_value += s.m_OberNrAlt;       m_value += ";";
m_value += s.m_Container;       m_value += ";";
m_value += s.m_FehlNummerAlt;   m_value += ";";
m_value += s.m_NummerParent;    m_value += ";";
m_value += g_UserName;          m_value += ";";
m_value += s.m_Schicht;         m_value += ";";
m_value += s.m_LaengeBrutto;    m_value += ";";
m_value += s.m_BreiteBrutto;    m_value += ";";
m_value += s.m_DickeBrutto;

// ab Hier kommen die Gatterdaten
m_value += ";";
m_value += s.m_GatterDatumAnfang;			m_value += ";";
m_value += s.m_GatterDatumEnde;				m_value += ";";
m_value += s.m_GatterZeitAnfang;			m_value += ";";
m_value += s.m_GatterZeitEnde;				m_value += ";";
m_value += s.m_GatterZaehlerstandAnfang;	m_value += ";";
m_value += s.m_GatterZaehlerstandEnde;		m_value += ";";
m_value += s.m_GatterSandverbrauch;			m_value += ";";
m_value += s.m_GatterKalkverbrauch;			m_value += ";";
m_value += s.m_GatterBlockhoehe;			m_value += ";";
m_value += s.m_GatterBlattart;				m_value += ";";
m_value += s.m_GatterNeueBlaetter;			m_value += ";";
m_value += s.m_GatterAnzahlSchnitte;

// Maß-/Fehlecke-Änderung
m_value += ";";
m_value += s.m_LaengeAlt;					m_value += ";";
m_value += s.m_BreiteAlt;					m_value += ";";
m_value += s.m_FehlLaengeAlt;				m_value += ";";
m_value += s.m_FehlBreiteAlt;				m_value += ";";
m_value += s.m_RestKz;						m_value += ";";
return *this;
}

//-------------------------------------------------------------------------
char *ToBuffer(CString str,char *z,char *buffer);
//-------------------------------------------------------------------------
void CSteinSatz::WriteToFile(CFile& fileSave)
{
char buffer[1000];
ToBuffer(m_value,"\r\n",buffer);
fileSave.Write(buffer,strlen(buffer));

}