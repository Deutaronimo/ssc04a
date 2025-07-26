#include<iostream>
#include<fcntl.h>
#include<termios.h>
#include<unistd.h>
#include<cstdint>
#include<chrono>
#include<thread>
#include"ssc.hpp"

SSC::SSC()
{

    serialPort = open(portName, O_RDWR | O_NOCTTY | O_NDELAY);

	if (serialPort < 0) 
	{
	    std::cout << RED ;
	    std::cerr << "Failed to open port: " << portName << std::endl;
            
        }
        
	std::cout << GREEN ;
        
	std::cout << "Serial port opened: " << std::endl;
	
	std::cout << RESET;

	configurePorts();
}


SSC::~SSC()
{
    close(serialPort);
    std::cout << "Closed serial port to SSC." << std::endl;
}


void SSC::configurePorts()
{
    // Configure port
    tcgetattr(serialPort, &options);

    cfsetispeed(&options, B9600); // Qik default baud rate
    cfsetospeed(&options, B9600);

    options.c_cflag &= ~PARENB; // No parity
    options.c_cflag &= ~CSTOPB; // One stop bit
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;     // 8 data bits
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;

    tcflush(serialPort, TCIFLUSH);
    tcsetattr(serialPort, TCSANOW, &options);
}

// Sets the behaviour parameters on the servo.
void SSC::setParameters(byte servo, byte data)
{
    if(servo < 0 | servo > 7)
	{
		std::cout << "Servo # out of range. [0-7] \n";
		return;
	}
    uint8_t command[5] = {STARTBYTE, DEVICEID, command_setParameters, servo, data};
	write(serialPort,command, sizeof(command));
    delay(5);
}

// Sets speed of move, 0 is fastest, nonzero is slower.
void SSC::setSpeed(byte servo, byte speed)
{
    if(speed < 0 | speed > 127)
	{
		std::cout << "Speed is out of range. [0-127]\n";
		return;
	}

    if(servo < 0 | servo > 7)
	{
		std::cout << "Servo # out of range. [0-7] \n";
		return;
	}
    uint8_t command[5] = {STARTBYTE, DEVICEID, command_setSpeed, servo, speed};
	write(serialPort,command, sizeof(command));
    delay(5);
}

// Puts the thread to sleep for x Milliseconds to create a delay.
void delay (int duration)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

