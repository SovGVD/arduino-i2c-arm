#ifdef ENABLE_TOF
const char grayRamp[] PROGMEM = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

char tofValueToChar(uint16_t value){
  uint8_t index = map(value, 0, 65536, 0, 69);

  return pgm_read_word_near(grayRamp + index);
}

void tofPrint()
{
  for (uint8_t i = 0; i < 256; i++) {
    if (i % 16) {
      cliSerial->println();
    }
    cliSerial->print(tofValueToChar(image[i]));
  }
  cliSerial->println();
}
#endif
