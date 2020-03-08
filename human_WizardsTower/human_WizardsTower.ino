// Sends a message through an RF transmitter outside the arena to an RF receiver on the robot inside the arena

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(7, 8);  // CE, CSN
String message = "#MRDC"; //Message to be sent to wizard's tower through robot
const byte address[6] = "00001"; //address through which two modules communicate.

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
  byte ARRAY[message.length()+1]; //Turns string into an array
  int size = (sizeof(ARRAY)/sizeof(ARRAY[0]));
  message.getBytes(ARRAY,message.length()+1); //Initalizes array to ASCII bytes (in 7-bit)
   for (int i = 0; i <= size; i++){
    ARRAY[i] = ARRAY[i] + 128;                //Converts 7-bit values to 8-bit values
    Serial.println(ARRAY[i]);
  }
  radio.write(&ARRAY, sizeof(ARRAY)); //RF Transmission
  delay(100);
}
