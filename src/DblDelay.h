#ifndef MY_DBLDELAY_H
#define MY_DBLDELAY_H
#include <Arduino.h>

class DblDelay {

  private:
    bool _bit;
    bool _state;
    bool _lastReading;
    bool _runStatus;
    bool _lastRunStatus;
    unsigned long _previousMillis = 0;
    unsigned long _blipfilter     = 0;
    unsigned long _outputOnDelay  = 0;
    unsigned long _outputOffDelay = 0;

  public:
    DblDelay(unsigned long outputOnDelay, unsigned long outputOffDelay, unsigned long blipfilter);
    void init();
    void Update();
    bool State();
    void Start();
    void Stop();
};
#endif
