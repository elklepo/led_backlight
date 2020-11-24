#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H

#include <ESP8266WebServer.h>  

class WifiConnection
{
private:
    std::unique_ptr<ESP8266WebServer> server;
public:
    WifiConnection(const char *ssid, const char *pass, int port, uint8_t led_pin);
    void handleClient(void);
};

#endif