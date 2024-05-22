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

pinMode(14,OUTPUT);
pinMode(16,OUTPUT);

Serial.begin(9600);
 WiFi.begin("pouya","123321123");
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  
//digitalWrite(14,1);
digitalWrite(16,1);
        

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

      
      sensp=sens;
      sensmax=sens;
}
void loop() {
sens=analogRead(A0);

  Serial.println(sensmax);

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }


  char url[100];
  sprintf(url,"/hand.php?sens=%d",sens);
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
    delay(200);
    if(sensp=1024)
    {
      sens=analogRead(A0);
      sensmax=sens;
      }
      else{
    sensp=sens;
    sensmax=sens; 
      sens=analogRead(A0);
      }
  
wdt_reset();
}

