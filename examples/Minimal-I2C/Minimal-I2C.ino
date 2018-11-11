/*
   --------------------------------------------------------------------------------------------------------------------
   Example sketch/program showing how to read data from a PICC to serial.
   --------------------------------------------------------------------------------------------------------------------
   This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid

   Example sketch/program showing how to read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
   Reader on the Arduino SPI interface.

   When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
   then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
   you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
   will show the ID/UID, type and any data blocks it can read. Note: you may see "Timeout in communication" messages
   when removing the PICC from reading distance too early.

   @license Released into the public domain.

   Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro   Due/Mega2560
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     23         9
   scl	       CLK	    5		  5 		      3                                     22
   sda         SC 	    4		  4           2                                     21

*/
#include <MFRC522.h>

constexpr uint8_t RST_PIN = 2;          // Configurable, see typical pin layout above

// The default address of the MFRC522 is 0X3C -- specify it here if you
// have it configured differently (pull up/down pins on the chip).
//
// MFRC522_I2C mfrc522(RST_PIN, 0x28 /*, chipAddr */);  		// Create MFRC522 instance

TwoWire i2cBus = TwoWire(0);
MFRC522_I2C dev = MFRC522_I2C(RST_PIN, 0x28, i2cBus);
MFRC522 mfrc522 = MFRC522(dev);

void setup() {
  Serial.begin(115200);	// Initialize serial communications with the PC
  while (!Serial);		  // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  i2cBus.begin(5, 4, 400000); 

  mfrc522.PCD_Init();		// Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
  
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return; // no card in sight.
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    Serial.println("Bad read (was card removed too quickly?)");
    return;
  };
  
  if ( mfrc522.uid.size == 0) {
    Serial.println("Bad card read (size = 0)");
    return;
  }

  char buff[sizeof(mfrc522.uid.uidByte)* 5] = { 0 };
  for (int i = 0; i < mfrc522.uid.size; i++) {
    char tag[5]; // 3 digits, dash and \0.
    snprintf(buff, sizeof(buff), "%s%d", i ? "-" : "", mfrc522.uid.uidByte[i]);
    strncat(buff, tag, sizeof(tag));
  };
  Serial.println("Good scan: ");
  Serial.println(buff);

  // disengage with the card.
  //
  mfrc522.PICC_HaltA();
}

