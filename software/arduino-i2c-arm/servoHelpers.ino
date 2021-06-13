uint16_t angleToPulse(double angleRad) {
  double angleDeg = radToDeg(angleRad);

  if (angleDeg < servoMainProfile.minAngle) angleDeg = servoMainProfile.minAngle;
  if (angleDeg > servoMainProfile.maxAngle) angleDeg = servoMainProfile.maxAngle;

  // TODO how to make it better???

  if (angleDeg < 30) {
    return mapf(angleDeg, servoMainProfile.minAngle, 30, servoMainProfile.degMin, servoMainProfile.deg30) + servoMainProfile.defTrim;
  }

  if (angleDeg < 60) {
    return mapf(angleDeg, 30, 60, servoMainProfile.deg30, servoMainProfile.deg60) + servoMainProfile.defTrim;
  }

  if (angleDeg < 90) {
    return mapf(angleDeg, 60, 90, servoMainProfile.deg60, servoMainProfile.deg90) + servoMainProfile.defTrim;
  }

  if (angleDeg < 120) {
    return mapf(angleDeg, 90, 120, servoMainProfile.deg90, servoMainProfile.deg120) + servoMainProfile.defTrim;
  }

  if (angleDeg < 150) {
    return mapf(angleDeg, 120, 150, servoMainProfile.deg120, servoMainProfile.deg150) + servoMainProfile.defTrim;
  }

  if (angleDeg <= servoMainProfile.maxAngle) {
    return mapf(angleDeg, 150, servoMainProfile.maxAngle, servoMainProfile.deg150, servoMainProfile.degMax) + servoMainProfile.defTrim;
  }


  return 1500;  // TODO actualy we should fail here...
}
