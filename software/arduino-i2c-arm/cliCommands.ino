#ifdef ENABLE_CLI

double cliHelp()
{
  for (int i = 0; i < CLI_COMMANDS; i++) {
    cliSerial->print(cliCommands[i].commandName);
    cliSerial->print(" ");
    cliSerial->println(cliCommands[i].params);
  }
}

double cliI2cScan()
{
  #ifdef ENABLE_I2C_MULTIPLEXER
    cliSerial->print(CUR_I2C_MULTIPLEXER);
    cliSerial->print(" ch ");
  #endif
  cliSerial->println("i2c: ");
  for (byte i = 1; i < 127; i++) {
    Wire.beginTransmission (i);        // Begin I2C transmission Address (i)
    if (Wire.endTransmission () == 0)  // Receive 0 = success (ACK response) 
    {
      #ifdef ENABLE_I2C_MULTIPLEXER
        if (i == 112) {
          continue;
        }
      #endif
      cliSerial->print (i, DEC);
      cliSerial->print (" (0x");
      cliSerial->print (i, HEX);
      cliSerial->print ("), ");
    }
  }
  CUR_I2C_MULTIPLEXER++;
  if (CUR_I2C_MULTIPLEXER > 7) {
    CUR_I2C_MULTIPLEXER = 0;

    tcaselect(CUR_I2C_MULTIPLEXER);
    cliSerial->println("DONE");
  } else {
    tcaselect(CUR_I2C_MULTIPLEXER);
    cliSerial->println("");
    cliI2cScan();
  }
}

double cliInitEEPROM()
{
  settingsInitEEPROM();
}

double cliSetServoCalib() {
  uint8_t servoId = CLI_readInt();
  int ms = CLI_readInt();
  cliSerial->println(servoId);
  cliSerial->println(ms);
  setServoMs(servoId, ms);
}

#endif
