#include "gpio_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Signal handler for clean exit
void signalHandler(int signum) {
    cleanup();
    exit(signum);
}

int main() {
    // Register signal handler for clean exit
    signal(SIGINT, signalHandler);
    
    // Initialize BCM2835 library
    if (!bcm2835_init()) {
        printf("BCM2835 initialization failed\n");
        return 1;
    }
    
    // Initialize pins
    initializePin(LED1_PIN, true);    // LED1 as output
    initializePin(LED2_PIN, true);    // LED2 as output
    initializePin(BUTTON_PIN, false); // Button as input
    
    printf("Binary Counter Started\n");
    printf("Press Ctrl+C to exit\n\n");
    
    int lastCount = -1;  // To track changes
    
    while (1) {
        int count = readButtonPress(BUTTON_PIN);
        
        // Only update display if count has changed
        if (count != lastCount) {
            // Update LEDs to show binary count
            setPin(LED1_PIN, count & 1);    // Least significant bit
            setPin(LED2_PIN, count & 2);    // Most significant bit
            
            printf("Count: %d (Binary: %d%d)\n", 
                   count, 
                   (count & 2) ? 1 : 0, 
                   (count & 1) ? 1 : 0);
            
            lastCount = count;
        }
        
        bcm2835_delay(10); // Small delay to prevent CPU hogging
    }
    
    cleanup();
    return 0;
}
