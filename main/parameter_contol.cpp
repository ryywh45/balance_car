#include "Arduino.h"
#include "bluetooth.h"
#include <DabbleESP32.h>
#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE

String preSerialdata = "";
String Serialdata = "";
float value = 0;
bool dataflag = 0;
bool isfloat = 0;

void parameter_change_init(){
  Serial.begin(115200);       // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("balence_car");    //set bluetooth name of your device
}

void parameter_change() {
  Dabble.processInput();             
  if (Terminal.available() != 0){
    while (Terminal.available() != 0){
      Serialdata = String(Serialdata + char(Terminal.read()));
    }
    try {
        // 嘗試將Serialdata轉換為浮點數
        value = std::stof(Serialdata.c_str());  // 使用 std::stof 進行轉換
        Terminal.print("Input is float: ");
        isfloat = 1;
      } catch (const std::invalid_argument& e) {
        // 處理無效參數異常
        Terminal.println("Input is not a valid float.");
        isfloat = 0;
      } catch (const std::out_of_range& e) {
        // 處理超出範圍異常
        Terminal.println("Input is out of range for float.");
        isfloat = 0;
      } catch (...) {
        // 處理其他異常
        Terminal.println("An unexpected error occurred.");
        isfloat = 0;
      }
    if(preSerialdata == "kpb"){
      if(isfloat == 1){
        Kp_b = value;
        Terminal.print("kpb = ");
        Terminal.print(Kp_b);
      }
      else Terminal.print("Please input number after input parameter");
    }
    else if(preSerialdata == "kdb"){
      if(isfloat == 1){
        Kd_b = value;
        Terminal.print("kdb = ");
        Terminal.print(Kd_b);
      }
      else Terminal.print("Please input number after input parameter");
    }
    else if(preSerialdata == "kps"){
      if(isfloat == 1){
        Kp_s = value;
        Terminal.print("kps = ");
        Terminal.print(Kp_s);
      }
      else Terminal.print("Please input number after input parameter");
    }
    else if(preSerialdata == "kis"){
      if(isfloat == 1){
        Ki_s = value;
        Terminal.print("kis = ");
        Terminal.print(Ki_s);
      }
      else Terminal.print("Please input number after input parameter");
    }
    else if(preSerialdata == "kpd"){
      if(isfloat == 1){
        Kp_d = value;
        Terminal.print("kpd = ");
        Terminal.print(Kp_d);
      }
      else Terminal.print("Please input number after input parameter");
    }
    else if(preSerialdata == "kdd"){
      if(isfloat == 1){
        Kd_d = value;
        Terminal.print("kdd = ");
        Terminal.print(Kd_d);
      }
      else Terminal.print("Please input number after input parameter");
    }
    else if(Serialdata == "all"){
      Terminal.print("kpb = ");
      Terminal.print(Kp_b);
      Terminal.print("kdb = ");
      Terminal.print(Kd_b);
      Terminal.print("kps = ");
      Terminal.print(Kp_s);
      Terminal.print("kis = ");
      Terminal.print(Ki_s);
      Terminal.print("kpd = ");
      Terminal.print(Kp_d);
      Terminal.print("kdd = ");
      Terminal.print(Kd_d);
    }
    preSerialdata = Serialdata;
    Serialdata = "";
  }
}

  
