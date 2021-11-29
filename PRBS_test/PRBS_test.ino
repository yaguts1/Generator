byte state = 0b10000001;
byte seq[255];
byte output[1000];
int k2 = 0;

unsigned int cnt = 0;

void setup()
{
  // put your setup code here, to run once:
  int k = 0;
   
  Serial.begin(9600);
  delay(100);
  pinMode(3, OUTPUT);

  for (int i = 0; i < 254; i = i + 1)
  {
    Serial.println(state & 1);
    seq[i] = state & 1;
    byte newbit = (state^(state>>3)^(state>>5)^(state>>6))&1;
    state = (state >> 1) | (newbit << 7);
  }
  while (k < 254)
  {
    output[k2] = 1;
    for (int j=0; j < (seq[k]*2 + seq[k+1] + 1); j++){
      output[k2+j+1] = 0;
    }
    k2 = k2 + 2 +seq[k]*2 + seq[k+1];
    k = k + 2;
  }
  for (int t = 0; t < 80; t = t + 1)
  {
    output[k2] = 0;
    k2 = k2 + 1;
  }
  int k3 = 0;
  for (int h = 0; h < 254; h += 2)
  {
    Serial.print(seq[h]); 
    Serial.print(seq[h+1]); 
    Serial.print(" : ");
    if(1 || !(h < 2)) {
      for (int j = 0; j < seq[h]*2+seq[h+1]+2; j++){
        Serial.print(output[k3]);
        k3++;
      }
    }
    Serial.println();
  }

  cli(); //stop interrupts

  //set timer1 interrupt at 50Hz
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1 = 0;  //initialize counter value to 0
  // set compare match register for 50hz increments
  OCR1A = 39999; // = (16*10^6) / (50*8) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS11); // Set CS#1 bit for 8 prescaler for timer 1
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei(); //allow interrupts
}

ISR(TIMER1_COMPA_vect)
{ //timer1 interrupt 200Hz toggles

  if (output[cnt] == 1)
  {
    digitalWrite(3, HIGH);
  }

  else
  {
    digitalWrite(3, LOW);
  }
  cnt = cnt + 1;
  if (cnt == k2)
  {
    cnt = 0;
  }
}
void loop()
{
  // put your main code here, to run repeatedly:
}
