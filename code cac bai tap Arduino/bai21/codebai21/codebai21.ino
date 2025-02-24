int led1=7,led2=8,led3=9,led4=10;
int analogchan = A0;
void setup()
{
  Serial.begin(9600);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
}
void tathet()
{
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
}
void den1sang()
{
  digitalWrite(led1,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
}
void den2sang()
{
  digitalWrite(led1,LOW);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
}
void den3sang()
{
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,HIGH);
  digitalWrite(led4,LOW);
}
void den4sang()
{
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,HIGH);
}
void loop()
{
  int giatridoc = analogRead(analogchan);
  Serial.print("gia tri analog: ");
  Serial.print(giatridoc);
  int nhietdo = map(giatridoc,0,1023,0,100);
  Serial.print("  - nhiet do: ");
  Serial.println(nhietdo);
  if(nhietdo<30)
  {
    tathet();
  }
  else if (nhietdo>30&&nhietdo<=50)
  {
    den1sang();
  }
  else if (nhietdo>50&&nhietdo<=60)
  {
    den2sang();
  }
  else if (nhietdo>60&&nhietdo<=80)
  {
    den3sang();
  }
  else if (nhietdo>80)
  {
    den4sang();
  }
}
