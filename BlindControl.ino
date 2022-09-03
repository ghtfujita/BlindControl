#include <Stepper.h>
const int stepsPerRev = 2048;

const int motorPin[] = {6, 7, 8, 9};
const int cdsPin = A1;

const int cdsMin = 0;
const int cdsMax = 1000;
const int revRange = 6; //# rotations from close to open

/*
 * relCds 0(暗)   100(明)
 * relPos 0(閉)   100(開)
 */

Stepper motor(stepsPerRev, motorPin[0], motorPin[2], motorPin[1], motorPin[3]); 

int posNow = 0;
int posTarget = 0;

void setup() {
	motor.setSpeed(15);
  pinMode(cdsPin, INPUT);

  Serial.begin(9600);
  delay(2000);
  Serial.println("system started.");
}

void loop() {
  int cds = -analogRead(cdsPin);
  if ( cds > cdsMax ) cds = cdsMax;
  else if ( cds < cdsMin ) cds = cdsMin;
  Serial.print("cds:"); Serial.print(cds); Serial.print(" ");

  int relCds = map(cds, cdsMin, cdsMax, 0, 100);
  Serial.print("relCds:"); Serial.print(relCds); Serial.print(" ");

  posTarget = cdsToTarget(relCds);
  Serial.print("posTarget:"); Serial.print(posTarget); Serial.print(" ");

  int movt = posTarget - posNow;
  Serial.print("movt:"); Serial.print(movt); Serial.print(" ");
  motor.step(movt);
  motorStop();
  posNow = posTarget;
}

int cdsToTarget(int i) {
  int target;
  target = map(100 - i, 0, 100, 0, revRange * stepsPerRev);
  return target;
}

void motorStop() {
  for (int i = 0; i < 4; i++) digitalWrite(motorPin[i], LOW);
}
