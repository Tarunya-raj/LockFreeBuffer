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
	};
}

int main()
{
	UD::unique_ptr<int> ptr; // default constructor
	
}