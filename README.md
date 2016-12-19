# Arduino L298N Library

##An object-oriented class library to control L298N in Arduino

When I received a L298N Dual H-Bridge I started using Yohendry
library and it worked fine from the beginning. But there are some
lacks like no brake, no direction correction, no backward driving,
no turn ratio... The L298N library fixes these lacks.

##[Wiki](https://github.com/AlonsoLP/Arduino-L298N-Library/wiki)

You can find all information in the project's wiki. If you think
there's something missing/wrong, you are invited to add/fix it.

###To-Do

- Motor acceleration (inc/decrease speed gradually)
- Intelligent orders change (avoid BACKWARD FULLSPEED after FORWARD FULLSPED directly)
