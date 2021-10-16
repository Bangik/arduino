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
    pinMode(pinBtn[i], INPUT_PULLUP);
  }
  
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(pinBuzz, OUTPUT);

  servos.attach(10);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(pinBtn[0]), bukaServo, FALLING);
  attachInterrupt(digitalPinToInterrupt(pinBtn[1]), tutupServo, RISING);

  Serial.println("Masukkan 1 --> Masuk Ruangan");
  Serial.println("Masukkan 2 --> Keluar Ruangan");
  Serial.println();
  
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

void bukaServo(){
  servos.write(180);
//  delay();
}

void tutupServo(){
  servos.write(0);
}

void loop() {
  cekSuhu(pinSuhu);
  if(Serial.available()){
    int pilihan = Serial.read();
    if(pilihan == 49){
      Serial.println("1");
      if(cekJarak() <= 200){
        if(cekSuhu(pinSuhu) >= 38){
          Serial.print("Suhu anda = ");
          Serial.println(cekSuhu(pinSuhu));
          digitalWrite(pinBuzz, HIGH);
          digitalWrite(pinLed[0], HIGH);
          delay(2000);
          digitalWrite(pinBuzz, LOW);
          digitalWrite(pinLed[0], LOW);
          servos.write(0);
        }else{
          Serial.print("Suhu anda = ");
          Serial.println(cekSuhu(pinSuhu));
          digitalWrite(pinBuzz,LOW);
          digitalWrite(pinLed[1], HIGH);
          servos.write(180);
          delay(3000);
          servos.write(0);
          digitalWrite(pinLed[1], LOW);
        }
      }else{
        Serial.println("Jarak terlalu jauh");
        delay(500);
        digitalWrite(pinBuzz,LOW);
        servos.write(0);
      }
    }
    if(pilihan == 50){
      Serial.println("2");
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
}
