/*
  DblDelay Example
  Objective: Turn on a Light Emitting Diode(LED) when a sensor detects an object.
  The output is subject to a 2 second 'on delay' and a 5 second "off delay" vs the input state.
  Note: some sensors are logic 'high' when nothing is detected and only go "low" when something is detected.
  Change the value of 'invertInput' from false to true or vice versa to compensate for this.
*/
#include "DblDelay.h"                         // For implementing independent on and off delays.
#define DEBUG

//    These constants won't change. They're used here to define our pin numbers:
const int    SensorPin = A3;                  // the sensor (input for our timer) pin
const int       LedPin = LED_BUILTIN;         // the builtin LED (normally pin 13) but using this constant is correct for all Arduinos)
const bool invertInput = true;                // Swap this between true and false according to sensor and desired behaviour. (inverts the input - see timing chart)

bool input;
bool prevInput;    // the prior input - so we can only report on change
bool output;
bool prevOutput;   // the prior Output - so we can only report on change


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
  input = digitalRead(SensorPin);             // get and save the input
  if (prevInput != input) {
    Serial.print("Input :");
    Serial.println(input);
    prevInput = input;                        // save the input so we can report only on change
  }

  output = myTimer.output();                  // get and save the output
  if (prevOutput != output) {
    Serial.print("\t Output :");
    Serial.println(output);
    prevOutput = output;                      // save the output so we can report only on change
  }
#endif
}
