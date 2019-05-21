/*==========================================================================

	HHPInfo - Hand Held Products Information Library

	
	UNLESS OTHER WISE AGREED TO BY HHP AND THE USER OF THIS CODE,
	THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
	ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
	THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
	PARTICULAR PURPOSE.

	COPYRIGHT (C) 2000 HAND HELD PRODUCTS, Inc.

	THIS SOFTWARE IS PROTECTED BY COPYRIGHT LAWS OF THE UNITED STATES OF 
	AMERICA AND OF FOREIGN COUNTRIES. THIS SOFTWARE IS FURNISHED UNDER A 
	LICENSE AND/OR A NONDISCLOSURE AGREEMENT AND MAY BE USED IN ACCORDANCE 
	WITH THE TERMS OF THOSE	AGREEMENTS. UNAUTHORIZED REPRODUCTION, 
	DUPLICATION OR DISTRIBUTION OF THIS SOFTWARE, OR ANY PORTION OF IT 
	WILL BE PROSECUTED TO THE MAXIMUM EXTENT POSSIBLE UNDER THE LAW.


	Description: 
	
	The HHPInfo library provides access to HHP vendor-specific information
	such as unit serial number and manufacturing date.
				
==========================================================================*/

#define TOUCHPANEL_TYPE_NONE			0
#define TOUCHPANEL_TYPE_INSTALLED		1

#define KEYBOARD_TYPE_UNDEFINED			0
#define KEYBOARD_TYPE_43KEY				1
#define KEYBOARD_TYPE_56KEY				2
#define KEYBOARD_TYPE_35KEY				3
#define KEYBOARD_TYPE_56CALCKEY			4

#define SCANNER_TYPE_UNKNOWN			-1
#define SCANNER_TYPE_NONE				0
#define SCANNER_TYPE_IT4200				1	// WelchAllyn IT4200 imager
#define SCANNER_TYPE_SE1200				2	// Symbol SE1200 non-decoded laser
#define SCANNER_TYPE_SE1223				3	// Symbol SE1223 decoded laser
#define SCANNER_TYPE_WAYFARER			4	// Wayfarer RF ID reader
#define SCANNER_TYPE_IT4000				5	// WelchAllyn IT4000 imager (IC Media mini-imager)
#define SCANNER_TYPE_IT4100				6
#define SCANNER_TYPE_IT4300				7

#define MODEL_NO_UNKNOWN				-1

#define DISPLAY_TYPE_UNKNOWN			0		// 7400
#define DISPLAY_TYPE_SAMSUNG			1		// 7400
#define DISPLAY_TYPE_DATAIMAGE			2		// 7400
#define DISPLAY_TYPE_NANYA				3		// 7400	monochrome
#define DISPLAY_TYPE_SHARP				16		// 9500
#define DISPLAY_TYPE_NANYA_9500			17		// 9500 monochrome

/* HHP manufacturing data and hardware information */
#define MANDATA_STRUCT_01				\
	DWORD size;							\
	TCHAR date[16];						\
	TCHAR serialNo[16];					\
	TCHAR partNo[16];					\
	DWORD hardwarerev;					\
	DWORD touchpaneltype;				\
	DWORD scannertype;					\
	DWORD modelNo;						\
	TCHAR CPLDVer[18];					\
	TCHAR specialPartNo[18];			\
	DWORD displaytype;					\
	DWORD BatterySerialNumber;			\
	DWORD KBType;						\
	DWORD KBmajor_version;				\
	DWORD KBminor_version;				\
	TCHAR KBversion_suffix[16];			\
	TCHAR processorname[40];

typedef struct 
{
MANDATA_STRUCT_01
} MANDATA;

/* HHP eboot version information */
#define EBOOTVER_STRUCT_01				\
	DWORD size;							\
	DWORD major_version;				\
	DWORD minor_version;				\
	TCHAR version_suffix[16];			\
	TCHAR version_time[16];         	\
    TCHAR version_date[16];         	

typedef struct  
{
EBOOTVER_STRUCT_01
} EBOOTVER;

/* HHP kernel version information */
#define KERNELVER_STRUCT_01				\
	DWORD size;							\
	DWORD major_version;				\
	DWORD minor_version;				\
	TCHAR version_suffix[16];			\
	TCHAR version_time[16];         	\
	TCHAR version_date[16];         

typedef struct 
{
KERNELVER_STRUCT_01
} KERNELVER;

/* HHP kernel, eboot, manufacturing and battery  information */
typedef struct  
{
	MANDATA		mandata;
	EBOOTVER	eboot;  
	KERNELVER	kernel;  
} HHPINFO;

/* Retrieve version info of library */
DWORD GetHHPInfoVersion();

/* Retrieve HHP kernel, eboot, manufacturing and battery information */
BOOL GetHHPInfo(MANDATA *pManData, EBOOTVER *pEboot, KERNELVER *pKernel);			
