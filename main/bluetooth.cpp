#include "Arduino.h"
#include "bluetooth.h"
#include <DabbleESP32.h>
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

void BT_init() {
  Serial.begin(115200);      
  Dabble.begin("balence_car");
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
}

// read and process data
void BT_read() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  Serial.print("KetPressed: ")
  if (GamePad.isUpPressed()){
    /* move forward */
    Target_Speed = 10;
    Serial.print("F");
  }
  else if (GamePad.isDownPressed()){
    /* movebak */
    Target_Speed = -10;
    Serial.print("B");
  }

  else if(GamePad.isLeftPressed()){
    /* turn left */
    Target_Direction = -30;
    Serial.print("L");
  }

  else if(GamePad.isRightPressed()){
    /* turn right */
    Target_Direction = 30;
    Serial.print("R");
  }
  else if(GamePad.isSquarePressed()){
    /* park */
    digitalWrite(27,0);
    Serial.print("parking");
  }
  else{
    /* stop */
    Target_Speed = 0;
    Target_Direction = 0;
    Serial.println("S");
  }
  delay(20);
}