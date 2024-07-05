#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TDD_DeviceDriver/DeviceDriver.cpp"
#include "../TDD_DeviceDriver/Application.cpp"

using namespace testing;

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class DeviceDriverFixture : public testing::Test {
public:
	MockFlashMemoryDevice mockFlash;

	const long TEST_ADDRESS = 0x1234;
	const int WRITE_VALUE = 0xABCD;
private:

};


TEST_F(DeviceDriverFixture, Read5Times) {
	EXPECT_CALL(mockFlash, read(TEST_ADDRESS))
		.Times(5)
		.WillRepeatedly(Return(1));

	DeviceDriver deviceDriver(&mockFlash);
	EXPECT_THAT(deviceDriver.read(TEST_ADDRESS), Eq(1));
}

TEST_F(DeviceDriverFixture, ReadException) {
	EXPECT_CALL(mockFlash, read(TEST_ADDRESS))
		.Times(3)
		.WillOnce(Return(1))
		.WillOnce(Return(1))
		.WillOnce(Return(0))
		.WillRepeatedly(Return(1));

	DeviceDriver deviceDriver(&mockFlash);
	EXPECT_THROW({ deviceDriver.read(TEST_ADDRESS); }, ReadFailException);
}

TEST_F(DeviceDriverFixture, WriteSuccess) {
	EXPECT_CALL(mockFlash, read(TEST_ADDRESS))
		.Times(1)
		.WillRepeatedly(Return(0xFF));

	EXPECT_CALL(mockFlash, write(TEST_ADDRESS, WRITE_VALUE))
		.Times(1);

	DeviceDriver deviceDriver(&mockFlash);
	deviceDriver.write(TEST_ADDRESS, WRITE_VALUE);
}

TEST_F(DeviceDriverFixture, WriteException) {
	EXPECT_CALL(mockFlash, read(TEST_ADDRESS))
		.Times(1)
		.WillRepeatedly(Return(0x1));

	DeviceDriver deviceDriver(&mockFlash);
	EXPECT_THROW({ deviceDriver.write(TEST_ADDRESS, WRITE_VALUE); }, WriteFailException);
}


// Application
TEST_F(DeviceDriverFixture, AppRead) {
	EXPECT_CALL(mockFlash, read(0))
		.Times(5)
		.WillRepeatedly(Return(1));
	EXPECT_CALL(mockFlash, read(1))
		.Times(5)
		.WillRepeatedly(Return(2));
	EXPECT_CALL(mockFlash, read(2))
		.Times(5)
		.WillRepeatedly(Return(3));
	EXPECT_CALL(mockFlash, read(3))
		.Times(5)
		.WillRepeatedly(Return(4));
	EXPECT_CALL(mockFlash, read(4))
		.Times(5)
		.WillRepeatedly(Return(5));

	DeviceDriver deviceDriver(&mockFlash);
	Application app(&deviceDriver);
	app.ReadAndPrint(0x0, 0x4);
}

TEST_F(DeviceDriverFixture, AppWrite) {
	EXPECT_CALL(mockFlash, read)
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(mockFlash, write(0, WRITE_VALUE));
	EXPECT_CALL(mockFlash, write(1, WRITE_VALUE));
	EXPECT_CALL(mockFlash, write(2, WRITE_VALUE));
	EXPECT_CALL(mockFlash, write(3, WRITE_VALUE));
	EXPECT_CALL(mockFlash, write(4, WRITE_VALUE));

	DeviceDriver deviceDriver(&mockFlash);
	Application app(&deviceDriver);
	app.WriteAll(WRITE_VALUE);
}
