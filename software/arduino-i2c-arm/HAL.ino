void HAL_updateCurrentPosition()
{
  if (!updatePosition) {
    return;
  }
}

void setServoAngle(uint8_t servoId, double angleDeg)
{
  setServoMs(servoId, angleToPulse(angleDeg), 0);
}

void setServoMs(uint8_t servoId, int ms, int trimMs)
{
  updatePosition = false;

  switch(servoId){
    case ID_SERVO_SHOULDER:
      servoShoulder.writeMicroseconds(ms + trimMs);
      break;
    case ID_SERVO_ELBOW:
      servoElbow.writeMicroseconds(ms + trimMs);
      break;
    case ID_SERVO_WRIST:
      servoWrist.writeMicroseconds(ms + trimMs);
      break;
    case ID_SERVO_WRIST_ROTATE:
      servoWristRotate.writeMicroseconds(ms + trimMs);
      break;
    case ID_SERVO_GRIPPER:
      servoGripper.writeMicroseconds(ms + trimMs);
      break;
    default:
      cliSerial->print(servoId);
      cliSerial->println(" unknown servo ID");
  }
}
