/*-----------Digital Thermometer Using Arduino-------------*/
// @ARDUINOUNOR3
//  طراح : امیررضا علیزاده
#include<LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);

#define sensor A0

byte degree[8] = 
              {
                0b00011,
                0b00011,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000
              };

byte armsDown[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b01010
};

byte armsUp[8] = {
  0b00100,
  0b01010,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b01010
};

void setup()
{
  lcd.begin(16,2);
  // create a new character
  lcd.createChar(5, armsDown);
  // create a new character
  lcd.createChar(6, armsUp);
   
  // set the cursor to the top left
  lcd.setCursor(0, 0);

  lcd.createChar(1, degree);
  lcd.setCursor(0,0);
  lcd.print("  ARDUINOUNOR3");
  lcd.setCursor(0,1);
  lcd.print("  Thermometer   ");
  delay(4000);
  lcd.clear();
  lcd.print("    Amirreza");
  delay(1000);
  lcd.clear();
}

void loop()
{
  /*---------Temperature-------*/
     float reading=analogRead(sensor);
     float temperature=reading*(5.0/1023.0)*100;
     delay(100);
  
  /*------Display Result------*/
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Temperature");
    lcd.setCursor(4,1);
    lcd.print(temperature);
    lcd.write(1);
    lcd.print("C");
    delay(1000);
///////////////////////////////////////////////////////////////////////////////
 // read the potentiometer on A0:
  int sensorReading = analogRead(A0);
  // map the result to 200 - 1000:
  int delayTime = map(sensorReading, 0, 1023, 200, 1000);
  // set the cursor to the bottom row, 5th position:
  lcd.setCursor(2, 1);
  // draw the little man, arms down:
  lcd.write(5);
  delay(delayTime);
  lcd.setCursor(2, 1);
  // draw him arms up:
  lcd.write(6);
  delay(1500);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////  
//مو int sensorReading = analogRead(A0);
  // map the result to 200 - 1000:
  // set the cursor to the bottom row, 5th position:
  lcd.setCursor(12, 1);
  // draw the little man, arms down:
  lcd.write(5);
  delay(delayTime);
  lcd.setCursor(12, 1);
  // draw him arms up:
  lcd.write(6);
  delay(1500);
}
//موفق باشین                                          


