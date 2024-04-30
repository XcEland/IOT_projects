#include <SoftwareSerial.h>

int button = D6;
char phone[]="----------";  // "ur Phone number";

SoftwareSerial sim808(D3, D2);  //---RX=D3 and TX=D2
String lattitude, longitude;
String data[5];
int i = 0;
char c;



void setup() {
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  sim808.begin(9600);
  miss_call();
  sim808.println("AT+CGNSPWR=1");
  delay(2000);
  sim808.println("AT+CGNSSEQ=\"RMC\"");
  delay(2000);
}

void loop() {
  Serial.println("scanning button");
  gps_location();
  delay(1000);
  if(digitalRead(button)==LOW){
    delay(40);                          //wait 40mSec to debounce
    while(digitalRead(button)==LOW);    //wait till button released
    Serial.println("Button pressed");
    gps_location();
    sms_send();
    miss_call();
  }
    
 }

void miss_call(){
  Serial.println("Calling.......");
  sim808.print("ATD");                      // Call command ATD9730579463;
  sim808.print(phone);                      
  sim808.println(";");
  delay(10000);
  Serial.println("Call disconected");
  sim808.println("ATH");
  delay(1000); 
}

 void sms_send()
 {    sim808.println("AT+CMGF=1");                // Select Text mode for messsaging
      delay(100);
      sim808.print("AT+CMGS=\"");               
      sim808.print(phone);
      sim808.println("\"");
      delay(1000);   
      sim808.print("http://maps.google.com/maps?q=loc:");
      sim808.print(lattitude);
      sim808.print(",");
      sim808.print(longitude);
      delay(500);     
      sim808.println((char)26);
      delay(100);
      Serial.println("Message is sent");
      delay(100);
 }
 
void gps_location(){
    int i=0;
    longitude = "";
    lattitude = "";
      for(i=0; i<5; i++)
        data[i]="";
    i=0;
    Serial.println("--GPS--request--given----");
    sim808.flush();        
    long int time = millis();
    sim808.println("AT+CGNSINF");
    while ((time+1000 ) > millis()){
    while(sim808.available()){
        c = sim808.read();
        if (c != ',') {
          data[i] +=c;
          delay(20);
         } 
         else 
         i++;
        }
        if(i==5)
        break;
    }
    lattitude = data[3];
    longitude = data[4];
    Serial.print("lattitude = ");
    Serial.println(lattitude);
    Serial.print("longitude = ");
    Serial.println(longitude);
 }
