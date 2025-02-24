#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
int cambien = 2;
void setup() 
{
  lcd.begin(16, 2);
  pinMode(cambien,INPUT);
}

void loop() 
{
  int doccambien = digitalRead(cambien);
  if(doccambien==HIGH)
  {
    lcd.setCursor(0,0);
    lcd.print("khong co vat the");
  }
  else if(doccambien==LOW)
  {
    lcd.setCursor(0,0);
    lcd.print("co vat the       ");
  }
}
