#include <Wire.h>

const int MPU = 0x68;

int16_t AcX, AcY, AcZ;

/******** BUTTON PINS ********/
#define RIGHT_BUTTON 7
#define LEFT_BUTTON  9
/*****************************/

/******** SETTINGS ********/
float forwardThreshold = 0.6;
float backwardThreshold = -0.6;
float sideThreshold = 0.6;
/**************************/

bool leftClick=false;
bool rightClick=false;
bool goBack=false;
bool goForward=false;

int circleStage=0;
bool runGesture=false;

void setup() {

  Serial.begin(9600);
  Wire.begin();

  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);

  // Wake MPU6050
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {

  /* ===== READ MPU ===== */
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);

  AcX = Wire.read()<<8 | Wire.read();
  AcY = Wire.read()<<8 | Wire.read();
  AcZ = Wire.read()<<8 | Wire.read();

  float ax = AcX / 16384.0;
  float ay = AcY / 16384.0;

  /* ===== BUTTON STATES ===== */
  bool rightBtn = digitalRead(RIGHT_BUTTON)==LOW;
  bool leftBtn  = digitalRead(LEFT_BUTTON)==LOW;

  /* ===== CLICK FROM GESTURE OR BUTTON ===== */
  if(ax > forwardThreshold || leftBtn){
      leftClick=true;
      rightClick=false;
  }
  else if(ax < backwardThreshold || rightBtn){
      rightClick=true;
      leftClick=false;
  }
  else{
      leftClick=false;
      rightClick=false;
  }

  /* ===== SIDE PUSH ===== */
  if(ay < -sideThreshold){
      goBack=true;
      goForward=false;
  }
  else if(ay > sideThreshold){
      goForward=true;
      goBack=false;
  }
  else{
      goBack=false;
      goForward=false;
  }

  /* ===== CIRCLE DETECTION ===== */
  if(circleStage==0 && ay>0.7) circleStage=1;
  else if(circleStage==1 && ax>0.7) circleStage=2;
  else if(circleStage==2 && ay<-0.7) circleStage=3;
  else if(circleStage==3 && ax<-0.7){
      runGesture=true;
      circleStage=0;
  }

  /* ===== SEND DATA ===== */
  Serial.print("X:");
  Serial.print(ax,2);
  Serial.print(",");

  Serial.print("Y:");
  Serial.print(ay,2);
  Serial.print(",");

  Serial.print("LC:");
  Serial.print(leftClick?0:1);
  Serial.print(",");

  Serial.print("RC:");
  Serial.print(rightClick?0:1);
  Serial.print(",");

  Serial.print("GB:");
  Serial.print(goBack?0:1);
  Serial.print(",");

  Serial.print("GF:");
  Serial.print(goForward?0:1);
  Serial.print(",");

  Serial.print("RUN:");
  Serial.println(runGesture?0:1);

  runGesture=false;

  delay(150);
}