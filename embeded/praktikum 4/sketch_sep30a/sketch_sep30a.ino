#include <LiquidCrystal.h>
String data;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("2");
  Serial.flush(); 
}

void loop() {
  String data="";
  while (Serial.available() >0) {
    data+= (char) Serial.read();
    delay (5);
  }
  
  lcd.setCursor(0,0);
  lcd.print("2");
  lcd.setCursor(0,1);
  delay (50);
  
  if (data == "KEDIP"){
    lcd.setCursor (0,1);
    lcd.print(data);
    delay(1000);
    lcd.clear();
  }else if(data == "HIDUP"){
    lcd.setCursor (0,1);
    lcd.print(data);
    delay(1000);
    lcd.clear();
  }else if (data == "MATI"){
    lcd.setCursor (0,1);
    lcd.print(data);
    delay(1000);
    lcd.clear();
  }
}
