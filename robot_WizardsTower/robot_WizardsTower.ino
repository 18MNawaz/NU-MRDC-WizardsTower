//Code to be uploaded to robot, sends message that was received by RF to Wizard's Tower using IR
#include <IRLibSendBase.h>    
#include <IRLib_HashRaw.h>  
  
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(48, 49);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";
int number;
byte space = 128;
byte check;
int j;
IRsendBase mySender;
String str;

void setup() {
  while (!Serial);
    Serial.begin(9600);
  
  radio.begin();
  
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();
  Serial1.begin(9600);
}

 
void loop() {
  byte temp[32];

  if(radio.available()) {
    radio.read(&temp, sizeof(temp));
  }
int size1 = (sizeof(temp)/sizeof(temp[0]));
    j = 0;
    while(temp[j] !=  128){
      Serial.println(temp[j]);
      j++;
      if(j > 32) {
        break;
      }
    }
      Serial.println(j);
              Serial.print("Start");
      number = 0;
      byte message[j+1];
      for (int i = 0; i<=j; i++) {
        message[i] = temp[i];

        Serial.println(message[i]);
      }

  for (int i=0;i<size1;i++){
       mySender.sendGeneric(message[i], 8, 0, 15000, 526, 0, 0, 526, 38, 0); //(data, numBits, headMark, headSpace, markOne, markZero, spaceOne, spaceZero, kHz, stopBits)
    }
   //Pass the buffer,length, optionally frequency
  if (Serial1.available() > 0) {
      str = Serial1.readString(); // read the incoming byte:
      Serial.println(str);
    }
    delay(500);
  }
