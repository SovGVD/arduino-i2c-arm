#ifdef ENABLE_CLI

void cliHelp()
{
  for (int i = 0; i < CLI_COMMANDS; i++) {
    cliSerial->print(cliCommands[i].commandName);
    cliSerial->print(" ");
    cliSerial->println(cliCommands[i].params);
  }
}

void cliI2cScan()
{
  #ifdef ENABLE_I2C_MULTIPLEXER
    cliSerial->print(CUR_I2C_MULTIPLEXER);
    cliSerial->print("ch ");
  #endif
  cliSerial->println("i2c:");
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
    cliSerial->println();
    cliI2cScan();
  }
}

void cliInitEEPROM()
{
  settingsInitEEPROM();
}

void cliSetServoCalib() {
  updatePosition = false;

  uint8_t servoId = CLI_readInt();
  int ms = CLI_readInt();
  int trimMs = CLI_readInt();
  cliSerial->println(servoId);
  cliSerial->println(ms);
  cliSerial->println(trimMs);
  setServoMs(servoId, ms, trimMs);
}

void cliSetServoAngle() {
  updatePosition = false;

  uint8_t servoId = CLI_readInt();
  double angleRad = degToRad(CLI_readFloat());
  cliSerial->println(servoId);
  cliSerial->println(radToDeg(angleRad));
  setServoAngle(servoId, angleRad);
}

void cliHAL() {
  updatePosition = CLI_readInt() ? true : false;
}

void cliSetWrist()
{
  targetPosition[WRIST_ANGLE]        = degToRad(CLI_readFloat());
  targetPosition[WRIST_ROTATE_ANGLE] = degToRad(CLI_readFloat());
}

void cliSetPosition()
{
  targetPosition[Y_AXIS] = CLI_readFloat();
  targetPosition[Z_AXIS] = CLI_readFloat();
}

void cliGetAngles()
{
  double servoPositionOutput = 0.0;

  for (uint8_t id = 0; id < 4; id++) {
    servoPositionOutput = servoPositions[id];
    if (servoInverted[id]) {
      servoPositionOutput = M_PI - servoPositionOutput;
    }

    cliSerial->print(radToDeg(servoPositionOutput));
    cliSerial->print(",");
  }
  cliSerial->println();
}

void cliGetPosition()
{
  for (uint8_t id = 0; id < 4; id++) {
    if (id > Z_AXIS) {
      cliSerial->print(radToDeg(currentPosition[id]));
      cliSerial->print("->");
      cliSerial->print(radToDeg(targetPosition[id]));
      cliSerial->print(",");
    } else {
      cliSerial->print(currentPosition[id]);
      cliSerial->print("->");
      cliSerial->print(targetPosition[id]);
      cliSerial->print(",");
    }
  }
  cliSerial->println();
}

void cliToFImage()
{
  #ifdef ENABLE_TOF
  tofPrint();
  #endif
}

#endif
