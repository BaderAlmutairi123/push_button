#include "gpio_input.h"
#include <stdio.h>

static int buttonPressCount = 0;
static bool lastButtonState = false;

void initializePin(int pin, bool isOutput) {
    if (isOutput) {
        bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
    } else {
        bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
        bcm2835_gpio_set_pud(pin, BCM2835_GPIO_PUD_UP);
    }
}

void setPin(int pin, bool value) {
    bcm2835_gpio_write(pin, value);
}

int readPin(int pin) {
    return bcm2835_gpio_lev(pin);
}

int readButtonPress(int pin) {
    bool currentState = !readPin(pin);  // Invert because pull-up resistor
    
    // Button press detected (transition from not pressed to pressed)
    if (currentState && !lastButtonState) {
        buttonPressCount++;
        // Small delay for debouncing
        bcm2835_delay(50);
    }
    
    lastButtonState = currentState;
    return buttonPressCount;
}

void cleanup(void) {
    bcm2835_close();
}
