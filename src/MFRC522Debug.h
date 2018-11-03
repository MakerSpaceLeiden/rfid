#include <MFRC522.h>

#ifndef MFRC522Debug_h
#define MFRC522Debug_h

class MFRC522Debug {
private:
	
public:
	// Get human readable code and type
	static const __FlashStringHelper *PICC_GetTypeName(MFRC522_BASE::PICC_Type type);
	static const __FlashStringHelper *GetStatusCodeName(MFRC522_BASE::StatusCode code);
};
#endif // MFRC522Debug_h
