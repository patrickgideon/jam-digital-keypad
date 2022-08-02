#include <LcdKeypad.h>
#include <LiquidCrystal.h>
#include "RTClib.h"
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#include<Wire.h>
RTC_DS3231 rtc;
int jam, menit;
int jam1, menit1;
int tombollcd  = 0;
int bacatombol = 0;
#define tombolright  0
#define tombolup     1
#define tomboldown   2
#define tombolleft   3
#define tombolselect 4
#define tombolnone   5
int read_LCD_buttons()
{
 bacatombol = analogRead(0);      
 if (bacatombol > 1000) return tombolnone;
 if (bacatombol < 50)   return tombolright;  
 if (bacatombol < 250)  return tombolup; 
 if (bacatombol < 450)  return tomboldown; 
 if (bacatombol < 650)  return tombolleft; 
 if (bacatombol < 850)  return tombolselect;  
 return tombolnone;
}

void setup()
{
lcd.begin(16, 2);
Serial.begin(9600);    
rtc.begin();
lcd.clear();
}
 
void loop(){
 tombollcd = read_LCD_buttons();
 DateTime now = rtc.now();
 lcd.setCursor(0,1);
 if(now.hour()<=9){lcd.print("0");}
 lcd.print(now.hour(),DEC);
 lcd.print(':');
 if(now.minute()<=9){lcd.print("0");}
 lcd.print(now.minute(),DEC);
 lcd.print(':');
 if(now.second()<=9){lcd.print("0");}
 lcd.print(now.second(),DEC);
 jam = now.hour(),DEC;
 menit = now.minute(),DEC;
 if(tombollcd == tombolselect) {Settings();}
 }

 void Settings(){
  lcd.clear();
  int b =1;
  DateTime now = rtc.now();
  jam = now.hour(),DEC;
  menit = now.minute(),DEC;

  while(1){
   tombollcd = read_LCD_buttons();
   if(tombollcd == tombolright){b++; if(b=3) b=1;}
   lcd.setCursor(0,0);lcd.print(jam,DEC);
   lcd.setCursor(2,0);lcd.print(":");
   lcd.setCursor(3,0);lcd.print(menit,DEC);
   lcd.setCursor(0,1);lcd.print("SAVE ?");

   switch (b){
    case 1 : 
    lcd.setCursor(0,0);lcd.print(jam,DEC);
    lcd.setCursor(0,0);lcd.print(" ");
    lcd.setCursor(2,0);lcd.print(":");
    if(tombollcd == tombolup) {jam++;if(jam==24)jam=0;}
    if(tombollcd == tomboldown) { jam--;if(jam==-1)jam=23;}
    break;
    case 2 :
    lcd.setCursor(3,0);lcd.print(menit,DEC);
    lcd.setCursor(3,0);lcd.print(" ");
    if(tombollcd == tombolup) {menit++;if(menit==60)menit=0;}
    if(tombollcd == tomboldown) {menit--;if(menit==-1)menit=59;}
    break;
    case 3 :
    lcd.setCursor(0,1);lcd.print("SAVE?");
    lcd.setCursor(0,1);lcd.print(" ");
    if(tombollcd == tombolup){
      jam1=jam; menit1=menit;
      rtc.adjust(DateTime(2020,10,29,jam1,menit1));
      lcd.setCursor(0,0);lcd.print("Data Tersimpan...");
      delay(1000);lcd.clear();
      break;
    }
   }
   if(tombollcd==tombolleft){lcd.clear();break;
  }
 }
 }

 

