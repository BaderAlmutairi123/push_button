#ifndef GPIO_INPUT_H
#define GPIO_INPUT_H

#include <bcm2835.h>
#include <stdbool.h>

// Function prototypes
void initializePin(int pin, bool isOutput);
void setPin(int pin, bool value);
int readPin(int pin);
int readButtonPress(int pin);
void cleanup(void);

// Constants for LED pins
#define LED1_PIN RPI_GPIO_P1_11  // For least significant bit
#define LED2_PIN RPI_GPIO_P1_13  // For most significant bit
#define BUTTON_PIN RPI_GPIO_P1_15

#endif // GPIO_INPUT_H
