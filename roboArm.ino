/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815
  
  These drivers use I2C to communicate, 2 pins are required to  
  interface.

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include "arm.h"
#include "serialArmHandler.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  110 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  480 // this is the 'maximum' pulse length count (out of 4096)


// our servo # counter
uint8_t servonum = 0;
short int values[6];
int addr=0;

Arm bot;
SerialHandler  handler(&bot);

void setup(){
  Serial.begin(9600);
  bot.setDebug(&Serial);
  delay(10);
}

void ssetup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(50);  // Analog servos run at ~60 Hz updates
  values[0] = 200;
  values[1] = 100;
  values[2] = 240;
  values[3] = 360;
  values[4] = 200;
  values[5] = 200;
  delay(10);
}
void apply(){
  Serial.print("\033[2J\033[H");
  for (int i=0; i <6;i++){
    pwm.setPWM(i,0,values[i]);
    Serial.println(
      ((addr == i) ? "*" : " ") + 
      String(i)+" pulse: "+String(values[i]));
  }
}

void incr(int addr, int val){
  values[addr]+=val;
}

// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void loop(){
  handler.loop();
}
  
void sloop(){
  char c;
  if (Serial.available() > 0){
    c = Serial.read();
    if (c== '0') addr=0;
    if (c== '1') addr=1;
    if (c== '2') addr=2;
    if (c== '3') addr=3;
    if (c== '4') addr=4;
    if (c== '5') addr=5;
    if (c== '6') addr=6;
    if (c== 'q') incr(addr,+50);
    if (c== 'w') incr(addr,-50);
    if (c== 'a') incr(addr,+10);
    if (c== 's') incr(addr,-10);
    if (c== 'z') incr(addr,+5);
    if (c== 'x') incr(addr,-5);
    apply();
  }
}

void oloop() {
  // Drive each servo one at a time
  Serial.println(servonum);
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
    pwm.setPWM(servonum, 0, pulselen);
    delay(10);
  }

  delay(500);
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
    pwm.setPWM(servonum, 0, pulselen);
    delay(10);
  }

  delay(500);

  servonum ++;
  if (servonum > 7 ) servonum = 0;
}
