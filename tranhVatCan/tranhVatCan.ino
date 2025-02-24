#include <Servo.h>
Servo myservo;  // tạo đối tượng servo để điều khiển servo
int pos = 0;    // biến lưu vị trí servo
/****** khai báo chân input/output**************/

const int trig = 6;     // chân trig của SRF-05.
const int echo = 5;     // chân echo của SRF-05.
int tien1 = 10;         // chân IN - A của Module L298.
int tien2 = 11;         // chân IN - C của Module L298.
int lui1 = 12;          // chân IN - D của Module L298.
int lui2 = 13;          // chân IN - B của Module L298.
int dongcoservo = 9;    // chân Orange c?a Servo.

int gioihan = 25
              ;
int i;
int x = 0;
unsigned long thoigian; // biến đo thời gian
int khoangcach;           // biến luu khoảng cách
int khoangcachtrai, khoangcachphai;

void dokhoangcach();
void dithang(int duongdi);
void disangtrai();
void disangphai();
void dilui();
void resetdongco();
void quaycbsangphai();
void quaycbsangtrai();
void setup() {

  myservo.attach(9);  // đặt chân pin 9 trên arudino cho servo
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(tien1, OUTPUT);
  pinMode(tien2, OUTPUT);
  pinMode(lui1, OUTPUT);
  pinMode(lui2, OUTPUT);
  digitalWrite(tien1, LOW);
  digitalWrite(tien2, LOW);
  digitalWrite(lui1, LOW);
  digitalWrite(lui1, LOW);
  // Serial.begin(9600);
  myservo.write(90);
  delay(500);
}
void loop()
{
  khoangcach = 0;
  dokhoangcach();
  if (khoangcach > gioihan || khoangcach == 0)
  {
    dokhoangcach();
    if (khoangcach > gioihan || khoangcach == 0)
    {
      dithang();
    }
  }
  else
  {
    resetdongco();
    quaycbsangtrai();
    khoangcachtrai = khoangcach;
    quaycbsangphai();
    khoangcachphai = khoangcach;
    if (khoangcachphai < 10 && khoangcachtrai < 10) {
      dilui();
    }
    else
    {
      if (khoangcachphai > khoangcachtrai)
      {
        disangphai();
        delay(1500);
      }
      if (khoangcachphai < khoangcachtrai)
      {
        disangtrai();
        delay(1500);
      }
    }
  }
  //Serial.println(khoangcach);
}
void dithang()
{
  digitalWrite(tien1, HIGH);
  digitalWrite(tien2, HIGH);
  //delay(2);
}
void disangtrai()
{
  resetdongco();
  digitalWrite(lui1, HIGH);
  delay(300);
  digitalWrite(lui1, LOW);
}
void disangphai()
{
  resetdongco();
  digitalWrite(lui2, HIGH);
  delay(300);
  digitalWrite(lui2, LOW);
}
void dilui()
{
  resetdongco();
  for (i = 0; i < 20; i++)
    digitalWrite(lui1, HIGH);
  digitalWrite(lui2, HIGH);
  delay(1000);
  digitalWrite(lui1, LOW);
  digitalWrite(lui2, LOW);
}
void resetdongco()
{
  digitalWrite(tien1, LOW);
  digitalWrite(tien2, LOW);
  digitalWrite(lui1, LOW);
  digitalWrite(lui2, LOW);
}
/****** chuong trình do khoang cách SRF04 ***************/
void dokhoangcach()
{
  /* Phát xung t? chân trig */
  digitalWrite(trig, 0);  // t?t chân trig
  delayMicroseconds(2);
  digitalWrite(trig, 1);  // phát xung t? chân trig
  delayMicroseconds(10);   // xung có d? dài 5 microSeconds
  digitalWrite(trig, 0);  // t?t chân trig
  /* Tính toán th?i gian */
  // Ðo độ rộng xung HIGH của chân echo.
  thoigian = pulseIn(echo, HIGH);
  // Tính khoảng cách d?n v?t.
  khoangcach = int(thoigian / 2 / 29.412);
}
/********* chuong trình quay cảm biến sang trái *********/
void quaycbsangtrai()
{
  myservo.write(180);              // tell servo to go to position in variable 'pos'
  delay(1000);
  dokhoangcach();
  myservo.write(90);              // tell servo to go to position in variable 'pos'
}
void quaycbsangphai()
{
  myservo.write(0);              // tell servo to go to position in variable 'pos'
  delay(1000);
  dokhoangcach();
  myservo.write(90);              // tell servo to go to position in variable 'pos'
}
void resetservo()
{
  myservo.write(90);
}
