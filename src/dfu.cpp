#include "dfu.h"

class MyServerCallbacks: public BLEServerCallbacks {
public:
    MyServerCallbacks(esp32_dfu *e_dfu) {
        dfu = e_dfu;
    }
    void onConnect(BLEServer* pServer) {
      dfu->set_device_connected(true);
    };

    void onDisconnect(BLEServer* pServer) {
      dfu->set_device_connected(false);
    }
private:
    esp32_dfu *dfu;
};

class MyCallbacks: public BLECharacteristicCallbacks {
public:
    MyCallbacks(esp32_dfu_req_handler *e_req_handler) {
        req_handler = e_req_handler;
    }
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string rxValue = pCharacteristic->getValue();
        if (rxValue.length() > 0) {
            Serial.println("*********");
            Serial.print("Received Value: ");
            for (int i = 0; i < rxValue.length(); i++) {
                Serial.print(rxValue[i], HEX);
                Serial.print(" ");
            }   
            Serial.println();
            Serial.println("*********");
        }
        uint16_t len = rxValue.length();
        // ctr_response ret = req_handler->process_command(rxValue.c_str(), len);
        dummy_handler(pCharacteristic, rxValue.c_str(), len);
        
    }
private:
    esp32_dfu_req_handler *req_handler;
    void dummy_handler(BLECharacteristic *pCharacteristic, const char *cmd, uint16_t len) {
        switch (cmd[0])
        {

        case 0x01: {
            uint8_t data[15] = {0x60, 0x01, 0x01};
            pCharacteristic->setValue(data, 3);
            pCharacteristic->notify();
        }break;

        case 0x02: {
            uint8_t data[3] = {0x60, 0x02, 0x01};
            pCharacteristic->setValue(data, 3);
            pCharacteristic->notify();
        }break;

        case 0x06: {
            uint8_t data[15] = {0x60, 0x06, 0x01, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
            pCharacteristic->setValue(data, 15);
            pCharacteristic->notify();   
        }break;
        
        default:
            break;
        }
        
    };
};

bool esp32_dfu::initialize() {
    // Create the BLE Device
    BLEDevice::init("Nordic DFU Service");

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks(this));

    this->req_handler = esp32_dfu_req_handler();

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


    pControlCharacteristic->setCallbacks(new MyCallbacks(&(this->req_handler)));
    pPacketCharacteristic->setCallbacks(new MyCallbacks(&(this->req_handler)));

    // Start the service
    pService->start();

    

    // Start advertising
    pServer->getAdvertising()->start();
    Serial.println("DFU Service started");
}

void esp32_dfu::set_device_connected(bool isConnected){
    this->deviceConnected = isConnected;
    Serial.printf("Device connected = %d\n", this->deviceConnected);
}

bool esp32_dfu::set_value_control(uint8_t *val, uint16_t len){
    this->pControlCharacteristic->setValue(val, len);
}