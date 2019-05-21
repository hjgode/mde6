// SaveMsg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "SaveMsg.h"


// CSaveMsg-Dialogfeld

IMPLEMENT_DYNAMIC(CSaveMsg, CDialog)

CSaveMsg::CSaveMsg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveMsg::IDD, pParent)
{

}

CSaveMsg::~CSaveMsg()
{
}

void CSaveMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSaveMsg, CDialog)
END_MESSAGE_MAP()


// CSaveMsg-Meldungshandler
