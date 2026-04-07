#include "bluetooth.h"
#include "JWT.h" // siakinnik - added
#include <WiFi.h>
#include "program_controller.h"
#include <cstdarg>
#include <WebSocketsServer.h>

// extern const char* WLAN_SSID;
// extern const char* WLAN_PASSWORD;

// WebSocket
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
// ChatGPT parts!!!
void webSocketEvent(uint8_t client_num, WStype_t type, uint8_t* payload, size_t length) {
  if (type == WStype_CONNECTED) {
    Serial.printf("Client %u connected\n", client_num);
    clientAuthorized = false;
    incoming_line = "";

    // siakinnik - added
    connectionCode = String(random(1000, 9999));
    Serial.print("Connection code: ");
    Serial.println(connectionCode);
    String cmd1 = "fg 16";
    String cmd2 = "w |" + connectionCode + "|";
    program_controller_handle_command(std::string(cmd1.c_str()));
    program_controller_handle_command(std::string(cmd2.c_str()));

    webSocket.sendTXT(client_num, "Enter connection code:");
  } else if (type == WStype_TEXT) {
    String msg = "";
    for (size_t i = 0; i < length; i++) msg += (char)payload[i];
    msg.trim();

    if (!clientAuthorized) {
      if (msg == connectionCode) {
        clientAuthorized = true;
        webSocket.sendTXT(client_num, "Authorized! Send commands.");

        // siakinnik - added
        // siakinnik TODO - put original fg size and mode
        String cmd1 = "fg 6";
        String cmd2 = "fg clock";
        program_controller_handle_command(std::string(cmd1.c_str()));
        program_controller_handle_command(std::string(cmd2.c_str()));

      } else {
        webSocket.sendTXT(client_num, "Wrong code. Disconnecting...");
        webSocket.disconnect(client_num);

        // siakinnik - added
        // siakinnik TODO - put original fg size and mode
        String cmd1 = "fg 6";
        String cmd2 = "fg clock";
        program_controller_handle_command(std::string(cmd1.c_str()));
        program_controller_handle_command(std::string(cmd2.c_str()));
      }
      return;
    }

    program_controller_handle_command(std::string(msg.c_str()));

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

  // siakinnik - removed
  // connectionCode = String(random(1000, 9999));
  // Serial.print("Connection code: ");
  // Serial.println(connectionCode);

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