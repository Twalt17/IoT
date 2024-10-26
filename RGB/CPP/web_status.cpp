#include"web_status.h"
#include<Arduino.h>

const char* ssid = "Tyler's iPhone";
const char* password = "yddhkird";





void connectWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void get_status() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;  // Use secure client
    HTTPClient http;
    client.setInsecure();  

    String url = "https://www.tylerwalters17.com/APIs/results.txt";


    // Send the GET request
    Serial.println("Sending request to: " + String(url));
     http.begin(client, url);
    http.GET();
    DynamicJsonDocument doc(1024);
    String full_response = http.getString();
    deserializeJson(doc,full_response);

    String Node = doc["Node"];
    String status = doc["status"];


}
}

String getStatus(int node, int led) {


  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;

    String url = "https://www.tylerwalters17.com/APIs/results.txt";
    Serial.println("Sending request to: " + url);

    http.begin(client, url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      DynamicJsonDocument doc(2048);
      String full_response = http.getString();
      Serial.println("Full Response: " + full_response);
      deserializeJson(doc,full_response);
    
        String key = "Node" + String(node) + "_LED" + String(led); 
        Serial.println(key);
        String status = doc[key];
        
        return status;
      

     
  }
  
  }
  return {};
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


String getRGB(int node, int rgb) {


  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;

    String url = "https://www.tylerwalters17.com/APIs/sliders.txt";
    Serial.println("Sending request to: " + url);

    http.begin(client, url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      DynamicJsonDocument doc(2048);
      String full_response = http.getString();
      Serial.println("Full Response: " + full_response);
      deserializeJson(doc,full_response);
    
        String key = "Node" + String(node) + "_RGB" + String(rgb); 
        Serial.println(key);
        String status = doc[key];
        
        return status;
      

     
  }
  
  }
  return {};
}