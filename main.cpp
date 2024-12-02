#include <Arduino.h>
#include "MQTT.h"
#include<PubSubClient.h>

const char* ssid = "Tyler's iPhone";
const char* password = "yddhkird";

// MQTT variables
const char* mqtt_server = "broker.mqtt-dashboard.com";
const char* publishTopic = "testtopic/temp/outTopic/voltage";   // outTopic where ESP publishes
const char* subscribeTopic = "testtopic/temp/inTopic/inESP";  // inTopic where ESP has subscribed to
#define publishTimeInterval 10000 // in seconds 
const char* publishTopic2 = "testtopic/temp/outTopic/LEDon";

// Definitions 
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
#define BUILTIN_LED 2 // built-in LED
#define LEDPIN D2
char msg[MSG_BUFFER_SIZE];
int value = 0;
int ledStatus = 0;

WiFiClient espClient;
PubSubClient client(espClient); // define MQTTClient 


void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
  //------------------------------------------

void callback(char* topic, byte* payload, int length) {
  Serial.print("Message arrived ["); // Received the incoming message
  Serial.print(topic);
  Serial.print("] ");
  String message = ""; 
  for (int i = 0; i < length; i++) {
    // Serial.print((char)payload[i]);  // the received value is in (char)payload[i]
    message += (char)payload[i];
  }
  Serial.println(message);
   if (message == "1"){
    digitalWrite(LEDPIN,HIGH);
   }
   else if (message == "0"){
    digitalWrite(LEDPIN, LOW);
   }

  // Switch on the LED if an 1 was received as first character
  // add your code here

}
  //------------------------------------------

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // ... and resubscribe
      client.subscribe(subscribeTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
 //------------------------------------------

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(LEDPIN,OUTPUT);
}
//------------------------------------------
void loop() {

  if (!client.connected()) {
    reconnect(); // check for the latest value in inTopic 
  }
  client.loop();

// Publish to outTopic 

  if (check_switch()) {
    bool retain = true;
    float value = adc_read();
    snprintf(msg, sizeof(msg), "%.2f", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(publishTopic, msg, retain);
    Serial.println("1");
    client.publish(publishTopic2,"1", retain);
    delay(500);
  }
}
