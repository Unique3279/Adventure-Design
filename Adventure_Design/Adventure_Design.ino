String err[2];
double xErr = 0.0, yErr = 0.0;
String sSplit1 = "";
String sSplit2 = "";          // works, don't touch it

class str {             
public:
  String Str;

  void getStr(String s) {
    this->Str = s;
  }

  void split(char sep) {
    int nCount = 0;
    int nIndex = 0;

    String sData = this->Str;
    while (1) {
      nIndex = sData.indexOf(sep);

      if (nIndex != -1) {
        sSplit1 = sData.substring(0, nIndex);
        err[0] = sSplit1;
        sSplit2 = sData.substring(nIndex + 1);
        sData = sData.substring(nIndex + 1);
      } 
      else {
        err[1] = sSplit2;
        break;
      }
      nCount++;
    }
  }
};

str data;

void getData(){               // get directional error from raspberry pi and save x, y error at xErr, yErr vars *it works, don't you touch it!!!!!*
  // get raw error data
  if (Serial.available()) {
    data.getStr(Serial.readStringUntil('!'));
  } 

  // split and parse error values
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
}