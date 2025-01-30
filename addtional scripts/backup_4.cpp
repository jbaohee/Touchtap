#include <Arduino.h>

const int th_out = 2;
const int th_in = 3;

const int in_out = 4;
const int in_in = 5;

const int mid_out = 6;
const int mid_in = 7;

const int ring_out = 8;
const int ring_in = 9;

const int li_out = 10;
const int li_in = 11;

const int thumb_led = 14;
const int ind_led = 15;
const int mid_led = 16;
const int mid_led = 17;
const int mid_led = 18;

const int switch_pin = 13;

const int loopcnt = 30;
const int CS_Timeout_Millis = 10000;
const int TOUCH_THRESHOLD = 100;


long thumb(){
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

long index(){
  long sensor_read = 0;
  for(int i = 0; i < loopcnt; i++) {
    // Discharge input pin to low
    digitalWrite(in_out, LOW);
    
    // Discharging by writing low by temporarily making the input pin an output 
    pinMode(in_in, OUTPUT);
    digitalWrite(in_in, LOW);

    // Then wait for 10 us
    delayMicroseconds(10);

    // Then making the pin as an input again
    pinMode(in_in, INPUT);

    // Writing high to the output pin
    digitalWrite(in_out, HIGH);

    // Wait & Count until Input is HIGH
    while((!digitalRead(in_in)) && (sensor_read < CS_Timeout_Millis)) {
      sensor_read++;
    }
  }
  // Serial.print("Index: ");
  // Serial.println(sensor_read);
  return(sensor_read);
}

long middle(){
  long sensor_read = 0;
  for(int i = 0; i < loopcnt; i++) {
    // Discharge input pin to low
    digitalWrite(mid_out, LOW);
    
    // Discharging by writing low by temporarily making the input pin an output 
    pinMode(mid_in, OUTPUT);
    digitalWrite(mid_in, LOW);

    // Then wait for 10 us
    delayMicroseconds(10);

    // Then making the pin as an input again
    pinMode(mid_in, INPUT);

    // Writing high to the output pin
    digitalWrite(mid_out, HIGH);

    // Wait & Count until Input is HIGH
    while((!digitalRead(mid_in)) && (sensor_read < CS_Timeout_Millis)) {
      sensor_read++;
    }
  }
  // Serial.print("Middle: ");
  // Serial.println(sensor_read);
  return(sensor_read);
}


void setup() {
  //setting the pin modes for the touch pads
  pinMode(th_out, OUTPUT);
  pinMode(th_in, INPUT);

  //setting the pin modes for the indicator lights 
  pinMode(switch_pin, INPUT);
  pinMode(thumb_led,OUTPUT);
  pinMode(mid_led,OUTPUT); 
  pinMode(ind_led,OUTPUT); 

  digitalWrite(thumb_led,LOW);
  digitalWrite(ind_led,LOW);
  digitalWrite(mid_led,LOW);

  Serial.begin(9600);
}

int led_state = 0;
int button_state = 0;
int last_button_state = 0;
long val =0;

void loop() {
  
  button_state = digitalRead(switch_pin);
  
  if(button_state == LOW && last_button_state == HIGH){
    led_state = (led_state + 1) % 5;
  }

  switch (led_state){
    case 0: //thumb
      digitalWrite(thumb_led,HIGH);
      digitalWrite(ind_led,LOW);
      digitalWrite(mid_led,LOW);
      val = thumb();
      Serial.println(val);
      break;
    case 1: //index
      digitalWrite(thumb_led,LOW);
      digitalWrite(ind_led,HIGH);
      digitalWrite(mid_led,LOW);
      index();
      val = index();
      Serial.println(val);
      break;
    case 2: //middle
      digitalWrite(thumb_led,LOW);
      digitalWrite(ind_led,LOW);
      digitalWrite(mid_led,HIGH);
      middle();
      val = middle();
      Serial.println(val);
      break;
  }

  last_button_state = button_state;
  delay(5);
}
 
 