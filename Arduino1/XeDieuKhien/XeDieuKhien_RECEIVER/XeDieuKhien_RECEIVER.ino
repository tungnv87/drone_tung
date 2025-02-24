/*ARDUINO JOYSTICK CONTROLLED CAR (RECEIVER)

  YOU HAVE TO INSTALL THE RF24 LIBRARY BEFORE UPLOADING THE CODE
   https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define enA 3  //2 -đổi 3 thành 2 do chân 2 không hỗ trợ PWM
#define in1 2  //3
#define in2 4
#define enB 6  //7 - đổi 7 thành 6 do chân 7 không hỗ trợ PWM
#define in3 5
#define in4 7      //6
RF24 radio(8, 9);  // CE, CSN <-- updated 9 -> 10
const byte address[6] = "00001";
char receivedData[32] = "";
int trucNgang, trucDoc;  //giá trị trục ngang/ trục dọc của joysticks
int banhPhai = 0;        //toc do banh phai
int banhTrai = 0;        //toc do banh trai
int tocDoToiDa = 255;    //Tốc độ tối đa của 4 motor
int ideTimer = 0;        // Xử lý trường hợp mất tín hiệu/ tín hiệu không ổn định
int maxIde = 10;
int receivedDataSize = 0;  // kích thước dữ liệu x, y nhận được từ joystick (Byte)
int logEnabled = 0;
void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  //đọc dữ liệu radio từ NRF240L01
  if (radio.available()) {                        //Nếu NRF240L01 nhận được dữ liệu
    receivedDataSize = sizeof(receivedData);      //tính dung lượng dữ liệu vừa nhận
    radio.read(&receivedData, receivedDataSize);  // Đọc dữ liệu vừa nhận và đưa vào mảng kí tự vd: ['1', '0', '2', '3']



    Serial.print("receivedData:  ");
    Serial.print(receivedData);
    trucNgang = atoi(&receivedData[0]);  // Chuyển mảng kí tự thành số nguyên, vd: ['1', '0', '2', '3'] -> 1023
    delay(10);
    radio.read(&receivedData, sizeof(receivedData));
    trucDoc = atoi(&receivedData[0]);
    delay(10);
  } else {
    ideTimer++;
    receivedDataSize = 0;
  }
  if (receivedDataSize == 0) {
    ideTimer++;
  } else {
    ideTimer = 0;
  }

  Serial.print("trucNgang:  ");
  Serial.print(trucNgang);
  Serial.print("trucDoc:  ");
  Serial.print(trucDoc);
  Serial.print(", ideTimer:  ");
  Serial.println(ideTimer);


  // Trục dọc joysticks dùng để điều khiển xe tiến - lùi
  if (trucDoc < 470) {  //Joystick đẩy lùi
    // Motor trái đi lùi
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // Motor phải đi lùi
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // Chuyển đổi giá trị trục dọc của joystick từ 470 - 0 thành tốc độ động cơ từ 0 - 255 (giá trị tín hiệu PWM)
    banhPhai = map(trucDoc, 470, 0, 0, tocDoToiDa);
    banhTrai = map(trucDoc, 470, 0, 0, tocDoToiDa);
  } else if (trucDoc > 550) {  //Joystick đẩy tới
    // Motor trái tiến
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // Motor phải tiến
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // Chuyển đổi giá trị trục dọc của joystick từ 550 - 1023 thành tốc độ động cơ từ 0 - 255 (giá trị tín hiệu PWM)
    banhPhai = map(trucDoc, 550, 1023, 0, tocDoToiDa);
    banhTrai = map(trucDoc, 550, 1023, 0, tocDoToiDa);
  }
  // Nếu joystick ở ví giữa thì 2 motor dừng
  else {
    banhPhai = 0;
    banhTrai = 0;
  }

  // Trục ngang joystick điều khiển xe rẽ trái/phải
  if (trucNgang < 470) {
    // Chuyển đổi trục ngang joystick thành giá trị lệch ngang
    int lechNgang = map(trucNgang, 470, 0, 0, tocDoToiDa);
    // Rẽ trái - giảm tốc độ bánh trái, tăng tốc độ bánh phải
    banhPhai = banhPhai + lechNgang;
    banhTrai = banhTrai - lechNgang;
    // giới hạn giá trị bánh trái, bánh phải chỉ từ 0 -> 255
    if (banhPhai < 0) {
      banhPhai = 0;
    }
    if (banhTrai > tocDoToiDa) {
      banhTrai = tocDoToiDa;
    }
  }
  if (trucNgang > 550) {
    // Chuyển đổi trục ngang joystick từ 550 - 1023 thành giá trị lệch ngang từ 0 đến 255
    int lechNgang = map(trucNgang, 550, 1023, 0, tocDoToiDa);
    // Rẽ phải - giảm tốc độ bánh phải, tăng tốc độ bánh trái
    banhPhai = banhPhai - lechNgang;
    banhTrai = banhTrai + lechNgang;
    // Giới hạn giá trị bánh trái, bánh phải trong khoảng 0-255
    if (banhPhai > tocDoToiDa) {
      banhPhai = tocDoToiDa;
    }
    if (banhTrai < 0) {
      banhTrai = 0;
    }
  }
  // Nếu tốc độ 2 bánh quá thấp thì gán bằng 0, vì giá trị PWM <70 thì motor không thể quay
  if (banhPhai < 70) {
    banhPhai = 0;
  }
  if (banhTrai < 70) {
    banhTrai = 0;
  }

  if (ideTimer > maxIde) {
    banhTrai = 0;
    banhPhai = 0;
  }
  //test revert
  analogWrite(enA, banhTrai);  // Set giá trị PWM (độ rộng xung) cho bánh trái
  analogWrite(enB, banhPhai);  // Set giá trị PWM cho bánh phải

  if (logEnabled == 1) {
    Serial.print(", T: ");
    Serial.print(banhTrai);
    Serial.print(" P: ");
    Serial.println(banhPhai);
  }

  delay(10);
}
