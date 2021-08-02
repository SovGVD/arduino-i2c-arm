#ifdef ENABLE_TOF
// TODO
//const char grayRamp[70] PROGMEM = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
const char grayRamp[10] PROGMEM = " .:-=+*#%@";

char tofValueToChar(uint16_t value, uint16_t vmin = 0, uint16_t vmax = 65536){
  uint8_t index = 9 - map(value, vmin, vmax, 0, 9);

  return pgm_read_word_near(grayRamp + index);
}

void tofPrint()
{
  if (!tofReady) {
    cliSerial->println("error");
    return;
  }

  cliSerial->print(">");
  for (uint8_t imgIdx = 0; imgIdx < 16; imgIdx++) {
    cliSerial->print(char(imgIdx+65));
  }
  tofVMin = 65536;
  tofVMax = 0;
  for (uint8_t imgIdx = 0; imgIdx < 255; imgIdx++) {
    if (image[imgIdx] > tofVMax) tofVMax = image[imgIdx];
    if (image[imgIdx] < tofVMin) tofVMin = image[imgIdx];
  }
  for (uint8_t imgIdx = 0; imgIdx < 255; imgIdx++) {
    if (imgIdx % 16 == 0) {
      cliSerial->println();
      cliSerial->print(char(imgIdx / 16 + 65));
    }
    cliSerial->print(tofValueToChar(image[imgIdx], tofVMin, tofVMax));
  }
  cliSerial->println();
}
#endif
