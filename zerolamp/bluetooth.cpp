#include "bluetooth.h"
#include <WiFi.h>
#include "program_controller.h"
#include <cstdarg>
#include <WebSocketsServer.h>

// extern const char* WLAN_SSID;
// extern const char* WLAN_PASSWORD;

//WebSocket
WebSocketsServer webSocket(81);

String incoming_line;
String connectionCode;
bool clientAuthorized = false;

// SerialWrapper
BLESerialWrapper wsSerial;

void BLESerialWrapper::println(const String& msg) {
  if (clientAuthorized) {
    webSocket.broadcastTXT(msg + "\n");
  }
}

void BLESerialWrapper::printf(const char* fmt, ...) {
  char buffer[256];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);
  println(String(buffer));
}

// Websocet event 
void webSocketEvent(uint8_t client_num, WStype_t type, uint8_t* payload, size_t length) {
  if (type == WStype_CONNECTED) {
    clientAuthorized = false;
    webSocket.sendTXT(client_num, "Enter connection code:");
  } else if (type == WStype_TEXT) {
    String msg = String((char*)payload);
    msg.trim();

    if (!clientAuthorized) {
      if (msg == connectionCode) {
        clientAuthorized = true;
        webSocket.sendTXT(client_num, "Authorized! Send commands.");
      } else {
        webSocket.sendTXT(client_num, "Wrong code. Disconnecting...");
        webSocket.disconnect(client_num);
      }
      return;
    }
    for (unsigned int i = 0; i < msg.length(); i++) {
      char c = msg[i];
      if (c == '\r') continue;
      if (c == '\n') {
        if (incoming_line.length() > 0) {
          program_controller_handle_command(incoming_line.c_str());
          incoming_line = "";
        }
      } else {
        incoming_line += c;
      }
    }
  } else if (type == WStype_DISCONNECTED) {
    clientAuthorized = false;
    incoming_line = "";
  }
}

void bluetooth_init() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Waiting for Wi-Fi connection...");
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
    }
  }

  connectionCode = String(random(1000, 9999));
  Serial.print("Connection code: ");
  Serial.println(connectionCode);

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void bluetooth_tick() {
  webSocket.loop();
}

BLESerialWrapper* bluetooth_serial() {
  return &wsSerial;
}

bool bluetooth_device_connected() {
  return clientAuthorized;
}