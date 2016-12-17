// ---------------------------------------------------------------------------
// Arduino L298N Library - v1.0 - 12/16/2016
//
// AUTHOR/LICENSE:
// Created by Alonso José Lara Plana - alonso.lara.plana@gmail.com
// Based on Yohendry Hurtado L298N library
// Copyright 2016 License: GNU GPL v3 http://www.gnu.org/licenses/gpl.html
//
// LINKS:
// Project home: https://github.com/AlonsoLP/Arduino-L298N-Library
// Yohendry Hurtado L298N library: https://github.com/yohendry/arduino_L298N
//
// DISCLAIMER:
// This software is furnished "as is", without technical support, and with no
// warranty, express or implied, as to its usefulness for any purpose.
//
// BACKGROUND:
// When I received a L298N Dual H-Bridge I started using Yohendry library and
// it worked fine from the beginning. But there are some lacks like no brake,
// no direction correction, no turn radius... The L298N library fixes these
// lacks and adds new features.
//
// FEATURES:
// * Stops vehicle with/without brakes.
// * Trajectory correction and turn ratio, giving custom speed to each motor
//   independently (see turn method)
//
// CONSTRUCTOR:
//   L298N driver(ena, in1, in2, in3, in4, enb [, minspeed]);
//     ena      - Enable/Disable MOTOR_A
//     in1/2    - Controls MOTOR_A
//     in3/4    - Controls MOTOR_B
//     enb      - Enable/Disable MOTOR_B
//     minspeed - [Optional] Minimum speed motors can handle before stop. Default=0, Recommended=50.
//
// METHODS:
//   driver.move([direction [, speed [, delay_time]]]) - Move vehicle to direction (FORWARD/BACKWARD) at defined speed and waits delay_time milliseconds (no stop when finish).
//   driver.turn(direction [, speed [, slave_percent [, delay_time]]]) - Turn vehicle to direction (LEFT/RIGHT), setting master motor to defined speed and slave motor to slave_percent and waits delay_time. If master is 160 and slave_percent 50, the slave motor speed is 80 (160*50/100). slave_percent goes from -100 to 100.
//   driver.stop([brake [, delay_time]]) - Stop vehicle (using brakes if brake is true) and waits delay_time before brakes are released.
//
//
// HISTORY:
// 12/16/2016 v1.0 - Initial release.
// ---------------------------------------------------------------------------

#ifndef L298N_h
#define L298N_h

#include "Arduino.h"

class L298N
{
  public:
    static const uint8_t LEFT = 0, RIGHT = 1, BACKWARD = 0, FORWARD = 1;
    L298N(uint8_t ena, uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t enb, uint8_t minspeed = 0);
    void move(uint8_t direction = 1, uint8_t speed = 255, int delay_time = 0);
    void turn(uint8_t direction, uint8_t speed = 255, short slave_percent = 0, int delay_time = 0);
    void stop(boolean brake = true, int delay_time = 0);
  private:
    void setup_motor(uint8_t motor_index, uint8_t in1, uint8_t in2);
};

#endif

