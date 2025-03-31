#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define the CE and CSN pins for Arduino
#define CE_PIN   3
#define CSN_PIN  10

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
    radio.openReadingPipe(1, address);

    // Set the radio to receive mode
    radio.setPALevel(RF24_PA_HIGH);
    radio.startListening();
}

void loop() {

    Serial.println("test loop___________: ");
    // Check if there is data available to read
    if (radio.available()) {
        char text[32] = {0}; // Buffer to store received data
        radio.read(&text, sizeof(text)); // Read the data

        // Print the received data
        Serial.print("Received: ");
        Serial.println(text);
    }
}