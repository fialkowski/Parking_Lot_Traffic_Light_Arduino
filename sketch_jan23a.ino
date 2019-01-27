
#include <millisDelay.h>

unsigned long DOOR_CONTACT_DELAY = 300; // 0.3sec
unsigned long doorContactDelayStart = 0; // the time the delay started
bool doorContactDelayRunning = false; // true if still waiting for delay to finish

unsigned long DOOR_OPEN_DELAY = 15000; // 15 sec
unsigned long doorOpenDelayStart = 0; // the time the delay started
bool doorOpenDelayRunning = false; // true if still waiting for delay to finish

unsigned long DRIVE_IN_DELAY = 4000; // 10 sec
unsigned long driveInDelayStart = 0; // the time the delay started
bool driveInDelayRunning = false; // true if still waiting for delay to finish

const int cardReader = 12;
const int garageDoor = 13;// the number of the pushbutton pin
const int redRelay =  4;      // the number of the LED pin
const int greenRelay = 5;

// variables will change:
int garageDoorState = 0;         // variable for reading the pushbutton status
int cardReaderState = 0;

void setup() {
  pinMode(redRelay, OUTPUT);
  pinMode(greenRelay, OUTPUT);
  pinMode(garageDoor, INPUT);
  pinMode(cardReader, INPUT);
 
  doorOpenDelayStart = millis();
  driveInDelayStart = millis();
  //Serial.begin(9600);  
}

void loop() {
  cardReaderState = digitalRead(cardReader);
  //garageDoorState = digitalRead(garageDoor);
  Serial.println(doorOpenDelayRunning);
  
  if(digitalRead(cardReader == HIGH)){
    doorContactDelayStart = millis();
    doorContactDelayRunning = true;
    garageDoorState = HIGH;
  }
     
  if(doorContactDelayRunning && ((millis() - doorContactDelayStart) >= DOOR_CONTACT_DELAY)){
    doorContactDelayRunning = false;
    garageDoorState = LOW;
  }
  
  if(doorOpenDelayRunning && ((millis() - doorOpenDelayStart) >= DOOR_OPEN_DELAY)){
    doorOpenDelayRunning = false;
  }
  if(driveInDelayRunning && ((millis() - driveInDelayStart) >= DRIVE_IN_DELAY)){
    driveInDelayRunning = false;
  }
  
  if(garageDoorState == LOW){
    driveInDelayRunning = false;
    if(cardReaderState == HIGH){
      doorOpenDelayStart = millis();
      doorOpenDelayRunning = true;
      //Serial.println("timer started");
    }
  }
  if(doorOpenDelayRunning && garageDoorState == HIGH){
    doorOpenDelayRunning = false;
    driveInDelayStart = millis();
    driveInDelayRunning = true;
  }
  if(driveInDelayRunning){
    signalToGreen(true);
  } else {
    signalToGreen(false);
  }
  if(cardReaderState == HIGH && garageDoorState == HIGH){
    doorOpenDelayRunning = false;
    driveInDelayStart = millis();
    driveInDelayRunning = true;
  }
}


void signalToGreen(bool state) {
  if (state == true) {
    digitalWrite(redRelay, LOW);
    digitalWrite(greenRelay, HIGH);
  } else {
    digitalWrite(redRelay, HIGH);
    digitalWrite(greenRelay, LOW);
  }
}
