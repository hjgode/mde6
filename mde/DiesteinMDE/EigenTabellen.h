#pragma once

//****************************************************************************
#define DATEI_ARTIKELGRUPPEN    _T("Artikelgruppen.txt")
#define DATEI_MATERIALGRUPPEN   _T("Materialgruppen.txt")
#define DATEI_MATERIAL          _T("Materialarten.txt")
#define DATEI_OBERFLAECHE       _T("Oberflaechen.txt")
#define DATEI_LAGER             _T("Lagerorte.txt")
#define DATEI_LAGERMAT          _T("LagerorteM.txt")
#define DATEI_LIEFERANTEN       _T("Lieferanten.txt")
#define DATEI_EINHEITEN         _T("Mengeneinheiten.txt")
#define DATEI_PREISLISTEN       _T("Preislisten.txt")
#define DATEI_FEHLERBEZEICHNUNG _T("Fehlerbezeichnung.txt")
#define DATEI_GATTERDATEN		_T("Gatterdaten.txt")
#define DATEI_LAGERORIGINALSTATUS		_T("LagerDatum.txt")
//----------------------------------------------------------------------------
class C2String
{
public:
    CString m_key;
    CString m_bez;

    void operator=(const C2String& s2);
    void Reset();

    C2String& Set(const CString& strkey,const CString& strbez);
    CString GruppenKey() const;     // Erster Teil von key
    CString Key2() const;           // Zweiter Teil von key
};
//----------------------------------------------------------------------------
class C3String
{
public:
    CString m_key;
    CString m_value1;
    CString m_value2;

    void operator=(const C3String& s3);
    void Reset();

    C3String& Set(const CString& strkey,const CString& strval1,const CString& strval2);
};
//----------------------------------------------------------------------------
class C4String
{
public:
	CString m_key;
	CString m_value1;
	CString m_value2;
	CString m_value3;

	void operator=(const C4String& s4);
    void Reset();

    C4String& Set(const CString& strkey,const CString& strval1,const CString& strval2,const CString& strval3);
};
//----------------------------------------------------------------------------
class C2StringTabelle : public CArray<class C2String,const class C2String&>
{
public:
    int m_curSelected;

    C2StringTabelle();

    void operator=(const C2StringTabelle& s2);
    void Reset();

    BOOL Read(const TCHAR *folder,const TCHAR *datnam);
    void SetCombo(CComboBox& ctrlComboBox,CString& strCombo);
    void SetComboKey2AndBez(CComboBox& ctrlComboBox,CString& strRet);
    int GetIndexByKey(const TCHAR *key) const;
    int GetIndexByValue(const TCHAR *value,bool compareCase=false) const;
    C2String GetItemByKey(const TCHAR *key) const;
    C2String GetItemByValue(const TCHAR *value,bool compareCase=false) const;
    int SetGruppe(const C2StringTabelle& src,const TCHAR *grKey);
    CString GruppenKey(int index) const;   // Erster Teil
    CString Key2(int index) const;     // Zweiter Teil
    C2String Selected() const {return GetAt(m_curSelected);}

    void Debug() const;
};
//----------------------------------------------------------------------------
class C3StringTabelle : public CArray<class C3String,const class C3String&>
{
public:

    C3StringTabelle();

    void operator=(const C3StringTabelle& s3);
    void Reset();

    BOOL Read(const TCHAR *folder,const TCHAR *datnam);
    void Save(const TCHAR *folder,const TCHAR *dateiname);

    int GetIndexByKey(const TCHAR *key) const;
    C3String GetItemByKey(const TCHAR *key) const;

    void Debug() const;
};
//----------------------------------------------------------------------------
class C4StringTabelle : public CArray<class C4String,const class C4String&>
{
public:
	C4StringTabelle();

	void operator=(const C4StringTabelle& s4);
    void Reset();

    BOOL Read(const TCHAR *folder,const TCHAR *datnam);
    void Save(const TCHAR *folder,const TCHAR *dateiname);

    int GetIndexByKey(const TCHAR *key) const;
    C4String GetItemByKey(const TCHAR *key) const;

    void Debug() const;
};
//----------------------------------------------------------------------------
class CArtikelGruppen : public C2StringTabelle
{
public:
    void operator=(const CArtikelGruppen& l2);

    BOOL Read();
    
    BOOL IsRohPlattenGruppe(const CString& strGr) const;
	BOOL IsRohBlockGruppe(const CString& strGr) const;
};
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
class CMaterialGruppen : public C2StringTabelle
{
public:
    void operator=(const CMaterialGruppen& l2);

    BOOL Read();
};
//----------------------------------------------------------------------------
class CMaterialTabelle : public C2StringTabelle
{
public:
    void operator=(const CMaterialTabelle& l2);

    int GetIndexByKey(const TCHAR *art,const TCHAR *nr) const;
    C2String GetItemByKey(const TCHAR *art,const TCHAR *nr) const;

    BOOL Read();
};
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
class COberflTabelle : public C2StringTabelle
{
public:
    void operator=(const COberflTabelle& l2);

    int GetIndexByKey(const TCHAR *art,const TCHAR *nr) const;
    C2String GetItemByKey(const TCHAR *art,const TCHAR *nr) const;

    BOOL Read();
};
//----------------------------------------------------------------------------
class CLagerTabelle : public C2StringTabelle
{
public:
    void operator=(const CLagerTabelle& l2);

    BOOL Read();
};
//----------------------------------------------------------------------------
class CLagerMatTabelle : public C3StringTabelle
{
public:
    void operator=(const CLagerMatTabelle& tab3);

    BOOL Read();
};
//----------------------------------------------------------------------------
class CLieferantenTabelle : public C2StringTabelle
{
public:
    void operator=(const CLieferantenTabelle& l2);

    BOOL Read();
};
//----------------------------------------------------------------------------
class CEinheitenTabelle : public C2StringTabelle
{
public:
    void operator=(const CEinheitenTabelle& l2);

    BOOL Read();
};
//----------------------------------------------------------------------------
class CFehlerbezeichnungTabelle : public C2StringTabelle
{
public:
    void operator=(const CFehlerbezeichnungTabelle& l2);

    BOOL Read();
};
//----------------------------------------------------------------------------
class CPreislistenTabelle : public C3StringTabelle
{
public:
    void operator=(const CPreislistenTabelle& l3);

    BOOL Read();
};
//----------------------------------------------------------------------------
class CGatterdatenTabelle : public C4StringTabelle
{
public:
    void operator=(const CGatterdatenTabelle& l4);

    BOOL Read();
};
class CLagerOriginalStatusTabelle : public C2StringTabelle
{
public:
    void operator=(const CLagerOriginalStatusTabelle& tab3);

    BOOL Read();
};
//----------------------------------------------------------------------------
// Dient zum Speichern von Programmeinstellungen, die nach Programmende gespeichert
// bleiben sollen (Freie Schlüsselwahl)
//----------------------------------------------------------------------------
class CProgrammStatusTabelle : public C3StringTabelle
{
public:
    void operator=(const CProgrammStatusTabelle& tab3);

    BOOL Read();
    void Save();
};


