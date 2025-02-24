int led = 8;
int i;
void setup()
{
  pinMode(led,OUTPUT);
  for(i=0;i<4;i=i+1)
  {
    digitalWrite(led,HIGH);
    delay(3000);
    digitalWrite(led,LOW);
    delay(3000);
  }
}
void loop()
{
}
