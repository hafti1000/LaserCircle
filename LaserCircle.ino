#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

Servo Xservo;
Servo Yservo;

#define y0 95
#define x0 90


int posx = x0;
int posy = y0;    
int x,y;
int t=0;
int r=22;
int s=10;


void setup() {
  Xservo.attach(9);  
  Yservo.attach(8);
  Xservo.write(posx);
  Yservo.write(posy);
  
  Serial.begin(9600);
  
  lcd.begin();
  lcd.backlight();
  lcd.print("Los Gehts!");
  for(int i = 9; i>=0; i--)
  {
    lcd.setCursor(0,1);
    lcd.print(i);
    delay(555);
  }
  lcd.clear();
  lcd.setCursor(7,1);
  lcd.print(" by Peter");
}

void printd(int i)
{
    boolean neg=false;
    if(i<0)
    {
      neg=true;
      i=-i;
    }

    if(i<100)
    {
      lcd.print(" ");
      if(i<10)
        lcd.print(" ");
    }
    if(neg)
      lcd.print("-");
    else
      lcd.print(" ");
    lcd.print(i);
}

void loop()
{

          y=r*sin((t-90)*3.141/180);
          x=r*sin(t*3.141/180);
          Yservo.write(posy=y*0.7+y0);
          Xservo.write(posx=x+x0);
              lcd.setCursor(0,0);
              lcd.print("x =");
              printd(x);
              lcd.print(" t =");
              printd(t);
              lcd.setCursor(0,1);
              lcd.print("y =");
              printd(y); 
          t+=s;
          if(t>=360) t=0;
  
  if (Serial.available())
    {
       switch(Serial.read())
       {
        case 'r':
            r = Serial.read()-'0';
            while (Serial.available())
              {
                r*=10;
                r+= Serial.read()-48;
              }
        break;
        case 's':  
            s = Serial.read()-'0';
            while (Serial.available())
              {
                s*=10;
                s+= Serial.read()-48;
              }
        break;
        default :  
        break;
       }
    }
}
