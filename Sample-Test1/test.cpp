#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../tdd4-devicedriverkata/DeviceDriver.cpp"

using namespace testing;
using namespace std;

class MockFlashMemoryDevice : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriverTest, FiveRead) {
	MockFlashMemoryDevice mockFlash;

	EXPECT_CALL(mockFlash, read)
		.Times(5);

	DeviceDriver driver(&mockFlash);
	driver.read(0xA);
}

TEST(DeviceDriverTest, Exception) {
	MockFlashMemoryDevice mockFlash;
	EXPECT_CALL(mockFlash, read)
		.WillOnce(Return(77))
		.WillOnce(Return(77))
		.WillOnce(Return(77))
		.WillOnce(Return(77))
		.WillOnce(Return(1));

	DeviceDriver driver(&mockFlash);
	EXPECT_THROW(driver.read(0x33), ReadFailException);
}

TEST(DeviceDriverTest, Read) {
	MockFlashMemoryDevice mockFlash;
	EXPECT_CALL(mockFlash, read)
		.WillOnce(Return(77))
		.WillOnce(Return(77))
		.WillOnce(Return(77))
		.WillOnce(Return(77))
		.WillOnce(Return(77));

	DeviceDriver driver(&mockFlash);
	int actual = driver.read(0x00);
	EXPECT_THAT(77, Eq(actual));
}

