#ifndef MY_DBLDELAY_H
#define MY_DBLDELAY_H

class DblDelay {

  private:
    bool _output;                         // DblDelay Timer output
    bool _input;                          // DblDelay Timer input
    bool _lastInput;                      // internal value to see if something has changed
    bool _invertInput;                    // invert the input of the timer if true. (needed for some sensors)
    unsigned long _nextChangeOfState = 0;    // internal value holding the next scheduled change of state time
    unsigned long    _outputOnDelay  = 0;    // internal value to hold the on delay time value
    unsigned long    _outputOffDelay = 0;    // internal value to hold the off delay time value
    void init();

  public:
    DblDelay(unsigned long outputOnDelay, unsigned long outputOffDelay, bool invertInput);
    void update();
    void input(bool myInput);
    bool output();
};
#endif
