#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "TP-LINK_6642"
#define STAPSK  "40462929"
#define pin 0

#endif

const char* ssid = STASSID;
const char* password = STAPSK;
const char index_html[] PROGMEM={"<style>\n  body {\n  padding-top: 80px;\n  text-align: center;\n  font-family: monaco, monospace;\n  background: url(http://media.giphy.com/media/Jrd9E2kuPuOYM/giphy.gif) 50%;\n  background-size: cover;\n}\nh1, h2 {\n  display: inline-block;\n  background: #fff;\n}\nh1 {\n  font-size: 30px\n}\nh2 {\n  font-size: 20px;\n}\nspan {\n  background: #fd0;\n}\n</style>\n\n<html>\n<h1>Sistema para controle de umidade <span>de carga</span></h1><br>\n<h2></h2>\n\n\n</html>"};

ESP8266WebServer server(80);



void handleRoot() {

  if(analogRead(pin) >= 500) {
     server.send_P(200, "text/html", index_html);
 } else {
    Serial.print("não foi possivel");
 }

}

void handleNotFound() {

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  
}

void setup(void) {
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
