#include "DHTStable.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //SCL SDA A4




DHTStable DHT;

#define DHT11_PIN       4


//L298N
#define IN1 7
#define IN2 8
#define MAX_SPEED 255 //từ 0-255
#define MIN_SPEED 0


//LED
#define LED_IN 2


void setup()
{
  Serial.begin(115200);

  setupDHT();
  setupLCD();
  setupL298N();

}

void setupDHT() {
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHTSTABLE_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
}

void setupL298N() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void setupLED() {
  pinMode(LED_IN, OUTPUT);
}

void tatQuat() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void batQuat(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void setupLCD() {
  lcd.init();
  lcd.backlight();
}


int printLCD(float humi, float temp) {
  lcd.clear();
  lcd.print("Humi: " + String(humi));
  lcd.setCursor(0, 1);
  lcd.print("Temp:" + String(temp));
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:
      Serial.print("OK,\t");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("Checksum error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.print("Time out error,\t");
      break;
    default:
      Serial.print("Unknown error,\t");
      break;
  }
  // DISPLAY DATA
  Serial.print(DHT.getHumidity(), 1);
  Serial.print(",\t");
  Serial.println(DHT.getTemperature(), 1);
  

  printLCD(DHT.getHumidity(), DHT.getTemperature());
  batQuat(MAX_SPEED); // motor 1 tiến
  kiemTraDoAm();
  delay(1000);

}

void kiemTraDoAm() {
  float doAm = DHT.getHumidity();
  if (doAm > 61) {
    //bat quat
    batQuat(MAX_SPEED);
    //hien thi ON
    hienThiTrangThai("ON", doAm);
    //tat LED
    tatLed();
  } else {
    //tat quat
    tatQuat();
    //hien thi OFF
    hienThiTrangThai("OFF", doAm);
    //bat led
    batLed();

  }
}

void hienThiTrangThai(String trangThai, float doAm) {
    lcd.clear();
    lcd.print(trangThai + " - " + String(doAm));
}

void batLed() {
  digitalWrite(LED_IN, HIGH);
}

void tatLed() {
  digitalWrite(LED_IN, LOW);
}
