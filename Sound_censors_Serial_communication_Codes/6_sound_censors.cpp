// some change
#include "mbed.h"

#define Fs 100
#define T 5
#define N 6
#define L (Fs*T*N)

volatile unsigned short sound[L];
volatile int ptr=0;
Ticker flipper;

// Initialize a pins to perform analog input and digital output functions
AnalogIn   mic1(A0);
AnalogIn   mic2(A1);
AnalogIn   mic3(A2);
AnalogIn   mic4(A3);
AnalogIn   mic5(A4);
AnalogIn   mic6(A5);
DigitalOut led1(LED1);


volatile bool foo;
// float storage[SAMPLE_RATE * TIME_LENGTH * NUM_SOUND];
void log_sound()
{
    foo = 1;
}

#define XXX 20
void send_message()
{
    // flipper.detach();
    // printf("123\n");

    for (int k=0; k<XXX; k++)
    {
        printf("%d ", 0);
        for (int i=0; i<L; i++)
        {
            if (sound[i] == 0)
            {
                sound[i] = 1;
            }
            printf("%d ", sound[i]);
        }
        printf("%d ", ptr+1);
    }
    // flipper.attach(&log_sound, 1/Fs);
}

int main(void)
{       
    int counter = 0;
    foo = 0;
    ptr = 0;
    flipper.attach(&log_sound, 1.0f/Fs);

    while(1)
    {
        if (foo)
        {
            counter++;
            sound[ptr] = 2*mic1.read_u16();
            sound[(ptr+1)%L] = 2*mic2.read_u16();
            sound[(ptr+2)%L] = 2*mic3.read_u16();
            sound[(ptr+3)%L] = 2*mic4.read_u16();
            sound[(ptr+4)%L] = 2*mic5.read_u16();
            sound[(ptr+5)%L] = 2*mic6.read_u16();
            ptr = (ptr + 6) % L;

            if (counter == Fs*10)
            {
                send_message();
            }

            foo = 0;
        }
    }
    // sound[ptr] = mic1.read_u16();
    // sound[ptr+1] = mic2.read_u16();
    // sound[ptr+2] = mic3.read_u16();
    // sound[ptr+3] = mic4.read_u16();
    // sound[ptr+4] = mic5.read_u16();
    // sound[ptr+5] = mic6.read_u16();
    // wait(1);
    // led1 = !led1;
}
