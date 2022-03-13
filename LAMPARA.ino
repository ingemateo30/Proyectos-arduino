int Do_note=262;
int Re_note = 294;
int Mi_note = 330;
int Fa_note = 349;
int Sol_note = 392;
int La_note = 440;
int Si_note = 494;
int DoH_note = 523;

int duration = 1000;

// Sensores
int MicPin = A0;
int MicValue;
// Actuadores
int LedPin1 = 7;
int LedPin2 = 9;
int LedPin3 = 10;
int BuzzerPin = 8; 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LedPin1,OUTPUT);
  pinMode(LedPin2,OUTPUT);
  pinMode(LedPin3,OUTPUT);
  pinMode(BuzzerPin,OUTPUT);
}
bool BabyCry = false;
void loop() {
  // put your main code here, to run repeatedly:
  MicValue = analogRead(MicPin); // Asignar en una variable los datos del microfono
  Serial.println(MicValue);
  /*
    Si el bebe llorar encender cada led con cada tonalidad
    Si deja de llorar esperar un segundo y apagar los leds y el buzzer
  */

  // Bebe para de llorar
   if (BabyCry == true && MicValue < 30){
      delay(1000);
      digitalWrite(LedPin1,LOW);
      digitalWrite(LedPin2,LOW);
      digitalWrite(LedPin3,LOW);
      digitalWrite(BuzzerPin,LOW);
      BabyCry = false;
      delay(1000);
   }
  // Bebe Llorando
  if (BabyCry == false && MicValue >=30){
      digitalWrite(LedPin1,HIGH);
      tone(BuzzerPin,Do_note,duration);
      delay(1000);
      digitalWrite(LedPin2,HIGH);
      tone(BuzzerPin,Si_note,duration);
      delay(1000);
      digitalWrite(LedPin3,HIGH);
      tone(BuzzerPin,Fa_note,duration);
      delay(1000);
      BabyCry = true;
  }
}
