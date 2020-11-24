#pragma once

#include <ESP8266WebServer.h>

class GETHandler : public RequestHandler 
{
  public:
    GETHandler(const char* uri)
    : _uri(uri)
    {}

    bool canHandle(HTTPMethod method, String uri) override 
    {
      return method == HTTP_GET && uri == _uri;
    }

    bool handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) override 
    { 
      if (!canHandle(requestMethod, requestUri)) { 
        return false;
      }

      server.send(200, "text/plain", "Requested URI: " + requestUri);
      
      return true;
    }

  protected:
    String _uri;  
};