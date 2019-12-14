#include "TouchRead.h"

int val;
boolean changed;
boolean button_state;
boolean triggered;

uint64_t last_button_check_time;  //time of the last button check
uint8_t button_check_number;      //total number of button checks gone through
boolean button_enabled;   //enable button action




void touchInit()
{
  //pinMode(LED_PIN, OUTPUT);
  val = 0;
  changed = false;
  button_state = false;
  triggered = false;
  ledcSetup(0, 500, 8);
  ledcAttachPin(12, 0);
  ledcWriteTone(0, 500);
  ledcWrite(0, 10);
}

void touchAcq()
{
  if (!phone_state){
    if (esp_timer_get_time()- last_button_check_time > 20){
      
      val += touchRead(TOUCH_PIN);             //acquire the value// Just test touch pin - Touch0 is T0 which is on GPIO 4.
      //Serial.println(val);
      button_check_number++;            //auto increment the number of button checks
      last_button_check_time = esp_timer_get_time();
    }
    if (button_check_number >= 50){
      val = val/50;
      //Serial.println(val);
      if (triggered & val >= TRIGGER_THRESHOULD){
        button_state = true;
        lightStateChg();            //call change light state
        ledcWrite(0, 200);
      }else{
        button_state = false;
        ledcWrite(0, 0);
      }
      //digitalWrite(LED_PIN, button_state);
      triggered = val < TRIGGER_THRESHOULD;
      button_check_number = 0;
      val = 0;  
    }  
  }
}
