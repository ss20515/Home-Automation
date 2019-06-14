#include <Wire.h>

#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <dht.h>

StaticJsonBuffer<120> jsonBuffer;

#define led_r2pin 7
#define fire_buzzer_pin 4
#define fan_pin 3
#define intrusion_buzzer_pin 2
#define dht_pin 5
#define led_r1pin 6
#define led_kpin 9
#define led_gpin 8
#define red 10
#define blue 11
#define green 12

dht DHT;

char mcudata[20];
char mculen[3];
int done = 0;
int no=0;
char data[100];
int index=0;
int bytes = 0;
char bytesbuff[4];
int buffindex = 0;
bool datamark=true;
int garage;

void setup()
{
 
 Wire.begin(8);                
 Wire.onReceive(receiveEvent);
 Wire.onRequest(requestEvent);
 

 pinMode(led_r2pin,OUTPUT);
 pinMode(fire_buzzer_pin, OUTPUT);
 pinMode(fan_pin, OUTPUT);
 pinMode(intrusion_buzzer_pin, OUTPUT);
 pinMode(dht_pin, INPUT);
 pinMode(led_r1pin, OUTPUT);
 pinMode(led_gpin, OUTPUT);
 pinMode(led_kpin, OUTPUT);
   pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
 
 digitalWrite(intrusion_buzzer_pin, LOW);
 digitalWrite(fire_buzzer_pin, LOW);
 Serial.begin(9600);
 int val = DHT.read11(dht_pin);
 String temp = String(DHT.temperature)+';';
 
 String humidity = String(DHT.humidity)+';';
 
 String final  = temp+humidity;
 String len = String(final.length());
 Serial.println(final);
 len.toCharArray(mculen,3);
 Serial.println(mculen);
 final.toCharArray(mcudata,20);

 
 
 delay(5000);
 }

 void loop(){

 }
 
 void receiveEvent(int howMany) {
 
//Serial.println(howMany);
 if(howMany<4&&datamark){
  
  while(Wire.available()){
    char c = Wire.read();
    
    bytesbuff[buffindex] = c;
    buffindex++;
    }
    buffindex=0;
    Serial.println(bytesbuff);
    datamark = false;
    bytes = String(bytesbuff).toInt();
   Serial.println("bytesbuff");
    Serial.print(bytes);
    Serial.println();
    
  }
 else{ 
 while (Wire.available()) {
    char c = Wire.read();
     data[index]=c;
     index++;
     /* print the character */
  }
  
  
  if(index>=bytes){
    jsonBuffer.clear();
    
    index=0;
    bytes = 0;
    datamark = true;
    no=0;
    Serial.println(data);
    JsonObject& root = jsonBuffer.parseObject(data);
    
    if(!root.success()){
      //Serial.println("wrong");
      
      return;
      }
    else{
      
    int led_r1 = root["r1"];
    int fan = root["f"];
    int fire_buzzer = root["fire"];
    int intrusion_buzzer = root["intr"];
    int led_g = root["led_g"];
    int led_k = root["led_k"];
    int led_r2 = root["r2"];
    int r = root["r"];
    int g = root["g"];
    int b = root["b"];


    analogWrite(red, r);
  analogWrite(green, g);
  analogWrite(blue, b);
    
    
    digitalWrite(led_r2pin,led_r2);
    digitalWrite(fire_buzzer_pin, fire_buzzer);
    digitalWrite(intrusion_buzzer_pin, intrusion_buzzer);
    digitalWrite(led_r1pin, led_r1);
    digitalWrite(led_gpin, led_g);
    digitalWrite(led_kpin, led_k);

    int val = DHT.read11(dht_pin);
    Serial.println("gsdfd");
    Serial.println(DHT.temperature);
  String temp = String(DHT.temperature)+';';
 
 String humidity = String(DHT.humidity)+';';
 String final  = temp+humidity;
 String len = String(final.length());
 Serial.println(len);
 len.toCharArray(mculen,3);
 Serial.println(mculen);
 final.toCharArray(mcudata,20);
    }
    }
    else{
      }
      }
 }
void requestEvent(){
    Wire.write(mcudata);
 }



int strtodata(int *arr, String data){
  int i=0;
  int l=0;
  boolean loop = true;
  int index = data.indexOf(',');
  int next;
  while(loop){
    l++;
    if(l==50){
      return -1;}
    arr[i] = data.toInt();
    i++;
    data = data.substring(index+1);
    if(data.length()>0){
    index = data.indexOf(',');
    
    }
    else{
      loop=false;
      }
    }
    return i;
  }
