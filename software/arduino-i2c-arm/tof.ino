#ifdef ENABLE_TOF
void tofSetup()
{
  if (distanceSensor.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("ET");
    return;
  }

  // Short mode max distance is limited to 1.3 m but has a better ambient immunity.
  // Above 1.3 meter error 4 is thrown (wrap around).
  distanceSensor.setDistanceModeShort();
  //distanceSensor.setDistanceModeLong(); // default

  /*
   * The minimum timing budget is 20 ms for the short distance mode and 33 ms for the medium and long distance modes.
   * Predefined values = 15, 20, 33, 50, 100(default), 200, 500.
   */
  distanceSensor.setTimingBudgetInMs(20);

  // measure periodically. Intermeasurement period must be >/= timing budget.
  distanceSensor.setIntermeasurementPeriod(25);
  distanceSensor.startRanging(); // Start once

  tofReady = true;
}

void tofLoop()
{
  if (!tofReady) {
    return;
  }

  // TODO this delays are not ideal...
  distanceSensor.setROI(4,4, roiID);
  delay(1);
  while (!distanceSensor.checkForDataReady())
  {
    delay(1);
  }

  uint8_t  rangeStatus = distanceSensor.getRangeStatus();
  uint16_t distance    = distanceSensor.getDistance();       // distance in mm
  distanceSensor.clearInterrupt();

  setRange(distance, rangeStatus);
  
  nextROI();
}

void nextROI()
{
  // This should work fine for `byte` type
  roiID++;
}


void setRange(uint16_t distance, uint8_t rangeStatus)
{
  // We will use 0 as mark that data not available, so we need to +1 all data and when distance 65535 it can not become 65536 for uint16_t
  if (distance != 65535) distance++;

  image[getPosition()] = rangeStatus == 0 ? distance : 0;
}

byte getPosition()
{
  byte x = 0;
  byte y = 0;
  
  if (roiID < 128) {
    x = roiID / 8;
    y = roiID - x*8;
  } else {
    x = (255 - roiID) / 8;
    y = (255 - roiID) - x * 8 + 8;
  }

  x = 15 - x;

  return x + y*16;
}
#endif
