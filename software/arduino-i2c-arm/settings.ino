/**
 * Save and restore settings using EEPROM
 * 
 * EEPROM map
 *        0: version
 *        1: version revision
 */

#define EEPROM_VERSION 0x01
#define EEPROM_REV     0x01
#define EEPROM_OFFSET     2 // skip first value as it is version number

// TODO
// - check EEPROM data structure version
// - print setting to Serial


void initSettings() {
  settingsCheck();
  settingsLoad();
}

void settingsCheck() {
  if (EEPROM.read(0) == EEPROM_VERSION && EEPROM.read(1) == EEPROM_REV ) return;
  settingsInitEEPROM();
}

void settingsInitEEPROM() {
  // In some cases that can be moving data from one version to another
  Serial.println("Re-init EEPROM");
  delay(5000);
  EEPROM.write(0, EEPROM_VERSION);
  EEPROM.write(1, EEPROM_REV);
  for (int i = 2; i < 14; i++) {
    EEPROM.write(i,128);  // Zeroes for trim
  }
  
  for (int i = 15; i < EEPROM.length(); i++) {
    EEPROM.write(i,0);
  }
}

void settingsLoad() {
  // TODO
}
