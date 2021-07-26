#include "DblDelay.h"

DblDelay::DblDelay(unsigned long outputOnDelay, unsigned long outputOffDelay, unsigned long blipfilter) {
  // Save delays into the equivelent local variables (with the underscore). Signal changes of less than blipfilter duration will be ignored.
  _outputOnDelay   = outputOnDelay;
  _outputOffDelay  = outputOffDelay;
  _blipfilter      = blipfilter;
  init();                            // At initialization the timer is not running and the time values are set to zero (see below)
}

void DblDelay::init() {
  _previousMillis = millis();        // set the timer to current time
  _state = false;                    // assume the timer is on
  _runStatus = true;                 // start the timer by default
  _lastRunStatus = false;            // the last reading of the running status
}


void DblDelay::Update() {            // Do an update by checking time values.
  /*
     Output delays are handled directly in the class, so you don't have to think about it elsewhere in your code
     Two different delays are involved
        When the timer is started a "low to high" delay is used and the state changes after the delay
        When the timer is stopped   "high to low" delay is used and the state changes after that delay
        neither of these is checked until the blipfilter time has expired.
  */

  if (_runStatus != _lastRunStatus) {    // something has changed in our running status. It is not the same as it was
    _previousMillis = millis();          // capture the new time for this change
    _lastRunStatus = _runStatus;         // and save the reading for next time through
  }
  else {                                                  // run status has not changed
    if (millis() - _previousMillis >= _blipfilter) {      // Only check the other delays if the blipfilter time has passed.
      if (_state == false) {                              // It current state is false we are using the OnDelay timing before changing state.
        if (millis() - _previousMillis >= _outputOnDelay) {
          _state = true;                                  // Only Update the 'state' if the right delay time has passed
        }
      }
      else {                                              // Current state must be true OffDelay timing before changing state.
        if (millis() - _previousMillis >= _outputOffDelay) {
          _state = false;                                 // Only Update the 'state' if the right delay time has passed
        }
      }
    }
  }
}

bool DblDelay::State() {
  return _state;
}

void DblDelay::Start() {
  // Start Timer
  _previousMillis = millis();     // Reset the start time
  _runStatus = true;              // Set the flag so we know.
}

void DblDelay::Stop() {
  _previousMillis = millis();     // Reset the start time
  _runStatus = false;             // Set the flag so we know.
}
