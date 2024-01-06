#include "Arduino.h"
#include "BluetoothSerial.h"
#include "bluetooth.h"

String device_name = "ESP32-BT-Slave";

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
  #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
  #error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

void BT_init() {
  Serial.begin(115200);
  SerialBT.begin(device_name); //Bluetooth device name
  //SerialBT.deleteAllBondedDevices(); // Uncomment this to delete paired devices; Must be called after begin
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
}

// read and process data
void BT_read() {
  if (SerialBT.available()) {
    char receivedChar = SerialBT.read();
    Serial.println(receivedChar);
    SerialBT.print(receivedChar);
    SerialBT.print("\n");
    dataProcess(receivedChar);
  }
  else dataProcess('S');
  delay(20);
}

void dataProcess(char data){
  switch (data){
    case '1':
      /* move forward */
      Target_Speed = 10;
      break;
    case '2':
      /* move backward */
      Target_Speed = -10;
    case '3':
      /* turn left */
      Target_Direction = -30;
    case '4':
      /* turn right */
      Target_Direction =  30;  
    default:
      /* stop */
      Target_Speed = 0;
      Target_Direction = 0;
      break;
  }
}