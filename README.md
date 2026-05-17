# ZeroLamp

<img width="240" height="320" alt="image" src="https://github.com/user-attachments/assets/944838e6-bf32-46ca-b142-0eb1b922bc8c" />
<img width="240" height="320" alt="image" src="https://github.com/user-attachments/assets/92ee6429-2c0b-4d20-95a2-9c80f8fb8c93" />


ZeroBone's ESP32-based smart lamp project.

## 📦 Dependencies / Arduino Libraries

**ZeroLamp** requires the following Arduino libraries, compatible with **ESP32-S3**.
All libraries can be installed via the **Arduino Library Manager**.

| Library         | Purpose                                       | Author               | Install via Library Manager         |
|-----------------|-----------------------------------------------|----------------------|-------------------------------------|
| FastLED         | Control addressable RGB LEDs (WS2812B matrix) | Daniel Garcia et al. | Search `FastLED` in Library Manager |
| WiFi            | Connect ESP32-S3 to Wi-Fi networks            | Espressif Systems    | Built-in for ESP32 in Arduino core  |
| ESPmDNS         | Device name discovery over network (mDNS)     | Espressif Systems    | Built-in for ESP32 in Arduino core  |
| BluetoothSerial | Bluetooth communication (ESP32-S3)            | Espressif Systems    | Built-in for ESP32 in Arduino core  |

**Notes:**  

- `TOUCH_BUTTON_PIN` (TTP223) uses standard `digitalRead()`, no extra library required.  
- Make sure your **Arduino IDE** is updated and ESP32-S3 board support is installed via **Boards Manager**.

## 🚀 Quick Start

1. Clone the repository
2. Open `zerolamp.ino` in Arduino IDE
3. Set `WLAN_SSID` and `WLAN_PASSWORD` in `wlan.h`
4. Upload to ESP32-S3 board
5. Press `TOUCH_BUTTON_PIN` to wake / sleep
