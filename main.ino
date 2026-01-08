#include <Arduino.h>
#include <SD.h>
#include <Audio.h>

// SD Card pins
#define SD_CS 5

// Button pins
const int buttonPins[9] = {12, 13, 14, 15, 16, 17, 21, 22, 33};

// Audio object
Audio audio;

// Sound file names on SD card
const char* soundFiles[9] = {
  "/sound1.mp3",
  "/sound2.mp3",
  "/sound3.mp3",
  "/sound4.mp3",
  "/sound5.mp3",
  "/sound6.mp3",
  "/sound7.mp3",
  "/sound8.mp3",
  "/sound9.mp3"
};

// Button state tracking
bool lastButtonState[9] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
bool buttonState[9] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
unsigned long lastDebounceTime[9] = {0};
const unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(115200);
  
  // Initialize button pins
  for (int i = 0; i < 9; i++) {
    pinMode(buttonPins[i], INPUT_PULLDOWN);
  }
  
  // Initialize SD card
  SPI.begin();
  if (!SD.begin(SD_CS)) {
    Serial.println("SD Card initialization failed!");
    while (1);
  }
  Serial.println("SD Card initialized successfully");
  
  // Initialize audio with I2S pins
  audio.setPinout(26, 27, 25);  // BCLK, LRC, DIN
  audio.setVolume(15);  // Volume 0-21
  
  Serial.println("ESP32 Soundboard Ready!");
  Serial.println("Press any button to play a sound");
}

void loop() {
  audio.loop();  // Keep audio processing
  
  // Check each button
  for (int i = 0; i < 9; i++) {
    int reading = digitalRead(buttonPins[i]);
    
    // Debounce logic
    if (reading != lastButtonState[i]) {
      lastDebounceTime[i] = millis();
    }
    
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      if (reading != buttonState[i]) {
        buttonState[i] = reading;
        
        // Button pressed (LOW to HIGH transition)
        if (buttonState[i] == HIGH) {
          Serial.print("Button ");
          Serial.print(i + 1);
          Serial.println(" pressed");
          
          // Stop current sound and play new one
          audio.stopSong();
          
          if (audio.connecttoFS(SD, soundFiles[i])) {
            Serial.print("Playing: ");
            Serial.println(soundFiles[i]);
          } else {
            Serial.print("Error playing: ");
            Serial.println(soundFiles[i]);
          }
        }
      }
    }
    
    lastButtonState[i] = reading;
  }
}

// Optional: Audio status callbacks
void audio_info(const char *info){
  Serial.print("audio_info: ");
  Serial.println(info);
}

void audio_eof_mp3(const char *info){
  Serial.println("End of file");
}
