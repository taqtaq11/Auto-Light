#include <NewPing.h>

const int echo_1 = 2;
const int trig_1 = 5;
const int echo_2 = 9;
const int trig_2 = 10;
const int led = 8;

const int max_distance = 200;
const long activation_distance = 65;

byte dir = 0; //1 - in, 2 - out

NewPing sonar1(trig_1, echo_1, max_distance);
NewPing sonar2(trig_2, echo_2, max_distance);

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(50);
  
  unsigned int dist1 = sonar1.ping() / 58;
  unsigned int dist2 = sonar2.ping() / 58;

  pinMode(echo_1,OUTPUT);  
  digitalWrite(echo_1,LOW);  
  pinMode(echo_1,INPUT);
  
  pinMode(echo_2,OUTPUT);  
  digitalWrite(echo_2,LOW);  
  pinMode(echo_2,INPUT);
  
  //Serial.print("Ping1: ");  
  //Serial.println(dist1);
  //Serial.print("Ping2: ");  
  //Serial.println(dist2);

  if (dist1 < activation_distance && dist2 < activation_distance) {
    unsigned int delta = dist2 - dist1;
    dir = delta < 0 ? 2 : 1;
  }

  if (dist1 < activation_distance) {
    if (dir == 0) {
      dir = 1;
    }
    else if (dir == 2) {
      Serial.println("Action: Out");
      dir = 0;
    }
  }
  else {
    if (dir == 1) {
      dir = 0;  
    }
  }

  if (dist2 < activation_distance) {
    if (dir == 0) {
      dir = 2;
    }
    else if (dir == 1) {
      Serial.println("Action: In");
      dir = 0;
    }
  }
  else {
    if (dir == 2) {
      dir = 0;  
    }
  }
}

long getDistance(int echoPort, int trigPort) {
  digitalWrite(trigPort, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPort, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPort, LOW);
  
  long duration = pulseIn(echoPort, HIGH);
  
  return duration / 58;
}

void enableLight() {
  digitalWrite(led, HIGH);
}

void disableLight() {
  digitalWrite(led, LOW);
}
