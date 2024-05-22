int i=0;
/*
  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 2 (connect to TX of other device)
 * TX is digital pin 3 (connect to RX of other device)
 
 created back in the mists of time
 modified 9 Apr 2012
 by Tom Igoe
 based on Mikal Hart's example
 
 This example code is in the public domain.
 
 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(12,13); // RX, TX

void setup()  
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   

  
  //Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
 // mySerial.println("Hello, world?");
}

void loop() // run over and over
{
 unsigned int start=millis();
   while (millis() - start < 5000) 
  {
  if (mySerial.available())
    Serial.write(mySerial.read());
  delay(40);
  }

     String cmd,cmd1,cmd2,cmd3,cmd4;
if(i==0){
cmd="AT+SAPBR=1,1 \n";
mySerial.print(cmd);
}
if(i==1)
{
  cmd1="AT+HTTPINIT \n";
  mySerial.print(cmd1);
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
cmd2+="500000,400000";
cmd2+="&";
cmd2+="dht=";
cmd2+="2022,555";
cmd2+='"';
cmd2+=" \n";
  mySerial.print(cmd2);
  }
  if(i==3)
  {
    cmd3="AT+HTTPACTION=1\n";
    mySerial.print(cmd3);
    delay(400);
    
    }
i++;
if(i==4){
i=0;
}
/*
 int chk=DHT.read22(16);
  bool newdata = false;
 unsigned long start1 = millis();
  // Every 5 seconds we print an update
  while (millis() - start1 < 6000) 
  {
  temp=DHT.temperature;
  hum=DHT.humidity;
  if(temp != -999.00 )
  {
  y=temp;
  y+=',';
  y+=hum;
  break;
  }
  
  }
  unsigned long start = millis();
  // Every 5 seconds we print an update
  while (millis() - start < 5000) 
  {
    if (mySerial.available()) 
    
    {
      char c = mySerial.read();
      //Serial.print(c);  // uncomment to see raw GPS data
      if (gps.encode(c)) 
      {
        //digitalWrite(14,1);
        newdata = true;
        break;  // uncomment to print new data immediately!
      }
      else{
        ;//digitalWrite(14,0);
      }
    }
  }
  
  if (newdata) 
  {
    //digitalWrite(4,1);
    int a,b;
    Serial.println("Acquired Data");
    Serial.println("-------------");
    gpsdump(gps,a,b);
    Serial.println("-------------");
    Serial.println();
  l+=a;
  l+=',';
  l+=b;
  Serial.println("GPS"+l);
  }
  else{
    //digitalWrite(4,0);
    l="Gps Could not found where you are";
    Serial.println(l);
    }
 */
}
