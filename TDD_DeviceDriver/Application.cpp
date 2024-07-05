#include <iostream>
#include "DeviceDriver.h"
#include "Application.h"

Application::Application(DeviceDriver* deviceDriver) : deviceDriver(deviceDriver) {
}

void Application::ReadAndPrint(long startAddr, long endAddr) {
	for (long addr = startAddr; addr <= endAddr; addr++) {
		std::cout << "Address: " << addr << " Data: " << deviceDriver->read(addr) << std::endl;
	}
}

void Application::WriteAll(int value) {
	for (long addr = 0; addr <= 4; addr++) {
		deviceDriver->write(addr, value);
	}
}