#include <swDuino.h>
#include <IRremote.h>

swDuino objswDuino;

const int low_duration = 520;
const int high_duration = 1100;

IRsend irsend;
unsigned int receivedCommand[197];


void setup() {
  Serial.begin(9600);
}

void loop() {
  objswDuino.read(trigger);  
}

void trigger(String VARIABLE, String VALUE) {
  if (VARIABLE == "ss_command")
  {
    generateCommand(VALUE);
    for (int i = 0; i < 3; i++) {
      irsend.sendRaw(receivedCommand, 197, 38);
      delay(10);
    }
  }
}

void generateCommand(String binCom) {
  receivedCommand[0] = 3040;
  receivedCommand[1] = 4460;
  
  for(int i = 0; i < binCom.length(); i++) {
    receivedCommand[i * 2 + 2] = low_duration;
    receivedCommand[i * 2 + 3] = low_duration + ((unsigned int) (binCom.charAt(i) - '0')) * high_duration;
  }
}
