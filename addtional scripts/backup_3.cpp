// Define the pin numbers
const int buttonPin = 13;
const int redLEDPin = 15;
const int greenLEDPin = 14;
const int blueLEDPin = 16;

// Variable to keep track of the LED state
int ledState = 0;

// Variable for the button state
int buttonState = 0;
int lastButtonState = 0;

void setup() {
  // Initialize the LED pins as outputs
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);

  // Initialize the button pin as input with internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);

  // Start with all LEDs off
  digitalWrite(redLEDPin, LOW);
  digitalWrite(greenLEDPin, LOW);
  digitalWrite(blueLEDPin, LOW);
}

void loop() {
  // Read the button state
  buttonState = digitalRead(buttonPin);

  // Check if the button is pressed (LOW) and was previously released (HIGH)
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Increment the LED state
    ledState = (ledState + 1) % 3;

    // Update the LEDs based on the current state
    switch (ledState) {
      case 0:
        digitalWrite(redLEDPin, HIGH);
        digitalWrite(greenLEDPin, LOW);
        digitalWrite(blueLEDPin, LOW);
        break;
      case 1:
        digitalWrite(redLEDPin, LOW);
        digitalWrite(greenLEDPin, HIGH);
        digitalWrite(blueLEDPin, LOW);
        break;
      case 2:
        digitalWrite(redLEDPin, LOW);
        digitalWrite(greenLEDPin, LOW);
        digitalWrite(blueLEDPin, HIGH);
        break;
    }
  }

  // Remember the button state for the next loop iteration
  lastButtonState = buttonState;

  // Small delay for debouncing
  delay(5);
}
