#include "StdAfx.h"

COptionen::COptionen(void)
    {
    }

//-----------------------------------------------------------------------
// Definition von Kundenvarianten in DiesteinMDE.ini
//-----------------------------------------------------------------------
// String in DiesteinMDE.ini, z.B. 100108P111
// Bit 0:   Auskunft
// Bit 1:   Maße ändern möglich
// Bit 2:   Rückbuchen möglich
// Bit 3:   Inventur
// Bit 4:   Länge Auftragsname (z.B. 08)
// Bit 5:           "
// Bit 6:   Produktion/Verkauf(Juma) (P,V,1, 1=P+V)
// Bit 7:   Zugang
// Bit 8:   Lagerumbuchung
// Bit 9:   Einkauf
// Bit 10:  Preisinfo möglich
// Bit 11:  1. Preisliste (Fa. Böse)
// .
// .
// Bit 20:  10. Preisliste
// Bit 21:  Böse enabled
// Bit 22:  Reservierung enabled
// Bit 23:  Lieferung enabled
// Bit 24:  Oberfläche ändern enabled
// Bit 25:  Container enabled
// Bit 26:  Benutzer-Einwahl-Dialog enabled
// Bit 30:	Gattern enabled
// Bit 31:  Produktion - Platte zu mehrere Aufträge zuordnen (Bernasconi)
// Bit 32:  Zugang Eingabe von/bis Steinnr (Bernasconi)
// Bit 33:	Steinbruch - Brutto = Nettomaße
// Bit 34:	Steinbruch - Summe Blöcke (m³) des Tages anzeigen 
// Bit 35:	Inventur - Platten ohne Daten (Agr, Mgr, usw) erfassen 
// Bit 36:	Inventur - Rohplatten (AGR-Kz) nicht doppelt scannen lassen
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------
// DiesteinMDE.ini einlesen und in g_strOptionen speichern
//-----------------------------------------------------------------------
void COptionen::ReadIni()
{
CString iniName;
iniName.Format(_T("%s\\%s"),FOLDER_PROGRAM,DATEI_INI);

CFile iniFile;
CString cstr;
if(iniFile.Open(iniName,CFile::modeRead))
    {
    char buffer[100];
    int l;
    while((l = iniFile.Read(buffer,EL(buffer)-1)) > 0)
        {
        *(buffer+l) = 0;
        cstr += buffer;
        }
    iniFile.Close();
    }
else
    return;

m_strIni = cstr;
int next = cstr.Find(_T(";"),0);
if(next < 0)
    next = cstr.Find(_T("\r"),0);
if(next < 0)
    next = cstr.Find(_T("\n"),0);
if(next > 0)
    {
    m_strIni = cstr.Left(next);
    }
m_strIni.MakeUpper();    // z.B. "101108"
}
//-----------------------------------------------------------------------
BOOL COptionen::InfoEnabled() const
{
if(m_strIni.GetLength() > 0)
    {
    if(!m_strIni.Mid(0,1).Compare(_T("1")))
        return TRUE;
    }
return FALSE;
}
//-----------------------------------------------------------------------
BOOL COptionen::PreisinfoEnabled() const
{
if(m_strIni.GetLength() > 10)
    {
    if(!m_strIni.Mid(10,1).Compare(_T("1")))
        return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::VerkaufEnabled() const
{
if(m_strIni.GetLength() > 6)
    {
    if(!m_strIni.Mid(6,1).Compare(_T("1")))
        return TRUE;
    if(!m_strIni.Mid(6,1).Compare(_T("V")))
        return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::ProduktionEnabled() const
{
if(m_strIni.GetLength() > 6)
    {
    if(!m_strIni.Mid(6,1).Compare(_T("1")))
        return TRUE;
    if(!m_strIni.Mid(6,1).Compare(_T("P")))
        return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::LagerUmEnabled() const
{
if(m_strIni.GetLength() > 8)
    {
    if(!m_strIni.Mid(8,1).Compare(_T("1")))
        return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::EinkaufEnabled() const
{
if(m_strIni.GetLength() > 9)
    {
    if(!m_strIni.Mid(9,1).Compare(_T("1")))
        return TRUE;
    }

return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::ZugangEnabled() const
{
if(m_strIni.GetLength() > 7)
    {
    if(!m_strIni.Mid(7,1).Compare(_T("1")))
        return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::InventurEnabled() const
{
if(m_strIni.GetLength() > 3)
    {
    if(!m_strIni.Mid(3,1).Compare(_T("1")))
        return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
// Flag für "Letztes Zeichen bei "Auftragsnummer scannen" unterdrücken abfragen
// Zwei Zeichen 1,0,0,1,06  06 = Länge der verbleibenden Auftragsnummer
int COptionen::LastAufNrSupress() const
{
if(m_strIni.GetLength() > 4)
    return _ttoi(m_strIni.Mid(4,2));

return 0;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::MasseAendEnabled() const
{
if(m_strIni.GetLength() > 1)
    {
    if(!m_strIni.Mid(1,1).Compare(_T("1")))
        return TRUE;
    }

return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::RueckEnabled() const
{
if(m_strIni.GetLength() > 2)
    {
    if(!m_strIni.Mid(2,1).Compare(_T("1")))
        return TRUE;
    }

return FALSE;
}
//-------------------------------------------------------------------------------------
CString COptionen::PVEnabled() const
{
if(m_strIni.GetLength() > 6)
    {
    CString str = m_strIni.Mid(6,1);
    if((str == _T("P")) || (str == _T("V")))
        return str;
    }
CString str1;
return str1;
}
//-------------------------------------------------------------------------------------
// Bits 11..20 enablen Preislsiten für Böse (max 4 gleichzeitig) i = 0...9
BOOL COptionen::PreislisteEnabled(int i) const
{
if(m_strIni.GetLength() > (i+11))
    {
    if(!m_strIni.Mid(i+11,1).Compare(_T("1")))
        return TRUE;
    }

return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::BoeseEnabled() const
{
if(m_strIni.GetLength() > (21))
    {
    if(!m_strIni.Mid(21,1).Compare(_T("1")))
        return TRUE;
    }

return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::ReservierungEnabled() const
{
if(m_strIni.GetLength() > (22))
    {
    if(!m_strIni.Mid(22,1).Compare(_T("1")))
        return TRUE;
    }

return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::LieferungEnabled() const
{
if(m_strIni.GetLength() > (23))
    {
    if(!m_strIni.Mid(23,1).Compare(_T("1")))
        return TRUE;
    }

return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::OberflAendernEnabled() const
{
if(m_strIni.GetLength() > 24)
    {
    if(!m_strIni.Mid(24,1).Compare(_T("1")))
        return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::ContainerEnabled() const
{
if(m_strIni.GetLength() > 25)
    {
    if(!m_strIni.Mid(25,1).Compare(_T("1")))
        return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::BenutzerEnabled() const
{
if(m_strIni.GetLength() > 26)
    {
    if(!m_strIni.Mid(26,1).Compare(_T("1")))
        return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::SteinbruchEnabled() const
{
if(m_strIni.GetLength() > 27)
    {
    if(!m_strIni.Mid(27,1).Compare(_T("1")))
        return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::SteinbruchMassCheckDisabled() const
{
if(m_strIni.GetLength() > 28)
    {
    if(!m_strIni.Mid(28,1).Compare(_T("1")))
        return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::SteinbruchEmailDisabled() const
{
if(m_strIni.GetLength() > 29)
    {
    if(!m_strIni.Mid(29,1).Compare(_T("1")))
        return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::GatternEnabled() const
{
if(m_strIni.GetLength() > 30)
    {
    if(!m_strIni.Mid(30,1).Compare(_T("1")))
        return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::ProduktionMehrereAuftraegeEnabled() const
{
if(m_strIni.GetLength() > 31)
    {
    if(!m_strIni.Mid(31,1).Compare(_T("1")))
        return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::ZugangSteinnrVonBisEnabled() const
{
if(m_strIni.GetLength() > 32)
    {
    if(!m_strIni.Mid(32,1).Compare(_T("1")))
        return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::SteinbruchNettoGleichBruttoMasseEnabled() const
{
if(m_strIni.GetLength() > 33)
    {
    if(!m_strIni.Mid(33,1).Compare(_T("1")))
        return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::SteinbruchTagessummeAnzeigenEnabled() const
{
if(m_strIni.GetLength() > 34)
    {
    if(!m_strIni.Mid(34,1).Compare(_T("1")))
        return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::InventurPlattenOhneZusatzdatenErfassenEnabled() const
{
if(m_strIni.GetLength() > 35)
    {
    if(!m_strIni.Mid(35,1).Compare(_T("1")))
        return TRUE;
    }
return FALSE;
}
//-------------------------------------------------------------------------------------
BOOL COptionen::InventurRohplattenNichtDoppeltErfassenEnabled() const
{
if(m_strIni.GetLength() > 36)
    {
    if(!m_strIni.Mid(36,1).Compare(_T("1")))
        return TRUE;
    }
return FALSE;
}