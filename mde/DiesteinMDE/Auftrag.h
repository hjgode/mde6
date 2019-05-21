#pragma once

// Auftrag.h: interface for the CAuftrag class.
//
//////////////////////////////////////////////////////////////////////

class CSteinSatz;
class CSteinSaetze;

class CAuftrag  
{
public:
	CString m_strIdent;
	CSteinSaetze m_Positionen;

public:
	CAuftrag();
	CAuftrag(const CAuftrag& auf);
	CAuftrag(CString auftrName);
	virtual ~CAuftrag(){};

    void operator=(const CAuftrag& auf);
    CAuftrag& Create(CString inCSVStr);
    CSteinSatz& Position(int index) {return m_Positionen.SteinSatz(index);}
//    CSteinSatz& Position(CString steinNummer);
    CSteinSatz PositionConst(int index) const {return m_Positionen.arr[index];}
//	CAuftrag& AddPosition(const CSteinSatz& satz,CString& errMsg);
	CAuftrag& AddPosition(CSteinSatz& satz);  // Aktualisierung der Lagerliste
//    CAuftrag& SubPosition(const CSteinSatz& satz,CString& errMsg);
    CAuftrag& RemovePosition(CString strNummer);

};
