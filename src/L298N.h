// ---------------------------------------------------------------------------
// Arduino L298N Library (v1.21)
//
// AUTHOR/LICENSE:
// Created by Alonso José Lara Plana - alonso.lara.plana@gmail.com
// Copyright 2016 License: GNU GPL v3 http://www.gnu.org/licenses/gpl.html
//
// LINKS:
// Project home: https://github.com/AlonsoLP/Arduino-L298N-Library
//
// DISCLAIMER:
// This software is furnished "as is", without technical support, and with no
// warranty, express or implied, as to its usefulness for any purpose.
//
// BACKGROUND:
// When I received a L298N Dual H-Bridge I started using Yohendry library and
// it worked fine from the beginning. But there are some lacks like no brakes,
// no direction correction, no backward driving, no turn ratio... The L298N
// library fixes these lacks.
//
// FEATURES:
// * Simple methods for basic tasks and a complex method for full customization.
// * Stops vehicle with/without brakes.
// * Trajectory correction and turn ratio, adjusting motors speed independently.
//   It can be used backward and forward (v1.1).
//
// CONSTRUCTOR:
//   L298N driver(ena, in1, in2, in3, in4, enb [, invert][, minspeed]);
//     ena      - Enable/Disable and regulates MOTOR_A speed (must be a PWM pin).
//     in1/2    - Controls MOTOR_A.
//     in3/4    - Controls MOTOR_B.
//     enb      - Enable/Disable and regulates MOTOR_B speed (must be a PWM pin).
//     invert   - [Optional] Change direction solution (Left<->Right).
//     minspeed - [Optional] Minimum speed motors can handle before stop.
//
// METHODS:
//   COMPLEX:
//     driver.drive([direction][, speed][, slave_percent][, delay_time])
//       Send an order to motors. If no direction given, go strait ahead.
//       slave_percent (0-100) works only on FORWARD_L, FORWARD_R, BACKWARD_L
//       and BACKWARD_R. It defines the slave motor speed.
//         E.g.: speed=150 slave_percent=50 => slave_speed=75
//       (*) See DIRECTIONS section for valid orders.
//   SIMPLE:
//     driver.stop([brake][, delay_time]) - Stop vehicle (using brakes if true)
//       and waits delay_time.
//     driver.forward([speed][, delay_time]) - Move forward and waits delay_time.
//     driver.backward([speed][, delay_time]) - Move backward and waits delay_time.
//     driver.left([speed][, delay_time]) - Rotate left and waits delay_time.
//     driver.right([speed][, delay_time]) - Rotate right and waits delay_time.
//
// DIRECTIONS:
//   FORWARD     250  11111010  (master - master)
//   FORWARD_R   234  11101010  (master- slave)
//   FORWARD_L   218  11011010  (slave - master)
//   BACKWARD    245  11110101  (master_inv - master_inv)
//   BACKWARD_R  229  11100101  (master_inv - slave_inv)
//   BACKWARD_L  213  11010101  (slave_inv - master_inv)
//   RIGHT       249  11111001  (master - master_inv)
//   LEFT        246  11110110  (master_inv - master)
//   STOP          0  00000000
//   BRAKE       255  11111111
//                    ABTT1234  ENA ENB TYPEA TYPEB IN1 IN2 IN3 IN4
// (*)   TYPE = 1 master - 0 slave
// (**)  Masters works at speed provided, slave at percent (lower) speed.
// (***) inv = inverted, ENA/ENB = PWM speed if 1
//
// TROUBLESHOOTING:
// * Left is right, right is left! - Exchange motors wires A<->B (hardware method)
//   or put invert _true_ when create object (software method).
//   E.g.: L298N driver(ENA, IN1, IN2, IN3, IN4, ENB, true, MINSPEED);
// * Motors does not work! - Remember to use PWM pins for ENA/ENB: 3, 5-6, 9-11
//   on most Arduino boards; 2-13 and 44-46 on Arduino Mega.
//
// HISTORY:
// 03/11/2018 v1.21 - Cosmetic fixes.
//
// 12/19/2016 v1.2 - Added simple methods for basic orders (easy reading code).
//   Fixed *no need check* in constructor. Cosmetic fixes.
//
// 12/18/2016 v1.1 - Code rewrited. Simplified method list. Direction variables
//   reflects bits used to configure motors, no need to code it separately. You
//   can turn backward. Added invert to constructor to avoid motor wire exchange
//   when left is right and vice versa.
//
// 12/16/2016 v1.0 - Initial release.
// ---------------------------------------------------------------------------

#ifndef L298N_h
#define L298N_h

#include "Arduino.h"

class L298N
{
  public:
    const uint8_t FORWARD = 250, \
                  FORWARD_R = 234, \
                  FORWARD_L = 218, \
                  BACKWARD = 245, \
                  BACKWARD_R = 229, \
                  BACKWARD_L = 213, \
                  RIGHT = 249, \
                  LEFT = 246, \
                  STOP = 0, \
                  BRAKE = 255;
    // constructor
    L298N (uint8_t ena, uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t enb, boolean invert=false, uint8_t minspeed=0);
    // complex method (all orders)
    void drive (uint8_t direction=0, uint8_t speed=255, uint8_t slave_percent=0, int delay_time=0);
    // simple methods (basic orders)
    void stop     (boolean brake=false, int delay_time=100);
    void forward  (uint8_t speed=255, int delay_time=0);
    void backward (uint8_t speed=255, int delay_time=0);
    void left     (uint8_t speed=255, int delay_time=200);
    void right    (uint8_t speed=255, int delay_time=200);
};

#endif
