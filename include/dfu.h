#ifndef DFU_H__
#define DFU_H__

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Arduino.h>
#include "dfu_req_handler.h"

#define DFU_SERVICE_UUID                  "FE59" 
#define DFU_CHARACTERISTIC_UUID_CONTROL   "8EC90001-F315-4F60-9FB8-838830DAEA50"
#define DFU_CHARACTERISTIC_UUID_PACKET    "8EC90002-F315-4F60-9FB8-838830DAEA50"

class esp32_dfu {
public:
    bool initialize();
    void set_device_connected(bool isConnected);
    bool set_value_control(uint8_t *val, uint16_t len);
private:
    BLEServer *pServer = NULL;
    BLECharacteristic * pControlCharacteristic;
    BLECharacteristic * pPacketCharacteristic;
    esp32_dfu_req_handler req_handler;
    bool deviceConnected = false;
};





#endif //DFU_H__