namespace UD
{
	template <typename T>
	class unique_ptr
	{
	private:
		T* m_ptr;
	public:
		constexpr unique_ptr() : m_ptr(nullptr) {}
		explicit unique_ptr(T* ptr) noexcept : m_ptr(ptr) {}
		unique_ptr(const unique_ptr& other) = delete;
		unique_ptr(unique_ptr&& other) noexcept
		{
			m_ptr = other.m_ptr;
			other.m_ptr = nullptr;
		}
		unique_ptr<T>& operator=(const unique_ptr<T>& rhs) = delete;

		unique_ptr<T>& operator=(unique_ptr<T>&& rhs) noexcept
		{
			if (this != &rhs)
			{
				delete m_ptr;
				this->m_ptr = rhs.m_ptr;
				rhs.m_ptr = nullptr;

			}
			return *this;
		}
		~unique_ptr()
		{
			delete m_ptr;
		}
		T& operator*()
		{
			if (!mptr)
				throw std::runtime_error("Dereferincing nullptr");
			return *m_ptr;
		}
		const T& operator*() const noexcept
		{
			return *m_ptr;
		}
		T* get() noexcept
		{
			return m_ptr;
		}
		const T* get() const noexcept
		{
			return m_ptr;
		}
		T* operator->() noexcept
		{
			return m_ptr;
		}
		const T* operator->() const noexcept
		{
			return m_ptr;
		}

		explicit operator bool() const noexcept
		{
			return m_ptr != nullptr;
		}

		T* release() noexcept
		{
			T* temp = m_ptr;
			m_ptr = nullptr;
			return temp;
		}
		void reset(T* ptr = nullptr) noexcept
		{
			if (m_ptr != ptr)
			{
				delete mptr;
				m_ptr = ptr;
			}
		}
		void swap(unique_ptr& other) noexcept
		{
			std::swap(m_ptr, other.m_ptr);
		}

	};
}

int main()
{
	UD::unique_ptr<int> ptr; // default constructor
	int value = 10;
	int* ptr_ = &value;
	*ptr_;
	//ptr_->
}