#pragma once
#include <exception>
#include "FlashMemoryDevice.h"

class ReadFailException : public std::exception {
};

class WriteFailException : public std::exception {
};

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    const int CLEAN_DATA = 0xFF;
    FlashMemoryDevice* m_hardware;
};