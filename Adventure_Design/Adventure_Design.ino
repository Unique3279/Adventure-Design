#define PI 3.1415926535897932384626433832795
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
  double prevErr = 0.0;
  double sum = 0;
public:
  PIDController(double Kp, double Ki, double Kd){
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
  }
private:
    double Ep = 0;
    double Ei = 0;
    double Ed = 0;

    double derivate(double currentErr, long long dt){
      double dErr = currentErr - this->prevErr;
      return dErr / (dt / 1000.0);    // Return Err/s
    }
    double integral(double currentErr, long long dt){
      this->sum = this->sum + (currentErr * dt / 1000);
      this->sum = constrain(this->sum, -100, 100);    // anti-windup
      return this->sum;
    }
public:
  int control(double state, double target, int delta){
    this->Ep = target - state;
    this->Ei = this->integral(this->Ep, delta);
    this->Ed = this->derivate(this->Ep, delta);
    int ctrlVal = (int)((this->Ep * this->Kp) + (this->Ei * this->Ki) + (this->Ed * this->Kd));
    ctrlVal = constrain(ctrlVal, -255, 255);    // anti-windup
    this->prevErr = this->Ep;
    return ctrlVal;
  }

  void reset(){
    this->prevErr = 0.0;
    this->sum = 0.0;
  }
};


  double xErr = -30;

  void setup() {
    Serial.begin(9600);
  }

  void loop() {

  }