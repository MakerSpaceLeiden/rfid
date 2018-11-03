#ifndef MFRC522_H
#define MFRC522_H

#include <MFRC522_spi.h>
#include <MFRC522_i2c.h>
#include <MFRC522_base.h>

// Simple glue class to maintain backwards compatibility if no
// specific bus is specified. We default to the SPI bus.
//
// Also includes a legacy method which is prolly no longer
// used by anyone.
//
class MFRC522 : public MFRC522_SPI {

  void PCD_Init( byte chipSelectPin, byte resetPowerDownPin ) 
  {
        _chipSelectPin = chipSelectPin;
        _resetPowerDownPin = resetPowerDownPin;

        MFRC522_SPI::PCD_Init();
  };
};
#endif
