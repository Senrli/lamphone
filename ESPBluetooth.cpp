#include "ESPBluetooth.h"

BluetoothSerial SerialBT;  //define Bluetooth Stack here


void bluetoothInit() {
  SerialBT.begin(BT_DEV_NAME); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void bluetoothRead(){
  if(SerialBT.available()){
  char message [20] = "";
  int i = 0;
  while(SerialBT.available()>0){
    message[i] += SerialBT.read();
    i++;
  }
  int len = strlen(message);
  for(int j=0; j<len; j++){
    Serial.write(message[j]);
    }
    Serial.println("");
  Serial.println(len);
  if (len!=18){
    Serial.println("len!=18");
    bluetoothResend();
  }
  else if (message[0]=='H' && message[1]=='R' && message[5]=='G' && message[9]=='B' && message[13]=='S'){
    int r = (message[2] - 48) * 100 + (message[3] - 48) * 10 + message[4] - 48;
    int g = (message[6] - 48) * 100 + (message[7] - 48) * 10 + message[8] - 48;
    int b = (message[10] - 48) * 100 + (message[11] - 48) * 10 + message[12] - 48;
    int sum = (message[14] - 48) * 100 + (message[15] - 48) * 10 + message[16] - 48;
    if (r + g + b==sum){
      RGBVal retRGB;
      retRGB.R = r;
      retRGB.G = g;
      retRGB.B = b;
      lightGradient(retRGB);
      Serial.print("RGB received");
      Serial.print(" R: ");
      Serial.print(retRGB.R);
      Serial.print(" G: ");
      Serial.print(retRGB.G);
      Serial.print(" B: ");
      Serial.println(retRGB.B);
    } else{
      Serial.println("data not tally");
      bluetoothResend();
    }
  }else{
    Serial.println("ELSE");
    bluetoothResend();
  }
}
}

void bluetoothResend(){
    uint8_t h = 'h', N = 'N';
    SerialBT.write(h);SerialBT.write(N);SerialBT.write(10);
    Serial.println("NAK!");
}

void bluetoothSendConnected(){
    uint8_t h = 'h', P = 'P', I = '1';
    SerialBT.write(h);SerialBT.write(P);SerialBT.write(I);SerialBT.write(10);
    Serial.println("Phone Connected");
}
void bluetoothSendDisconnected(){
    uint8_t h = 'h', P = 'P', O = '0';
    SerialBT.write(h);SerialBT.write(P);SerialBT.write(O);SerialBT.write(10);
    Serial.println("Phone Disconnected");
}
