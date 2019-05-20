#pragma once
#include "mbed.h"
//#include "global.h"
#include "ov7670sreg.h"
//#include "SDFileSystem.h"
#include "SPI_TFT_ILI9341.h"
#include "FastPWM.h"


#define OV7670_WRITE (0x42)
#define OV7670_READ  (0x43)
#define OV7670_REGMAX (201)
#define OV7670_I2CFREQ (100) //us half period
#define CAMERA_CLK_PERIOD 0.35//micro second 0.35

extern const int tmarray ;
extern char desfile[25];
extern Serial pc;
extern Timer Time;
extern bool Done;
extern bool Doneaff;
extern bool volatile captur;
extern unsigned char bank[];
extern unsigned char bankf[];
extern SPI_TFT_ILI9341 TFT;
extern FILE *fp;



class OV7670
{
public:

    OV7670(
        PinName siod,    // Camera I2C port data
        PinName sioc,  // Camera I2C port clock
        PinName xclk, //  XCLK
        //PinName vs, // VSYNC
        //PinName hr, // HREF
        // PinName pclk,      // Pixelclock
        PortName port,
        int mask,
        /*
        VSYNC
        HREF
        Pixelclock
        PinName d7, // D7
        PinName d6, // D6
        PinName d5, // D5
        PinName d4, // D4
        PinName d3, // D3
        PinName d2, // D2
        PinName d1, // D1
        PinName d0, // D0 */
        PinName rst // /RESET
    );

    void InitQQVGA() ;
    void WriteBy(int addr);    // write to camera
    void WriteReg2(int data);    // write to camera
    void WriteReg(int subad,int data);    // write to camera
    int ReadReg(int subad);               // read from camera
    int ReadBy(void);
    void Reset(void);                    // reset reg camera
    void Start(void);
    void End (void);
    void CaptureNext(void);
    void capture(void);
    unsigned char reverse(unsigned char b);
    void exrgbf(int j);
    int ar(float a);
    int Init(char *format, int n);
    int  PixelCounter ;



private:
    DigitalInOut _siod;
    DigitalOut _sioc;
    FastPWM _xclk;
    // DigitalIn _pclk;
    //DigitalIn _vs;
    //DigitalIn _hr;
    PortIn data;
    /*
        DigitalIn _vs;
        DigitalIn _hr;
         DigitalIn _pclk;
           DigitalIn d7;
           DigitalIn d6;
           DigitalIn d5;
           DigitalIn d4;
           DigitalIn d3;
           DigitalIn d2;
           DigitalIn d1;
           DigitalIn d0;
        */
    DigitalOut _rst;
};