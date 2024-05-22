
int i=0;
#include <SoftwareSerial.h>
#include<TinyGPS.h>;
#include<dht.h>
String Arsp, Grsp;
#define LED_pin 13
dht DHT;
SoftwareSerial gsm(5,4); // RX, TX
SoftwareSerial mySerial(16,14); // RX, TX
TinyGPS gps;
float lat,lon;
void senD(String s,String q)
{
  delay(4000);
  if(gsm.available())
  {
    Grsp = gsm.readString();
    Serial.println(Grsp);
  }

  
  if(Serial.available())
  {
    Arsp = Serial.readString();
    
    gsm.println(Arsp);
  
  }
String cmd,cmd1,cmd2,cmd3,cmd4;
if(i==0){
cmd="AT+SAPBR=1,1 \n";
gsm.print(cmd);
}
if(i==1)
{
  cmd1="AT+HTTPINIT \n";
  gsm.print(cmd1);
  }
if(i==2)
{
cmd2="AT+HTTPPARA=";
cmd2+='"';
cmd2+="URL";
cmd2+='"';
cmd2+=",";
cmd2+='"';
cmd2+="http://sepaj.ir/testy.php?sens=";
cmd2+=s;
cmd2+="&";
cmd2+="dht=";
cmd2+=q;
cmd2+='"';
cmd2+=" \n";
  gsm.print(cmd2);
  }
  if(i==3)
  {
    cmd3="AT+HTTPACTION=1\n";
    gsm.print(cmd3);
    delay(1000);
    
    }
i++;
if(i==4){i=0;}

  
  }
void setup() {

  // put your setup code here, to run once:
  mySerial.begin(9600);
  Serial.begin(9600);
  Serial.println("Transit Project IoT Iran Research Center Amir Rasekhnia pouya Ghaffarzade Soheil Pakmard Sina Ghaffarzade but it developed by myself you know who am I :)");
  gsm.begin(115200);

}

void loop() {
  
  String y=" ",l=" ";
  
  
  //analogWrite(A0,1022);
  delay(300);
  //analogWrite(A0,0);
  int chk = DHT.read22(12);
//  String y;
  y=DHT.temperature;
  y+=',';
  y+=DHT.humidity;
  
  //String l="";
   // Serial.write(mySerial.read());
  
  if(gps.encode(mySerial.read()))// encode gps data
  {
    //digitalWrite(13,1);
    gps.f_get_position(&lat,&lon);
   //lat*=1000000;
   float kam;
  kam=lat;
  kam*=1000000;
  l+=kam;
  //
   kam=lon;
   kam*=1000000;
   l+=',';
   l+=kam;
  Serial.print(l);
  }
  //Serial.println(l);
   
//  delay(4000);


  
  
String cmd,cmd1,cmd2,cmd3,cmd4;
if(i==0){
cmd="AT+SAPBR=1,1 \n";
gsm.print(cmd);
}
if(i==1)
{
  cmd1="AT+HTTPINIT \n";
  gsm.print(cmd1);
  }
if(i==2)
{
cmd2="AT+HTTPPARA=";
cmd2+='"';
cmd2+="URL";
cmd2+='"';
cmd2+=",";
cmd2+='"';
cmd2+="http://sepaj.ir/testy.php?sens=";
cmd2+=l;
cmd2+="&";
cmd2+="dht=";
cmd2+=y;
cmd2+='"';
cmd2+=" \n";
  gsm.print(cmd2);
  }
  if(i==3)
  {
    cmd3="AT+HTTPACTION=1\n";
    gsm.print(cmd3);
    delay(1000);
    
    }
i++;
if(i==4){i=0;}

   
  }
  


