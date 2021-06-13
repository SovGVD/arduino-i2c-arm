#include "def.h"
#include "config.h"
#include <EEPROM.h>
#include <Wire.h>
#include <Servo.h>

#ifdef ENABLE_CLI
  #include "cli.h"
#endif

#ifdef ENABLE_TOF
  #include "SparkFun_VL53L1X.h"
  
  SFEVL53L1X distanceSensor;

  uint16_t image[256];
  byte     roiID = 0;

  /**Table of Optical Centers**
    *
    * 128,136,144,152,160,168,176,184,  192,200,208,216,224,232,240,248
    * 129,137,145,153,161,169,177,185,  193,201,209,217,225,233,241,249
    * 130,138,146,154,162,170,178,186,  194,202,210,218,226,234,242,250
    * 131,139,147,155,163,171,179,187,  195,203,211,219,227,235,243,251
    * 132,140,148,156,164,172,180,188,  196,204,212,220,228,236,244,252
    * 133,141,149,157,165,173,181,189,  197,205,213,221,229,237,245,253
    * 134,142,150,158,166,174,182,190,  198,206,214,222,230,238,246,254
    * 135,143,151,159,167,175,183,191,  199,207,215,223,231,239,247,255
    
    * 127,119,111,103, 95, 87, 79, 71,  63, 55, 47, 39, 31, 23, 15, 7
    * 126,118,110,102, 94, 86, 78, 70,  62, 54, 46, 38, 30, 22, 14, 6
    * 125,117,109,101, 93, 85, 77, 69,  61, 53, 45, 37, 29, 21, 13, 5
    * 124,116,108,100, 92, 84, 76, 68,  60, 52, 44, 36, 28, 20, 12, 4
    * 123,115,107, 99, 91, 83, 75, 67,  59, 51, 43, 35, 27, 19, 11, 3
    * 122,114,106, 98, 90, 82, 74, 66,  58, 50, 42, 34, 26, 18, 10, 2
    * 121,113,105, 97, 89, 81, 73, 65,  57, 49, 41, 33, 25, 17, 9, 1
    * 120,112,104, 96, 88, 80, 72, 64,  56, 48, 40, 32, 24, 16, 8, 0             ^ Y
    *                                                                  pin1      |
    *                                                                        X <-+
    */
#endif

Servo servoShoulder;
Servo servoElbow;
Servo servoWrist;
Servo servoWristRotate;
Servo servoGripper;

// Settings
bool updatePosition = true;

// Position
double bodyPosition[3]    = {0.0, 0.0, 0.0};  // position of body servo axis from main platform 0,0,0... Actually all calculations are in 2D, so we don't need extra double value and can save space
double targetPosition[5]  = {0.0, 110.0, 50.0,  0.0, M_PI_2};
double currentPosition[5] = {0.0, 110.0, 50.0,  0.0, M_PI_2};

double servoPositions[5] = { M_PI_2, M_PI_2, M_PI_2, M_PI_2, M_PI_2 };
bool servoInverted[5]    = {   true,  false,  false,  false,  false };

bool doPositionUpdate = true;
#ifdef ENABLE_I2C_MULTIPLEXER
uint8_t CUR_I2C_MULTIPLEXER = 0;
#endif

// Loop
unsigned long currentTime;
unsigned long previousTime;
unsigned long loopTime;

//CLI
Stream *cliSerial;

void setup(void)
{
  // I just hope that we can have two masters on one line
  // The idea is to communicate with arm via i2c bus, but Arduino
  // can handle only one hardware connection, so it will be
  // master for ToF sensor and slave for the controller
  Wire.begin(ARM_ADDRESS);

  Serial.begin(115200);

  cliSerial = &Serial;

  initSettings();
  IK_preInitValues();

  #ifdef ENABLE_I2C_MULTIPLEXER
    tcaselect(CUR_I2C_MULTIPLEXER);
  #endif


  #ifdef ENABLE_TOF
    tofSetup();
  #endif

  servoShoulder.attach(SERVO_SHOULDER_PIN);
  servoElbow.attach(SERVO_ELBOW_PIN);
  servoWrist.attach(SERVO_WRIST_PIN);
  servoWristRotate.attach(SERVO_WRIST_ROTATE_PIN);
  servoGripper.attach(SERVO_GRIPPER_PIN);
}

void loop(void)
{
  currentTime = micros();
  #ifdef ENABLE_INTERFACE_I2C
    readCommand();
  #endif
  #ifdef ENABLE_TOF
    tofLoop();
  #endif

  #ifdef ENABLE_CLI
    if (CLI_get(CLI_BUFFER)){
      CLI_doCommand();
    }
  #endif

  if (doPositionUpdate) {
    nextTransition();
    IK_calculateServoAngles();
    HAL_updateCurrentPosition();
  }

  loopTime = micros() - currentTime;
//  cliSerial->println(loopTime);
}

#ifdef ENABLE_I2C_MULTIPLEXER
void tcaselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}
#endif
