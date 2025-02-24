int nut1=4, nut2=3, nut3=2,nut4=1,nut5=0;
int in1=8, in2=9, chanpwm=10;
void setup()
{
  pinMode(nut1,INPUT);
  pinMode(nut2,INPUT);
  pinMode(nut3,INPUT);
  pinMode(nut4,INPUT);
  pinMode(nut5,INPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(chanpwm,OUTPUT);
}
void loop()
{
  int docnut1=digitalRead(nut1);
  int docnut2=digitalRead(nut2);
  int docnut3=digitalRead(nut3);
  int docnut4=digitalRead(nut4);
  int docnut5=digitalRead(nut5);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  if(docnut1==LOW)
  {
    analogWrite(chanpwm,0);
  }
  else if(docnut2==LOW)
  {
    analogWrite(chanpwm,43);
  }
  else if(docnut3==LOW)
  {
    analogWrite(chanpwm,85);
  }
  else if(docnut4==LOW)
  {
    analogWrite(chanpwm,170);
  }
  else if(docnut5==LOW)
  {
    analogWrite(chanpwm,213);
  }
}
