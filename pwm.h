#pragma once
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class PWM {
  private:
    Adafruit_PWMServoDriver pwm;
  public:
    PWM(): pwm() {
      this->pwm.begin();
      this->pwm.setPWMFreq(50);
    }
    void set(uint8_t num, uint16_t off) {
      this->pwm.setPWM(num, 0, off);
    }
};

