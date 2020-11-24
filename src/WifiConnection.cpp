#include "../include/WifiConnection.h"
#include "../include/handlers/GETHandler.h"
#include "Arduino.h"

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

WifiConnection::WifiConnection(const char *ssid, const char *pass, int port, uint8_t led_pin)
{
    digitalWrite(led_pin, LOW); // led ON

    this->server = std::unique_ptr<ESP8266WebServer>(new ESP8266WebServer(port));

    Serial.println(ssid);
    Serial.println(pass);

    Serial.print("Connecting to ");
    Serial.print(ssid); Serial.println(" ...");
    WiFi.begin(ssid, pass);

    for (uint8_t i = 0; WiFi.status() != WL_CONNECTED; ++i) 
    {
        digitalWrite(led_pin, (const uint8_t[]){HIGH, LOW}[i % 2]); // toggle led
        delay(250);
        Serial.print('.');
    }

    digitalWrite(led_pin, LOW); // led ON
    Serial.println('\n');
    Serial.print("Connected to WiFi: ");
    Serial.println(WiFi.SSID()); 
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

    if (MDNS.begin("esp8266")) 
    {              // Start the mDNS responder for esp8266.local
        Serial.println("mDNS responder started");
    } 
    else 
    {
        Serial.println("Error setting up MDNS responder!");
    }

    server->addHandler(new GETHandler("/test"));
    server->addHandler(new GETHandler("/"));

    server->begin();

    digitalWrite(led_pin, HIGH); // led OFF
    Serial.println("HTTP server started");
}


void WifiConnection::handleClient(void)
{
    server->handleClient();
}