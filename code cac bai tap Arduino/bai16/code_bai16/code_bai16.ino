int led[]={2,3,4,5,6,7,8,9};
int i;
void setup()
{
  for(i=0;i<8;i++)
  {
    pinMode(led[i],OUTPUT);
  }
}
void tathet()
{
  for(i=0;i<8;i++)
  {
    digitalWrite(led[i],LOW);
  }
}
void sang1357()
{
  for(i=0;i<8;i=i+2)
  {
    digitalWrite(led[i],HIGH);
    delay(500);
  }
}
void sang2468()
{
  for(i=1;i<8;i=i+2)
  {
    digitalWrite(led[i],HIGH);
    delay(500);
  }
}
void sang8642()
{
  for(i=7;i>=0;i=i-2)
  {
    digitalWrite(led[i],HIGH);
    delay(500);
  }
}
void sang7531()
{
  for(i=6;i>=0;i=i-2)
  {
    digitalWrite(led[i],HIGH);
    delay(500);
  }
}
void loop()
{
  tathet();
  sang1357();
  sang2468();
  tathet();
  sang8642();
  sang7531();
}
