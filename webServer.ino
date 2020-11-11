#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


const byte ledR = D2;
const byte ledY = D1;
const byte ledG = D0;

boolean statusLED0 = LOW;
boolean statusLED1 = LOW;
boolean statusLED2 = LOW;

char ssid[] = "FTTH JAILTON";
char senha[] = "afjo2811";

WiFiServer server(80);

void setup() {
  pinMode(ledR, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledG, OUTPUT);
  
  Serial.begin(115200);
  delay(10);

  conectaWiFi(ssid, senha);

  server.begin();
  Serial.println("Servidor inicializado");

}

void loop() {

  WiFiClient client = server.available();
  if(!client) {
    return;
  }

  while(!client.available()){
    delay(1);
  }

  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  if (req.indexOf("LEDon") != -1){
    digitalWrite(ledR, HIGH);
    statusLED0 = HIGH;
  }
  else if (req.indexOf("LEDoff") != -1){
    digitalWrite(ledR, LOW);
    statusLED0 = LOW;
  }
  if (req.indexOf("LEDon") != -1){
    digitalWrite(ledY, HIGH);
    statusLED1 = HIGH;
  }
  else if (req.indexOf("LEDoff") != -1){
    digitalWrite(ledY, LOW);
    statusLED1 = LOW;
  }
  if (req.indexOf("LEDon") != -1){
    digitalWrite(ledG, HIGH);
    statusLED2 = HIGH;
  }
  else if (req.indexOf("LEDoff") != -1){
    digitalWrite(ledG, LOW);
    statusLED2 = LOW;
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<title>Acendendo Lampadas</title>");
  client.println("<meta charset=\"UTF-8\" >");
  client.println("<style>  </style>");
  client.println("");
  client.println("</head>");
  client.println("<body>");
  client.println("<div class='led'>");

  if (!statusLED0){
    client.println("<p> LED VERMELHO <a href=\"LEDon\"> <button>LIGAR</button> </p>");
  }
  else {
    client.println("<p> LED VERMELHO <a href=\"LEDoff\"> <button>DESLIGAR</button> </p>");
  }

  client.println("/<div>");
  client.println("<div class='led'>");
  
  if (!statusLED1){
    client.println("<p> LED AMARELO <a href=\"LEDon\"> <button>LIGAR</button> </p>");
  }
  else {
    client.println("<p> LED AMARELO <a href=\"LEDoff\"> <button>DESLIGAR</button> </p>");
  }
  
  client.println("/<div>");
  client.println("<div class='led'>");

  if (!statusLED2){
    client.println("<p> LED VERDE <a href=\"LEDon\"> <button>LIGAR</button> </p>");
  }
  else {
    client.println("<p> LED VERDE <a href=\"LEDoff\"> <button>DESLIGAR</button> </p>");
  }
  
  client.println("/<div>");
  client.println("</body>");
  client.println("</html>");
  
}

void conectaWiFi(char SSID[],char SENHA[]){

  Serial.print("Conectando a rede ");
  Serial.println(SSID);

  WiFi.begin(SSID,SENHA);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println(" ");
  Serial.println("WiFi Conectado");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());
}
