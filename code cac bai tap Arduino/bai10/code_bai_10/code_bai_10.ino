int nut1 = 2, nut2 = 3, nut3 = 4;
int led1 = 8, led2 = 9, led3 = 10;
void setup()
{
  pinMode(nut1,INPUT);
  pinMode(nut2,INPUT);
  pinMode(nut3,INPUT);  
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
}
void loop()
{
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  int trangthainut1 = digitalRead(nut1);
  int trangthainut2 = digitalRead(nut2);
  int trangthainut3 = digitalRead(nut3);
  if(trangthainut1==1)
  {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW); 
    delay(5000);  
  }
  else if(trangthainut2==1)
  {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,LOW); 
        delay(5000);   
  }
  else if(trangthainut3==1)
  {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);   
        delay(5000); 
  }
}
