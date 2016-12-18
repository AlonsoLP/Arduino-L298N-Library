#include <L298N.h>

const uint8_t ENA = 3;
const uint8_t ENB = 4;
const uint8_t IN1 = 8;
const uint8_t IN2 = 9;
const uint8_t IN3 = 10;
const uint8_t IN4 = 11;

const uint8_t MINSPEED = 50;
const uint8_t MAXSPEED = 255;

L298N driver(ENA, IN1, IN2, IN3, IN4, ENB, false, MINSPEED); 

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("FORWARD RIGHT");
  driver.drive(driver.FORWARD_R, MAXSPEED, 40, 1000);
  driver.drive(driver.STOP, 0, 0, 1000); // stop using drive method
  Serial.println("BACKWARD RIGHT");
  driver.drive(driver.BACKWARD_R, MAXSPEED, 40, 1000);
  driver.stop(false, 1000); // stop using stop method
  Serial.println("FORWARD LEFT");
  driver.drive(driver.FORWARD_L, MAXSPEED, 40, 1000);
  driver.drive(driver.STOP, 0, 0, 1000);
  Serial.println("BACKWARD LEFT");
  driver.drive(driver.BACKWARD_L, MAXSPEED, 40, 1000);
  driver.drive(driver.STOP, 0, 0, 1000);
  Serial.println("FORWARD");
  driver.drive(driver.FORWARD, MAXSPEED, 40, 1000);
  driver.drive(driver.BRAKE, 0, 0, 1000); // brake using drive method
  Serial.println("BACKWARD");
  driver.drive(driver.BACKWARD, MAXSPEED, 40, 1000);
  driver.stop(true, 1000); // brake using stop method
  Serial.println("RIGHT");
  driver.drive(driver.RIGHT, MAXSPEED, 40, 1000);
  driver.drive(driver.STOP, 0, 0, 1000);
  Serial.println("LEFT");
  driver.drive(driver.LEFT, MAXSPEED, 40, 1000);
  driver.drive(driver.STOP, 0, 0, 1000);
}

