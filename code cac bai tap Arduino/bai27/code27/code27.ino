int nut = 2, led = 12, in1 = 8, in2 = 9, e = 10;
int dem = 0;
int pre=LOW;
void setup()
{
//  pinMode(nut,INPUT);
//  pinMode(led,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(e,OUTPUT);
  Serial.begin(9600);
}
void chedo1()
{
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(e,20);
//  digitalWrite(led,LOW);
}
void chedo2()
{
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(e,30);
//  digitalWrite(led,LOW);
}
void chedo3()
{
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(e,255);
  Serial.println("Che do 3____");
//  digitalWrite(led,LOW);
}
void chedo4()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
//  analogWrite(e,0);
//  digitalWrite(led,HIGH);
}

void loop()
{
  chedo3();
  delay(5000);

  
////  int docnut = digitalRead(nut);
//  Serial.println(dem);
//  if(docnut==HIGH&&pre==LOW)
//  {
//    dem=dem+1;
//    delay(300);
//  }
//      pre=docnut;
//  if(dem==1)
//  {
//    chedo1();
//  }
//  else if(dem==2)
//  {
//    chedo2();    
//  }
//  else if(dem==3)
//  {
//    chedo3();    
//  }
//  else if(dem==4)
//  {
//    chedo4();    
//  }
//  else if(dem==5)
//  {
//    dem=0;
//  }
}
