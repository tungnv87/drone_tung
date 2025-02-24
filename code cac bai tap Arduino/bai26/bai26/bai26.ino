#include<LiquidCrystal.h>
LiquidCrystal lcd (12,11,7,6,5,4);
int i;
void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
}
void loop()
{
  for(i=15;i>(-15);i--)
  {
    lcd.setCursor(i,0);
    lcd.print("thinh dep trai");
    lcd.setCursor(i,1);
    lcd.print("con nha ngheo");
    delay(300);
    lcd.clear();
  }
}
