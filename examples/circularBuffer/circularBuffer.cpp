
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
		m_buffer = std::make_unique<T[]>(capacity);
	}
	~CircularBuffer() = default;

	//Copy constructor- Deep copy
	CircularBuffer(const CircularBuffer& other) :
		m_buffer(std::make_unique<T[]>(other.m_capacity)),
		m_size(other.m_size),
		m_capacity(other.m_capacity),
		m_read_index(other.m_read_index),
		m_write_index(other.m_write_index)
	{
		for (size_t i = 0; i < m_capacity; ++i)
		{
			m_buffer[i] = other.m_buffer[i];
		}
	}

	//Copy assignment
	CircularBuffer& operator=(const CircularBuffer& rhs)
	{
		if (this != &rhs)
		{
			auto temp = std::make_unique<T[]>(rhs.m_capacity);
			for (size_t i = 0; i < rhs.m_capacity; ++i)
			{
				temp[i] = rhs.m_buffer[i];
			}
			m_buffer = std::move(temp);
			m_capacity = rhs.m_capacity;
			m_read_index = rhs.m_read_index;
			m_write_index = rhs.m_write_index;
			m_size = rhs.m_size;
		}
		return *this;

	}
	CircularBuffer(CircularBuffer&& other) noexcept = default;
	CircularBuffer& operator=(CircularBuffer&& rhs) noexcept = default;

	size_t capacity() const noexcept
	{
		return m_capacity;
	}
	size_t size() const noexcept
	{
		return m_size;
	}
	bool isEmpty() const noexcept
	{
		return m_size == 0;
	}
	bool isFull() const noexcept
	{
		return m_size == m_capacity;
	}
	void push(const T& value)
	{
		if (isFull())
		{
			throw std::overflow_error("Buffer Overflow\n");
		}
		m_buffer[m_write_index] = value;
		m_write_index = (m_write_index + 1) % m_capacity;
		m_size++;
	}
	void push(T&& value)
	{
		if(isFull())
			throw std::overflow_error("Buffer OverFlow\n");
		m_buffer[m_write_index]=std::move(value);
		m_write_index=(m_write_index+1)%m_capacity;
		++m_size;
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

	const T& front() const
	{
		if (isEmpty())
			throw std::underflow_error("Queue empty");
		return m_buffer[m_read_index];
	}

	// existing data is treated as garbage, data only logically removed from buffer
	//physically still present in memory, new data pushed overides them.
	//Capacity retained to reuse the buffer.
	void clear() noexcept
	{
		m_read_index = 0;
		m_write_index = 0;
		m_size = 0;
	}
};
