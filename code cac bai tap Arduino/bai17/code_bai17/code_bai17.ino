int led = 2;
void setup()
{
  pinMode(led,OUTPUT);
  int i = 0;
  while(i<5)
  {
    digitalWrite(led,HIGH);
    delay(3000);
    digitalWrite(led,LOW);
    delay(3000);
    i=i+1;
  }
}
void loop()
{
}
