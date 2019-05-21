// DiesteinMDEDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "DiesteinMDE.h"
#include "DiesteinMDEDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDiesteinMDEDlg-Dialogfeld

CDiesteinMDEDlg::CDiesteinMDEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDiesteinMDEDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDiesteinMDEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDiesteinMDEDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDiesteinMDEDlg-Meldungshandler

BOOL CDiesteinMDEDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen
	
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CDiesteinMDEDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	DRA::RelayoutDialog(
		AfxGetInstanceHandle(), 
		this->m_hWnd, 
		DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_DIESTEINMDE_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_DIESTEINMDE_DIALOG));
}
#endif

