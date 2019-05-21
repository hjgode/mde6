// BestelleingangBuchungen.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "BestelleingangBuchungen.h"

/////////////////////////////////////////////////////////////////////////////
// CBestelleingangBuchungen dialog

IMPLEMENT_DYNAMIC(CBestelleingangBuchungen, CDialog)

CBestelleingangBuchungen::CBestelleingangBuchungen(CWnd* pParent /*=NULL*/)
	: CDialog(CBestelleingangBuchungen::IDD, pParent)
{
m_curSel = -1;
}


void CBestelleingangBuchungen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BESTELLEINGANG, m_ctrlListBestelleingang);
	DDX_Control(pDX, IDC_STATIC_STEINNUMMER, m_ctrlStaticSteinnummer);
	DDX_Control(pDX, IDC_STATIC_LAGER, m_ctrlStaticLager);
	DDX_Control(pDX, IDC_STATIC_BUCHUNGEN, m_ctrlStaticBuchungen);
	DDX_Control(pDX, IDC_BUTTON_ERASE, m_ctrlButtonErase);
}


BEGIN_MESSAGE_MAP(CBestelleingangBuchungen, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ERASE, OnButtonErase)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBestelleingangBuchungen message handlers
//---------------------------------------------------------------------------------------
BOOL CBestelleingangBuchungen::OnInitDialog()
{
CDialog::OnInitDialog();

CenterWindow(GetDesktopWindow());	// center to the hpc screen

TranslateStatic(m_ctrlStaticBuchungen);
TranslateStatic(m_ctrlStaticSteinnummer);
TranslateStatic(m_ctrlStaticLager);
TranslateButton(m_ctrlButtonErase);

m_pTabLager->Read();

int iarr[]={40};
m_ctrlListBestelleingang.SetTabStops(1,iarr);

SetListe(&m_pAuftraege->Auftrag(0));

return TRUE;
}
//-------------------------------------------------------------------------------------------
void CBestelleingangBuchungen::SetListe(CAuftrag *pAuftrag)
{
for(int i = 0; i < pAuftrag->m_Positionen.Anzahl(); i++)
    {
    SSatz ss(pAuftrag->m_Positionen.SteinSatzConst(i));
    CString str;
    CString strLager;
    int lix = m_pTabLager->GetIndexByKey(ss.m_Lager);
    if(lix >= 0)
        strLager.Format(_T("%s %s"),ss.m_Lager,m_pTabLager->GetAt(lix).m_bez);
    str.Format(_T("%s\t%s"),ss.m_Nummer,strLager);
    m_ctrlListBestelleingang.AddString(str);
    }
}
//-------------------------------------------------------------------------------------------
void CBestelleingangBuchungen::OnButtonErase() 
{
int m_curSel = m_ctrlListBestelleingang.GetCurSel();
if(m_curSel < 0) return;

CAuftrag& Auf = m_pAuftraege->Auftrag(0);

SSatz ssAuf(Auf.PositionConst(m_curSel));

BOOL changeLager = TRUE;
for(int i = m_curSel+1; i < Auf.m_Positionen.Anzahl(); i++)   // Wenn  weiter hinten nochmal zugeordnet, in den Steinsätzen nichts machen
    {
    if(ssAuf.m_Nummer.Compare(Auf.Position(i).Nummer()) == 0)
        {
        changeLager = FALSE;
        break;
        }
    }

if(changeLager)
    {
    CString oldlager;
    for(int i = m_curSel-1; i >= 0; i--)   // Wenn allerdings vorher schonmal zugeordnet, dies Zuordnung wiederherstellen
        {
        if(ssAuf.m_Nummer.Compare(Auf.Position(i).Nummer()) == 0)
            {
            SSatz ssold(Auf.Position(i));
            oldlager = ssold.m_Lager;
            break;
            }
        }

    int six;
    if(m_pContSteinSaetze->FoundAt(ssAuf.m_Nummer,six))    // In den Steinsätzen Lager auf leer oder oldlager
        {
        CSteinSatz& satz = m_pContSteinSaetze->SteinSatz(six);
        SSatz ss(satz);
        ss.m_Lager = oldlager;
        satz.Set(ss);
        }
    }

m_ctrlListBestelleingang.DeleteString(m_curSel);            // Aus Liste entfernen
Auf.m_Positionen.RemoveAt(m_curSel);                // Aus Auftrag entfernen

if(m_curSel >= Auf.m_Positionen.Anzahl())
    m_curSel--;

if(m_curSel >= 0)
    m_ctrlListBestelleingang.SetCurSel(m_curSel);
}
