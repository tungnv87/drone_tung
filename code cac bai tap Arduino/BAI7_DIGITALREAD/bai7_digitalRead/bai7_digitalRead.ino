int led = 10;
int nutnhan = 3;
void setup()
{
  pinMode(led,OUTPUT);
  pinMode(nutnhan,INPUT);
}
void loop()
{
    int docnutnhan = digitalRead(nutnhan);
    if(docnutnhan == 1)
    {
      digitalWrite(led,HIGH);
      delay(5000);
      digitalWrite(led,LOW);
      delay(5000);
      digitalWrite(led,HIGH);
    }
}
