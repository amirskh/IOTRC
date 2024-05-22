#include <stdio.h>
#include <RCSwitch.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include<EEPROM.h>
RCSwitch mySwitch = RCSwitch();
const char* host = "sh.iotiran.com";
int z;
int q=0;
int p=0;
WiFiServer server(80);
void setup() {

Serial.begin(9600);
 EEPROM.begin(256);
pinMode(16,INPUT);
pinMode(13,1);
digitalWrite(13,1);

}

void loop() {
  
int b=0; 
    z=EEPROM.read(0);
while(z==1){
  
 delay(600);
digitalWrite(13,1);
delay(800);
digitalWrite(13,0); 
  if(q==0){
    q=1;
  WiFi.mode(WIFI_AP);
    IPAddress apIP(192, 168, 1, 1);  // Defining a static IP address: local & gateway
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00  
String ssid="";
String pass="";
int render=1;
int klock=0;
while(char(EEPROM.read(render)) != ':')
{
//Serial.print(char(EEPROM.read(render)));
if(char(EEPROM.read(render)) == ','){
  klock=1;
  render++;
  }
if(klock==0)
{
  ssid+=char(EEPROM.read(render));
  }
  if(klock==1)
{
  pass+=char(EEPROM.read(render));
  }
render++;

}
Serial.println(ssid);
Serial.println(",");
Serial.println(pass);
  WiFi.softAP(ssid.c_str(),pass.c_str());
Serial.println("DONE!...");

  server.begin();
  Serial.println("I'm here bro");
  }
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
   // Serial.println("client is not here");
  WiFiClient client = server.available();
    return;
  delay(100);
  
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  if(req.indexOf("button1") != -1){
    p=1;
    }
  if(req.indexOf("button2") != -1){
    p=2;
    }
  if(req.indexOf("button3") != -1){
    p=3;
    }
      

    if(req.indexOf("back") != -1){
      p=0;
      }
  if(req.indexOf("int") != -1){
    int j=0;
    int l=0;
    String a,b,c;
    for(int i=0 ; i < req.length() ; i++){
 if(req[i]=='=' && j < 2)
    {  
      j++;
      i++;
    while(req[i] != '&'){
    if(i==req.length())
    break;
      
     // Serial.println(s[i]);
      if(j==1){
        a+=req[i];
        //Serial.println(s[i]);
        }
      if(j==2){
        b+=req[i];
        }
      
      i++;
      
      }
    if(req[i] != '&')
    i++;
    }
if(req[i]=='=' && j==2)
    {  
      j++;
      i++;
    while(req[i] != ' '){
      //Serial.println(s[i]);
      c+=req[i];
      //Serial.println("**");
      i++;
      
      }
    
    }
      

}
int err=0;
if(b!=c){
Serial.println("ERROR");
client.print("<a href=\"back\">An Error Happened</a>");
/******************************/
String ssid1="";
String pass1="";
int render1=1;
int klock1=0;
while(char(EEPROM.read(render1)) != ':')
{
//Serial.print(char(EEPROM.read(render)));
if(char(EEPROM.read(render1)) == ','){
  klock1=1;
  render1++;
  }
if(klock1==0)
{
  ssid1+=char(EEPROM.read(render1));
  }
  if(klock1==1)
{
  pass1+=char(EEPROM.read(render1));
  }
render1++;
a=ssid1;
c=pass1;
}
/******************************/
}
a+=',';
a+=c;
l=a.length()+1;
Serial.print("*");
Serial.print(a);
Serial.print("*");
Serial.print("\n");

Serial.println(l);
for(int i=1;i<=l+1;i++)
{
  
  if(i==l)
  {
    EEPROM.write(i,':');
    }
  else
  EEPROM.write(i,a[i-1]);
  Serial.print(".");
  EEPROM.commit();
  }

    }
  
  if(req.indexOf("ext") != -1){
    int addr=0;
while(EEPROM.read(addr) != ':')
addr++;
addr++;

        int j=0;
    int l=0;
    String a="",b="";
    for(int i=0 ; i < req.length() ; i++){
 if(req[i]=='=' && j < 1)
    {  
      j++;
      i++;
    while(req[i] != '&'){
    if(i==req.length())
    break;
      
     // Serial.println(s[i]);
      if(j==1){
        a+=req[i];
        //Serial.println(s[i]);
        }
 
      
      i++;
      
      }
    if(req[i] != '&')
    i++;
    }
if(req[i]=='=' && j==1)
    {  
      j++;
      i++;
    while(req[i] != ' '){
      //Serial.println(s[i]);
      b+=req[i];
      //Serial.println("**");
      i++;
      
      }
    
    }
      

}
    /****************************************/
    
    a+=',';
    a+=b;
    int y=0;
    Serial.print("*");Serial.print(a);Serial.print("*");
    for(int i=addr;i<=addr+a.length();i++)
    {
      if(i==addr+a.length()){
        EEPROM.write(i,':');
        }
      
      else
      EEPROM.write(i,a[y]);
      y++;
      }
    EEPROM.commit();
    }
  
  
  
  if(req.indexOf("close") != -1){
      Serial.println("now...");
EEPROM.write(0,0);  
EEPROM.commit();
q=0;
z=0;
    }

  // Prepare the response. Start with the common header:
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
 if(p==1){
s+="<html> \r\n";
s+="<head> \r\n";
s+="<meta charset='UTF-8' /> \r\n";
s+="<meta name='viewport' content='width=device-width, initial-scale=1.0'> \r\n";
s+="<style> \r\n";
s+="*{ box-sizing: border-box; } \r\n";
s+=".menu { float: left; width: 100%;} \r\n";
s+=".menuitem { border: hidden; border-radius:8px; padding: 8px; margin-top: 7px; border-bottom: 1px solid #f1f1f1; width: 100%; height:50px; font-size:17px; direction: rtl; padding-right:15px; }\r\n";
s+="button:hover{ background:rgb(0, 17, 51); color:#FFFFFF; transition:1s; } \r\n";
s+="input:hover{ background:rgb(0, 17, 51); color:#FFFFFF; transition:1s; } \r\n";
s+=".btn{ background:#006633; color:#FFFFFF; } \r\n";
s+=".btn1{ background:#006699; color:#FFFFFF; } \r\n";
s+="@media only screen and (max-width:800px) { \r\n";
s+=".main { width: 80%; padding: 0; } \r\n";
s+="} \r\n";
s+="@media only screen and (max-width:500px) { \r\n";
s+=".menu{ width: 100%; } \r\n";
s+="} \r\n";
s+="</style> \r\n";
s+="</head> \r\n";
s+="<body style='font-family:Verdana; background:#669999;'> \r\n";
s+="<div style='background-color:#f1f1f1; padding:15px;'> \r\n";
s+="<center><h1>اعمال تغییرات روی مودم داخلی</h1></center> \r\n";
s+="</div> \r\n";
s+="<div style='overflow:auto'> \r\n";
s+="<div class='menu'> \r\n";
s+="<form method='get' action='int'>\r\n";
s+="<input name='username' type='text' placeholder='نام مودم داخلی' maxlength='20' class='menuitem'> \r\n";
s+="<input name='pass1' type='password' placeholder='رمز عبور' maxlength='20' class='menuitem'> \r\n";
s+="<input name='pass2' type='password' placeholder='تکرار رمز عبور' maxlength='20' class='menuitem'> \r\n";
s+="<input  type='submit' value='اعمال تغییرات' maxlength='20' class='menuitem btn'>\r\n";
s+="</form>\r\n";
s+="<A href=\"/back\"><BUTTON class='menuitem btn1' >بازگشت</button></A> \r\n";

s+="</div> \r\n";
s+="</div> \r\n";
s+="</body> \r\n";

 }
 if(p==0)
 {
 s+="<head> \r\n";
s+="<meta charset='UTF-8' /> \r\n";
s+="<meta name='viewport' content='width=device-width, initial-scale=1.0'> \r\n";
s+="<style> \r\n";
s+="*{ box-sizing: border-box; } \r\n";
s+=".menu { float: left; width: 100%;} \r\n";
s+=".menuitem { border: hidden; border-radius:8px; padding: 8px; margin-top: 7px; border-bottom: 1px solid #f1f1f1; width: 100%; height:50px; font-size:17px; }\r\n";
s+="button:hover{ background:rgb(0, 17, 51); color:#FFFFFF; transition:1s; } \r\n";
s+=".btn{ background:#8A0000; color:#FFFFFF;}\r\n";
s+="@media only screen and (max-width:800px) { \r\n";
s+=".main { width: 80%; padding: 0; } \r\n";
s+="} \r\n";
s+="@media only screen and (max-width:500px) { \r\n";
s+=".menu{ width: 100%; } \r\n";
s+="} \r\n";
s+="</style> \r\n";
s+="</head> \r\n";
s+="<body style='font-family:Verdana; background:#669999;'> \r\n";
s+="<div style='background-color:#f1f1f1; padding:15px;'> \r\n";
s+="<center><h1>(IoT Iran)خانه هوشمند</h1></center> \r\n";
s+="</div> \r\n";
s+="<div style='overflow:auto'> \r\n";
s+="<div class='menu'> \r\n";
s+="<A href=\"/button1\"><BUTTON class='menuitem'>اعمال تغییرات روی مودم داخلی</button></A> \r\n";
s+="<A href=\"/button2\"><BUTTON class='menuitem'>اتصال به شبکه</button></A> \r\n";
s+="<A href=\"/button3\"><BUTTON class='menuitem'>سنسور های متصل</button></A> \r\n";
s+="<A href=\"/close\"><BUTTON class='menuitem btn' >خروج</button></A> \r\n";
s+="</div> \r\n";
s+="</div> \r\n";
s+="</body> \r\n";
 
  }
   if(p==2)
 {
  s+="<head> \r\n";
s+="<meta charset='UTF-8' /> \r\n";
s+="<meta name='viewport' content='width=device-width, initial-scale=1.0'> \r\n";
s+="<style> \r\n";
s+="*{ box-sizing: border-box; } \r\n";
s+=".menu { float: left; width: 100%;} \r\n";
s+=".menuitem { border: hidden; border-radius:8px; padding: 8px; margin-top: 7px; border-bottom: 1px solid #f1f1f1; width: 100%; height:50px; font-size:17px; direction: rtl; padding-right:15px; }\r\n";
s+="button:hover{ background:rgb(0, 17, 51); color:#FFFFFF; transition:1s; } \r\n";
s+="input:hover{ background:rgb(0, 17, 51); color:#FFFFFF; transition:1s; } \r\n";
s+=".btn{ background:#006633; color:#FFFFFF; } \r\n";
s+=".btn1{ background:#006699; color:#FFFFFF; } \r\n";
s+="@media only screen and (max-width:800px) { \r\n";
s+=".main { width: 80%; padding: 0; } \r\n";
s+="} \r\n";
s+="@media only screen and (max-width:500px) { \r\n";
s+=".menu{ width: 100%; } \r\n";
s+="} \r\n";
s+="</style> \r\n";
s+="</head> \r\n";
s+="<body style='font-family:Verdana; background:#669999;'> \r\n";
s+="<div style='background-color:#f1f1f1;padding:15px;'> \r\n";
s+="<center><h1>اتصال به شبکه</h1></center> \r\n";
s+="</div> \r\n";
s+="<div style='overflow:auto'> \r\n";
s+="<div class='menu'> \r\n";
s+="<form method='get' action='ext'>\r\n";
s+="<input name='wifiname' type=' text' placeholder='نام شبکه' maxlength='20' class='menuitem'> \r\n";
s+="<input name='wifipass' type='password' placeholder='رمز عبور' maxlength='20' class='menuitem'> \r\n";
s+="<input  type='submit' value='اعمال تغییرات' maxlength='20' class='menuitem btn'>\r\n";
s+="</form>\r\n";
s+="<A href=\"/back\"><BUTTON class='menuitem btn1' >بازگشت</button></A> \r\n";
s+="</div> \r\n";
s+="</div> \r\n";
s+="</body> \r\n";
}
   if(req.indexOf("button3") != -1){
  s+="<head> \r\n";
s+="<meta charset='UTF-8' /> \r\n";
s+="<meta name='viewport' content='width=device-width, initial-scale=1.0'> \r\n";
s+="<style> \r\n";
s+="*{ box-sizing: border-box; } \r\n";
s+=".menu { float: left; width: 100%;} \r\n";
s+=".menuitem { border: hidden; border-radius:8px; padding: 8px; margin-top: 7px; border-bottom: 1px solid #f1f1f1; width: 100%; height:50px; font-size:17px; background:#DCDCDC; direction:rtl; }";
s+="button:hover{ background:rgb(0, 17, 51); color:#FFFFFF; transition:1s; } \r\n";
s+=".btn{ background:#006699; color:#FFFFFF; } \r\n";
s+="@media only screen and (max-width:800px) { \r\n";
s+=".main { width: 80%; padding: 0; } \r\n";
s+="} \r\n";
s+="@media only screen and (max-width:500px) { \r\n";
s+=".menu{ width: 100%; } \r\n";
s+="} \r\n";
s+="</style> \r\n";
s+="</head> \r\n";
s+="<body style'font-family:Verdana; background:#669999;'> \r\n";
s+="<div style='background-color:#f1f1f1; padding:15px;'> \r\n";
s+="<center><h1>سنسور های متصل</h1></center> \r\n";
s+="</div> \r\n";
s+="<div style='overflow:auto'> \r\n";
s+="<div class='menu'> \r\n";
s+="<div class='menuitem'><center>سنسور تشخیص حریق(55436476)</center></div> \r\n";
s+="<div class='menuitem'><center>سنسور تشخیص حرکت (54678930)</center></div> \r\n";
s+="<div class='menuitem'><center>سنسور درب (43765498)</center></div></div>\r\n";
s+="<A href=\"/back\"><BUTTON class='menuitem btn' >بازگشت</button></A> \r\n";
s+="</div> \r\n";
s+="</div> \r\n";
s+="</body> \r\n";  
    } 
s+="</body> \r\n";
  s += "</html>";
Serial.println(p);
  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");


wdt_reset();

}
if(z==0){

if(q==0){
int addr=0;
while(EEPROM.read(addr) != ':')
addr++;
addr++;
String ssid="";
String pass="";
int render=addr;
int klock=0;
while(char(EEPROM.read(render)) != ':')
{
//Serial.print(char(EEPROM.read(render)));
if(char(EEPROM.read(render)) == ','){
  klock=1;
  render++;
  }
if(klock==0)
{
  ssid+=char(EEPROM.read(render));
  }
  if(klock==1)
{
  pass+=char(EEPROM.read(render));
  }
render++;

}
Serial.print("SSID IS:");
Serial.print(ssid);
Serial.print("PASS IS:");
Serial.print(pass);
Serial.print("avallin do noghte:");

   
   WiFi.begin(ssid.c_str(),pass.c_str());
   
    while (WiFi.status() != WL_CONNECTED) {
    
   delay(200);
digitalWrite(13,1);
delay(300);
digitalWrite(13,0);
    
    Serial.print(".");
  b=digitalRead(16);
  if(b == 1)
{
  Serial.println("now...");
EEPROM.write(0,!z);  
EEPROM.commit();
q=0;
break;
}

 }
  mySwitch.enableReceive(2);  // Receiver on interrupt 0 => that is pin #2
  q=1;
  }
    digitalWrite(13,1);
    String k;
  if (mySwitch.available()) {
    
    Serial.print("Received ");
    Serial.print( mySwitch.getReceivedValue() );
    k=mySwitch.getReceivedValue();
    Serial.print(" / ");
    Serial.print( mySwitch.getReceivedBitlength() );
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println( mySwitch.getReceivedProtocol() );

   
  
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }


  String url;
  url="/testish.php?mac=";
  url+=random(1000);
  url+="&";
  if(mySwitch.getReceivedValue()==5592407){
  url+="id=";
  url+="3"; 
  }  if(mySwitch.getReceivedValue()==16011088){
  url+="id=";
  url+="2"; 
  }
    if(mySwitch.getReceivedValue()==5592413){
  url+="id=";
  url+="1"; 
  }
  Serial.println("*****************");
  Serial.println("url:");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
 // Serial.println("sensor:");
//Serial.println(mySwitch.getReceivedValue());
 mySwitch.resetAvailable();
 wdt_reset();
}  

  }
  unsigned int start=millis();
while(millis()-start<1000){
b=digitalRead(16);
//Serial.println(digitalRead(D4));
b=b && 1;

wdt_reset();
}
if(b == 1)
{
  Serial.println("now...");
EEPROM.write(0,!z);  
EEPROM.commit();
q=0;
}

//for(int h=0;h<50;h++){
 // Serial.println(char(EEPROM.read(h)));
  //}
wdt_reset();
}



