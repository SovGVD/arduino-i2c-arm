#define TRANSITION_STEP 0.1
#define TRANSITION_ANGLE_STEP 0.01 // RAD

// TODO: that should be better, TRANSITION_STEP can be too slow, time should be use
void nextTransition()
{
  for (uint8_t i = 0; i < 5; i++) {
    if (currentPosition[i] = targetPosition[i]) {
      continue;
    }

    if (i > Z_AXIS) {
      currentPosition[i] = currentPosition[i] < targetPosition[i] ? currentPosition[i] + TRANSITION_STEP : currentPosition[i] - TRANSITION_STEP;
    } else {
      currentPosition[i] = currentPosition[i] < targetPosition[i] ? currentPosition[i] + TRANSITION_ANGLE_STEP : currentPosition[i] - TRANSITION_ANGLE_STEP;
    }
  }
}
