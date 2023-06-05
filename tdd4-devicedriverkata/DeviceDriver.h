#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int readWithDelay(long address);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
private:
    const int TotalReadTryCount = 5;
};