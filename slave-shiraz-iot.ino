//***********************************lib********************************//
#include <Wire.h>
//***********************************lib********************************//

//**********************************global******************************//
int id= 0;
//**********************************global******************************//

//**********************************setup*******************************//
void setup() {
  Serial.begin(9600);
  Wire.begin(9);

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
  
  Wire.onReceive(receiveEvent);
}
//**********************************setup*******************************//

//*************************************i2c*****************************//
void receiveEvent(int bytes) {
  id= Wire.read();   
}
//*************************************i2c*****************************//

//**********************************loop********************************//
void loop() {
  Serial.println(id);
  switch(id){
    case 1:{
      digitalWrite(13,1);
      break;
    }
    case 2:{
      digitalWrite(12,1);
      break;
    }
    case 3:{
      digitalWrite(11,1);
      break;
    }
    case 4:{
      digitalWrite(10,1);
      break;
    }
    case 5:{
      digitalWrite(9,1);
      break;
    }
    case 6:{
      digitalWrite(8,1);
      break;
    }
    case 7:{
      digitalWrite(7,1);
      break;
    }
    case 8:{
      digitalWrite(6,1);
      break;
    }
    case 9:{
      digitalWrite(5,1);
      break;
    }
    case 10:{
      digitalWrite(4,1);
      break;
    }
    case 11:{
      digitalWrite(4,1);
      break;
    }
  }
  
//**********************************loop********************************//
}
