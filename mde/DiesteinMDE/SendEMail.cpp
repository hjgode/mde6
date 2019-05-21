// SendEMail.cpp : Definiert die Initialisierungsroutinen für die DLL.
//

#include "stdafx.h"
#include "cstools4.h"
#include "SendEMail.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
// Einsprungpunkt
//---------------------------------------------------------------------------------------------
BOOL EMAIL_Send(
                 const TCHAR *strFrom,
                 const TCHAR *strTo,
                 const TCHAR *strBcc,       // kann NULL oder "" sein
                 const TCHAR *strCc,        // kann NULL oder "" sein
                 const TCHAR *strSubject,   // kann NULL oder "" sein
                 const TCHAR *strMessage,   // kann NULL oder "" sein
                 const TCHAR *strAttachment,// kann NULL oder "" sein
                 const TCHAR *strHostName,
                 UINT nHostPort,            // kann 0 sein
                 const TCHAR *strUserName,  // kann NULL oder "" sein
                 const TCHAR *strPassword,  // kann NULL oder "" sein
                 BOOL bAuthenticate,
                 TCHAR *strError)           // Receive String

{

if (!MimeInitialize(_T("DKHLQKCTJOHBMVNF"), NULL) ||
	!SmtpInitialize(_T("DKHLQKCTJOHBMVNF"), NULL))    //CSTOOLS4_LICENSE_KEY
    {
    _tcscpy(strError,_T("Falscher Lizenzkey"));
    return FALSE;
    }

CSendEMail myEmail(strFrom,strTo,strBcc,strCc,strSubject,strMessage,strAttachment,
                   strHostName,nHostPort,strUserName,strPassword,bAuthenticate);
myEmail.Send(); 
_tcscpy(strError,myEmail.m_strError);

MimeUninitialize();
SmtpUninitialize();

if(myEmail.m_strError.IsEmpty())
    return TRUE;
return FALSE;
}
//---------------------------------------------------------------------------------------------
CSendEMail::CSendEMail(
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
                     BOOL bAuthenticate)
{
m_strFrom = strFrom;
m_strTo = strTo;
if(strBcc) m_strBcc = strBcc;   // kann NULL sein
if(strCc)  m_strCc = strCc;
if(strSubject) m_strSubject = strSubject;
if(strMessage) m_strMessage = strMessage;
if(strAttachment) m_strAttachment = strAttachment;
m_strHostName = strHostName;
m_nHostPort = nHostPort;
if(!nHostPort) m_nHostPort = SMTP_PORT_DEFAULT;
if(strUserName) m_strUserName = strUserName;
if(strPassword) m_strPassword = strPassword;
m_bAuthenticate =  bAuthenticate;

m_hClient = INVALID_CLIENT;
m_hMessage = INVALID_MESSAGE;
m_bCanceled = FALSE;
}
//-----------------------------------------------------------------------------------
CSendEMail::~CSendEMail()
{
if(m_hClient != INVALID_CLIENT)
    {
	SmtpDisconnect(m_hClient);
	m_hClient = INVALID_CLIENT;
    }

if(m_hMessage != INVALID_MESSAGE)
    {
	MimeDeleteMessage(m_hMessage);
	m_hMessage = INVALID_MESSAGE;
    }
}
//-------------------------------------------------------------------------------		
void CSendEMail::ShowError(DWORD dwError)
{
TCHAR szError[128];

*(szError) = 0;

if(dwError == 0)
	dwError = GetLastError();

// Because the error codes all shared between all of the
// SocketTools libraries, the descriptions are the same,
// regardless of what function actually generated the error

if((MimeGetErrorString(dwError,szError,126)) == 0)
	m_strError.Format(_T("Unknown SocketTools error 0x%08lX"),dwError);
else
    m_strError = szError;

m_strError = _T("Errortest");
//AfxMessageBox(m_strError,MB_OK|MB_ICONEXCLAMATION);
}

// This event handler function is called as the message is being
// submitted to the mail server

//void CALLBACK CSendMailDlg::EventHandler(HCLIENT hClient, UINT nEventId, DWORD dwError, DWORD dwParam)
//{
//	CSendMailDlg *pThis = (CSendMailDlg *)dwParam;
//
//	if (pThis == NULL)
//		return;
//	
//	SMTPTRANSFERSTATUS smtpStatus;
//	INT nResult = SmtpGetTransferStatus(hClient, &smtpStatus);
//
//	if (nResult != SMTP_ERROR && smtpStatus.dwBytesTotal > 0)
//	{
//		INT nPercent = (INT)((DOUBLE)(100.0 * (DOUBLE)smtpStatus.dwBytesCopied / (DOUBLE)smtpStatus.dwBytesTotal));
//		if (nPercent > 100)
//			nPercent = 100;
//
//		pThis->m_ctlProgress.SetPos(nPercent);
//		pThis->m_ctlProgress.RedrawWindow();
//	}		
//
//	TCHAR szStatus[256];
//
//	wsprintf(szStatus, _T("Submitting message to server %lu/%lu"),
//			 smtpStatus.dwBytesCopied, smtpStatus.dwBytesTotal);
//
//	pThis->m_ctlStatus.SetWindowText(szStatus);
//	pThis->m_ctlStatus.RedrawWindow();
//}

void CSendEMail::Send() 
{
BOOL bResult;
int nResult;

// Compose the message based on the input provided by the user
m_hMessage = MimeComposeMessage(
	                            m_strFrom,
	                            m_strTo,
	                            m_strCc,
	                            m_strSubject,
	                            m_strMessage,
	                            NULL,
	                            MIME_CHARSET_ISOLATIN1,
	                            MIME_ENCODING_8BIT
	                            );

if(m_hMessage == INVALID_MESSAGE)
    {
	ShowError();
	return;
    }

// If a file attachment was specified, then attach it to the
// message that was created

CStringArray strArr;
int start = 0;
CString str = m_strAttachment.Tokenize(_T(";,"),start);
while(!str.IsEmpty())
    {
    str.Trim();
    strArr.Add(str);
    str = m_strAttachment.Tokenize(_T(";,"),start);
    }

for(int i = 0; i < strArr.GetCount(); i++)
    {
    if(strArr.GetAt(i).GetLength() > 0)
        {
	    bResult = MimeAttachFile(m_hMessage,strArr.GetAt(i),MIME_ATTACH_BASE64);
	    if(!bResult)
	        {
		    ShowError();
		    return;
	        }
        }
    }

// Get the contents of the complete message, including the headers,
// main message body and optional file attachment data; it will be
// returned a global memory handle

HGLOBAL hgblMessage = NULL;
DWORD dwMessageSize = 0;

bResult = MimeExportMessageEx(
	                            m_hMessage,
	                            MIME_EXPORT_HGLOBAL, 
	                            MIME_OPTION_DEFAULT,
	                            &hgblMessage,
	                            &dwMessageSize);

if(!bResult)
    {
	ShowError();
	return;
    }

// Parse the sender email address to make sure that we only have
// the actual address, not their name, etc.

TCHAR szSender[256];
MimeParseAddress(m_strFrom, NULL, szSender, 256);

// Create a list of all of the recipient addresses; we will use
// this when submitting the message to the SMTP server

LPTSTR lpszRecipients = NULL;
DWORD cchRecipients = 0;
INT nRecipients = 0;

// Determine the number of characters that should be allocated to store
// all of the addresses in the current message

nRecipients = MimeEnumMessageRecipients(
	                                    m_hMessage,
	                                    m_strBcc,
	                                    NULL,
	                                    &cchRecipients);

// Allocate the memory for the string buffer that will contain all
// of the recipient addresses and call MimeEnumMessageRecipients
// again to store those addresses in the buffer

if((nRecipients > 0) && (cchRecipients > 0))
    {
	lpszRecipients = (LPTSTR)LocalAlloc(LPTR,cchRecipients*sizeof(TCHAR));
	if(lpszRecipients == NULL)
		return; // Virtual memory exhausted

	nRecipients = MimeEnumMessageRecipients(
		                                    m_hMessage,
		                                    m_strBcc,
		                                    lpszRecipients,
		                                    &cchRecipients);
    }

if(nRecipients == 0)
    {
	AfxMessageBox(_T("kein Empfänger"), MB_ICONEXCLAMATION);
	return;
    }
else
    {
	TCHAR *lpszAddress = lpszRecipients;
	int cchAddress;

	while(lpszAddress != NULL)
	    {
		if((cchAddress = (int)_tcslen(lpszAddress)) == 0)
			break;

		// Change the null characters which separate each address
		// into commas, creating a comma-separated list of addresses

		if (*(lpszAddress + cchAddress + 1) != '\0')
			*(lpszAddress + cchAddress) = ',';

		lpszAddress += cchAddress + 1;
	    }
    }

	// Connect to the SMTP server that was specified by the user

m_hClient = SmtpConnect(
	                    m_strHostName,
	                    m_nHostPort,
	                    10,//SMTP_TIMEOUT, 
	                    SMTP_OPTION_EXTENDED,
	                    NULL,
	                    NULL);

if(m_hClient == INVALID_CLIENT)
    {
	ShowError();
	return;
    }		


// If the user has checked the 'requires authentication' checkbox,
// then authenticate the client session with the server

if(m_bAuthenticate)
    {
	BOOL bExtended;
	DWORD dwOptions;
	INT nResult;

	// Determine if this server really does support extended
	// options, and if it does, what they are

	bExtended = SmtpGetExtendedOptions(m_hClient, &dwOptions);

	if(bExtended && (dwOptions & SMTP_EXTOPT_AUTHLOGIN))
	    {
		nResult = SmtpAuthenticate(
			m_hClient,
			SMTP_AUTH_DEFAULT,
			m_strUserName,
			m_strPassword);

		if(nResult == SMTP_ERROR)
		    {
			// Display a friendly error message here if the user could
			// not be authenticated; some SMTP servers can return rather
			// cryptic messages
			m_strError = _T("Falscher Authorisierungskode");
			return;
		    }
	    }
	else
	    {
		// This server doesn't support authentication; the user needs
		// to clear the checkbox and try again
		m_strError = _T("Kein Authorisierungskode");
		return;
	    }
    }

// Register a handler for the SMTP_EVENT_PROGRESS event so that
// we can update the progress bar control; note that since the
// event handler is static, we pass the 'this' pointer as the
// optional parameter and then use that in the handler

//nResult = SmtpRegisterEvent(
//	                        m_hClient,
//	                        SMTP_EVENT_PROGRESS,
//	                        EventHandler,
//	                        (DWORD)this);
//
//if(nResult == SMTP_ERROR)
//    {
//	ShowError();
//	return;
//    }


nResult = SmtpSendMessage(
	                        m_hClient,
	                        szSender,
	                        lpszRecipients,
	                        hgblMessage,
	                        dwMessageSize,
	                        SMTP_MESSAGE_HGLOBAL);

// Free memory allocated for the message
GlobalFree(hgblMessage);

if(nResult == SMTP_ERROR)
    {
	DWORD dwError = SmtpGetLastError();

	if(dwError != ST_ERROR_NO_VALID_RECIPIENTS)
		ShowError();
	else
	    {
		// If the error is ST_ERROR_NO_VALID_RECIPIENTS the server is
		// probably rejecting the message because its being asked to
		// relay a message to a user outside of its domain, and the client
		// session has not been authenticated.

		// Display a helpful error message, disconnect from the server
		// and allow the user to try again, rather than closing the
		// dialog

		m_strError = _T("Ungültiger Empfänger");

		SmtpDisconnect(m_hClient);
		m_hClient = INVALID_CLIENT;

		MimeDeleteMessage(m_hMessage);
		m_hMessage = INVALID_MESSAGE;
		return;
	    }
    }
else
    {
//	AfxMessageBox(_T("Email-Versand erfolgreich"),MB_ICONINFORMATION);
    }
}
