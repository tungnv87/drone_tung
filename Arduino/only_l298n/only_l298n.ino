
//L298N
//Thiết đặt các chân động cơ
#define IN1 7
#define IN2 6
#define IN3 5
#define IN4 4
//Thiết đặt các thông số
#define MAX_SPEED 255 //từ 0-255
#define MIN_SPEED 0

void setup()
{
  Serial.begin(115200);
  setupL298N();

}

void setupL298N() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void motor_1_Dung() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void motor_1_Tien(int speed) { //speed: từ 0 - MAX_SPEED
  //  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  //  digitalWrite(IN1, HIGH);// chân này không có PWM
  //  analogWrite(IN2, 255 - speed);
  //  Serial.print("motor1_tien");

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void motor_2_Tien(int speed) { //speed: từ 0 - MAX_SPEED
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  analogWrite(IN3, speed);
  digitalWrite(IN4, LOW);// chân này không có PWM


}

void motor_2_Lui(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  analogWrite(IN4, 255 - speed);
  digitalWrite(IN3, HIGH);// chân này không có PWM
}


void loop()
{
  motor_2_Tien(MAX_SPEED); // motor 1 tiến
  Serial.println("IN1: " + String(digitalRead(IN3)));
  Serial.println("IN2: " + String(digitalRead(IN4)));
  delay(1000);

//  motor_1_Dung();
//  delay(5000);
}
