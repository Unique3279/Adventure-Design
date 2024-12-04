class errorCalculator {

  private:
    double xErr = 0.0, yErr = 0.0;
    String Str;
    String sSplit1 = "";
    String sSplit2 = "";          // works, don't touch it

    void getStr(String s) {
      this->Str = s;
    }

    void split(char sep) {
      int nIndex = 0;
      int startTime = millis();

      String sData = this->Str;
      // while (1) {
        nIndex = sData.indexOf(sep);

        if (nIndex != -1) {
          sSplit1 = sData.substring(0, nIndex);
          sSplit2 = sData.substring(nIndex + 1);
          sData = sData.substring(nIndex + 1);
        } 
        // else {
        //   break;
        // }

        // if (millis() - startTime > 1000) break;   // timeout break
      // }
    } 

    void getData(){               // get directional error from raspberry pi and save x, y error at xErr, yErr vars *it works, don't you touch it!!!!!*
      // get raw error data
      if (Serial.available()) {
        this->getStr(Serial.readStringUntil('!'));
      } 

      // split and parse error values
      this->split(',');
      xErr = sSplit1.toDouble();
      yErr = sSplit2.toDouble();
    }

  public:               

    void updateData(){    // update data
      this->getData();
    }

    double getXErr() {    // return x error value
      return xErr;
    }

    double getYErr() {    // return y error value
      return yErr;
    }
  };

class PIDController {
private:
    double Kp; // 비례 이득
    double Ki; // 적분 이득
    double Kd; // 미분 이득

    double previousError; // 이전 오차 값
    double integral;      // 적분 항

public:
    // 생성자: PID 게인 초기화
    PIDController(double Kp, double Ki, double Kd) {
        this->Kp = Kp;
        this->Ki = Ki;
        this->Kd = Kd;
        this->previousError = 0.0;
        this->integral = 0.0;
    }

    // PID 제어 출력 계산
    double compute(double setPoint, double currentValue, long dt) {
        // 오차 계산
        double error = setPoint - currentValue;

        // 적분 항 업데이트
        integral += error * (dt / 1000.0);

        // 미분 항 계산
        double derivative = (error - previousError) / (dt / 1000.0);

        // PID 출력 계산
        double output = Kp * error + Ki * integral + Kd * derivative;

        // 이전 오차 갱신
        previousError = error;

        return output;
    }

    // 게인 값을 설정하는 함수 (필요 시 사용)
    void setTunings(double Kp, double Ki, double Kd) {
        this->Kp = Kp;
        this->Ki = Ki;
        this->Kd = Kd;
    }
};


  errorCalculator errCalc;

  void setup() {
    Serial.begin(9600);
  }

  long xErr = 300;

  void loop() {
  }