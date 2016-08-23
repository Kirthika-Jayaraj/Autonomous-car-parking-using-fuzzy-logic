#include <LiquidCrystal.h>
#include <Servo.h> 
#include <SoftPWM.h>
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

Servo myservo;  // create servo object to control a servo 

const int motfPin =  11; // dc motor logic pins
const int motrPin =  12; 

const int pingPin = 2;// ultrasonic sensor pins
const int pingReceive = 3;

const int ping1Pin = 4;
const int ping1Receive = 5;

const int ping2Pin = 6;
const int ping2Receive = 7;

const int ping3Pin = 8;
const int ping3Receive = 9;

int sensorValue = 0;        // value read from the pot
long duration, inches, cm;

long duration1, inches1, cm1;

long duration2, inches2, cm2;

long duration3, inches3, cm3;
int lef,stp,timer_bit,timer1_var,timer1_val,timer2_var,timer2_val,ctrl_bit,sum1_bit,result,start_bit;

void ultra(); 
void ultra1(); 
void ultra2(); 
void ultra3();  
void mydecimal(int,char,char);
void fun();
void fun1();
void final_func();
void stop_func();
void reverse_func();
void forward_func();
void func2();

void setup() 
{
 Serial.begin(9600);
  lcd.begin(16, 2);
   myservo.attach(10);  // attaches the servo on pin 10 to the servo object 
  pinMode(motfPin, OUTPUT); 
  pinMode(motrPin, OUTPUT); 
  SoftPWMBegin();
  SoftPWMSet(13, 0);
  SoftPWMSetFadeTime(13, 1000, 1000);
  delay(1000);delay(1000);
  lcd.begin(16, 2);
  // Print a message to the LCD.
 // lcd.print("hello, world!");
  // Print a message to the LCD.
  lcd.print("                ");
  ctrl_bit=5;
  start_bit=0;
  digitalWrite(motfPin, HIGH);
  digitalWrite(motrPin, LOW);
  SoftPWMSet(13, 200);
    // initialize timer1 
 /* noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 31250;            // compare match register 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts*/
}
void loop()
{
  //SoftPWMSet(13, 255);
  SoftPWMSet(13, 200);
  ultra();
  ultra1();
  ultra2();
  ultra3();  
  mydecimal(cm,0,0);
  mydecimal(cm1,5,0);
  mydecimal(cm2,0,1);
  mydecimal(cm3,5,1);

 if(start_bit==0)
  {
     if(cm<=10){ctrl_bit=0;}
  }
   if(cm>=11 && ctrl_bit==0)
   {
            lcd.setCursor(15,1);
            lcd.print("dsfsds");
          start_bit=1;func1();
     
    } 
 
    if(ctrl_bit==1)
    {
        lcd.setCursor(15,1);
        lcd.print("S");
        digitalWrite(motfPin, LOW);
        digitalWrite(motrPin, LOW);delay(3000);
        lcd.setCursor(15,1);
        lcd.print("R");
        myservo.write(115); delay(2000); 
        lcd.setCursor(15,1);
        lcd.print("F");
        digitalWrite(motfPin, HIGH);
        digitalWrite(motrPin, LOW);
        delay(2000);
        SoftPWMSet(13, 250);delay(2000);
        
          lcd.setCursor(15,1);
        lcd.print("S");
        digitalWrite(motfPin, LOW);
        digitalWrite(motrPin, LOW);delay(3000);
         lcd.setCursor(15,1);
        lcd.print("L");
         myservo.write(75); delay(2000); 
        lcd.setCursor(15,1);
        lcd.print("F");
        digitalWrite(motfPin, HIGH);
        digitalWrite(motrPin, LOW); delay(2000);
         SoftPWMSet(13, 250);delay(3000);
        lcd.setCursor(15,1);
        lcd.print("S");
        digitalWrite(motfPin, LOW);
        digitalWrite(motrPin, LOW);delay(3000);
        
          lcd.setCursor(14,1);
        lcd.print("ST");
       myservo.write(95); delay(2000); 
          lcd.setCursor(15,1);
             lcd.print("R");
             digitalWrite(motrPin, HIGH);
      digitalWrite(motfPin, LOW);//delay(2000); 
        //reverse_func();
      /*   lcd.setCursor(15,1);
        lcd.print("S");
        digitalWrite(motfPin, LOW);
        digitalWrite(motrPin, LOW);
        lcd.setCursor(15,1);
        lcd.print("F");*/
         final_func();
        
         
       lcd.setCursor(15,1);
             lcd.print("S");
         digitalWrite(motfPin, LOW);
      digitalWrite(motrPin, LOW);
      delay(3000);start_bit=2;ctrl_bit=2;
  
     /* lcd.setCursor(15,1);
             lcd.print("L");
         myservo.write(115); delay(3000);
          lcd.setCursor(15,1);delay(3000);
        digitalWrite(motfPin, LOW);
      digitalWrite(motrPin, LOW);
             lcd.print("F");
             digitalWrite(motfPin, HIGH);
      digitalWrite(motrPin, LOW);delay(3000);
        digitalWrite(motfPin, LOW);
      digitalWrite(motrPin, LOW);
      timer1_var=0;*/
      
    }
   /* else
    {start_bit=0;
      lcd.setCursor(14,1);
             lcd.print("RE");
         myservo.write(95); 
       }*/
     
   
   /*if(ctrl_bit==1 && cm>100)
   {
     ctrl_bit=2;
   }
   if(ctrl_bit==2)
   {
      if(cm<10)
      {
          timer2_var++;
           mydecimal(timer2_var,4,1);
        
      }
      else
      {
          timer2_val=timer2_var;
         mydecimal(timer2_val,10,1);sum1_bit=2;ctrl_bit=3;
      }
   }
      if(sum1_bit==2)
      {
        sum1_bit=0;
         result=timer2_val-timer1_val;delay(1000);
          mydecimal(result,0,1);
      }*/
  /*if(cm2>50 && stp)
      {
          digitalWrite(motrPin, LOW);
          digitalWrite(motfPin, LOW);
          delay(1000);delay(1000);
          lcd.setCursor(9,0);
          lcd.print("left");
          //lcd.setCursor(0,1);
          //lcd.print("reii");
           delay(1000);myservo.write(75);
          //fun1();
          delay(1000);delay(1000);
          digitalWrite(motrPin, HIGH);
          digitalWrite(motfPin, LOW);
          lcd.setCursor(9,0);
          lcd.print("forr");
          while(cm>50)
                {
                     ultra(); 
                     mydecimal(cm,0,0);
                }
          lcd.setCursor(9,0);
          delay(1000);delay(1000);
          digitalWrite(motrPin, LOW);
          digitalWrite(motfPin, LOW);
          lcd.print("STOP");
          stp=0;
          
      }*/
}
/*ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
 // digitalWrite(ledPin, digitalRead(ledPin) ^ 1);   // toggle LED pin
 if(timer_bit==1){timer_var++;}
}*/
void func1()
{
   while(1)
    {
       ultra();
       timer1_var++;
        mydecimal(timer1_var,12,0);
        if(timer1_var>2){delay(1000);timer1_var=0;ctrl_bit=1;break;}
      // if(cm<=10){ctrl_bit=1; break;}
     } 
 }
 void  reverse_func()
 {
   while(1)
   {
     
     lcd.setCursor(14,1);
        lcd.print("ST");
         myservo.write(95); 
      lcd.setCursor(15,1);ultra2();
             lcd.print("R");
             digitalWrite(motrPin, HIGH);
      digitalWrite(motfPin, LOW); 
      delay(1000);
      if(cm2<=15){ digitalWrite(motfPin, LOW);
      digitalWrite(motrPin, LOW);break; }
      ultra();
    if(cm<15){stop_func();break;}
   }
 }
  void  forward_func()
 {
   while(1)
   {
    
      lcd.setCursor(15,1);
        lcd.print("L");
        myservo.write(115); 
      lcd.setCursor(15,1); ultra3();
             lcd.print("F");
             digitalWrite(motfPin, HIGH);
      digitalWrite(motrPin, LOW);
      delay(1000);
      if(cm3<=15){ digitalWrite(motfPin, LOW);
      digitalWrite(motrPin, LOW);break; }
      ultra();
    if(cm<15){stop_func();break;}
   }
 }
 void final_func()
  {
    while(1)
    {
        
         mydecimal(cm,0,0);
       reverse_func();
         forward_func();
        
         
     
    }
    
  }
  void stop_func()
  {
    
       lcd.setCursor(12,1);
        lcd.print("STOP");
       digitalWrite(motfPin, LOW);
      digitalWrite(motrPin, LOW);cm=cm1=cm2=cm3=0;
      start_bit=2;ctrl_bit=2;while(1);
  
    
    
  }
 void func2()
{
   while(1)
    {
      
       timer2_var++;ctrl_bit=2;
       mydecimal(timer2_var,5,1);
       
     } 
 }
void ultra()
{
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingReceive, INPUT);
  duration = pulseIn(pingReceive, HIGH);
  // convert the time into a distance
 // inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
}
  void ultra1()
{
  pinMode(ping1Pin, OUTPUT);
  digitalWrite(ping1Pin, LOW);
  delayMicroseconds(2);
  digitalWrite(ping1Pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(ping1Pin, LOW);
  pinMode(ping1Receive, INPUT);
  duration1 = pulseIn(ping1Receive, HIGH);
  // convert the time into a distance
 // inches = microsecondsToInches(duration);
  cm1 = microsecondsToCentimeters(duration1);  
  //Serial.print(inches);
  //Serial.print("#");delay(50);
 //Serial.print(cm);delay(50);
  //Serial.write("\x0d\x0a");
  //delay(50);
// Serial.print("cm");
  //Serial.println(); 
  //delay(10);
}
  void ultra2()
{
  pinMode(ping2Pin, OUTPUT);
  digitalWrite(ping2Pin, LOW);
  delayMicroseconds(2);
  digitalWrite(ping2Pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(ping2Pin, LOW);
  pinMode(ping2Receive, INPUT);
  duration2 = pulseIn(ping2Receive, HIGH);

  // convert the time into a distance
 // inches = microsecondsToInches(duration);
  cm2 = microsecondsToCentimeters(duration2);
  
  //Serial.print(inches);
  //Serial.print("#");delay(50);
 //Serial.print(cm);delay(50);
  //Serial.write("\x0d\x0a");
  //delay(50);
// Serial.print("cm");
  //Serial.println();
  
  //delay(10);
}
  void ultra3()
{
  pinMode(ping3Pin, OUTPUT);
  digitalWrite(ping3Pin, LOW);
  delayMicroseconds(2);
  digitalWrite(ping3Pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(ping3Pin, LOW);
  pinMode(ping3Receive, INPUT);
  duration3 = pulseIn(ping3Receive, HIGH);

  // convert the time into a distance
 // inches = microsecondsToInches(duration);
  cm3 = microsecondsToCentimeters(duration3);
  
  //Serial.print(inches);
  //Serial.print("#");delay(50);
 //Serial.print(cm);delay(50);
  //Serial.write("\x0d\x0a");
  //delay(50);
// Serial.print("cm");
  //Serial.println();
  
  //delay(10);
}
  long microsecondsToInches(long microseconds)
      {
       
            return microseconds / 74 / 2;
      }
      
      long microsecondsToCentimeters(long microseconds)
      {
      
            return microseconds / 29 / 2;
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
void fun()
{
   myservo.write(96); 
}  
/*void fun1()
{
   myservo.write(96); 
}
*/

  
  
  
  

