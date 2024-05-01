void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  float Sensor_Data = analogRead(A0);
  int Temp = (Sensor_Data*500)/1023;

  if(Temp<15)
  {
    digitalWrite(13,HIGH);
  }
  else
  {
    digitalWrite(13,LOW);
  }
}
