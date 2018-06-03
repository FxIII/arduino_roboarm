#include "arm.h"
#include "pwm.h"
Arm::Arm() : pwm() {
  this->dbg = NULL;
  values[0] = 200; // S base left/right
  values[1] = 100; // L base forward/backword
  values[2] = 240; // U forearm raise/lower
  values[3] = 360; // R wrist roll (?check)
  values[4] = 200; // B wrist up/down (?check)
  values[5] = 200; // claw
}

void Arm::refresh() {
  for (int i = 0; i < 6; i++) {
    this->pwm.set(i, this->values[i]);
  }
}

void Arm::dump(uint8_t addr) {
  if (this->dbg) {
    this->dbg->print("\033[2J\033[H");
    for (int i = 0; i < 6; i++) {
      this->dbg->println(
        ((addr == i) ? "*" : " ") +
        String(i) + " pulse: " + String(values[i]));
    }
  }
}

