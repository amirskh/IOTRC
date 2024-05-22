#include <dht.h>
dht DHT;
#define DHT11_PIN 14

float t;
int a;
#include <ESP8266WiFi.h>
#include <stdio.h>

const char* host = "sepaj.ir";
int sens,sensp,sensmax;
int def(int x1,int x2,int d){
  if((x1-x2)>d)
    return 1;
  else if((x2-x1)>d)
    return 0;
  else
    return 1;
}
void setup() {



Serial.begin(9600);
 WiFi.begin("hunter","123321123");
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  else{Serial.println("hoora!");}


}
void loop() {

 

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  char url[100];
   int chk = DHT.read11(DHT11_PIN);
  
  t=DHT.humidity;
  
  delay(1000);
 
 
  sprintf(url,"/mylog.php?sens=%u",int(t));
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
/*
    delay(200);
 
    sensp=sens;
    sensmax=sens; 
    while(sens-sensp<30){
    sensp=sens;
    sens=analogRead(A0);
    wdt_reset();
  }
  while(sens>sensp){
     sensp=sens;
     sensmax=sens;
    sens=analogRead(A0);
    wdt_reset();
  }
  */
}

