#include "PhoneDetect.h"

boolean phone_state;     //boolean storing the current state of the phone
uint64_t phone_state_chk_ctr;   //storing the last time that the phone existence has been checked
boolean last_check_state; //storing the last state when checked



void phoneInit(){
  pinMode(RED_LED, INPUT);    //set inputs
  pinMode(BLUE_LED, INPUT);   //set inputs
  phone_state = false;
  phone_state_chk_ctr = esp_timer_get_time();
  }

  
void phoneDetect(){
  if (esp_timer_get_time() - phone_state_chk_ctr > CHK_INTERVAL){  //if it has passed 1s since last checking
    
    boolean state_current = (digitalRead(RED_LED) && digitalRead(BLUE_LED));
    //Serial.print("state: ");
    //Serial.println(state_current);
    if (state_current == last_check_state){
      if(state_current != phone_state){    //if state changed
        phone_state = state_current;         //assign the new state to the phoneState
        if(state_current){            //if phone connected
          bluetoothSendConnected();   //notify Android
        }else{                        //if phone disconnected
          bluetoothSendDisconnected();
        }
        lightStateChg();            //call change light state
      }
      
    }
    last_check_state = state_current;
    phone_state_chk_ctr = esp_timer_get_time();      //reassign the time of checking
  }
}
