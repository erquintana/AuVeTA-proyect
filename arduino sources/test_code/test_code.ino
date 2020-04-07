/*

  Code for testsensorPibg components of Spimeter proyect

*/
#include <Encoder.h>
#include <Time.h>
#include <TimeLib.h>


// Variable declarations:
int sensorPin = 3; // sensor decl
int buttonPin = 13; // button decl
int buzzerPin = 6; // buzzer decl
// comunication decl RX
// comunication decl TX
Encoder encoder(8, 9); // rotatory encoder setup



unsigned long duration = 0;
float rps = 0;
int counter = 0;
int present = 0;
int previous = 0;
unsigned long elapsed = 0;
unsigned long elapsed_prev = 0;
String st = "";
int rpso = 0;
int enc = 0;
int oldPosition  = 0;
int newPosition = 0;
int resolution = 100;
int msi = millis() / resolution;
unsigned long millPrev = 0;
unsigned long mill = 0;

/*int hi = hour();
  int mi = minute();
  int si = second() - 1;
  int h;
  int m;
  int s = 0;
  int sPrev = 0;
*/
bool state = false;
int R = 10;
int G = 11;
int B = 12;


void setup() {
  Serial.begin(19200); // serial for test and visualization, comment later if not needed
  pinMode(sensorPin, INPUT); // black = 1 || white = 0
  pinMode(buttonPin, INPUT); // on = 0
  pinMode(buzzerPin, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  st = "m,r,e,s";
  Serial.println(st);

}



void loop() {


  if ((digitalRead(buttonPin) == 0) && state == false) {
    advTone();
    state = true;
    digitalWrite(G, HIGH);
    digitalWrite(R, LOW);


  } else if ((digitalRead(buttonPin) == 0) && state == true) {
    digitalWrite(G, LOW);
    digitalWrite(R, HIGH);
    advTone();
    state = false;
  }
  printData();
  delay(25);
}


void advTone() {
  if (state == false) {
    tone(buzzerPin, 2500);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 3250);
    delay(50);
    noTone(buzzerPin);
  } else if (state == true) {
    tone(buzzerPin, 2500);
    delay(100);
    noTone(buzzerPin);
    tone(buzzerPin, 1750);
    delay(500);
    noTone(buzzerPin);
  }

}

void printData() {
  millPrev = mill;
  /*  sPrev = s;
    h = hour() - hi;
    m = minute() - mi;
    s = second() - si;
  */
  mill = millis() / resolution - msi;
  enc = getEncVal();
  if (millPrev != mill) {
    if (state == true) {
      mill = millis() / resolution - msi;
      rpso = getRPS();
      st = String(mill) + ',' + String(rpso) + ',' + String(enc) + ',' + String(state);
      Serial.println(st);

    } else if (state == false) {
      mill = millis() / resolution - msi;
      st = String(mill) + ',' + String(rpso) + ',' + String(enc) + ',' + String(state);
      Serial.println(st);

    }
  }
}


float getRPS() {

  ///////////////////////one rotation measure///////////////////
  if (digitalRead(sensorPin) == 1 && previous == 0)
  {
    previous = 1;
    duration = elapsed - elapsed_prev;
    elapsed_prev  = micros();
  }
  if (digitalRead(sensorPin) == 1 && previous == 1)
  {
    previous = 1;
  }
  if (digitalRead(sensorPin) == 0 && previous == 1)
  {
    previous = 0;
  }
  if (digitalRead(sensorPin) == 0 && previous == 0)
  {
    previous = 0;
    elapsed = micros();
  }
  //////////////////////////////////////////////////////////////

  rps = 1000000 / duration;

  return rps;
}


int getEncVal() {
  if (state == true) {
    newPosition = encoder.read() / 4;
    if (newPosition != oldPosition) {
      oldPosition = newPosition;
      tone(buzzerPin, 3000);
      delay(5);
      noTone(buzzerPin);

      return newPosition;
    }

  } else {
    return oldPosition;
  }

}
