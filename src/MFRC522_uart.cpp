#include <Arduino.h>
#include <MFRC522.h>

MFRC522_UART::MFRC522_UART(HardwareSerial &serial, byte resetPin)
	: _resetPowerDownPin(resetPin), _serialPort(serial) {}

bool MFRC522_UART::PCD_Init() {
  _serialPort.begin(9600, SERIAL_8N1);

  if (_resetPowerDownPin != UNUSED_PIN) {
    pinMode(_resetPowerDownPin, OUTPUT);
    digitalWrite(_resetPowerDownPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_resetPowerDownPin, HIGH);
    delay(50);
    return true;
  }
  return false;
}

void MFRC522_UART::PCD_WriteRegister(MFRC522::PCD_Register reg, byte value) {
	_serialPort.write(0x7F & reg);
  	while (!_serialPort.available());
  	_serialPort.read();
	_serialPort.write(value);
}

void MFRC522_UART::PCD_WriteRegister(
  	MFRC522::PCD_Register reg, byte count, byte *values) {

	for (byte index = 0; index < count; ++index)
    	this->PCD_WriteRegister(reg, values[index]);
}

byte MFRC522_UART::PCD_ReadRegister(MFRC522::PCD_Register reg) {
	_serialPort.write(0x80 | reg);
	while (!_serialPort.available());
	byte value = _serialPort.read();
	return value;
}

void MFRC522_UART::PCD_ReadRegister(
  	MFRC522::PCD_Register reg, byte count, byte *values, byte rxAlign) {

	byte index = 0;
	if (rxAlign) {
		byte mask = 0xFF << rxAlign;
		byte value = this->PCD_ReadRegister(reg);
		values[0] = (values[0] & ~mask) | (value & mask);
		++index;
	}

	while (index < count) {
		values[index] = this->PCD_ReadRegister(reg);
		++index;
	}
}