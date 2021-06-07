/**
 * Save and restore settings using EEPROM
 * 
 * EEPROM map
 *        0: version
 *        1: version revision
 *        2: trim shoulder servo
 *        3: trim elbow servo
 *        4: trim wrist servo
 *        5: trim wrist rotate servo
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
  for (int i = 2; i <= 5; i++) {
    EEPROM.write(i,128);  // Zeroes for trim
  }
  
  for (int i = 6; i < EEPROM.length(); i++) {
    EEPROM.write(i,0);
  }
}

void settingsLoad() {
  // TODO
}

double settingsUint8ToDouble(uint8_t value) {
  // This is for servo trimming, so the value of uint8_t is 0 to 255
  // can be converted to -0.25...+0.25 rad that should be enough for 
  // servo trimming, in other cases you are doing hardware wrong
  // (256 values with sign: 0 to 255 -> -127...126 -> /500 and rad->deg -> -14.6...14.5 deg)
  return ((double)value-128)/500;
}

uint8_t settingsDoubleToUint8(double value) {
  // see settingsUint8ToDouble();
  if (value >=  SERVO_TRIM_LIMIT) value =  SERVO_TRIM_LIMIT;
  if (value <= -SERVO_TRIM_LIMIT) value = -SERVO_TRIM_LIMIT;
  
  return value*500+128;
}
