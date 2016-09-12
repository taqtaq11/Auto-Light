#include <NewPing.h>

const byte echo_1 = 2;
const byte trig_1 = 5;
const byte echo_2 = 9;
const byte trig_2 = 10;
const byte led = 8;
const byte tick_duration = 50;

class Sonar {
  public:
    Sonar(byte num, byte echo, byte trig);
    boolean checkActivation();

  private:
    const unsigned int max_distance = 200;
    const unsigned int activation_distance_delta = 60;
    const unsigned int restoration_time = 1000;
    const unsigned int time_to_activation_check = 100;

    NewPing* sonar;
    int current_elapsed_time = 0;
    boolean isRestorating = false;
    unsigned int distance_sum = 0;
    byte echo;
    byte trig;
    byte num;
};

Sonar::Sonar(byte num, byte echo, byte trig) {
  this->num = num;
  this->echo = echo;
  this->trig = trig;
  this->sonar = new NewPing(trig, echo, this->max_distance);
}

boolean Sonar::checkActivation() {
  if (isRestorating) {
    current_elapsed_time += tick_duration;

    if (current_elapsed_time > restoration_time) {
      isRestorating = false;
      current_elapsed_time = 0;
    }
    
    return false;
  }
  
  unsigned int dist = sonar->ping() / 58;

  pinMode(echo,OUTPUT);  
  digitalWrite(echo,LOW);  
  pinMode(echo,INPUT);

  if (current_elapsed_time < time_to_activation_check) {
    distance_sum += dist;
    current_elapsed_time += tick_duration;
  }
  else {
    int ticks_to_activation_check = time_to_activation_check / tick_duration;
    float distance_mean = distance_sum / ((float)ticks_to_activation_check);
    
    //Serial.print(this->num);
    //Serial.print(" -- ");
    //Serial.println(distance_mean);

    if (abs(distance_mean - 150) > activation_distance_delta) {
      isRestorating = true;
      distance_sum = 0;
      return true;
    }

    distance_sum = 0;
    current_elapsed_time = 0;
  }

  return false;
}

//byte dir = 0; //1 - in, 2 - out
boolean son1_was_active = false;
boolean son2_was_active = false;

Sonar son1(1, echo_1, trig_1);
Sonar son2(2, echo_2, trig_2);

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(tick_duration);

  boolean son1_activated = son1.checkActivation();
  boolean son2_activated = son2.checkActivation();
  
  if (son1_activated) {
    if (son2_was_active) {
      Serial.println("Action: Out");
      son2_was_active = false;
    }
    else {
      son1_was_active = true;
    }
  }

  if (son2_activated) {
    if (son1_was_active) {
      Serial.println("Action: In");
      son1_was_active = false;
    }
    else {
      son2_was_active = true;
    }
  }
  /*if (son1_activated && son2_activated) {
    unsigned int delta = dist2 - dist1;
    dir = delta < 0 ? 2 : 1;
  }

  if (dist1 < activation_distance) {
    if (dir == 0) {
      dir = 1;
    }
    else if (dir == 2) {
      //Serial.println("Action: Out");
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
      //Serial.println("Action: In");
      dir = 0;
    }
  }
  else {
    if (dir == 2) {
      dir = 0;  
    }
  }*/
}

void enableLight() {
  digitalWrite(led, HIGH);
}

void disableLight() {
  digitalWrite(led, LOW);
}
