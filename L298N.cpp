// ---------------------------------------------------------------------------
// Created by Alonso José Lara Plana - alonso.lara.plana@gmail.com
// Copyright 2016 License: GNU GPL v3 http://www.gnu.org/licenses/gpl.html
//
// See "L298N.h" for purpose, syntax, version history, links, and more.
// ---------------------------------------------------------------------------

#include "L298N.h"

struct Motor
{
  uint8_t in1;
  uint8_t in2;
  uint8_t pwn;
};

Motor motors[2];

static const uint8_t MOTOR_A = 0, MOTOR_B = 1;
uint8_t MINSPEED = 0;

// ---------------------------------------------------------------------------
// L298N constructor
// ---------------------------------------------------------------------------

L298N::L298N(uint8_t ena, uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t enb, uint8_t minspeed = 0)
{
  pinMode (ena, OUTPUT);
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);
  pinMode (in3, OUTPUT);
  pinMode (in4, OUTPUT);
  pinMode (enb, OUTPUT);

  motors[0].in1 = in1;
  motors[0].in2 = in2;
  motors[0].pwn = ena;

  motors[1].in1 = in3;
  motors[1].in2 = in4;
  motors[1].pwn = enb;

  if (minspeed > 0) MINSPEED = byte(minspeed);
}


// ---------------------------------------------------------------------------
// L298N Basic Method
// ---------------------------------------------------------------------------

void L298N::setup_motor(uint8_t motor_index, uint8_t in1, uint8_t in2)
{
  digitalWrite(motors[motor_index].in1, in1);
  digitalWrite(motors[motor_index].in2, in2);
}


// ---------------------------------------------------------------------------
// L298N Public Methods
// ---------------------------------------------------------------------------

void L298N::move(uint8_t direction = 1, uint8_t speed = 255, int delay_time = 0)
{
  if (direction == this->FORWARD) // direction = 1
  {
    this->setup_motor(MOTOR_A, HIGH, LOW);
    this->setup_motor(MOTOR_B, HIGH, LOW);
  }
  else if (direction == this->BACKWARD) // direction = 0
  {
    this->setup_motor(MOTOR_A, LOW, HIGH);
    this->setup_motor(MOTOR_B, LOW, HIGH);
  }
  else return; // direction != (0|1)

  analogWrite(motors[MOTOR_A].pwn, speed < MINSPEED ? MINSPEED : speed);
  analogWrite(motors[MOTOR_B].pwn, speed < MINSPEED ? MINSPEED : speed);

  delay(delay_time);
}

void L298N::turn(uint8_t direction, uint8_t speed = 255, short slave_ratio = 0, int delay_time = 0)
{
  if ((slave_ratio >= -100) && (slave_ratio <= 100)) // check slave_ratio range
  {
    uint8_t master, slave;

    if (direction == this->LEFT) // direction = 0
    {
      master = MOTOR_A;
      slave = MOTOR_B;
    }
    else if (direction == this->RIGHT) // direction = 1
    {
      master = MOTOR_B;
      slave = MOTOR_A;
    }
    else return; // direction != (0|1)

    if (slave_ratio < 0) // negative, backwards slave
    {
      this->setup_motor(master, HIGH, LOW);
      this->setup_motor(slave, LOW, HIGH);
    }
    else if (slave_ratio == 0) // zero, stops slave
    {
      this->setup_motor(master, HIGH, LOW);
      this->setup_motor(slave, LOW, LOW);
    }
    else // positive, forwards slave
    {
      this->setup_motor(master, HIGH, LOW);
      this->setup_motor(slave, HIGH, LOW);
    }

    // MINSPEED <= speed_master <= MAXSPEED (255)
    analogWrite(motors[master].pwn, speed < MINSPEED ? MINSPEED : speed);
    // 0 <= speed_slave <= speed*abs(slave_ratio)/100 || speed_slave=speed if slave_ratio==+-100
    analogWrite(motors[slave].pwn, abs(slave_ratio)==100 ? speed : (speed<MINSPEED ? 0 : speed*abs(slave_ratio)/100));

    delay(delay_time);
  }
}

void L298N::stop(boolean brake = true, int delay_time = 0)
{
  this->setup_motor(MOTOR_A, LOW, LOW);
  this->setup_motor(MOTOR_B, LOW, LOW);

  analogWrite(motors[MOTOR_A].pwn, brake ? 255 : 0);
  analogWrite(motors[MOTOR_B].pwn, brake ? 255 : 0);

  delay(delay_time);
}

