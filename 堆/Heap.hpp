#pragma once
#include<memory>
#include<initializer_list>
//#include<iostream>
#include<algorithm>

template<typename _Ty,
	typename _Cmp=std::greater<_Ty>>
	class Heap
{
public:
	Heap(int capacity) :m_last(0), m_capacity(capacity) {
		this->m_imtes.reset(new _Ty[this->m_capacity+1], [](_Ty *arr) {//shared_ptr管理数组要自己定义删除器，且不支持下标[]运算，只能用get()代替
			delete[] arr;
		});
	}

	Heap(const std::initializer_list<_Ty> &ilt) :m_last(0), m_capacity(ilt.size()) {
		this->m_imtes.reset(new _Ty[this->m_capacity+1], [](_Ty *arr) {
			delete[] arr;
		});
		this->insert(ilt);
	}
/*
	~Heap() {
		std::for_each(this->getRef(), this->getRef(this->m_last+1), [](_Ty ty) {
			std::cout << ty << " ";
		});
		std::cout << std::endl;
	}*/

	Heap(const Heap &hp) {}

	Heap& operator=(const Heap &hp) {
		return *this;
	}

	Heap(Heap &&hp) noexcept{}//不应抛出异常

	Heap& operator=(Heap &&hp) noexcept {
		return *this;
	}

	int insert(_Ty ty) {
		if (!this->full()) {
			this->set(++this->m_last, ty);
			this->swim(this->m_last);
			return this->m_last;
		}
		return -1;
	}

	void insert(const std::initializer_list<_Ty> &lst) {
		size_t rest = this->m_capacity - this->m_last;
		if (rest) {
			auto elmLast = (rest > lst.size()) ? lst.end() : lst.begin() + rest;
			std::for_each(lst.begin(), elmLast, [&](_Ty ty) {
				this->insert(ty);
			});
		}
	}

	_Ty pop() {
		if (this->m_last != 0) {
			auto temp = this->getVal();
			this->set(1, this->getVal(this->m_last--));
			this->sink();
			return temp;
		}
		return _Ty();
	}

private:
	_Ty* getRef(int i = 1) const {
		return this->m_imtes.get() + i;
	}

	_Ty getVal(int i = 1)const {
		return *this->getRef(i);
	}

	void set(int i,_Ty ty) {
		*this->getRef(i) = ty;
	}

	bool val_cmp(int i, int j) const{
		return _Cmp()(this->getVal(i), this->getVal(j));
	}

	void exch(int i, int j) {
		if (i != j && i <= this->m_last && j <= this->m_last) {
			_Ty temp = this->getVal(i);
			*this->getRef(i) = this->getVal(j);
			*this->getRef(j) = temp;
		}
	}

	void swim(int i) {
		if (this->val_cmp(i, i / 2) && i > 1) {
			this->exch(i, i / 2);
			this->swim(i / 2);
		}
	}

	bool exist(int i)const {
		return i <= this->m_last;
	}

	void sink(int i = 1) {
		if (this->exist(i * 2) && this->exist(i * 2 + 1)) {
			if (this->val_cmp(i * 2, i * 2 + 1)) {
				if (this->val_cmp(i * 2, i)) {
					this->exch(i, i * 2);
					this->sink(i * 2);
				}
			}
			else {
				if (this->val_cmp(i * 2 + 1, i)) {
					this->exch(i, i * 2 + 1);
					this->sink(i * 2 + 1);
				}
			}
		}
		else if (!this->exist(i * 2 + 1) && this->exist(i * 2)) {
			if (this->val_cmp(i * 2, i)) {
				this->exch(i, i * 2);
			}
		}
	}

	bool full() {
		return this->m_last >= this->m_capacity;
	}

	std::shared_ptr<_Ty> m_imtes;
	int m_last;
	int m_capacity;
};