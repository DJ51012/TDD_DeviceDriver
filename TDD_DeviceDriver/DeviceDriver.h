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
    FlashMemoryDevice* m_hardware;
};