int pinVermelho = 10;
int pinAmarelo = 9;
int pinVerde = 8;
int pinBotao = 7;
int pinPedestreVermelho = 3;
int pinPedestreVerde = 2;

int faseSemaforo;

int estadoBotao;
int estadoAnteriorBotao;

int tempoPisca = 0;
int fasePisca = HIGH;

void setup() {
  // put your setup code here, to run once:

  pinMode(pinVerde, OUTPUT);
  pinMode(pinAmarelo, OUTPUT);
  pinMode(pinVermelho, OUTPUT);
  pinMode(pinBotao, INPUT);
  pinMode(pinPedestreVerde, OUTPUT);
  pinMode(pinPedestreVermelho, OUTPUT);

  faseSemaforo = 1;
}

void loop() {
  // put your main code here, to run repeatedly:

  estadoBotao = digitalRead(pinBotao);

  if ((estadoBotao == HIGH) && (estadoAnteriorBotao == LOW)){
    if (faseSemaforo < 4){
      faseSemaforo = faseSemaforo +1;
    } else{
      faseSemaforo = 1;
    }
  }

  estadoAnteriorBotao = estadoBotao;

  if (faseSemaforo == 1){   //Semaforo Aberto(Verde)
    digitalWrite(pinVerde, HIGH);
    digitalWrite(pinAmarelo, LOW);
    digitalWrite(pinVermelho, LOW);

    pinMode(pinPedestreVerde, LOW);
    pinMode(pinPedestreVermelho, HIGH);
    
  }
  
  if (faseSemaforo == 2){   //Semaforo Amarelo
    digitalWrite(pinAmarelo, HIGH);
    digitalWrite(pinVerde, LOW);
    digitalWrite(pinVermelho, LOW);

    pinMode(pinPedestreVerde, LOW);
    pinMode(pinPedestreVermelho, HIGH);
    
   }
  
  if (faseSemaforo == 3){   //Semaforo Fechado(Vermelho)
    digitalWrite(pinVermelho, HIGH);
    digitalWrite(pinVerde, LOW);
    digitalWrite(pinAmarelo, LOW);

    pinMode(pinPedestreVerde, HIGH);
    pinMode(pinPedestreVermelho, LOW);
    
   }

   if (faseSemaforo == 4){ //Semaforo Pedestre Piscando
    digitalWrite(pinAmarelo, HIGH);
    digitalWrite(pinVerde, LOW);
    digitalWrite(pinVermelho, LOW);

    tempoPisca = tempoPisca + 1;
    if (tempoPisca == 400){
      fasePisca = !fasePisca;
      tempoPisca = 0;
      
    }

    pinMode(pinPedestreVerde, LOW);
    pinMode(pinPedestreVermelho, fasePisca);
    
   }

   delay(1);
}
