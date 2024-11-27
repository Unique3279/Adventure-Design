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
    while (1) {
      nIndex = sData.indexOf(sep);

      if (nIndex != -1) {
        sSplit1 = sData.substring(0, nIndex);
        sSplit2 = sData.substring(nIndex + 1);
        sData = sData.substring(nIndex + 1);
      } 
      else {
        break;
      }

      if (millis() - startTime > 1000) break;   // timeout break
    }
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

errorCalculator errCalc;

void setup() {
  Serial.begin(9600);
}

void loop() {
  errCalc.updateData();
  Serial.print(errCalc.getXErr());
  Serial.print(" , ");
  Serial.println(errCalc.getYErr());
}