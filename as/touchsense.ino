
const int dout = 4;
const int din = 6;
const int LED_pin = 8;
const int loopcnt = 30;
const int CS_Timeout_Millis = 10000;
const int TOUCH_THRESHOLD = 100;

bool led_state = false;
bool turn_on = false;
int flag = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(dout, OUTPUT);
  pinMode(LED_pin, OUTPUT);
  pinMode(din, INPUT);
  Serial.begin(9600);
}

void loop() {

  noInterrupts();
  long start = millis();
  long total1 = 0;
  for(int i=0;i<loopcnt;i++)
  {
    // Discharge input pin to low
    digitalWrite(dout, LOW);
    pinMode(din, OUTPUT);
    digitalWrite(din, LOW);
    delayMicroseconds(10);
    pinMode(din, INPUT);

    // Set Output to HIGH
    digitalWrite(dout, HIGH);

    // Wait & Count until Input is HIGH
    while( (!digitalRead(din)) && (total1<CS_Timeout_Millis) )
    {
      total1++;
    }
  }
  interrupts();

  Serial.print(millis() - start);
  Serial.print("\t");
  Serial.println(total1);
  
  delay(20);

  if(total1>TOUCH_THRESHOLD)
  {
    if(flag==0)
    {
      turn_on = !turn_on;
      flag = 1;
    }
  }
  else
  {
    flag = 0;
  }


  digitalWrite(LED_pin, turn_on);
}
