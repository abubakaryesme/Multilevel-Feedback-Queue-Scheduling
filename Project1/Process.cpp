//Class Implementation :
#include<iostream>
#include<string>
#include "Process.h"

using namespace std;



//***********************************************************
//Default Constructor for Process class.					*
//***********************************************************
Process::Process()
{
	priorityNum = arrivalTime = burstTime = remainingBurstTime = 0;
	waitingStartInQueue = startTime= finalTime = -1;
	processName = "";
}

//***************************************************************************************************
//Copy Constructor for Process Class which makes the copy of the object that pass it as parameter.	*
//***************************************************************************************************
Process::Process(const Process& orig)
{
	processName = orig.processName;
	priorityNum = orig.priorityNum;
	arrivalTime = orig.arrivalTime;
	burstTime = orig.burstTime;
	remainingBurstTime = orig.remainingBurstTime;
	waitingStartInQueue = orig.waitingStartInQueue;
	startTime = orig.startTime;
	finalTime = orig.finalTime;
}

//***********************************************
//Destructor for Process class.					*
//***********************************************
Process::~Process()
{
}

//***********************************************************************************
//This Overloads the < operator to compare two Process objects to					*
//determine whether one Process object(left operand) is smaller						*
//than the other Process object(right operand) on the basis of arrival time			*
// if process is not in queue yet otherwise on the basis of remaining  burst time.	* 
//***********************************************************************************
bool Process::operator < (const Process& rhs) const
{
	//WaitingStartInQueue == -1 represents that a process is not yet in queue
	//as waiting time starts in queue when a process eneters in Queue.

	if (waitingStartInQueue == -1)   //If process is not in queue then
		return arrivalTime < rhs.arrivalTime; //returns on the basis of arrival time.
	else //otherwise
		return remainingBurstTime < rhs.remainingBurstTime; //returns according to remaining burst time.
}

//***********************************************************************************
//This Overloads the > operator to compare two Process objects to					*
//determine whether one Process object(left operand) is larger						*
//than the other Process object(right operand) on the basis of arrival time			*
// if process is not in queue yet otherwise on the basis of remaining burst time.	* 
//***********************************************************************************
bool Process::operator > (const Process& rhs)const
{
	if (waitingStartInQueue == -1) 
		return arrivalTime > rhs.arrivalTime; 
	else  
		return remainingBurstTime > rhs.remainingBurstTime; 
}

//***********************************************************************************
//This Overloads the <= operator to compare two Process objects to					*
//determine whether one Process object(left operand) is smaller than or				*
//equal to the other Process object(right operand) on the basis of arrival time		*
// if process is not in queue yet otherwise on the basis of remaining  burst time.	* 
//***********************************************************************************
bool Process::operator <= (const Process& rhs) const
{
	if (waitingStartInQueue == -1) //If process is not in queue then
		return arrivalTime <= rhs.arrivalTime; //returns on the basis of arrival time.
	else //otherwise
		return remainingBurstTime <= rhs.remainingBurstTime;  //returns according to remaining burst time.
}


//***********************************************************************************
//This Overloads the >= operator to compare two Process objects to					*
//determine whether one Process object(left operand) is larger than or				*
//equal to the other Process object(right operand) on the basis of arrival time		*
// if process is not in queue yet otherwise on the basis of remaining burst time.	* 
//***********************************************************************************
bool Process::operator >= (const Process& rhs)const
{
	if (waitingStartInQueue == -1) 
		return arrivalTime >= rhs.arrivalTime;  
	else 
		return remainingBurstTime >= rhs.remainingBurstTime; 
}

//*******************************************************************************
//This Overloads the == operator to compare two Process objects					*
//It decide on the basis of arriavl time if the process is not					*
// in queue yet otherwise it decide on the basis of remaining bust time.		*
//*******************************************************************************
bool Process::operator == (const Process& rhs)const
{
	if (waitingStartInQueue == -1) //If process is not in queue then
		return arrivalTime == rhs.arrivalTime;  //returns on the basis of arrival time.
	else //otherwise
		return remainingBurstTime == rhs.remainingBurstTime; //returns according to remaining burst time.
}

//*******************************************************************************
//This Overloads the >= operator to compare two Process objects					*
//It decide on the basis of arriavl time if the process is not					*
// in queue yet otherwise it decide on the basis of remaining bust time.		*
//*******************************************************************************
bool Process::operator != (const Process& rhs)const
{
	if (waitingStartInQueue == -1) //If process is not in queue then
		return arrivalTime != rhs.arrivalTime; //returns on the basis of arrival time.
	else //otherwise
		return remainingBurstTime != rhs.remainingBurstTime; //returns according to remaining burst time.
}

//*******************************************************************************
//This Overloads the Assignment Operator for Process class						*
//which can be used to assign one Process object to another.					*
//*******************************************************************************
const Process& Process::operator = (const Process& rhs)
{

	if (this != &rhs) //Check for Self assignment.
	{
		//Copying object:
		processName = rhs.processName;
		priorityNum = rhs.priorityNum;
		arrivalTime = rhs.arrivalTime;
		burstTime = rhs.burstTime;
		remainingBurstTime = rhs.remainingBurstTime;
		waitingStartInQueue = rhs.waitingStartInQueue;
		startTime = rhs.startTime;
		finalTime = rhs.finalTime;
	}
	return *this; //returns
}

//****************************************************************************************************************
//This function takes a value as parameter and substract that value from remaining burst time.					 *
//-->If the remaining burst time is smaller than value(quantum) then return the differnce (left quantum)		 *
//-->If remaining burst time is larger or equal then returns 0.													 *
//****************************************************************************************************************
int Process::substractBurst(int value)
{
	if ((remainingBurstTime - value) >= 0) //If larger or equal
		remainingBurstTime -= value; //the substract that value from remaining burst. 
	else //otherwise in case of smaller
	{
		int leftQuantum = value - remainingBurstTime; //get difference / left quantum
		remainingBurstTime = 0;
		return leftQuantum; //returns left quantum/difference.
	}
	return 0; //returns 0 as its larger or equal.
}

