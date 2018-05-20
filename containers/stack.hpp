#pragma once

template<typename T>
class stack
{
	struct node
	{
		T value;
		node* child;
	};

public:
	stack()
		: top_(nullptr)
		, size_(0)
	{ }

	stack(const stack& s)
	{
		for (node* const n = s.top_; n != nullptr; n = n->child, top_ = new node { n->value, top_ } );
		size_ = s.size_;
	}

	stack& operator=(stack s)
	{
		node* tmp = top_;
		top_ = s.top_;
		s.top_ = tmp;
	}

	void push(const T& value)
	{
		top_ = new node { value, top_ };
		++size_;
	}
	
	template<typename ...Args>
	void emplace_push(Args&&... args)
	{
		assert(false);	
	}
	
	const T& top() const
	{
		assert(top_ != nullptr);
		return top_->value;
	}

	T& top()
	{
		assert(top_ != nullptr);
		return top_->value;
	}

	void pop()
	{
		assert(top_ != nullptr);
		node* child = top_->child;
		delete top_;
		top_ = child;
		--size_;
	}

	void multipop(unsigned int count)
	{
		assert(size >= count);
		for (unsigned int i = 0; i < count; i++, pop());
	}

	unsigned int size() const
	{
		return size_;
	}

	~stack()
	{
		for (;size_ != 0; pop());
	}

private:
	node* top_;
	unsigned int size_;
};
