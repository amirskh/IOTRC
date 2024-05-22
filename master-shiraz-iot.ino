//***********************************lib********************************//
#include <RCSwitch.h>
#include <Wire.h>
#include <EEPROM.h>
//***********************************lib********************************//

//**********************************global******************************//
RCSwitch centerSwitch = RCSwitch();
int value=0;
int id=0;
//int n1=EEPROM.read(1),n2=EEPROM.read(2),n3=EEPROM.read(3),n4=EEPROM.read(4),n5=EEPROM.read(5),n6=EEPROM.read(6),n7=EEPROM.read(7),n8=EEPROM.read(8),n9=EEPROM.read(9),n10=EEPROM.read(10),n11=EEPROM.read(11);
int n1=0,n2=0,n3=0,n4=0,n5=0,n6=0,n7=0,n8=0,n9=0,n10=0,n11=0;

//**********************************global******************************//

//*******************************Functions******************************//

//*************************************i2c*****************************//
void i2c(int num){
  Wire.beginTransmission(9);
  Wire.write(num);
  Wire.endTransmission();
}
//*************************************i2c*****************************//

//*************************************func****************************//
void func(){
  
  switch(id){
    case 1:{
      digitalWrite(13,1);
      if(value!=0 && n1<9){
      n1++;
      }
      if(n1>=9){
        EEPROM.write(id,9);
        i2c(id);
      }
      break;
    }
    case 2:{
      digitalWrite(12,1);
      if(value!=0 && n2<9 ){
      n2++;
      }
      if(n2>=9){
        EEPROM.write(id,9);
        i2c(id);
      }
      break;
    }
    case 3:{
      digitalWrite(11,1);
      if(value!=0 && n3<9){
      n3++;
      }
      if(n3>=9){
        EEPROM.write(id,9);
        i2c(id);
      }
      break;
    }
    case 4:{
      digitalWrite(10,1);
      if(value!=0 && n4<9){
      n4++;
      }
      if(n4>=9){
        EEPROM.write(id,9);
        i2c(id);
      }
      break;
    }
    case 5:{
      digitalWrite(9,1);
      if(value!=0 && n5<9){
      n5++;
      }
      if(n5>=9){
        EEPROM.write(id,9);
        i2c(id);
      }
      break;
    }
    case 6:{
      digitalWrite(8,1);
      if(value!=0 && n6<9){
      n6++;
      }
      if(n6>=9){
        EEPROM.write(id,9);
        i2c(id);
      }
      break;
    }
    case 7:{
      digitalWrite(7,1);
      if(value!=0 && n7<9){
      n7++;
      }
      if(n7>=9){
        EEPROM.write(id,9);
        i2c(id);
      }
      break;
    }
    case 8:{
      digitalWrite(6,1);
      if(value!=0 && n8<9){
      n8++;
      }
      if(n8>=9){
        EEPROM.write(id,9);
        i2c(id);
      }
      break;
    }
    case 9:{
      digitalWrite(5,1);
      if(value!=0 && n9<9){
      n9++;
      }
      if(n9>=9){
        EEPROM.write(id,9);
        i2c(id);
      }
      break;
    }
    case 10:{
      digitalWrite(4,1);
      if(value!=0 && n10<9){
      n10++;
      }
      if(n10>=9 && n11>=9){
        EEPROM.write(id,9);
        i2c(id);
      }
      break;
    }
    case 11:{
      digitalWrite(4,1);
      if(value!=0 && n11<9){
      n11++;
      }
      if(n11>=9 && n10>=9){
        EEPROM.write(id,9);
        i2c(id);
      }
      break;
    }
  }
}
//*************************************func****************************//

//******************************get*Id*Value****************************//
void getId_value(long int data){
  value=data%100000;
  id=data/1000000;
 Serial.println();
 Serial.println(n9);
  Serial.println(id);
  Serial.println(value);
  func();
}
//******************************get*Id*Value****************************//

//*******************************Functions******************************//




//**********************************setup*******************************//
void setup() {
  Serial.begin(9600);
  Wire.begin();
 
  pinMode(13,OUTPUT);
  digitalWrite(13,0);
  
  pinMode(12,OUTPUT);
  digitalWrite(12,0);
  
  pinMode(11,OUTPUT);
  digitalWrite(11,0);
  
  pinMode(10,OUTPUT);
  digitalWrite(10,0);
  
  pinMode(9,OUTPUT);
  digitalWrite(9,0);
  
  pinMode(8,OUTPUT);
  digitalWrite(8,0);
  
  pinMode(7,OUTPUT);
  digitalWrite(7,0);
  
  pinMode(6,OUTPUT);
  digitalWrite(6,0);
  
  pinMode(5,OUTPUT);
  digitalWrite(5,0);
  
  pinMode(4,OUTPUT);
  digitalWrite(4,0);
  
  centerSwitch.enableReceive(0);  
}
//**********************************setup*******************************//

//**********************************loop********************************//

void loop() {
//******************************for*Received****************************//
  if (centerSwitch.available()) {
    Serial.print("Received ");
    Serial.print( centerSwitch.getReceivedValue() );
//******************************get*Id*Value****************************//
    getId_value(centerSwitch.getReceivedValue());
//******************************get*Id*Value****************************//
    centerSwitch.resetAvailable();
  }
//******************************for*Received****************************//
  
}
//**********************************loop********************************//

