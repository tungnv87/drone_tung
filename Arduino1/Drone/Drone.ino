//L298N
#define IN1_A 7
#define IN2_A 8
#define e_A 9


#define IN1_B 4
#define IN2_B 5
#define e_B 6

#define remote 2

#define MAX_SPEED 255 //từ 0-255
#define MIN_SPEED 0
#define SPEED 140

bool l298nEnabled = true;


void setup()
{
  Serial.begin(115200);
  if (l298nEnabled) {
    setupL298N();
  }

  pinMode(remote, INPUT);
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
  analogWrite(e_B, SPEED + 30);
  delay(20);
  banhATien(SPEED);
  banhBTien(SPEED);
}

void diLui() {
  Serial.println("nv___LUI");
  resetDongCo();
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
void testDiChuyen() {
  banhATien(255); //CW
  banhBTien(255); //CCW
  //  delay(3000);
  //  delay(255);
  //  banhATien(0);
  //  banhBTien(0);
  delay(5000);
  resetDongCo();
  delay(5000);
}

void loop()
{
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

  //  diChuyenXe();
  //  testDiChuyen();
  int remoteValue = analogRead(remote);
  Serial.println("nv__remoteValue: " + String(remoteValue));
  delay(500);
}
