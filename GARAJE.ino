#include <Servo.h>

//Sensores de entrada (Potenciometro y PhotoResistor)
int PotPin = A0;
int PotValue;
int LightPin = A1;
int LightValue;
//Sensores de salida (Buzzer, Led y el servo)
int LedPin = 3;
int BuzzerPin = 5;
int ServoPin = 6;
Servo servo;
void setup() {
  // put your setup code here, to run once:
  //Inicializar el monitor Serial
  Serial.begin(9600);
  pinMode(LedPin,OUTPUT);
  pinMode(BuzzerPin,OUTPUT);
  //pinMode --> servo.attach
  servo.attach(ServoPin);
  //Ajustar el servo en 0 grados
  servo.write(0);
}
bool CarroEnGaraje = false;
void loop() {
  // put your main code here, to run repeatedly:
  PotValue    = analogRead(PotPin);// 0 -1024 
  LightValue  = analogRead(LightPin);
 /* Codigo Para calibrar el sensor de luz (establecer los parametros de que es 
  *  Oscuridad y que es luz )
 // digitalWrite(LedPin,HIGH);
 // Serial.print("Sensor de Luz: ");
 // Serial.print(LightValue);
 // Serial.println();
 // delay(100);
 */
 /*
  Cuando se acerque un carro (potenciometro valor mayor a 500)
  -- Servo Igual 90 (grados)
  -- Se enciende el led
 */
 Serial.print("Sensor del carro: ");
 Serial.print(PotValue);
 Serial.println();
 if(PotValue >500 && CarroEnGaraje==false){
  servo.write(90);
  digitalWrite(LedPin,HIGH);
  CarroEnGaraje=true;
  delay(5000);
 }
 /*
    Cuando el sensor de luz este en oscuridad > 200
    -- Servo Igual a 0 (grados)
    -- Led se apaga
    -- Buzzer se enciende (90 - 0)
 */
 if(LightValue > 350 && CarroEnGaraje==true){
    digitalWrite(LedPin,LOW);
    digitalWrite(BuzzerPin,HIGH);
    for(int i=90; i>=0;i=i-10){// 90 80 70 60 50 40 0
      servo.write(i);// 90 - 80 - 70 - 60 - ... - 0 
      delay(1000);
    }
    digitalWrite(BuzzerPin,LOW);
    CarroEnGaraje=false;
 }
}
