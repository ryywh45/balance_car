#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include "BluetoothSerial.h"

class BluetoothHelper {
public:
  BluetoothHelper(const char* deviceName);
  void BT_init();
  void BT_send(unsigned long timestamp, float angle, int pwm_value, float pitch_angular_v);
  void BT_read();
private:
  String _deviceName;
  BluetoothSerial _serialBT;
  bool _sendData = false;
};

#endif