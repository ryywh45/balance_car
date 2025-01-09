#include "bluetooth.h"
#include <stdio.h> // For sprintf
#include "BluetoothSerial.h"

extern float Kp_b;
extern float Kd_b;

BluetoothHelper::BluetoothHelper(const char* deviceName) : _deviceName(deviceName) {
}

void BluetoothHelper::BT_init() {
  Serial.begin(115200);
  _serialBT.begin(_deviceName);  //Bluetooth device name
  //_serialBT.deleteAllBondedDevices(); // Uncomment this to delete paired devices; Must be called after begin
  Serial.printf("The device is started.\nNow you can pair it with Bluetooth!\n");
}

void BluetoothHelper::BT_send(unsigned long timestamp, float angle, int pwm_value, float pitch_angular_v) {
    if (_sendData) {
        char buffer[128];
        sprintf(buffer, "%lu,%.2f,%d,%.2f\n", timestamp, angle, pwm_value, pitch_angular_v);
        _serialBT.print(buffer);
    }
}


void BluetoothHelper::BT_read(){
    if (_serialBT.available()) {
        String command = _serialBT.readStringUntil('\n');
        command.trim();  // Remove any leading or trailing whitespace
        if(command == "send"){
            _sendData = true;
        } else if (command == "send_stop"){
            _sendData = false;
        }else {
            Serial.printf("Received unknown command: %s\n", command.c_str());
        }
      if (command.startsWith("p")) {
          // 解析指令以提取數值
          int dIndex = command.indexOf('d');
          if (dIndex > 1) {
              String param1Str = command.substring(1, dIndex); // 提取 "30.5"
              String param2Str = command.substring(dIndex + 1); // 提取 "10.2"
              
              // 將字串轉為浮點數
              Kp_b = param1Str.toFloat();
              Kd_b = param2Str.toFloat();

              // 打印確認
              Serial.printf("Extracted param1: %.2f, param2: %.2f\n", Kp_b, Kd_b);

              // 你可以在這裡進行其他處理，例如將數值賦值給成員變數
          } 
          else {
            Serial.println("Invalid command format. Missing 'd'.");
          }
      }
    }
}