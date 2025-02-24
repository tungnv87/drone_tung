//L298N
#define IN1 7
#define IN2 8
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
}


void tatQuat() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void batQuat(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void loop()
{
  batQuat(MAX_SPEED); // motor 1 tiến
  delay(1000);

}
