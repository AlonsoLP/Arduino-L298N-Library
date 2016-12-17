#include <L298N.h>

const uint8_t ENA = 3;
const uint8_t ENB = 4;
const uint8_t IN1 = 8;
const uint8_t IN2 = 9;
const uint8_t IN3 = 10;
const uint8_t IN4 = 11;

const uint8_t MINSPEED = 50;
const uint8_t MAXSPEED = 255;

L298N driver(ENA,IN1,IN2,IN3,IN4,ENB, MINSPEED); 

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("FORWARD AT FULL SPEED (255)");
  driver.move(driver.FORWARD, MAXSPEED, 1000);
  driver.stop(true, 500);
  Serial.println("BACKWARD AT FULL SPEED (255)");
  driver.move(driver.BACKWARD, MAXSPEED, 1000);
  driver.stop(true, 500);
  Serial.println("LEFT (STATIONARY)");
  driver.turn(driver.LEFT, MAXSPEED, -100, 1000);
  driver.stop(false, 500);
  Serial.println("RIGHT (STATIONARY)");
  driver.turn(driver.RIGHT, MAXSPEED, -100, 1000);
  driver.stop(false, 5000);
}

