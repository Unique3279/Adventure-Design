// 핀 정의
const int pwmPinA = 9; // 드라이버 IN1
const int pwmPinB = 10; // 드라이버 IN2
const int pwmPinC = 11; // 드라이버 IN3

const int hallA = 2; // Hall A 센서
const int hallB = 3; // Hall B 센서
const int hallC = 4; // Hall C 센서

int speed = 0; // 초기 속도 (0~255)
int step = 0;  // 커뮤테이션 단계
bool direction = true; // true: 정방향, false: 역방향

void setup() {
  // 핀 모드 설정
  pinMode(pwmPinA, OUTPUT);
  pinMode(pwmPinB, OUTPUT);
  pinMode(pwmPinC, OUTPUT);

  pinMode(hallA, INPUT);
  pinMode(hallB, INPUT);
  pinMode(hallC, INPUT);

  Serial.begin(115200);
  Serial.println("BLDC Motor Control Ready");
}

void loop() {
  // 홀 센서 읽기
  int hA = digitalRead(hallA);
  int hB = digitalRead(hallB);
  int hC = digitalRead(hallC);

  // 방향에 따라 커뮤테이션 단계 계산
  if (direction) {
    step = getCommutationStep(hA, hB, hC); // 정방향
  } else {
    step = getReverseCommutationStep(hA, hB, hC); // 역방향
  }

  // 단계에 따른 PWM 출력
  setCommutation(step, speed);

  // 속도 및 방향 조절 (시리얼 입력으로 설정)
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n'); // 입력 값 읽기
    input.trim(); // 공백 제거

    if (input.length() > 1) {
      char dir = input.charAt(0); // 첫 번째 문자를 방향으로 처리

      speed = constrain(newSpeed, 0, 255); // 속도 제한

      if (dir == 'F' || dir == 'f') { // 정방향
        direction = true;
        Serial.println("Direction: Forward");
      } else if (dir == 'R' || dir == 'r') { // 역방향
        direction = false;
        Serial.println("Direction: Reverse");
      } else {
        Serial.println("Invalid Direction! Please use 'F' or 'R'.");
        return;
      }

      Serial.print("Speed set to: ");
      Serial.println(speed);
    }
  }

  delay(5); // 단계 전환 속도 (모터 속도에 따라 조정 가능)
}

// 홀 센서 상태로 정방향 커뮤테이션 단계 계산
int getCommutationStep(int hA, int hB, int hC) {
  if (hA == HIGH && hB == LOW && hC == HIGH) return 0;
  if (hA == HIGH && hB == HIGH && hC == LOW) return 1;
  if (hA == LOW && hB == HIGH && hC == HIGH) return 2;
  if (hA == LOW && hB == HIGH && hC == LOW) return 3;
  if (hA == HIGH && hB == LOW && hC == LOW) return 4;
  if (hA == LOW && hB == LOW && hC == HIGH) return 5;
  return 0; // 기본값
}

// 홀 센서 상태로 역방향 커뮤테이션 단계 계산
int getReverseCommutationStep(int hA, int hB, int hC) {
  if (hA == HIGH && hB == LOW && hC == HIGH) return 5;
  if (hA == HIGH && hB == HIGH && hC == LOW) return 4;
  if (hA == LOW && hB == HIGH && hC == HIGH) return 3;
  if (hA == LOW && hB == HIGH && hC == LOW) return 2;
  if (hA == HIGH && hB == LOW && hC == LOW) return 1;
  if (hA == LOW && hB == LOW && hC == HIGH) return 0;
  return 0; // 기본값
}

// 커뮤테이션 단계에 따른 PWM 출력 설정
void setCommutation(int step, int pwmValue) {
  switch (step) {
    case 0:
      analogWrite(pwmPinA, pwmValue);
      analogWrite(pwmPinB, 0);
      analogWrite(pwmPinC, 0);
      break;
    case 1:
      analogWrite(pwmPinA, pwmValue);
      analogWrite(pwmPinB, pwmValue);
      analogWrite(pwmPinC, 0);
      break;
    case 2:
      analogWrite(pwmPinA, 0);
      analogWrite(pwmPinB, pwmValue);
      analogWrite(pwmPinC, 0);
      break;
    case 3:
      analogWrite(pwmPinA, 0);
      analogWrite(pwmPinB, pwmValue);
      analogWrite(pwmPinC, pwmValue);
      break;
    case 4:
      analogWrite(pwmPinA, 0);
      analogWrite(pwmPinB, 0);
      analogWrite(pwmPinC, pwmValue);
      break;
    case 5:
      analogWrite(pwmPinA, pwmValue);
      analogWrite(pwmPinB, 0);
      analogWrite(pwmPinC, pwmValue);
      break;
  }
}
