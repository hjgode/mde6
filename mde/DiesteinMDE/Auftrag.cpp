// Auftrag.cpp: implementation of the CAuftrag class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAuftrag::CAuftrag()
{
}
//----------------------------------------------------------------------------
CAuftrag::CAuftrag(const CAuftrag& auf)
{
*this = auf;
}
//----------------------------------------------------------------------------
// Neuer Auftrag ohne Positionen
CAuftrag::CAuftrag(CString auftrName)
{
m_strIdent = auftrName;
}
//----------------------------------------------------------------------------
void CAuftrag::operator=(const CAuftrag& auf)
{
if(this == &auf)
    return;
m_strIdent = auf.m_strIdent;
m_Positionen = auf.m_Positionen;
}
//-----------------------------------------------------------------
CAuftrag& CAuftrag::Create(CString inCSVStr)
{
char ch = ';';
int start = 0;
int next = inCSVStr.Find(ch,start); if(next < 0) return *this;
m_strIdent = inCSVStr.Left(next);

CSteinSatz satz(inCSVStr.Mid(next+1));
AddPosition(satz);
return *this;
}
//----------------------------------------------------------------------------
CAuftrag& CAuftrag::AddPosition(CSteinSatz& satz)
{
m_Positionen.Add(satz);
return *this;
}
//----------------------------------------------------------------------------
