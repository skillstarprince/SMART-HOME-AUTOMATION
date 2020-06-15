#include <SimpleDHT.h>
#include<SoftwareSerial.h>
SoftwareSerial gsm(2,3);
#define echoPin 7//echo pin
#define trigpin 8//trigger pin
#define FAN 11
#define BUZZ 12
#define LIGHT 13
#define PIR A2
#define LDR A1
int a=0;
int b=0;
int pinDHT11 = 9;
SimpleDHT11 dht11(pinDHT11);
long duration;//duration used to calculate distance
float distance;
void setup() {
  // put your setup code here, to run once:
//pinMode(5,INPUT);
//pinMode(6,INPUT);
pinMode(LDR,INPUT);
pinMode(PIR,INPUT);
pinMode(pinDHT11,INPUT);
pinMode(echoPin,INPUT);
pinMode(FAN,OUTPUT);
pinMode(BUZZ,OUTPUT);
pinMode(LIGHT,OUTPUT);
pinMode(trigpin,OUTPUT);
gsm.begin(9600);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 a=analogRead(PIR);
 b=analogRead(LDR);
Serial.println("LDR VALUE");
Serial.println(b);
delay(1000);
Serial.println("PIR VALUE");
Serial.println(a);
delay(1000);
if(a>50)
{
  if(b>=150)
{
 digitalWrite(BUZZ,LOW);
 digitalWrite(LIGHT,HIGH);
 //Serial.println("Anybody present out of our room"); //.......................
 }
 else
 {
 digitalWrite(BUZZ,LOW);
 digitalWrite(LIGHT,LOW);
 }
}
else
{ 
 if(b>=100)
  {
  digitalWrite(BUZZ,LOW);
  digitalWrite(LIGHT,HIGH);
  Serial.println("Anybody Present here so light is on");
  }
  else
   {
  digitalWrite(BUZZ,LOW);
  digitalWrite(LIGHT,LOW);
  }
}
 //================ULTRASONIC SENSOR =======================
 digitalWrite(trigpin,LOW);
 delayMicroseconds(2);

  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);

 digitalWrite(trigpin,LOW );
  duration =pulseIn(echoPin,HIGH);
  //calculate the distance in cm based on the speed of sound.
  distance =duration*0.034/2;
  Serial.println("distance Value");
  Serial.println(distance);
  delay(100);

  if ( distance>=10)
  {
 //digitalWrite(BUZZ,HIGH); 
 Serial.println("Any Person try to touch my device");
 delay(1000);
//=========NEW==============
 digitalWrite(BUZZ,HIGH); 
delay(10000);
gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS=\"+917488248448\"\r");
  delay(1000);
  gsm.println("INTRUDER IN YOUR HOUSE");
  delay(100);
  gsm.println((char)26);
  delay(1000);
  Serial.println("MESSAGE SENT");
  delay(1000);
  }
  else
  {
    digitalWrite(BUZZ,LOW);
  }
  //==========WORKING ON TEMPERATURE AND HUMIDITY SENSOR================
    // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  delay(1000);
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);//delay(1000);
    return;
  }
  int x=(int)temperature;
  int y=(int)humidity;
  Serial.print("Sample OK: ");
  Serial.println(x);
 // Serial.print(" *C, "); 
  Serial.println(y); 
  //Serial.println(" H");
  
  // DHT11 sampling rate is 1HZ.
  delay(1500);
   if(x>=20)
   {
   digitalWrite(FAN,HIGH);
  // delay(1000);
   Serial.println("Temperature is up to 20*C so FAN is ON."); 
   }
   else
   {
   digitalWrite(FAN,LOW);
   Serial.println("Temperature is less than 20*C so FAN is OFF.");
   }
   }
