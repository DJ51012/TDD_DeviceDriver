#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TDD_DeviceDriver/DeviceDriver.cpp"

using namespace testing;

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};


TEST(FlashMock, Read5Times) {
	MockFlashMemoryDevice mockFlash;
	EXPECT_CALL(mockFlash, read)
		.Times(5)
		.WillRepeatedly(Return(1));

	DeviceDriver deviceDriver(&mockFlash);
	EXPECT_THAT(deviceDriver.read(0xF), Eq(1));
}

TEST(FlashMock, ReadException) {
	MockFlashMemoryDevice mockFlash;
	EXPECT_CALL(mockFlash, read)
		.Times(3)
		.WillOnce(Return(1))
		.WillOnce(Return(1))
		.WillOnce(Return(0))
		.WillRepeatedly(Return(1));

	DeviceDriver deviceDriver(&mockFlash);
	EXPECT_THROW({ deviceDriver.read(0xF); }, ReadFailException);
}

TEST(FlashMock, WriteSuccess) {
	MockFlashMemoryDevice mockFlash;
	EXPECT_CALL(mockFlash, read)
		.Times(1)
		.WillRepeatedly(Return(0xFF));

	EXPECT_CALL(mockFlash, write)
		.Times(1);

	DeviceDriver deviceDriver(&mockFlash);
	deviceDriver.write(0xF, 2);
}

TEST(FlashMock, WriteException) {
	MockFlashMemoryDevice mockFlash;
	EXPECT_CALL(mockFlash, read)
		.Times(1)
		.WillRepeatedly(Return(0x1));

	DeviceDriver deviceDriver(&mockFlash);
	EXPECT_THROW({ deviceDriver.write(0xF, 2); }, WriteFailException);
}
