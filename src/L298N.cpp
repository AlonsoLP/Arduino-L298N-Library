// ---------------------------------------------------------------------------
// Created by Alonso José Lara Plana - alonso.lara.plana@gmail.com
// Copyright 2016 License: GNU GPL v3 http://www.gnu.org/licenses/gpl.html
// Version: 1.3
// See "L298N.h" for purpose, syntax, version history, links, and more.
// ---------------------------------------------------------------------------

#include "L298N.h"

// ---------------------------------------------------------------------------
// L298N Constructor
// ---------------------------------------------------------------------------

// Note: Default arguments must only be specified in the header file (.h).
L298N::L298N(uint8_t ena, uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t enb, boolean invert, uint8_t minspeed)
{
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb, OUTPUT);

  // Assign parameters to private class members
  _ena = ena;
  _enb = enb;
  _in1 = in1;
  _in2 = in2;
  _in3 = in3;
  _in4 = in4;

  _invert = invert;
  _minspeed = minspeed;
}

// ---------------------------------------------------------------------------
// L298N Complex Method
// ---------------------------------------------------------------------------

void L298N::drive(uint8_t direction, uint8_t speed, uint8_t slave_ratio, int delay_time)
{
  // Verify if the provided direction matches a valid predefined state
  if (direction == FORWARD  || direction == FORWARD_R  || direction == FORWARD_L  || \
      direction == BACKWARD || direction == BACKWARD_R || direction == BACKWARD_L || \
      direction == RIGHT    || direction == LEFT       || \
      direction == STOP     || direction == BRAKE)
  {
    uint8_t master = 255;
    uint8_t slave = 0;

    // Calculate the master motor speed, ensuring it meets the minimum speed requirement
    if (direction != BRAKE) {
      master = (speed < _minspeed) ? _minspeed : speed;
    }

    // Calculate the slave motor speed based on the provided percentage ratio
    if (direction != STOP) {
      slave = (slave_ratio == 100) ? speed : ((speed <= _minspeed) ? 0 : (speed * slave_ratio / 100));
    }

    // Write digital states to direction control pins based on the bitmask
    digitalWrite(_in1, bitRead(direction, _invert ? 1 : 3));
    digitalWrite(_in2, bitRead(direction, _invert ? 0 : 2));
    digitalWrite(_in3, bitRead(direction, _invert ? 3 : 1));
    digitalWrite(_in4, bitRead(direction, _invert ? 2 : 0));

    // Write PWM signals to enable pins to control motor speed
    analogWrite(_ena, bitRead(direction, _invert ? 4 : 5) ? master : slave);
    analogWrite(_enb, bitRead(direction, _invert ? 5 : 4) ? master : slave);

    // Pause execution to allow the motors to maintain the current state
    delay(delay_time);
  }
}

// ---------------------------------------------------------------------------
// L298N Simple Methods
// ---------------------------------------------------------------------------

void L298N::stop(boolean brake, int delay_time)
{
  this->drive(brake ? BRAKE : STOP, 0, 0, delay_time);
}

void L298N::forward(uint8_t speed, int delay_time)
{
  this->drive(FORWARD, speed, 100, delay_time);
}

void L298N::backward(uint8_t speed, int delay_time)
{
  this->drive(BACKWARD, speed, 100, delay_time);
}

void L298N::left(uint8_t speed, int delay_time)
{
  this->drive(LEFT, speed, 100, delay_time);
}

void L298N::right(uint8_t speed, int delay_time)
{
  this->drive(RIGHT, speed, 100, delay_time);
}

// ---------------------------------------------------------------------------
// L298N Smooth Drive Method
// ---------------------------------------------------------------------------

void L298N::smoothDrive(uint8_t direction, uint8_t start_speed, uint8_t end_speed, int step_delay)
{
  // Accelerate: start speed is lower than target speed
  if (start_speed < end_speed) 
  {
    for (int speed = start_speed; speed <= end_speed; speed++) 
    {
      this->drive(direction, speed, 100, step_delay);
    }
  } 
  // Decelerate: start speed is higher than target speed
  else if (start_speed > end_speed) 
  {
    for (int speed = start_speed; speed >= end_speed; speed--) 
    {
      this->drive(direction, speed, 100, step_delay);
    }
    
    // Ensure the hardware is fully stopped if the target speed was zero
    if (end_speed == 0) 
    {
      this->drive(STOP, 0, 0, 0); 
    }
  }
}
