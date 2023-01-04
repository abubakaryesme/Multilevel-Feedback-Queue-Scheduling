// Class Specification / Definition :

//If this class is not already define then define it:
#ifndef READYQUEUE_H
#define READYQUEUE_H

#include"Process.h"
#include "Queue.h"
struct QueueObject
{
	Queue<Process> processInQueue;
	string algorithmType;
	int priorityNumOfQueue;
	int quantum; //It will be -1 if SJF.
	int promotionTime; //It will be 0 for top Queue.
};

//Global Constants:
const int NO_OF_QUEUES = 3;
class ReadyQueue
{
private:
	QueueObject queueNum[NO_OF_QUEUES];
public:
	const int CHECK_PROMOTION_AFTER = 30; //checks for promotion after every N mseconds;
	ReadyQueue();
	void promotionPolicy(const int,const int);
	bool nextProcessOnGC(Process &,int&);
	bool nextProcessArrivalTime(int&);
	void insertProcessRR(Process);
	void insertProcessSJF(Process);
	bool isEmpty();
	friend ostream& operator << (ostream&,  ReadyQueue&); //Overload the stream insertion operator << (as a friend function).
};
#endif // !READYQUEUE_H

