const int LED = 2;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  delay(1000);
  digitalWrite(LED, HIGH);
  delay(10000);
  digitalWrite(LED, LOW);
}