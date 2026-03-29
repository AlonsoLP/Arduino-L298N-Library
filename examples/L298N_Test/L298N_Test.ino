// ---------------------------------------------------------------------------
// L298N Library Test Example (Refactored)
//
// This example demonstrates how to use the refactored L298N library.
// It cycles through basic and complex movement methods, including
// trajectory corrections (e.g., compensating for motor speed differences).
// ---------------------------------------------------------------------------

#include <L298N.h>

// Hardware pin definitions for the L298N motor driver
const uint8_t PIN_ENA = 3;  // PWM pin for Motor A speed control
const uint8_t PIN_ENB = 4;  // PWM pin for Motor B speed control
const uint8_t PIN_IN1 = 8;  // Direction control pin 1 for Motor A
const uint8_t PIN_IN2 = 9;  // Direction control pin 2 for Motor A
const uint8_t PIN_IN3 = 10; // Direction control pin 1 for Motor B
const uint8_t PIN_IN4 = 11; // Direction control pin 2 for Motor B

// Speed and timing configuration
const uint8_t MIN_SPEED = 50;   // Minimum PWM value that allows the motors to move
const uint8_t MAX_SPEED = 255;  // Maximum PWM value for full speed
const int DELAY_TIME = 1000;    // Standard delay between actions in milliseconds

// Initialize the L298N driver object
// Parameters: ENA, IN1, IN2, IN3, IN4, ENB, invert_direction, min_speed
L298N driver(PIN_ENA, PIN_IN1, PIN_IN2, PIN_IN3, PIN_IN4, PIN_ENB, false, MIN_SPEED);

void setup() 
{
  // Initialize serial communication for debugging output
  Serial.begin(9600);
  Serial.println("Starting L298N Motor Driver Test...");
}

void loop() 
{
  // -------------------------------------------------------------------------
  // Section 1: Testing basic movement methods
  // -------------------------------------------------------------------------
  
  Serial.println("Moving forward...");
  driver.forward(MAX_SPEED, DELAY_TIME);
  driver.stop(true, DELAY_TIME); // Stop actively using electromagnetic braking

  Serial.println("Moving backward...");
  driver.backward(MAX_SPEED, DELAY_TIME);
  driver.stop(false, DELAY_TIME); // Stop passively (coast to a halt without brakes)

  Serial.println("Turning left...");
  driver.left(MAX_SPEED, DELAY_TIME);
  driver.stop(true, DELAY_TIME);

  Serial.println("Turning right...");
  driver.right(MAX_SPEED, DELAY_TIME);
  driver.stop(false, DELAY_TIME);

  // -------------------------------------------------------------------------
  // Section 2: Testing complex methods (same actions, different syntax)
  // -------------------------------------------------------------------------
  
  Serial.println("Moving forward (complex method)...");
  // Parameters: direction, speed, slave_ratio (100% means both motors run equally), delay
  driver.drive(driver.FORWARD, MAX_SPEED, 100, DELAY_TIME);
  driver.drive(driver.BRAKE, 0, 0, DELAY_TIME); 

  Serial.println("Moving backward (complex method)...");
  driver.drive(driver.BACKWARD, MAX_SPEED, 100, DELAY_TIME);
  driver.drive(driver.STOP, 0, 0, DELAY_TIME); 

  Serial.println("Turning left (complex method)...");
  driver.drive(driver.LEFT, MAX_SPEED, 100, DELAY_TIME);
  driver.drive(driver.BRAKE, 0, 0, DELAY_TIME); 

  Serial.println("Turning right (complex method)...");
  driver.drive(driver.RIGHT, MAX_SPEED, 100, DELAY_TIME);
  driver.drive(driver.STOP, 0, 0, DELAY_TIME);

  // -------------------------------------------------------------------------
  // Section 3: Trajectory correction methods (differential drive)
  // Useful when one motor is physically faster than the other, causing drifting.
  // -------------------------------------------------------------------------
  
  Serial.println("Forward right curve (slave motor at 40% speed)...");
  driver.drive(driver.FORWARD_R, MAX_SPEED, 40, DELAY_TIME);
  
  Serial.println("Forward left curve (slave motor at 40% speed)...");
  driver.drive(driver.FORWARD_L, MAX_SPEED, 40, DELAY_TIME);
  
  Serial.println("Forward right curve...");
  driver.drive(driver.FORWARD_R, MAX_SPEED, 40, DELAY_TIME);
  
  Serial.println("Forward left curve...");
  driver.drive(driver.FORWARD_L, MAX_SPEED, 40, DELAY_TIME);
  
  driver.stop(false, DELAY_TIME);

  // -------------------------------------------------------------------------
  // Section 4: Backward trajectory correction
  // -------------------------------------------------------------------------
  
  Serial.println("Backward left curve...");
  driver.drive(driver.BACKWARD_L, MAX_SPEED, 40, DELAY_TIME);
  
  Serial.println("Backward right curve...");
  driver.drive(driver.BACKWARD_R, MAX_SPEED, 40, DELAY_TIME);
  
  Serial.println("Backward left curve...");
  driver.drive(driver.BACKWARD_L, MAX_SPEED, 40, DELAY_TIME);
  
  Serial.println("Backward right curve...");
  driver.drive(driver.BACKWARD_R, MAX_SPEED, 40, DELAY_TIME);
  
  driver.stop(false, DELAY_TIME);
}
