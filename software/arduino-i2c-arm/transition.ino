#define TRANSITION_STEP 0.1
#define TRANSITION_ANGLE_STEP 0.001 // RAD

// TODO: that should be better, TRANSITION_STEP can be too slow, time should be use
void nextTransition()
{
  doPositionUpdate = false;
  for (uint8_t i = 0; i < 4; i++) {
    if (currentPosition[i] != targetPosition[i]) {
      if (i > Z_AXIS) {
        currentPosition[i] = currentPosition[i] < targetPosition[i] ? currentPosition[i] + TRANSITION_ANGLE_STEP : currentPosition[i] - TRANSITION_ANGLE_STEP;
        doPositionUpdate = true;
      } else {
        currentPosition[i] = currentPosition[i] < targetPosition[i] ? currentPosition[i] + TRANSITION_STEP : currentPosition[i] - TRANSITION_STEP;
        doPositionUpdate = true;
      }
    }
  }
}
