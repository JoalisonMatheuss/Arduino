
int led = LED_BUILTIN;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(led, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  char caracter;

  caracter = Serial.read();

   if (caracter == 'a'){
     Serial.println("Ligou o Led");
     digitalWrite(led, HIGH);
   }
   else{
     if (caracter == 'b'){
       Serial.println("Desligou o Led");
       digitalWrite(led, LOW);
     }
   }
   delay(100);
}
