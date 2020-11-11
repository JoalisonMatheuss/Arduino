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

  if (req.indexOf("LED0on") != -1){
    digitalWrite(ledR, HIGH);
    statusLED0 = HIGH;
  }
  else if (req.indexOf("LED0off") != -1){
    digitalWrite(ledR, LOW);
    statusLED0 = LOW;
  }
  else if (req.indexOf("LED1on") != -1){
    digitalWrite(ledY, HIGH);
    statusLED1 = HIGH;
  }
  else if (req.indexOf("LED1off") != -1){
    digitalWrite(ledY, LOW);
    statusLED1 = LOW;
  }
  else if (req.indexOf("LED2on") != -1){
    digitalWrite(ledG, HIGH);
    statusLED2 = HIGH;
  }
  else if (req.indexOf("LED2off") != -1){
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
  client.println("<style> body{font-size: 20px; font-family: Arial, Helvetica, sans-serif; color: #000000;} section #banner {display: flex; justify-content: center;} div .container {display: flex; justify-content: space-between; width: 100%;} div .leds {height: 210px; display: flex;} .led1, .led2, .led3 {flex: 1; color: #000000; font-weight: bold; padding: 50px;} div .led1 {background-color: #3bc93b;} div .led2 {background-color: #ffee00;} div .led3 {background-color: #FF0000;} button {border: 3px solid #CCCCCC; border-radius: 5px; font-size: 20px; background-color: #CCCCCC; padding: 10px; border: none; border-radius: 10px; cursor: pointer;} button:hover {box-shadow: 5px 5px 5px #424040;} </style>");
  client.println("");
  client.println("</head>");
  client.println("<body>");
  client.println("<section id=\"banner\">");
  client.println("<div class=\"container\">");
  client.println("<div class=\"leds\">");
  client.println("<div class=\"led\">");

  if (!statusLED0){
    client.println("<p> LED VERMELHO <a href=\"LED0on\"> <button>LIGAR</button></a> </p>");
  }
  else {
    client.println("<p> LED VERMELHO <a href=\"LED0off\"> <button>DESLIGAR</button></a> </p>");
  }

  client.println("</div>");
  client.println("<div class=\"led\">");
  
  if (!statusLED1){
    client.println("<p> LED AMARELO <a href=\"LED1on\"> <button>LIGAR</button></a> </p>");
  }
  else {
    client.println("<p> LED AMARELO <a href=\"LED1off\"> <button>DESLIGAR</button></a> </p>");
  }
  
  client.println("</div>");
  client.println("<div class=\"led\">");

  if (!statusLED2){
    client.println("<p> LED VERDE <a href=\"LED2on\"> <button>LIGAR</button></a> </p>");
  }
  else {
    client.println("<p> LED VERDE <a href=\"LED2off\"> <button>DESLIGAR</button></a> </p>");
  }
  
  client.println("</div>");
  
  client.println("</div>");
  client.println("</div>");
  client.println("<section>");
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
