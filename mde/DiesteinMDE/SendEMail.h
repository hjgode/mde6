// SendEMail.h : Hauptheaderdatei für die SendEMail DLL
//

#pragma once


//*********************************************************************************
//*********************************************************************************
class CSendEMail
{
public:
	CString m_strFrom;
	CString m_strTo;
	CString m_strBcc;
	CString m_strCc;
	CString m_strSubject;
	CString m_strMessage;
	CString m_strAttachment;

	CString m_strHostName;
	UINT m_nHostPort;       // SMTP_PORT_DEFAULT;
	CString m_strUserName;
	CString m_strPassword;
	BOOL m_bAuthenticate;   // FALSE;
    CString m_strError;

private:
	HCLIENT m_hClient;
	HMESSAGE m_hMessage;
	BOOL m_bCanceled;
	void ShowError(DWORD dwError=0);
//	static void CALLBACK EventHandler(HCLIENT hClient, UINT nEventId, DWORD dwError, DWORD dwParam);
public:
    CSendEMail(
                 const TCHAR *strFrom,
                 const TCHAR *strTo,
                 const TCHAR *strBcc,
                 const TCHAR *strCc,
                 const TCHAR *strSubject,
                 const TCHAR *strMessage,
                 const TCHAR *strAttachment,
                 const TCHAR *strHostName,
                 UINT nHostPort,
                 const TCHAR *strUserName,
                 const TCHAR *strPassword,
                 BOOL bAuthenticate);
    ~CSendEMail();

    void Send();
};

