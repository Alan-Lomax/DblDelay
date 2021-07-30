# DblDelay

This class defines a timer that has individually configurable on delay and off delay intervals which are handled directly in the class. 
Two different delays are involved using a passed boolean value as a trigger.
- When the boolean goes from "low to high" the output of this class also goes from "Low to High" after an ON Delay period that you define.
- Conversely when the boolean goes from "high to low" the output of this class also goes from "high to low" but this time after an OFF Delay period that you also define.

On a model railway this type of timer is very handy for general timing, signalling and automation . 

Notes:
1) This class does not associate with any specific I/O pins it just wants a boolean 'input'
2) Either of the time intervals could be 'zero' thus making it a simple 'On Delay' only, or 'off delay only.
3) For a visual representation see the simple timing chart in the github repo
4) Some sensors (active IR sensors - varies by manufacturer) are inverted whereby the signal is normally high (when nothing is in the beam)
   and when something is detected the signal goes low.  For these types of sensors set the boolean "invertInput" parameter to true.

An example of use:
Using a Light dependant resistor (LDR) to detect a passing train. Send the on/off value to a timer of this class and it can activate signals
after a few seconds. The signals connected to the output will not change if a small gap passes over the LDR (It is inherantly 'debounced' because of the off delay.) 
Furthermore a long off delay would keep the signals at "danger" until the train has truly passed on down the line.
A second timer (using the same input but with different timing values) could trigger some trackside animation effects (like sounds).

### Files: DblDelay.h, DblDelay.CPP

### Example Program:
    /*
      DblDelay Example
      Objective: Turn on a Light Emitting Diode(LED) when a sensor detects an object.
      The output is subject to a 1 second 'on delay' and a 5 second "off delay" vs the input state.
      Note: some sensors are logic 'high' when nothing is detected and only go "low" when something is detected.
      Change the value of 'invertInput' from false to true or vice versa to compensate for this.
    */
    #include "DblDelay.h"                         // For implementing independent on and off delays.
    // #define DEBUG

    //    These constants won't change. They're used here to define our pin numbers:
    const int    SensorPin = A3;                  // the sensor (input for our timer) pin
    const int       LedPin = LED_BUILTIN;         // the builtin LED (normally pin 13) but using this constant is correct for all Arduinos)
    const bool invertInput = true;                // Swap this between true and false according to sensor and desired behaviour. (inverts the input - see timing chart)

    // Use the class to define myTimer
    DblDelay myTimer  (1000, 5000, invertInput);  // Create a timer with a 1 second on delay, 5 second off delay, input inversion is specified by the third parameter.

    void setup() {
      Serial.begin(9600);                         // for serial / debug console
      Serial.println(__FILE__);                   // by default I like to output the file name as a minimum.

      pinMode(SensorPin, INPUT_PULLUP);           // define our pin as input with pull up enabled
      pinMode(LedPin, OUTPUT);                    // define our led pin as an output
    }

    void loop() {
      // Three lines of code below to make the timer work. 
      myTimer.update();                           // update timer to see if anything needs doing this time through the loop
      myTimer.input(digitalRead(SensorPin));      // pass the input to the timer
      digitalWrite ( LedPin, myTimer.output());   // set the LED according to the timers output.

    #ifdef DEBUG
      Serial.print("Input :");
      Serial.print(digitalRead(SensorPin));
      Serial.print("\t Output :");
      Serial.println(myTimer.output());
      delay (1000);
    #endif
    }


### Instantiate
    DblDelay(unsigned long outputOnDelay, unsigned long outputOffDelay, bool invertInput);

### Methods 
    void update();
    void input(bool myInput);

### Properties 
    bool output();



