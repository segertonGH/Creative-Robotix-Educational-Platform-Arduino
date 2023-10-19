# Creative-Robotix-Educational-Platform-Arduino
An Arduino library for use with the Creative Robotix Educational Platform

Creative Robotix is a project by the Creative Science Foundation.  It is a fully customizable
robotics platform, with body parts that can be 3D printed and contstructed with low cost open hardware.

Creative-Robotix can be used by teachers, parents, children, adults, in groups or as individuals to address core STEAM (Science, Technology, Engineering, Arts & Maths) learning and making activities in a fun, hands-on, social and interactive way.  Our open-source platform can be used by anyone from 7 years up who are interested in learning more about technology. The tasks are carefully designed to fit the abilities of all ages, ranging from simple to more complex assembly, depending on your age, knowledge and guidance available.

[Our website](https://creative-science.org/partnerships/creative-robotix/) has more information about the project, including build Instructables, 

## Download

## Install 
The library can be installed using the [standard Arduino library install procedure](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-installing-a-library)

This library has two dependencies which also should be installed [LEDControl](https://www.arduino.cc/reference/en/libraries/ledcontrol/) and [NewPing](https://www.arduino.cc/reference/en/libraries/newping/).  The Creative Robotix library makes use the arduino tone function which creates a timmer conflict with the NewPing library.  Edit NewPing.h and change all instances of "#define TIMER_ENABLED true" to "#define TIMER_ENABLED false" to resolve the compile conflict.  The NewPing.h file can be found in the [arduino library folder](https://docs.arduino.cc/hacking/software/Libraries).

## Documentation
