//watch_trigger.h

#ifndef _watch_trigger_h_
#define _watch_trigger_h_

#include "stdafx.h"

void startWatchThread(TCHAR* stateStr, TCHAR* deltaStr, BYTE vkVal, BOOL fireEvents);

void stopWatchThread();

#endif