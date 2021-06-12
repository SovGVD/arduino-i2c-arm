void HAL_updateCurrentPosition()
{
  if (!updatePosition) {
    return;
  }
}

void setServoMs(uint8_t servoId, int ms)
{
  updatePosition = false;

  switch(servoId){
    case ID_SERVO_SHOULDER:
      servoShoulder.writeMicroseconds(ms);
      break;
    case ID_SERVO_ELBOW:
      servoElbow.writeMicroseconds(ms);
      break;
    case ID_SERVO_WRIST:
      servoWrist.writeMicroseconds(ms);
      break;
    case ID_SERVO_WRIST_ROTATE:
      servoWristRotate.writeMicroseconds(ms);
      break;
    case ID_SERVO_GRIPPER:
      servoGripper.writeMicroseconds(ms);
      break;
    default:
      cliSerial->print(servoId);
      cliSerial->println(" unknown servo ID");
  }
}
