double IK_armPosition[2] = {0.0, 0.0};  // temporary calculated position
double L_SHOULDER_sq;
double L_ELBOW_sq;

void IK_preInitValues()
{
  L_SHOULDER_sq = sq(L_SHOULDER);
  L_ELBOW_sq    = sq(L_ELBOW);
}

bool IK_calculateServoAngles()
{
  if (!updatePosition) {
    return;
  }

  servoPositions[ID_SERVO_WRIST_ROTATE] = currentPosition[WRIST_ROTATE_ANGLE];

  // Find the Arm position based on given position of gripper (gripper X,Y,Z and two rotations)
  IK_armPosition[Y_AXIS] = currentPosition[Y_AXIS] - cos(currentPosition[WRIST_ANGLE]) * (L_WRIST + L_GRIPPER);
  IK_armPosition[Z_AXIS] = currentPosition[Z_AXIS] - sin(currentPosition[WRIST_ANGLE]) * (L_WRIST + L_GRIPPER);

  double arm_Z_delta = IK_armPosition[Z_AXIS] - bodyPosition[Z_AXIS];

  double h = sq(arm_Z_delta) + sq(IK_armPosition[Y_AXIS] - bodyPosition[Y_AXIS]);
  double sqrth = sqrt(h);

  double elbowValue    = acos((L_SHOULDER_sq + L_ELBOW_sq - h) / (2 * L_SHOULDER * L_ELBOW));
  double shoulderValue = M_PI - asin(arm_Z_delta/sqrth) - acos((L_SHOULDER_sq - L_ELBOW_sq + h)/(2 * L_SHOULDER * sqrth));
  double wristValue    = M_PI - acos(arm_Z_delta/sqrth) - acos((L_ELBOW_sq - L_SHOULDER_sq + h)/(2 * L_ELBOW    * sqrth)) - currentPosition[WRIST_ANGLE];

  if (isIKValueSafe(elbowValue) && isIKValueSafe(shoulderValue) && isIKValueSafe(wristValue)) {
    servoPositions[ID_SERVO_ELBOW]=elbowValue;
    servoPositions[ID_SERVO_SHOULDER]=shoulderValue;
    servoPositions[ID_SERVO_WRIST]=wristValue;
    return true;
  }

  return false;
}

bool isIKValueSafe(double value)
{
  if (isnan(value)) return false;
  if (value < 0) return false;
  if (value > 180) return false;

  return true;
}
