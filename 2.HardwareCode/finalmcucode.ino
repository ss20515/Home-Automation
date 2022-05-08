
/*-----------------------------------------------------------Inculsion of various libraries to be used in this project------------------------*/

#include <SD.h>
#include "FirebaseESP8266.h"
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <dht.h>
#include "Stepper.h"

#include  <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
/*--------------------------------------------------------Definations------------------------------------------------*/

#define user "Dexter" // HOME WIfi SSID
#define pass "12345678" // WIFI PASSWORD
#define FIREBASE_AUTH "zfEOrJkczD1U75NVogSsHiumtqFfom1yfhOZF6f1" // FIREBASE AUTHORIZATION KEY
#define FIREBASE_HOST "test-3f5ea.firebaseio.com" // FIREBASE HOSTNAME

/*---------------------------------------------------------Pins------------------------------------------------------*/
//GIVING THE DEFINATIONS TO THE PIN WHICH MEANS WHICH PIN OF SENSORS AND DEVICES IS CONNECTED TO WHICH PIN OF NODEMCU



#define pir_r2pin D0 //PIR SENSOR OF ROOM 2 IS CONNECTED TO D0 PIN OF NODEMCU
#define systemled D4 //LED to show whether the system is on or off
#define fire_pin A0  //Fire sensor pin is connected to the Ao pin of Nodemcu


Stepper myStepper(32, D5, D7, D6, D8); // Stepper motor connected to D5,6,7,8 PIN OF NODEMCU
/*--------------------------------------------------------Global Variables-------------------------------------------*/
//Global variables to be used to implement program logic

int garage_done = 0;
const int stepsPerRevolution = 90;
int state = LOW;                                                 // by default, no motion detected
int val = 0;                                                     // variable to store the pir_r2pin status (value)
long timersr1, timerer1, diff;
long timersr2,timerer2;// variables for timer delay to get nonblocking delay
int master1 = 0;

int fbtstart, fbtend;
int fire_logic;
int fire_buzzer;
int intrusion_buzzer;
int intr_logic;
int intrstart, intrend;

/*------------------------------------------------------------Buffers-------------------------------------------------*/
//INCLUDES VARIOUS JSON BUFFERS TO HOLD THE VALUES OF CURRENT JSON STATE OF THE SYSTEM

DynamicJsonBuffer jsonBuffer;
DynamicJsonBuffer jsonBuffer2;
DynamicJsonBuffer jsonBuffer3;
DynamicJsonBuffer jsonBuffer4;

FirebaseData firebaseData; //Buffer to hold the data from the firebase



/*----------------------------------------------------------Function Declaration------------------------------------*/
void sendToArduino(String test);                                // Function to take a String and send it to Arduino via I2C Interface


/*----------------------------------------------------------Main Setup --------------------------------------------*/
void setup() {

  Serial.begin(9600); // Serial interface to begin at 9600 baud rate
  Wire.begin(D1, D2); // I2C interface at pin D1 and D2

  myStepper.setSpeed(600); // Setting the motor speed to 600 steps

  pinMode(pir_r2pin, INPUT); // setting the modes of the various pins to input and output
  pinMode(systemled, OUTPUT);
  pinMode(fire_pin, INPUT);

  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  //pinMode(pir_r1pin, INPUT);

  digitalWrite(systemled, HIGH);

  Serial.println("Ready");
 // delay(60000); // A delay in order to system to boot up effectively so that all sensors are heated effective for effective working
  
  
  WiFi.begin(user, pass); //Starting of wireless connection
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("connected");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //Initializing of various non blocking timers because the delay library function cause system to block 
  timersr2 = millis();
  timersr1 = millis();
  fbtstart = millis();
  intrstart = millis();
  
  fire_logic = 1;
  intr_logic = 1;
  
  digitalWrite(systemled, LOW);
}

/*-------------------------------------------------------------Loop---------------------------------------------------------*/

void loop() {

// Various local variables to be used in the code
  int val = 0;
  String json;
  String json_data;
  String json_data2;
  char arr[1000];
  int led_r2;
  int pir_r2;
  int pir_r2status;
  int led_r2cntrl;
  int led_r1;
  int pir_r1;
  int pir_r1status;
  int led_r1cntrl;
  bool successful;
  int led_r2mode;
  int led_r1mode;
  int humidity;
  int temperature;
  int fan;
  int fan_tempset;
  int fan_temp;
  int fan_cntrl;
  int fire;
  int fire_alarm;
  int intrusion_set;
  int intrusion_alarm;
  int garage;
  int led_g;
  int led_k;
  int led_h;
  int r,g,b;


  /*--------------------------------------------------------------------------Getting Json Data------------------------------------------------*/

  successful = Firebase.getJSON(firebaseData, "/");
//  if  (!successful) {
//    return;
//  }
  json = firebaseData.jsonData();
  json.toCharArray(arr, 1000);
  Serial.println(arr);
  JsonObject& root = jsonBuffer.parseObject(arr);
  if (!root.success()) {
    Serial.println("parseObject() failed"); 
    return;
  }
 /*------------------------------------------------------------------------------Getting arduino Data---------------------------------------------------*/
 char mcudata[32];
 int mcudataindex =0;
    Wire.requestFrom(8, 32);
  while(Wire.available()){
    mcudata[mcudataindex] = Wire.read();
    mcudataindex++;
    }
  

 int mcuval[2];
 String datamcu = String(mcudata);

 strtodata(mcuval, datamcu);
 Serial.println("MY MCU");
 Serial.println(mcuval[1]);
 Serial.println(mcuval[0]);

/*----------------------------------------------------------------------------Led and PIR functionality ------------------------------------------------------------*/
  intrusion_set = root["intrusion_set"];

  led_r2cntrl = root["led_r2cntrl"];
  led_r2mode = root["led_r2mode"];
  pir_r2 = digitalRead(pir_r2pin);
  Serial.println("room 2 pir");
  Serial.println(pir_r2);
  pir_r2status = pirCheck(pir_r2, &timerer2, &timersr2);
  Serial.println("room 2 pir status");
  Serial.println(pir_r2status);

  led_r1cntrl = root["led_r1cntrl"];
  led_r1mode = root["led_r1mode"];
 // pir_r1 = digitalRead(pir_r1pin);
  Serial.println("room 1 pir");
  Serial.println(pir_r1);
 // pir_r1status = pirCheck(pir_r1, &timerer1, &timersr1);
  
  intrusioncheck(&intrusion_set, &intrusion_alarm, &intrstart, &intrend, &intrusion_buzzer, &intr_logic, pir_r2status);
  //intrusioncheck(&intrusion_set, &intrusion_alarm, &intrstart, &intrend, &intrusion_buzzer, &intr_logic, pir_r1status);
  
  ledCheck(&led_r2, led_r2mode, pir_r2status, led_r2cntrl);
  ledCheck(&led_r1, led_r1mode, pir_r1status, led_r1cntrl);

  led_g = root["led_g"];
  led_k = root["led_k"];


  /*-------------------------------------------------------------------------------------fan---------------------------------------------------------*/
  temperature = mcuval[0];
  humidity = mcuval[1];
  fan_tempset = root["fan_tempset"];
  fan = root["fan"];
  fan_cntrl = root["fan_cntrl"];
  fan_temp = root["fan_temp"];

  if (fan_tempset == 1) {
    if (temperature > fan_temp) {
      fan = 1;
    }
    else {
      if (fan_cntrl == 1) {
        fan = 1;
      }
      else {
        fan = 0;
      }
    }
  }
  else {
    if (fan_cntrl == 1) {
      fan = 1;
    }
    else {
      fan = 0;
    }
  }


  /*--------------------------------------------------Fire Alarm------------------------------------------------------------------*/
  fire = analogRead(fire_pin);
  Serial.println("fure:");
  Serial.println(fire);
  firecheck(&fire_buzzer, &fbtstart, &fbtend, &fire, &fire_alarm, &fire_logic);

/*----------------------------------------------------------Garage-------------------------------------------------------------*/
garage = root["garage"];
 if(garage == 1&& garage_done == 0)
  { 
   myStepper.step(-800);
   
   garage_done =1;
   delay(500);
   }
  if(garage ==0 && garage_done == 1){
    myStepper.step(800);
    garage_done = 0;
    delay(500);
    }
    /*---------------------------------------------------------Control hall rgb led --------------------------------------------------------*/

    led_h = root["led_h"];
    if(led_h == 0){
      r=0;
      g=0;
      b=0;
      
      }else{
        r= root["r"];
        g = root["g"];
        b = root["b"];
        }
    
  /*----------------------------------------------------Uploading Data---------------------------------------------------------------*/

  JsonObject& object = jsonBuffer2.createObject();// data to update
  object["pir_r2"] = pir_r2status;
  object["led_r2"] = led_r2;
  //object["pir_r1"] = pir_r1status;
  object["led_r1"] = led_r1;
  object["fan"] = fan;
  object["fire_alarm"] = fire_alarm;
  object["intrusion_alarm"] = intrusion_alarm;
  object["temp"] = mcuval[0];
  object["humidity"] = mcuval[1];


  object.printTo(json_data2);
  Firebase.updateNode(firebaseData, "/", json_data2);




  /*----------------------------------------------------------Sending data to arduino-----------------------------------------------------*/

  JsonObject& arduinoData = jsonBuffer3.createObject();
  arduinoData["r2"] = led_r2;
  arduinoData["r1"] = led_r1;
  arduinoData["f"] = fan;
  arduinoData["fire"] = fire_buzzer;
  arduinoData["intr"] = intrusion_buzzer;
  arduinoData["led_g"] = led_g;
  arduinoData["led_k"] = led_k;
  arduinoData["r"] = r;
  arduinoData["g"] = g;
  arduinoData["b"] = b;
//  arduinoData["garage"] = garage;
  
  

  arduinoData.printTo(json_data);
  String bytes = String(json_data.length());
  
  sendToArduino(bytes);
  sendToArduino(json_data);

  lcd.setCursor(1,0);
  lcd.print("Temprature: ");
  lcd.print(temperature);
  lcd.setCursor(1,1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  

  jsonBuffer.clear();
  jsonBuffer2.clear();
  jsonBuffer3.clear();


 
}


int strtodata(int *arr, String data){
  int i=0;
  int l=0;
  boolean loop = true;
  int index = data.indexOf(';');
  
  while(loop){
    l++;
    if(l==32){
      return -1;}
    arr[i] = data.toInt();
    i++;
    data = data.substring(index+1);
    
    index = data.indexOf(';');
    
    if(l<2){loop = true;}
    else{
      loop=false;
      }
    }
    return i;
  }
/*---------------------------------------------------------------------Function to send data--------------------------------------------------------------*/
void sendToArduino(String test) {
  char ch[1000];
  int i;
  for (i = 0; i < test.length(); i += 31) {
    test.substring(i).toCharArray(ch, 32);
    
    Wire.beginTransmission(8);
    Wire.write(ch);
    
    Wire.endTransmission();
    Serial.print(ch);
    Serial.println();
  }
}
