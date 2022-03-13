//Sensores
int PotPin = A0;
int PotValue;
int PulsadorEPin = 5;
int PulsadorEValue;
int PulsadorCPin = 6;
int PulsadorCValue;
//Actuadores
int LedPin = 7;
int BuzzerPin = 8;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LedPin,OUTPUT);
  pinMode(BuzzerPin,OUTPUT);
  pinMode(PulsadorEPin,INPUT);
  pinMode(PulsadorCPin,INPUT);
}
bool EstufaEncendida = false; 
void loop() {
  // put your main code here, to run repeatedly:
  PotValue = analogRead(PotPin);// Almacenar el valor del potenciometro en una variable
  /* Calculo del Temporizador
  Potenciometro --> 0 -- 1023
                --> 1 -- 10 (map)
  */
  PotValue = map(PotValue,0,1023,1,10);
  PotValue = constrain(PotValue,1,10);
  Serial.print("Temporizador: ");
  Serial.print(PotValue);
  Serial.println();
  /*
    Si se enciende la estufa iniciar el temporizador
  */
  PulsadorEValue = digitalRead(PulsadorEPin);
  PulsadorCValue = digitalRead(PulsadorCPin);
  if (EstufaEncendida == false && PulsadorEValue == HIGH){
    // Recorrido para mostrar el conteo
    Serial.println("Encender estufa: ");
    for(int i=1; i <= PotValue; i++){
       Serial.print("Tiempo: ");
       Serial.print(i);
       Serial.print(" s");
       Serial.println();
       delay(1000);
    }
    EstufaEncendida = true;
  }
  // Si la estufa Esta encendida Encender Buzzer y led intermitente hasta que oprima el
  // otro pulsador
  if (EstufaEncendida == true && PulsadorCValue == LOW) {
      digitalWrite(BuzzerPin,HIGH);
      // intermitencia
      digitalWrite(LedPin,HIGH);
      delay(200);
      digitalWrite(LedPin,LOW);
      delay(200);
  } else{
      digitalWrite(BuzzerPin,LOW);
      digitalWrite(LedPin,LOW);
      EstufaEncendida = false;
  }
}
