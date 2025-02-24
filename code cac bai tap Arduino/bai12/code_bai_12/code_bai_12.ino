int nut1 = 2, nut2 = 3, nut3 = 4, nut4=5;
int led1 = 8, led2 = 9, led3 = 10, led4=11;
void setup()
{
  pinMode(nut1,INPUT);
  pinMode(nut2,INPUT);
  pinMode(nut3,INPUT);  
  pinMode(nut4,INPUT); 
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
}
void chedo1()
{
  digitalWrite(led1,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
}
void chedo2()
{
  digitalWrite(led1,LOW);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
}
void chedo3()
{
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,HIGH);
  digitalWrite(led4,LOW);
}
void chedo4()
{
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,HIGH);
}
void loop()
{
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
  int trangthainut1 = digitalRead(nut1);
  int trangthainut2 = digitalRead(nut2);
  int trangthainut3 = digitalRead(nut3);
  int trangthainut4 = digitalRead(nut4);
  if(trangthainut1==1)
  {
    chedo1();
  }
  else if (trangthainut2==1)
  {
    chedo2();
  }
  else if (trangthainut3==1)
  {
    chedo3();
  }
  else if(trangthainut4==1)
  {
    chedo4();
  }
}
