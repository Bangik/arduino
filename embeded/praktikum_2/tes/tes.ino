int pinLed = 6;
int button = 2;
int bacaButton, lastButton, kondisi = 0;
void setup() {
 pinMode (pinLed, OUTPUT);
 pinMode (button, INPUT);
}
void loop() {
  digitalWrite(pinLed, true);
  delay(500);
  digitalWrite(pinLed, false);
  delay(1000);
}
