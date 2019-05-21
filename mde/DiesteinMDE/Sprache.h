#pragma once

class MDEStringArray;
//------------------------------------------------------------------------
class CSprache  
{
public:
  	CSprache();
  	~CSprache(){};

  	CString m_pathFileName;

  	CString m_germanKey;        // "D  "
  	CString m_strangeKey;       // Schlüssel der Zielsprache
  	CString m_defaultKey;       // Falls bei Zielsprache keine übersetzung gefunden wird, diese Sprache probieren, ansonsten deutsch

    MDEStringArray m_arrGerman;
    MDEStringArray m_arrStrange;

    void Reset();

    int Read();

    // Übersetzungsfunktionen
    CString Translate(const CString &german);
    CString Translate(const CString &german1,const CString& c1,const CString& german2);
    CString Translate(const CString &german1,int zahl,const CString& german2);
    CString Translate(const CString &german1,const CString& c1,const CString& german2,const CString& c2,const CString& german3);
    CString Translate(const CString &german1,int zahl1,const CString& german2,int zahl2,const CString& german3);
    CString TranslateSK(const CString &german,const CString& keys,CString& keyRet);

    void Debug(int i) const;

protected:
    CString TranslateSub(const CString &german);   // Direktübersetzung nach Aufbereitung
    BOOL BorderSignLeft(TCHAR sign);
    BOOL BorderSignRight(TCHAR sign);
};

