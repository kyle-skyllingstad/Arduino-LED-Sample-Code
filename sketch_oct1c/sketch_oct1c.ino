/*
  This Arduino (C) code pairs with a physical device that has three lights. The task
  here is to signal four separate colors on 3 or fewer LEDs with three or fewer
  physical buttons. The design simply cannot allow 4 buttons and/or 4 LED lights,
  so our team has to use a combination or sequence of button presses to trigger
  certain colors. We also have to program the LEDs such that at least one of them
  can display multiple colors when pressed by different button 
  combinations/sequences. In this program, we differentiate by debouncing and 
  clearing the code between different color flashes; we use a multiple Switch 
  Debounce to RGB LED

  Each time the input pin goes from HIGH to LOW to HIGH (e.g. because of a push-button
  press/release), the output pin is toggled from LOW to HIGH or HIGH to LOW. There's a
  minimum delay between toggles to debounce the circuit (i.e. to ignore noise).

  The circuit we have is as follows:
  - RGB LED attached from pins 9,6,3 to ground
  - pushbutton attached from pin 8,5,2 to ground


  This example code from which we began is in the public domain at:
  http://www.arduino.cc/en/Tutorial/Debounce
  
*/




/////////////////////////////////// Initialization and Setup ///////////////////////////////////////




// These are constants won't change. They're used here to set pin numbers:
const int buttonPin1 = 2;   // the number of the 1st pushbutton pin
const int buttonPin2 = 5;   // the number of the 2nd pushbutton pin
const int buttonPin3 = 8;   // the number of the 3rd pushbutton pin
const int ledPin1 = 9;      // the number of the 1st LED pin
const int ledPin2 = 6;      // the number of the 2nd LED pin
const int ledPin3 = 3;      // the number of the 3rd LED pin

// Variables will change:
int ledState1 = 0;         // the current state of the 1st output pin
int ledState2 = 0;         // the current state of the 2nd output pin
int ledState3 = 0;         // the current state of the 3rd output pin
int buttonState1 = HIGH;        // the current reading from the 1st input pin
int buttonState2 = HIGH;        // the current reading from the 2nd input pin
int buttonState3 = HIGH;        // the current reading from the 3rd input pin
int lastButtonState1 = HIGH;         // the previous reading from the 1st input pin
int lastButtonState2 = HIGH;         // the previous reading from the 2nd input pin
int lastButtonState3 = HIGH;         // the previous reading from the 3rd input pin

int ColorVal = 20;       // color intensity variable


// The following variables are unsigned longs because the time, measured in milliseconds, and
// They will quickly become a bigger number than can be stored in an int variable.
unsigned long lastDebounceTime1 = 0;  // the last time the 1st output pin was toggled
unsigned long lastDebounceTime2 = 0;  // the last time the 2nd output pin was toggled
unsigned long lastDebounceTime3 = 0;  // the last time the 3rd output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

unsigned long lastColorTime1 = 0; // the last time the 1st output pin was toggled
unsigned long ColorDelay = 3000; // Colar Delay 3 seconds time

// Set button and LED pins
void setup() {

  // Button and LED pins
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  // Set initial LED state
  analogWrite(ledPin1, ledState1);
  analogWrite(ledPin2, ledState2);
  analogWrite(ledPin3, ledState3);
}





//////////////////////////////// Main loop to run continuously /////////////////////////////////////




// Run the main loop continuously in time
void loop() {
  // Read the state of the switch into a local variable:
  int reading1 = digitalRead(buttonPin1);
  int reading2 = digitalRead(buttonPin2);
  int reading3 = digitalRead(buttonPin3);

  // Check to see if you just pressed the button (i.e. the input went from LOW to HIGH), and you've 
  // waited long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading1 != lastButtonState1) {
    
    // Reset the debouncing timer
    lastDebounceTime1 = millis();
  }
  if (reading2 != lastButtonState2) {
    
    // Reset the debouncing timer
    lastDebounceTime2 = millis();
  }
  if (reading3 != lastButtonState3) {
    
    // Reset the debouncing timer
    lastDebounceTime3 = millis();
  }

  // COLOR ONE
  // Whatever the reading is at, it's been there for longer than the debounce delay, so take it as 
  // the actual current state:
  if ((reading3 == HIGH) && ((millis() - lastDebounceTime1) > debounceDelay)) {

    // See if the button state has changed:
    if (reading1 != buttonState1) {
      buttonState1 = reading1;

      // Only toggle the LED if the new button state is HIGH
      if (buttonState1 == HIGH) {
        lastColorTime1 = millis();
        ledState1 = 0;
        ledState2 = 0;
        ledState3 = ColorVal;
      }
    }
  }


  // COLOR TWO
  // Whatever the reading is at, it's been there for longer than the debounce delay, so take it as 
  // the actual current state:
  if ((reading3 == LOW) && ((millis() - lastDebounceTime1) > debounceDelay)) {

    // See if the button state has changed:
    if (reading1 != buttonState1) {
      buttonState1 = reading1;

      // Only toggle the LED if the new button state is HIGH
      if (buttonState1 == HIGH) {
        lastColorTime1 = millis();
        ledState1 = 0;
        ledState2 = ColorVal - ColorVal*9/10;
        ledState3 = ColorVal;
      }
    }
  }


  // COLOR THREE
  // Whatever the reading is at, it's been there for longer than the debounce delay, so take it as 
  // the actual current state:
  if ((reading3 == HIGH) && ((millis() - lastDebounceTime2) > debounceDelay)) {

    // See if the button state has changed:
    if (reading2 != buttonState2) {
      buttonState2 = reading2;

      // Only toggle the LED if the new button state is HIGH
      if (buttonState2 == HIGH) {
        lastColorTime1 = millis();
        ledState1 = ColorVal;
        ledState2 = 0;
        ledState3 = 0;
      }
    }
  }


  // COLOR FOUR
  // Whatever the reading is at, it's been there for longer than the debounce delay, so take it as 
  // the actual current state:
  if ((reading3 == LOW) && ((millis() - lastDebounceTime2) > debounceDelay)) {

    // See if the button state has changed:
    if (reading2 != buttonState2) {
      buttonState2 = reading2;

      // Only toggle the LED if the new button state is HIGH
      if (buttonState2 == HIGH) {
        lastColorTime1 = millis();
        ledState1 = ColorVal - ColorVal*8/10;
        ledState2 = 0;
        ledState3 = ColorVal;
      }
    }
  }


  // Set the LED:
  analogWrite(ledPin1, ledState1);
  analogWrite(ledPin2, ledState2);
  analogWrite(ledPin3, ledState3);


  // Delay 3 seconds
  if ((millis() - lastColorTime1) > ColorDelay) {
    ledState1 = 0;
    ledState2 = 0;
    ledState3 = 0;
  }


  // Old code for comparison and validation purposes
  // delay 3 seconds
  // if (ledState1 > 0 || ledState2 > 0 || ledState3 > 0) {
    // delay(3000);
    // ledState1 = 0;
    // ledState2 = 0;
    // ledState3 = 0;
  // }


  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState1 = reading1;
  lastButtonState2 = reading2;
  lastButtonState3 = reading3;

}
