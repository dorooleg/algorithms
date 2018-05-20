#pragma once

template<typename T/*, typename Allocator = ... */>
class hashed_array_tree
{
public:
	// types
	using value_type = T;
	// using allocator_type = Allocator;
	using pointer = T*;
	using const_potiner = const T*;
	using reference = T&;
	using const_reference = const value_type&;
	using size_type = unsigned int;
	using difference_type = unsigned int;
	// using iterator = ...;
	// using const_iterator = ...;
	// using reverse_iterator = ...;
	// using const_reverse_iterator = ...;

	hashed_array_tree() noexcept
		: top_(nullptr)
		, power_(-1)
		, size_(0)
	{
	}

	// element access
	reference operator[](size_type idx)
	{
		return *(static_cast<T*>(top_[top_index(idx)]) + leaf_index(idx));
	}

	const_reference operator[](size_type idx) const
	{
		return *(static_cast<T*>(top_[top_index(idx)]) + leaf_index(idx));
	}

	reference at(size_type idx)
	{
		return *(static_cast<T*>(top_[top_index(idx)]) + leaf_index(idx));
	}

	const_reference at(size_type idx) const
	{
		return *(static_cast<T*>(top_[top_index(idx)]) + leaf_index(idx));
	}

	const_reference back() const
	{
		return operator[](size_ - 1);
	}

	reference back()
	{
		return operator[](size_ - 1);
	}

	const_reference front() const
	{
		return operator[](0);
	}

	reference front()
	{
		return operator[](0);
	}

	void resize(size_type size)
	{
		if (size <= capacity())
		{
			return;
		}
		unsigned int new_power = power_ + 1;
		void** new_top = new void*[1 << new_power]{};

		for (unsigned int i = 0; i < size_; i++)
		{
			if (new_top[top_index(i, new_power)] == nullptr)
			{
				new_top[top_index(i, new_power)] = new char*[(1 << new_power) * sizeof(T)];
			}		
			new ((char*)new_top[top_index(i, new_power)] + sizeof(T) * leaf_index(i)) T {operator[](i)};  
		}

		this->~hashed_array_tree();

		top_ = new_top;
		power_ = new_power;
	}

	//modifiers	
	void push_back(const T& value)
	{
		resize(size_ + 1);
		if (top_[top_index(size_)] == nullptr)
		{
			top_[top_index(size_)] = new char*[(1 << power_) * sizeof(T)];
		}
		new ((char*)top_[top_index(size_)] + sizeof(T) * leaf_index(size_)) T { value };
		++size_;
	}

	void push_back(T&& value)
	{
		resize(size_ + 1);
		if (top_[top_index(size_)] == nullptr)
		{
			top_[top_index(size_)] = new char*[(1 << power_) * sizeof(T)];
		}
		new ((char*)top_[top_index(size_)] + sizeof(T) * leaf_index(size_)) T { value };
		++size_;
	}

	void pop_back()
	{
		back().~T();
		--size_;
	}

	// capacity
	[[nodiscard]] bool empty() const noexcept
	{
		return size_ == 0;
	}

	size_type size() const noexcept
	{
		return size_;
	}

	size_type capacity() const noexcept
	{
		return power_ == -1 ? 0 : (1 << (power_ << 1));
	}

	~hashed_array_tree()
	{
		for (unsigned int i = 0; i < size_; i++)
		{
			operator[](i).~T();
		}

		for (unsigned int i = 0; power_ != -1 && i < 1 << power_; i++)
		{
			delete[] (char*)top_[i]; 
		}

		delete[] top_;
	}

private:
	static size_type top_index(size_type idx, size_type power)
	{
		return idx >> power;
	}
	
	static size_type leaf_index(size_type idx, size_type power)
	{
		return idx & ((1 << power) - 1);
	}

	size_type top_index(size_type idx)
	{
		return top_index(idx, power_);
	}
	
	size_type leaf_index(size_type idx)
	{
		return leaf_index(idx, power_);
	}

private:
	void** top_;
	size_type power_;
	size_type size_;
};
