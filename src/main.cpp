#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Arduino.h>

BLEServer *pServer = NULL;
BLECharacteristic * pControlCharacteristic;
BLECharacteristic * pPacketCharacteristic;
bool deviceConnected = false;

#define DFU_SERVICE_UUID                  "FE59" 
#define DFU_CHARACTERISTIC_UUID_CONTROL   "8EC90001-F315-4F60-9FB8-838830DAEA50"
#define DFU_CHARACTERISTIC_UUID_PACKET    "8EC90002-F315-4F60-9FB8-838830DAEA50"

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue.length(); i++)
          Serial.print(rxValue[i]);

        Serial.println();
        Serial.println("*********");
      }
    }
};

void setup() {
  Serial.begin(115200);

  // Create the BLE Device
  BLEDevice::init("Nordic DFU Service");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(DFU_SERVICE_UUID);

  // Create a BLE Characteristic
  pPacketCharacteristic = pService->createCharacteristic(
                       DFU_CHARACTERISTIC_UUID_PACKET,
                      BLECharacteristic::PROPERTY_WRITE_NR
                    );
                    
  pControlCharacteristic = pService->createCharacteristic(
                    DFU_CHARACTERISTIC_UUID_CONTROL,
                    BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY
                  );
                      
  pControlCharacteristic->addDescriptor(new BLE2902());
  

  pControlCharacteristic->setCallbacks(new MyCallbacks());
  pPacketCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  Serial.println("DFU Service started");
}

void loop() {
  // put your main code here, to run repeatedly:

}
