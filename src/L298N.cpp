// ---------------------------------------------------------------------------
// Created by Alonso José Lara Plana - alonso.lara.plana@gmail.com
// Copyright 2016 License: GNU GPL v3 http://www.gnu.org/licenses/gpl.html
//
// See "L298N.h" for purpose, syntax, version history, links, and more.
// ---------------------------------------------------------------------------

#include "L298N.h"

uint8_t ENA, ENB, IN1, IN2, IN3, IN4;
boolean INVERT = false;
uint8_t MINSPEED = 0;


// ---------------------------------------------------------------------------
// L298N constructor
// ---------------------------------------------------------------------------

L298N::L298N(uint8_t ena, uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t enb, boolean invert=false, uint8_t minspeed=0)
{
  pinMode (ena, OUTPUT);
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);
  pinMode (in3, OUTPUT);
  pinMode (in4, OUTPUT);
  pinMode (enb, OUTPUT);

  ENA = ena;
  ENB = enb;

  IN1 = in1;
  IN2 = in2;
  IN3 = in3;
  IN4 = in4;

  INVERT = invert;
  MINSPEED = minspeed;
}


// ---------------------------------------------------------------------------
// L298N Complex Method
// ---------------------------------------------------------------------------

void L298N::drive(uint8_t direction=0, uint8_t speed=255, uint8_t slave_ratio=0, int delay_time=0)
{
  if ( direction==FORWARD  || direction==FORWARD_R  || direction==FORWARD_L  || \
       direction==BACKWARD || direction==BACKWARD_R || direction==BACKWARD_L || \
       direction==RIGHT    || direction==LEFT       || \
       direction==STOP     || direction==BRAKE )
  {
    uint8_t master = 255, slave = 0;

    // MINSPEED <= speed_master <= MAXSPEED (255) || 255 (if BRAKE)
    if (direction != BRAKE)
      master = speed < MINSPEED?MINSPEED:speed;

    // 0 <= speed_slave <= (speed*slave_ratio/100) || speed_slave=speed (if slave_ratio==100)
    if (direction != STOP)
      slave = (slave_ratio==100)?speed:(speed <= MINSPEED?0:(speed*slave_ratio/100));

    digitalWrite(IN1, bitRead(direction, INVERT?1:3));
    digitalWrite(IN2, bitRead(direction, INVERT?0:2));
    digitalWrite(IN3, bitRead(direction, INVERT?3:1));
    digitalWrite(IN4, bitRead(direction, INVERT?2:0));

    analogWrite(ENA, bitRead(direction, INVERT?4:5)?master:slave);
    analogWrite(ENB, bitRead(direction, INVERT?5:4)?master:slave);

    delay(delay_time);
  }
}


// ---------------------------------------------------------------------------
// L298N Simple Methods
// ---------------------------------------------------------------------------

void L298N::stop(boolean brake=false, int delay_time=100)
{
  this->drive(brake?BRAKE:STOP, 0, 0, delay_time);
}

void L298N::forward(uint8_t speed=255, int delay_time=0)
{
  this->drive(FORWARD, speed, 100, delay_time);
}

void L298N::backward(uint8_t speed=255, int delay_time=0)
{
  this->drive(BACKWARD, speed, 100, delay_time);
}

void L298N::left(uint8_t speed=255, int delay_time=200)
{
  this->drive(LEFT, speed, 100, delay_time);
}

void L298N::right(uint8_t speed=255, int delay_time=200)
{
  this->drive(RIGHT, speed, 100, delay_time);
}
