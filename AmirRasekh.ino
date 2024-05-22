float b;
float a;
float temp=0;
float hum=0;
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <stdio.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <dht.h>
dht DHT;

const char* ssid = "ghb";
const char* password =  "aps727474";
const char* mqttServer = "m21.cloudmqtt.com";
const int mqttPort = 15171;
const char* mqttUser = "vnioepnl";
const char* mqttPassword = "mUrjDPNUjdsz";
WiFiClient espClient;
PubSubClient client(espClient);
SoftwareSerial mySerial(12, 13);
TinyGPS gps;
void gpsdump(TinyGPS &gps, float &a,float &b);
void setup() {
  Serial.begin(115200);
  pinMode(4,OUTPUT);
  digitalWrite(4,0);
  pinMode(14,OUTPUT);
  digitalWrite(14,0);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
    
  }
  Serial.println("Connected to the WiFi network");
  digitalWrite(4,1);

  client.setServer(mqttServer, mqttPort);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    

    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {

      Serial.println("connected");
      digitalWrite(14,1);  

    } else {

      Serial.print("failed with state ");
      digitalWrite(14,0);
      Serial.print(client.state());
      delay(2000);

    }
  }

}

void loop(){
    
  client.setServer(mqttServer, mqttPort);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {

      Serial.println("connected");
      digitalWrite(14,1);  

    } else {

      Serial.print("failed with state ");
      digitalWrite(14,0);
      Serial.print(client.state());
      delay(2000);

    }
  }
   
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
      String packet="";  
packet=a;
packet+=":";
packet+=b;
packet+=":";
packet+=temp;
packet+=":";
packet+=hum;
packet+=":";
Serial.println("OK**");
Serial.println(packet);
const char *s = packet.c_str();
  client.publish("data", s);
  client.loop();
  delay(2000);
  
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
