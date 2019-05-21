#include "stdafx.h"
#include "Symbologyconfig.h"

#define MAX_REPLY_BUFF 64

void decEnableDisableSymbology(int iSymID, BOOL bEnable){
	DEBUGMSG(1, (L"decEnableDisableSymbology called %i, 5i\n"));
	//enable/disable hardware trigger
	BYTE rgbCommand[]={0x53, 0x40, 0x01}; // 53 is the symbology GID, second byte is always 0x40 and third is enable/disable
	//set symID
	int nSymId=0;
	rgbCommand[0]=iSymID;
	//set enable / disable
	if(bEnable)
		rgbCommand[2]=0x01;
	else
		rgbCommand[2]=0x00;

	HRESULT hr;
	BYTE rgbReplyBuff[MAX_REPLY_BUFF];
	DWORD dwReplyBuffSize=MAX_REPLY_BUFF;
	IS9CConfig3 *myIS9CConfig;
	HRESULT hrStatus = ITCDeviceOpen( TEXT("default"), IID_IS9CConfig3, ITC_DHDEVFLAG_NODATA, (LPVOID *) &myIS9CConfig );
	if( SUCCEEDED(hrStatus) )
	{
		if(iSymID == SYM_ALL)
		{
			for (iSymID=SYM_FIRST; iSymID < NUM_SYMBOLOGIES; iSymID++)
			{
				rgbCommand[0]=iSymID;
				hr = myIS9CConfig->ISCPSetConfig(
									rgbCommand,
									(DWORD)sizeof(rgbCommand),
									rgbReplyBuff,
									MAX_REPLY_BUFF,
									&dwReplyBuffSize
									);

			}
		}
		else{
			hr = myIS9CConfig->ISCPSetConfig(
								rgbCommand,
								(DWORD)sizeof(rgbCommand),
								rgbReplyBuff,
								MAX_REPLY_BUFF,
								&dwReplyBuffSize
								);
		}
		//ITCDeviceClose(&myIS9CConfig);
	}//succeeded		
}

 void decSetSymbologyDefaults(int iSymID){
	 //we do not have defaults within these classes
	 //we could load SmartSystems and then ...
 }
 