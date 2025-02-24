#include<LiquidCrystal.h>
LiquidCrystal lcd (12,11,7,6,5,4);
void setup()
{
  lcd.begin(16,2);
}
void loop()
{
  lcd.setCursor(1,0);
  lcd.print("THINH DEP TRAI");
  lcd.setCursor(2,1);
  lcd.print("CON NHA NGHEO");
}
