#pragma once
#include <stdint.h>
#include "pwm.h"
class Arm {
  private:
    PWM pwm;
    Stream * dbg;
  public:
    uint16_t values[6];
    Arm();
    void refresh();
    void dump(uint8_t addr);
    void setDebug(Stream * dbg) {
      this->dbg = dbg;
    }
    bool incr(uint8_t addr, uint16_t val) {
      values[addr] += val;
      return true;
    }
};

