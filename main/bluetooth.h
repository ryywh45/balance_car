#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

extern float Target_Speed;
extern float Target_Direction;

void BT_init();
void BT_read();
void dataProcess(char data);


#endif // __BLUETOOTH_H__