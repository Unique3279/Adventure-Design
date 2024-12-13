#include<Stepper.h>
int nSpeed, nSpeedStep, agree, step;

class BLDC {
private:
  int pwm;
  int dir;
public:
  BLDC(int pwm, int dir){
    this->pwm = pwm;
    this->dir = dir;
  }

  void Clockwise(int speed) {
    digitalWrite(dir, HIGH);
    analogWrite(pwm, speed);
  }

  void counterClockWise(int speed) {
    digitalWrite(dir, LOW);
    analogWrite(pwm, speed);
  }
};

BLDC baseMotor(1, 2);
Stepper pitchMotor1(200, 22, 23, 24, 25);
Stepper pitchMotor2(200, 26, 27, 28, 29);

void setup() {
  Serial.begin(9600);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  
}

void loop() {
  Serial.println("Choose the (BLDC) or (step)");

  if (Serial.readString() == "BLDC"){
    Serial.println("Choose the (CW) or (CCW)");
    
    if (Serial.readString() == "CW"){
      String speed = Serial.readString();
      nSpeed = speed.toInt();
      Serial.print("Speed set to: ");
      Serial.println(nSpeed);
      baseMotor.Clockwise(nSpeed);
    }

    else if (Serial.readString() == "CCW"){
      String speed = Serial.readString();
      nSpeed = speed.toInt();
      Serial.print("Speed set to: ");
      Serial.println(nSpeed);
      baseMotor.Clockwise(nSpeed);
    }
  }

  else if (Serial.readString() == "step"){
    Serial.println("Choose the (CW) or (CCW)");

    if (Serial.readString() == "CW"){
      String speedStep = Serial.readString();
      nSpeedStep = speedStep.toInt();
      Serial.print("Speed set to: ");
      Serial.println(nSpeedStep);
      pitchMotor1.setSpeed(nSpeedStep);
      pitchMotor2.setSpeed(nSpeedStep);

      Serial.print("agree set to: ");
      agree = Serial.readString();
      Serial.print("agree set to: ");
      Serial.println(agree);
      step = agree.toInt() / 1.8;
      pitchMotor1.step(step);
      pitchMotor2.step(step);
    }

    else if (Serial.readString() == "CCW"){
      String speedStep = Serial.readString();
      nSpeedStep = speedStep.toInt();
      Serial.print("Speed set to: ");
      Serial.println(nSpeedStep);
      pitchMotor1.setSpeed(nSpeedStep);
      pitchMotor2.setSpeed(nSpeedStep);

      Serial.print("agree set to: ");
      agree = Serial.readString();
      Serial.print("agree set to: ");
      Serial.println(agree);
      step = agree.toInt() / 1.8;
      pitchMotor1.step(-step);
      pitchMotor2.step(-step);
    }

  }
}