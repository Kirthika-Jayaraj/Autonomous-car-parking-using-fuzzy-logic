#include <LiquidCrystal.h>
#include <SoftPWM.h>
#include <Servo.h>
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

Servo myservo; 
const int motfPin =  11; // dc motor logic pins
const int motrPin =  12;                                   // Start entering the coordinates with (1,1) and end with (0,0).
int x[]={ 1, 2, 3, 0}; // make sure last and first numbers are not same.
int y[]={ 1, 1, 2, 0}; // last number should end with a '0'.
int i=0, j=0, h=0, v=0, n=16; // n value should include '0'

void mydecimal(int,char,char);

void setup()
{
  pinMode(motfPin, OUTPUT); 
  pinMode(motrPin, OUTPUT); 
  myservo.attach(10); 
  SoftPWMBegin();
  
  SoftPWMSet(13, 0);

  SoftPWMSetFadeTime(13, 1000, 1000);
  digitalWrite(motfPin, HIGH);
  digitalWrite(motrPin, LOW);
  SoftPWMSet(13, 0);
  lcd.begin(16, 2);
  lcd.print("                ");
  
}

void loop()
{ 
  
  while(((x[i])!=(x[n-1]))&&((y[i])!=(y[n-1])))
  {
 

    if(((x[i]==x[i+1])&&(y[i]!=y[i+1]))||((y[i]==y[i+1])&&(x[i]!=x[i+1])))
    {
      if((x[i]==x[i+1])&&(y[i]!=y[i+1]))
      {
        v=1;
        h=0;
      }
      if((y[i]==y[i+1])&&(x[i]!=x[i+1]))
      {
        h=1;
        v=0;
      }
      j=j+1;
       mydecimal(j,0,0);
       mydecimal(h,0,1);
       mydecimal(v,5,1);
       delay(400);
    }
   if((x[i]!=x[i+1])&&(y[i]!=y[i+1]))
    {
      lcd.setCursor(3,1);
      lcd.print("Start");
      delay(400);
      lcd.setCursor(3,1);
      lcd.print("           ");
      lcd.setCursor(3,1);
      lcd.print("Straight");
     digitalWrite(motfPin, HIGH);
     digitalWrite(motrPin, LOW);
     SoftPWMSet(13, 200);
     delay(j*1000);
      lcd.setCursor(3,1);
      lcd.print("           ");
     lcd.setCursor(3,1);
      lcd.print("Stop");
     digitalWrite(motfPin, LOW);
     digitalWrite(motrPin, LOW);delay(3000);
     j=0;
       mydecimal(j,0,0);
       delay(400);
   if((h==1)&&(v==0))
{   
  lcd.setCursor(3,1);
      lcd.print("           ");
      lcd.setCursor(3,1);
      lcd.print("HORIZONTAL M"); 
      delay(400);  
     if((y[i+1]>y[i])&&(y[i+1]!=0))
    {
            lcd.setCursor(3,1);
      lcd.print("           ");
      lcd.setCursor(3,1);
      lcd.print("Left");
     myservo.write(75); delay(2000);
           lcd.setCursor(3,1);
      lcd.print("           ");
     lcd.setCursor(3,1);
     lcd.print("Start");
     digitalWrite(motfPin, HIGH);
     digitalWrite(motrPin, LOW);
     delay(200);
     SoftPWMSet(13, 200);delay(5000);
      lcd.setCursor(3,1);
      lcd.print("           ");
     lcd.setCursor(3,1);
      lcd.print("Stop");
     digitalWrite(motfPin, LOW);
     digitalWrite(motrPin, LOW);delay(2000);
     myservo.write(90); delay(2000);
    }
   else
    {
       if(y[i+1]!=0)
       {
      lcd.setCursor(3,1);
      lcd.print("           ");
      lcd.setCursor(3,1);
      lcd.print("Right");
     myservo.write(115); delay(2000);
           lcd.setCursor(3,1);
      lcd.print("           ");
     lcd.setCursor(3,1);
      lcd.print("Start");
      delay(300);
     digitalWrite(motfPin, HIGH);
     digitalWrite(motrPin, LOW);
     SoftPWMSet(13, 200);delay(5000);
           lcd.setCursor(3,1);
      lcd.print("           ");
     lcd.setCursor(3,1);
      lcd.print("Stop");
     delay(300);
     digitalWrite(motfPin, LOW);
     digitalWrite(motrPin, LOW);delay(3000);
     myservo.write(90); delay(2000);
    }
    } 
}
if((v==1)&&(h==0))
{   
  lcd.setCursor(3,1);
      lcd.print("           ");
      lcd.setCursor(3,1);
      lcd.print("VERTICAL M"); 
      delay(2000);  
     if((x[i+1]<x[i])&&(x[i+1]!=0))
    {
            lcd.setCursor(3,1);
      lcd.print("           ");
      lcd.setCursor(3,1);
      lcd.print("Left");
     myservo.write(75); delay(2000);
           lcd.setCursor(3,1);
      lcd.print("           ");
     lcd.setCursor(3,1);
     lcd.print("Start");
     delay(200);
     digitalWrite(motfPin, HIGH);
     digitalWrite(motrPin, LOW);
     SoftPWMSet(13, 200);delay(2000);
      lcd.setCursor(3,1);
      lcd.print("           ");
     lcd.setCursor(3,1);
      lcd.print("Stop");
     digitalWrite(motfPin, LOW);
     digitalWrite(motrPin, LOW);delay(2000);
     myservo.write(90); delay(2000);
    }
   else
    {
       if(x[i+1]!=0)
       {
      lcd.setCursor(3,1);
      lcd.print("           ");
      lcd.setCursor(3,1);
      lcd.print("Right");
     myservo.write(115); delay(2000);
           lcd.setCursor(3,1);
      lcd.print("           ");
     lcd.setCursor(3,1);
      lcd.print("Start");
     digitalWrite(motfPin, HIGH);
     digitalWrite(motrPin, LOW);
     SoftPWMSet(13, 200);delay(2000);
           lcd.setCursor(3,1);
      lcd.print("           ");
     lcd.setCursor(3,1);
      lcd.print("Stop");
     
     digitalWrite(motfPin, LOW);
     digitalWrite(motrPin, LOW);delay(3000);
     myservo.write(90); delay(2000);
    }
    } 
}










   }
    i=i+1;
         mydecimal(i,5,0);
       delay(400);
  }
  
}
void mydecimal(int a,char pos,char j)
{
  lcd.setCursor(0+pos,j);
  lcd.write(a%1000/100+0x30);
  lcd.setCursor(1+pos,j);
  lcd.write(a%100/10+0x30);
  lcd.setCursor(2+pos,j);
  lcd.write(a%10+0x30);delay(50);
}
