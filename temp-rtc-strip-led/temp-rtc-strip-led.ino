
#include<stdio.h>
#include<stdlib.h>
#include <FastLED.h>
#include <dht.h>
#include <DS3231.h>
// How many leds in your strip?
#define NUM_LEDS 64

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN3 49
#define DATA_PIN4 50
#define DATA_PIN5 51
#define DATA_PIN6 52
#define DHT11_PIN 53
#define LED_TYPE WS2812
#define LightDodgerBlue 0x6ea8dc
#define BRIGHTNESS 24
char data;            //Variable for storing received data
char global_data = '3';
String parseTime;
String hour,minute;
String date;

// Define the array of leds
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
CRGB leds4[NUM_LEDS];
DS3231 rtc(SDA, SCL);


uint8_t beginHue = 160;
//DodgerBlue 160 - 230
uint8_t deltaHue = 1;
int count = 0;


dht DHT;



void setup()
{


  Serial.begin(9600);
  rtc.begin();
//  rtc.setDOW(WEDNESDAY);
//  rtc.setTime(5, 55, 10);
//  rtc.setDate(1, 1, 2018);

  
  FastLED.addLeds<WS2812, DATA_PIN3, GRB>(leds1, NUM_LEDS);
  FastLED.addLeds<WS2812, DATA_PIN4, GRB>(leds2, NUM_LEDS);
  FastLED.addLeds<WS2812, DATA_PIN5, GRB>(leds3, NUM_LEDS);
  FastLED.addLeds<WS2812, DATA_PIN6, GRB>(leds4, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

     // Setup Serial connection
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}
  

  for (int i=2; i<=19; i++) {
    pinMode(i, OUTPUT);

}
for (int i=22; i<=48; i++) {
    pinMode(i, OUTPUT);

}

}

void loop()
{

  int hr, min;
  parseTime = rtc.getTimeStr();
  hour = parseTime.substring(0,2);
  hr = hour.toInt();
  minute = parseTime.substring(3,5);
  min = minute.toInt();
  date = rtc.getDOWStr();
  //Serial.println(rtc.getDOWStr()); //"Wednesday"

  double temperature = DHT.temperature;
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);

  
      data = Serial.read();
      if(data == '1' || data == '2' || data == '3' || data == '4'){
        global_data = data;
      }
      Serial.print(global_data);          //Print Value inside data in Serial monitor
      Serial.print("\n"); 
      mode(global_data, hr, min, temperature, date);
  
  // Wait one second before repeating
  delay (1000);


}

void mode(char mode_num, int hr, int min, int temperature, String date){
  switch(mode_num){
        case '1':
          emoji_demo(hr,min);
          break;
        case '2':
          temp_mode(hr,min,temperature);
          break;
        case '3':
          emoji_mode(hr,min,date);
          break;
        case '4':
          bulb_demo(hr,min,temperature,date);
          break;
        
      
  }
}


void temp_mode(int hr, int min, double temperature){
  FastLED.clear();
  temp(int(temperature));
  time(hr,min);
}

void emoji_mode(int hr, int min, String date){
  FastLED.clear();
  emoji(date);
  time(hr,min);
}
void emoji_demo(int hr, int min){
  count = count % 7; 
  FastLED.clear();
  switch(count){
  case 0:
    Monday();
    break;
  case 1:
    Tuesday();
    break;
  case 2:
    Wednesday();
    break;
  case 3:
    Thursday();
    break;
  case 4:
    Friday();
    break;
  case 5:
    Saturday();
    break;
  case 6:
    Sunday();
    break;
  }
  delay(1000);
  count++;
  time(hr,min);
}

void bulb_demo(int h, int m, int t, String d){
      
  int sec = 0, min = 1;
  
  for (sec=0; sec<=60; sec ++) {
    time(min,sec);
    data = Serial.read();
      if(data == '1' || data == '2' || data == '3' || data == '4'){
        global_data = data;
        break;
      }
      
    
    if (sec==60) {
      sec = 0;
      min++;
      if(min == 13){
        min = 1;
      }
    }
    
  
  delay(1000);
  
  
}
}


void temp(int temperature){
  
  if(temperature<25){
    snowFlake();
    delay(500);

    switch(temperature){
      case 22:
        FastLED.clear();
        Twenty2();
        delay(1000);
        break;
      case 23:
        FastLED.clear();
        Twenty3();
        delay(1000);

        break;
      case 24:
        FastLED.clear();
        Twenty4();
        delay(1000);
        break;
    }

   
  }else if(temperature> 24 && temperature < 27){
    switch(temperature){
      case 25:
        FastLED.clear();
        house25();
        delay(2000);    
        break;
      case 26:
        FastLED.clear();
        house26();
        delay(2000);        
        break;
      
    }
}else{
  FastLED.clear();
  fire();        

  switch(temperature){
      case 27:
        FastLED.clear();
        Twenty7();
        delay(1000);
        break;
      case 28:
        FastLED.clear();
        Twenty8();
        delay(1000);
        break;
      case 29:
        FastLED.clear();
        Twenty9();
        delay(1000);
        break;
      case 30:
        FastLED.clear();
        Thirty0();
        delay(1000);
        break;
  }
  delay(1500);
}

}


void emoji(String date){
  if(date == "Monday"){
    Monday();
  }else if(date == "Tuesday"){
    Tuesday();
  }else if(date == "Wednesday"){
    Wednesday();
  }else if(date =="Thursday"){
    Thursday();
  }else if(date == "Friday"){
    Friday();
  }else if(date == "Saturday"){
    Saturday();
  }else{
    Sunday();
  }
    delay(1500);
  
}





void fire(){
  fireFrame1();
  delay(100);
  FastLED.clear();
  fireFrame2();
  delay(100);
  FastLED.clear();
  fireFrame3();
  delay(100);
  FastLED.clear();
  fireFrame2();
  delay(100);
  FastLED.clear();
  fireFrame1();
  delay(100);
  FastLED.clear();
  fireFrame2();
  delay(100);
  FastLED.clear();
  fireFrame3();
  delay(100);
  FastLED.clear();
  fireFrame2();
  delay(100);
  FastLED.clear();
  fireFrame1();
  delay(100);
  FastLED.clear();
}


void snowFlake(){
  int index1[] = {13,15,19,22,23,26,27,31,36,39,41,45,47,50,54,55,56,57,58,59,60,61,62,63};
  int index2[] = {15,21,23,27,30,31,34,35,39,44,47,49,53,55,58,62,63};
  int index3[] = {14,20,23,27,28,37,42,46,51,55,58,59,60,61,62,63};
  int index4[] = {22,28,31,35,36,45,50,54,59,63};


while(beginHue < 200){
  for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    fill_rainbow(leds1 + index1[i], 1, beginHue, deltaHue); 
}

for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    fill_rainbow(leds2 + index2[i], 1, beginHue, deltaHue); 
}


for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    fill_rainbow(leds3 + index3[i], 1, beginHue, deltaHue); 
}


for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    fill_rainbow(leds4 + index4[i], 1, beginHue, deltaHue); 
}

  EVERY_N_MILLISECONDS( 10 ) { beginHue++; } // slowly cycle the "base color" through the rainbow
  FastLED.show();
} 

while(beginHue > 160){

 for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    fill_rainbow(leds1 + index1[i], 1, beginHue, deltaHue); 
}
for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    fill_rainbow(leds2 + index2[i], 1, beginHue, deltaHue); 
}


for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    fill_rainbow(leds3 + index3[i], 1, beginHue, deltaHue); 
}

for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    fill_rainbow(leds4 + index4[i], 1, beginHue, deltaHue); 
}
    EVERY_N_MILLISECONDS( 10 ) { beginHue--; } // slowly cycle the "base color" through the rainbow
    FastLED.show();
 }
}






void house25(){

  int index1[] = {15,22,29,36,43,50,57,58};
  int index2[] = {15, 22,23,29,36,43,50,57};
  int index3[] = {7,17,18,19,20,21,22,23,25,33,41,49,57};
  int index5[] = {36,39,44,45,52,54,60,63};
  int index4[] = {10,11,12,13,14,15,18,26,34,42,50,56,58};
  int index6[] = {36,37,38,44,52,53,54,62};

  
for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    leds1[index1[i]] = CRGB::SaddleBrown; 
    leds1[61] = CRGB::DarkGreen;
    leds1[62] = CRGB::DarkGreen;
    

}

for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    leds2[index2[i]] = CRGB::SaddleBrown; 
    leds2[39] = CRGB::DarkGreen;
    leds2[47] = CRGB::DarkGreen;
    leds2[55] = CRGB::DarkGreen;
       
}

for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    leds3[index3[i]] = CRGB::SaddleBrown; 
}
for(int i=0; i < sizeof(index5)/sizeof(index5[0]); i++){
    leds3[index5[i]] = CRGB::DarkGreen; 
}


for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    leds4[index4[i]] = CRGB::SaddleBrown;
}
for(int i=0; i < sizeof(index6)/sizeof(index6[0]); i++){
    leds4[index6[i]] = CRGB::DarkGreen;   
}


FastLED.show();

}


void house26(){

  int index1[] = {15,22,29,36,43,50,57,58};
  int index2[] = {15,22,23,29,36,43,50,57};
  int index3[] = {7,17,18,19,20,21,22,23,25,33,41,49,57};
  int index4[] = {10,11,12,13,14,15,18,26,34,42,50,56,58};
  int index11[] = {61,62};
  int index21[] = {39,47,55};
  int index31[] = {36,39,44,45,52,54,60,63};
  int index41[] = {36,37,38,44,46,52,53,54,62};
  
for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    leds1[index1[i]] = CRGB::SaddleBrown; 
    FastLED.show();   
}

for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    leds2[index2[i]] = CRGB::SaddleBrown; 
    FastLED.show();   
    }

for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    leds3[index3[i]] = CRGB::SaddleBrown; 
    FastLED.show();
    
}

for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    leds4[index4[i]] = CRGB::SaddleBrown;
    FastLED.show();
  }
  
for(int i=0; i < sizeof(index11)/sizeof(index11[0]); i++){
    leds1[index11[i]] = CRGB::DarkGreen; 
    FastLED.show();  
}

for(int i=0; i < sizeof(index21)/sizeof(index21[0]); i++){
    leds2[index21[i]] = CRGB::DarkGreen; 
    FastLED.show();  
}

for(int i=0; i < sizeof(index31)/sizeof(index31[0]); i++){
    leds3[index31[i]] = CRGB::DarkGreen; 
    FastLED.show();    
}

for(int i=0; i < sizeof(index41)/sizeof(index41[0]); i++){
    leds4[index41[i]] = CRGB::DarkGreen; 
    FastLED.show();    
}

}




void fireFrame1(){

  int index1[] = {7, 15, 23, 30, 31, 38, 39, 46, 53, 54,  61 };
  int index2[] = {29,  38, 39, 45, 46, 47, 52, 53, 54, 59, 60, 61};
  int index3[] = {19, 20,  26, 27, 28, 29,30,31,33, 34, 35, 39, 41, 42, 49, 50, 57, 58};
  int index5[] = {36, 37, 38, 43, 44, 45, 46, 47,  51, 52, 53, 54, 55, 59, 60, 61, 62, 63};
  int index4[] = {11, 12, 13, 14, 15, 19, 20, 21, 22, 23, 26, 27, 28, 34, 35,  43,  60};
  int index6[] = {29, 30, 31, 36, 37, 38, 39, 44, 45, 46, 47, 52, 53, 54, 55, 61, 62, 63};


for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    leds1[index1[i]] = CRGB::Maroon; 
    leds1[47] = CRGB::Orange;
    leds1[55] = CRGB::Orange;
    leds1[62] = CRGB::Orange;
    leds1[63] = CRGB::Orange;
    

}


for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    leds2[index2[i]] = CRGB::Maroon; 
    leds2[55] = CRGB::Orange;
    leds2[62] = CRGB::Orange;
    leds2[63] = CRGB::Orange;
   

}

for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    leds3[index3[i]] = CRGB::Maroon; 
      
}
for(int i=0; i < sizeof(index5)/sizeof(index5[0]); i++){
    leds3[index5[i]] = CRGB::Orange; 
      
}


for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    leds4[index4[i]] = CRGB::Maroon;
        
}
for(int i=0; i < sizeof(index6)/sizeof(index6[0]); i++){
    leds4[index6[i]] = CRGB::Orange;
        
}
FastLED.show();

}

void fireFrame2(){
  int index1[] = {23,31,38,39,46,47,51,53,54,59,60,61};
  int index2[] = {29,31,38,39,45,46,47,51,52,53,54,57,58,59,60};
  int index3[] = {19, 20, 21,  26, 27, 28, 29,30, 33, 34, 35, 39, 41, 42, 49, 50, 57, 58};
  int index5[] = {36, 37, 38, 43, 44, 45, 46, 47,  51, 52, 53, 54, 55, 59, 60, 61, 62, 63};
  int index4[] = {11, 12, 13, 14, 15, 19, 20, 21, 22, 23, 26, 27, 28, 34, 35, 42, 43,  51,  60};
  int index6[] = {29, 30, 31, 36, 37, 38, 39, 44, 45, 46, 47, 52, 53, 54, 55, 61, 62, 63};
  
for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    leds1[index1[i]] = CRGB::Maroon; 
    leds1[55] = CRGB::Orange;
    leds1[62] = CRGB::Orange;
    leds1[63] = CRGB::Orange;
    

}


for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    leds2[index2[i]] = CRGB::Maroon; 
    leds2[55] = CRGB::Orange;
    leds2[61] = CRGB::Orange;
    leds2[62] = CRGB::Orange;
    leds2[63] = CRGB::Orange;
   

}

for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    leds3[index3[i]] = CRGB::Maroon; 
      
}
for(int i=0; i < sizeof(index5)/sizeof(index5[0]); i++){
    leds3[index5[i]] = CRGB::Orange; 
      
}


for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    leds4[index4[i]] = CRGB::Maroon;
        
}
for(int i=0; i < sizeof(index6)/sizeof(index6[0]); i++){
    leds4[index6[i]] = CRGB::Orange;
        
}
FastLED.show();

}

void fireFrame3(){
  int index1[] = {31,38,39,43,45,46,47,51,52,53,54,59,61};
  int index2[] = {30,39,46,47,51,52,53,54,57,58,59,60};
  int index3[] = {19, 20, 21, 22, 26, 27, 28, 29, 30, 31, 33, 34, 35, 39, 41, 42, 49, 50, 57, 58};
  int index5[] = {36, 37, 38, 43, 44, 45, 46, 47,  51, 52, 53, 54, 55, 59, 60, 61, 62, 63};
  int index4[] = {11, 12, 13, 14, 15, 19, 20, 21, 22, 23, 26, 27, 28, 34, 35, 42, 43, 50, 51, 59, 60};
  int index6[] = {29, 30, 31, 36, 37, 38, 39, 44, 45, 46, 47, 52, 53, 54, 55, 61, 62, 63};
   
for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    leds1[index1[i]] = CRGB::Maroon; 
    leds1[55] = CRGB::Orange;
    leds1[62] = CRGB::Orange;
    leds1[63] = CRGB::Orange;
    

}


for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    leds2[index2[i]] = CRGB::Maroon; 
    leds2[55] = CRGB::Orange;
    leds2[61] = CRGB::Orange;
    leds2[62] = CRGB::Orange;
    leds2[63] = CRGB::Orange;
   

}

for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    leds3[index3[i]] = CRGB::Maroon; 
      
}
for(int i=0; i < sizeof(index5)/sizeof(index5[0]); i++){
    leds3[index5[i]] = CRGB::Orange; 
      
}


for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    leds4[index4[i]] = CRGB::Maroon;
        
}
for(int i=0; i < sizeof(index6)/sizeof(index6[0]); i++){
    leds4[index6[i]] = CRGB::Orange;
        
}
FastLED.show();

}












//emoji
//monday blue
void Monday(){

  int index1[] = {4,5,6,7,11,18,25,32,34,35,36,37,38,40,48,56};
  int index2[] = {4,5,6,7,11,18,20,25,28,32,36,40,44,48,52,56};
  int index3[] = {6,7,13,20,27,32,34,37,40,42,46,48,50,54,56,58,62};
  int index4[] = {20,21,22,23,27,34,41,44,48,53,54,55,56};
  
for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    leds1[index1[i]] = CRGB::DodgerBlue; 

}

for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    leds2[index2[i]] = CRGB::DodgerBlue; 

}

for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    leds3[index3[i]] = CRGB::DodgerBlue; 
    leds3[40] = CRGB::Maroon;
    leds3[48] = CRGB::Maroon;
    leds3[56] = CRGB::Maroon;
    leds3[32] = CRGB::ForestGreen;



}
for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    leds4[index4[i]] = CRGB::DodgerBlue; 
    leds4[5] = CRGB::Maroon;
    leds4[6] = CRGB::Maroon;
    leds4[7] = CRGB::Maroon;
}

    FastLED.show();

leds1[44] = CRGB:: DodgerBlue;
leds2[37] = CRGB:: DodgerBlue;
    FastLED.show();

delay(500);
leds1[52] = CRGB:: DodgerBlue;
leds2[38] = CRGB:: DodgerBlue;
    FastLED.show();

delay(500);
leds1[60] = CRGB:: DodgerBlue;
leds2[39] = CRGB:: DodgerBlue;
    FastLED.show();
delay(500);


leds1[44] = CRGB:: Black;
leds2[37] = CRGB:: Black;
leds1[52] = CRGB:: Black;
leds2[38] = CRGB:: Black;
leds1[60] = CRGB:: Black;
leds2[39] = CRGB:: Black;

FastLED.show();

}


void Tuesday(){

  int index1[] = {4,5,6,7,11,18,25,32,35,38,40,44,45,48,56};
  int index2[] = {4,5,6,7,11,18,25,28,32,37,40,45,48,52,56};
  int index3[] = {6,7,13,20,27,34,42,50,54,58,62,48,56};
  int index4[] = {5,6,7,20,21,22,23,27,34,41,48,54,55,56};
  
for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    leds1[index1[i]] = CRGB::Crimson; 

}

for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    leds2[index2[i]] = CRGB::Crimson; 

}

for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    leds3[index3[i]] = CRGB::Crimson; 
    leds3[48] = CRGB::Maroon;
    leds3[56] = CRGB::Maroon;
    leds3[32] = CRGB::ForestGreen;//ForestGreen
    leds3[40] = CRGB::ForestGreen;//ForestGreen


}
for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    leds4[index4[i]] = CRGB::Crimson; 
    leds4[5] = CRGB::Maroon;
    leds4[6] = CRGB::Maroon;
    leds4[7] = CRGB::Maroon;
}

    FastLED.show();



delay(500);
leds4[53] = CRGB:: Crimson;
leds3[46] = CRGB:: Crimson;
    FastLED.show();

delay(500);
leds3[37] = CRGB:: Crimson;
leds4[44] = CRGB:: Crimson;
    FastLED.show();
delay(500);


leds3[37] = CRGB:: Black;
leds4[53] = CRGB:: Black;
leds3[46] = CRGB:: Black;
leds4[44] = CRGB:: Black;


FastLED.show();

}



void Wednesday(){

  int index1[] = {4,5,6,7,11,18,25,32,36,37,40,44,45,48,56};
  int index2[] = {4,5,6,7,11,18,25,32,36,37,40,44,45,48,56};
  int index3[] = {6,7,13,20,27,34,42,50,58,54,61,63};//54,61,63 & 46,47,53
  int index4[] = {20,21,22,23,27,34,41,48,56,47,54,63};//47,54,63 & 46,47,53,61
  
for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    leds1[index1[i]] = CRGB::RoyalBlue; 

}

for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    leds2[index2[i]] = CRGB::RoyalBlue; 

}

for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    leds3[index3[i]] = CRGB::RoyalBlue; 
    leds3[32] = CRGB::ForestGreen;//ForestGreen
    leds3[40] = CRGB::ForestGreen;//ForestGreen
    leds3[48] = CRGB::ForestGreen;//ForestGreen
    leds3[56] = CRGB::Maroon;



}
for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    leds4[index4[i]] = CRGB::RoyalBlue; 
    leds4[5] = CRGB::Maroon;
    leds4[6] = CRGB::Maroon;
    leds4[7] = CRGB::Maroon;
}

    FastLED.show();



delay(500);
leds3[54] = CRGB:: Black;
leds3[63] = CRGB:: Black;
leds4[54] = CRGB:: Black;
leds4[63] = CRGB:: Black;

leds1[62] = CRGB:: RoyalBlue;
leds1[63] = CRGB:: RoyalBlue;
leds2[63] = CRGB:: RoyalBlue;
leds2[55] = CRGB:: RoyalBlue;
leds3[46] = CRGB:: RoyalBlue;
leds3[47] = CRGB:: RoyalBlue;
leds3[53] = CRGB:: RoyalBlue;
leds4[46] = CRGB:: RoyalBlue;
leds4[53] = CRGB:: RoyalBlue;
leds4[61] = CRGB:: RoyalBlue;

    FastLED.show();

delay(500);
leds3[54] = CRGB:: RoyalBlue;
leds3[61] = CRGB:: RoyalBlue;
leds3[63] = CRGB:: RoyalBlue;
leds4[54] = CRGB:: RoyalBlue;
leds4[63] = CRGB:: RoyalBlue;

leds1[62] = CRGB:: Black;
leds1[63] = CRGB:: Black;
leds2[63] = CRGB:: Black;
leds2[55] = CRGB:: Black;
leds3[46] = CRGB:: Black;
leds3[47] = CRGB:: Black;
leds3[53] = CRGB:: Black;
leds4[46] = CRGB:: Black;
leds4[53] = CRGB:: Black;
leds4[61] = CRGB:: Black;

    FastLED.show();


}

void Thursday(){

  int index1[] = {4,5,6,7,11,18,25,32,35,36,37,38,40,43,44,45,46,48,56};
  int index2[] = {4,5,6,7,11,18,25,28,29,32,36,37,40,44,45,48,52,53,56};
  int index3[] = {6,7,13,20,27,34,42,50,54,58,62};//46,38
  int index4[] = {20,21,22,23,27,34,41,48,54,55,56};//53,52
  
for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    leds1[index1[i]] = CRGB::MediumVioletRed; 

}

for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    leds2[index2[i]] = CRGB::MediumVioletRed; 

}

for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    leds3[index3[i]] = CRGB::MediumVioletRed; 
    leds3[32] = CRGB::ForestGreen;
    leds3[40] = CRGB::ForestGreen;
    leds3[48] = CRGB::ForestGreen;
    leds3[56] = CRGB::ForestGreen;


}
for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    leds4[index4[i]] = CRGB::MediumVioletRed; 
    leds4[5] = CRGB::Maroon;
    leds4[6] = CRGB::Maroon;
    leds4[7] = CRGB::Maroon;
}

    FastLED.show();



delay(500);
leds3[46] = CRGB:: MediumVioletRed;
leds4[53] = CRGB:: MediumVioletRed;
    FastLED.show();

delay(500);
leds3[38] = CRGB:: MediumVioletRed;
leds4[52] = CRGB:: MediumVioletRed;
    FastLED.show();
    
delay(500);


leds3[46] = CRGB:: Black;
leds4[53] = CRGB:: Black;
leds3[38] = CRGB:: Black;
leds4[52] = CRGB:: Black;


FastLED.show();

}


void Friday(){

leds1[42] = CRGB:: Black;
leds1[43] = CRGB:: Black;
leds1[44] = CRGB:: Black;
leds1[45] = CRGB:: Black;
leds1[46] = CRGB:: Black;

FastLED.show();

  int index1[] = {4,5,6,7,11,18,25,32,35,36,37,40,42,46,48,56};
  int index2[] = {4,5,6,7,11,18,21,25,28,32,36,40,44,48,53,56};
  int index3[] = {6,7,13,20,27,31,34,38,42,45,50,53,58,61};
  int index4[] = {20,21,22,23,27,34,41,45,46,47,48,52,56,59};

  
  
for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    leds1[index1[i]] = CRGB::Gold; 

}

for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    leds2[index2[i]] = CRGB::Gold; 

}

for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    leds3[index3[i]] = CRGB::Gold; 
    leds3[32] = CRGB::ForestGreen;
    leds3[40] = CRGB::ForestGreen;
    leds3[48] = CRGB::ForestGreen;
    leds3[56] = CRGB::ForestGreen;



}
for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    leds4[index4[i]] = CRGB::Gold; 
    leds4[5] = CRGB::Maroon;
    leds4[6] = CRGB::Maroon;
    leds4[7] = CRGB::ForestGreen;
}

FastLED.show();

delay(500);
leds1[35] = CRGB:: Black;
leds1[36] = CRGB:: Black;
leds1[37] = CRGB:: Black;
leds1[42] = CRGB:: Black;
leds1[46] = CRGB:: Black;
leds1[42] = CRGB:: Gold; 
leds1[43] = CRGB:: Gold; 
leds1[44] = CRGB:: Gold; 
leds1[45] = CRGB:: Gold; 
leds1[46] = CRGB:: Gold; 


FastLED.show();



}

void Saturday(){
leds1[28] = CRGB:: Black;
leds1[29] = CRGB:: Black;
leds1[35] = CRGB:: Black;
leds1[38] = CRGB:: Black;
leds2[28] = CRGB:: Black;
leds2[35] = CRGB:: Black;
leds2[43] = CRGB:: Black;
leds2[52] = CRGB:: Black;
leds3[31] = CRGB:: Black;
leds3[39] = CRGB:: Black;
leds3[47] = CRGB:: Black;
leds3[55] = CRGB:: Black;
leds3[63] = CRGB:: Black;
leds4[59] = CRGB:: Black;
leds4[60] = CRGB:: Black;
leds4[61] = CRGB:: Black;
leds4[62] = CRGB:: Black;
leds4[63] = CRGB:: Black;

FastLED.show();

  int index1[] = {4,5,6,7,11,18,25,32,36,37,40,44,45,48,56};
  int index2[] = {4,5,6,7,11,18,25,32,36,37,40,44,45,48,56};
  int index3[] = {6,7,13,20,27,34,38,42,45,46,50,52,54,58,60,62};
  int index4[] = {20,21,22,23,27,34,38,39,41,45,48,52,53,54,55,56};
  
for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    leds1[index1[i]] = CRGB::LightSalmon; 

}

for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    leds2[index2[i]] = CRGB::LightSalmon; 

}

for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    leds3[index3[i]] = CRGB::LightSalmon; 
    leds3[32] = CRGB::Green;
    leds3[40] = CRGB::Green;
    leds3[48] = CRGB::Green;
    leds3[56] = CRGB::Green;



}
for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    leds4[index4[i]] = CRGB::LightSalmon; 
    leds4[5] = CRGB::Red;
    leds4[6] = CRGB::Green;
    leds4[7] = CRGB::Green;
}

FastLED.show();



delay(500);
leds1[36] = CRGB:: Black;
leds1[37] = CRGB:: Black;
leds1[44] = CRGB:: Black;
leds1[45] = CRGB:: Black;
leds1[28] = CRGB:: LightSalmon;
leds1[29] = CRGB:: LightSalmon;
leds1[35] = CRGB:: LightSalmon;
leds1[38] = CRGB:: LightSalmon;
leds2[36] = CRGB:: Black;
leds2[37] = CRGB:: Black;
leds2[44] = CRGB:: Black;
leds2[45] = CRGB:: Black;
leds2[28] = CRGB:: LightSalmon;
leds2[35] = CRGB:: LightSalmon;
leds2[43] = CRGB:: LightSalmon;
leds2[52] = CRGB:: LightSalmon;
leds3[46] = CRGB:: Black;
leds3[54] = CRGB:: Black;
leds3[62] = CRGB:: Black;
leds3[31] = CRGB:: LightSalmon;
leds3[39] = CRGB:: LightSalmon;
leds3[47] = CRGB:: LightSalmon;
leds3[55] = CRGB:: LightSalmon;
leds3[63] = CRGB:: LightSalmon;
leds4[53] = CRGB:: Black;
leds4[54] = CRGB:: Black;
leds4[55] = CRGB:: Black;
leds4[59] = CRGB:: LightSalmon;
leds4[60] = CRGB:: LightSalmon;
leds4[61] = CRGB:: LightSalmon;
leds4[62] = CRGB:: LightSalmon;
leds4[63] = CRGB:: LightSalmon;



FastLED.show();



}



 


void Sunday(){

  
leds1[28] = CRGB:: Black;
leds1[53] = CRGB:: Black;
leds1[60] = CRGB:: Black;

leds2[35] = CRGB:: Black;
leds2[39] = CRGB:: Black;
leds2[46] = CRGB:: Black;

FastLED.show();

  int index1[] = {4,5,6,7,11,18,25,32,37,38,40,45,46,48,56};
  int index2[] = {4,5,6,7,11,18,25,32,40,44,45,48,52,53,56};
  int index3[] = {6,7,13,20,27,34,38,42,45,50,54,58,61};
  int index4[] = {20,21,22,23,27,34,41,44,46,48,51,53,55,56};
  
for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    leds1[index1[i]] = CRGB::Indigo; 

}

for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    leds2[index2[i]] = CRGB::Indigo; 

}

for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    leds3[index3[i]] = CRGB::Indigo; 
    leds3[32] = CRGB::ForestGreen;
    leds3[40] = CRGB::ForestGreen;
    leds3[48] = CRGB::ForestGreen;
    leds3[56] = CRGB::ForestGreen;



}
for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    leds4[index4[i]] = CRGB::Indigo; 
    leds4[5] = CRGB::ForestGreen;
    leds4[6] = CRGB::ForestGreen;
    leds4[7] = CRGB::ForestGreen;
}

    FastLED.show();



delay(500);
leds1[28] = CRGB:: Indigo;
leds1[53] = CRGB:: Indigo;
leds1[60] = CRGB:: Indigo;
leds1[38] = CRGB:: Black;
leds1[45] = CRGB:: Black;
leds2[35] = CRGB:: Indigo;
leds2[39] = CRGB:: Indigo;
leds2[46] = CRGB:: Indigo;
leds2[45] = CRGB:: Black;
leds2[52] = CRGB:: Black;
    FastLED.show();



}





//number

void Twenty2(){

  int index1[] = {34,35,36,37,41,46,54,61};
  int index2[] = {21,22,28,31,36,44,52,61};
  int index3[] = {12,20,21,28,30,36,39,44,52};
  int index4[] = {34,35,36,37,38,39,46,53,60};
  
for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    leds1[index1[i]] = CRGB::DodgerBlue; 
    FastLED.show();
    delay(10);
}

for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    leds3[index3[i]] = CRGB::DodgerBlue; 
    FastLED.show();
    delay(10);
}

for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    leds2[index2[i]] = CRGB::DodgerBlue; 
    FastLED.show();
    delay(10);
    }


for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    leds4[index4[i]] = CRGB::DodgerBlue;
    FastLED.show();
    delay(10);
  }

}


void Twenty3(){

  int index1[] = {34,35,36,37,41,46,54,61};
  int index2[] = {21,22,28,31,36,39,44,47,52,55,61};
  int index3[] = {12,20,21,28,30,36,39,44,52};
  int index4[] = {35,36,37,38,42,47,50,58};
  
for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    leds1[index1[i]] = CRGB::DodgerBlue; 
    FastLED.show();
    delay(10);
}

for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    leds3[index3[i]] = CRGB::DodgerBlue; 
    FastLED.show();
    delay(10);
}

for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    leds2[index2[i]] = CRGB::DodgerBlue; 
    FastLED.show();
    delay(10);
    }


for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    leds4[index4[i]] = CRGB::DodgerBlue;
    FastLED.show();
    delay(10);
  }

}


void Twenty4(){

  int index1[] = {34,35,36,37,41,46,54,61};
  int index2[] = {28,29,30,31,60,61,62,63};
  int index3[] = {12,20,21,28,30,36,39,44,52};
  int index4[] = {35,43,51,57,58,59,60,61,62,63};
  
for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    leds1[index1[i]] = CRGB::DodgerBlue; 
    FastLED.show();
    delay(10);
}

for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    leds3[index3[i]] = CRGB::DodgerBlue; 
    FastLED.show();
    delay(10);
}

for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    leds2[index2[i]] = CRGB::DodgerBlue; 
    FastLED.show();
    delay(10);
    }


for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    leds4[index4[i]] = CRGB::DodgerBlue;
    FastLED.show();
    delay(10);
  }

}

void Twenty7(){
  int index1[] = {35,36,37,38,42,47,55,62};
  int index2[] = {21,22,23,28,36,44,52,53};
  int index3[] = {20,28,29,36,38,44,47,52,60};
  int index4[] = {34,42,50,58};
  
for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    leds1[index1[i]] = CRGB::Maroon; 
    FastLED.show();
    delay(10);
}

for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    leds3[index3[i]] = CRGB::Maroon; 
    FastLED.show();
    delay(10);
}

for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    leds2[index2[i]] = CRGB::Maroon; 
    FastLED.show();
    delay(10);
    }


for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    leds4[index4[i]] = CRGB::Maroon;
    FastLED.show();
    delay(10);
  }

}

void Twenty8(){
  int index1[] = {34,35,36,37,41,46,54,61};
  int index2[] = {21,22,28,31,36,39,44,47,52,55,61,62};
  int index3[] = {12,20,21,28,30,36,39,44,52};
  int index4[] = {35,36,37,38,42,47,50,55,59,62};
  
for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    leds1[index1[i]] = CRGB::Maroon; 
    FastLED.show();
    delay(10);
}

for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    leds3[index3[i]] = CRGB::Maroon; 
    FastLED.show();
    delay(10);
}

for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    leds2[index2[i]] = CRGB::Maroon; 
    FastLED.show();
    delay(10);
    }


for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    leds4[index4[i]] = CRGB::Maroon;
    FastLED.show();
    delay(10);
  }

}

    
void Twenty9(){
  int index1[] = {34,35,36,37,41,46,54,61};
  int index2[] = {21,22,23,28,36,44,53,54,55};
  int index3[] = {12,20,21,28,30,36,39,44,52};
  int index4[] = {35,36,37,38,42,50,58,59,60,61};
  
for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    leds1[index1[i]] = CRGB::Maroon; 
    FastLED.show();
    delay(10);
}

for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    leds3[index3[i]] = CRGB::Maroon; 
    FastLED.show();
    delay(10);
}

for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    leds2[index2[i]] = CRGB::Maroon; 
    FastLED.show();
    delay(10);
    }


for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    leds4[index4[i]] = CRGB::Maroon;
    FastLED.show();
    delay(10);
  }

}


void Thirty0(){

  int index1[] = {34,35,36,37,41,46,54,58,59,60,61};
  int index2[] = {21,22,23,28,36,44,52,61,62,63};
  int index3[] = {13,20,28,36,44,47,53,54};
  int index4[] = {35,36,37,38,42,47,50,55,58,63};
  
for(int i=0; i < sizeof(index1)/sizeof(index1[0]); i++){
    leds1[index1[i]] = CRGB::Maroon; 
    FastLED.show();
    delay(10);
}

for(int i=0; i < sizeof(index3)/sizeof(index3[0]); i++){
    leds3[index3[i]] = CRGB::Maroon; 
    FastLED.show();
    delay(10);
}

for(int i=0; i < sizeof(index2)/sizeof(index2[0]); i++){
    leds2[index2[i]] = CRGB::Maroon; 
    FastLED.show();
    delay(10);
    }


for(int i=0; i < sizeof(index4)/sizeof(index4[0]); i++){
    leds4[index4[i]] = CRGB::Maroon;
    FastLED.show();
    delay(10);
  }

}



void time(int hr, int min){

  
   //for hours
    if (hr==1 || hr==13) {
    for(int i = 2; i<=13; i++){
      if(i ==2){
          digitalWrite(i, LOW);
      }else{
          digitalWrite(i, HIGH);
      }
    }
  } else if (hr==2 || hr==14) {
    for(int i = 2; i<=13; i++){
      if(i ==3){
          digitalWrite(i, LOW);
      }else{
          digitalWrite(i, HIGH);
      }
    }
  } else if (hr==3 || hr==15) {
    for(int i = 2; i<=13; i++){
      if(i ==4){
          digitalWrite(i, LOW);
      }else{
          digitalWrite(i, HIGH);
      }
    }
  } else if (hr==4|| hr==16) {
    for(int i = 2; i<=13; i++){
      if(i ==5){
          digitalWrite(i, LOW);
      }else{
          digitalWrite(i, HIGH);
      }
    }
  } else if (hr==5 || hr==17) {
    for(int i = 2; i<=13; i++){
      if(i ==6){
          digitalWrite(i, LOW);
      }else{
          digitalWrite(i, HIGH);
      }
    }
  } else if (hr==6 || hr==18) {
    for(int i = 2; i<=13; i++){
      if(i ==7){
          digitalWrite(i, LOW);
      }else{
          digitalWrite(i, HIGH);
      }
    }
  } else if (hr==7 || hr==19) {
    for(int i = 2; i<=13; i++){
      if(i ==8){
          digitalWrite(i, LOW);
      }else{
          digitalWrite(i, HIGH);
      }
    }
  } else if (hr==8 || hr==20) {
    for(int i = 2; i<=13; i++){
      if(i ==9){
          digitalWrite(i, LOW);
      }else{
          digitalWrite(i, HIGH);
      }
    }
  } else if (hr==9 || hr==21) {
   for(int i = 2; i<=13; i++){
      if(i ==10){
          digitalWrite(i, LOW);
      }else{
          digitalWrite(i, HIGH);
      }
    }
    digitalWrite(44, HIGH); 
  } else if (hr==10 || hr==22) {
    for(int i = 2; i<=13; i++){
      if(i == 11){
          digitalWrite(i, LOW);
      }else{
          digitalWrite(i, HIGH);
      }
    }
  } else if (hr==11 || hr==23) {
    for(int i = 2; i<=13; i++){
      if(i ==12){
          digitalWrite(i, LOW);
      }else{
          digitalWrite(i, HIGH);
      }
    }
  } else if (hr==12 || hr==24) {
    for(int i = 2; i<=13; i++){
      if(i ==13){
          digitalWrite(i, LOW);
      }else{
          digitalWrite(i, HIGH);
      }
    }
  }

  
  
  
/*
pin 22  23  24 DMUX1
    A2 A1 A0
pin 25  26  27 DMUX2
    A2 A1 A0
pin 28  29  30 DMUX3
    A2 A1 A0
pin 31 32 33 DMUX4
    A2 A1 A0
pin 34 35 36 DMUX5
    A2 A1 A0
pin 37 38 39 DMUX6
    A2 A1 A0
pin 40 41 42 DMUX7
    A2 A1 A0
pin 43 44 45 DMUX8
    A2 A1 A0
pin 46 47 48 DMUX9
    A2 A1 A0
*/
  // for min
  
    if (min==0) {
    for(int i=22; i<=24; i++){
      digitalWrite( i, LOW);
    }
    
    for(int i =25; i<=48; i++){
      digitalWrite( i, HIGH);
    }
    
  }
  if (min==1) {
    for(int i=22; i<=27; i++){
      digitalWrite( i, LOW);
    }
    for(int i =28; i<=48; i++){
      digitalWrite( i, HIGH);
    }
    
  }
  if (min==2) {
    for(int i=22; i<=30; i++){
      digitalWrite( i, LOW);
    }
     for(int i=31; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==3) {
    for(int i=22; i<=33; i++){
      digitalWrite( i, LOW);
    }
     for(int i=34; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==4) {
    for(int i=22; i<=36; i++){
      digitalWrite( i, LOW);
    }
     for(int i=37; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==5) {
    for(int i=22; i<=39; i++){
      digitalWrite( i, LOW);
    }
     for(int i=40; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==6) {
    for(int i=22; i<=42; i++){
      digitalWrite( i, LOW);
    }
    for(int i=43; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==7) {
    for(int i=22; i<=45; i++){
      digitalWrite( i, LOW);
    }
    for(int i=46; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==8) {
    for(int i=22; i<=33; i++){
      digitalWrite( i, HIGH);
    }
    for(int i=34; i<=48; i++){
      digitalWrite( i, LOW);
    }
  }
  if (min==9) {
    digitalWrite( 22, LOW);
    digitalWrite( 23, LOW);
    for(int i=24; i<=36; i++){
      digitalWrite( i, HIGH);
    }
    for(int i=37; i<=48; i++){
      digitalWrite( i, LOW);
    }
  }
  if (min==10) {
    digitalWrite( 22, LOW);
    digitalWrite( 23, LOW);
    digitalWrite( 24, HIGH);
    digitalWrite( 25, LOW);
    digitalWrite( 26, LOW);
    for(int i=27; i<=39; i++){
      digitalWrite( i, HIGH);
    }
    for(int i=40; i<=48; i++){
      digitalWrite( i, LOW);
    }
  }
  if (min==11) {
    digitalWrite( 22, LOW);
    digitalWrite( 23, LOW);
    digitalWrite( 24, HIGH);
    digitalWrite( 25, LOW);
    digitalWrite( 26, LOW);
    digitalWrite( 27, HIGH);
    digitalWrite( 28, LOW);
    digitalWrite( 29, LOW);
    for(int i=30; i<=42; i++){
      digitalWrite( i, HIGH);
    }
    for(int i=43; i<=48; i++){
      digitalWrite( i, LOW);
    }
  }
  if (min==12) {
    digitalWrite( 22, LOW);
    digitalWrite( 23, LOW);
    digitalWrite( 24, HIGH);
    digitalWrite( 25, LOW);
    digitalWrite( 26, LOW);
    digitalWrite( 27, HIGH);
    digitalWrite( 28, LOW);
    digitalWrite( 29, LOW);
    digitalWrite( 30, HIGH);
    digitalWrite( 31, LOW);
    digitalWrite( 32, LOW);
    for(int i=33; i<=45; i++){
      digitalWrite( i, HIGH);
    }
    for(int i=46; i<=48; i++){
      digitalWrite( i, LOW);
    }
  }
  if (min==13) {
    digitalWrite( 22, LOW);
    digitalWrite( 23, LOW);
    digitalWrite( 24, HIGH);
    digitalWrite( 25, LOW);
    digitalWrite( 26, LOW);
    digitalWrite( 27, HIGH);
    digitalWrite( 28, LOW);
    digitalWrite( 29, LOW);
    digitalWrite( 30, HIGH);
    digitalWrite( 31, LOW);
    digitalWrite( 32, LOW);
    digitalWrite( 33, HIGH);
    digitalWrite( 34, LOW);
    digitalWrite( 35, LOW); 
    for(int i=36; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==14) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, HIGH);
    digitalWrite( 24, HIGH);
    digitalWrite( 25, LOW);
    digitalWrite( 26, LOW);
    digitalWrite( 27, HIGH);
    digitalWrite( 28, LOW);
    digitalWrite( 29, LOW);
    digitalWrite( 30, HIGH);
    digitalWrite( 31, LOW);
    digitalWrite( 32, LOW);
    digitalWrite( 33, HIGH);
    digitalWrite( 34, LOW);
    digitalWrite( 35, LOW); 
    digitalWrite( 36, HIGH);
    digitalWrite( 37, LOW);
    digitalWrite( 38, LOW);
    for(int i=39; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==15) {
    for(int i=22; i<=27; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 28, LOW);
    digitalWrite( 29, LOW);
    digitalWrite( 30, HIGH);
    digitalWrite( 31, LOW);
    digitalWrite( 32, LOW);
    digitalWrite( 33, HIGH);
    digitalWrite( 34, LOW);
    digitalWrite( 35, LOW); 
    digitalWrite( 36, HIGH);
    digitalWrite( 37, LOW);
    digitalWrite( 38, LOW);
    digitalWrite( 39, HIGH);
    digitalWrite( 40, LOW);
    digitalWrite( 41, LOW);
    for(int i=42; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==16) {
    for(int i=22; i<=30; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 31, LOW);
    digitalWrite( 32, LOW);
    digitalWrite( 33, HIGH);
    digitalWrite( 34, LOW);
    digitalWrite( 35, LOW); 
    digitalWrite( 36, HIGH);
    digitalWrite( 37, LOW);
    digitalWrite( 38, LOW);
    digitalWrite( 39, HIGH);
    digitalWrite( 40, LOW);
    digitalWrite( 41, LOW);
    digitalWrite( 42, HIGH);
    digitalWrite( 43, LOW);
    digitalWrite( 44, LOW);
    for(int i=45; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==17) {
    for(int i=22; i<=33; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 34, LOW);
    digitalWrite( 35, LOW); 
    digitalWrite( 36, HIGH);
    digitalWrite( 37, LOW);
    digitalWrite( 38, LOW);
    digitalWrite( 39, HIGH);
    digitalWrite( 40, LOW);
    digitalWrite( 41, LOW);
    digitalWrite( 42, HIGH);
    digitalWrite( 43, LOW);
    digitalWrite( 44, LOW);
    digitalWrite( 45, HIGH);
    digitalWrite( 46, LOW);
    digitalWrite( 47, LOW);
    digitalWrite( 48, HIGH);
  }
  if (min==18) {
    digitalWrite( 22, LOW);
    digitalWrite( 23, HIGH);
    digitalWrite( 24, LOW);
    for(int i=25; i<=36; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 37, LOW);
    digitalWrite( 38, LOW);
    digitalWrite( 39, HIGH);
    digitalWrite( 40, LOW);
    digitalWrite( 41, LOW);
    digitalWrite( 42, HIGH);
    digitalWrite( 43, LOW);
    digitalWrite( 44, LOW);
    digitalWrite( 45, HIGH);
    digitalWrite( 46, LOW);
    digitalWrite( 47, LOW);
    digitalWrite( 48, HIGH);
  }
  if (min==19) {
    digitalWrite( 22, LOW);
    digitalWrite( 23, HIGH);
    digitalWrite( 24, LOW);
    digitalWrite( 25, LOW);
    digitalWrite( 26, HIGH);
    digitalWrite( 27, LOW);
    for(int i=28; i<=39; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 40, LOW);
    digitalWrite( 41, LOW);
    digitalWrite( 42, HIGH);
    digitalWrite( 43, LOW);
    digitalWrite( 44, LOW);
    digitalWrite( 45, HIGH);
    digitalWrite( 46, LOW);
    digitalWrite( 47, LOW);
    digitalWrite( 48, HIGH);
  }
  if (min==20) {
    digitalWrite( 22, LOW);
    digitalWrite( 23, HIGH);
    digitalWrite( 24, LOW);
    digitalWrite( 25, LOW);
    digitalWrite( 26, HIGH);
    digitalWrite( 27, LOW);
    digitalWrite( 28, LOW);
    digitalWrite( 29, HIGH);
    digitalWrite( 30, LOW);
    for(int i=31; i<=42; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 43, LOW);
    digitalWrite( 44, LOW);
    digitalWrite( 45, HIGH);
    digitalWrite( 46, LOW);
    digitalWrite( 47, LOW);
    digitalWrite( 48, HIGH);
  }
  if (min==21) {
    digitalWrite( 22, LOW);
    digitalWrite( 23, HIGH);
    digitalWrite( 24, LOW);
    digitalWrite( 25, LOW);
    digitalWrite( 26, HIGH);
    digitalWrite( 27, LOW);
    digitalWrite( 28, LOW);
    digitalWrite( 29, HIGH);
    digitalWrite( 30, LOW);
    digitalWrite( 31, LOW);
    digitalWrite( 32, HIGH);
    digitalWrite( 33, LOW);
    for(int i=34; i<=45; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 46, LOW);
    digitalWrite( 47, LOW);
    digitalWrite( 48, HIGH);
  }
  if (min==22) {
    digitalWrite( 22, LOW);
    digitalWrite( 23, HIGH);
    digitalWrite( 24, LOW);
    digitalWrite( 25, LOW);
    digitalWrite( 26, HIGH);
    digitalWrite( 27, LOW);
    digitalWrite( 28, LOW);
    digitalWrite( 29, HIGH);
    digitalWrite( 30, LOW);
    digitalWrite( 31, LOW);
    digitalWrite( 32, HIGH);
    digitalWrite( 33, LOW);
    digitalWrite( 34, LOW);
    digitalWrite( 35, HIGH); 
    digitalWrite( 36, LOW);
    for(int i=37; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==23) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, HIGH);
    digitalWrite( 24, HIGH);
    digitalWrite( 25, LOW);
    digitalWrite( 26, HIGH);
    digitalWrite( 27, LOW);
    digitalWrite( 28, LOW);
    digitalWrite( 29, HIGH);
    digitalWrite( 30, LOW);
    digitalWrite( 31, LOW);
    digitalWrite( 32, HIGH);
    digitalWrite( 33, LOW);
    digitalWrite( 34, LOW);
    digitalWrite( 35, HIGH); 
    digitalWrite( 36, LOW);
    digitalWrite( 37, LOW);
    digitalWrite( 38, HIGH);
    digitalWrite( 39, LOW);
    for(int i=40; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==24) {
    for(int i=22; i<=27; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 28, LOW);
    digitalWrite( 29, HIGH);
    digitalWrite( 30, LOW);
    digitalWrite( 31, LOW);
    digitalWrite( 32, HIGH);
    digitalWrite( 33, LOW);
    digitalWrite( 34, LOW);
    digitalWrite( 35, HIGH); 
    digitalWrite( 36, LOW);
    digitalWrite( 37, LOW);
    digitalWrite( 38, HIGH);
    digitalWrite( 39, LOW);
    digitalWrite( 40, LOW);
    digitalWrite( 41, HIGH);
    digitalWrite( 42, LOW);
    for(int i=43; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==25) {
    for(int i=22; i<=30; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 31, LOW);
    digitalWrite( 32, HIGH);
    digitalWrite( 33, LOW);
    digitalWrite( 34, LOW);
    digitalWrite( 35, HIGH); 
    digitalWrite( 36, LOW);
    digitalWrite( 37, LOW);
    digitalWrite( 38, HIGH);
    digitalWrite( 39, LOW);
    digitalWrite( 40, LOW);
    digitalWrite( 41, HIGH);
    digitalWrite( 42, LOW);
    digitalWrite( 43, LOW);
    digitalWrite( 44, HIGH);
    digitalWrite( 45, LOW);
    digitalWrite( 46, HIGH);
    digitalWrite( 47, HIGH);
    digitalWrite( 48, HIGH);
  }
  if (min==26) {
    for(int i=22; i<=33; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 34, LOW);
    digitalWrite( 35, HIGH); 
    digitalWrite( 36, LOW);
    digitalWrite( 37, LOW);
    digitalWrite( 38, HIGH);
    digitalWrite( 39, LOW);
    digitalWrite( 40, LOW);
    digitalWrite( 41, HIGH);
    digitalWrite( 42, LOW);
    digitalWrite( 43, LOW);
    digitalWrite( 44, HIGH);
    digitalWrite( 45, LOW);
    digitalWrite( 46, LOW);
    digitalWrite( 47, HIGH);
    digitalWrite( 48, LOW);
  }
  if (min==27) {
    digitalWrite( 22, LOW);
    for(int i=23; i<=36; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 37, LOW);
    digitalWrite( 38, HIGH);
    digitalWrite( 39, LOW);
    digitalWrite( 40, LOW);
    digitalWrite( 41, HIGH);
    digitalWrite( 42, LOW);
    digitalWrite( 43, LOW);
    digitalWrite( 44, HIGH);
    digitalWrite( 45, LOW);
    digitalWrite( 46, LOW);
    digitalWrite( 47, HIGH);
    digitalWrite( 48, LOW);
  }
  if (min==28) {
    digitalWrite( 22, LOW);
    digitalWrite( 23, HIGH);
    digitalWrite( 24, HIGH);
    digitalWrite( 25, LOW);
    for(int i=26; i<=39; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 40, LOW);
    digitalWrite( 41, HIGH);
    digitalWrite( 42, LOW);
    digitalWrite( 43, LOW);
    digitalWrite( 44, HIGH);
    digitalWrite( 45, LOW);
    digitalWrite( 46, LOW);
    digitalWrite( 47, HIGH);
    digitalWrite( 48, LOW);
  }
  if (min==29) {
    digitalWrite( 22, LOW);
    digitalWrite( 23, HIGH);
    digitalWrite( 24, HIGH);
    digitalWrite( 25, LOW);
    digitalWrite( 26, HIGH);
    digitalWrite( 27, HIGH);
    digitalWrite( 28, LOW);
    for(int i=29; i<=42; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 43, LOW);
    digitalWrite( 44, HIGH);
    digitalWrite( 45, LOW);
    digitalWrite( 46, LOW);
    digitalWrite( 47, HIGH);
    digitalWrite( 48, LOW);
  }
  if (min==30) {
    digitalWrite( 22, LOW);
    digitalWrite( 23, HIGH);
    digitalWrite( 24, HIGH);
    digitalWrite( 25, LOW);
    digitalWrite( 26, HIGH);
    digitalWrite( 27, HIGH);
    digitalWrite( 28, LOW);
    digitalWrite( 29, HIGH);
    digitalWrite( 30, HIGH);
    digitalWrite( 31, LOW);
    for(int i=32; i<=45; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 46, LOW);
    digitalWrite( 47, HIGH);
    digitalWrite( 48, LOW);
  }
  if (min==31) {
    digitalWrite( 22, LOW);
    digitalWrite( 23, HIGH);
    digitalWrite( 24, HIGH);
    digitalWrite( 25, LOW);
    digitalWrite( 26, HIGH);
    digitalWrite( 27, HIGH);
    digitalWrite( 28, LOW);
    digitalWrite( 29, HIGH);
    digitalWrite( 30, HIGH);
    digitalWrite( 31, LOW);
    digitalWrite( 32, HIGH);
    digitalWrite( 33, HIGH);
    digitalWrite( 34, LOW);
    for(int i=35; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==32) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, HIGH);
    digitalWrite( 24, HIGH);
    digitalWrite( 25, LOW);
    digitalWrite( 26, HIGH);
    digitalWrite( 27, HIGH);
    digitalWrite( 28, LOW);
    digitalWrite( 29, HIGH);
    digitalWrite( 30, HIGH);
    digitalWrite( 31, LOW);
    digitalWrite( 32, HIGH);
    digitalWrite( 33, HIGH);
    digitalWrite( 34, LOW);
    digitalWrite( 35, HIGH); 
    digitalWrite( 36, HIGH);
    digitalWrite( 37, LOW);
    for(int i=38; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==33) {
    for(int i=22; i<=27; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 28, LOW);
    digitalWrite( 29, HIGH);
    digitalWrite( 30, HIGH);
    digitalWrite( 31, LOW);
    digitalWrite( 32, HIGH);
    digitalWrite( 33, HIGH);
    digitalWrite( 34, LOW);
    digitalWrite( 35, HIGH); 
    digitalWrite( 36, HIGH);
    digitalWrite( 37, LOW);
    digitalWrite( 38, HIGH);
    digitalWrite( 39, HIGH);
    digitalWrite( 40, LOW);
    for(int i=41; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
if (min==34) {
    for(int i=22; i<=30; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 31, LOW);
    digitalWrite( 32, HIGH);
    digitalWrite( 33, HIGH);
    digitalWrite( 34, LOW);
    digitalWrite( 35, HIGH); 
    digitalWrite( 36, HIGH);
    digitalWrite( 37, LOW);
    digitalWrite( 38, HIGH);
    digitalWrite( 39, HIGH);
    digitalWrite( 40, LOW);
    digitalWrite( 41, HIGH);
    digitalWrite( 42, HIGH);
    digitalWrite( 43, LOW);
    for(int i=44; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==35) {
    for(int i=22; i<=33; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 34, LOW);
    digitalWrite( 35, HIGH); 
    digitalWrite( 36, HIGH);
    digitalWrite( 37, LOW);
    digitalWrite( 38, HIGH);
    digitalWrite( 39, HIGH);
    digitalWrite( 40, LOW);
    digitalWrite( 41, HIGH);
    digitalWrite( 42, HIGH);
    digitalWrite( 43, LOW);
    digitalWrite( 44, HIGH);
    digitalWrite( 45, HIGH);
    digitalWrite( 46, LOW);
    digitalWrite( 47, HIGH);
    digitalWrite( 48, HIGH);
  }
  if (min==36) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, LOW);
    digitalWrite( 24, LOW);
    for(int i=25; i<=36; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 37, LOW);
    digitalWrite( 38, HIGH);
    digitalWrite( 39, HIGH);
    digitalWrite( 40, LOW);
    digitalWrite( 41, HIGH);
    digitalWrite( 42, HIGH);
    digitalWrite( 43, LOW);
    digitalWrite( 44, HIGH);
    digitalWrite( 45, HIGH);
    digitalWrite( 46, LOW);
    digitalWrite( 47, HIGH);
    digitalWrite( 48, HIGH);
  }
  if (min==37) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, LOW);
    digitalWrite( 24, LOW);
    digitalWrite( 25, HIGH);
    digitalWrite( 26, LOW);
    digitalWrite( 27, LOW);
    for(int i=28; i<=39; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 40, LOW);
    digitalWrite( 41, HIGH);
    digitalWrite( 42, HIGH);
    digitalWrite( 43, LOW);
    digitalWrite( 44, HIGH);
    digitalWrite( 45, HIGH);
    digitalWrite( 46, LOW);
    digitalWrite( 47, HIGH);
    digitalWrite( 48, HIGH);
  }
  if (min==38) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, LOW);
    digitalWrite( 24, LOW);
    digitalWrite( 25, HIGH);
    digitalWrite( 26, LOW);
    digitalWrite( 27, LOW);
    digitalWrite( 28, HIGH);
    digitalWrite( 29, LOW);
    digitalWrite( 30, LOW);
    for(int i=31; i<=42; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 43, LOW);
    digitalWrite( 44, HIGH);
    digitalWrite( 45, HIGH);
    digitalWrite( 46, LOW);
    digitalWrite( 47, HIGH);
    digitalWrite( 48, HIGH);
  }
  if (min==39) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, LOW);
    digitalWrite( 24, LOW);
    digitalWrite( 25, HIGH);
    digitalWrite( 26, LOW);
    digitalWrite( 27, LOW);
    digitalWrite( 28, HIGH);
    digitalWrite( 29, LOW);
    digitalWrite( 30, LOW);
    digitalWrite( 31, HIGH);
    digitalWrite( 32, LOW);
    digitalWrite( 33, LOW);
    for(int i=34; i<=45; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 46, LOW);
    digitalWrite( 47, HIGH);
    digitalWrite( 48, HIGH);
  }
  if (min==40) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, LOW);
    digitalWrite( 24, LOW);
    digitalWrite( 25, HIGH);
    digitalWrite( 26, LOW);
    digitalWrite( 27, LOW);
    digitalWrite( 28, HIGH);
    digitalWrite( 29, LOW);
    digitalWrite( 30, LOW);
    digitalWrite( 31, HIGH);
    digitalWrite( 32, LOW);
    digitalWrite( 33, LOW);
    digitalWrite( 34, HIGH);
    digitalWrite( 35, LOW); 
    digitalWrite( 36, LOW);
    for(int i=37; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==41) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, HIGH);
    digitalWrite( 24, HIGH);
    digitalWrite( 25, HIGH);
    digitalWrite( 26, LOW);
    digitalWrite( 27, LOW);
    digitalWrite( 28, HIGH);
    digitalWrite( 29, LOW);
    digitalWrite( 30, LOW);
    digitalWrite( 31, HIGH);
    digitalWrite( 32, LOW);
    digitalWrite( 33, LOW);
    digitalWrite( 34, HIGH);
    digitalWrite( 35, LOW); 
    digitalWrite( 36, LOW);
    digitalWrite( 37, HIGH);
    digitalWrite( 38, LOW);
    digitalWrite( 39, LOW);
    for(int i=40; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==42) {
    for(int i=22; i<=28; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 29, LOW);
    digitalWrite( 30, LOW);
    digitalWrite( 31, HIGH);
    digitalWrite( 32, LOW);
    digitalWrite( 33, LOW);
    digitalWrite( 34, HIGH);
    digitalWrite( 35, LOW); 
    digitalWrite( 36, LOW);
    digitalWrite( 37, HIGH);
    digitalWrite( 38, LOW);
    digitalWrite( 39, LOW);
    digitalWrite( 30, HIGH);
    digitalWrite( 41, LOW);
    digitalWrite( 42, LOW);
    for(int i=43; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==43) {
    for(int i=22; i<=31; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 32, LOW);
    digitalWrite( 33, LOW);
    digitalWrite( 34, HIGH);
    digitalWrite( 35, LOW); 
    digitalWrite( 36, LOW);
    digitalWrite( 37, HIGH);
    digitalWrite( 38, LOW);
    digitalWrite( 39, LOW);
    digitalWrite( 40, HIGH);
    digitalWrite( 41, LOW);
    digitalWrite( 42, LOW);
    digitalWrite( 43, HIGH);
    digitalWrite( 44, LOW);
    digitalWrite( 45, LOW);
    digitalWrite( 46, HIGH);
    digitalWrite( 47, HIGH);
    digitalWrite( 48, HIGH);
  }
  if (min==44) {
    for(int i=22; i<=34; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 35, LOW); 
    digitalWrite( 36, LOW);
    digitalWrite( 37, HIGH);
    digitalWrite( 38, LOW);
    digitalWrite( 39, LOW);
    digitalWrite( 40, HIGH);
    digitalWrite( 41, LOW);
    digitalWrite( 42, LOW);
    digitalWrite( 43, HIGH);
    digitalWrite( 44, LOW);
    digitalWrite( 45, LOW);
    digitalWrite( 46, HIGH);
    digitalWrite( 47, LOW);
    digitalWrite( 48, LOW);
  }
  if (min==45) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, LOW);
    for(int i=24; i<=37; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 38, LOW);
    digitalWrite( 39, LOW);
    digitalWrite( 40, HIGH);
    digitalWrite( 41, LOW);
    digitalWrite( 42, LOW);
    digitalWrite( 43, HIGH);
    digitalWrite( 44, LOW);
    digitalWrite( 45, LOW);
    digitalWrite( 46, HIGH);
    digitalWrite( 47, LOW);
    digitalWrite( 48, LOW);
  }
  if (min==46) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, LOW);
    digitalWrite( 24, HIGH);
    digitalWrite( 25, HIGH);
    digitalWrite( 26, LOW);
    for(int i=27; i<=40; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 41, LOW);
    digitalWrite( 42, LOW);
    digitalWrite( 43, HIGH);
    digitalWrite( 44, LOW);
    digitalWrite( 45, LOW);
    digitalWrite( 46, HIGH);
    digitalWrite( 47, LOW);
    digitalWrite( 48, LOW);
  }
  if (min==47) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, LOW);
    digitalWrite( 24, HIGH);
    digitalWrite( 25, HIGH);
    digitalWrite( 26, LOW);
    digitalWrite( 27, HIGH);
    digitalWrite( 28, HIGH);
    digitalWrite( 29, LOW);
    for(int i=30; i<=43; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 44, LOW);
    digitalWrite( 45, LOW);
    digitalWrite( 46, HIGH);
    digitalWrite( 47, LOW);
    digitalWrite( 48, LOW);
  }
  if (min==48) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, LOW);
    digitalWrite( 24, HIGH);
    digitalWrite( 25, HIGH);
    digitalWrite( 26, LOW);
    digitalWrite( 27, HIGH);
    digitalWrite( 28, HIGH);
    digitalWrite( 29, LOW);
    digitalWrite( 30, HIGH);
    digitalWrite( 31, HIGH);
    digitalWrite( 32, LOW);
    for(int i=33; i<=46; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 47, LOW);
    digitalWrite( 48, LOW);
  }
  if (min==49) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, LOW);
    digitalWrite( 24, HIGH);
    digitalWrite( 25, HIGH);
    digitalWrite( 26, LOW);
    digitalWrite( 27, HIGH);
    digitalWrite( 28, HIGH);
    digitalWrite( 29, LOW);
    digitalWrite( 30, HIGH);
    digitalWrite( 31, HIGH);
    digitalWrite( 32, LOW);
    digitalWrite( 33, HIGH);
    digitalWrite( 34, HIGH);
    digitalWrite( 35, LOW);
    for(int i=36; i<=48; i++){
      digitalWrite( i, HIGH);
    } 
  }
  if (min==50) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, HIGH);
    digitalWrite( 24, HIGH);
    digitalWrite( 25, HIGH);
    digitalWrite( 26, LOW);
    digitalWrite( 27, HIGH);
    digitalWrite( 28, HIGH);
    digitalWrite( 29, LOW);
    digitalWrite( 30, HIGH);
    digitalWrite( 31, HIGH);
    digitalWrite( 32, LOW);
    digitalWrite( 33, HIGH);
    digitalWrite( 34, HIGH);
    digitalWrite( 35, LOW); 
    digitalWrite( 36, HIGH);
    digitalWrite( 37, HIGH);
    digitalWrite( 38, LOW);
    for(int i=39; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==51) {
    for(int i=22; i<=28; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 29, LOW);
    digitalWrite( 30, HIGH);
    digitalWrite( 31, HIGH);
    digitalWrite( 32, LOW);
    digitalWrite( 33, HIGH);
    digitalWrite( 34, HIGH);
    digitalWrite( 35, LOW); 
    digitalWrite( 36, HIGH);
    digitalWrite( 37, HIGH);
    digitalWrite( 38, LOW);
    digitalWrite( 39, HIGH);
    digitalWrite( 40, HIGH);
    digitalWrite( 41, LOW);
    for(int i=42; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
  if (min==52) {
    for(int i=22; i<=31; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 32, LOW);
    digitalWrite( 33, HIGH);
    digitalWrite( 34, HIGH);
    digitalWrite( 35, LOW); 
    digitalWrite( 36, HIGH);
    digitalWrite( 37, HIGH);
    digitalWrite( 38, LOW);
    digitalWrite( 39, HIGH);
    digitalWrite( 40, HIGH);
    digitalWrite( 41, LOW);
    digitalWrite( 42, HIGH);
    digitalWrite( 43, HIGH);
    digitalWrite( 44, LOW);
    digitalWrite( 45, HIGH);
    digitalWrite( 46, HIGH);
    digitalWrite( 47, HIGH);
    digitalWrite( 48, HIGH);
  }
  if (min==53) {
    for(int i=22; i<=34; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 35, LOW); 
    digitalWrite( 36, HIGH);
    digitalWrite( 37, HIGH);
    digitalWrite( 38, LOW);
    digitalWrite( 39, HIGH);
    digitalWrite( 40, HIGH);
    digitalWrite( 41, LOW);
    digitalWrite( 42, HIGH);
    digitalWrite( 43, HIGH);
    digitalWrite( 44, LOW);
    digitalWrite( 45, HIGH);
    digitalWrite( 46, HIGH);
    digitalWrite( 47, LOW);
    digitalWrite( 48, HIGH);
  }
  if (min==54) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, HIGH);
    digitalWrite( 24, LOW);
    for(int i=25; i<=37; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 38, LOW);
    digitalWrite( 39, HIGH);
    digitalWrite( 40, HIGH);
    digitalWrite( 41, LOW);
    digitalWrite( 42, HIGH);
    digitalWrite( 43, HIGH);
    digitalWrite( 44, LOW);
    digitalWrite( 45, HIGH);
    digitalWrite( 46, HIGH);
    digitalWrite( 47, LOW);
    digitalWrite( 48, HIGH);
  }
  if (min==55) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, HIGH);
    digitalWrite( 24, LOW);
    digitalWrite( 25, HIGH);
    digitalWrite( 26, HIGH);
    digitalWrite( 27, LOW);
    for(int i=28; i<=40; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 41, LOW);
    digitalWrite( 42, HIGH);
    digitalWrite( 43, HIGH);
    digitalWrite( 44, LOW);
    digitalWrite( 45, HIGH);
    digitalWrite( 46, HIGH);
    digitalWrite( 47, LOW);
    digitalWrite( 48, HIGH);
  }
  if (min==56) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, HIGH);
    digitalWrite( 24, LOW);
    digitalWrite( 25, HIGH);
    digitalWrite( 26, HIGH);
    digitalWrite( 27, LOW);
    digitalWrite( 28, HIGH);
    digitalWrite( 29, HIGH);
    digitalWrite( 30, LOW);
    for(int i=31; i<=43; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 44, LOW);
    digitalWrite( 45, HIGH);
    digitalWrite( 46, HIGH);
    digitalWrite( 47, LOW);
    digitalWrite( 48, HIGH);
  }
  if (min==57) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, HIGH);
    digitalWrite( 24, LOW);
    digitalWrite( 25, HIGH);
    digitalWrite( 26, HIGH);
    digitalWrite( 27, LOW);
    digitalWrite( 28, HIGH);
    digitalWrite( 29, HIGH);
    digitalWrite( 30, LOW);
    digitalWrite( 31, HIGH);
    digitalWrite( 32, HIGH);
    digitalWrite( 33, LOW);
    for(int i=34; i<=46; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 47, LOW);
    digitalWrite( 48, HIGH);
  }
  if (min==58) {
    digitalWrite( 22, HIGH);
    digitalWrite( 23, HIGH);
    digitalWrite( 24, LOW);
    digitalWrite( 25, HIGH);
    digitalWrite( 26, HIGH);
    digitalWrite( 27, LOW);
    digitalWrite( 28, HIGH);
    digitalWrite( 29, HIGH);
    digitalWrite( 30, LOW);
    digitalWrite( 31, HIGH);
    digitalWrite( 32, HIGH);
    digitalWrite( 33, LOW);
    digitalWrite( 34, HIGH);
    digitalWrite( 35, HIGH); 
    digitalWrite( 36, LOW);
    for(int i=37; i<=48; i++){
      digitalWrite( i, HIGH);
    }

  }
  if (min==59) {
    for(int i=22; i<=26; i++){
      digitalWrite( i, HIGH);
    }
    digitalWrite( 27, LOW);
    digitalWrite( 28, HIGH);
    digitalWrite( 29, HIGH);
    digitalWrite( 20, LOW);
    digitalWrite( 31, HIGH);
    digitalWrite( 32, HIGH);
    digitalWrite( 33, LOW);
    digitalWrite( 34, HIGH);
    digitalWrite( 35, HIGH); 
    digitalWrite( 36, LOW);
    digitalWrite( 37, HIGH);
    digitalWrite( 38, HIGH);
    digitalWrite( 39, LOW);
    for(int i=40; i<=48; i++){
      digitalWrite( i, HIGH);
    }
  }
}
