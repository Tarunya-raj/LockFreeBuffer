#include "../3rdParty/googletest/googletest/include/gtest/gtest.h"
#include <stdexcept>
//#include "../examples/circularBuffer/circularBuffer.h"
#include "../examples/producerConsumer/SPSC_mutex.h"
#include <atomic>
#include <thread>
using namespace UD;
TEST(MutexSPSCQueueTest, Constructor)
{
	EXPECT_NO_THROW(MutexSPSCQueue<int> queue(5));
}

TEST(MutexSPSCQueueTest, ProduceConsumeSingleElement)
{
	MutexSPSCQueue<int> queue(5);
	queue.produce(5);
	EXPECT_EQ(queue.consume(), 5);
}

TEST(MutexSPSCQueueTest, MaintainsFIFOOrder)
{
	MutexSPSCQueue<int> queue(10);
	for(size_t i=0; i<10; ++i)
	{
		queue.produce(i);
	}
	for(int i=0; i<10;++i)
	{
		EXPECT_EQ(queue.consume(), i);
	}
	
}

TEST(MutexSPSCQueueTest, ProducerConsumerThreads)
{
	MutexSPSCQueue<int> queue(10);
	const int COUNT =1000;
	std::vector<int> consumed;
	consumed.reserve(COUNT);
	std::thread producer{
		[&]() {	for(int i=0; i<COUNT;++i)
				queue.produce(i);
			}
		};
	std::thread consumer{
		[&](){	for(int i=0; i<COUNT; ++i)
				consumed.push_back(queue.consume());}};
	producer.join();
	consumer.join();
	ASSERT_EQ(consumed.size(), COUNT);
	for(int i=0; i<COUNT; ++i)
		EXPECT_EQ(consumed[i],i);
}

TEST(MutexSPSCQueueTest, NoDataLoss)
{
	MutexSPSCQueue<int> queue(50);
	int COUNT = 100000;
	std::atomic<int> produced{0};
	std::atomic<int> consumed{0};
	std::thread producer{[&]()
		{
			for(int i=0; i<COUNT; ++i)
			{
				queue.produce(i);
				produced++;
			}
		}};
	std::thread consumer { [&]()
		{
			for(int i=0; i<COUNT; ++i)
			{
				queue.consume();
				consumed++;
			}
		}};
	producer.join();
	consumer.join();
	EXPECT_EQ(produced.load(), COUNT);
	EXPECT_EQ(consumed.load(), COUNT);
}

TEST(MutexSPSCQueueTest, ProducerBlcokWhenQueueFull)
{
	MutexSPSCQueue<int> queue(2);
	queue.produce(1);
	queue.produce(2);
	std::atomic<bool> thirdProduced= false;
	std::thread producer{[&]()
		{
			queue.produce(3);
			thirdProduced= true;
		}};
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		EXPECT_FALSE(thirdProduced);
		EXPECT_EQ(queue.consume(),1);
		EXPECT_TRUE(thirdProduced);
		producer.join();
}


		
int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}
