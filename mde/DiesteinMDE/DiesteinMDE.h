// DiesteinMDE.h : Hauptheaderdatei f�r die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "\"stdafx.h\" vor dieser Datei f�r PCH einschlie�en"
#endif

#ifdef POCKETPC2003_UI_MODEL
#include "resourceppc.h"
#endif 

// CDiesteinMDEApp:
// Siehe DiesteinMDE.cpp f�r die Implementierung dieser Klasse
//

class CDiesteinMDEApp : public CWinApp
{
public:
	CDiesteinMDEApp();
	
// �berschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};
