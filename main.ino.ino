#include <Adafruit_PCF8574.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
const char *ssid     = "Juan Pablo"; //Your WiFi SSID
const char *password = "6Z5UMR3L"; //Your WiFi password

//Pin definitions
#define DG0 0
#define DG1 1
#define DG2 2
#define DG3 3
#define DG4 7
#define DG5 6
#define DG6 5
#define DG7 4
#define DG8 0
#define DG9 1

#define AN1 D0
#define AN2 D5
#define AN3 D6
#define AN4 D7

int hours;
int minutes;
int digit1;
int digit2;
int digit3;
int digit4;
int oldmillis;

//User config
int tubetime = 3; //Time in milliseconds of lamp ignite time (Increase when tube is not glowing, decrease when flickering is visible)
int updateinterval = 20000; //Time between clock update
const long utcOffsetInSeconds = 7200; //Positive offset in seconds (UTC + 2hrs(7200 seconds))

Adafruit_PCF8574 pcf1;
Adafruit_PCF8574 pcf2;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds); //Set up NTC Client

void writeNixie(int dig, int num){
  switch(num){
    case 1:
      digitalWrite(AN1, HIGH);
      break;
    case 2:
      digitalWrite(AN2, HIGH);
      break;
    case 3:
      digitalWrite(AN3, HIGH);
      break;
    case 4:
      digitalWrite(AN4, HIGH);
      break;
    
  }
  switch(dig){
    case 0:
      pcf1.digitalWrite(DG0, HIGH);
      break;
    case 1:
      pcf1.digitalWrite(DG1, HIGH);
      break;
    case 2:
      pcf1.digitalWrite(DG2, HIGH);
      break;
    case 3:
      pcf1.digitalWrite(DG3, HIGH);
      break;
    case 4:
      pcf1.digitalWrite(DG4, HIGH);
      break;
    case 5:
      pcf1.digitalWrite(DG5, HIGH);
      break;
    case 6:
      pcf1.digitalWrite(DG6, HIGH);
      break;
    case 7:
      pcf1.digitalWrite(DG7, HIGH);
      break;
    case 8:
      pcf2.digitalWrite(DG8, HIGH);
      break;
    case 9:
      pcf2.digitalWrite(DG9, HIGH);
      break;
  }
  delay(tubetime); //Give the tube some time to ignite and maintain the glow
  clearLamp(dig, num); //Clear the current digit
}

//Write digit to desired tube
void clearLamp(int dig, int num){
  switch(num){
    case 1:
      digitalWrite(AN1, LOW);
      break;
    case 2:
      digitalWrite(AN2, LOW);
      break;
    case 3:
      digitalWrite(AN3, LOW);
      break;
    case 4:
      digitalWrite(AN4, LOW);
      break;
    
  }
  switch(dig){
    case 0:
      pcf1.digitalWrite(DG0, LOW);
      break;
    case 1:
      pcf1.digitalWrite(DG1, LOW);
      break;
    case 2:
      pcf1.digitalWrite(DG2, LOW);
      break;
    case 3:
      pcf1.digitalWrite(DG3, LOW);
      break;
    case 4:
      pcf1.digitalWrite(DG4, LOW);
      break;
    case 5:
      pcf1.digitalWrite(DG5, LOW);
      break;
    case 6:
      pcf1.digitalWrite(DG6, LOW);
      break;
    case 7:
      pcf1.digitalWrite(DG7, LOW);
      break;
    case 8:
      pcf2.digitalWrite(DG8, LOW);
      break;
    case 9:
      pcf2.digitalWrite(DG9, LOW);
      break;
  
  }
}

//Clear all nixies (For startup only)
void clearNixie(){
  pcf1.digitalWrite(DG0, LOW);
  pcf1.digitalWrite(DG1, LOW);
  pcf1.digitalWrite(DG2, LOW);
  pcf1.digitalWrite(DG3, LOW);
  pcf1.digitalWrite(DG4, LOW);
  pcf1.digitalWrite(DG5, LOW);
  pcf1.digitalWrite(DG6, LOW);
  pcf1.digitalWrite(DG7, LOW);
  pcf2.digitalWrite(DG8, LOW);
  pcf2.digitalWrite(DG9, LOW);
  digitalWrite(AN1, LOW);
  digitalWrite(AN2, LOW);
  digitalWrite(AN3, LOW);
  digitalWrite(AN4, LOW);
  
}

void setup() {
  Serial.begin(9600); 

  WiFi.begin(ssid, password); //Start the Wifi
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  //Get the time data
  timeClient.begin();
  timeClient.update();
  
  if (!pcf1.begin(0x3F, &Wire)) {
    Serial.println("Couldn't find PCF8574 - 1");
    while (1);
  }
  else{
    Serial.println("Found PCF8574 - 1");
  }
  if (!pcf2.begin(0x38, &Wire)) {
    Serial.println("Couldn't find PCF8574 - 2");
    while (1);
  }
  else{
    Serial.println("Found PCF8574 - 2");
  }

  //Set up all pins
  pcf1.pinMode(DG0, OUTPUT);
  pcf1.pinMode(DG1, OUTPUT);
  pcf1.pinMode(DG2, OUTPUT);
  pcf1.pinMode(DG3, OUTPUT);
  pcf1.pinMode(DG4, OUTPUT);
  pcf1.pinMode(DG5, OUTPUT);
  pcf1.pinMode(DG6, OUTPUT);
  pcf1.pinMode(DG7, OUTPUT);
  pcf2.pinMode(DG8, OUTPUT);
  pcf2.pinMode(DG9, OUTPUT);
  pinMode(AN1, OUTPUT);
  pinMode(AN2, OUTPUT);
  pinMode(AN3, OUTPUT);
  pinMode(AN4, OUTPUT);
  clearNixie(); //Initialize all tubes
}

void loop() {
  //Update time every x milliseconds (default 20000)
  if(millis() - oldmillis >= updateinterval){
    timeClient.update();
    hours = timeClient.getHours();
    minutes = timeClient.getMinutes();

    //Split up numbers into digits
    digit1 = (hours/10)%10;
    digit2 = hours%10;
    digit3 = (minutes/10)%10;
    digit4 = minutes%10;
  }
  //Show everything on the nixies
  writeNixie(digit1, 1);
  writeNixie(digit2, 2);
  writeNixie(digit3, 3);
  writeNixie(digit4, 4);
}
