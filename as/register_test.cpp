#include <Arduino.h>

const int th_out = 2;
const int th_in = 3;


const int loopcnt = 30;
const int CS_Timeout_Millis = 10000;
const int TOUCH_THRESHOLD = 100;


long thumb_org(){
  long sensor_read = 0;
  for(int i = 0; i < loopcnt; i++) {
    // Discharge input pin to low
    digitalWrite(th_out, LOW);
    
    // Discharging by writing low by temporarily making the input pin an output 
    pinMode(th_in, OUTPUT);
    digitalWrite(th_in, LOW);

    // Then wait for 10 us
    delayMicroseconds(10);

    // Then making the pin as an input again
    pinMode(th_in, INPUT);

    // Writing high to the output pin
    digitalWrite(th_out, HIGH);

    // Wait & Count until Input is HIGH
    while((!digitalRead(th_in)) && (sensor_read < CS_Timeout_Millis)) {
      sensor_read++;
    }
  }
  // Serial.print("Thumb: ");
  // Serial.println(sensor_read);
  return(sensor_read);
}

long thumb(){
  long sensor_read = 0;
  for(int i = 0; i < loopcnt; i++) {
    // Discharge input pin to low, input bit set to 0 all other uchg
    // digitalWrite(th_out, LOW);
    PORTD &= 0b11111011;
    
    // Discharging by writing low by temporarily making the input pin an output 
    // pinMode(th_in, OUTPUT);
    DDRD |= 0b00001000;

    // digitalWrite(th_in, LOW);
    PORTD &=  0b11110111;

    // Then wait for 10 us
    delayMicroseconds(10);

    // Then making the pin as an input again
    // pinMode(th_in, INPUT);
    DDRD &= 0b11110111;

    // Writing high to the output pin
    // digitalWrite(th_out, HIGH);
    PORTD |= 0b00000100;

    // Wait & Count until Input is HIGH
    while((!digitalRead(th_in)) && (sensor_read < CS_Timeout_Millis)) {
      sensor_read++;
    }
  }
  // Serial.print("Thumb: ");
  // Serial.println(sensor_read);
  return(sensor_read);
}


void setup() {
  //pin 2 is op, pin 3 is i/p
  pinMode(th_out, OUTPUT);
  pinMode(th_in, INPUT);
  // DDRD = 0b00000100;

  // pinMode(switch_pin, INPUT);

  //enabling internal pullup of pin 13

  
  //setting the pin modes for the indicator lights 
  DDRC = 0b00000001;
  
  //pull the indicators low  
  PORTC = 0b00000000;

  //start serial communication
  Serial.begin(9600);
}

long val =0;
int switch_pin = 13;

void loop() {
  
  //thumb high, all else low
  PORTC = 0b00000001;
  val = thumb();
  Serial.print("Thumb data: "); //debug line
  Serial.println(val);


  delay(5);
}
