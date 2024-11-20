void setup(){
    Serial1.begin(9600);
    Serial1.setTimeout(20);

    if (Serial1.available()) Serial.print("READY");
    else Serial1.print("Failed to open Serial!");
}

void loop(){
  if(Serial1.available()){
    String data = Serial1.readString();
  }
}