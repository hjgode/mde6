// Eigenschaften.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "Eigenschaften.h"


// CEigenschaften-Dialogfeld

IMPLEMENT_DYNAMIC(CEigenschaften, CDialog)

CEigenschaften::CEigenschaften(CWnd* pParent /*=NULL*/)
	: CDialog(CEigenschaften::IDD, pParent)
{

}

CEigenschaften::~CEigenschaften()
{
}

void CEigenschaften::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEigenschaften, CDialog)
END_MESSAGE_MAP()


// CEigenschaften-Meldungshandler
