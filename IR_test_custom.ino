// ИК-приемник подключить к Digital Pin-02 на MEGA или Duemilanove
// Кнопку начала сканирования подключить между землей и Digital Pin-04

// Arduino Mega
#if defined(__AVR_ATmega2560__)
#define IRpin_PIN PINE
#define IRpin 4
// Arduino Duemilanove
#else
#define IRpin_PIN PIND
#define IRpin 4
#endif

#define MAXPULSE 65000
#define RESOLUTION 20 // Timing resolution 

int buttonPin = 4;
int buttonState = 0;        
uint16_t pulses[200][2]; // 100 pairs standart
uint8_t currentpulse = 0;
uint8_t sendpulse = 0;

void setup(void){
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);  
  Serial.begin(9600);
  Serial.println("\nPress Receive key...");
};

void loop(void){
  buttonState = digitalRead(buttonPin);
    uint16_t highpulse, lowpulse;
    highpulse = lowpulse = 0;
    while (IRpin_PIN & (1 << IRpin))
      {
      highpulse++;
      delayMicroseconds(RESOLUTION);
      if ((highpulse >= MAXPULSE) && (currentpulse != 0))
        {
        printpulses();
        sendpulse=currentpulse;
        currentpulse=0;
        return;
        }
      }
    pulses[currentpulse][0] = highpulse;
    while (! (IRpin_PIN & _BV(IRpin)))
      {
      // pin is still LOW
      lowpulse++;
      delayMicroseconds(RESOLUTION);
      if ((lowpulse >= MAXPULSE) && (currentpulse != 0))
        {
        printpulses();
        sendpulse=currentpulse;
        currentpulse=0;
        return;
        }
      }
    pulses[currentpulse][1] = lowpulse;
    currentpulse++;
};

void printpulses(void){
  Serial.println("\nReceived:");
  Serial.print("\nunsigned int IRsignal[");
  Serial.print(currentpulse*2-1);
  Serial.print("] = {");
  for (uint8_t i = 0; i < currentpulse-1; i++)
    {
    Serial.print(pulses[i][1] * RESOLUTION, DEC);
    Serial.print(", ");
    Serial.print(pulses[i+1][0] * RESOLUTION, DEC);
    Serial.print(", ");
    }
  Serial.print(pulses[currentpulse-1][1] * RESOLUTION, DEC);
  Serial.print("};");
  Serial.println("");
};

