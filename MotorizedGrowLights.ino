#include <L298N.h>

// pin definition
#define ENA 5
#define ENB 6
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

// create a motor instance
L298N motor1(ENA, IN1, IN2);
L298N motor2(ENB, IN3, IN4);

float totalDistance = 0; //s tores total distance of a measureing pass
float currentDistance = 0; // used to condition again totalDistance and obtain slower speeds at either end of a track.

int limitSwitch0 = 12; // limit switch pin
int limitSwitch1 = 13; // limit  switch pin

int direcitonSwitchCount = 0; // store how many times we have changed direction to determin if we are under a measuring pass or not.
bool limitReached = false; // deboucer bool used to increment directionSwitch only once per limit switch.

float speedOverRPM = 3.5 / 255; // 3.5 rotations per min, divided by 255 PWM parts

unsigned long RPMWait = millis(); // debouncer for main loop to keep main interavals every 1 second and help logevity of hardware's life.

bool movingForward = false;

void setup() {
  Serial.begin(9600);
  
  // Setup limit switch pins
  pinMode(limitSwitch0, INPUT);
  digitalWrite(limitSwitch0, HIGH);
  
  pinMode(limitSwitch1, INPUT);
  digitalWrite(limitSwitch1, HIGH);
  
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
        Serial.println("Slow Speed");
        motor1.stop(); // min RPMs
        motor2.stop(); // min RPMs
        delay(128);
        if(movingForward == true) {
          motor1.forward(); // max RPMs
          motor2.forward(); // max RPMs           
        } else {
          motor1.backward(); // max RPMs
          motor2.backward(); // max RPMs 
        }       
      }
    } else { // measuring pass speed
      Serial.println("High Speed");
      motor1.setSpeed(255); // max RPMs
      motor2.setSpeed(255); // max RPMs
    }

    // Limit switch 1 logic
    if (digitalRead(limitSwitch0) == LOW && limitReached == false) {
      limitReached = true; // pull up limitReached debouncer
      currentDistance = 0; // reset currentDistance for next pass
      
      // move motoers forward
      motor1.forward(); 
      motor2.forward();
      movingForward = true;
    } else if (digitalRead(limitSwitch0) == HIGH && limitReached == true) { //if our limit switch was on, but not is off
      limitReached = false; // reset limitReached debouncer
      direcitonSwitchCount++; // increment numuber of direction changes.
    }

    // Limit switch 2 logic
    if (digitalRead(limitSwitch1) == LOW && limitReached == false) {
      limitReached = true; // pull up limitReached debouncer
      currentDistance = 0; // reset currentDistance for next pass

      // move motors backwards
      motor1.backward();
      motor2.backward();
      movingForward = false;
    } else if (digitalRead(limitSwitch1) == HIGH && limitReached == true) {
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
