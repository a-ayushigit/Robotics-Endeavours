// Include the library files
#define BLYNK_TEMPLATE_ID "TMPLDtzcoHlp"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "m9jPuPVNqivOSYQBmQbZs1kuWHChpmui"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// Define the motor pins
#define ENA D5
#define IN1 D8
#define IN2 D7
#define IN3 D4
#define IN4 D3
#define ENB D6

// Variables for the Blynk widget values
// Variables for the Blynk widget values
int x = 50;
int y = 50;
int Speed;
char auth[] = "m9jPuPVNqivOSYQBmQbZs1kuWHChpmui"; //Enter your Blynk auth token
char ssid[] = "AndroidAPS"; //Enter your WIFI name
char pass[] = "rufj8000"; //Enter your WIFI passowrd

void setup() {
  Serial.begin(9600);

     
  
  
  
  
  //Set the motor pins as output pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
 // Initialize the Blynk library
   Blynk.begin(auth, ssid, pass,"blynk.cloud",80);
}
//Get the slider values
BLYNK_WRITE(V5) {
  Speed = param.asInt();
}



// Get the joystick values
BLYNK_WRITE(V1) {
  x = param[0].asInt();
}
// Get the joystick values
BLYNK_WRITE(V0) {
  y = param[0].asInt();
}
// Check these values using the IF condition
void WIFI_car() {
  if (x ==1) {
    carForward();
    Serial.println("carForward");
  } else if (x ==-1) {
    carBackward();
    Serial.println("carBackward");
  } else if (y ==-1) {
    carLeft();
    Serial.println("carLeft");
  } else if (y ==1) {
    carRight();
    Serial.println("carRight");
  } else if (x ==0 && y==0) {
    carStop();
    Serial.println("carstop");
  }
  else if (x==1 && y==1){
    carForwardRight();
    Serial.println("car forward right");
  }
   else if (y==-1 && x==1){
    carForwardLeft();
    Serial.println("car forward left");
  }
   else if (y==-1 && x==-1){
    carBackwardLeft();
    Serial.println("car backward left");
  }
   else if (y==1 && x==-1){
    carBackwardRight();
    Serial.println("car backward right");
  }
}
void loop() {
  Blynk.run();// Run the blynk function
   WIFI_car();// Call the main function
  
}

/*****Motor movement functions******/
void carForward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carBackward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carLeft() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carRight() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
 void carForwardRight(){
   analogWrite(ENA, Speed);
  analogWrite(ENB, Speed/2);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
   
 }
 void carForwardLeft(){
   analogWrite(ENA, Speed/4);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
   
 }
void carBackwardRight() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed/4);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carBackwardLeft() {
  analogWrite(ENA, Speed/4);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}