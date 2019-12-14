#include "LightCtr.h"

CRGB leds[NUM_LEDS]; // Define the array of leds
int light_state;          //determine which state the light is in, auto, or manual
int light_gradient_ctr;   //record down how many loops has the delay counter been through

RGBVal RGB_curr;           //store current RGB values
RGBVal RGB_gradient[EFF_GRAD_STEPS];         //store RGB channel gradient in values and go through them

const uint64_t timer_const = 10000000;

uint64_t timer_off_val;          //delay timer value
boolean timer_off_en;       //store the timer state
boolean next_state;         //boolean flag to store for the next state

const RGBVal RGB_high_manual = {255,255,255};
const RGBVal RGB_mid_manual = {127,127,127};
const RGBVal RGB_low_manual = {63,63,63};
const RGBVal RGB_off = {0,0,0};

void lightInit(void) { 
  FastLED.addLeds<WS2812B, LED_OUT_PIN, RGB>(leds, NUM_LEDS);
  light_state = OFF;
  light_gradient_ctr = EFF_GRAD_STEPS - 1;
}

void lightChg(void) {
  if (light_gradient_ctr < EFF_GRAD_STEPS){ 
  /*
    for (int i = 0; i < NUM_LEDS; i++){
    leds[i].setRGB(RGB_gradient[light_gradient_ctr].R, RGB_gradient[light_gradient_ctr].G, RGB_gradient[light_gradient_ctr].B);
    }
  FastLED.show();
  */
  lightWrite(RGB_gradient[light_gradient_ctr]);
  RGB_curr = RGB_gradient[light_gradient_ctr];
  light_gradient_ctr++;
  }
}


void lightWrite(RGBVal val){
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i].setRGB(val.G, val.R, val.B);
    }
  RGB_curr = val;
  FastLED.show();
  Serial.print("RGB changed");
  Serial.print(" R: ");
  Serial.print(val.R);
  Serial.print(" G: ");
  Serial.print(val.G);
  Serial.print(" B: ");
  Serial.println(val.B);
}


void lightStateChg(void){
  switch(light_state){
    case OFF:
      if(phone_state){
        light_state = AUTO;
      }else if(button_state){
        light_state = HIGH_MA;
        //lightWrite(RGB_high_manual);
        //RGB_curr = RGB_high_manual;
        lightGradient(RGB_high_manual);
      }
      break;

    case HIGH_MA:
      if(phone_state){
        light_state = AUTO;
      }else if(button_state){
        light_state = MID_MA;
        //lightWrite(RGB_mid_manual);
        //RGB_curr = RGB_mid_manual;
        lightGradient(RGB_mid_manual);
      }
      break;
      
    case MID_MA:
      if(phone_state){
        light_state = AUTO;
      }
      if(button_state){
        light_state = LOW_MA;
        //lightWrite(RGB_low_manual);
        //RGB_curr = RGB_low_manual;
        lightGradient(RGB_low_manual);
      } 
      break;
      
    case LOW_MA:
      if(phone_state){
        light_state = AUTO;
      }
      if(button_state){
        light_state = OFF;
        //lightWrite(RGB_off);
        //RGB_curr = RGB_off;
        lightGradient(RGB_off);
      }
      break;
      
    case AUTO:
      if(!phone_state){
        light_state = AUTO_OFF;
        timer_off_en = true;
        timer_off_val = esp_timer_get_time();
      }
      break;
      
    case AUTO_OFF:
      if(phone_state){
        timer_off_en = false;
        light_state = AUTO;        
      }else if(button_state){
        timer_off_en = false;
        light_state = OFF;
        //lightWrite(RGB_off);
        //RGB_curr = RGB_off;
        lightGradient(RGB_off);
      }
      break;
    }
    button_state = false;                                            //Clear button state buffer after the state machine
}

void lightNextState(void){
  
}


void lightAutoOff(void){
  if(timer_off_en){
    if (esp_timer_get_time()- timer_off_val > timer_const){
      Serial.println("timed off");
      button_state = true;                                            //Enable flag of button pressed to signal a turn off
      lightStateChg();                                                //Call lightStateChg to change the state machine
    }
  }
}

void lightGradient(RGBVal tarval){
  for (int i; i< EFF_GRAD_STEPS; i++){
    RGB_gradient[i].R = map(i,0,EFF_GRAD_STEPS,RGB_curr.R,tarval.R);
    RGB_gradient[i].G = map(i,0,EFF_GRAD_STEPS,RGB_curr.G,tarval.G);
    RGB_gradient[i].B = map(i,0,EFF_GRAD_STEPS,RGB_curr.B,tarval.B);
    }
  RGB_gradient[EFF_GRAD_STEPS-1] = tarval;
  light_gradient_ctr = 0; 
}
