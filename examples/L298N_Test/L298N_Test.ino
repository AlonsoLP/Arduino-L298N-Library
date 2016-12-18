#include <L298N.h>

const uint8_t ENA = 3;
const uint8_t ENB = 4;
const uint8_t IN1 = 8;
const uint8_t IN2 = 9;
const uint8_t IN3 = 10;
const uint8_t IN4 = 11;

const uint8_t MINSPEED = 50;
const uint8_t MAXSPEED = 255;
int delay_time = 1000;

L298N driver(ENA, IN1, IN2, IN3, IN4, ENB, false, MINSPEED); 

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // Some tests using simple methods
  Serial.println("FORWARD");
  driver.forward(MAXSPEED, delay_time);
  driver.stop(true, delay_time); // stop with brakes
  Serial.println("BACKWARD");
  driver.backward(MAXSPEED, delay_time);
  driver.stop(false, delay_time); // stop without brakes
  Serial.println("LEFT");
  driver.left(MAXSPEED, delay_time);
  driver.stop(true, delay_time); // stop with brakes
  Serial.println("RIGHT");
  driver.right(MAXSPEED, delay_time);
  driver.stop(false, delay_time); // stop without brakes

  // same as above with complex methods
  Serial.println("FORWARD");
  driver.drive(driver.FORWARD, MAXSPEED, 100, delay_time);
  driver.drive(driver.BRAKE, 0, 0, delay_time); // stop with brakes
  Serial.println("BACKWARD");
  driver.drive(driver.BACKWARD, MAXSPEED, 100, delay_time);
  driver.drive(driver.STOP, 0, 0, delay_time); // stop without brakes
  Serial.println("LEFT");
  driver.drive(driver.LEFT, MAXSPEED, 100, delay_time);
  driver.drive(driver.BRAKE, 0, 0, delay_time); // stop with brakes
  Serial.println("RIGHT");
  driver.drive(driver.RIGHT, MAXSPEED, 100, delay_time);
  driver.drive(driver.STOP, 0, 0, delay_time); // stop without brakes

  // trajectory correction methods (drunk driving)
  Serial.println("FORWARD RIGHT");
  driver.drive(driver.FORWARD_R, MAXSPEED, 40, 1000);
  Serial.println("FORWARD LEFT");
  driver.drive(driver.FORWARD_L, MAXSPEED, 40, 1000);
  Serial.println("FORWARD RIGHT");
  driver.drive(driver.FORWARD_R, MAXSPEED, 40, 1000);
  Serial.println("FORWARD LEFT");
  driver.drive(driver.FORWARD_L, MAXSPEED, 40, 1000);
  driver.stop(false, delay_time); // stop without brakes

  // backward trajectory driving (very drunk driving)
  Serial.println("BACKWARD LEFT");
  driver.drive(driver.BACKWARD_L, MAXSPEED, 40, 1000);
  Serial.println("BACKWARD RIGHT");
  driver.drive(driver.BACKWARD_R, MAXSPEED, 40, 1000);
  Serial.println("BACKWARD LEFT");
  driver.drive(driver.BACKWARD_L, MAXSPEED, 40, 1000);
  Serial.println("BACKWARD RIGHT");
  driver.drive(driver.BACKWARD_R, MAXSPEED, 40, 1000);
  driver.stop(false, delay_time); // stop without brakes
}

