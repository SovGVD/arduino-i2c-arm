/* Math */
#define RADTODEG 180/PI
#define DEGTORAD PI/180

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

#define WRIST_ANGLE        3
#define WRIST_ROTATE_ANGLE 4

#define ID_SERVO_SHOULDER     0
#define ID_SERVO_ELBOW        1
#define ID_SERVO_WRIST        2
#define ID_SERVO_WRIST_ROTATE 3
#define ID_SERVO_GRIPPER      4

#define SERVO_TRIM_LIMIT  0.24   // See settingsUint8ToDouble()

typedef struct {
  uint8_t minAngle;
  uint8_t maxAngle;
  uint16_t degMin;  // PWM pulse at minAngle deg
  uint16_t deg30;   // PWM pulse at 30 deg
  uint16_t deg60;
  uint16_t deg90;   // PWM pusle at 90 deg, middle
  uint16_t deg120;
  uint16_t deg150;  // PWM pulse at 150 deg
  uint16_t degMax;  // PWM pulse at maxAngle deg
  uint8_t defTrim;
} servoProfile;
