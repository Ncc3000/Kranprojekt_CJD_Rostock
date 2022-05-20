int arm[3] = {90, 105, 80}; //länge der Arme in mm
const float pi = 3.1416;

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

int rad2deg(float winkel){
  return (int) winkel * 180 / pi;
  }

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

//rechne von sollkoordinaten rückwärts...
kartkoord xysoll;
xysoll.x = 100; xysoll.y = 100; 
int zsoll = 0 ; 
float sollwinkel = 0;

//umrechnen in zylinderkoordinaten:
zylkoord zylsoll=kart2zyl(xysoll);

//Sollwinkel von innen nach aussen
float alphasoll[4];

//Berechnung zylinderkoordinaten ohne externen Arm
zylkoord zylsoll_ohne_ext;
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
 
}
