int led[]= {2,3,4,5,6,7,8,9};
int i;
void setup()
{
  for(i=0;i<8;i++)
  {
    pinMode(led[i],OUTPUT);
  }
  for(i=0;i<8;i++)
  {
    digitalWrite(led[i],HIGH);
    delay(1000);
  }
  for(i=0;i<8;i++)
  {
    digitalWrite(led[i],LOW);
    delay(500);
  }
}
void loop()
{
}
