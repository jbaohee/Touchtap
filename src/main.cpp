#include <Arduino.h>

// global variable declaration
const int loopcnt = 30;
const int CS_Timeout_Millis = 10000;
const int TOUCH_THRESHOLD = 100;
int led_state = 0;
int button_state = 0;
int last_button_state = 0;
long val =0;

long thumb(){
  long sensor_read = 0;
  for(int i = 0; i < loopcnt; i++) {
    // Discharge output pin to low, input bit set to 0 all other uchg
    PORTD &=  0b11111011;
    
    // temporarily making the input pin an output then discharging 
    DDRD |= 0b00001000;
    PORTD &=  0b11110111;

    delayMicroseconds(10);

    // Then making the pin as an input again
    DDRD &= 0b11110111;

    // Writing high to the output pin
    PORTD |= 0b00000100;

    // Wait & Count until Input is HIGH
    while( !(PIND & 0b00001000) && (sensor_read < CS_Timeout_Millis)) {
      sensor_read++;
    }
  }
  return(sensor_read);
}

// same logic for rest of the finger functions
long index(){

  long sensor_read = 0;

  for(int i = 0; i < loopcnt; i++) {

    PORTD &=  0b11101111;
    DDRD |=   0b00100000;
    PORTD &=  0b11011111;
    delayMicroseconds(10);
    DDRD &=  0b11011111;
    PORTD |= 0b00010000;

    while( !(PIND & 0b00100000) && (sensor_read < CS_Timeout_Millis)) {
      sensor_read++;
    }
  }
  return(sensor_read);
}

long middle(){
  
  long sensor_read = 0;

  for(int i = 0; i < loopcnt; i++) {

    PORTD &=  0b10111111;
    DDRD |=   0b10000000;
    PORTD &=  0b01111111;
    delayMicroseconds(10);
    DDRD &=  0b01111111;
    PORTD |= 0b01000000;

    while( !(PIND & 0b10000000) && (sensor_read < CS_Timeout_Millis)) {
      sensor_read++;
    }
  }
  return(sensor_read);
}

long ring(){
  
  long sensor_read = 0;

  for(int i = 0; i < loopcnt; i++) {

    PORTB &=  0b11111110;
    DDRB |=   0b00000010;
    PORTB &=  0b11111101;
    delayMicroseconds(10);
    DDRB &=  0b11111101;
    PORTB |= 0b00000001;

    while( !(PINB & 0b00000010) && (sensor_read < CS_Timeout_Millis)) {
      sensor_read++;
    }
  }
  return(sensor_read);
}

long little(){
  
  long sensor_read = 0;

  for(int i = 0; i < loopcnt; i++) {

    PORTB &=  0b11111011;
    DDRB |=   0b00001000;
    PORTB &=  0b11110111;
    delayMicroseconds(10);
    DDRB &=  0b11110111;
    PORTB |= 0b00000100;

    while( !(PINB & 0b00001000) && (sensor_read < CS_Timeout_Millis)) {
      sensor_read++;
    }
  }
  return(sensor_read);
}

void setup() {
  //setting the pin modes for the touch pads and state change switch
  DDRD = 0b01010100;
  DDRB = 0b00000101;

  //enabling internal pullup of pin 13
  PORTB = 0b00100000;
  
  //setting the pin modes for the indicator lights 
  DDRC = 0b00011111;
  
  //pulling the indicators low  
  PORTC = 0b00000000;

  last_button_state = PINB & 0b00100000;

  //starting serial communication
  Serial.begin(9600);

}

void loop() {
  // poll the button

  button_state = PINB & 0b00100000;

  // change LED state if button press is detected
  if((button_state == 0) && (last_button_state != 0)){
    led_state = (led_state + 1) % 5;
  }  

  switch (led_state){
    case 0: //thumb high, all else low
      PORTC = 0b00000001;
      val = thumb();
      // Serial.print("Thumb data: "); //debug line
      Serial.println(val);
      break;

    case 1: //index high, all else low
      PORTC = 0b00000010;
      val = index();
      // Serial.print("Index data: "); //debug line
      Serial.println(val);
      break;
      
    case 2: //middle high, all else low
      PORTC = 0b00000100;
      val = middle();
      // Serial.print("Middle data: "); //debug line
      Serial.println(val);
      break;

    case 3: //ring high, all else low
      PORTC = 0b00001000;
      val = ring();
      // Serial.print("Ring data: "); //debug line
      Serial.println(val);
      break;
      
    case 4: //little high, all else low
      PORTC = 0b00010000;
      val = little();
      // Serial.print("Little data: "); //debug line
      Serial.println(val);
      break;
  }

  last_button_state = button_state;
  delay(5);
}

