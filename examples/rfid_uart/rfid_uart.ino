/*
 * This example simply changes the state of the LED_PIN based on a known tag code.
 * This code uses the NodeMCU (ESP-12E) layout for pin assignment.
 * Pin 16 is the LED next to the USB connector on the NodeMCU board.
 * Pin 2 is a generic GPIO (used here for initialization of RFID module).
 */

#include <MFRC522.h>

// Sample tag (assuming four bytes)
byte TEST_TAG[] = { 0x11, 0xBC, 0x4A, 0x10 };

// Tested on NodeMCU (ESP-12E)
const unsigned RST_PIN = 2;
const unsigned LED_PIN = 16;
const unsigned long RFID_POLLING_PERIOD_MS = 100;
unsigned long lastTimestamp = 0;

MFRC522_UART mfrc522(Serial, RST_PIN);
MFRC522 rfid(&mfrc522);

void setup() {
  pinMode(LED_PIN, OUTPUT);

  // RFID
  rfid.PCD_Init();
  rfid.PCD_SetAntennaGain(MFRC522::RxGain_max);
}

void loop(){

  unsigned long currentTimestamp = millis();
  if ((currentTimestamp - lastTimestamp) > RFID_POLLING_PERIOD_MS) {
    lastTimestamp = currentTimestamp;
    
    if (rfid.PICC_IsNewCardPresent()) {
      if (rfid.PICC_ReadCardSerial()) {

        // Compares the code obtained from a tag with our TEST_TAG
        if (memcmp(rfid.uid.uidByte, TEST_TAG, sizeof(TEST_TAG) / sizeof(byte)) == 0) {
          digitalWrite(LED_PIN, HIGH);
        } else {
          digitalWrite(LED_PIN, LOW);
        }
      }
    }
  }
}