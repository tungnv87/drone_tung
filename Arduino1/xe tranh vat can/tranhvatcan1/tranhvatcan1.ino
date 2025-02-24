
#include <Servo.h>
//L298N
#define IN1_A 7
#define IN2_A 8
#define e_A 11


#define IN1_B 4
#define IN2_B 5
#define e_B 6


//int tien1=10;           // chân IN - A của Module L298. -> IN1_A
//int tien2=11;           // chân IN - C của Module L298. -> IN2_A
//int lui1=12;            // chân IN - D của Module L298.  -> IN2_B
//int lui2=13;            // chân IN - B của Module L298. -> IN2_A

#define MAX_SPEED 255 //từ 0-255
#define MIN_SPEED 0
#define SPEED 140

const int trig = 12;     // chân trig của HC-SR04
const int echo = 13;     // chân echo của HC-SR04

bool servoEnabled = true;
bool sr04Enabled = true;
bool l298nEnabled = true;

//servo
int pos = 0;
Servo myservo;

int gioihan = 30
              ;
int i;
int x = 0;
unsigned long thoigian; // biến đo thời gian
int khoangcach;           // biến luu khoảng cách
int khoangcachtrai, khoangcachphai;

void setup()
{
  Serial.begin(115200);
  if (l298nEnabled) {
    setupL298N();
  }

  if (sr04Enabled) {
    setupRSO4();
  }

  if (servoEnabled) {
    setupServo();
  }


}

void setupServo() {
  myservo.attach(10);
}


void setupRSO4() {
  pinMode(trig, OUTPUT);  // chân trig sẽ phát tín hiệu
  pinMode(echo, INPUT);   // chân echo sẽ nhận tín hiệu
}

//RSO4
void handleRSO4() {
  unsigned long duration; // biến đo thời gian
  int distance;           // biến lưu khoảng cách

  /* Phát xung từ chân trig */
  digitalWrite(trig, 0);  // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig, 1);  // phát xung từ chân trig
  delayMicroseconds(5);   // xung có độ dài 5 microSeconds
  digitalWrite(trig, 0);  // tắt chân trig

  /* Tính toán thời gian */
  // Đo độ rộng xung HIGH ở chân echo.
  duration = pulseIn(echo, HIGH);
  // Tính khoảng cách đến vật.
  distance = int(duration / 2 / 29.412);

  /* In kết quả ra Serial Monitor */
  Serial.print(distance);
  Serial.println("cm");
}

void setupL298N() {
  //Banh A
  pinMode(IN1_A, OUTPUT);
  pinMode(IN2_A, OUTPUT);
  pinMode(e_A, OUTPUT);

  //Banh B
  pinMode(IN1_B, OUTPUT);
  pinMode(IN2_B, OUTPUT);
  pinMode(e_B, OUTPUT);
}

void banhADung() {
  digitalWrite(IN1_A, LOW);
  digitalWrite(IN2_A, LOW);
  Serial.println("nv___banh A dung");
}

void banhATien(int speed) {
  digitalWrite(IN1_A, HIGH);
  digitalWrite(IN2_A, LOW);
  analogWrite(e_A, speed);
  int speedValueA = analogRead(e_A);
  Serial.println("nv__speed A: " + String(speedValueA) + " -- inputtedValue: " + String(speed));
}

void banhALui(int speed) {
  digitalWrite(IN1_A, LOW);
  digitalWrite(IN2_A, HIGH);
  analogWrite(e_A, speed);

}

void banhBDung() {
  digitalWrite(IN1_B, LOW);
  digitalWrite(IN2_B, LOW);
  Serial.println("nv___banh B dung");
}

void banhBTien(int speed) {
  digitalWrite(IN1_B, HIGH);
  digitalWrite(IN2_B, LOW);
  analogWrite(e_B, speed);
  int speedValueB = analogRead(e_B);
  Serial.println("                                                nv__speed B: " + String(speedValueB) + " -- inputtedValue: " + String(speed));
}

void banhBLui(int speed) {
  digitalWrite(IN1_B, LOW);
  digitalWrite(IN2_B, HIGH);
  analogWrite(e_B, speed);
}

void diThang() {
  Serial.println("nv___THANG");
  resetDongCo();
  analogWrite(e_A, SPEED);
  analogWrite(e_B, SPEED+30);
  delay(20);
  banhATien(SPEED);
  banhBTien(SPEED+10);
  //    int in1A= digitalRead(IN1_A);
  //    int in2A=  digitalRead(IN2_A);
  //    int in1B = digitalRead(IN1_B);
  //    int in2B =  digitalRead(IN2_B);
  //    int speedValueA = analogRead(e_A);
  //    int speedValueB = analogRead(e_B);
  //    Serial.println("nv__speed A: " + String(speedValueA) + ", speedValueB: " + String(speedValueB) + ", logic A: " + String(in1A) + ", " + String(in2A) + ", logic B: " + String(in1B) + ", " + String(in2B));
}

void diLui() {
  Serial.println("nv___LUI");
  resetDongCo();
  for (i = 0; i < 20; i++)
    banhALui(SPEED);
  banhBLui(SPEED);
  delay(500);
  resetDongCo();
}

void rePhai() {
  Serial.println("nv___RE PHAI");
  resetDongCo();
  banhBLui(SPEED);
  delay(350);
  resetDongCo();
}

void reTrai() {
  Serial.println("nv___RE PHAI");
  resetDongCo();
  banhALui(SPEED);
  delay(500);
  resetDongCo();
}

//CLONNING...

void resetDongCo()
{
  digitalWrite(IN1_A, LOW);
  digitalWrite(IN2_A, LOW);
  digitalWrite(IN1_B, LOW);
  digitalWrite(IN2_B, LOW);
}
void diThang11()
{
  digitalWrite(IN1_A, HIGH);
  digitalWrite(IN1_B, HIGH);
  //delay(2);
}


/*servo*/

void handleServo() {
  for (pos = 0; pos < 180; pos += 1) {
    myservo.write(pos);
    Serial.println("nv___servo write: " + String(pos));
    delay(15);
  }

  for (pos = 180; pos >= 1; pos -= 1) {
    myservo.write(pos);
    Serial.println("nv___servo write1: " + String(pos));
    delay(15);
  }
}
void nhinThang()
{
  myservo.write(90);
}

void liecTrai()
{
  Serial.println("nv___servo: liec trai");
  myservo.write(180);              // tell servo to go to position in variable 'pos'
  delay(1000);
  doKhoangCach();
  myservo.write(90);              // tell servo to go to position in variable 'pos'
}

void liecPhai()
{
  Serial.println("nv___servo: liec phai");
  myservo.write(0);              // tell servo to go to position in variable 'pos'
  delay(1000);
  doKhoangCach();
  myservo.write(90);              // tell servo to go to position in variable 'pos'
}

void doKhoangCach()
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
  //  Serial.println("nv___khoang cach: " + String(khoangcach) + " thoi gian: " + String(thoigian));

}

void diChuyenXe() {
  khoangcach = 0;
  doKhoangCach();
  if (khoangcach > gioihan || khoangcach == 0)
  {
    doKhoangCach();
    if (khoangcach > gioihan || khoangcach == 0)
    {
      diThang();
    }
  }
  else
  {
    Serial.println("nv___PHAT HIEN VAT CAN - khoang cach: " + String(khoangcach));
    resetDongCo();
    liecTrai();
    khoangcachtrai = khoangcach;
    liecPhai();
    khoangcachphai = khoangcach;
    if (khoangcachphai < 10 && khoangcachtrai < 10) {
      diLui();
    }
    else
    {
      if (khoangcachphai > khoangcachtrai)
      {
        rePhai();
        delay(400);
      }
      if (khoangcachphai < khoangcachtrai)
      {
        reTrai();
        delay(400);
      }
    }
  }
}

void testDiChuyen() {
  //  banhBTien(2);
  //  delay(3000);
  //  delay(255);
  for (i = 70; i < 255; i++) {
    banhATien(i);
    banhBTien(i);
    delay(20);
  }
  banhATien(0);
  banhBTien(0);
  delay(5000);

  //    for (i = 255; i >= 0; i--) {
  //      banhATien(i);
  //      banhBTien(i);
  //      delay(20);
  //    }
  //    delay(5000);


  //    diThang();
  //    delay(500);
  //    resetDongCo();
  //    delay(2000);
  //
  //    rePhai();
  //    resetDongCo();
  //    delay(2000);
  //
  //    reTrai();
  //    resetDongCo();
  //    delay(2000);
  //
  //    diThang();
  //    delay(500);
  //    resetDongCo();
  //    delay(2000);
}

void loop()
{
  if (sr04Enabled) {
    //    handleRSO4();
    //    delay(200);
  }
  if (l298nEnabled) {
    //    //    diThang11();
    //
    //    analogWrite(e_A, 100);
    //    analogWrite(e_B, 100);
    //    //    reTrai();
    //        banhBTien(100); //ok
    //    //    banhBLui(100); //ok
    //        banhATien(100); //ok
    //        delay(500);
    //    //    banhALui(100); //ok
    //        diThang();//ok
    //        diLui();//ok
    //    //    rePhai();//ok
    //    //    reTrai();//ok
    //
    //    delay(3000);
  }


  if (servoEnabled) {
    //    //    handleServo();
    //    nhinThang(); //ok
    //    delay(2000);
    //    liecTrai();
    //    liecPhai();
    //    //    delay(200);
  }

        diChuyenXe();
//  banhBTien(100); //ok
  //  testDiChuyen();
}
