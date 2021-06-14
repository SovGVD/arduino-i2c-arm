#ifdef ENABLE_TOF
// TODO
const char grayRamp[70] PROGMEM = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

char tofValueToChar(uint16_t value){
  uint8_t index = map(value, 0, 65536, 0, 69);

  return pgm_read_word_near(grayRamp + index);
}

void tofPrint()
{
  cliSerial->print(">");
  for (uint8_t i = 0; i < 16; i++) {
    cliSerial->print(i+65);
  }
  for (uint8_t i = 0; i < 256; i++) {
    if (i % 16) {
      cliSerial->println();
      cliSerial->print(i/16+65);
    }
    cliSerial->print(tofValueToChar(image[i]));
  }
  cliSerial->println();
}
#endif
