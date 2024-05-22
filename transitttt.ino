float b;
float a;
float temp=0;
float hum=0;
#include <stdio.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <dht.h>
dht DHT;


const char* host = "sepaj.ir";
SoftwareSerial mySerial(12, 13);
TinyGPS gps;
void gpsdump(TinyGPS &gps, float &a,float &b);

void setup() {

   Serial.begin(115200);
   pinMode(4,OUTPUT);
   digitalWrite(4,0);
   pinMode(14,OUTPUT);
   digitalWrite(14,0);
   WiFi.begin("amir","00000000");
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  digitalWrite(4,1);  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    digitalWrite(14,0);
    return;
  }
  else{
    Serial.println("connected");
    digitalWrite(14,1);
  }

   }

void loop() {
  bool newdata = false;
  unsigned long start = millis();
  // Every 5 seconds we print an update
  while (millis() - start < 1000) 
  {
    if (mySerial.available()) 
    
    {
      char c = mySerial.read();
      //Serial.print(c);  // uncomment to see raw GPS data
      if (gps.encode(c)) 
      {
        newdata = true;
        break;  // uncomment to print new data immediately!
      }
    }
  }
  
  if (newdata) 
  {

    //Serial.println("Acquired Data");
    //Serial.println("-------------");
    gpsdump(gps,a,b);
    Serial.println(a/1000000,6);
       //Serial.println("\n");
       Serial.println(b/1000000,6);
  }
  int l=millis();
  while(millis()-l<1000)
  {
  int chk = DHT.read22(16);
  if(DHT.temperature != -999.00){
  Serial.print("Temp: ");
  Serial.print(DHT.temperature);
  temp=DHT.temperature;
  Serial.print("C");
 
  Serial.print("Humidity: ");
  Serial.print(DHT.humidity);
 hum=DHT.humidity;
  Serial.println("%");
  break;
  }

 // wdt_reset();
  }
      
String packetGps="";
String packetDht="";  
packetGps=a;
packetGps+=",";
packetGps+=b;
packetDht=temp;
packeDht+=",";
packetDht+=hum;
Serial.println("OK**");
Serial.println(packet);
  delay(2000);
   WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    digitalWrite(14,0);
    return;
  }
  char url[100];
  digitalWrite(14,1);
  sprintf(url,"/testy.php?sens=%s&dht=%s",packetGps,packetDht);  //file php
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  while(client.available()){
    String line = client.readString();
    Serial.print(line);
  }

   delay(1000);

   }
   void gpsdump(TinyGPS &gps , float &a,float &b)
{
  
  long lat, lon;
  float flat, flon;
  unsigned long age, date, time, chars;
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned short sentences, failed;

  gps.get_position(&lat, &lon, &age);
  a=lat;
  b=lon;
}
