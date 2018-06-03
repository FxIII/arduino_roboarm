#pragma once
#include "arm.h"
class SerialHandler {
    Arm * arm;
    uint8_t addr;
  public:
    SerialHandler(Arm *arm) {
      this->arm = arm;
      this->addr = 0;
    }
    void loop() {
      char c;
      if (Serial.available() > 0) {
        c = Serial.read();
        if (c == '0') addr = 0;
        if (c == '1') addr = 1;
        if (c == '2') addr = 2;
        if (c == '3') addr = 3;
        if (c == '4') addr = 4;
        if (c == '5') addr = 5;
        if (c == '6') addr = 6;
        if (c == 'q') arm->incr(addr, +50);
        if (c == 'w') arm->incr(addr, -50);
        if (c == 'a') arm->incr(addr, +10);
        if (c == 's') arm->incr(addr, -10);
        if (c == 'z') arm->incr(addr, +5);
        if (c == 'x') arm->incr(addr, -5);
        arm->refresh();
        arm->dump(addr);
      }
    }
};

