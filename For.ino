int pinLed[9] = {12,11,10,9,8,7,6,5,4}; //Array = [] --> Lista de 9 elementos
int numeroLed;

void setup() {

  int x;
  for (x = 0; x <= 8; x = x+1){
    pinMode(pinLed[x], OUTPUT);
  }
}
void loop() {
  
  for (numeroLed = 0; numeroLed <= 8; numeroLed = numeroLed+1){
    digitalWrite(pinLed[numeroLed], HIGH);
    delay(200);
  }
}
