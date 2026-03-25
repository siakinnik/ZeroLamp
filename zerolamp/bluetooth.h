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

void bluetooth_init();
void bluetooth_tick();
BLESerialWrapper* bluetooth_serial();
bool bluetooth_device_connected();

#endif
