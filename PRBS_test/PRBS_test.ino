byte state = 10000001;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
    

}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.println(state & 1);
    byte newbit = (state^(state>>1))&1;
    state = (state>>1)| (newbit<<7);

}
