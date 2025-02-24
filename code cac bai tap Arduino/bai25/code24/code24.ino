#include<LiquidCrystal.h>
#include"DHT.h"
const int DHTPIN = 2;
const int DHTTYPE = DHT11;
DHT dht(DHTPIN,DHTTYPE);
LiquidCrystal lcd (12,11,7,6,5,4);
void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);
  dht.begin();
}
void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  lcd.setCursor(0,0);
  lcd.print("h:");
  lcd.setCursor(8,0);
  lcd.print(h);
  lcd.setCursor(0,1);
  lcd.print("t:");
  lcd.setCursor(10,1);
  lcd.print(t);
  
}
