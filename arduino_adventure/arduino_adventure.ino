#include <Stepper.h>
int nSpeed, nSpeedStep, step;
String agree;

class BLDC {
private:
  int pwm;
  int dir;
  int brk;
public:
  BLDC(int pwm, int dir, int brk) {
    this->pwm = pwm;
    this->dir = dir;
    this->brk = brk;
    pinMode(pwm, OUTPUT);
    pinMode(dir, OUTPUT);
    pinMode(brk, OUTPUT);
  }

  void Clockwise(int speed) {
    digitalWrite(dir, HIGH);
    analogWrite(pwm, speed);
  }

  void counterClockWise(int speed) {
    digitalWrite(dir, LOW);
    analogWrite(pwm, speed);
  }

  void stop(){
    digitalWrite(brk, HIGH);
  }
};

BLDC baseMotor(7, 8, 9);
Stepper pitchMotor1(2024, 2, 3, 4, 5);
Stepper pitchMotor2(200, 35, 37, 39, 41);

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');  // 입력을 한 줄 단위로 읽음
    input.trim();                                 // 입력 문자열에서 불필요한 공백 및 개행 제거

    if (input == "BLDC") {
      Serial.println("Choose the (CW) or (CCW)");

      while (!Serial.available())
        ;  // 입력 대기
      String direction = Serial.readStringUntil('\n');
      direction.trim();

      if (direction == "CW" || direction == "CCW") {
        Serial.println("Enter speed (0-255):");
        while (!Serial.available())
          ;
        String speedInput = Serial.readStringUntil('\n');
        speedInput.trim();

        nSpeed = speedInput.toInt();
        Serial.print("Speed set to: ");
        Serial.println(nSpeed);

        if (direction == "CW") {
          baseMotor.Clockwise(nSpeed);
        } else {
          baseMotor.counterClockWise(nSpeed);
        }
      }
    } else if (input == "step") {
      Serial.println("Choose the (CW) or (CCW)");

      while (!Serial.available())
        ;
      String direction = Serial.readStringUntil('\n');
      direction.trim();

      if (direction == "CW" || direction == "CCW") {
        Serial.println("Enter speed:");
        while (!Serial.available())
          ;
        String speedStepInput = Serial.readStringUntil('\n');
        speedStepInput.trim();

        nSpeedStep = speedStepInput.toInt();
        Serial.print("Speed set to: ");
        Serial.println(nSpeedStep);

        pitchMotor1.setSpeed(nSpeedStep);
        pitchMotor2.setSpeed(nSpeedStep);

        Serial.println("Enter degrees to rotate:");
        while (!Serial.available())
          ;
        String degreesInput = Serial.readStringUntil('\n');
        degreesInput.trim();

        step = degreesInput.toInt() / 1.8;  // 1.8도 = 1스텝
        if (direction == "CW") {
          pitchMotor1.step(step);
          pitchMotor2.step(step);
        } else {
          pitchMotor1.step(-step);
          pitchMotor2.step(-step);
        }
      }
    } else {
      Serial.println("Choose the (BLDC) or (step)");
    }
  }
}
