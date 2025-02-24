#include<LiquidCrystal.h>
int analog = A0;
LiquidCrystal lcd (12,11,7,6,5,4);
void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);
}
void loop()
{
  int giatria = analogRead(analog);
  lcd.setCursor(0,0);
  lcd.print("analog:");
  lcd.setCursor(8,0);
  lcd.print(giatria);
  int nhietdo = map(giatria,0,1023,0,100);
  lcd.setCursor(0,1);
  lcd.print("nhiet do:");
  lcd.setCursor(10,1);
  lcd.print(nhietdo);
  
}
