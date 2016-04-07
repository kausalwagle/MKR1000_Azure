//THANK YOU MOHANP 
#include <SPI.h>
#include <WiFi101.h>

///*** WiFi Network Config ***///
char ssid[] = "Your_SSID"; //  your network SSID (name)
char pass[] = "YourKey";    // your network password (use for WPA, or use as key for WEP)
///*** Azure IoT Hub Config ***///
//see: http://mohanp.com/  for details on getting this right if you are not sure.

char hostname[] = "[iotHubName].azure-devices.net";    // host name address for your Azure IoT Hub
char azurePOST_Uri[] = "/devices/[DeviceName]/messages/events?api-version=2016-02-03"; //feed URI
char authSAS[] = "[Shared Access Key]";
///*** Azure IoT Hub Config ***///

unsigned long lastConnectionTime = 0;            
const unsigned long pollingInterval = 10L * 1000L; // 10 sec polling delay, in milliseconds

String STATUS; /// for sending update over azure

int status = WL_IDLE_STATUS;

WiFiSSLClient client;
/////////////////////////////////////////////////////////////////
int maxDownLevel = 5;
int minDownLevel = 10;

int maxTopLevel = 4;
int minTopLevel = 18;

bool change = false;
/////////////////////////////////////////
int relayPin = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relayPin,OUTPUT);
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("Error With Wifi Shield");
  }
}

void loop() {
  /*
  long now=millis();
  Serial.print("Up Sensor: ");
  Serial.println(upSensor());
  Serial.print("Down Sensor: ");
  Serial.println(downSensor());
  Serial.println(millis()-now);
  Serial.println(motorStatus());
  Serial.println();
  */
  if (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
  }
  else{
    Serial.println("Connected");
  }
  Serial.println(motorExecute());

  ///update to azure IoT Hub
  if (millis() - lastConnectionTime > pollingInterval) {
    updateLoop();
  }
  
}


int topSensor(){
  int trigPin=4,echoPin=5;
  pinMode(trigPin,OUTPUT);
  digitalWrite(trigPin, HIGH);
  delay(20);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin,INPUT);
  float duration=pulseIn(echoPin, HIGH);
  float distance= ((duration/2)/29.1) ;
  //Serial.print("Distance : ");
  //Serial.println(distance);
  return distance;
}

int downSensor(){
  int trigPin=3,echoPin=2;
  pinMode(trigPin,OUTPUT);
  digitalWrite(trigPin, HIGH);
  delay(20);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin,INPUT);
  float duration=pulseIn(echoPin, HIGH);
  float distance= ((duration/2)/29.1) ;
  //Serial.print("Distance : ");
  //Serial.println(distance);
  return distance;
}






