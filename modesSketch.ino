#include <swDuino.h>

swDuino objswDuino;

const int relay_ctrl = 7;
const int photoresistor_in = 0;
const int dist_sensor_echo = 2;
const int dist_sensor_trig = 5;
const int led = 8;

const int max_luminocity_lvl = 200;
const long activation_distance = 50;

byte mode = 2; //0 - disabled, 1 - enabled, 2 - auto
bool light_enabled = false;

void setup() {  
  pinMode(relay_ctrl, OUTPUT);
  pinMode(photoresistor_in, INPUT);
  pinMode(led, OUTPUT);
  
  digitalWrite(relay_ctrl, LOW);
  
  objswDuino.begin(9600);
}

void loop() {
  objswDuino.read(trigger);

  int current_lum_lvl = analogRead(photoresistor_in);
  long current_distance = getDistance();

  if (mode == 0) {
    disableLight();
  }
  else if (mode == 1) {
    enableLight();
  }
  else {
      if (current_lum_lvl < max_luminocity_lvl && current_distance < activation_distance) {
        enableLight();
      }
      else {
        disableLight();
      }
  }

  objswDuino.write("current_distance", String(current_distance));
  objswDuino.write("luminocity_lvl", String(current_lum_lvl));
  objswDuino.write("mode", String(mode));
  objswDuino.write("light_enabled", String(light_enabled));

  delay(500);
}

void enableLight() {
  digitalWrite(relay_ctrl, LOW);
  digitalWrite(led, HIGH);
  light_enabled = true;
}

void disableLight() {
  digitalWrite(relay_ctrl, HIGH);
  digitalWrite(led, LOW);
  light_enabled = false;
}

long getDistance() {
  pinMode(dist_sensor_trig, OUTPUT);
  digitalWrite(dist_sensor_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(dist_sensor_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(dist_sensor_trig, LOW);
  
  pinMode(dist_sensor_echo, INPUT);
  long duration = pulseIn(dist_sensor_echo, HIGH);
  
  return mcrToCm(duration);
}

long mcrToCm(long microseconds) {
  return microseconds / 29 / 2;
}

void trigger(String VARIABLE, String VALUE) {
  if (VARIABLE == "mode")
  {
    if (VALUE == "0")
    {
      mode = 0;
    }
    else if (VALUE == "1")
    {
      mode = 1;
    }
    else {
      mode = 2;
    }
  }
}
