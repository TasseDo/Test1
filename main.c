#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define SPI_CHANNEL 0
#define SPI_SPEED   500000

#define DC_PIN      8  // GPIO pin for DC
#define RST_PIN     9  // GPIO pin for RST

void setupGPIO() {
    // Set DC and RST pins as outputs
    pinMode(DC_PIN, OUTPUT);
    pinMode(RST_PIN, OUTPUT);
}

void setPinHigh(int pin) {
    digitalWrite(pin, HIGH);
}

void setPinLow(int pin) {
    digitalWrite(pin, LOW);
}

void resetDisplay() {
    setPinLow(RST_PIN);
    delay(100); // Delay in milliseconds
    setPinHigh(RST_PIN);
    delay(100);
}

int main() {
    unsigned char data[2] = {0xA5, 0x5A}; // Example data to send

    // Setup WiringPi
    if (wiringPiSetup() == -1) {
        printf("wiringPi setup failed\n");
        return -1;
    }

    // Setup GPIO pins
    setupGPIO();

    // Reset the display
    resetDisplay();

    // Setup SPI
    if (wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1) {
        printf("wiringPiSPI setup failed\n");
        return -1;
    }

    // Set DC pin for command mode (example usage)
    setPinLow(DC_PIN);
    // Send command byte (example)
    if (wiringPiSPIDataRW(SPI_CHANNEL, data, 1) == -1) {
        printf("SPI data transfer failed\n");
        return -1;
    }

    // Set DC pin for data mode (example usage)
    setPinHigh(DC_PIN);
    // Send data byte (example)
    if (wiringPiSPIDataRW(SPI_CHANNEL, data, 1) == -1) {
        printf("SPI data transfer failed\n");
        return -1;
    }

    // Print received data (example usage)
    printf("Received data: 0x%X 0x%X\n", data[0], data[1]);

    return 0;
}
