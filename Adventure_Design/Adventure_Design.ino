String err[2];
double xErr = 0.0, yErr = 0.0;

class str {
public:
  String Str;

  void getStr(String s) {
    this->Str = s;
  }

  void split(char sep) {
    int nCount = 0;
    int nIndex = 0;

    String temp = "";
    String temp2 = "";
    String sData = this->Str;
    while (1) {
      nIndex = sData.indexOf(sep);

      if (nIndex != -1) {
        temp = sData.substring(0, nIndex);
        err[0] = temp;
        temp2 = sData;
        sData = sData.substring(nIndex + 1);
      } 
      else {
        err[1] = temp2;
        break;
      }
      nCount++;
    }
  }
};

void getData(){               // get directional error from raspberry pi and save x, y error at xErr, yErr vars
  // get raw error data
  str data;
  if (Serial.available()) {
    data.getStr(Serial.readStringUntil('!'));
  } 

  // split and parse errors
  String sXErr, sYErr;
  data.split(',');
  sXErr = err[0];
  sYErr = err[1];
  xErr = sXErr.toDouble();
  yErr = sYErr.toDouble();
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  getData();
  Serial.print(xErr);
  Serial.print(" , ");
  Serial.println(yErr);
  delay(500);
}