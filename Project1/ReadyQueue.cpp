//Class Implementation :
#include <iostream>
#include "ReadyQueue.h"

//***************************************************************
// Default Constructor for ReadyQueue Class.					*
//It store the data of Queue algorithm,quantum					*
// and etc in QueueObject (data member)							*
//***************************************************************
 ReadyQueue::ReadyQueue()
{
	 //Queue 1 -> Top Queue
	 queueNum[0].priorityNumOfQueue = 1;
	 queueNum[0].algorithmType = "RR";
	 queueNum[0].promotionTime = 0; //beacuse Top queue
	 queueNum[0].quantum = 5;

	 //Queue 2
	 queueNum[1].priorityNumOfQueue = 2;
	 queueNum[1].algorithmType = "RR";
	 queueNum[1].promotionTime = 10;
	 queueNum[1].quantum = 8;


	 //Queue 3
	 queueNum[2].priorityNumOfQueue = 3;
	 queueNum[2].algorithmType = "SJF";
	 queueNum[2].promotionTime = 20;
	 queueNum[2].quantum = -1; //because SJF
}

//****************************************************************************************************************
//This function implement aging to avoid starvation for which promotion policy is as below:						 *
//--------->If a process wait time is 20 sec in last queue Q3, it will be moved to Q2.							 *
//--------->If process kept on waiting in Q2 for 10 sec, it will move to Q1.									 *
//****************************************************************************************************************
 void ReadyQueue::promotionPolicy(const int currTime,const int promotionCounter)
 {
	 for (int qNo = 1; qNo < NO_OF_QUEUES; qNo++) //Pick a queue till  NO_OF_QUEUES
	 {
		 while (!(queueNum[qNo].processInQueue.isEmpty())) //Check any process exist in this queue.
		 {
			 Process processCheck = queueNum[qNo].processInQueue.deQueue();
			 if ((currTime-processCheck.getWaitingStartTimeInQueue()) >= queueNum[qNo].promotionTime) //if wait time is more than promotion time:
			 {
				 int priorityNo = processCheck.getPriorityNum();
				 priorityNo--;
				 processCheck.setPriorityNum(priorityNo); //then increase its priority and
				 processCheck.setWaitingTimeStart((CHECK_PROMOTION_AFTER * promotionCounter));
				 queueNum[qNo - 1].processInQueue.enQueue(processCheck); //shift to its upper queue/high priorty queue.
			 }
			 else
				queueNum[qNo].processInQueue.enQueue(processCheck);
		 }
		 if (queueNum[qNo].algorithmType == "SJF") //It will sort that queue according to burst time if algorithm type of queue is SJF. 
			 queueNum[qNo].processInQueue.sortQueue();
	 }
 }

//****************************************************************************************************************
//This function return that process through parameter by refernece from											 *
//-->Queue 1: which process comes first in the queue. Condition : Non empty										 *
//-->Queue 2: which process comes first in the queue. Condition : Non empty and Queue 1 is empty.				 *
//-->Queue 3: which process has shortest burst time.  Condition : Non empty and Queue 1 and Queue 2 are empty.	 *
//It will return true if a process is found in any queue otherwise false.										 *
//****************************************************************************************************************
 bool ReadyQueue::nextProcessOnGC(Process& nextProcces, int& quantum)
 {
	 bool processFound = false;
	 for (int qNo = 0; qNo < NO_OF_QUEUES; qNo++) //Pick a Queue
	 {
		 if (!(queueNum[qNo].processInQueue.isEmpty())) //if its not empty
		 {
			 nextProcces = queueNum[qNo].processInQueue.deQueue(); //then get process from front of the queue.
			 quantum = queueNum[qNo].quantum;
			 return true; //Returns true as process found.
		 }
	 }
	 return processFound; //If all queue is empty -> returns false.
 }

//*******************************************************************************************************
//This function returns true if a process is found														*
//in any queue otherwise false. It will returns the arrival time of the process							*
//which will run next on timeline through paramter by reference.										*								
//*******************************************************************************************************
 bool ReadyQueue::nextProcessArrivalTime(int& arrTime)
 {
	 bool processFound = false;
	 for (int qNo = 0; qNo < NO_OF_QUEUES; qNo++) //Pick a Queue
	 {
		 if (!(queueNum[qNo].processInQueue.isEmpty())) //if its not empty
		 {
			 Process nextProcces = queueNum[qNo].processInQueue.getElementAtFront(); //then get process from front of the queue but don't remove.
			 arrTime = nextProcces.getArrivalTime(); //gets its arrival time.
			 return true; //returns true as process found.
		 }
	 }
	 return processFound; //If all queue is empty -> No process found -> returns false.
 }

 //**********************************************************************************
 //This function returns true if all the Ready Queues are empty						*
 //otherwise false.																	*
 //**********************************************************************************
 bool ReadyQueue::isEmpty()
 {
	 bool processFound = true;
	 for (int qNo = 0; qNo < NO_OF_QUEUES; qNo++) //Pick a Queue till NO_OF_QUEUES
	 {
		 if (!(queueNum[qNo].processInQueue.isEmpty())) //If its not empty.
		 {
			 processFound = false; //then change the flag to false.
		 }
	 }
	 return processFound; //otherwise returns true -> As no process found.
 }

 //**************************************************************************************
 //This function insert the process accoding to its priority but						*
 //Queue must have algorithm type "RR".													*
 //**************************************************************************************
 void ReadyQueue::insertProcessRR(Process processInfo)
 {
	 int qNo = processInfo.getPriorityNum(); //Gets process priority num
	 queueNum[qNo-1].processInQueue.enQueue(processInfo); //insert in queue according to its priority num.
 }

 //**************************************************************************************
//This function insert the process accoding to its priority but							*
//Queue must have algorithm type "SJF".													*
//***************************************************************************************
 void ReadyQueue::insertProcessSJF(Process processInfo)
 {
	 int qNo = processInfo.getPriorityNum(); //Gets process priority num
	 queueNum[qNo-1].processInQueue.enQueue(processInfo); //insert in queue according to its priority num.
	 queueNum[qNo-1].processInQueue.sortQueue(); //Then sort that queue according to burst time.
 }
