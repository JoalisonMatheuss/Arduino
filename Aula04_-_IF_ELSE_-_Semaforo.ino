int pinVermelho = 10; //led conectado ao pino 10
int pinAmarelo = 9; //led conectado ao pino 9
int pinVerde = 8; //led conectado ao pino 8
int pinBotao = 7; //botao conectado ao pino 7
int pinPedestreVermelho = 3; //led conectado ao pino 3
int pinPedestreVerde = 2; //led conectado ao pino 2

int faseSemaforo;

int estadoBotao;
int estadoAnteriorBotao;

int tempoPisca = 0; //variável para guardar o valor lido
int estadoPisca = HIGH;

void setup() {
  // put your setup code here, to run once:

  //Inicializar o modo de cada Pino

  // pinMode --> Configura o pino especificado para funcionar como uma entrada ou saída.

  pinMode(pinVerde, OUTPUT); //configura o pino digital como saída
  pinMode(pinAmarelo, OUTPUT); //configura o pino digita como saída
  pinMode(pinVermelho, OUTPUT); //configura o pino digita como saída
  pinMode(pinBotao, INPUT); //configura o pino digita como entrada
  pinMode(pinPedestreVerde, OUTPUT); //configura o pino digita como saída
  pinMode(pinPedestreVermelho, OUTPUT); //configura o pino digita como saída

  faseSemaforo = 1;

  estadoAnteriorBotao = digitalRead(pinBotao);
}

void loop() {
  // put your main code here, to run repeatedly:

  estadoBotao = digitalRead(pinBotao); //lê o pino de entrada

  if ((estadoBotao == HIGH) && (estadoAnteriorBotao == LOW)){
    if (faseSemaforo < 4){
      faseSemaforo = faseSemaforo +1;
    } else{
      faseSemaforo = 1;
    }
  }

  estadoAnteriorBotao = estadoBotao;

  if (faseSemaforo == 1){   //Semaforo Aberto(Verde)
    
    digitalWrite(pinVerde, HIGH); // aciona o LED com o valor alto
    digitalWrite(pinAmarelo, LOW); // desativa o LED com o valor baixo
    digitalWrite(pinVermelho, LOW); // desativa o LED com o valor baixo

    pinMode(pinPedestreVerde, LOW); // desativa o LED com o valor baixo
    pinMode(pinPedestreVermelho, HIGH); // aciona o LED com o valor alto
    
  }
  
  if (faseSemaforo == 2){   //Semaforo Amarelo
    
    digitalWrite(pinAmarelo, HIGH); // aciona o LED com o valor alto
    digitalWrite(pinVerde, LOW); // desativa o LED com o valor baixo
    digitalWrite(pinVermelho, LOW); // desativa o LED com o valor baixo

    pinMode(pinPedestreVerde, LOW); // desativa o LED com o valor baixo
    pinMode(pinPedestreVermelho, HIGH); // aciona o LED com o valor alto
    
   }
  
  if (faseSemaforo == 3){   //Semaforo Fechado(Vermelho)
    
    digitalWrite(pinVermelho, HIGH); // aciona o LED com o valor alto
    digitalWrite(pinVerde, LOW); // desativa o LED com o valor baixo
    digitalWrite(pinAmarelo, LOW); // desativa o LED com o valor baixo

    pinMode(pinPedestreVerde, HIGH); // aciona o LED com o valor alto
    pinMode(pinPedestreVermelho, LOW); // desativa o LED com o valor baixo
    
   }

   if (faseSemaforo == 4){ //Semaforo Pedestre Piscando
    
    digitalWrite(pinAmarelo, HIGH); // aciona o LED com o valor alto
    digitalWrite(pinVerde, LOW); // desativa o LED com o valor baixo
    digitalWrite(pinVermelho, LOW); // desativa o LED com o valor baixo

    tempoPisca = tempoPisca + 1;
    if (tempoPisca == 400){
      estadoPisca = !estadoPisca;
      tempoPisca = 0;
      
    }

    pinMode(pinPedestreVerde, LOW); // desativa o LED com o valor baixo
    pinMode(pinPedestreVermelho, estadoPisca); //acionando o led de acordo com o estado 
    
   }

   delay(1); //esperar
}
