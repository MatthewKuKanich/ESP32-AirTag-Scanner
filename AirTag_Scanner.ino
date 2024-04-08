// AirTag Scanner by Matthew KuKanich
// https://github.com/MatthewKuKanich/ESP32-AirTag-Scanner
// https://github.com/MatthewKuKanich/FindMyFlipper

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <set>

int scanTime = 1;
BLEScan* pBLEScan;
std::set<String> foundDevices;
unsigned int airTagCount = 0;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      // raw data
      uint8_t* payLoad = advertisedDevice.getPayload();
      size_t payLoadLength = advertisedDevice.getPayloadLength();

      // searches both "1E FF 4C 00" and "4C 00 12 19" as the payload can differ slightly
      bool patternFound = false;
      for (int i = 0; i <= payLoadLength - 4; i++) {
        if (payLoad[i] == 0x1E && payLoad[i+1] == 0xFF && payLoad[i+2] == 0x4C && payLoad[i+3] == 0x00) {
          patternFound = true;
          break;
        }
        if (payLoad[i] == 0x4C && payLoad[i+1] == 0x00 && payLoad[i+2] == 0x12 && payLoad[i+3] == 0x19) {
          patternFound = true;
          break;
        }
      }

      if (patternFound) {
        String macAddress = advertisedDevice.getAddress().toString().c_str();
        macAddress.toUpperCase();

        if (foundDevices.find(macAddress) == foundDevices.end()) {
          foundDevices.insert(macAddress);
          airTagCount++;

          int rssi = advertisedDevice.getRSSI();

          Serial.println("AirTag found!");
          Serial.print("Tag: ");
          Serial.println(airTagCount);
          Serial.print("MAC Address: ");
          Serial.println(macAddress);
          Serial.print("RSSI: ");
          Serial.print(rssi);
          Serial.println(" dBm");
          Serial.print("Payload Data: ");
          for (size_t i = 0; i < payLoadLength; i++) {
            Serial.printf("%02X ", payLoad[i]);
          }
          Serial.println("\n");
        }
      }
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning for AirTags...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks(), true);
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
  delay(1000);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if (command.equals("rescan")) {
      foundDevices.clear();
      airTagCount = 0;
      Serial.println("Rescanning for AirTags...");
    }
  }

  BLEScanResults foundDevicesScan = pBLEScan->start(scanTime, false);
  pBLEScan->clearResults();
  delay(50);
}
