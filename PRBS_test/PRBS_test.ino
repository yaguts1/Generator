byte state = 0b10000001;
boolean toggle1 = 0;
boolean toggle2 = 0;
byte seq [255];
byte output[1000];
int k =0;
int k2=0;
unsigned int cnt = 0;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(3, OUTPUT);

 for (int i = 0; i < 254; i  = i+1) {
    //Serial.println(state & 1);
    seq[i] = state&1;
    byte newbit = (state^(state>>1))&1;
    state = (state>>1)| (newbit<<7);
}
while (k<255){
      if (seq[k] == 0 && seq[k+1] == 0){
      

      output[k2]=1;
      output[k2+1]=0;
      k = k+2;
      k2=k2+2;
      }
       
        
      
      else if (seq[k] == 0 && seq[k+1] == 1){
      

        output[k2]=1;
        output[k2+1]=0;
        output[k2+2]=0;
      
       k = k+2;
       k2=k2+3;
        
      }
      else if (seq[k] == 1 && seq[k+1] == 0){
      

        output[k2]=1;
        output[k2+1]=0;
        output[k2+2]=0;
        output[k2+3]=0;
       k = k+2;
       k2=k2+4; 
      }
      else {

        output[k2] = 1;
        output[k2+1]=0;
        output[k2+2]=0;
        output[k2+3]=0;
        output[k2+4]=0;
         k = k+2;
         k2=k2+5;
         
        
      }
        }
        for (int t = 0; t <80;t=t+1)
        {
          output[k2] = 0;
          k2=k2+1;
        }
        /*for (int h =0; h<k2;h=h+1)  {
          Serial.print(output[h]);
        }*/
          

    cli();//stop interrupts

//set timer1 interrupt at 50Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 50hz increments
  OCR1A = 39999;// = (16*10^6) / (50*8) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS11); // Set CS#1 bit for 8 prescaler for timer 1  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

sei();//allow interrupts

}


ISR(TIMER1_COMPA_vect){//timer1 interrupt 200Hz toggles
      if (toggle2){
        
        if (output[cnt]==1){
         digitalWrite(3,HIGH);
        }
        cnt = cnt+1;
    toggle2 = 0;
  }
  else{  
        digitalWrite(3,LOW);
        cnt = cnt+1;
    toggle2 = 1;

}
if(cnt == k2)
{
  cnt=0;
  }
}
void loop() {
  // put your main code here, to run repeatedly:
    

}
