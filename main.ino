//arm_top: 68
//reduktion klein: 33 groß: 61
//arm_hub: 62

#define joyZ A8
#define joyX A9
#define joyY A10

#define stepX 2
#define dirX 5

#define stepY 3
#define dirY 6

#define stepZ 4
#define dirZ 7

const int delayMS = 500;

const int min_joy = 450;
const float joySpeed = 0.01;

int arm[3] = {90, 105, 80}; //länge der Arme in mm
const float pi = 3.1416;

kartkoord xysoll;

struct kartkoord{
 int x;  //x in mm
 int y;  //y in mm
};

struct zylkoord{
  int p;  //Abstand in mm
  float delta;  //Winkel in radiant
};

zylkoord kart2zyl(kartkoord kn)
{
  zylkoord zylinder;
  zylinder.p = sqrt(kn.x^2 + kn.y^2);
  zylinder.delta = atan( kn.y / kn.x);
  return zylinder;
}

int rad2deg(float winkel[4]){
  return {(int) winkel[0] * 180 / pi, 
    (int) winkel[1] * 180 / pi, 
    (int) winkel[2] * 180 / pi, 
    (int) winkel[3] * 180 / pi};
}

int deg2rot(int[2] degsoll) {
  return {(int) degsoll[0] / 360, (int) degsoll[0] / 360};
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
}

void loop() {
  float[3] input = getInput();
  xysoll.x += input[0] * joySpeed;
  xysoll.y += input[1] * joySpeed;

  // alles berechnen
  float[4] alphasoll = calculate(xysoll);
  
  int[4] degsoll = rad2deg(alphasoll); // zu 360° System umrechnen
  
  moveMotors(degsoll);
}

void moveMotors(int degsoll) {
  int[2] rotationsoll = deg2rot({degsoll[0], degsoll[1]}); // benögtigte Umdrehungen berechnen

  int[2] stepsNeeded = {rotationsoll[0] * 200, rotationsoll[1] * 200};
}

float[3] getInput() {
  float x = (analogRead(joyX) - 511) / 511; // links/rechts  -1 <-> 1
  float y = (analogRead(joyY) - 511) / 511; // hinten/vorne -1 <-> 1
  float z = (analogRead(joyZ) - 511) / 511; // oben, unten -1 <-> 1
  float[3] input = {x, y, z};
  return input;
}

float[4] calculate(kartkoord xysoll) {
  float sollwinkel = 0;
  zylkoord zylsoll = kart2zyl(xysoll);
  
  float alphasoll[4]; // von innen nach außen
  
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

  alphasoll[0]= zylsoll.delta + acos((zylsoll_ohne_ext.p^2 + arm[0]^2 - arm[1]^2) / 2 * arm[1] * zylsoll_ohne_ext.p);
  alphasoll[1]= acos((arm[1]^2 + arm[0]^2 - zylsoll_ohne_ext.p^2) / 2 * arm[1] * arm[0]);
  alphasoll[2] += pi - alphasoll[1] - alphasoll[0];

  return alphasoll;
}
