//#define ENABLE_TOF
#define ENABLE_I2C_MULTIPLEXER
#define ENABLE_CLI
#define ENABLE_INTERFACE_I2C

#define ARM_ADDRESS 0x09
#define TCAADDR 0x70
#define TOFADDR 0x29

#define SERVO_SHOULDER_PIN      5
#define SERVO_ELBOW_PIN         6
#define SERVO_WRIST_PIN         7
#define SERVO_WRIST_ROTATE_PIN  8
#define SERVO_GRIPPER_PIN       9

#define L_SHOULDER 40.0
#define L_ELBOW    41.2311
#define L_WRIST    36.1      // from Wrist asix to gripper axis in top view, TODO measure it cafefully
#define L_GRIPPER  35.0

#define GRIPPER_OPEN_PWM   1700
#define GRIPPER_CLOSE_PWM  1300

// find my `servo_calib` for WK-P0025
servoProfile servoMainProfile = {
  0,
  180,
  610,
  910,
  1210,
  1500,
  1790,
  2040,
  2300,
  30
};
