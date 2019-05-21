// DiesteinMDE.h : Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "\"stdafx.h\" vor dieser Datei für PCH einschließen"
#endif

#ifdef POCKETPC2003_UI_MODEL
#include "resourceppc.h"
#endif 

// CDiesteinMDEApp:
// Siehe DiesteinMDE.cpp für die Implementierung dieser Klasse
//

class CDiesteinMDEApp : public CWinApp
{
public:
	CDiesteinMDEApp();
	
// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};
