#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(7, 8);  // CE, CSN
String str;
String message = "#DRAGON["; //address through which two modules communicate.
const byte address[6] = "00001";

void setup()
{
  Serial.begin(9600);
  radio.begin();
  
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();
}
void loop()
{
  //Send message to receiver
  byte ARRAY[message.length()+1];
  int size = (sizeof(ARRAY)/sizeof(ARRAY[0]));
  message.getBytes(ARRAY,message.length()+1); //Initalizes array to of bytes (in 7-bit)
   for (int i = 0; i <= size; i++){
    ARRAY[i] = ARRAY[i] + 128;                //Converts 7-bit values to 8-bit values
    Serial.println(ARRAY[i]);
  }
  //const char text[] = "Hello World";
  radio.write(&ARRAY, sizeof(ARRAY));
  delay(100);
}
