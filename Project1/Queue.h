// Class Specification / Definition :

//If this class is not already define then define it:
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "Process.h"
#include <iomanip>
using namespace std;

template<typename T>
class Queue
{
	int rear;
	int front;
	int capacity;
	int noOfElements;
	T* data;
	void reSize(int newSize);

public:
	Queue()
	{
		rear = front = noOfElements = capacity = 0;
		data = nullptr;
	}
	Queue(const Queue<T>&);
	Queue<T>& operator=(const Queue <T>&);
	~Queue();
	void enQueue(T);
	T deQueue();
	T getElementAtFront() const;
	bool isEmpty()const;
	bool isFull()const;
	int getNoOfElements()const;
	int getCapacity()const;
	void sortQueue();
	template<typename U>
	friend ostream& operator << (ostream&, const Queue<U>&); //Overload the stream insertion operator << (as a friend function).
};

//******************************************************************************************
//This member function is used to sort the queue element in ascending order.			   *
//******************************************************************************************
template<typename T>
void Queue<T>::sortQueue()
{
	int innerElement = front, outerElemet = front;
	for (int elementNo = 0; elementNo < noOfElements; elementNo++)
	{
		innerElement = outerElemet;
		for (int compareWith = elementNo + 1; compareWith < noOfElements; compareWith++)
		{
			innerElement = (innerElement + 1) % capacity;
			if (data[outerElemet] > data[innerElement])
			{
				T temp = data[outerElemet];
				data[outerElemet] = data[innerElement];
				data[innerElement] = temp;
			}
		}
		outerElemet = (outerElemet + 1) % capacity;
	}
}

template<typename T>
int Queue<T>::getCapacity()const
{
	return capacity;
}

template<typename T>
int Queue<T>::getNoOfElements()const
{
	return noOfElements;
}

template<typename T>
bool Queue<T>::isFull()const
{
	return noOfElements == capacity;
}

template<typename T>
bool Queue<T>::isEmpty()const
{
	return noOfElements == 0;
}

template<typename T>
T Queue<T>::getElementAtFront() const
{
	if (isEmpty())
		exit(0);
	return data[front];
}

template<typename T>
Queue<T>::~Queue()
{
	if (!data)
		delete[]data;
	rear = front = noOfElements = capacity = 0;
	data = nullptr;
}

template<typename T>
void Queue<T>::reSize(int newSize)
{
	T* temp = new T[newSize];
	int tempElements = noOfElements, tempFront = front;
	for (int i = 0; i < noOfElements; i++)
	{
		temp[i] = data[tempFront];
		tempFront = (tempFront + 1) % capacity;
	}
	this->~Queue();
	data = temp;
	rear = tempElements;
	capacity = newSize;
	noOfElements = tempElements;
	front = 0;
}

template<typename T>
T Queue<T>::deQueue()
{
	if (isEmpty())
		exit(0);
	T val = data[front];
	front = (front + 1) % capacity;
	noOfElements--;
	if (noOfElements > 0 && noOfElements == capacity / 4)
		reSize(capacity / 2);
	return val;
}

template<typename T>
void Queue<T>::enQueue(T val)
{
	if (isFull())
	{
		reSize(capacity == 0 ? 1 : capacity * 2);
	}
	data[rear] = val;
	rear = (rear + 1) % capacity;
	noOfElements++;
}

template<typename T>
Queue<T>::Queue(const Queue<T>& ref)
{
	if (ref.data == nullptr)
	{
		rear = front = noOfElements = capacity = 0;
		data = nullptr;
		return;
	}
	noOfElements = ref.noOfElements;
	capacity = ref.capacity;
	rear = ref.noOfElements;
	front = 0;
	data = new T[ref.capacity];
	int tempFront = ref.front;
	for (int i = 0; i < noOfElements; i++)
	{
		data[i] = ref.data[tempFront];
		tempFront = (tempFront + 1) % capacity;
	}
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue <T>& ref)
{
	if (this == &ref)
		return *this;
	this->~Queue();
	if (ref.data == nullptr)
	{
		rear = front = noOfElements = capacity = 0;
		data = nullptr;
		return *this;
	}
	noOfElements = ref.noOfElements;
	capacity = ref.capacity;
	rear = ref.noOfElements;
	front = 0;
	data = new T[ref.capacity];
	int tempFront = ref.front;
	for (int i = 0; i < noOfElements; i++)
	{
		data[i] = ref.data[tempFront];
		tempFront = (tempFront + 1) % capacity;
	}
	return *this;
}

#endif // !QUEUE_H

