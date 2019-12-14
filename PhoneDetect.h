#ifndef _PHONEDETECT_H_
#define _PHONEDETECT_H_

#include "Arduino.h"

#define RED_LED     34//define the pin for the red led on the wireless charger
#define BLUE_LED    35//define the pin for the blue led on the wireless charger
#define CHK_INTERVAL    1000000//define the interval for two checking state

extern boolean phone_state;     //boolean storing the current state of the phone
extern uint64_t phone_state_chk_ctr;   //storing the last time that the phone existence has been checked
extern boolean last_check_state; //storing the last state when checked


void phoneInit();       //Init for the input functions
void phoneDetect();  //function that detects whether the phone is present on the charger

extern void bluetoothSendConnected();     //imported from ESPBluetooth.h
extern void bluetoothSendDisconnected();  //imported from ESPBluetooth.h
extern void lightStateChg(void);          //imported from LightCtr.h

#endif
