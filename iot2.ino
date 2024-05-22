int h;
#include <ESP8266WiFi.h>
#include <stdio.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>
const char* ssid="MobinNet9277";
const char* pass="30449277";
const char* host = "sepaj.ir";

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use thi for the 12-bit version */

void setup(void) 
{
  WiFi.begin(ssid,pass);
      while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  pinMode(A0,INPUT);
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Hello!");
  
  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  
  ads.begin();
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

void loop(void) 
{
    WiFiClient client;

  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connect ion failed");
    return;
  }
  
  int16_t a0, a1, a2, a3,a4;
char s[100];
sprintf(s,"/log.php?sens=%u",h);
  a0 = ads.readADC_SingleEnded(0);
  //s+=a0;
  a1 = ads.readADC_SingleEnded(1);
 // s+="*";
  //s+=a1;
  a2 = ads.readADC_SingleEnded(2);
 // s+="*";
  //s+=a2;
  //a3 = ads.readADC_SingleEnded(3);
  //Serial.println(analogRead(A0));
  //Serial.print("AIN0: "); Serial.println(a0);
  //Serial.print("AIN1: "); Serial.println(a1);
//  Serial.print("AIN2: "); Serial.println(a2);
//  Serial.print("AIN3: "); Serial.println(a3);
 // Serial.print("AIN4: ");Serial.println(a4);
  Serial.print(s);
  Serial.println(" ");
  h++;
 
  client.print(String("GET ") + s + " HTTP/1.1\r\n" +
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
  
  wdt_reset();
  
  delay(1000);
}
