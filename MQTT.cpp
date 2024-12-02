#include "MQTT.h"
#include<Arduino.h>
#include <String.h>


float adc_read(){
    float adcVal = analogRead(A0);
    float Vin = adcVal * (3.3 / 1023); 
    Serial.println("Input Voltage:  " );
    Serial.println(Vin); 
    return Vin;
}


bool check_switch() {
    if (digitalRead(D1) == LOW) {
        delay(50);  // Debounce delay
        if (digitalRead(D1) == LOW) {
            return true;
        }
    }
    return false;
}
/*
void connectWiFi() {
  String ssid = "Tyler's iPhone";
  String password = "yddhkird";

  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}
*/

