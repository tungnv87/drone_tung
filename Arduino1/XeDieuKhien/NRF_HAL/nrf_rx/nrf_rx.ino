/*
   Copyright (c) 2015,2016,2020 Piotr Stolarz for the Ardiono port

   This software is distributed WITHOUT ANY WARRANTY; without even the
   implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the License for more information.
*/

#include <SPI.h>
#include <nrf_hal.h>
#include <SoftwareSerial.h>

// if 1 - write some info to the serial output
#define INFO_ON_SERIAL   1

// nRF communication channel (1MHz wide)
#define CHANNEL     20

// nRF Chip Enable (CE) pin
#define CE_PIN      6
// SPI CS (slave select) pin
#define CS_PIN      10
// blinking LED pin
//#define LED_PIN     8

#define chip_enable()   digitalWrite(CE_PIN, HIGH)
#define chip_disable()  digitalWrite(CE_PIN, LOW)

static uint8_t rx[NRF_MAX_PL] = {};
static int cnt = 0;
static uint8_t led_val = LOW;

//bluetooth
SoftwareSerial mySerial(A4, A5); // RX, TX
const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data
char receivedXChars[10];   // an array to store the received X data
char receivedYChars[10];   // an array to store the received X data
boolean newData = false;

int bluetoothNotAvailableCount = 0;


#define enA 2
#define in1 3
#define in2 4
#define enB 8
#define in3 5
#define in4 7

int  xAxis, yAxis;
int motorSpeedA = 0;
int motorSpeedB = 0;

//#define toggle_led() \
//  digitalWrite(LED_PIN, (led_val==LOW ? (led_val=HIGH) : (led_val=LOW)))


void setup()
{
  setupBluetooth();
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // CE as output
  pinMode(CE_PIN, OUTPUT);
  chip_disable();

  // init LED
  //  pinMode(LED_PIN, OUTPUT);
  //  digitalWrite(LED_PIN, led_val);

#if INFO_ON_SERIAL
  Serial.begin(115200);
#endif

  // SPI init
  SPI.begin();
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

  // init NRF HAL
  hal_nrf_set_cs_pin(CS_PIN);

  restart_rx();

#if INFO_ON_SERIAL
  uint8_t addr[5];
  char sp_buf[48];

  hal_nrf_get_address(HAL_NRF_PIPE0, addr);
  sprintf(sp_buf, "P0 addr: %02x:%02x:%02x:%02x:%02x",
          addr[0], addr[1], addr[2], addr[3], addr[4]);
  Serial.println(sp_buf);

  Serial.println("Tuned up, waiting for messages...");
#endif
}

/* RX loop */
void loop()
{

  readSerial();
  delay(20);

  //  //NRF handle
  //    uint8_t irq_flg;
  //
  //    irq_flg = hal_nrf_get_clear_irq_flags();
  //    if (irq_flg & (1U << HAL_NRF_RX_DR))
  //    {
  //      /* read RX FIFO of received messages */
  //      while (!hal_nrf_rx_fifo_empty())
  //      {
  //        hal_nrf_read_rx_payload(rx);
  //        if (rx[0] == 0xAB)
  //        {
  //          //        toggle_led();
  //
  //          xAxis = atoi((const char *)&rx[1]);
  //          yAxis = atoi((const char *)&rx[6]);
  //  #if INFO_ON_SERIAL
  //          Serial.println("Received: \"");
  //          Serial.println(String(xAxis) + ", " + String(yAxis));
  //  #endif
  //          handleAxisChanged();
  //
  //          // Set Motor A backward
  //
  //        }
  //        cnt = 0;
  //      }
  //    }
  //
  //    // for unknown reason, from time to time, RX seems to be locking in and
  //    // stops to detect incoming traffic until restarting the transceiver
  //    if (cnt >= 5000)
  //    {
  //      cnt = 0;
  //      restart_rx();
  //    } else {
  //      delayMicroseconds(1000);
  //      cnt++;
  //    }
}


void setupBluetooth() {
  // put your setup code here, to run once:
  mySerial.begin(9600);
  //  Serial.begin(9600);

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
  //    char reply[50];
  //    char lastCommand;
  //    int i = 0;
  //  Serial.println("nv___reply: ");
  //  //  Serial.println(reply);
  //  while (mySerial.available()) {
  //    reply[i] = mySerial.read();
  //    lastCommand = reply[i];
  //    Serial.println("nv___reading__" + String(lastCommand));
  //    i += 1;
  //
  //    //    if (lastCommand == 'F') { //46
  //    //      banhATien(SPEED);
  //    //    } else if (lastCommand == 'B') { //42
  //    //      banhALui(SPEED);
  //    //    } else if (lastCommand == 'S') { //53
  //    //      banhADung();
  //    //    }
  //
  //  }

  //
  //  Serial.println("nv___reading__" + String(lastCommand));
  //
  //
  //  //end the string
  //  reply[i] = '\0';
  //  if (strlen(reply) > 0) {
  //    Serial.println(reply);
  //    Serial.println("We have just read some data");
  //    Serial.println("nv___handleLast command: " + String(lastCommand));
  //  }

  recvWithEndMarker();
  showNewData();
}


void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
  if (mySerial.available() == 0) {
    bluetoothNotAvailableCount++;
    if (bluetoothNotAvailableCount == 5) { //if not received signal in 5 times, stop car
    stopCar();
    }
  }
  while (mySerial.available() > 0 && newData == false) {
    rc = mySerial.read();
    //    Serial.println("nv___recvWithEndMarker_" + String(rc));
    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void showNewData() {
  if (newData == true) {
    //    Serial.print("This just in ... ");
    //    Serial.println(receivedChars);
    newData = false;
    bluetoothNotAvailableCount = 0;

    char* ptr = strtok(receivedChars, "|");
    byte i = 0;
    Serial.println(F("x\ty"));
    int axisX = 0;
    int axisY = 0;
    while (ptr) { // ptr is the ASCII text we want to transform into an integer
      if (i == 0) {
        axisX = atol(ptr); // atol(ptr) will be your long int you could store in your array at position i. atol() info at http://www.cplusplus.com/reference/cstdlib/atol
      } else if (i == 1) {
        axisY = atol(ptr);
      }

      ptr = strtok(NULL, "|");
      i++;
    }

    Serial.println("xyAxis: (" + String(axisX) + ", " + String(axisY) + ")");
    xAxis = axisX;
    yAxis = axisY;
    bluetoothAxisHandle();
  }
}

void backward() {
  // Set Motor A backward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // Set Motor B backward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  motorSpeedA = map(abs(yAxis), 0, 40, 0, 255);
  motorSpeedB = map(abs(yAxis), 0, 40, 0, 255);
  Serial.println("Move backward: " + String(motorSpeedA) + ", " + String(motorSpeedB));
  //  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  //  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
  applySpeed();
}

void forward() {
  // Set Motor A forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // Set Motor B forward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
  motorSpeedA = map(abs(yAxis), 0, 40, 0, 255);
  motorSpeedB = map(abs(yAxis), 0, 40, 0, 255);

  Serial.println("Move forward: " + String(motorSpeedA) + ", " + String(motorSpeedB));
  //  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  //  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
  applySpeed();
}

void moveLeft() {
  // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
  int xMapped = map(xAxis, 40, 0, 0, 255);
  // Move to left - decrease left motor speed, increase right motor speed
  motorSpeedA = motorSpeedA + xMapped;
  motorSpeedB = motorSpeedB - xMapped;
  // Confine the range from 0 to 255
  if (motorSpeedA < 0) {
    motorSpeedA = 0;
  }
  if (motorSpeedB > 255) {
    motorSpeedB = 255;
  }

  Serial.println("Move left: " + String(motorSpeedA) + ", " + String(motorSpeedB));
}

void bluetoothAxisHandle() {
  // Y-axis used for forward and backward control
  if (yAxis < 0) {
    backward();
    delay(10);
  }
  else if (yAxis > 0) {
    forward();
    delay(10);
  }
  // If joystick stays in middle the motors are not moving
  else {
    motorSpeedA = 0;
    motorSpeedB = 0;
  }
  // X-axis used for left and right control
  if (xAxis > 0) {
    // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
    int xMapped = map(abs(xAxis), 40, 0, 0, 255);
    // Move to left - decrease left motor speed, increase right motor speed
    motorSpeedA = motorSpeedA + xMapped;
    motorSpeedB = motorSpeedB - xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA < 0) {
      motorSpeedA = 0;
    }
    if (motorSpeedB > 255) {
      motorSpeedB = 255;
    }

    Serial.println("Move left: " + String(motorSpeedA) + ", " + String(motorSpeedB));
  }
  if (xAxis < 0) {
    // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
    int xMapped = map(abs(xAxis), 40, 0, 0, 255);
    // Move right - decrease right motor speed, increase left motor speed
    motorSpeedA = motorSpeedA - xMapped;
    motorSpeedB = motorSpeedB + xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA > 255) {
      motorSpeedA = 255;
    }
    if (motorSpeedB < 0) {
      motorSpeedB = 0;
    }

    Serial.println("Move right: " + String(motorSpeedA) + ", " + String(motorSpeedB));
  }
  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  if (motorSpeedA < 70) {
    motorSpeedA = 0;
  }
  if (motorSpeedB < 70) {
    motorSpeedB = 0;
  }
  applySpeed();
  delay(10);
}

void applySpeed() {
  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
}

void stopCar() {
  Serial.println("Stop car");
  // Set Motor A backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  // Set Motor B backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0); // Send PWM signal to motor A
  analogWrite(enB, 0); // Send PWM signal to motor B
}

void handleAxisChanged() {
  // Y-axis used for forward and backward control
  if (yAxis < 470) {
    // Set Motor A backward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // Set Motor B backward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 470, 0, 0, 255);
    motorSpeedB = map(yAxis, 470, 0, 0, 255);
    Serial.println("Move backward: " + String(motorSpeedA) + ", " + String(motorSpeedB));
    analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
    analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
    delay(20);
  }
  else if (yAxis > 550) {
    // Set Motor A forward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // Set Motor B forward
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(yAxis, 550, 1023, 0, 255);
    motorSpeedB = map(yAxis, 550, 1023, 0, 255);

    Serial.println("Move forward: " + String(motorSpeedA) + ", " + String(motorSpeedB));
    analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
    analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
    delay(20);
  }
  // If joystick stays in middle the motors are not moving
  else {
    motorSpeedA = 0;
    motorSpeedB = 0;

    //    Serial.println("Not moving: " + String(motorSpeedA) + ", " + String(motorSpeedB));
  }
  // X-axis used for left and right control
  if (xAxis < 470) {
    // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
    int xMapped = map(xAxis, 470, 0, 0, 255);
    // Move to left - decrease left motor speed, increase right motor speed
    motorSpeedA = motorSpeedA + xMapped;
    motorSpeedB = motorSpeedB - xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA < 0) {
      motorSpeedA = 0;
    }
    if (motorSpeedB > 255) {
      motorSpeedB = 255;
    }

    Serial.println("Move left: " + String(motorSpeedA) + ", " + String(motorSpeedB));
  }
  if (xAxis > 550) {
    // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
    int xMapped = map(xAxis, 550, 1023, 0, 255);
    // Move right - decrease right motor speed, increase left motor speed
    motorSpeedA = motorSpeedA - xMapped;
    motorSpeedB = motorSpeedB + xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA > 255) {
      motorSpeedA = 255;
    }
    if (motorSpeedB < 0) {
      motorSpeedB = 0;
    }

    Serial.println("Move right: " + String(motorSpeedA) + ", " + String(motorSpeedB));
  }
  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  if (motorSpeedA < 70) {
    motorSpeedA = 0;
  }
  if (motorSpeedB < 70) {
    motorSpeedB = 0;
  }
  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
  delay(10);
}

void init_rx()
{
  hal_nrf_flush_rx();
  hal_nrf_flush_tx();

  // clear all extra features for the purpose of this example
  hal_nrf_enable_dynamic_payload(false);
  hal_nrf_enable_ack_payload(false);
  hal_nrf_enable_dynamic_ack(false);

  hal_nrf_set_rf_channel(CHANNEL);
  hal_nrf_set_datarate(HAL_NRF_1MBPS);
  hal_nrf_set_crc_mode(HAL_NRF_CRC_16BIT);

  // RX setup: use default pipe 0 address
  hal_nrf_set_operation_mode(HAL_NRF_PRX);

  hal_nrf_close_pipe(HAL_NRF_ALL);
  hal_nrf_config_rx_pipe(HAL_NRF_PIPE0, NULL, true, NRF_MAX_PL);

  // TX output power for auto ack
  hal_nrf_set_output_power(HAL_NRF_0DBM);
}

void restart_rx()
{
  stopCar();
  chip_disable();

  hal_nrf_set_power_mode(HAL_NRF_PWR_DOWN);
  delayMicroseconds(1000);

  hal_nrf_set_power_mode(HAL_NRF_PWR_UP);
  delayMicroseconds(1500);

  init_rx();

  chip_enable();
  delayMicroseconds(150);
}
