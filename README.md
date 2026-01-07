Hardware Requirements

- **ESP32 development board**
- **MicroSD card module** (SPI interface)
- **9 push buttons**
- **Audio amplifier** (like PAM8403, MAX98357A, or similar)
- **Speaker** (4-8 ohms)
- **MicroSD card** (formatted as FAT32)
- **Resistors** (10kΩ for pull-down resistors on buttons)
- **Connecting wires**

## Wiring Connections

**MicroSD Card Module (SPI):**
- CS → GPIO 5
- MOSI → GPIO 23
- MISO → GPIO 19
- SCK → GPIO 18
- VCC → 3.3V
- GND → GND

**Buttons (with pull-down resistors):**
Buttons 1-9 → GPIO 12, 13, 14, 15, 16, 17, 21, 22, 33

**Audio Output (I2S DAC like MAX98357A):**
- BCLK → GPIO 26
- LRC → GPIO 25
- DIN → GPIO 27

## Arduino Code Installation Steps

1. **Install Arduino IDE** and add ESP32 board support
2. **Install the ESP32-audioI2S library** by Schreibfaul1:
   - In Arduino IDE: Sketch → Include Library → Manage Libraries
   - Search for "ESP32-audioI2S" and install it

3. **Prepare your SD card:**
   - Format as FAT32
   - Copy 9 audio files named: `sound1.mp3`, `sound2.mp3`, ... `sound9.mp3`
   - Place them in the root directory of the SD card
