#include <Arduino.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <SPI.h>
#include <LiquidCrystal.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>

Servo servo;
RF24 radio(9,10);
int data[2];
int led;
SoftwareSerial gpsSerial(3,4);
TinyGPS gps;
float lat;
float lon;

void setup() {
  gpsSerial.begin(9600);
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  radio.begin();
  radio.setChannel(5);
  radio.setDataRate(RF24_1MBPS);
  radio.openReadingPipe(1,0x1234567890LL);
  radio.startListening(); 
}

void loop() {
  if(radio.available()) {
    digitalWrite(led,HIGH);
    radio.read(&data,sizeof(data));
    servo.write(data[0]);
    if(data[1] == HIGH){
      digitalWrite(led,HIGH);
      }else{
      digitalWrite(led,LOW);  
        }
  }
  while(gpsSerial.available()) {
    if(gps.encode(gpsSerial.read())) {
      gps.f_get_position(&lat,&lon);
      Serial.println(lat);
      Serial.println(lon);
      }
    }
}
