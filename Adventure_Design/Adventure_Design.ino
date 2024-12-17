class errorCalculator {
private:
  String Str;

  void getStr(String s) {
    this->Str = s;
  }

  void getSerialData(){
    // get raw error data
    String temp;
    if (Serial.available()) {
      temp = Serial.readStringUntil('\n');
      temp.trim();
      getStr(temp);
    } 
  }

public:               

  void updateData(){
    this->getSerialData();
  }

  String getData(){
    return this->Str;
  }
};

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
    analogWrite(pwm, 0);
    digitalWrite(brk, HIGH);
  }
};

class STEP{
  private:
  int DIR;
  int STEPS;
  public:
  STEP(int d, int s){
    this->DIR = d;
    this->STEPS = s;
    pinMode(DIR, OUTPUT);
    pinMode(STEPS, OUTPUT);
  }

  void revCounterClockwise(){
    digitalWrite(DIR, HIGH);
    for(int i = 0; i<5; i++){
      digitalWrite(STEPS, HIGH);
      delayMicroseconds(1500);
      digitalWrite(STEPS, LOW);
      delayMicroseconds(1500);
    }
  }

  void revClockwise(){
    digitalWrite(DIR, LOW);
    for(int i = 0; i<5; i++){
      digitalWrite(STEPS, HIGH);
      delayMicroseconds(1500);
      digitalWrite(STEPS, LOW);
      delayMicroseconds(1500);
    }
  }
};

errorCalculator EC;
BLDC BaseMotor(2, 3, 4);
STEP YawMotor1(5, 6);
STEP YawMotor2(7, 8);


void setup() {
  Serial.begin(9600);
}


void loop() {
  EC.updateData();
  if(EC.getData() == "stop"){
    BaseMotor.stop();
  }
  else if(EC.getData() == "left"){
    BaseMotor.counterClockWise(5);
  }
  else if(EC.getData() == "right"){
    BaseMotor.Clockwise(5);
  }
  else if(EC.getData() == "up"){
    YawMotor1.revCounterClockwise();
    YawMotor2.revClockwise();
  }
  else if(EC.getData() == "down"){
    YawMotor1.revClockwise();
    YawMotor2.revCounterClockwise();
  }
}