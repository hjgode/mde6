// MDEStringArray.h: interface for the MDEStringArray class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

class MDEStringArray : public CStringArray  
{
public:
	MDEStringArray();
	virtual ~MDEStringArray(){};

    int GetCount() const {return GetSize();}
    BOOL FoundAt(const CString& str,int& ix);
    void Sort(BOOL sortDown=FALSE,BOOL compareNoCase=FALSE);
    void Swap(int i,int j);
};

