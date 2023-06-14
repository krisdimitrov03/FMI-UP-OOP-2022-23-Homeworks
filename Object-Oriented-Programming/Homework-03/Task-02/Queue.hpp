#pragma once
#include <stdexcept>

namespace globals {
	const int RESIZE_COUNT = 4;
}

template <typename T>
struct Element
{
	T element;
	int priority;
};

template <typename T>
class Queue
{
	Element<T>* data = nullptr;
	size_t count = 0;
	size_t capacity = globals::RESIZE_COUNT;
	int maxPriority = 0;

	void free();
	void copyFrom(const Queue& other);
	void moveFrom(Queue&& other);
	void resize();
public:
	Queue();
	Queue(int priorities, bool& flag);

	Queue(const Queue& other);
	Queue(Queue&& other);

	Queue& operator=(const Queue& other);
	Queue& operator=(Queue&& other);

	~Queue();

	void push(const T& element, int priority = 0);
	void push(T&& element, int priority = 0);
	void pop();
	const T& peek() const;


};

template<typename T>
inline void Queue<T>::free()
{
	delete[] data;
	data = nullptr;
	count = 0;
	capacity = globals::RESIZE_COUNT;
}

template<typename T>
inline void Queue<T>::copyFrom(const Queue& other)
{
	count = other.count;
	capacity = other.capacity;

	data = new Element<T>[capacity];
	for (size_t i = 0; i < count; i++)
		data[i] = other.data[i];
}

template<typename T>
inline void Queue<T>::moveFrom(Queue&& other)
{
	data = other.data;
	other.data = nullptr;
	count = other.count;
	other.count = 0;
	capacity = other.capacity;
	other.capacity = globals::RESIZE_COUNT;
}

template<typename T>
inline void Queue<T>::resize()
{
	capacity += globals::RESIZE_COUNT;

	Element<T>* newData = new Element<T>[capacity];

	for (size_t i = 0; i < count; i++)
		newData[i] = data[i];

	delete[] data;
	data = newData;
	newData = nullptr;
}

template<typename T>
inline Queue<T>::Queue()
{
	data = new Element<T>[capacity];
}

template<typename T>
inline Queue<T>::Queue(int priorities, bool& flag) : Queue()
{
	if (priorities < 1) {
		flag = false;
		return;
	}

	maxPriority = priorities - 1;
}

template<typename T>
inline Queue<T>::Queue(const Queue& other)
{
	copyFrom(other);
}

template<typename T>
inline Queue<T>::Queue(Queue&& other)
{
	moveFrom(std::move(other));
}

template<typename T>
inline Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return (*this);
}

template<typename T>
inline Queue<T>& Queue<T>::operator=(Queue<T>&& other)
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return (*this);
}

template<typename T>
inline Queue<T>::~Queue()
{
	free();
}

template<typename T>
inline void Queue<T>::push(const T& element, int priority)
{
	if (priority > maxPriority)
		throw std::invalid_argument("Error! No such priority!");

	if (count == capacity)
		resize();

	data[count++] = { element, priority };
}

template<typename T>
inline void Queue<T>::push(T&& element, int priority)
{
	if (priority > maxPriority)
		throw std::invalid_argument("Error! No such priority!");

	if (count == capacity)
		resize();

	data[count++] = { std::move(element), priority };
}

template<typename T>
inline void Queue<T>::pop()
{
	const T& element = peek();

	size_t idx = 0;
	for (size_t i = 0; i < count; i++) {
		if (data[i].element == element) {
			idx = i;
			break;
		}
	}

	for (size_t i = idx; i < count - 1; i++)
		data[i] = data[i + 1];

	--count;
}

template<typename T>
inline const T& Queue<T>::peek() const
{
	if (count == 0)
		throw std::invalid_argument("Error! Queue is empty!");

	if (maxPriority == 0)
		return data[0].element;

	size_t index = 0;

	for (size_t i = 0; i < count; i++)
		if (data[i].priority > data[index].priority)
			index = i;

	return data[index].element;
}