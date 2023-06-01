#pragma once

#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <iostream>

template<typename T>
struct Node {
private:
	T* elem;
public:
	Node() { elem = nullptr; };
	Node(T e) { elem = new T(e); };
	~Node() { delete elem; next = nullptr; prev = nullptr; }

	Node<T>* next = nullptr;
	Node<T>* prev = nullptr;

	inline T* get_elem() { return elem; }
	void set_elem(T el) { elem = new T(el); }
};

template<typename T>
class BasicContainer abstract
{
protected:
	int32_t _size;
	Node<T>* dummy_first;
	Node<T>* dummy_last;

	BasicContainer() {
		_size = 0; dummy_first = new Node<T>(); dummy_last = new Node<T>();
		dummy_first->next = dummy_last;
		dummy_last->prev = dummy_first;
	}
	BasicContainer(const BasicContainer& a) : BasicContainer() {
		Node<T>* ptr = a.dummy_first;
		while ((ptr = ptr->next) != a.dummy_last) _insert(*(ptr->get_elem()), -1);
	}
	~BasicContainer() {
		Node<T>* ptr = dummy_first;
		while ((ptr = ptr->next) != nullptr) 
			delete ptr->prev;
		delete ptr;
	}

	Node<T>* _get_pre(int32_t index) {
		int32_t i = 0;
		Node<T>* pre = dummy_first;
		while (i++ < index) pre = pre->next;
		return pre;
	}

	void _insert(T elem, int32_t index) {
		if (index < 0) index += _size + 1;
		if (index > _size || index < 0) throw std::out_of_range("Can't insert element out of range");
		Node<T>* node = new Node<T>(elem);
		if (index == _size - 1) {
			node->prev = dummy_last->prev;
			dummy_last->prev->next = node;
			node->next = dummy_last;
			dummy_last->prev = node;
			_size++;
			return;
		}
		Node<T>* pre = _get_pre(index);
		node->prev = pre;
		node->next = pre->next;
		pre->next->prev = node;
		pre->next = node;
		_size++;
	}
	Node<T>* _get(int32_t index) {
		if (index < 0) index += _size + 1;
		if (_size < index || index < 0) throw std::out_of_range("Can't get element out of range!");

		if (index == _size - 1) return dummy_last->prev;
		return _get_pre(index)->next;
	}
	T _remove(int32_t index) {
		Node<T>* to_delete = _get(index);
		to_delete->prev->next = to_delete->next;
		to_delete->next->prev = to_delete->prev;
		T res = *(to_delete->get_elem());
		delete to_delete;
		_size--;
		return res;
	}
public:
	int32_t size() { return _size; }
};



template<typename T>
struct ListIterator {
private:
	Node<T>* elem;
public:
	ListIterator(Node<T>* elem) { this->elem = elem; }
	~ListIterator() {};

	inline bool operator==(const ListIterator& it) { return elem == it.elem; }
	inline bool operator!=(const ListIterator& it) { return elem != it.elem; }

	ListIterator& operator++() {
		if (!elem->next) throw std::out_of_range("");
		elem = elem->next;
		return *this;
	}
	ListIterator operator++(int) {
		if (!elem->next) throw std::out_of_range("");
		elem = elem->next;
		return *this;
	}
	T* operator->() { return elem->get_elem(); }
	T& operator*() { return *(elem->get_elem()); }
};



template<typename T>
class Iterable abstract {
protected:
	Iterable() {};
public:
	virtual ListIterator<T> begin() = 0;
	virtual ListIterator<T> end() = 0;
};



template<typename T>
class Queue : public BasicContainer<T> {
public:
	Queue() : BasicContainer<T>() {};
	Queue(const Queue& a) : BasicContainer<T>(a) {};

	inline void push(T elem) { this->_insert(elem, -1); }
	[[nodiscard]] inline const T& get_top() { return *(this->dummy_first->next->get_elem()); }
	inline T pop() { return this->_remove(0); }
};

template<typename T>
class List : public BasicContainer<T>, public Iterable<T> {
public:
	List() : BasicContainer<T>() {};
	List(const List& a) : BasicContainer<T>(a) {};

	inline void push_front(T elem) { this->_insert(elem, 0); }
	inline void push_back(T elem) { this->_insert(elem, -1); }
	inline void insert(T elem, int32_t index) { this->_insert(elem, index); }
	inline T pop_front() { return this->_remove(0); }
	inline T pop_back() { return this->_remove(-1); }
	inline T remove(int32_t index) { return this->_remove(index); }
	[[nodiscard]] inline T& get(int32_t index) { return *(this->_get(index)->get_elem()); }

	virtual ListIterator<T> begin() { 
		return ListIterator<T>(this->dummy_first->next); 
	}
	virtual ListIterator<T> end() {
		return ListIterator<T>(this->dummy_last); 
	}
};


template<typename _FIRST_T, typename _SECOND_T>
class Pair {
public:
	Pair(_FIRST_T f, _SECOND_T s) : first(f), second(s) {};
	Pair(const Pair& a) : Pair(a.first, a.second) {};

	_FIRST_T first;
	_SECOND_T second;
};

#endif // !CONTAINERS_H