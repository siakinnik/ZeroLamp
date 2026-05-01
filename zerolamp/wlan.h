#ifndef ZB_WLAN_H
#define ZB_WLAN_H

// #define WLAN_SSID "YODA"
// #define WLAN_PASSWORD "2I9gF8FyJB27rf0ObvaVmrOGaJw5zrVh"

#define WLAN_SSID "TP-Link_BF08"
#define WLAN_PASSWORD "16333161"

#define TIME_SYNC_INTERVAL 30000 // how often to syncronize time, in milliseconds
#define MDNS_NAME "ZeroLamp"
#define AP_SSID "ZeroLamp-Setup"
#define AP_PASSWORD "12345678"
#define WIFI_CONNECT_TIMEOUT 30000

void wlan_init();
void wlan_tick();
struct tm* get_current_time();

#endif