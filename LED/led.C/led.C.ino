int led = 12;


void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led,HIGH);
  Serial.write("High")
  delay(500);
 

  digitalWrite(led,LOW);
  Serial.write("Low")
  delay(500);
}
