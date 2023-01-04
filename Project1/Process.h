// Class Specification / Definition :

//If this class is not already define then define it:
#ifndef PROCESS_H
#define PROCESS_H

#include<string>
using namespace std;

class Process
{
	string processName;
	int priorityNum;
	int arrivalTime;
	int burstTime;
	int remainingBurstTime;
	int waitingStartInQueue;
	int startTime, finalTime;
public:

	Process(); //DEfault Constructor
	Process(const Process&); //Copy Constructor
	~Process(); //Destructor.
	
	//Inline functions ---> (Getter,Setter)
	string getProcessName()
	{
		return processName;
	}
	int getPriorityNum()
	{
		return priorityNum;
	}
	int getArrivalTime()
	{
		return arrivalTime;
	}
	int getBurstTime()
	{
		return burstTime;
	}
	int getRemainingBurst()
	{
		return remainingBurstTime;
	}
	int getWaitingStartTimeInQueue()
	{
		return waitingStartInQueue;
	}
	int getStartTime()
	{
		return startTime;
	}
	int getFinalTime()
	{
		return finalTime;
	}

	//Setter:
	int substractBurst(int value);
	void setWaitingTimeStart(int waitTimeQueue)
	{
		waitingStartInQueue = waitTimeQueue;
	}
	void setStartTime(int timeStart)
	{
		startTime = timeStart;
	}
	void setFinalTime(int endTime)
	{
		finalTime = endTime;
	}
	void setPriorityNum(int updatePriorityNum)
	{
		priorityNum = updatePriorityNum;
	}
	//Operator Overloading:
	bool operator < (const Process&) const;
	bool operator > (const Process&)const;
	bool operator <= (const Process&) const;
	bool operator >= (const Process&)const;
	bool operator == (const Process&)const;
	bool operator != (const Process&)const;
	const Process& operator = (const Process&);

	friend ostream& operator << (ostream&, const Process&); //Overload the stream insertion operator << (as a friend function).
	friend istream& operator >> (istream&, Process&); //Overload the stream extraction operator >> (as a friend function).
};



#endif