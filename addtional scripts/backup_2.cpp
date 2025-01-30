#include <Arduino.h>

const int dout = 2;
const int din = 3;

const int loopcnt = 30;
const int CS_Timeout_Millis = 10000;
const int TOUCH_THRESHOLD = 100;

void setup() {
  pinMode(dout, OUTPUT);
  
  pinMode(din, INPUT);
  Serial.begin(9600);
}

void loop() {
  long start = millis();
  long total1 = 0;
  for(int i = 0; i < loopcnt; i++) {
    // Discharge input pin to low
    digitalWrite(dout, LOW);
    
    // Discharging by writing low by temporarily making the input pin an output 
    pinMode(din, OUTPUT);
    digitalWrite(din, LOW);

    // Then wait for 10 us
    delayMicroseconds(10);

    // Then making the pin as an input again
    pinMode(din, INPUT);

    // Writing high to the output pin
    digitalWrite(dout, HIGH);

    // Wait & Count until Input is HIGH
    while((!digitalRead(din)) && (total1 < CS_Timeout_Millis)) {
      total1++;
    }
  }

  long currentMillis = millis(); // Get the current time in milliseconds

  // Print the timestamp, duration, and total1
  // Serial.print(currentMillis);  // Print the current time
  // Serial.print("\t");
  // Serial.print(currentMillis - start); // Print the elapsed time for the loop
  // Serial.print(",");
  Serial.println(total1);
  
  delay(5);
}
