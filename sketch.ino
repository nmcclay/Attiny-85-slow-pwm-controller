/*
  ATTiny85 Slow PWM SSR Controller

  Toggles an SSR using an adjustable duty rate based on a poteniometer.
  This sketch uses a 3 second cycle as its base for the duty-cycle, which
  is optimal for applications such as controlling resistive heating elements.

  modified 22 August 2020
  by Nicholas McClay 

  Copyright (c) 2020 Nicholas McClay <sirnikkio@gmail.com>
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

int ssrPin = 0;
int sensorPin = A3;
int timeBase = 3000; //3 seconds
int minValue = 1;
int maxValue = 1000;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ssrPin, OUTPUT);
  pinMode(sensorPin, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  int sensorValue = analogRead(sensorPin);

  // flattens out low sensor value
  if (sensorValue < minValue) {
    sensorValue = 0;
  }

  // maximizes high sensor value
  if (sensorValue > maxValue ) {
    sensorValue = 1023;
  }
  
  int onTime = map(sensorValue, 0, 1023, 0, timeBase);
  int offTime = timeBase - onTime;
  
  if (onTime > 0) {
    digitalWrite(ssrPin, HIGH); // turn the SSR on (HIGH is the voltage level)
    delay(onTime); // turn on for the appropriate duty cycle
  }
  
  if (offTime > 0) {
    digitalWrite(ssrPin, LOW); // turn the SSR off by making the voltage LOW
    delay(offTime); // wait  for the rest of the time base period to elapse
  }
}
