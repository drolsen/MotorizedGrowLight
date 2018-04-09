# Motorized Grow Light

Here you will learn to build your own Arduino based motorized grow light track for just under $100 USD.
This build can be ran on any length track and has canopy light distribution logic built in. 

Motor can be powered on and off at any point without error canopy logic (perfect for light timers and recommened).

```

### Installing

```
- Download copy of repository.
- Open Download.
- Copy libraries/L298N folder to the default location of your arduino install's libraries folder.
- Connect computer and Arduino nano via USB/firewire cable.
- Open MotorizedGrowLights.ino at root of download in Arduino IDE.
- Upload MotorizedGrowLights.ino to Ardino Nano.
```

## First Run

On frist runs, the arduino nano waits till a limit switch is hit to being what is called a "measuring pass". 
It is here in the "measuring pass" that the arduino will measure the total distance traveled until a second limit switch is pressed, ultimatly ending the "measuing pass" and capturing the total distance traveled. 

All other passes after the "measuring pass" use this captured distacnes and divide the distance up by three parts. From here our arduino nano ensures our tracks outer thirds are ran slower than the inner thrid giving us an even plant canopy. 

This process beings again with each time power is applied to the system.


## Acknowledgments

Huge kudos to the man to started the DIY trend A. Goldsby (https://www.youtube.com/channel/UCuOaafNgDdprNcBFTnTO_Wg). His video was a huge leaping point for me to actually try this and try to improve on the build with some micro controller logic.

