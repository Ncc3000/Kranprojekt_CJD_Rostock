#define joyZ A8
#define joyX A11
#define joyY A10

int delayMS = 480;
int delayRamp = 20;
int stepCounter = 0;

int NUM_STEPPER = 3;
int stepPins[] = {2, 3, 4}; //x, y, z
int richtungPins[] = {5, 6, 7}; //x, y, z
long steps = 4000;

float z;
float x;
float y;

void setup() {
  for(int i; i < NUM_STEPPER; i++) {
    pinMode(stepPins[i], OUTPUT);
    pinMode(richtungPins[i], OUTPUT);
  }
  pinMode(joyZ, INPUT);
  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);
  Serial.begin(9600);
}

void loop() {
  tick();
}

void tick() {
  // empfängt daten von den joysticks und ändert dem entsprechend variablen
  z = analogRead(joyZ)-(1024/2-13);
  x = analogRead(joyX)-(1024/2-13);
  y = analogRead(joyY)-(1024/2-13);
  if (z >= 100) {
    digitalWrite(richtungPins[0],HIGH); // im Uhrzeigersinn
    digitalWrite(richtungPins[1],HIGH);
    digitalWrite(richtungPins[2],HIGH);

    digitalWrite(stepPins[0],HIGH);
    digitalWrite(stepPins[1],HIGH);
    digitalWrite(stepPins[2],HIGH);
    delayMicroseconds(delayMS);
    digitalWrite(stepPins[0],LOW);
    digitalWrite(stepPins[1],LOW);
    digitalWrite(stepPins[2],LOW);
    delayMicroseconds(delayMS);
  }
  else if (z <= -100) {
    digitalWrite(richtungPins[0],LOW); // gegen den Uhrzeigersinn
    digitalWrite(richtungPins[1],LOW);
    digitalWrite(richtungPins[2],LOW);

    digitalWrite(stepPins[0],HIGH);
    digitalWrite(stepPins[1],HIGH);
    digitalWrite(stepPins[2],HIGH);
    delayMicroseconds(delayMS);
    digitalWrite(stepPins[0],LOW);
    digitalWrite(stepPins[1],LOW);
    digitalWrite(stepPins[2],LOW);
    delayMicroseconds(delayMS);
  }
}
