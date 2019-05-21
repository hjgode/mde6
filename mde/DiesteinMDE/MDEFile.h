// MDEFile.h: interface for the MDEFile class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

class MDEStringArray;
class CSteinSaetze;

class MDEFile : public CFile  
{
public:
	MDEFile();
	virtual ~MDEFile(){};

    int ReadStringArray(MDEStringArray& strArr);
    int ReadSteinSatzArray(CSteinSaetze& strArr);

    void WriteString(const CString& str);
};

