#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <SPI.h>

Servo servo;
RF24 radio(9,10);
int data[2];

void setup() {
  radio.begin();
  radio.setDataRate(RF24_1MBPS);
  radio.PALevel(RF24_PA_HIGH);
}
