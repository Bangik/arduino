//inisialisasi variabel
#include <Servo.h>
#define echoPin 11
#define trigPin 12
Servo servos;
int pinLed[] = {6,7,8,9};
int pinBtn[] = {2,3,4};
int pinSuhu = A1;
int pinBuzz = 5;

int sudut = 0;
long durasi;
int jarak;

void setup() {
  for (int i=0; i<4; i++){
    pinMode(pinLed[i], OUTPUT);
  }

  for (int i=0; i<3; i++){
    pinMode(pinBtn[i], INPUT);
  }
  
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(pinBuzz, OUTPUT);

  servos.attach(10);
  Serial.begin(9600);
  
  servos.write(0);
}

int cekSuhu(int pin){
  int suhu = 0;
  suhu = analogRead(pin);
  float vout = suhu*(5000/1024.0);
  float temperatur = vout/10;
  return temperatur;
}

int cekJarak(){
  digitalWrite(trigPin, LOW);
  delay(100);
  digitalWrite(trigPin, HIGH);
  delay(100);
  digitalWrite(trigPin, LOW);
  durasi = pulseIn(echoPin, HIGH);
  jarak = durasi * 0.034 / 2;
  return jarak;
}

void loop() {
  cekSuhu(pinSuhu);
  Serial.print(cekSuhu(pinSuhu));
  int btnState1 = digitalRead(pinBtn[0]);
  int btnState2 = digitalRead(pinBtn[0]);
  if(btnState1 == 0){
    if(cekJarak() <= 200){
      if(cekSuhu(pinSuhu) >= 38){
        Serial.print(cekSuhu(pinSuhu));
        digitalWrite(pinBuzz, HIGH);
        digitalWrite(pinLed[0], HIGH);
        delay(500);
        digitalWrite(pinBuzz, LOW);
        digitalWrite(pinLed[0], LOW);
        servos.write(0);
      }else{
        Serial.print(cekSuhu(pinSuhu));
        digitalWrite(pinBuzz,LOW);
        digitalWrite(pinLed[1], HIGH);
        servos.write(180);
        delay(3000);
        servos.write(0);
        digitalWrite(pinLed[1], LOW);
      }
    }else{
      Serial.print("Jarak terlalu jauh");
      delay(500);
      digitalWrite(pinBuzz,LOW);
      servos.write(0);
    }
  }
  if(btnState2 == 0){
    if(cekJarak() <= 200){
      digitalWrite(pinLed[3], HIGH);
      servos.write(180);
      delay(3000);
      servos.write(0);
      digitalWrite(pinLed[3], LOW);
    }else{
      digitalWrite(pinLed[2], HIGH);
      servos.write(0);
      digitalWrite(pinLed[2], LOW);
    }
  }
}
