#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include<PubSubClient.h>

bool check_switch();
void connectWiFi();
float adc_read();
void reconnect();
void callback(char* topic, byte* payload, int length);


