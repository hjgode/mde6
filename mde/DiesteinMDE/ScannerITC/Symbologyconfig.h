#pragma once
#include "afxwin.h"

//needed for configuration setup
#include "IS9CConfig.h"
#pragma comment (lib, "ITCUUID.lib")
#include "ITCADCMgmt.h"
#pragma comment (lib, "ITCAdcDevMgmt.lib")

// ********************************************************
// *                 SETUP GID                            *
// ********************************************************
#define SYM_FIRST 0x30
#define NUM_SYMBOLOGIES 37
#define SYM_ALL 0xff			//pseudo code to disable all

	  typedef enum tagGIDSETUP
{
  
   // Symbologies [0x30..0x3F] postal codes
   GID_POSTNET          = 0x30,  // Postnet
   GID_PLANET           = 0x31,  // Planet
   GID_BPO              = 0x32,  // Code BPO
   GID_CANADAPOST       = 0x33,  // Canada post
   GID_AUSTRALIANPOST   = 0x34,  // Australia post
   GID_JAPANPOST        = 0x35,  // Japan post
   GID_DUTCHPOST        = 0x36,  // Dutch post
   GID_SWEDENPOST       = 0x37,  // Sweden post
   GID_KOREANPOST       = 0x38,  // Korean post
   GID_INFOMAIL         = 0x39,  // Infomail
   GID_INTELLIGENTMAIL  = 0x3A,  // IntelligentMail 

   // Symbologies [0x40..0x5F] 
   GID_CODABAR          = 0x40,  // Codabar
   GID_C93              = 0x41,  // Code 93
   GID_C39              = 0x42,  // Code 39
   GID_C128             = 0x43,  // Code 128/EAN128
   GID_ITF              = 0x44,  // Interleaved 2 of 5
   GID_25M              = 0x45,  // Matrix 2 of 5 
   GID_MSI              = 0x46,  // Code MSI
   GID_PLS              = 0x47,  // Code Plessey
   GID_25S              = 0x48,  // Standard 2 of 5
   GID_TLP              = 0x49,  // Code Telepen
   GID_C11              = 0x4A,  // Code 11
   GID_UPC              = 0x4B,  // Code EAN/UPC
   GID_PDF              = 0x4C,  // Code PDF417
   GID_CDB              = 0x4D,  // Codablock
   GID_TLC39            = 0x4E,  // Code TLC 39
   GID_GS1              = 0x4F,  // Code GS1 DataBar (AKA RSS)
   GID_C49              = 0x50,  // Code 49
   GID_C16K             = 0x51,  // Code 16K
   GID_MAXICODE         = 0x52,  // Code Maxicode
   GID_AZTEC            = 0x53,  // Code Aztec
   GID_DTM              = 0x54,  // Code Datamatrix
   GID_QR               = 0x55,  // Code QR
   GID_EUCOMPOSITE      = 0x56,  // Codes EAN.UCC Composite
   GID_BCC412           = 0x58,  // Code BCC 412
   GID_UDMC             = 0x59,  // Multicode
   GID_HANXIN           = 0x5A,  // Hanxin
} GIDSETUP;

#define SYM_CODE39 GID_C39
#define SYM_DATAMATRIX GID_DTM
#define SYM_EAN13 GID_UPC
#define SYM_QR GID_QR

void decEnableDisableSymbology(int, BOOL);
void decSetSymbologyDefaults(int);