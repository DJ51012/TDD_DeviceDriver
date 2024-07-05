#pragma once
class Application {
public:
	Application(DeviceDriver* deviceDriver);
	void ReadAndPrint(long startAddr, long endAddr);
	void WriteAll(int value);
private:
	DeviceDriver* deviceDriver;
};