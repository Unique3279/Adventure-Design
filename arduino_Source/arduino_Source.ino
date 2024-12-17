// 핀 정의(BLDC 모터)
const int pwmPinA = 9; // 드라이버 IN1
const int pwmPinB = 10; // 드라이버 IN2
const int pwmPinC = 11; // 드라이버 IN3

const int hallA = 2; // Hall A 센서
const int hallB = 3; // Hall B 센서
const int hallC = 4; // Hall C 센서

int speed = 0; // 초기 속도 (0~255)
int step = 0;  // 커뮤테이션 단계
bool direction = true; // true: 정방향, false: 역방향

// 핀 설정(스텝 모터)
const int stepPin = 3; // STEP 핀
const int dirPin = 4;  // DIR 핀


void setup() {
  // 핀 모드 설정
  pinMode(pwmPinA, OUTPUT);
  pinMode(pwmPinB, OUTPUT);
  pinMode(pwmPinC, OUTPUT);

  pinMode(hallA, INPUT);
  pinMode(hallB, INPUT);
  pinMode(hallC, INPUT);

  // 핀 모드 설정
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  // 시리얼 통신 초기화
  Serial.begin(9600);
  Serial.println("Choose the (BLDC) or (step)");
  Serial.println("Example: CW 500");
}

void loop() {
  //BLDC 모터 제어
  if (Serial.readString() == "BLDC"){
    // 홀 센서 읽기
    int hA = digitalRead(hallA);
    int hB = digitalRead(hallB);
    int hC = digitalRead(hallC);



    // 단계에 따른 PWM 출력
    setCommutation(step, speed);

    Serial.println("Enter direction (F/R) and speed (us) separated by a space:");


    // 속도 및 방향 조절 (시리얼 입력으로 설정)
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n'); // 입력 값 읽기
    input.trim(); // 공백 제거

    if (input.length() > 1) {
      char dir = input.charAt(0); // 첫 번째 문자를 방향으로 처리
      int newSpeed = input.substring(1).toInt(); // 나머지 숫자는 속도로 처리

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
    
    
    // 방향에 따라 커뮤테이션 단계 계산
    if (direction) {
      step = getCommutationStep(hA, hB, hC); // 정방향
    } 
    else {
      step = getReverseCommutationStep(hA, hB, hC); // 역방향
    }
    
  }

  delay(5); // 단계 전환 속도 (모터 속도에 따라 조정 가능)
  }
  

else if (Serial.readString() == "step"){
 if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // 입력된 문자열 읽기
    input.trim(); // 앞뒤 공백 제거

    // 방향과 속도 분리
    String direction = input.substring(0, input.indexOf(' '));
    String speedStr = input.substring(input.indexOf(' ') + 1);
    int speedMicroseconds = speedStr.toInt(); // 문자열을 숫자로 변환
Serial.println("Enter direction (CW/CCW) and speed (us) separated by a space:");
    // 방향 확인
    bool clockwise = false;
    if (direction.equalsIgnoreCase("CW")) {
      clockwise = true; // 시계 방향
    } else if (direction.equalsIgnoreCase("CCW")) {
      clockwise = false; // 반시계 방향
    } else {
      Serial.println("Invalid direction. Use 'CW' or 'CCW'.");
      return;
    }

    // 속도 확인
    if (speedMicroseconds <= 0) {
      Serial.println("Invalid speed. Enter a positive number.");
      return;
    }

    // 동작 실행
    Serial.print("Rotating ");
    Serial.print(direction);
    Serial.print(" at speed: ");
    Serial.print(speedMicroseconds);
    Serial.println(" us");

    rotateMotor(200, clockwise, speedMicroseconds); // 200 스텝 회전 (예제)




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


  // 시계 방향으로 회전
  digitalWrite(dirPin, HIGH); 
  stepMotor(200); // 200 스텝 회전 (모터에 따라 다름)

  delay(1000); // 1초 대기

  // 반시계 방향으로 회전
  digitalWrite(dirPin, LOW); 
  stepMotor(200);

  delay(1000); // 1초 대기
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

// 모터 회전 함수
// steps: 회전할 스텝 수
// clockwise: 방향 (true = 시계 방향, false = 반시계 방향)
// speedMicroseconds: 스텝 사이의 지연 시간 (us 단위, 값이 작을수록 빠름)
void rotateMotor(int steps, bool clockwise, int speedMicroseconds) {
  // 방향 설정
  digitalWrite(dirPin, clockwise ? HIGH : LOW);

  // 스텝 실행
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH); // STEP 신호 ON
    delayMicroseconds(speedMicroseconds); // 속도 조절
    digitalWrite(stepPin, LOW);  // STEP 신호 OFF
    delayMicroseconds(speedMicroseconds); // 속도 조절
  }
}
