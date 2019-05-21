// stdafx.h : Includedatei für Standardsystem-Includedateien
// oder häufig verwendete, projektspezifische Includedateien,
// die nur selten geändert werden.

#pragma once

#pragma comment(linker, "/nodefaultlib:libc.lib")
#pragma comment(linker, "/nodefaultlib:libcd.lib")

// HINWEIS: Dieser Wert steht in keinem engen Zusammenhang mit der verwendeten Version von Windows CE
#define WINVER _WIN32_WCE

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Selten verwendete Teile der Windows-Header ausschließen
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// einige CString-Konstruktoren sind explizit
#ifdef _CE_DCOM
#define _ATL_APARTMENT_THREADED
#endif

// Deaktiviert das Ausblenden einiger häufiger und oft ignorierter Warnungen durch MFC
#define _AFX_ALL_WARNINGS

#include <ceconfig.h>
#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP) 
#define SHELL_AYGSHELL
#endif

#include <afxwin.h>         // MFC-Kern- und -Standardkomponenten
#include <afxext.h>         // MFC-Erweiterungen

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC-Unterstützung für allgemeine Steuerelemente von Internet Explorer 4
#endif



#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC-Unterstützung für allgemeine Windows-Steuerelemente
#endif // _AFX_NO_AFXCMN_SUPPORT



#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
#ifndef _DEVICE_RESOLUTION_AWARE
#define _DEVICE_RESOLUTION_AWARE
#endif
#endif

#ifdef _DEVICE_RESOLUTION_AWARE
#include "DeviceResolutionAware.h"
#endif

#include <aygshell.h>
#pragma comment(lib, "aygshell.lib") 

#if (_WIN32_WCE < 0x500) && ( defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP) )
	#pragma comment(lib, "ccrtrtti.lib")
	#ifdef _X86_	
		#if defined(_DEBUG)
			#pragma comment(lib, "libcmtx86d.lib")
		#else
			#pragma comment(lib, "libcmtx86.lib")
		#endif
	#endif
#endif

#include <altcecrt.h>

#define EL(array) (sizeof(array)/sizeof(array[0]))

//*********************************************************************************************
// Eigene Definitionen
//*********************************************************************************************
#define DOLPHIN     1
#define DATALOGIC   2

#define DEVICE      DOLPHIN
//*********************************************************************************************
// Dateien, die vom Computer bereitgestellt werden
#define DATEI_LAGERBESTAND_UR   _T("LagerBestand.csv")          // Original vom Computer
#define DATEI_LAGERBESTAND      _T("LagerBestandKopie.csv")     // Damit wird gearbeitet, wird aktualisiert wenn Original neuer
#define DATEI_LAGERSTATUS       _T("LagerStatus.txt")           // Enthält Lagerstatus-Information (Änderungszeit der letzten Lagerbestandsdatei)
#define DATEI_CONTAINERBESTAND_UR       _T("ContainerBestand.csv")          // Original vom Computer
#define DATEI_CONTAINERBESTAND          _T("ContainerBestandKopie.csv")     // Damit wird gearbeitet, wird aktualisiert wenn Original neuer
#define DATEI_CONTAINERSTATUS           _T("ContainerStatus.txt")           // Enthält Containerstatus-Information
#define DATEI_BESTELLUNGEN      _T("Bestellungen.csv")          // == Einkauf
#define DATEI_BLOECKE           _T("Bloecke.csv")               // == Steinbruch

#define DATEI_SPRACHE           _T("SpracheMDE.txt")

#define DATEI_VORABDATEN	_T("Vorabdaten.csv")		//für die Vorab erfassten Blöcke - nur zur Kontrolle bzw. Übernahme der Daten für die Blockerfassung
// Datei, die der Computer bereitstellt und der aber über die Auftraege gelesen wird
#define NAME_GATTEROFFENEAUFTRAEGE			_T("GatterOffeneAuftraege")	

// Dateien und Auftragskopf-Einträge für die Rückgabe an den Computer
#define NAME_VERKAUF                _T("Verkauf")
#define NAME_RESERVIERUNG           _T("Reservierung")
#define NAME_PRODUKTION             _T("Produktion")
#define NAME_LAGERUM                _T("Lagerumbuchung")
#define NAME_OBERFLAENDERN          _T("OberflaecheAendern")
#define NAME_ZUGANG                 _T("Zugang")
#define NAME_INVENTUR               _T("Inventur")
#define NAME_BESTELLUNGENEINGANG    _T("BestellungenEingang")  // Rückgabedatei Einkauf
#define NAME_CONTAINERBUCHUNG       _T("ContainerBuchung")     // Rückgabedatei Container-Bestelleingang
#define NAME_BLOECKE                _T("Bloecke")              // Rückgabedatei Steinbruch - eigentlich sind das alle Blöcke inkl. der Änderung.
#define NAME_BLOCKAENDERUNGEN		_T("BloeckeKorrektur")		// zusätzlich werden die Änderungen hier noch einmal abgespeichert, da die Suche nach geänderten Blöcken in der Datei "Bloecke.Csv" zu aufwendig ist.
#define NAME_GATTERAUFTRAEGE        _T("GatterAuftraege")              // Rückgabedatei Gattern
#define NAME_GATTERPLATTEN        _T("GatterPlatten")              // Rückgabedatei Gattern - erfasste Platten 
#define NAME_GATTERDATEN        _T("GatterDaten")              // Rückgabedatei Gattern - Zusatzinformationen
#define NAME_GATTERBLOECKE        _T("GatterBloecke")              // Rückgabedatei Gattern - Zusatzinformatione





// Optionenbits
#define ID_INFO                 1
#define ID_PREISINFO            2
#define ID_VERKAUF              4
#define ID_LIEFERUNG            8
#define ID_RESERVIERUNG         16
#define ID_PRODUKTION           32
#define ID_LAGERUM              64
#define ID_ZUGANG               128
#define ID_BESTELLUNGENEINGANG  256 // = Einkauf
#define ID_INVENTUR             512
#define ID_OBERFLAENDERN        1024
#define ID_CONTAINER            2048
#define ID_BLOECKE              4096
#define ID_GATTERN				8192

#undef _DEBUG
#ifdef _DEBUG
#define FOLDER_DOCU     _T("Storage Card")
#define FOLDER_PROGRAM  _T("Storage Card")
#else
#define FOLDER_DOCU     _T("My Documents")
#define FOLDER_PROGRAM  L"\\Program Files\\DiesteinMDE6" // _T("\\IPSM\\Dietrich")
#endif

#define FOLDER_BLOCKSICH  _T("Blocksicherung")


#define DATEI_INI           _T("DiesteinMDE.ini")
#define DATEI_PROGSTATUS    _T("ProgStatus.txt")            // Speichert Programmeinstellungen

#define SOUND_SCAN      _T("ScanOK.WAV")
#define SOUND_ADD       _T("AddPos.WAV")
#define SOUND_ERROR     _T("Error.WAV")
#define SOUND_OTHER     _T("ScanOther.WAV")

#include "DiesteinMDE.h"

// use FOR_CK75 define to compile for CK75
#define FOR_CK75
#ifndef FOR_CK75
#include ".\Scanner6\BarcodeScanner.h"
#else
#include ".\ScannerITC\BarcodeScanner.h"
#endif

#include "MDEStringArray.h"
#include "MDEFile.h"
#include "SSatz.h"
#include "SteinSatz.h"
#include "SteinSaetze.h"
#include "Optionen.h"
#include "Sprache.h"
#include "EigenTabellen.h"
#include "Auftrag.h"
#include "Auftraege.h"
#include "SaveMsg.h"

//-------------------------------------------------------------------------------------------
// Globale Funktionen
void PlaySoundScan();
void PlaySoundAdd();
void PlaySoundError();
void PlaySoundOther();

BOOL NoValueSetFocus(CString& strValue,CEdit& ctrlEdit);
BOOL NoValue(CString& strValue);
BOOL ValueExeed400(CEdit& edit);

char *ToBuffer(CString str,char *z,char *buffer);

void TranslateStatic(CStatic& ctrlStatic);
void TranslateButton(CButton& ctrlStatic);

CString Sprache(const CString &german);
CString SpracheSK(const CString &german,const CString& keys,CString& keyRet);
CString Sprache(const CString &german1,const CString& c1,const CString& german2);
CString Sprache(const CString &german1,int zahl,const CString& german2);
CString Sprache(const CString &german1,const CString& c1,const CString& german2,
                            const CString& c2,const CString& german3);
CString Sprache(const CString &german1,int zahl1,const CString& german2,
                            int zahl2,const CString& german3);
/////////////////////////////////////////////////////////////////////////////
void AlertString(const CString& str);
void AlertInt(int i);
void Alert2Int(int i,int j);
void AlertReal(double i);
/////////////////////////////////////////////////////////////////////////////
class CSteinSaetze;
class CSteinSatz;
class COptionen;
class CSprache;

extern CDiesteinMDEApp theApp;

extern CSteinSatz g_baseSteinSatz;
extern COptionen g_Optionen;
extern CSprache g_sprache;

/////////////////////////////////////////////////////////////////////////////
/*
use the following to either use CK75 Scankey fix or WM_SCANDATA handling with
a background thread in BarcodeScanner.cpp
*/
#define USE_SCANKEY_ENABLED

#ifdef USE_SCANKEY_ENABLED
	#pragma message ("stdafx.h: USE_SCANKEY_ENABLED is defined\n");
#else
	#pragma message ("stdafx.h: USE_SCANKEY_ENABLED is not defined\n");
#endif