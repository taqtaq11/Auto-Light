#include <swDuino.h>
#include <IRremote.h>

swDuino objswDuino;

IRsend irsend;
unsigned int enableRawCodes[197] = {3040, 4460, 540, 580, 600, 1620, 580, 560, 580, 1660, 580, 540, 580, 1660, 580, 560, 560, 1680, 560, 560, 580, 1660, 600, 1640, 580, 540, 580, 560, 580, 540, 580, 560, 600, 520, 580, 560, 580, 540, 600, 540, 560, 560, 580, 560, 560, 1680, 560, 1660, 600, 540, 600, 520, 580, 560, 600, 520, 600, 540, 580, 540, 600, 540, 600, 520, 580, 560, 580, 1660, 580, 540, 580, 560, 580, 540, 600, 520, 580, 1660, 600, 540, 600, 520, 600, 540, 560, 560, 600, 540, 580, 540, 600, 540, 580, 540, 580, 540, 600, 1640, 600, 540, 600, 520, 600, 1640, 580, 560, 580, 1640, 600, 540, 600, 1640, 600, 520, 600, 540, 600, 520, 600, 520, 620, 520, 600, 520, 620, 520, 580, 540, 620, 520, 600, 520, 580, 560, 600, 520, 600, 540, 600, 520, 600, 540, 600, 520, 600, 520, 620, 520, 600, 520, 620, 520, 600, 520, 620, 520, 560, 560, 600, 540, 600, 520, 600, 540, 600, 520, 600, 540, 600, 520, 600, 520, 620, 520, 580, 540, 620, 520, 600, 1640, 600, 520, 600, 1640, 600, 540, 600, 520, 600, 540, 600, 520, 600, 520, 600, 540, 600};
unsigned int disableRawCodes[197] = {3080, 4400, 600, 520, 620, 1620, 620, 520, 600, 1640, 600, 520, 600, 1640, 600, 540, 600, 1640, 580, 540, 600, 1640, 600, 1640, 600, 520, 600, 540, 600, 520, 600, 540, 580, 540, 600, 540, 580, 540, 600, 540, 580, 540, 600, 540, 580, 1640, 600, 1640, 600, 540, 600, 520, 600, 540, 580, 540, 600, 540, 580, 540, 600, 520, 600, 540, 600, 520, 600, 1640, 600, 540, 600, 520, 600, 540, 600, 520, 600, 1640, 600, 520, 600, 540, 600, 520, 600, 540, 600, 520, 600, 540, 600, 520, 600, 540, 600, 1620, 620, 520, 600, 520, 620, 520, 600, 1640, 600, 520, 600, 1640, 600, 540, 600, 1620, 620, 520, 600, 520, 620, 520, 600, 520, 600, 540, 600, 520, 600, 540, 600, 520, 600, 540, 600, 520, 600, 540, 580, 540, 600, 520, 600, 540, 600, 520, 600, 540, 600, 520, 600, 540, 600, 520, 600, 540, 580, 540, 600, 540, 580, 540, 600, 540, 580, 540, 600, 520, 600, 540, 600, 520, 600, 540, 600, 520, 600, 540, 600, 520, 600, 540, 580, 1660, 580, 540, 600, 1640, 600, 540, 580, 540, 600, 520, 600, 1640, 600, 1640, 600, 540, 580};


void setup() {
  Serial.begin(9600);
}

void loop() {
  objswDuino.read(trigger);
}

void trigger(String VARIABLE, String VALUE) {
  if (VARIABLE == "split_mode")
  {
    if (VALUE == "0")
    {
      disableSplitSystem();
    }
    else if (VALUE == "1")
    {
      enableSplitSystem();
    }
  }
}

void enableSplitSystem() {
  for (int i = 0; i < 3; i++) {
    irsend.sendRaw(enableRawCodes, 197, 38);
    delay(10);
  }
}

void disableSplitSystem() {
  for (int i = 0; i < 3; i++) {
    irsend.sendRaw(disableRawCodes, 197, 38);
    delay(10);
  }
}
