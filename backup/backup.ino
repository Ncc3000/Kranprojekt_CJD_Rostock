#include <Servo.h>

//arm_top: 68
//reduktion klein: 33 groß: 61
//arm_hub: 62

#define joyZ A8
#define joyX A9
#define joyY A10
#define joyS A11

#define stepX 2
#define dirX 5

#define stepY 3
#define dirY 6

#define stepZ 4
#define dirZ 7


int delayMS = 450;

int min_joy = 400;

float z;
float x;
float y;
float s;

Servo servo1;
Servo servo2;
int servoGrad1 = 90;
int servoGrad2 = 90;

int delayServo = 0;


void setup() {
  pinMode(stepX, OUTPUT);
  pinMode(stepY, OUTPUT);
  pinMode(stepZ, OUTPUT);

  pinMode(dirX, OUTPUT);
  pinMode(dirY, OUTPUT);
  pinMode(dirZ, OUTPUT);

  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);
  pinMode(joyZ, INPUT);
  pinMode(joyS, INPUT);


  servo1.attach(42);
  servo2.attach(32);
  servo1.write(servoGrad1);
  servo2.write(servoGrad2);
}

void loop() {
  tick();
}

void tick() {
  x = analogRead(joyX) - 511; // links/rechts
  y = analogRead(joyY) - 511; // hinten/vorne
  z = analogRead(joyZ) - 511; // oben, unten
  s = analogRead(joyS) - 511;
  servoGrad2 = map(analogRead(12), 0, 1023, 0, 180);

  if (z >= min_joy) {
    digitalWrite(dirZ, HIGH);
    digitalWrite(stepZ, HIGH);
  }
  else if (z <= -min_joy) {
    digitalWrite(dirZ, LOW);
    digitalWrite(stepZ, HIGH);
  }
  
  if (x >= min_joy) {
    digitalWrite(dirX, HIGH);
    digitalWrite(stepX, HIGH);
  }
  else if (x <= -min_joy) {
    digitalWrite(dirX, LOW);
    digitalWrite(stepX, HIGH);
  }

  if (y >= min_joy) {
    digitalWrite(dirY, HIGH);
    digitalWrite(stepY, HIGH);
  }
  else if (y <= -min_joy) {
    digitalWrite(dirY, LOW);
    digitalWrite(stepY, HIGH);
  }

  if (s >= min_joy and delayServo <= 0 and servoGrad1 <= 179) {
    servoGrad1++;
    delayServo = 8;
  } else if ( s <= -min_joy and delayServo <= 0 and servoGrad1 >= 1) {
    servoGrad1--;
    delayServo = 8;
  } else {
    delayServo--;
  }


  servo1.write(servoGrad1);
  servo2.write(servoGrad2);

  delayMicroseconds(delayMS);
  
  digitalWrite(stepZ, LOW);
  digitalWrite(stepX, LOW);
  digitalWrite(stepY, LOW);
}
