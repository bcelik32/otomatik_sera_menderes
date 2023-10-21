#include <AvrI2c_Greiman.h>
#include <LiquidCrystal_I2C_AvrI2C.h>
 
LiquidCrystal_I2C_AvrI2C lcd(0x27,16,2);
bool manuel=false;
bool oto=true;
#include "DHT.h"
#include <Servo.h>
Servo motor;
  Servo catimotor;
int ldr_pin=A0;
int ldr_pin2=A1;
int ldr_okunan;
int ldr_okunan2;
int servoaci=90;
int servomax=170;
int servomin=25;
#define DHTPIN A3  // veri okuma pini
#define EnA 7
#define EnB 6
#define In1 8
#define In2 9
#define In3 10
#define In4 11
#define DHTTYPE DHT11   // DHT 11
#define tnPin A2
#define waters A2
DHT dht(DHTPIN, DHTTYPE);
int uyariled1=6; // Role modulunun sinyal pininin bulundugu yeri kart degişkenine tanımladık.  
 // Role modulunun sinyal pininin bulundugu yeri kart degişkenine tanımladık.  

int kart3=5; // Role modulunun sinyal pininin bulundugu yeri kart degişkenine tanımladık.  
int sudegeri = 0;
int incomingByte;      // a variable to read incoming serial data into

void setup() {
   dht.begin();
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Akilli Sera"); //İlk satıra yazalım
  lcd.setCursor(9,1);
  lcd.print("Sistemi"); //İkinci satıra yazalım
  Serial.begin(9600);
  motor.attach(2);
  catimotor.attach(8);
  pinMode(kart3, OUTPUT); // Role kartının bulundugu pini açılmasını sağladık. 
  pinMode(EnA, OUTPUT);
  pinMode(EnB, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);       
  digitalWrite(kart3,HIGH);    // ıstıcı fanı kapat
oto=true;
   manuel=false;

}

void loop() {
ldr_okunan=analogRead(ldr_pin);
ldr_okunan2=analogRead(ldr_pin2);
int ldr1formul=(ldr_okunan)/2;
int ldr2formul=(ldr_okunan2)/2;
Serial.println("okubir");
Serial.println(ldr_okunan);
int ldrkalan=(ldr_okunan-ldr_okunan2);
Serial.println("okuiki");
Serial.println(ldr_okunan2);

if(ldr_okunan - ldr_okunan2>  ldr1formul && ldr_okunan - ldr_okunan2>ldr2formul){
  servoaci = servoaci +3;
  delay(3); 
  } 
else if(ldr_okunan2 - ldr_okunan>  ldr1formul && ldr_okunan2 - ldr_okunan>ldr2formul){
servoaci = servoaci -3;
delay(3);
}
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  int tnem = analogRead(tnPin);  // Read the analog value form sensor
  int tnem2 = map(tnem,0,1023,0,100);
  int yuzdetnem =(100-tnem2);
  int sudegeri = analogRead(waters);    // Read the analog value form sensor
  Serial.print(("z"));
  Serial.println(h);
  Serial.print(("s"));
  Serial.println(t);
  Serial.print(("t"));
  Serial.println(yuzdetnem);
  
  delay(250);
    lcd.setCursor(0,0);
    lcd.print("Sera Isisi: ");
    lcd.setCursor(12,0);
    lcd.print(t);
    lcd.setCursor(14,0);
    lcd.print("'C");
    lcd.setCursor(0,1);
    lcd.print("Toprak Nemi: ");
    lcd.setCursor(13,1);
    lcd.print("%");
    lcd.setCursor(14,1);
    lcd.print(yuzdetnem);

if (Serial.available() > 0) {
          incomingByte = Serial.read();
              if (incomingByte == 'o') {
              oto=true;
              manuel=false;
              }
              if (incomingByte == 'm') {
              oto=false;
              manuel=true;
              }
if (oto==1 || oto==true){
  if(ldr_okunan - ldr_okunan2>  ldr1formul && ldr_okunan - ldr_okunan2>ldr2formul){
  servoaci = servoaci +3;
  delay(3); 
  } 
else if(ldr_okunan2 - ldr_okunan>  ldr1formul && ldr_okunan2 - ldr_okunan>ldr2formul){
servoaci = servoaci -3;
delay(3);
   motor.write(servoaci); 
delay(3);
}
  if (t<=25){
    delay(100);
    digitalWrite(In3, LOW);
   digitalWrite(In4, HIGH);
  // hızı 150/255 yap
    analogWrite(EnB, 255);    // ıstıcı fanı kapatzz
    lcd.setCursor(0,0);
    lcd.print("Sera Isitiliyor");
    lcd.setCursor(0,1);
    lcd.print("Sera Isisi: ");
    lcd.setCursor(12,1);
    lcd.print(t);
    lcd.setCursor(14,1);
    lcd.print("'C");
    delay(100);
    }
  if (t>=28){
    
digitalWrite(In1, HIGH);
   digitalWrite(In2, LOW);
       analogWrite(EnA, 255);    // ıstıcı fanı kapat
    lcd.setCursor(0,0);
    lcd.print("Sera Sogutuluyor"); //İlk satıra yazalım    delay(100);
    lcd.setCursor(0,1);
    lcd.print("Sera Isisi: ");
    lcd.setCursor(12,1);
    lcd.print(t);
    lcd.setCursor(14,1);
    lcd.print("'C");
    delay(100);
    }
  if (t<28 && t>25){
    digitalWrite(In1, LOW);
    digitalWrite(In2, LOW);
     digitalWrite(In3, LOW);
    digitalWrite(In4, LOW);
  }
  if (yuzdetnem<40){
    delay(100);
    digitalWrite(kart3,  LOW);   
    lcd.setCursor(0,0);
    lcd.print("Toprak Sulaniyor");
    lcd.setCursor(0,1);
    lcd.print("Toprak Nemi: ");
    lcd.setCursor(12,1);
    lcd.print("%");
    lcd.setCursor(13,1);
    lcd.print(yuzdetnem);
    lcd.setCursor(16,1);
    lcd.print(" ");
    }
  if (yuzdetnem>70){
    delay(120);
    digitalWrite(kart3,  HIGH);   
    delay(100);
    }
  if (yuzdetnem<70 && yuzdetnem>40){
    delay(100);
    digitalWrite(kart3,  HIGH); 
    delay(100);
    }

  if (sudegeri<420){
   //catimotor.write(162);
    digitalWrite(uyariled1,  LOW);     
    delay(100);
    }
    Serial.println(tnem);
}
if (manuel==1 || manuel==true){


    if (incomingByte == 'q') { // olmazsa tektırnak yerine çift tırnak kullanmayı dene
    catimotor.write(5);
    delay(10);

    }
    if (incomingByte == 'w') {
    catimotor.write(78);
        delay(10);
    }
    if (incomingByte == 't') {
digitalWrite(In1, HIGH);
    digitalWrite(In2,LOW);
        analogWrite(EnA, 255);
                  Serial.println("ısıtıcı fan açıldı");
// ıstıcı fanı kapat
}
    if (incomingByte == 'y') {
digitalWrite(In1, LOW);
    digitalWrite(In2,LOW);
                          Serial.println("ısıtıcı fan kapatıldı");
// ıstıcı fanı kapat
}
    if (incomingByte == 'e') {
digitalWrite(In3, LOW);
   digitalWrite(In4, HIGH);
       analogWrite(EnB, 255);    // ıstıcı fanı kapat
}
    if (incomingByte == 'r') {
digitalWrite(In3, LOW);
   digitalWrite(In4, LOW);
       analogWrite(EnB, 255);    // ıstıcı fanı kapat
}
    if (incomingByte == 'u') {
      digitalWrite(kart3, LOW);
    }
     if (incomingByte == 'p') {
      digitalWrite(kart3, HIGH);
    }
    if (incomingByte == 'h') {
  servoaci = servoaci +10;
  delay(3);
    }
    if (incomingByte == 'j') {
  servoaci = servoaci -10;
  delay(3);
    }
   motor.write(servoaci); 

    }
}
      //}

}

 
 
