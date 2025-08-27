#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>
#include <HardwareSerial.h>

#define NUM_BUTTONS 9
const int buttonPins[NUM_BUTTONS] = { 13, 12, 14, 27, 26, 25, 33, 32, 35 }; // change pins as needed

HardwareSerial mySerial(1);  // use UART1 for DFPlayer
DFRobotDFPlayerMini mp3;

int lastButtonState[NUM_BUTTONS] = {HIGH};

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17 (to DFPlayer Mini)

  if (!mp3.begin(mySerial)) {
    Serial.println("DFPlayer not found!");
    while (true);
  }

  mp3.volume(25); // 0-30 volume

  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  Serial.println("Ready - Press buttons to play MP3s");
}

void loop() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    int buttonState = digitalRead(buttonPins[i]);

    if (lastButtonState[i] == HIGH && buttonState == LOW) {  // button press detected
      Serial.printf("Button %d pressed → Play track %d\n", i+1, i+1);
      mp3.playMp3Folder(i+1); // Play "mp3/0001.mp3" → button 1, etc.
      delay(200); // debounce
    }

    lastButtonState[i] = buttonState;
  }
}
