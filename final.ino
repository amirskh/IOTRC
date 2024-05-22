int i=0;
float temp,hum;/*********************
 *10 to GPS Module TX*
 *09 to GPS Module RX*
 *********************/
String l="12,8",y="12,8";
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <dht.h>
SoftwareSerial mySerial(12,13);
TinyGPS gps;
dht DHT;
void gpsdump(TinyGPS &gps);
void printFloat(double f, int digits = 2);

void setup()  
{
  pinMode(4,OUTPUT);
  digitalWrite(4,0);
  pinMode(14,OUTPUT);
  digitalWrite(14,0);
  // Oploen serial communications and wait for port to open:
  Serial.begin(9600);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  delay(1000);
 
  Serial.println(sizeof(TinyGPS));
  Serial.println(); 
}

void loop() // run over and over
{/*
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
  unsigned long start2 = millis();
  // Every 5 seconds we print an update
  while (millis() - start2 < 5000) 
  {
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
break;
}
    }
}

void gpsdump(TinyGPS &gps,int &a,int &b)
{
  long lat, lon;
  //float flat, flon;
  unsigned long age, date, time, chars;
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned short sentences, failed;

  gps.get_position(&lat, &lon, &age);
a=lat;
b=lon;
}
/*  

  Serial.print("Lat/Long(10^-5 deg): "); Serial.print(lat); Serial.print(", "); Serial.print(lon); 
  Serial.print(" Fix age: "); Serial.print(age); Serial.println("ms.");
  
  // On Arduino, GPS characters may be lost during lengthy Serial.print()
  // On Teensy, Serial prints to USB, which has large output buffering and
  //   runs very fast, so it's not necessary to worry about missing 4800
  //   baud GPS characters.

  gps.f_get_position(&flat, &flon, &age);
  Serial.print("Lat/Long(float): "); printFloat(flat, 5); Serial.print(", "); printFloat(flon, 5);
    Serial.print(" Fix age: "); Serial.print(age); Serial.println("ms.");

  gps.get_datetime(&date, &time, &age);
  Serial.print("Date(ddmmyy): "); Serial.print(date); Serial.print(" Time(hhmmsscc): ");
    Serial.print(time);
  Serial.print(" Fix age: "); Serial.print(age); Serial.println("ms.");

  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  Serial.print("Date: "); Serial.print(static_cast<int>(month)); Serial.print("/"); 
    Serial.print(static_cast<int>(day)); Serial.print("/"); Serial.print(year);
  Serial.print("  Time: "); Serial.print(static_cast<int>(hour+8));  Serial.print(":"); //Serial.print("UTC +08:00 Malaysia");
    Serial.print(static_cast<int>(minute)); Serial.print(":"); Serial.print(static_cast<int>(second));
    Serial.print("."); Serial.print(static_cast<int>(hundredths)); Serial.print(" UTC +08:00 Malaysia");
  Serial.print("  Fix age: ");  Serial.print(age); Serial.println("ms.");

  Serial.print("Alt(cm): "); Serial.print(gps.altitude()); Serial.print(" Course(10^-2 deg): ");
    Serial.print(gps.course()); Serial.print(" Speed(10^-2 knots): "); Serial.println(gps.speed());
  Serial.print("Alt(float): "); printFloat(gps.f_altitude()); Serial.print(" Course(float): ");
    printFloat(gps.f_course()); Serial.println();
  Serial.print("Speed(knots): "); printFloat(gps.f_speed_knots()); Serial.print(" (mph): ");
    printFloat(gps.f_speed_mph());
  Serial.print(" (mps): "); printFloat(gps.f_speed_mps()); Serial.print(" (kmph): ");
    printFloat(gps.f_speed_kmph()); Serial.println();

  gps.stats(&chars, &sentences, &failed);
  Serial.print("Stats: characters: "); Serial.print(chars); Serial.print(" sentences: ");
    Serial.print(sentences); Serial.print(" failed checksum: "); Serial.println(failed);
}

void printFloat(double number, int digits)
{
  // Handle negative numbers
  if (number < 0.0) 
  {
     Serial.print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  Serial.print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    Serial.print("."); 

  // Extract digits from the remainder one at a time
  while (digits-- > 0) 
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    Serial.print(toPrint);
    remainder -= toPrint;
  }
}
*/
