#include <HC595.h>
#include "U8glib.h"

U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);
const int chipCount = 4;
const int latchPin = 4;
const int clockPin = 3;
const int dataPin = 5;
int inPin = 2; 
int val = 0; 
int i = 0;
int etat = 0;
int pts = 0;
HC595 ledArray(chipCount,latchPin,clockPin,dataPin);
int delayMs = 100;
int lastPin = ledArray.lastPin();
int ledSpeed = 20;
int led = 6;
int combo = 0;
int sens = 1;

void setup() {
  ledArray.reset();
    u8g.firstPage();  
  do {
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(32, 21); 
  u8g.print("CYCLONE");
  } while( u8g.nextPage() );
  pinMode(inPin, INPUT);
  pinMode(led, OUTPUT);
  
  Serial.begin(9600);
  analogWrite(led, 0);
  delay (200);
  analogWrite(led, 20);
  delay (200);
  analogWrite(led, 40);
  delay (200);
  analogWrite(led, 60);
  delay (200);
  analogWrite(led, 80);
  delay (200);
  analogWrite(led, 100);
  delay (200);
  analogWrite(led, 120);
  delay (200);
  analogWrite(led, 140);
  delay (200);
  analogWrite(led, 160);
  delay (200);
  analogWrite(led, 180);
  delay (200);
  analogWrite(led, 200);
  delay (200);
  analogWrite(led, 220);
  delay (200);
  analogWrite(led, 240);
  delay (200);
  digitalWrite(led, HIGH);
}
void draw(void) {

            

           u8g.setFont(u8g_font_unifont);
           u8g.setPrintPos(20, 12); 
           u8g.print("score:");
            u8g.setFont(u8g_font_unifont);
           u8g.setPrintPos(70, 12); 
           u8g.print(pts);
            u8g.setFont(u8g_font_unifont);
           u8g.setPrintPos(16, 30); 
           u8g.print("speed:");
           u8g.setFont(u8g_font_unifont);
           u8g.setPrintPos(66, 30); 
           u8g.print(ledSpeed);
           u8g.setFont(u8g_font_unifont);
           u8g.setPrintPos(91, 30); 
           u8g.print("%");
           
           if (combo >= 1){
           u8g.setFont(u8g_font_unifont);
           u8g.setPrintPos(100, 12); 
           u8g.print("*");
           }
                      if (combo == 2){
           u8g.setFont(u8g_font_unifont);
           u8g.setPrintPos(110, 12); 
           u8g.print("*");
           }
  
}

void loop() {
  val = digitalRead(inPin);
  Serial.print(val);
  ledSpeed = 120 - delayMs;
  if (val == LOW){               
    etat = 1;
    delay(500);
  }
  

 if ((etat == 0)&&(sens == 1)){                    
    i = i+1 ;
    if (i == lastPin+1 ){
    i = 0;
    }   
    ledArray.reset();
    ledArray.setPin(i, ON);
    delay(delayMs);
  }
   if ((etat == 0)&&(sens == 2)){                    
    i = i-1 ;
    if (i == (-1) ){
    i = 31;
    }   
    ledArray.reset();
    ledArray.setPin(i, ON);
    delay(delayMs);
  }
 
  if ((etat==1)&&(i==30)){                          
     pts = pts +(ledSpeed/5);
     if(delayMs>20){
     delayMs=delayMs-2;
     }
     ledSpeed = 120 - delayMs;
       
    ledArray.setPin(i, ON);         
    digitalWrite(led, HIGH);
    delay(100);
    ledArray.setPin(i, OFF);
    digitalWrite(led, LOW);
    delay(100);
    ledArray.setPin(i, ON);
    digitalWrite(led, HIGH);
    delay(100);
    ledArray.setPin(i, OFF);
    digitalWrite(led, LOW);
    delay(100);
    ledArray.setPin(i, ON);
    digitalWrite(led, HIGH);
    delay(100);
    ledArray.setPin(i, OFF);
    digitalWrite(led, LOW);
    delay(100);
    ledArray.setPin(i, ON);
    digitalWrite(led, HIGH);
    delay(100);
    ledArray.setPin(i, OFF);
    digitalWrite(led, LOW);
    delay(100);
    ledArray.setPin(i, ON);
    digitalWrite(led, HIGH);
    
    u8g.firstPage();  
     do {
    draw();    
    } while( u8g.nextPage() );
   if (delayMs <=40){   
     combo = combo + 1;
     u8g.firstPage();  
      do {
      draw();    
      } while( u8g.nextPage() );
      }
   if (combo == 3){
      u8g.firstPage();
      do {
      u8g.setFont(u8g_font_unifont);
      u8g.setPrintPos(18, 12); 
      u8g.print("COMBO !!!");
      u8g.setFont(u8g_font_unifont);
      u8g.setPrintPos(12, 30); 
      u8g.print("Speed = 20%");
      } while( u8g.nextPage() );
      delayMs = 100;
      combo =0;
      }
    delay(200);
    i = random(0, 31);
    sens = random(1, 3);
    etat = 0;
     }
    
while ((etat==1)&&(i!=29)&&(i!=31)&&(i!=30)){          


  u8g.firstPage();  
  do {
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(23, 12); 
  u8g.print("GAME OVER");
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(55, 30); 
  u8g.print(pts);
  } while( u8g.nextPage() );
  ledArray.setPin(i, ON);
  val = digitalRead(inPin);
    
 if(val == LOW){                     
    pts = 0;
    combo = 0;
    delayMs = 100;
    ledSpeed = 120 - delayMs;    
    u8g.firstPage();  
    do {
    draw();
    } while( u8g.nextPage() );
    i = 0; 
    sens = 1;
    etat = 0;
    delay(400);
 }
}
 if ((etat==1)&&((i==29)||(i==31))){       
     pts = pts+2;                     
     combo = 0;
     if(delayMs>20){
     delayMs=delayMs-10;              
     }
     if(delayMs<=20){
     delayMs = 20;
     }
     ledSpeed = 120 - delayMs;       
     ledArray.setPin(i, ON);
     u8g.firstPage();  
     do {
     draw();
     } while( u8g.nextPage() );
     delay(1000);
     i = random(0, 31);               
     sens = random(1, 3);
     etat = 0;
   } 
 }
 
 
