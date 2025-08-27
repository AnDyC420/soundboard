#include <Arduino.h>

#define NUM_TRACKS 9

// ESP32 pins wired to GPD2846A IO1–IO9
const int gpdPins[NUM_TRACKS] = { 13, 12, 14, 27, 26, 25, 33, 32, 23 };

// Button inputs (you can change these as needed)
const int buttonPins[NUM_TRACKS] = { 4, 5, 18, 19, 21, 22, 34, 35, 36 };

int lastButtonState[NUM_TRACKS] = {HIGH};

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < NUM_TRACKS; i++) {
    pinMode(gpdPins[i], OUTPUT);
    digitalWrite(gpdPins[i], HIGH); // keep HIGH when idle
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  Serial.println("Ready - press a button to play track");
}

void loop() {
  for (int i = 0; i < NUM_TRACKS; i++) {
    int state = digitalRead(buttonPins[i]);

    if (lastButtonState[i] == HIGH && state == LOW) {  // button press
      Serial.printf("Button %d pressed -> Trigger MP3 %d\n", i+1, i+1);

      digitalWrite(gpdPins[i], LOW);
      delay(100); // short pulse
      digitalWrite(gpdPins[i], HIGH);

      delay(200); // debounce
    }
    lastButtonState[i] = state;
  }
}
