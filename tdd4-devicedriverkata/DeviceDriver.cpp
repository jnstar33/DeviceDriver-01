#include "DeviceDriver.h"

#include <iostream>
#include <windows.h>
#include <exception>

using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::readWithDelay(long address)
{
    Sleep(200);
	return (int)(m_hardware->read(address));
}

int DeviceDriver::read(long address)
{
    int firstReadValue = readWithDelay(address);
    
    for (int i=2 ; i<= TotalReadTryCount ; i++)
    {
	    int nextResult = readWithDelay(address);
        if (firstReadValue == nextResult) continue;
        throw std::exception("Exception!!");
        
    }
    return firstReadValue;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}