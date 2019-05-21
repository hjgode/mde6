// DlgTest.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "DlgTest.h"


// CDlgTest-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgTest, CDialog)

CDlgTest::CDlgTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTest::IDD, pParent)
{

}

CDlgTest::~CDlgTest()
{
}

void CDlgTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STEINSAETZE, m_ctrlListSteinSaetze);
}


BEGIN_MESSAGE_MAP(CDlgTest, CDialog)
END_MESSAGE_MAP()

//----------------------------------------
class CEinfach
{
public:
	int i;
	CString str;

	CEinfach(){i = 0;}				// Default-Konstruktor
	CEinfach(const CEinfach& ein);	// Kopier-Konstruktor
	CEinfach(const CString& s,int ix = 0);
	~CEinfach(){}					// Destruktor

	void operator=(const CEinfach& ein);
};
//----------------------------------------
CEinfach::CEinfach(const CEinfach& ein)
{
	*this = ein;
}
//----------------------------------------
void CEinfach::operator=(const CEinfach& ein)
{
	i = ein.i;
	str = ein.str;
}
//----------------------------------------
CEinfach::CEinfach(const CString& s,int ix)
{
	i = ix;
	str = s;
}

//---------------------------------------------------
class CNummern
{
	BOOL modified;
public:
	CArray <CSteinSatz, const CSteinSatz&> arr;
	CNummern();
	CNummern(const CNummern& num);

	BOOL Modified() const {return modified;}

	void operator=(const CNummern& num);
};
//-----------------------------------------------------
CNummern::CNummern()
{
	modified = FALSE;
}
//-----------------------------------------------------
CNummern::CNummern(const CNummern& num)
{
	*this = num;
}
//-----------------------------------------------------
void CNummern::operator=(const CNummern& num)
{
	CArray::RemoveAll();
	modified = num.modified;
	CArray::Append(num);
}
//------------------------------------------------------
BOOL CDlgTest::OnInitDialog()
{
CDialog::OnInitDialog();

// CArray <CSteinSatz, const CSteinSatz&> Nummern;
CNummern Nummern;
CEinfach ein;
CEinfach ein1(_T("Dies ist.."));
CEinfach ein2(_T("Dies ist.."),5);


for ( int i = 0 ; i < m_pSaetze->Anzahl (); i++ )
{
	m_ctrlListSteinSaetze.AddString(m_pSaetze->SteinSatz(i).m_value );
	Nummern.Add (m_pSaetze->SteinSatz(i));
}

CSteinSatz x;
x = Nummern.GetAt (22);

CNummern n1;

n1 = Nummern;
MessageBox( CSteinSatz::DoubleToString (Nummern.GetCount ()) );

//CSteinSaetze &saetze = *m_pSaetze;
//for (int i = 0; i < saetze.Anzahl (); i++ )
//{
//	m_ctrlListSteinSaetze.AddString (saetze.SteinSatz (i).m_value );
//}

return TRUE;  // return TRUE  unless you set the focus to a control
}

// CDlgTest-Meldungshandler


