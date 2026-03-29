# Arduino L298N Library

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

## An object-oriented class library to control L298N in Arduino

When I received a L298N Dual H-Bridge I started using the Yohendry library, and while it worked fine from the beginning, I noticed some critical missing features: no active braking, no trajectory correction, no backward driving, and no turn ratio. 

**The L298N library fixes these lacks and brings advanced, safe control to your motor setups.**

### Key Features
* **Fully Object-Oriented:** Safely encapsulated pin variables allow you to create multiple `L298N` instances without conflicts (perfect for 4-wheel drive/Mecanum robots).
* **Smart Hardware Protection:** Automatically inserts a 100ms deadtime pause when switching between opposite active directions (e.g., Forward to Backward) to prevent voltage spikes and protect your H-Bridge from burning out.
* **Active Braking:** Stop your motors instantly using electromagnetic braking, or let them coast to a halt.
* **Trajectory Correction:** Adjust the speed ratio between motors to perfectly drive in a straight line, compensating for hardware imperfections ("drunk driving" correction).
* **Smooth Acceleration:** Built-in `smoothDrive()` method to gradually accelerate or decelerate your motors without writing complex non-blocking timers.
* **Software Inversion:** Wired your motors backwards? Fix it with a simple `true` flag in the constructor instead of rebuilding your circuit.

## [Documentation & Wiki](https://github.com/AlonsoLP/Arduino-L298N-Library/wiki)

You can find all installation instructions, method references, and troubleshooting guides in the project's [Wiki](https://github.com/AlonsoLP/Arduino-L298N-Library/wiki). 

If you think there's something missing or wrong, you are more than welcome to open an issue or submit a pull request!

---
*Disclaimer: This software is furnished "as is", without technical support, and with no warranty, express or implied, as to its usefulness for any purpose.*
