int led[]={22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37};
int nut = 53;
int i;
int j;
void setup()
{
  for(i=0;i<16;i++)
  {
    pinMode(led[i],OUTPUT);
  }
  pinMode(nut,INPUT);
}
void sangtrenxuong()
{
  for(i=0;i<16;i++)
  {
    digitalWrite(led[i],HIGH);
    delay(300);
  }
}
void tatduoilen()
{
  for(i=15;i>=0;i--)
  {
    digitalWrite(led[i],LOW);
    delay(300);
  }
}
void motbongsangtrenxuong()
{
  for(i=0;i<16;i++)
  {
    digitalWrite(led[i],HIGH);
    delay(300);
    digitalWrite(led[i],LOW);
  }
}
void motbongsangduoilen()
{
  for(i=15;i>=0;i--)
  {
    digitalWrite(led[i],HIGH);
    delay(300);
    digitalWrite(led[i],LOW);
  }
}
void choptat10chuky()
{
  for(j=0;j<10;j++)
  {
    for(i=0;i<16;i++)
    {
      digitalWrite(led[i],HIGH);
    }
    delay(500);
    for(i=0;i<16;i++)
    {
      digitalWrite(led[i],LOW);
    }
    delay(500);    
  }
}
void loop()
{
  int docnut = digitalRead(nut);
  if(docnut==HIGH)
  {
    sangtrenxuong();
    tatduoilen();
    motbongsangtrenxuong();
    motbongsangduoilen();
    choptat10chuky();
  }
  else 
  {
    for(i=0;i<16;i++)
    {
      digitalWrite(led[i],LOW);
    }
  }
}
