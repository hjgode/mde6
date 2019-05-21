// DiesteinMDE.cpp : Definiert das Klassenverhalten f�r die Anwendung.
//

#include "stdafx.h"
#include "Auswahl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDiesteinMDEApp

BEGIN_MESSAGE_MAP(CDiesteinMDEApp, CWinApp)
END_MESSAGE_MAP()


// CDiesteinMDEApp-Erstellung
CDiesteinMDEApp::CDiesteinMDEApp()
	: CWinApp()
{
	// TODO: Hier Code zur Konstruktion einf�gen
	// Alle wichtigen Initialisierungen in InitInstance positionieren
}


// Das einzige CDiesteinMDEApp-Objekt
CDiesteinMDEApp theApp;

// Eigene globale Variablen
CSteinSatz  g_baseSteinSatz;    // globaler letzter verwendeter Satz
COptionen   g_Optionen;         // Aus DiesteinMDE gelesener Optionenstring
CSprache    g_sprache;
CString     g_UserName;         // aktueller Ger�tebenutzer, wenn mit Name angemeldet

// CDiesteinMDEApp-Initialisierung

BOOL CDiesteinMDEApp::InitInstance()
{
    // SHInitExtraControls sollte einmal w�hrend der Anwendungsinitialisierung aufgerufen werden, um alle
    // Windows Mobile-spezifischen Steuerelemente wie CAPEDIT und SIPPREF zu initialisieren.
    SHInitExtraControls();

	// Standardinitialisierung
	// Wenn Sie diese Features nicht verwenden und die Gr��e
	// der ausf�hrbaren Datei verringern m�chten, entfernen Sie
	// die nicht erforderlichen Initialisierungsroutinen.
	// �ndern Sie den Registrierungsschl�ssel, unter dem Ihre Einstellungen gespeichert sind.
	// TODO: �ndern Sie diese Zeichenfolge entsprechend,
	// z.B. zum Namen Ihrer Firma oder Organisation.
	SetRegistryKey(_T("DiesteinMDE2005"));

    g_Optionen.ReadIni();

// Sprachdatei einlesen
    g_sprache.Read();

    INT_PTR nResponse = 0;
    
	CAuswahl dlg;
	m_pMainWnd = &dlg;
	nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: F�gen Sie hier Code ein, um das Schlie�en des
		//  Dialogfelds �ber "OK" zu steuern
	}

	// Da das Dialogfeld geschlossen wurde, FALSE zur�ckliefern, sodass wir die
	//  Anwendung verlassen, anstatt das Nachrichtensystem der Anwendung zu starten.
	return FALSE;
}
