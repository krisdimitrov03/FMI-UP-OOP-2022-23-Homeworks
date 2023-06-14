#pragma once
#include <iostream>

namespace globals {
	const int CAPACITY_INCREASE_COUNT = 4;
}

template <typename T>
class Set
{
protected:
	T* elements = nullptr;
	size_t count = 0;
	size_t capacity = globals::CAPACITY_INCREASE_COUNT;

	void free();
	void copyFrom(const Set& other);
	void moveFrom(Set&& other);
public:
	Set();
	Set(const Set& other);
	Set(Set&& other);
	Set& operator=(const Set& other);
	Set& operator=(Set&& other);
	~Set();

	bool add(const T& element);
	bool add(T&& element);
	bool remove(const T& element);

	void empty();
	size_t length() const;

	T& operator[](size_t idx);
	const T& operator[](size_t idx) const;
	virtual bool contains(const T& element) const;

	void print() const;
	void printSingle(const T& element) const;
};

template<typename T>
inline void Set<T>::free()
{
	delete[] elements;
	elements = nullptr;
	count = 0;
	capacity = globals::CAPACITY_INCREASE_COUNT;
}

template<typename T>
inline void Set<T>::copyFrom(const Set& other)
{
	count = other.count;
	capacity = other.capacity;

	elements = new T[count];
	for (size_t i = 0; i < count; i++)
		elements[i] = other.elements[i];
}

template<typename T>
inline void Set<T>::moveFrom(Set&& other)
{
	count = other.count;
	capacity = other.capacity;
	other.count = 0;
	other.capacity = globals::CAPACITY_INCREASE_COUNT;

	elements = other.elements;
	other.elements = nullptr;
}

template<typename T>
inline Set<T>::Set()
{
	elements = new T[capacity];
}

template<typename T>
inline Set<T>::Set(const Set& other)
{
	copyFrom(other);
}

template<typename T>
inline Set<T>::Set(Set&& other)
{
	moveFrom(std::move(other));
}

template<typename T>
inline Set<T>& Set<T>::operator=(const Set<T>& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
inline Set<T>& Set<T>::operator=(Set<T>&& other)
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
inline Set<T>::~Set()
{
	free();
}

template<typename T>
inline bool Set<T>::add(const T& element)
{
	if (contains(element))
		return false;

	if (count == capacity) {
		capacity += globals::CAPACITY_INCREASE_COUNT;
		T* newData = new T[capacity];

		for (size_t i = 0; i < count; i++)
			newData[i] = elements[i];

		delete[] elements;
		elements = newData;
	}

	elements[count++] = element;
	return true;
}

template<typename T>
inline bool Set<T>::add(T&& element)
{
	if (contains(element))
		return false;

	if (count == capacity) {
		capacity += globals::CAPACITY_INCREASE_COUNT;
		T* newData = new T[capacity];

		for (size_t i = 0; i < count; i++)
			newData[i] = elements[i];

		delete[] elements;
		elements = newData;
	}

	elements[count++] = std::move(element);
	return true;
}

template<typename T>
inline bool Set<T>::remove(const T& element)
{
	if (!contains(element))
		return false;

	size_t idxToDelete = 0;

	for (size_t i = 0; i < count; i++)
	{
		if (elements[i] == element) {
			idxToDelete = i;
			break;
		}
	}

	for (size_t i = idxToDelete; i < count - 1; i++)
		elements[i] = elements[i + 1];

	count--;
}

template<typename T>
inline void Set<T>::empty()
{
	if (elements == nullptr)
		throw std::runtime_error("Set is already empty");

	count = 0;

	delete[] elements;
	elements = new T[capacity];
}

template<typename T>
inline size_t Set<T>::length() const
{
	return count;
}

template<typename T>
inline T& Set<T>::operator[](size_t idx)
{
	return elements[idx];
}

template<typename T>
inline const T& Set<T>::operator[](size_t idx) const
{
	return elements[idx];
}

template<typename T>
inline bool Set<T>::contains(const T& element) const
{
	for (size_t i = 0; i < count; i++)
		if (elements[i] == element)
			return true;

	return false;
}

template<typename T>
inline void Set<T>::print() const
{
	if (count == 0) {
		std::cout << "empty" << std::endl;
		return;
	}

	for (size_t i = 0; i < count; i++) {
		if (i == count - 1)
			std::cout << elements[i] << std::endl;
		else
			std::cout << elements[i] << ", ";
	}
}

template<typename T>
inline void Set<T>::printSingle(const T& element) const
{
	std::cout << element;
}
