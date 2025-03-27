#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define the CE and CSN pins
#define CE_PIN   PB1
#define CSN_PIN  PB0

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Define the address for the pipe
const byte address[6] = "00001";

void setup() {
    // Start the serial communication
    Serial.begin(9600);

    // Initialize the radio
    if (!radio.begin()) {
        Serial.println("NRF24L01 module not detected");
        while (1);
    }

    // Set the address for the pipe
    radio.openWritingPipe(address);

    // Set the radio to transmit mode
    radio.setPALevel(RF24_PA_HIGH);
    radio.stopListening();
}

void loop() {
    // Data to send
    const char text[] = "Hello, world";

    // Send the data
    if (radio.write(&text, sizeof(text))) {
        Serial.println("Data sent successfully");
    } else {
        Serial.println("Failed to send data");
    }

    // Wait for a second before sending again
    delay(1000);
}