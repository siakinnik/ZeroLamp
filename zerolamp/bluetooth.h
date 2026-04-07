#ifndef ZB_BLUETOOTH_H
#define ZB_BLUETOOTH_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

struct BLESerialWrapper {
    void println(const String& msg);
    void printf(const char* fmt, ...);
};

// siakinnik - added
// struct WSClientInit {
//     uint8_t client_num;
//     unsigned long connectTime; 
//     bool authorized;
// };

const unsigned long INIT_TIMEOUT = 2000; 

void bluetooth_init();
void bluetooth_tick();
BLESerialWrapper* bluetooth_serial();
bool bluetooth_device_connected();

#endif
