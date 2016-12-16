# Arduino L298N Library

##An object-oriented class library to control L298N in Arduino

When I received a L298N Dual H-Bridge I started using Yohendry
library. It worked fine from the beginning. But there are some
lacks like no brake, no direction correction, no turn ratio...
The L298N library fixes these lacks and adds new features.

#####Based on Yohendry Hurtado L298N library: https://github.com/yohendry/arduino_L298N

### What is a L298N Module?
Double H driver module uses ST L298N dual full-bridge driver.
It is a high voltage, high current dual full-bridge driver
designed to accept standard TTL logic levels and drive
inductive loads (relays, solenoids, DC and stepping
motors).

#####L298N Driver Board: http://www.geeetech.com/wiki/index.php/L298N_Motor_Driver_Board

###L298N Module Diagram
![alt tag](http://www.geeetech.com/wiki/images/a/a5/L298N_diagram1.jpg)

**VMS:** 5V-35V power source for motor. VMS is positive, GND is negtive.

**5V-JUMPER:** When the jumper is put on, 5V is supplied on the board from
the VMS port(7V < VMS < 18V). The power of logic circuit of the board is
supplied by the 5V port when this jumper put off.

**EA/EB:** Enable/Disable pins for two motors. Motor speed can be controlled
by PWM.

**IN1/2/3/4:** Pins for motor control. IN1/2 controls Motor A and IN3/4
controls Motor B.

###L298N Control Table

|ENA/ENB|IN1/3|IN2/4|Description|
|---|---|---|---|
|LOW|N/A|N/A|Motor off|
|HIGH|LOW|LOW|Motor stopped (brake)|
|HIGH|LOW|HIGH|Motor on (backward)|
|HIGH|HIGH|LOW|Motor on (forward)|
|HIGH|HIGH|HIGH|Motor stopped (brake)|
