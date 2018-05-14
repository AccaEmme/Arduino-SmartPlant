

/*
 
 All the resources for this project:
 http://randomnerdtutorials.com/
 
*/
#include <Wire.h>  
#include <LCD.h>
#include <LiquidCrystal_I2C.h> // Using version 1.2.1

// The LCD constructor - address shown is 0x27 - may or may not be correct for yours
// Also based on YWRobot LCM1602 IIC V1
// set the LCD address to 0x27 for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
// esempio lcd: http://henrysbench.capnfatz.com/henrys-bench/arduino-displays/ywrobot-lcm1602-iic-v1-lcd-arduino-tutorial/
// https://www.youtube.com/watch?v=xVC0X_PE_XE
// libreria: https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads/
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  

int rainPin = A0;
int greenLED = 6;
int redLED = 7;
int waterPump=17; // A3

// you can adjust the threshold value
int thresholdValue = 800;
String outMessage;


int water_angle=0;

void setup(){
  pinMode(rainPin, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(waterPump, OUTPUT);
  
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);

  lcd.begin(16,2); // sixteen characters across - 2 lines
  lcd.backlight();
  // first character - 1st line
  lcd.setCursor(2,0);  lcd.print("SmartPlant:");
  // 8th character - 2nd line 
  lcd.setCursor(0,1);  lcd.print("-Basilico-");


 /* Innaffiamo la pianta solo alle ore 23:30 affinché il terreno riscaldato si raffreddi e l'acqua non evapori. */
  
  delay(5000);
  Serial.begin(9600);
}

void loop() { 
    lcd.setCursor(0,0);  lcd.print("                ");    lcd.setCursor(0,1);  lcd.print("                ");

  // read the input on analog pin 0:
  int sensorValue = analogRead(rainPin);
  int sensorPerc = map(sensorValue, 197, 1010, 100, 0); // nell'acqua 197 senza acqua 1010
  if(sensorValue < thresholdValue){
    //digitalWrite(redLED, LOW);    digitalWrite(greenLED, HIGH);
    outMessage=String(sensorValue)+"="+String(sensorPerc)+"% sto bene!";
    analogWrite(waterPump, 0); // 0-255 is maxiumum speed
  }  else {
    //digitalWrite(redLED, HIGH);    digitalWrite(greenLED, LOW);
    outMessage=String(sensorValue)+"="+String(sensorPerc)+"% ho sete!";
    analogWrite(waterPump, 160); // 0-255 is maxiumum speed
  }
  //delay(100);
  lcd.setCursor(0,0);  lcd.print("-Erba cipollina-");
  lcd.setCursor(0,1);  lcd.print(outMessage);
  Serial.println(outMessage);
  delay(1000);
}
