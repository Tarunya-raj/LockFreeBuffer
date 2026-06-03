#include "../3rdParty/googletest/googletest/include/gtest/gtest.h"
#include <stdexcept>
#include <string>
#include "../examples/circularBuffer/circularBuffer.cpp"

TEST(CircularBufferConstructor, ValidCapicity)
{
	CircularBuffer<int> buffer(8);
	EXPECT_EQ(buffer.getCapacity(), 8);
	EXPECT_EQ(buffer.getSize(), 0);

}

TEST(CircularBufferConstructor, ZeroCapacityThrow)
{
	EXPECT_THROW(CircularBuffer<int>(0),std::invalid_argument);
}

TEST(CircularBufferConstructor, CheckCapacity)
{
	CircularBuffer<int> buffer(2);
	EXPECT_EQ(buffer.getCapacity(),2);
	EXPECT_TRUE(buffer.isEmpty());
}

TEST(CircularBufferState, EmptyBuffer)
{
	CircularBuffer<std::string> buffer(4);
	EXPECT_TRUE(buffer.isEmpty());
	EXPECT_FALSE(buffer.isFull());
}

TEST(CircularBufferState, FullBuffer)
{
	CircularBuffer<std::string> buffer(4);
	buffer.push("First Element");
	buffer.push("Second Element");
	buffer.push("third Element");
	buffer.push("fourth Element");
	EXPECT_TRUE(buffer.isFull());
	EXPECT_FALSE(buffer.isEmpty());
	EXPECT_EQ(buffer.getSize(), 4);
	EXPECT_EQ(buffer.getCapacity(), 4);
}

TEST(CircularBufferState, PartiallyFilledBuffer)
{
	CircularBuffer<std::string> buffer(4);
	buffer.push("First Element");
	EXPECT_FALSE(buffer.isEmpty());
	EXPECT_FALSE(buffer.isFull());
	EXPECT_EQ(buffer.getSize(), 1);
	EXPECT_EQ(buffer.getCapacity(), 4);
}

TEST(CircularBufferPush, SizeIncrement)
{
	CircularBuffer<int> buffer(4);
	buffer.push(1);
	EXPECT_EQ(buffer.getSize(), 1);
	buffer.push(2);
	EXPECT_EQ(buffer.getSize(), 2);
}

TEST(CirculartBufferPush, PushtoOverflow)
{
	CircularBuffer<int> buffer(2);
	buffer.push(1);
	buffer.push(2);
	buffer.push(3); //data discarded.
	EXPECT_EQ(buffer.getSize(),2); 
	EXPECT_EQ(buffer.front(), 1); //oginal data intact

}

TEST(CircularBufferPop, PopDecrementSize)
{
	CircularBuffer<int> buffer(2);
	buffer.push(10);
	buffer.push(42);
	EXPECT_EQ(buffer.getSize(), 2);
	EXPECT_EQ(buffer.pop(), 42);
	EXPECT_EQ(buffer.getSize(), 2);
}
TEST(CircularBufferPop, PopFromEmptyThrows)
{
	CircularBuffer<int> buffer(5);
	EXPECT_THROW(buffer.pop(), std::underflow_error);
}
TEST(CircularBufferPop, FIFOOrdering)
{
	CircularBuffer<int> buf(4);
	buf.push(10);
	buf.push(20);
	buf.push(30);
	EXPECT_EQ(buf.pop(), 10);
	EXPECT_EQ(buf.pop(), 20);
	EXPECT_EQ(buf.pop(), 30);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}