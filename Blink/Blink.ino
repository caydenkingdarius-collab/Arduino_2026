/*
  Blink
  Devleper Cayden
  Date 2.13.20.2026
  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://docs.arduino.cc/hardware/

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/Blink/
*/
// Pin definitions
const int speakerPin = 11;
const int ledRed = 10;
const int ledBlue = 9;
const int fadeLed = 6;

// Siren variables
int freq = 500;
int direction = 1;  // 1 = up, -1 = down

// Fade variables
int brightness = 0;
int fadeAmount = 5;

// Timing
unsigned long previousSirenMillis = 0;
unsigned long previousFlashMillis = 0;
unsigned long previousFadeMillis = 0;

const int sirenInterval = 5;
const int flashInterval = 150;
const int fadeInterval = 20;

bool redState = false;

void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(fadeLed, OUTPUT);
}

void loop() {

  unsigned long currentMillis = millis();

  // 🚨 Siren
  if (currentMillis - previousSirenMillis >= sirenInterval) {
    previousSirenMillis = currentMillis;

    tone(speakerPin, freq);

    freq += 10 * direction;

    if (freq >= 1500) direction = -1;
    if (freq <= 500) direction = 1;
  }

  // 🔴🔵 Flashing police lights
  if (currentMillis - previousFlashMillis >= flashInterval) {
    previousFlashMillis = currentMillis;

    redState = !redState;
    digitalWrite(ledRed, redState);
    digitalWrite(ledBlue, !redState);
  }

  // ✨ Fade LED
  if (currentMillis - previousFadeMillis >= fadeInterval) {
    previousFadeMillis = currentMillis;

    brightness += fadeAmount;

    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }

    analogWrite(fadeLed, brightness);
  }
}
