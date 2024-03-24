# ESP32-AirTag-Scanner

## Overview
This project allows for scanning AirTag MAC addresses and payloads without the need for an Android device or the nrfConnect app.

## Requirements
- ESP32-WROOM or ESP32-S3 module
- Flipper Zero or Arduino IDE for flashing the firmware

## Instructions

### Preparing the Firmware Files
1. Locate the following firmware files:
   - `airtag_scanner.ino.bootloader.bin`
   - `airtag_scanner.ino.partitions.bin`
   - `airtag_scanner.ino.bin`
2. Move these files to your Flipper Zero's SD card, specifically into the `apps_data/esp_flasher/` directory. For better organization, you can create a new folder within `esp_flasher` named `airtag`.

### Flashing the Firmware
1. Connect your ESP32-WROOM or ESP32-S3 to your computer and enter bootloader mode. To do this:
   - Hold down the **Boot** button.
   - Press the **Reset** button once.
   - Release the **Boot** button.
2. On your Flipper Zero, navigate to the ESP Flasher app located in `Apps` > `GPIO`.
3. Select `Manual Flash`.
4. If you are using an ESP32-S3, select `Select if using S3`.
5. Proceed to flash the firmware files in the following order:
   - Click on `bootloader` and select the `airtag_scanner.ino.bootloader.bin` file.
   - Click on `Part Table` and select the `airtag_scanner.ino.partitions.bin` file.
   - Click on `FirmwareA` and select the `airtag_scanner.ino.bin` file.
6. Leave all other options at their default settings and click `FLASH`.
7. Wait for the flashing process to complete.

### Using the Scanner
1. Once flashing is complete, open the UART Terminal app on your Flipper Zero.
2. Press the reset button on your ESP32 module. The device should start scanning for AirTags and display information such as MAC addresses and payloads.
