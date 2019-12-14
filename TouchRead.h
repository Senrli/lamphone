#ifndef _TOUCHREAD_H_
#define _TOUCHREAD_H_

#include "Arduino.h"

#define TOUCH_PIN    27 //define a pin for the touch sensor
#define LED_PIN       2 //define the pin no for the indicator led
#define TRIGGER_THRESHOULD  10
//define the threshould for the touch sensor triggering


extern int val;
extern boolean changed;
extern boolean button_state;
extern boolean triggered;

extern uint64_t last_button_check_time;  //time of the last button check
extern uint8_t button_check_number;      //total number of button checks gone through
extern boolean button_enabled;   //enable button action

extern boolean phone_state;     //boolean storing the current state of the phone
void touchAcq();
void touchInit();

extern void lightStateChg(void); //imported from LightCtr.h
#endif
