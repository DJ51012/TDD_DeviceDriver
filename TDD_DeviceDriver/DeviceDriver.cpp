#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int prevData = (int)(m_hardware->read(address));
    for (int i = 0; i < 4; i++) {
        int data = (int)(m_hardware->read(address));
        if (prevData != data) {
            throw ReadFailException();
        }
        prevData = data;
    }
    return prevData;
}

void DeviceDriver::write(long address, int data)
{
    int readData = (int)(m_hardware->read(address));
    if (readData != 0xFF)
        throw WriteFailException();
    m_hardware->write(address, (unsigned char)data);
}