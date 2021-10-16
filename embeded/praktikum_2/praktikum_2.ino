int pinLed[] = {3,5,6,9};
int pinBtn[] = {2,4,7};
int pinBuzz = 10;
int btnState1, btnState2, btnState3, lastBtn1, lastBtn2, lastBtn3, kondisiBtn1, kondisiBtn2, kondisiBtn3 = 0;
boolean sr = true;

void setup() {
  for (int i=0; i<4; i++){
    pinMode(pinLed[i], OUTPUT);
  }

  for (int i=0; i<3; i++){
    pinMode(pinBtn[i], INPUT);
  }

  pinMode(pinBuzz, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  btnState1 = digitalRead(pinBtn[0]);
  btnState2 = digitalRead(pinBtn[1]);
  btnState3 = digitalRead(pinBtn[2]);

  if((btnState1 == HIGH) && (lastBtn1 == LOW) ){
    kondisiBtn1 = 1 - kondisiBtn1;
    delay(10);
  }
  lastBtn1 = btnState1;

  if((btnState2 == HIGH) && (lastBtn2 == LOW) ){
    kondisiBtn2 = 1 - kondisiBtn2;
    delay(10);
  }
  lastBtn2 = btnState2;

  if((btnState3 == HIGH) && (lastBtn3 == LOW) ){
    kondisiBtn3 = 1 - kondisiBtn3;
    delay(10);
  }
  lastBtn3 = btnState3;
  
  if(kondisiBtn1 == 1){
    btnOneLow();
  }else{
    btnOneHigh();  
  }

  if(kondisiBtn2 == 1){
    btnTwoLow();
  }else{
    btnTwoHigh();   
  }

  if(kondisiBtn3 == 1){
    btnThreeLow();
  }else{
    btnThreeHigh();   
  }
}

void btnOneLow(){
  for(int i = 0; i < 4; i++){
    digitalWrite(pinLed[i],HIGH);
    delay(500);
  }
  digitalWrite(pinBuzz,HIGH);
  delay(100);
  digitalWrite(pinBuzz,LOW);
}

void btnOneHigh(){
  for(int i = 0; i < 4; i++){
    digitalWrite(pinLed[i],LOW);
  }
  digitalWrite(pinBuzz,LOW);
}

void btnTwoLow(){
  for (int dutyCycle = 0 ; dutyCycle <= 255; dutyCycle += 5){
    analogWrite(pinLed[3], dutyCycle);
    delay(100);
  }
  delay(1000);
  for (int dutyCycle = 0 ; dutyCycle <= 255; dutyCycle += 5){
    analogWrite(pinLed[2], dutyCycle);
    delay(100);
  }
  delay(1000);
  for (int dutyCycle = 0 ; dutyCycle <= 255; dutyCycle += 5){
    analogWrite(pinLed[1], dutyCycle);
    delay(100);
  }
  delay(1000);
  for (int dutyCycle = 0 ; dutyCycle <= 255; dutyCycle += 5){
    analogWrite(pinLed[0], dutyCycle);
    delay(100);
  }
  delay(1000);
}

void btnTwoHigh(){
  for(int i = 0; i < 4; i++){
    digitalWrite(pinLed[i],LOW);
  }
}

void btnThreeLow(){
  if(sr == true){
    Serial.println("Masukkan 1 --> Menyalakan 4 LED kelap-kelip");
    Serial.println("Masukkan 2 --> Buzzer seperti suara sirine (ON-OFF-ON-OFF) selama 5 detik");
    Serial.println("Masukkan 3 --> Lampu berjalan dari kiri ke kanan dengan setiap perindahan nayala LED diberi tanda bunyi buzzer");
    Serial.println("Masukkan 4 --> Menggunakan PWM untuk memadamkan 4 LED");
    Serial.println();
    sr = false;
  }
  
  if(Serial.available()){
    int pilihan = Serial.read();
    if(pilihan == 49){
      Serial.println("1");
        optionOne();
    }
    if(pilihan == 50){
      Serial.println("2");
      optionTwo();
    }
    if(pilihan == 51){
      Serial.println("3");
      optionThree();
    }
    if(pilihan == 52){
      Serial.println("4");
      optionFour();
    }
  }
}

void btnThreeHigh(){
  
}

void optionOne(){
  for(int i=0; i<4; i++){
    digitalWrite(pinLed[0],HIGH);
    digitalWrite(pinLed[1],HIGH);
    digitalWrite(pinLed[2],HIGH);
    digitalWrite(pinLed[3],HIGH);
    delay(1000);
    digitalWrite(pinLed[0],LOW);
    digitalWrite(pinLed[1],LOW);
    digitalWrite(pinLed[2],LOW);
    digitalWrite(pinLed[3],LOW);
    delay(1000);
  }
}

void optionTwo(){
  for(int i=0; i<5; i++){
    digitalWrite(pinBuzz,HIGH);
    delay(100);
    digitalWrite(pinBuzz,LOW);
    delay(1000);
  }
}

void optionThree(){
  for (int i=0; i < 3; i++){
    digitalWrite(pinLed[i],HIGH);
    delay(1000);
    digitalWrite(pinLed[i],LOW);
    delay(1000);
    digitalWrite(pinBuzz,HIGH);
    delay(100);
    digitalWrite(pinBuzz,LOW);
    delay(1000);   
  }
}

void optionFour(){
  for (int dutyCycle = 255 ; dutyCycle >= 0; dutyCycle -= 5){
    analogWrite(pinLed[0], dutyCycle);
    analogWrite(pinLed[1], dutyCycle);
    analogWrite(pinLed[2], dutyCycle);
    analogWrite(pinLed[3], dutyCycle);
    delay(300);
  }
}
