#include <Arduino.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include "LiquidCrystal_I2C.h"
#include "TinyGPS++.h"

const int DELAY = 100;
const int SWITCH_TIME = 5000;

int currentModeTime = 0;
bool showLocation = false;

LiquidCrystal_I2C lcd(0x3F, 16, 2);
SoftwareSerial gps_serial(A3, A2);
TinyGPSPlus gps_parser;

Servo servo;
RF24 radio(9,10);
int data[2];
int led;

void setup() {
  Serial.begin(9600);
  gps_serial.begin(9600);
  pinMode(led,OUTPUT);
  radio.begin();
  radio.setChannel(5);
  radio.setDataRate(RF24_1MBPS);
  radio.openReadingPipe(1,0x1234567890LL);
  radio.startListening(); 
}

String twoDigits(int x) {
  if(x < 10) return "0" + String(x);
  else return String(x);
}

void loop() {
  if(radio.available()) {
    digitalWrite(led,HIGH);
    radio.read(&data,sizeof(data));
    servo.write(data[0]);
  }else{
    digitalWrite(led,LOW);
  }
  while(gps_serial.available() > 0) {
    char temp = gps_serial.read();
    Serial.write(temp);
    gps_parser.encode(temp);
  }
  String lat  = "Unknown         ";
    String lng  = "location        ";
    if(gps_parser.location.isValid()) {
        lat = "Lat: " + String(gps_parser.location.lat(), 6);
        lng = "Lng: " + String(gps_parser.location.lng(), 6);
    }
    String date = "Unknown date    ";
    if(gps_parser.date.isValid()) {
        date = twoDigits(gps_parser.date.day()) + "/" +
               twoDigits(gps_parser.date.month()) + "/" +
               String(gps_parser.date.year()) + "      ";
    }
 String time = "Unknown time    ";
    if(gps_parser.time.isValid()) {
        time = twoDigits(gps_parser.time.hour()) + ":" +
               twoDigits(gps_parser.time.minute()) + ":" +
               twoDigits(gps_parser.time.second()) + " UTC    ";
    }

    if(showLocation) {
        lcd.setCursor(0, 0);
        lcd.print(lat);
        lcd.setCursor(0, 1);
        lcd.print(lng);
    } else { // show date and time
        lcd.setCursor(0, 0);
        lcd.print(date);
        lcd.setCursor(0, 1);
        lcd.print(time);
    }

    delay(DELAY);
    currentModeTime += DELAY;
    if(currentModeTime >= SWITCH_TIME) {
        lcd.clear();
        showLocation = !showLocation;
        currentModeTime = 0;
    }
}
