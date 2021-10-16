#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define btn1 A0
#define btn2 A1
#define btn3 A2
String a = "KEDIP";
String b = "HIDUP";
String c = "MATI";
String data ; 

void setup() {
  Serial.begin(9600); 
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("KIRIM");
  lcd.setCursor(0,1);
  
  if (Serial.available()){
    data = Serial.read();
    Serial.print(data);
    lcd.print(data);
  }

  int n1= digitalRead(btn1);
  int n2= digitalRead(btn2);
  int n3= digitalRead(btn3);

  if (n1==0) {
    lcd.clear();
    Serial.print (a);
    lcd.setCursor(0,1) ;
    lcd.print(a);
    delay(500);
    lcd.clear();
  }

  if (n2==0) {
    lcd.clear();
    Serial.print (b);
    lcd.setCursor(0,1) ;
    lcd.print(b);
    delay(500);
    lcd.clear();
  }

  if (n3==0) {
    lcd.clear();
    Serial.print (c);
    lcd.setCursor(0,1) ;
    lcd.print(c);
    delay(500);
    lcd.clear();
  }

  lcd.setCursor(0, 1);
}
