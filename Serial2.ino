

int ledPin = LED_BUILTIN;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  
}

//Função que vai ler uma string da Serial e retorna
String lerString(){
  String textoRecebido = "";
  char caracter;

  while(Serial.available()>0){

    caracter = Serial.read();

    if (caracter != '\n'){
      textoRecebido.concat(caracter);
    }
    delay(10);
  }
  Serial.print("Recebido: ");
  Serial.println(textoRecebido);

  return textoRecebido;
}

void loop() {
  if (Serial.available() > 0){

    String recebido = lerString();

    if(recebido == "acender"){
      digitalWrite(ledPin, HIGH);
    }

    if(recebido == "desligar"){
      digitalWrite(ledPin, LOW);
    }
  }
}
