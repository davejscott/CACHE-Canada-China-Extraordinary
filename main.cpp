#include "mbed.h"

// Initialize a pins to perform analog input and digital output functions
AnalogIn   loudness(A5);
DigitalOut dout(LED1);

int main(void)
{
    while (1) {
        // test the voltage on the initialized analog pin
        //  and if greater than 0.3 * VCC set the digital pin
        //  to a logic 1 otherwise a logic    
        //printf("hellod world");    
        // print the percentage and 16 bit normalized values
           printf("loudness: %3.3f%%\n", loudness.read()*100.0f);
        // printf("    ");
        wait(0.1f);
    }
}
