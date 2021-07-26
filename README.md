
  public:
    DblDelay(unsigned long outputOnDelay, unsigned long outputOffDelay, unsigned long blipfilter);
    void init();
    void Update();
    bool State();
    void Start();
    void Stop();


# DblDelay

This class defines a timer that has individually configurable on delay and off delay intervals.
Very handy if using LDR's to activate signals as the signal can be configured to change a few seconds after the LDR is triggered
and stay activated for some period of time after the LDR has been cleared.

### Files: DblDelay.h, DblDelay.CPP

### Usage:
Include the header file near the top of your code. (After this is done the compiler will know how to handle you using it.)

    #include "DblDelay.h";

Then create a new member of this class as follows:

     DblDelay(outputOnDelay, outputOffDelay, blipfilter);

Where outputOnDelay, outputOffDelay, blipfilter are all in milliseconds.

### Example Instantiation:
     DblDelay myLDR (2000, 10000, 50); // creates myLDR with an 2 second on delay, a 10 second off delay, and a 50ms blip filter.

### Methods
    void Update();                     // Update things based on elapsed time (call this in your loop code as often as possible)
    bool State();                      // Return the current state of the DblDelay Timer


### Properties:
    void Start();                      // Start the Timer running
    void Stop();                       // Stop the Timer ready for next time.
