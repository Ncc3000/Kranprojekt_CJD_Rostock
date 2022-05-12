int delayMS = 500;

int NUM_STEPPER = 3;
int stepPins[] = {2, 3, 4}; //x, y, z
int richtungPins[] = {5, 6, 7}; //x, y, z
bool steps[] = {false, false, false};
bool conn = false;
String data;

void setup() {
  for(int i; i < NUM_STEPPER; i++) {
    pinMode(stepPins[i], OUTPUT);
    pinMode(richtungPins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  tick_data();
  tick_stepper();
}

void tick_data() {
  // empfängt daten von computer und ändert dem entsprechend variablen
}

void tick_stepper() {
  digitalWrite(richtungPins[0],HIGH); // im Uhrzeigersinn
  digitalWrite(richtungPins[1],HIGH);
  digitalWrite(richtungPins[2],HIGH);
  for(stepCounter = 0;  stepCounter < steps; stepCounter++) {
    digitalWrite(stepPins[0],HIGH);
    digitalWrite(stepPins[1],HIGH);
    digitalWrite(stepPins[2],HIGH);
    delayMicroseconds(delayMS);
    digitalWrite(stepPins[0],LOW);
    digitalWrite(stepPins[1],LOW);
    digitalWrite(stepPins[2],LOW);
    delayMicroseconds(delayMS);
  }

  delay(1000);
  digitalWrite(richtungPins[0],LOW); // gegen den Uhrzeigersinn
  digitalWrite(richtungPins[1],LOW);
  digitalWrite(richtungPins[2],LOW);
  for(stepCounter = 0;  stepCounter < steps; stepCounter++) {
    digitalWrite(stepPins[0],HIGH);
    digitalWrite(stepPins[1],HIGH);
    digitalWrite(stepPins[2],HIGH);
    delayMicroseconds(delayMS);
    digitalWrite(stepPins[0],LOW);
    digitalWrite(stepPins[1],LOW);
    digitalWrite(stepPins[2],LOW);
    delayMicroseconds(delayMS);
  }
  delay(1000);
}