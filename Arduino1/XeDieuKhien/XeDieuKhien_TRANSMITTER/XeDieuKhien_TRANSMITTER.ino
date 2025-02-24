/*Arduino JOYSTICK CONTROLLED CAR (TRANSMITTER)
          
YOU HAVE TO INSTALL THE RF24 LIBRARY BEFORE UPLOADING THE CODE
   https://github.com/tmrh20/RF24/      
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(8,9); // CE, CSN
const byte address[6] = "00001";
char xyData[32] = ""; // Mảng dữ liệu sẽ gửi đi
String trucNgang, trucDoc;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {
  trucNgang = analogRead(A1); // Đọc dữ liệu trục ngang từ joystick
  trucDoc = analogRead(A0); // Đọc dữ liệu trục dọc từ joystick
  // X value
  trucNgang.toCharArray(xyData, 5); // Ghi giá trị trục ngang lên mảng dữ liệu sẽ gửi đi
  radio.write(&xyData, sizeof(xyData)); // Ghi dữ liệu trục ngang để NRF24L01 truyền đi

  // Y value
  trucDoc.toCharArray(xyData, 5); // Chuyển giá trị trục dọc thành mảng kí tự
  radio.write(&xyData, sizeof(xyData)); // Ghi dữ liệu trục dọc để NRF24L01 truyền đi

  Serial.print("nv__data: x: ");
  Serial.print(trucNgang);
  Serial.print(", y: ");
  Serial.println(trucDoc);
  delay(20);
}
