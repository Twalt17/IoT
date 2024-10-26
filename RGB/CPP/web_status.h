#ifndef WEB_STATUS_H
#define WEB_STATUS_H
#include <String.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <vector>
#include <utility>
#include <tuple>

bool check_switch();
void connectWiFi();
void get_status();
String getStatus(int node, int led);
String getRGB(int node, int rgb);

#endif