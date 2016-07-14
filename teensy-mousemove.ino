/*
 * This program uses the Teensy 3.2 as a HID mouse device, it toggles between moving the mouse back and forward, 
 * and releasing it back to the computer.
 * 
 * The button needs a pull-up resistor of 10KOhm, when it is pressed the voltage drops and the interupt is triggered,
 * toggling the mouse move routine on/off.
 * 
 * When the mouse is moving the internal LED is on.
 */
const int LED = 13;
const int BUTTON = 12;
boolean isOn = false;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);

  attachInterrupt(BUTTON, buttonPressed, LOW);
}

void loop() {
  if ( isOn ) {
    int i;
    for (i=0; i<40; i++) {
      Mouse.move(2, -1);
      if ( !isOn ) return;
      delay(10);
    }
  
    for (;i > 0; i--) {
      Mouse.move(-2, 1);
      if ( !isOn ) return;
      delay(10);
    }
  } else {
    delay(100);
  }
}

void buttonPressed() {
  if (digitalRead(BUTTON) == LOW ) {
    isOn = !digitalRead(LED);
    digitalWrite(LED, isOn);
  }
}


