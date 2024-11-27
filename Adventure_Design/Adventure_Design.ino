String err[2];

class str{
public:
  String S;

  void getStr(String s){
    s = self->S;
  }

  void split(String data, char sep){
    int nCount = 0;
    int nIndex = 0;

    String temp = "";
    String sData = data;
    while(1){
      nIndex = sData.indexOf(sep);

      if(nIndex != -1){
        temp = sData.substring(0, nIndex);
        err[0] = temp;
        sData = sData.substring(nIndex+1);
      }
      else{
        err[1] = sData;
      }
    }
  }
}

void setup(){
    Serial1.begin(9600);
    Serial1.setTimeout(20);

    if (Serial1.available()) Serial.print("READY");
    else Serial1.print("Failed to open Serial!");
}

void loop(){
  
}