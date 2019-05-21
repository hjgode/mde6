//watch_trigger.cpp

#include "stdafx.h"

TCHAR* stopThreadStr=L"stopWatchThread";
HANDLE stopThreadH=NULL;

HANDLE threadH=NULL;
DWORD  threadID=0;

struct EVENTNAMES{
	TCHAR state[MAX_PATH];
	TCHAR delta[MAX_PATH];
	BYTE  vk_value;
	BOOL bFireEvents;
};

EVENTNAMES eventNames;

//forward declare
DWORD watchThread(LPVOID lpParm);

void startWatchThread(TCHAR* stateStr, TCHAR* deltaStr, BYTE vkVal, BOOL fireEvents){
	wsprintf(eventNames.state, L"%s", stateStr);
	wsprintf(eventNames.delta, L"%s", deltaStr);
	eventNames.vk_value=vkVal;
	eventNames.bFireEvents=fireEvents;

	threadH = CreateThread(NULL, 0, watchThread, (LPVOID)&eventNames, 0, &threadID);
}

void stopWatchThread(){
	if(stopThreadH!=NULL)
		SetEvent(stopThreadH);
}

DWORD watchThread(LPVOID lpParm){
	DEBUGMSG(1,(L"watchThread starting..."));
	EVENTNAMES* evtNames=(EVENTNAMES*)lpParm;
	HANDLE stateHandle=CreateEvent(NULL, TRUE, false, evtNames->state); //manual reset
	HANDLE deltaHandle=CreateEvent(NULL, false, false, evtNames->delta);

	BYTE vk_key=evtNames->vk_value;
	BOOL bFireEvt=evtNames->bFireEvents;

	HANDLE StateLeftScan = CreateEvent(NULL, true, false, L"StateLeftScan");
	HANDLE DeltaLeftScan = CreateEvent(NULL, false, false, L"DeltaLeftScan");

	HANDLE handles[3];

	stopThreadH=CreateEvent(NULL, FALSE, FALSE, stopThreadStr);

	handles[0]=stateHandle;
	handles[1]=deltaHandle;
	handles[2]=stopThreadH;

	BOOL bRun=TRUE;
	DWORD dwWaitReturn;

	BOOL bIsKeyDown=TRUE;
	while (bRun){
		dwWaitReturn = WaitForMultipleObjects(3, handles, FALSE, INFINITE);
		switch(dwWaitReturn){
			case WAIT_OBJECT_0:
				DEBUGMSG(1, (L"state\r\n"));
				ResetEvent(stateHandle);
				if(bFireEvt)
					SetEvent(StateLeftScan);
				break;
			case WAIT_OBJECT_0 +1:
				DEBUGMSG(1, (L"DELTA\r\n"));
				if(bFireEvt){
					SetEvent(DeltaLeftScan);
					Sleep(1);
					ResetEvent(StateLeftScan);
				}
				if(bIsKeyDown){
					//KeyDown
					DEBUGMSG(1, (L"KeyDown\r\n"));
					keybd_event(vk_key, 0x00, 0, 0);
				}
				else{
					//KeyUp
					DEBUGMSG(1, (L"KeyUp\r\n"));
					keybd_event(vk_key, 0x00, KEYEVENTF_KEYUP, 0);
				}
				//on evrey Delta, toggle bIsKeyDown
				bIsKeyDown=!bIsKeyDown;
				break;
			case WAIT_OBJECT_0+2:
				//stop
				bRun=FALSE;
				break;
		}
	}
	stopThreadH=NULL;
	DEBUGMSG(1,(L"watchThread stopped"));
	return 0;
}