#include <iostream>
#include <stdexcept>
#include <memory>

template <typename T>
class CircularBuffer {
private: 
	size_t m_capacity;
	size_t m_write_index;
	size_t m_read_index;
	size_t m_size;
	std::unique_ptr<T[]> m_buffer;

public:	

	explicit CircularBuffer(size_t capacity) :
		m_capacity(capacity),
		m_write_index(0),
		m_read_index(0),
		m_size(0)
	{
		if (capacity == 0)
			throw std::invalid_argument("Capacity must be > 0");
		//m_buffer = new T[m_capacity];
	}
	~CircularBuffer()
	{
		delete[] m_buffer;
		m_buffer = nullptr;
	}
	void push(const T& value)
	{
		if (isFull())
		{
			std::cerr << "Buffer Overflow\n";
			return;
		}
		m_buffer[m_write_index] = value;
		m_write_index = (m_write_index + 1) % m_capacity;
		m_size++;
	}
	T pop()
	{
		if (isEmpty())
			throw std::underflow_error("Buffer underflow\n");
		T value = m_buffer[m_read_index];
		m_read_index = (m_read_index + 1) % m_capacity;
		m_size--;
		return value;
	}

	T read
};