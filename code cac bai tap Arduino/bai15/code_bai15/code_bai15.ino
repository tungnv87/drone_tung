int led[]={2,3,4,5,6,7,8,9};
int i;
void setup()
{
  for(i=0;i<8;i++)
  {
    pinMode(led[i],OUTPUT);
  }
}
void sangdantraiphai()
{
  for(i=0;i<8;i++)
  {
    digitalWrite(led[i],HIGH);
    delay(1000);
  }
}
void tatdantraiphai()
{
  for(i=0;i<8;i++)
  {
    digitalWrite(led[i],LOW);
    delay(500);
  }
}
void sangdanphaitrai()
{
  for(i=7;i>0;i=i-1)
  {
    digitalWrite(led[i],HIGH);
    delay(1000);
  }
}
void tatdanphaitrai()
{
  for(i=7;i>0;i=i-1)
  {
    digitalWrite(led[i],LOW);
    delay(500);
  }
}
void sang3giaytat()
{
  for(i=0;i<8;i++)
  {
    digitalWrite(led[i],HIGH);
  }
  delay(3000);
    for(i=0;i<8;i++)
  {
    digitalWrite(led[i],LOW);
  }
}
void loop()
{
  sangdantraiphai();
  tatdantraiphai();
  sangdanphaitrai();
  tatdanphaitrai();
  sang3giaytat();
}
