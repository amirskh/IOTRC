float b;
float a;
float temp=0;
float hum=0;
#include <stdio.h>
#include <ESP8266WiFi.h>
#include <TinyGPS.h>
#include <dht.h>
#include <SoftwareSerial.h>
#include <Thread.h>
#include <ThreadController.h>
dht DHT;
SoftwareSerial mySerial(12, 13);
TinyGPS gps;
void gpsdump(TinyGPS &gps, float &a,float &b);
SoftwareSerial myGsm(7,8);
String gpsPacket,dhtPacket;
String url="AT+HTTPPARA=\"URL\",\"http://sepj.ir/hamed2.php?sens=";
ThreadController controll = ThreadController();
Thread senss =  Thread();
Thread sendd = Thread();
void sendCallback(){
myGsm.println("AT+CGATT=1");
delay(200);
printSerialData();

myGsm.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR,connection type is GPRS
delay(1000);
printSerialData();

myGsm.println("AT+SAPBR=3,1,\"APN\",\"\"");//setting the APN,2nd parameter empty works for all networks
delay(5000);
printSerialData();

myGsm.println();
myGsm.println("AT+SAPBR=1,1");
delay(10000);
printSerialData();

myGsm.println("AT+HTTPINIT"); //init the HTTP request
delay(2000);
printSerialData();
url+=gpsPacket;
url+="&dhy=";
url+=dhtPacket;
myGsm.println(url);// setting the httppara,
//the second parameter is the website from where you want to access data
delay(1000);
printSerialData();

myGsm.println();
myGsm.println("AT+HTTPACTION=0");//submit the GET request
delay(8000);//the delay is important if the return datas are very large, the time required longer.
printSerialData();
myGsm.println("AT+HTTPREAD=0,20");// read the data from the website you access
delay(3000);
printSerialData();

myGsm.println("");
delay(1000);
myGsm.println("AT+HTTPTERM");// terminate HTTP service
printSerialData();
  
}

void sensCallback(){
  packetGps="";
  packetDht=""; 
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
 }
packetGps=a;
packetGps+=",";
packetGps+=b;
packetDht=temp;
packeDht+=",";
packetDht+=hum;
  
}

void setup()
{
myGsm.begin(115200);
Serial.begin(115200);
senss.onRun(sensCallback);
senss.setInterval(1500);
sendd.onRun(sendCallback);
sendd.setInterval(1500);
controll.add(&senss);
controll.add(&sendd); 
gpsSerial.begin(9600);
delay(500);



}

void loop()
{
 controll.run(); 
}

void printSerialData()
{
while(myGsm.available()!=0)
Serial.write(myGsm.read());
}
