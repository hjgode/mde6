#pragma once

class COptionen
    {
    public:
        COptionen(void);
        ~COptionen(void){};
 
 public:
    CString m_strIni;

    void ReadIni();

    // Grundfunktionen zum akivieren der Buttons
    BOOL InfoEnabled() const;
    BOOL PreisinfoEnabled() const;
    BOOL VerkaufEnabled() const;
    BOOL LieferungEnabled() const;
    BOOL ProduktionEnabled() const;
    BOOL ReservierungEnabled() const;
    BOOL EinkaufEnabled() const;
    BOOL LagerUmEnabled() const;
    BOOL InventurEnabled() const;
    BOOL ZugangEnabled() const;
    BOOL OberflAendernEnabled() const;
    BOOL ContainerEnabled() const;

    // Spezialhandling
    BOOL MasseAendEnabled() const;
    BOOL RueckEnabled() const;
    int LastAufNrSupress() const;
    CString PVEnabled() const;
    BOOL PreislisteEnabled(int i) const;
    BOOL BoeseEnabled() const;
    BOOL BenutzerEnabled() const;
    BOOL SteinbruchEnabled() const;
    BOOL SteinbruchMassCheckDisabled() const;
    BOOL SteinbruchEmailDisabled() const;
	BOOL GatternEnabled() const;
	BOOL ProduktionMehrereAuftraegeEnabled() const;
	BOOL ZugangSteinnrVonBisEnabled() const;
	BOOL SteinbruchNettoGleichBruttoMasseEnabled() const;
	BOOL SteinbruchTagessummeAnzeigenEnabled() const;
	BOOL InventurPlattenOhneZusatzdatenErfassenEnabled() const;
	BOOL InventurRohplattenNichtDoppeltErfassenEnabled() const;

    };
