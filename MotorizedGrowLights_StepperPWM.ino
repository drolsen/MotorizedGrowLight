#include <L298N.h>

// configurable settings and pins
int MaxSpeed = 255;
int MinSpeed = 128;
float MotorRPMS = 3.5;

#define ENA 5
#define ENB 6
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define LimitSwitchA 12
#define LimitSwitchB 13

// global logic variables
float speedOverRPM = MotorRPMS / 255; // 3.5 rotations per min, divided by 255 PWM parts
float totalDistance = 0; // stores total distance of a measureing pass
float currentDistance = 0; // used to condition again totalDistance and obtain slower speeds at either end of a track.

int direcitonSwitchCount = 0; // store how many times we have changed direction.
bool limitReached = false; // limit switch direction debounce.

unsigned long RPMWait = millis(); // main loop debounce to protect/prolong hardware life.

// motor instances
L298N motor1(ENA, IN1, IN2);
L298N motor2(ENB, IN3, IN4);

void setup() {
  Serial.begin(9600);

  // Setup limit switch pins
  pinMode(LimitSwitchA, INPUT);
  digitalWrite(LimitSwitchA, HIGH);
  
  pinMode(LimitSwitchB, INPUT);
  digitalWrite(LimitSwitchB, HIGH);
  
  // Setup initial speed of motors
  motor1.setSpeed(255);
  motor2.setSpeed(255);

  // Setup inital direction of motors
  motor1.forward();
  motor2.forward();
}

void loop() {
  // debounce by 1 second to give meaning of RPM
  if(((millis() - RPMWait) >= 1000)) {
    
    // if we are done with measuring pass
    if (direcitonSwitchCount >= 2) {
      if (currentDistance < (totalDistance / 3) || currentDistance > ((totalDistance / 3) * 2)) {
        motor1.setSpeed(MinSpeed);
        motor2.setSpeed(MinSpeed);
      }
    } else { // measuring pass speed
      motor1.setSpeed(MaxSpeed); // max RPMs
      motor2.setSpeed(MaxSpeed); // max RPMs
    }

    // Limit switch 1 logic
    if (digitalRead(LimitSwitchA) == LOW && limitReached == false) {
      limitReached = true; // pull up limitReached debouncer
      currentDistance = 0; // reset currentDistance for next pass
      
      // move motoers forward
      motor1.forward(); 
      motor2.forward();
    } else if (digitalRead(LimitSwitchA) == HIGH && limitReached == true) {
      limitReached = false; // reset limitReached debouncer
      direcitonSwitchCount++; // increment numuber of direction changes.
    }

    // Limit switch 2 logic
    if (digitalRead(LimitSwitchB) == LOW && limitReached == false) {
      limitReached = true; // pull up limitReached debouncer
      currentDistance = 0; // reset currentDistance for next pass

      // move motors backwards
      motor1.backward();
      motor2.backward();
    } else if (digitalRead(LimitSwitchB) == HIGH && limitReached == true) {
      limitReached = false; // reset limitReached debouncer
      direcitonSwitchCount++; // increment number of direction changes.
    }

    RPMWait = millis();
  }

  // only after having reached our first directionSwitch do we begin a measuring pass
  if (direcitonSwitchCount == 1) {
    totalDistance += speedOverRPM * (motor1.getSpeed());
  }

  // all other passes after the measuring pass are used to tally currentDistance
  if (direcitonSwitchCount >= 2) {
    currentDistance += speedOverRPM * (motor1.getSpeed());
  } 
}
