void HAL_updateCurrentPosition()
{
  if (!updatePosition) {
    return;
  }
  double servoPosition = 0.0;

  for (uint8_t id = 0; id < 5; id++) {
    servoPosition = servoPositions[id];
    if (servoInverted[id]) {
      servoPosition = M_PI - servoPosition;
    }

    setServoAngle(id, servoPosition);
  }
}

void setServoAngle(uint8_t servoId, double angleDeg)
{
  setServoMs(servoId, angleToPulse(angleDeg), 0);
}

void setServoMs(uint8_t servoId, int ms, int trimMs)
{
  int thisMs = ms + trimMs;
  switch(servoId){
    case ID_SERVO_SHOULDER:
      servoShoulder.writeMicroseconds(thisMs);
      break;
    case ID_SERVO_ELBOW:
      servoElbow.writeMicroseconds(thisMs);
      break;
    case ID_SERVO_WRIST:
      servoWrist.writeMicroseconds(thisMs);
      break;
    case ID_SERVO_WRIST_ROTATE:
      servoWristRotate.writeMicroseconds(thisMs);
      break;
    case ID_SERVO_GRIPPER:
      servoGripper.writeMicroseconds(thisMs);
      break;
  }
}
