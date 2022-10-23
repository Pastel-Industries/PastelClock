#include <Adafruit_PCF8574.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//User config
int tubetime = 3; //Time in milliseconds of lamp ignite time (Increase when tube is not glowing, decrease when flickering is visible)
const long utcOffsetInSeconds = 7200; //Positive offset in seconds (UTC + 2hrs(7200 seconds))
const char *ssid     = "YourSSID"; //Your WiFi SSID
const char *password = "YourPASS"; //Your WiFi password

//Pin definitions
int cathodes[10] = {0, 1, 2, 3, 7, 6, 5, 4, 0, 1};
int anodes[4] = {16, 14, 12, 13};

int hours;
int minutes;
int seconds;
int digit1;
int digit2;
int digit3;
int digit4;
int oldminutemillis;
int millistocompensate;

Adafruit_PCF8574 pcf1;
Adafruit_PCF8574 pcf2;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds); //Set up NTC Client

//Write digit to desired tube
void writeNixie(int dig, int an, int number){
  digitalWrite(an, HIGH);
  if(number >= 8){
    pcf2.digitalWrite(dig, HIGH);
  }
  else{
      pcf1.digitalWrite(dig, HIGH);
  }
  delay(tubetime); //Give the tube some time to ignite and maintain the glow
  clearLamp(dig, an, number); //Clear the current digit
}

//Clear digit from desired tube
void clearLamp(int dig, int an, int number){
  digitalWrite(an, LOW);
  if(number >= 8){
    pcf2.digitalWrite(dig, LOW);
  }
  else{
      pcf1.digitalWrite(dig, LOW);
  }
}

//Clear all nixies (For startup only)
void clearNixie(){
  pcf1.digitalWrite(0, LOW);
  pcf1.digitalWrite(1, LOW);
  pcf1.digitalWrite(2, LOW);
  pcf1.digitalWrite(3, LOW);
  pcf1.digitalWrite(4, LOW);
  pcf1.digitalWrite(5, LOW);
  pcf1.digitalWrite(6, LOW);
  pcf1.digitalWrite(7, LOW);
  pcf2.digitalWrite(0, LOW);
  pcf2.digitalWrite(1, LOW);
  digitalWrite(16, LOW);
  digitalWrite(14, LOW);
  digitalWrite(13, LOW);
  digitalWrite(13, LOW);
  Serial.println("Nixies initialized");
}

//Get the current time
void updatetime(){
  timeClient.update();
  hours = timeClient.getHours();
  minutes = timeClient.getMinutes();
  seconds = timeClient.getSeconds();
  millistocompensate = seconds*1000;

  //Split up numbers into digits
  digit1 = (hours/10)%10;
  digit2 = hours%10;
  digit3 = (minutes/10)%10;
  digit4 = minutes%10;
}

void setup() {
  Serial.begin(9600); 

  Serial.print("Connecting");
  WiFi.begin(ssid, password); //Start the Wifi
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  Serial.println(" ");
  
  //Get the time data
  timeClient.begin();
  timeClient.update();
  Serial.println("Time updated");
  
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
  pcf1.pinMode(0, OUTPUT);
  pcf1.pinMode(1, OUTPUT);
  pcf1.pinMode(2, OUTPUT);
  pcf1.pinMode(3, OUTPUT);
  pcf1.pinMode(4, OUTPUT);
  pcf1.pinMode(5, OUTPUT);
  pcf1.pinMode(6, OUTPUT);
  pcf1.pinMode(7, OUTPUT);
  pcf2.pinMode(0, OUTPUT);
  pcf2.pinMode(1, OUTPUT);
  Serial.println("Cathodes set");
  pinMode(16, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.println("Anodes set");
  clearNixie(); //Initialize all tubes
  updatetime();
  Serial.println("Time updated");
  
}

void loop() {
  //Update time every 60 seconds
  if(millis() - oldminutemillis >= 60000 - millistocompensate){
    millistocompensate = (millis() - oldminutemillis) - 60000;
    minutes++;
    if(minutes >= 60){
      hours++;
      if(hours >= 24){
        hours = 0;
      }
      minutes = 0;
    }
    oldminutemillis = millis();
    //chopping
    digit1 = (hours/10)%10;
    digit2 = hours%10;
    digit3 = (minutes/10)%10;
    digit4 = minutes%10;
  }
  //Show everything on the nixies
  writeNixie(cathodes[digit1], anodes[0], digit1);
  writeNixie(cathodes[digit2], anodes[1], digit2);
  writeNixie(cathodes[digit3], anodes[2], digit3);
  writeNixie(cathodes[digit4], anodes[3], digit4);
}
