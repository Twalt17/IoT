#include <Arduino.h>
#include "web_status.h"

const int ledPin = D2;
const int RGB1 = D3; // Red pin for RGB LED
const int RGB2 = D5; // Green pin for RGB LED
const int RGB3 = D6; // Blue pin for RGB LED

void setup() {
 Serial.begin(9600);  // Start serial communication
  connectWiFi();          // Connect to WiFi
  pinMode(ledPin,OUTPUT);

  pinMode(RGB1, OUTPUT);
  pinMode(RGB2, OUTPUT);
  pinMode(RGB3, OUTPUT);
}

void loop() {
  if (check_switch()) {
    String status1 = getStatus(1,1);
    String rgb1 = getRGB(1,1);
    int rgb1_int = rgb1.toInt();

    String rgb2 = getRGB(1,2);
    int rgb2_int = rgb2.toInt();

    String rgb3 = getRGB(1,3);
    int rgb3_int = rgb3.toInt();

    Serial.println("Single color LED Status: " + status1);
    if (status1 == "on"){
      digitalWrite(ledPin, HIGH);  // Turn on the LED
    } else if (status1 == "off")
    {
      digitalWrite(ledPin, LOW);
    }
    else {
      Serial.println("undefined state");
    }

    Serial.println("RGB1 status: " + rgb1);
    analogWrite(RGB1, rgb1_int);

    Serial.println("RGB3 status: " + rgb2);
    analogWrite(RGB2, rgb2_int);

    Serial.println("RGB3 status: " + rgb3);
    analogWrite(RGB3, rgb3_int);


    
    
   
    }
  }
