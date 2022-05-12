#define STICKX A0





int stepCounter;
int steps = 10000;
int delayMS = 500;

int NUM_STEPPER = 3;
int stepPins[] = {2, 3, 4}; //x, y, z
int richtungPins[] = {5, 6, 7}; //x, y, z

void setup() {
  for(int i; i < NUM_STEPPER; i++) {
    pinMode(stepPins[i], OUTPUT);
    pinMode(richtungPins[i], OUTPUT);
  }
}

void loop()
{

  if(analogRead(STICKX) >= 800)
  {
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
 
  else if(analogRead(STICKX) <= 300)
  {
  
  }

  
    
    }

  



  
  tick_stepper();
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
  

}
