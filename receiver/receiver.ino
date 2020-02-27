#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <SPI.h>

Servo servo;
RF24 radio(9,10);
int data[2];
int led;

void setup() {
  pinMode(led,OUTPUT);
  radio.begin();
  radio.setChannel(5);
  radio.setDataRate(RF24_1MBPS);
  radio.PALevel(RF24_PA_HIGH);
  radio.openReadingPipe(1,0x1234567890LL)
  radio.startListening(); 
}

void loop() {
  if(radio.available) {
    digitalWrite(led,HIGh);
    radio.read(&data,sizeof(data))
    servo.write(data[0])
  }else{
    digitalWrite(led,LOW);
  }
}
