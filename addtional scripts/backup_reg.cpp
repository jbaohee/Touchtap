#include <Arduino.h>

// const int th_out = 2;
const int th_in = 3;

// const int in_out = 4;
const int in_in = 5;

// const int mid_out = 6;
const int mid_in = 7;

// const int ring_out = 8;
const int ring_in = 9;

// const int li_out = 10;
const int li_in = 11;

// const int thumb_led = 14;
// const int ind_led = 15;
// const int mid_led = 16;
// const int ring_led = 17;
// const int lit_led = 18;

const int switch_pin = 13;

const int loopcnt = 30;
const int CS_Timeout_Millis = 10000;
const int TOUCH_THRESHOLD = 100;


long thumb(){
  long sensor_read = 0;
  for(int i = 0; i < loopcnt; i++) {
    // Discharge input pin to low, input bit set to 0 all other uchg
    // digitalWrite(th_out, LOW);
    PORTD &=  0b11111011;
    
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
    // !(PIND & (1 << PD2))
    while( !(PIND & 0b00001000) && (sensor_read < CS_Timeout_Millis)) {
      sensor_read++;
    }
  }
  // Serial.print("Thumb: ");
  // Serial.println(sensor_read);
  return(sensor_read);
}

// long index(){
//   long sensor_read = 0;
//   for(int i = 0; i < loopcnt; i++) {
//     // Discharge input pin to low
//     digitalWrite(in_out, LOW);
    
//     // Discharging by writing low by temporarily making the input pin an output 
//     pinMode(in_in, OUTPUT);
//     digitalWrite(in_in, LOW);

//     // Then wait for 10 us
//     delayMicroseconds(10);

//     // Then making the pin as an input again
//     pinMode(in_in, INPUT);

//     // Writing high to the output pin
//     digitalWrite(in_out, HIGH);

//     // Wait & Count until Input is HIGH
//     while((!digitalRead(in_in)) && (sensor_read < CS_Timeout_Millis)) {
//       sensor_read++;
//     }
//   }
//   // Serial.print("Index: ");
//   // Serial.println(sensor_read);
//   return(sensor_read);
// }

// long middle(){
//   long sensor_read = 0;
//   for(int i = 0; i < loopcnt; i++) {
//     // Discharge input pin to low
//     digitalWrite(mid_out, LOW);
    
//     // Discharging by writing low by temporarily making the input pin an output 
//     pinMode(mid_in, OUTPUT);
//     digitalWrite(mid_in, LOW);

//     // Then wait for 10 us
//     delayMicroseconds(10);

//     // Then making the pin as an input again
//     pinMode(mid_in, INPUT);

//     // Writing high to the output pin
//     digitalWrite(mid_out, HIGH);

//     // Wait & Count until Input is HIGH
//     while((!digitalRead(mid_in)) && (sensor_read < CS_Timeout_Millis)) {
//       sensor_read++;
//     }
//   }
//   // Serial.print("Middle: ");
//   // Serial.println(sensor_read);
//   return(sensor_read);
// }


void setup() {
  //setting the pin modes for the touch pads and state change switch
  DDRD = 0b01010100;
  DDRB = 0b00000101;
  // pinMode(switch_pin, INPUT);

  //enabling internal pullup of pin 13
  PORTB = 0b00100000;
  
  //setting the pin modes for the indicator lights 
  DDRC = 0b00011111;
  
  //pull the indicators low  
  PORTC = 0b00000000;

  //start serial communication
  Serial.begin(9600);
}

int led_state = 0;
int button_state = 0;
int last_button_state = 0;
long val =0;

void loop() {
  // poll the button
  // button_state = digitalRead(switch_pin);
  button_state = PINB & 0b00100000;
  

  // debug print 
  Serial.println();
  Serial.print("Button state = ");
  Serial.println(button_state);
  Serial.print("LED state = ");
  Serial.println(led_state);

  if((button_state == 0) && (last_button_state != 0)){
    led_state = (led_state + 1) % 5;
  }  

  switch (led_state){
    case 0: //thumb high, all else low
      PORTC = 0b00000001;
      val = thumb();
      Serial.print("Thumb data: "); //debug line
      Serial.println(val);
      break;

    case 1: //index high, all else low
      PORTC = 0b00000010;
      // index();
      // val = index();
      Serial.print("Index data: "); //debug line
      Serial.println(val);
      break;
      
    case 2: //middle high, all else low
      PORTC = 0b00000100;
      // middle();
      // val = middle();
      Serial.print("Middle data: "); //debug line
      Serial.println(val);
      break;

    case 3: //ring high, all else low
      PORTC = 0b00001000;
      // middle();
      // val = middle();
      Serial.print("Ring data: "); //debug line
      Serial.println(val);
      break;
      
    case 4: //little high, all else low
      PORTC = 0b00010000;
      // middle();
      // val = middle();
      Serial.print("Little data: "); //debug line
      Serial.println(val);
      break;
  }

  last_button_state = button_state;
  delay(500);
}

