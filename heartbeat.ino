#include <Adafruit_SSD1306.h>
#include <splash.h>

#include <EEPROM.h>


#include <Wire.h>
#include "RTClib.h"

#include <Adafruit_SSD1306.h>
 
#define OLED_Address 0x3C
Adafruit_SSD1306 oled(1);
 const int MPU_ADDR = 0x69; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
 int value=0;

/////////////////////////////////////////////
int stepcount_sensitivity=15000;
/////////////////////////////////////////////
int count=0;
int bpm_arr[10],BPM1,BPM_FLAG=0,j=0;
int cal,flag1=0,x=0;
int lastx=0;
int lasty=0;
int LastTime=0;
int temp_count=0;
int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int address=0;
int lacx=0,lacy=0,lacz=0,steps=0;
bool BPMTiming=false;
bool BeatComplete=false;
 unsigned int y;
  unsigned int m; 
  unsigned int d;
   int h; 
   int t;
  int flag=0;
  int temp_last; 
char tmp_str[7]; // temporary variable used in convert function

char* convert_int16_to_str(int16_t i) { 
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}
const int beat=A0; //Assigning pin A0 to variable beat 
const int sensor=A1; // Assigning pin A1 to variable sensor
const int buzzer= 12; //Assigning buzzer pin
int temp;  //variable to store temperature in degree Celsius
float vout;  //temporary variable to hold sensor reading
int BPM=0;

RTC_DS3231 rtc;

#define UpperThreshold 410
#define LowerThreshold 400

void setup() {
  
      if(EEPROM.read(address)==255)
  EEPROM.write(address,0);
  
  steps=EEPROM.read(0);
 
  Serial.begin(9600);
  Serial.println(EEPROM.read(1));
   Serial.println("hi");
   if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    //while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
  }
  // Comment out below lines once you set the date & time.
    // Following line sets the RTC to the date & time this sketch was compiled
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
   Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  pinMode(sensor,INPUT);  
  pinMode(beat,INPUT); // Configuring pin A1 as input
  //pinMode(13,OUTPUT);  
  pinMode(buzzer,OUTPUT);  
  
  digitalWrite(12,HIGH);
  
  oled.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
  oled.clearDisplay();
  oled.setTextSize(1);
  Serial.println("hi");
  
  
}


void loop() 
{
   /*DateTime no = rtc.now();
    y=no.year();
  
   m=no.month(); 
   d=no.day();
   h=no.hour(); 
   t=no.minute();
   if (temp_count==0)
  {
   vout=analogRead(sensor);
   vout=(vout*500)/1023;
   temp=vout;
   //temp=temp/90;
  }
   if ((temp-temp_last)>2)
   temp=temp+1;
   if ((temp_last-temp)>2)
   temp=temp-1;

     temp_last=temp;
  }
  
   temp_count++;
   
   if (temp_count==90)
   {
    temp_count=0;
    }
    
   //int value1 = analogRead(beat);
   temp=millis();

   

   while(millis()<(temp+10000))

   {

      if(analogRead(beat)>650)

        {

         count=count+1;

         
  }

   }

   

         
         count=count*6;


 
 temp=0;

 while(1);
 */oled.setTextColor(WHITE);
  
 /* Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
    
  accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
 int p= accelerometer_x-lacx;
 int q =accelerometer_y-lacy;
 int r= accelerometer_z-lacz;
 if(p>stepcount_sensitivity ||q>stepcount_sensitivity||r>stepcount_sensitivity)
 {
  if (flag==0)
  {steps++;
  EEPROM.write(address,steps);
  Serial.print("Steps");
  flag=1;}
  if (flag==1)
  {
    flag=0;}
  //Serial.println(EEPROM.read(address),DEC);
  }
  cal=0.04*steps;
  
  lacx=accelerometer_x;
  lacy=accelerometer_y;
  lacz=accelerometer_z;
  Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
  Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
  Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));
  Serial.println();
  */ 
   oled.writeFillRect(0,50,128,16,BLACK);
  
   
   oled.clearDisplay();
   oled.setTextSize(2);
   oled.setCursor(41,8);
   if (h >= 0 && h < 10) 
   oled.print('0');
   oled.print(h);
   oled.print(":");
   if (t >= 0 && t < 10) 
   oled.print('0');
   oled.print(t);
   Serial.print(h);
   Serial.print(":");
   Serial.println(t);
   oled.setTextSize(1);
   
  
   {
    oled.setTextSize(1);
   
   oled.setCursor(0,0);
   oled.print(y);
   oled.print("/");
  
   if (m >= 0 && m < 10) 
   oled.print('0');
   oled.print(m);
   oled.print("/");
  if (d >= 0 && d < 10) 
   oled.print('0');
   oled.print(d);

   oled.setCursor(80,0);
   oled.print(temp);
   oled.print(" C ");
   
   oled.setCursor(0,24);
   oled.print(cal);
   oled.print(" cal ");
   }
  
   {
   // steps=EEPROM.read(address);
   oled.setCursor(0,12);
   oled.print(steps);
   //oled.print(" STEPS");
   oled.setCursor(80,24);  
   {
    oled.print(BPM);
    oled.print(" ");   
   }
   oled.display();
   }
    oled.write(3);
      
    
    oled.display();
   
  Serial.print(BPM);
  Serial.println(" BPM");
  
  Serial.print(temp);
  Serial.println(" C");
  
  delay(500);
  x++;
}
