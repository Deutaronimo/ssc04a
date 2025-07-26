#include<iostream> 
#include<fcntl.h>
#include<termios.h>
#include<unistd.h>
#include<cstdint>
#include<string>
#include<chrono>
#include<thread>

#define RESET  "\033[0m"
#define BOLD   "\033[1m"
#define RED    "\033[31m"
#define GREEN  "\033[32m"
#define YELLOW "\033[33m"
#define BLUE   "\033[34m"
#define CYAN   "\033[36m"
#define CLEARSCREEN = "\033[2J\033[1;1H";

typedef uint8_t byte;


class SSC
{
    const char* portName = "/dev/ttyS0";
    int serialPort = 0;

    termios options;

    byte STARTBYTE = 0x80;
    byte DEVICEID  = 0x01;

    byte command_setParameters       = 0x00;
    byte command_setSpeed            = 0x01;
    byte command_SetPosition         = 0x02;
    byte command_SetPosition_8bit    = 0x03;
    byte command_SetPositionAbsolute = 0x04;
    byte command_SetNeutral          = 0x05;

    public:

    SSC();
    ~SSC();

    void configurePorts();
    void setParameters(byte servo, byte data);
    void setSpeed(byte servo, byte speed);
    void setPosition(byte servo, byte position);
    void setPosition_8bit(byte servo, byte position);
    void setPositionAbsolute(byte servo, byte position);
    void setNeutral(byte servo, byte position);
    
};

void delay(int time);