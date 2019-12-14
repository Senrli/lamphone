#ifndef _ESPBLUETOOTH_H_
#define _ESPBLUETOOTH_H_

#include "Arduino.h"
#include "BluetoothSerial.h"
#include "RGBVal.h"               //include the struct

#define BT_DEV_NAME    "LamPhone" //name for the bluetooth device

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

extern BluetoothSerial SerialBT;     //https://arduino.stackexchange.com/questions/39502/multiple-definition-of-compiler-error

void bluetoothInit();
void bluetoothRead();
void bluetoothResend();
void bluetoothSendConnected();
void bluetoothSendDisconnected();

extern void lightGradient(RGBVal tarval);                //Imported from LightCtr.h

#endif
