# Motorized Grow Light

Here you will be able to learn and download the required files to build your own arduino based motorized grow light for under 100$.

## Getting Started & Things to Know

This is a DIY project, so there is actual physical building required but the build is light and easy to do within in a single afternoon.

This project makes use of a low cost 12V DC GearBox motor NOT a costly high torque stepper motor. 
However, because we use of the L298N Motor H-Bridge you can choose any of the following motor setups:

```
- 1 DC 12V GearBox Motor (what tutorial uses)
- 2 DC 12V GearBox Motors
- 1 DC 24V GearBox Motor
- 1 DC 12/24V Stepper Motor (requires code change)
```
Besides being able to expand motor setups, we also use the L298N to perform PWM on Stepper Motor setups.

### What is PWM?
Without PWM, a motor is a very simple component that has no logic to fluctuate it's speed on demand. However with PWM, you can control a motor's speed. PWM (Pulse Width Modulation) are power pulses to the motor down to the milisecond level, and is most commonly done from a micro controller (our Arduino nano). The more pulses the fast the motor spins, fewer pulses the slower the motor turns.

The down side of PWM is of course, is the loss of a motor's torque. With fewer and fewer pulses, you will lose the manufactured rated torque. The only way to combat torque loss is of course to start off with a much high torque motor (aka $). That being said, the motor we use in this tutorial will suffer from far too much torque loss when using actual PWM, so our code uses a fake PWM by delaying the code between turing motor on and off manually.

If you are using a stepper motor however, you need to use the MotorizedGrowLight_Stepper.ino in order to achive actual PWM.

Neither of the code version make use of a potentiomiter due to unknown torque loss from motor to motor setups and instead hard codes the speeds into the code... for now.

### Ok, So Why PWM?
If you run a motorized grow light system from end to end without any speed changes (no matter how fast or slow the motor speed), you will experince an uneven canopy over time. This is cause the middle of the canopy will get twice as many light passes than the outer ends of the track. However if we slow the motors down on either ends of the track with the use of PWM (or equivalent) we can ensure that the outer ends of a canopy will grow even with the inner canopy.


### Prerequisites

```
- 2 (1 in. x 2 in. x 8 ft) wood boards ($4)
- 1 Gearbox High torque 3.5RPM DC Motor ($8)
- 1 RC Card Tire ($9)
- 1 RC Car Tire Coupler ($6)
- 2 Limit switches ($6)
- 1 Arduino nano ($14)
- 1 L298N H-Bridge Module ($10)
- 1 8-foot closet door track ($24)
- 1 40 PCS Double Sided Protoboards ($14) or boradboard
- 1 12v DC Female & Male power connection adapters ($3)
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

