#include "DblDelay.h"
#include <arduino.h>

DblDelay::DblDelay(unsigned long outputOnDelay, unsigned long outputOffDelay, bool invertInput) {
  // Save passed variables into the equivelent local variables (with the underscore)
  _outputOnDelay   = outputOnDelay;
  _outputOffDelay  = outputOffDelay;
  _invertInput = invertInput;
  init();                            // Do the initialization code
}

void DblDelay::init() {
  _previousMillis = 0;               // set the timer to 0
  _output = false;                   // assume the output is false (off)
  _input  = false;                   // assume the input is false (off)
  _lastInput = false;                // assume last input was the same as _input
}

void DblDelay::update() {
  /*
     Output delays are handled directly in the class. Two different delays are involved:
     A "low to high" delay changes the output after the "On Delay" has expired.
     A "high to low" delay changes the output after the "Off Delay" has expired.
  */
  if (_input != _lastInput) {            // The input has changed. It is not the same as it was!
    _previousMillis = millis();          // capture the new time for this change
    _lastInput = _input;                 // and save the input value for the next time through update
  }
  else {                                 // input has not changed (for example a subsequent call to update after the previous few lines of code was run)
    if (_input == true) {
      if (millis() - _previousMillis >= _outputOnDelay) {
        _output = true;                                              // Only update the 'output' after OnDelay time has passed.
      }
    }
    else {                                                           // _input must be false
      if (millis() - _previousMillis >= _outputOffDelay) {
        _output = false;                                             // Only update the 'output' after OffDelay time has passed
      }
    }
  }
}

bool DblDelay::output() {        // output is subject to the two delays
  return _output;
}

void DblDelay::input(bool myInput) {
  switch (_invertInput) {
    /* Note the internal variable _input is always 'On = true', 'Off = false'
       It will follow directly along with the passed digital input if _invertInput is false.
       if _invertInput is true then _input will be exactly the opposite of myInput
       Either way the timing is triggering off of _input so the onDelay and offDelay works.
    */
    case false:
      _input = myInput;          // save the digital input status
      break;
    case true:
      _input = !myInput;         // save the inverted digital input status
      break;
  }
}
