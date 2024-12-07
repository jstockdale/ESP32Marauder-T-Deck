#pragma once

#ifndef Trackball_h
#define Trackball_h

#include "configs.h"

#define TRACKBALL_UP 0
#define TRACKBALL_DOWN 1
#define TRACKBALL_LEFT 2
#define TRACKBALL_RIGHT 3
#define TRACKBALL_ANY 4
  // 0 - Up
  // 1 - Down
  // 2 - Left
  // 3 - Right
  // 4 - Any

class Trackball {
  private:
  public:
    Trackball();
    bool menuPress(int button);
};

#endif
