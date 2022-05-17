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

int delayMS = 500;

int min_joy = 450;

float z;
float x;
float y;

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
}

void loop() {
  tick();
}

void tick() {
  x = analogRead(joyX) - 511; // links/rechts
  y = analogRead(joyY) - 511; // hinten/vorne
  z = analogRead(joyZ) - 511; // oben, unten

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

  delayMicroseconds(delayMS);
  digitalWrite(stepZ, LOW),
  delayMicroseconds(delayMS * 2);
  digitalWrite(stepY, LOW);
  delayMicroseconds(delayMS);
  digitalWrite(stepX, LOW);
}
