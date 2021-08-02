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
  _nextChangeOfState = 0;            // initialize the next Change Of State to 0
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
    _lastInput = _input;                 // and save the input value for the next time through update
    if (_input == true) {                // Depending on what the input is now .. calculate the future time when the output needs to change
      _nextChangeOfState = millis() + _outputOnDelay;     // input is true so output changes at current time plus the on delay
    }
    else {
      _nextChangeOfState = millis() + _outputOffDelay;    // input is false so output changes at current time plus the off delay
    }
  }
  else {                                                  // input has not changed (for example a subsequent call to update after the previous few lines of code was run)
    if (_input == true) {                                 // input is true
      if (millis() >= _nextChangeOfState) {               // and time is up
        _output = true;                                   // so update the 'output' since the OnDelay time has passed.
      }
    }
    else {                                                // input must be false
      if (millis() >= _nextChangeOfState) {               // and time is up
        _output = false;                                  // so update the 'output' since the OffDelay time has passed.
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
