//arm_top: 68
//reduktion klein: 33 groß: 61
//arm_hub: 62
#include "math.h"

#define joyZ A8
#define joyX A9
#define joyY A10

#define stepX 2
#define dirX 5

#define stepY 3
#define dirY 6

#define stepZ 4
#define dirZ 7

int stepsMoved[2];

const int delayMS = 500;

const int min_joy = 450;
const float joySpeed = 1.0;

double alphasoll[4];

int arm[3] = {90, 105, 80}; //länge der Arme in mm
const double pi = 3.1416;

struct kartkoord{
 double x;  //x in mm
 double y;  //y in mm
};

struct zylkoord{
  double p;  //Abstand in mm
  double delta;  //Winkel in radiant
};

kartkoord xysoll;

zylkoord kart2zyl(kartkoord kn)
{
  zylkoord zylinder;
  zylinder.p = sqrt(sq(kn.x) + sq(kn.y));
  zylinder.delta = atan( ((double) kn.y) / kn.x);
  return zylinder;
}

int deg2rot(int degsoll[2]) {
  int value[] = {(int) degsoll[0] / 360, (int) degsoll[0] / 360};
  return value;
}

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

  xysoll.x = 0; xysoll.y = 0;

  Serial.begin(9600);
}

void loop() {

  xysoll.x += round((analogRead(joyX) - 511.0) / 511.0) * joySpeed;
  xysoll.y += round((analogRead(joyY) - 511.0) / 511.0) * joySpeed;
  Serial.print(xysoll.x);
 Serial.print(" ");
   Serial.print(xysoll.y);
  Serial.print(" ");

  // alles berechnen
  calculate(xysoll);
  
  Serial.print(alphasoll[0]);
  Serial.print(" ");
  Serial.print(alphasoll[1]);
  Serial.print(" ");
  Serial.print(alphasoll[2]);
  Serial.print(" ");
  Serial.print(alphasoll[3]);
  Serial.print("\n");
  
  int degsoll[4] = {(int) (alphasoll[0] * 180 / pi), 
    (int) (alphasoll[1] * 180 / pi), 
    (int) (alphasoll[2] * 180 / pi), 
    (int) (alphasoll[3] * 180 / pi)}; // zu 360° System umrechnen
  
  moveMotors(degsoll, round((analogRead(joyZ) - 511.0) / 511.0));
}

void moveMotors(int degsoll[], float moveZ) {
  
  int stepsNeeded[] = {degsoll[0] / 1.8, degsoll[1] / 1.8}; // rechne von umdrehungen zu steps
  stepsNeeded[0] -= stepsMoved[0]; // ziehe die bereits bewegten Schritte ab
  stepsNeeded[1] -= stepsMoved[1];

  if (stepsNeeded[0] == 0) {}
  else if (stepsNeeded[0] < 0) {
    digitalWrite(dirX, HIGH); // im uhrzeigersinn
  }
  else if (stepsNeeded[0] > 0) {
    digitalWrite(dirX, LOW); // gegen uhrzeigersinn
  }
  
  if (stepsNeeded[1] == 0) {}
  else if (stepsNeeded[1] < 0) {
    digitalWrite(dirY, HIGH); // gegen den Uhrzeigersinn
  }
  else if (stepsNeeded[1] > 0) {
    digitalWrite(dirY, LOW); // im Uhrzeigersinn
  }

  if (moveZ == 0) {}
  else if (moveZ > 0) {
    digitalWrite(dirZ, HIGH);
  }
  else if (moveZ < 0) {
    digitalWrite(dirZ, LOW);
  }
  
  stepsNeeded[0] = abs(stepsNeeded[0]);
  stepsNeeded[1] = abs(stepsNeeded[1]);
  
  while (stepsNeeded[0] != 0 and stepsNeeded[1] != 0) {
    if (abs(moveZ) > 0) {
      digitalWrite(stepZ, HIGH);
    }
    
    if (stepsNeeded[0] == 0) {}
    else {
      digitalWrite(stepX, HIGH);
      stepsMoved[0]++;
      stepsNeeded[0]--;
    }

    if (stepsNeeded[1] == 0) {}
    else {
      digitalWrite(stepY, HIGH);
      stepsMoved[1]++;
      stepsNeeded[1]--;
    }

    delayMicroseconds(delayMS * 3);
    
    digitalWrite(stepX, LOW);
    digitalWrite(stepY, LOW);
    digitalWrite(stepZ, LOW);
    
    delayMicroseconds(delayMS * 3);
  }
}

void calculate(kartkoord xysoll) {
  double sollwinkel = 0.0;
  zylkoord zylsoll = kart2zyl(xysoll);

  
  zylkoord zylsoll_ohne_ext; // ohne externen Arm
  zylsoll_ohne_ext.delta = zylsoll.delta;

  if (zylsoll.p > arm[0]+arm[1]){
    zylsoll_ohne_ext.p = zylsoll.p - arm[2];
    alphasoll[2] = zylsoll.delta;  
    alphasoll[3] = sollwinkel - zylsoll.delta;
  }
  else
  {
    zylsoll_ohne_ext.p = zylsoll.p + arm[2];
    alphasoll[2] = zylsoll.delta + pi;
    alphasoll[3] = sollwinkel - zylsoll.delta + pi;
  }

  alphasoll[0]= ( sq(arm[0]) + sq(zylsoll_ohne_ext.p) - sq(arm[1])) / (2 * arm[1] * zylsoll_ohne_ext.p);
  alphasoll[1]= acos((sq(arm[1]) + sq(arm[0]) - sq(zylsoll_ohne_ext.p)) / (2 * arm[1] * arm[0]));
  alphasoll[2] += pi - alphasoll[1] - alphasoll[0];

  return alphasoll;
}
