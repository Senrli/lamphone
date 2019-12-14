#ifndef _LIGHTCTR_H_
#define _LIGHTCTR_H_

#include "Arduino.h"
#include "FastLED.h"
#include "RGBVal.h"       //include the struct

#define NUM_LEDS  144       //no of leds for the lamp
#define LED_OUT_PIN      14 //```````set led register pin no

#define EFF_GRAD_STEPS    100         //set steps of change of effects
//#define AUTO_TIMER_OFF 300000000    //set timer to turn off the lamp, 5min
#define AUTO_TIMER_OFF 1000000    //set timer to turn off the lamp, 5min


extern CRGB leds[NUM_LEDS]; // Define the array of leds

extern uint64_t timer_off_val;          //delay timer value
extern boolean timer_off_en;       //store the timer state
extern boolean next_state;         //boolean flag to store for the next state



extern int light_gradient_ctr;   //record down how many loops has the delay counter been through
extern int light_state;          //determine which state the light is in, auto, or manual



extern RGBVal RGB_curr;           //store current RGB values
extern RGBVal RGB_gradient[EFF_GRAD_STEPS];         //store RGB channel gradient in values and go through them

extern boolean phone_state;
extern boolean button_state;                      //imported from TouchRead.h       

enum State_enum {OFF, HIGH_MA, MID_MA, LOW_MA, AUTO, AUTO_OFF};


void lightInit(void);                             //initialise led at the bootup
void lightChg(void);                              //change light value in each loop
void lightWrite(RGBVal val);                      //write RGB values to the LED strip
void lightStateChg(void);                   //turn on or off the light according to the button press, called by other functions
void lightNextState(void);                        //for the button to change between each state
void lightAutoOff(void);                    //automatic turn on or off the light when phone is disconnected
void lightGradient(RGBVal tarval);                //change the light to target values with gradient

#endif
