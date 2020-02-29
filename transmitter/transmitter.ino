#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9,10);
int data[2];
#define button 2

#define Joystick A0

void setup() {
  pinMode(button,INPUT);
  radio.begin();
  radio.setChannel(5);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.openWritingPipe(0x1234567890LL);
  }

void loop() {
    data[0] = map(analogRead(Joystick),0,1023,0,180);
    data[1] = digitalRead(button);
    radio.write(&data,sizeof(data));
}
