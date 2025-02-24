#include <SoftwareSerial.h>
SoftwareSerial mySerial(A4, A5); // RX, TX
int PIN_EN_OUT = 4;
int PIN_STATE_IN = 5;

//L298N
#define IN1_A 4
#define IN2_A 5
#define e_A 6


#define IN1_B 7
#define IN2_B 8
#define e_B 9
#define MAX_SPEED 255 //từ 0-255
#define MIN_SPEED 0
#define SPEED 60

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
  Serial.println("nv___banh A Tien");
}

void banhALui(int speed) {
  digitalWrite(IN1_A, LOW);
  digitalWrite(IN2_A, HIGH);
  analogWrite(e_A, speed);
  Serial.println("nv___banh A Lui");

}

void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600);
  Serial.begin(9600);

  sendCommand("AT");
  sendCommand("AT+ROLE0");
  sendCommand("AT+UUID0xFFE0");
  sendCommand("AT+CHAR0xFFE1");
  sendCommand("AT+NAMEAT09-Tung");
}

void sendCommand(const char * command) {
  Serial.print("Command send :");
  Serial.println(command);
  mySerial.println(command);
  //wait some time
  delay(100);

  char reply[100];
  int i = 0;
  while (mySerial.available()) {
    reply[i] = mySerial.read();
    i += 1;
  }
  //end the string
  reply[i] = '\0';
  Serial.print(reply);
  Serial.println("Reply end");
}

void readSerial() {
  char reply[50];
  char lastCommand;
  int i = 0;
  while (mySerial.available()) {
    reply[i] = mySerial.read();
    lastCommand = reply[i];
    Serial.println("nv___reading__" + String(lastCommand));
    i += 1;

    if (lastCommand == 'F') { //46
      banhATien(SPEED);
    } else if (lastCommand == 'B') { //42
      banhALui(SPEED);
    } else if (lastCommand == 'S') { //53
      banhADung();
    }

  }
  //end the string
  reply[i] = '\0';
  if (strlen(reply) > 0) {
    Serial.println(reply);
    Serial.println("We have just read some data");
    Serial.println("nv___handleLast command: " + String(lastCommand));
    //if (lastCommand == 'F' || lastCommand == 'R') { //46
    //      banhATien(SPEED);
    //    } else if (lastCommand == 'B' || lastCommand == 'L') { //42
    //      banhALui(SPEED);
    //    } else if (lastCommand == 'S') { //53
    //      banhADung();
    //    } else {
    //      Serial.println("But DO NOTHING");
    //    }


    //    if (strcmp(reply, "F") == 0) { //46
    //      banhATien(SPEED);
    //    } else if (strcmp(reply, "B") == 0) { //42
    //      banhALui(SPEED);
    //    } else if (strcmp(reply, "S") == 0) { //53
    //      banhADung();
    //    } else {
    //      Serial.println("But DO NOTHING");
    //    }


    //    switch (strlen(reply)) {
    //      case "F": //46
    //        banhATien(SPEED);
    //
    //      case "B": //42
    //        banhALUI(SPEED);
    //
    //      default:
    //        break;
    //    }
  }
}

char j = 0;
void loop() {
  readSerial();
  //  writeToBLE(j);
  //  j += 1;
  delay(2000);
}

void writeToBLE(char value) {
  Serial.print("Writing hex :");
  Serial.println(value, HEX);
  mySerial.write(value);
}
