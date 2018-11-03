#ifndef MFRC522_I2C_H
#define MFRC522_I2C_H

#include <MFRC522_base.h>
#include <Wire.h>

#define MFRC522_I2C_DEFAULT_ADDR (0x3C)

class MFRC522_I2C : public MFRC522_BASE {
public:

        MFRC522_I2C(byte resetPowerDownPin = UNUSEDPIN, 
		byte chipAddress = MFRC522_I2C_DEFAULT_ADDR, TwoWire & wire = Wire)
                : _resetPowerDownPin(resetPowerDownPin),  _chipAddress(chipAddress), _wire(wire) {};

	void PCD_Init();
        void PCD_WriteRegister(PCD_Register reg, byte value);
        void PCD_WriteRegister(PCD_Register reg, byte count, byte *values);
        byte PCD_ReadRegister(PCD_Register reg);
        void PCD_ReadRegister(PCD_Register reg, byte count, byte *values, byte rxAlign = 0);

private:
	byte _resetPowerDownPin;	// Optional, soft-rest will be used if set to UNUSEDPIN
	byte _chipAddress;		// Default is 0x3C
	TwoWire & _wire;		// Bus, defaults to the first i2c bus: Wire;
};
#endif
