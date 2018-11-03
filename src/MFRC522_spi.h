#ifndef MFRC522_SPI_H
#define MFRC522_SPI_H

#include <MFRC522_base.h>
#include <SPI.h>

class MFRC522_SPI : public MFRC522_BASE {
public:
        MFRC522_SPI(const byte chipSelectPin, const byte resetPowerDownPin = UNUSED_PIN,
                        SPIClass *spiClass = &SPI, 
			const SPISettings spiSettings = SPISettings(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0))
                     : _chipSelectPin(chipSelectPin),
			_resetPowerDownPin(resetPowerDownPin),
                        _spiClass(spiClass), 
			_spiSettings(spiSettings) {};

	void PCD_Init();

	void PCD_WriteRegister(	PCD_Register reg, byte value);
	void PCD_WriteRegister(	PCD_Register reg, byte count, byte *values);

	byte PCD_ReadRegister(	PCD_Register reg);
	void PCD_ReadRegister(	PCD_Register reg, byte count, byte *values, byte rxAlign = 0);
protected:
	// Pins
	byte _chipSelectPin;		
	byte _resetPowerDownPin; // optional; software set is used when set to UNUSED_PIN.
	
	// SPI communication
	SPIClass *_spiClass;		// defaults to the first SPI bus.
	const SPISettings _spiSettings;	// SPI settings; defaults to a speed known to work.
};
#endif
