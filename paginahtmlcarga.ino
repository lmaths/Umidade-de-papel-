#include <ESP8266WebServer.h>

//---------------------------------------------------------------
ESP8266WebServer server(80);

//-------------------VARIABLES GLOBALES--------------------------
int contconexion = 0;

const char *ssid = "matheuslima";
const char *password = "M@theus123000";

String XML, xmlTemperatura; 

unsigned long previousMillis = 0;

//--------CODIGO HTML y JavaScript-------------
String webSite = "<!DOCTYPE html>"
"<style>"
  "body {"
  "padding-top: 80px;"
  "text-align: center;"
 "font-family: monaco, monospace;"
  "background: url(https://www.smurfitkappa.com/-/media/video/english-videos/about_us_homepage_page_only.jpg?w=1366&h=450&hash=A36B8E8121A827A32B4487A128727A779CF73F7A) 50%;"
  "background-size: cover;"
  "background-repeat: no-repeat;"
"}"
"h1, h2, h3 {"
  "display: inline-block;"
  "background: #fff;"
"}"
"#imgpos {"
  "position: absolute; "
  "left: 35px; /* posiciona a 90px para a esquerda */ "
  "top: 25px; /* posiciona a 70px para baixo */"
  "}"
"h1 {"
  "font-size: 30px"
"}"
"h2 {"
  "font-size: 20px;"
"}"
"span {"
  "background: #fd0;"
"}"
"</style>"
"<html>"
"<head>"
"<meta charset='utf-8' />"
"<title>Controle de Umidade</title>"
"<h1> - Sistema para controle de <span> Umidade -</span></h1><br>"
"<img src='https://i.imgur.com/DQ43Q9e.png' alt='some text' width=250 height=45 id='imgpos'>"
"<script type='text/javascript'>"
"function loadDoc(){"
"  var xhttp = new XMLHttpRequest();"
"  xhttp.onreadystatechange = function() {"
"    if (this.readyState == 4 && this.status == 200) {"
"      myFunction(this);"
"    }"
"  };"
"  xhttp.open('GET','xml',true);"
"  xhttp.send();"
"  setTimeout('loadDoc()',500);"
"}"

"function myFunction(xml){"
"  var i;"
"  var xmlDoc = xml.responseXML;"
"  var dato ='';"
"  dato = xmlDoc.getElementsByTagName('TEMPERATURA')[0].childNodes[0].nodeValue;"
"  document.getElementById('temperatura').innerHTML = dato;"
"}"
"</script>"
"</head>"
"<body onload='loadDoc()'>"
"<h3> <a> - Umidade da carga: </a> <span> <a id='temperatura'></a> </span></h3>"
"</body>"
"</html>";

void construirXML(){
  XML="";
  XML+="<TEMPERATURA>";
  XML+=xmlTemperatura;
  XML+="</TEMPERATURA>";
}

void handleWebsite(){
  server.send(200,"text/html",webSite);
}

void handleXML(){
  construirXML();
  server.send(200,"text/xml",XML);
}

//---------------------------SETUP-------------------------------
void setup() {

  // Inicia Serial
  Serial.begin(115200);
  Serial.println("");

  // Conexión WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and contconexion <50) { 
    ++contconexion;
    delay(500);
    Serial.print(".");
  }
  

      Serial.println("WiFi conectado");
      Serial.println(WiFi.localIP());

  server.on("/",handleWebsite);
  server.on("/xml",handleXML);
  server.begin();
}

//--------------------------LOOP--------------------------------
void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) { 
    previousMillis = currentMillis;
    int analog = analogRead(0);
    analog = map(analog, 1023,0,0,100) * 2;
     String valor = String(analog);
    String aprovado = String("% - Aprovado");
    String reprovado = String("% - Reprovado");
    String testeteste = (valor + reprovado);

    String teste = (valor + aprovado);
   
    Serial.print(valor);

    if (analog < 15) {
      xmlTemperatura = (teste);
    } else {
       xmlTemperatura = (testeteste); //1 decimal
    }
   
  }

 
  server.handleClient();
}

