#include <iostream>
#include "../circularBuffer/circularBuffer.h"
#include <chrono>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <memory>
template<typename T>
class MutexSPSCQueue
{
	private:
		std::mutex mMutex;
		UD::CircularBuffer<T> mSharedBuffer;
		std::condition_variable producer_cv;
		std::condition_variable consumer_cv;

	public:
		explicit MutexSPSCQueue(size_t capacity):mSharedBuffer(capacity){}
		MutexSPSCQueue(const MutexSPSCQueue&) =delete;
		MutexSPSCQueue& operator=(const MutexSPSCQueue&) =delete;
		void produce(const T& item)
		{
			std::unique_lock<std::mutex> lock(mMutex);
			producer_cv.wait(lock,[this](){return mSharedBuffer.size()<mSharedBuffer.capacity();});
			//Wait until space is available.
			mSharedBuffer.push(item);
			lock.unlock();
			consumer_cv.notify_one();
		}
		T consume()
		{
			std::unique_lock<std::mutex> lock(mMutex);
			consumer_cv.wait(lock,[this](){return !mSharedBuffer.isEmpty();});
			T item=std::move(mSharedBuffer.front());
			mSharedBuffer.pop();
			lock.unlock();
			producer_cv.notify_one();
			return item;
		}
};
/*
		void producer(MutexSPSCQueue<int>& queue)
		{
			for(size_t i=0; i<100000;++i)
			{
				queue.produce(i);
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}

		void consumer(MutexSPSCQueue<int>& queue)
		{
			for(size_t i=0;i<100000;++i )
			{
				queue.consume();
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
			}
		}

int main()
{
	MutexSPSCQueue<int> queue(5);

	std::thread t1{producer, std::ref(queue)};

	std::thread t2{consumer, std::ref(queue)};
	t1.join();
	t2.join();
	return 0;
}*/

