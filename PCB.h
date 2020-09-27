/*
 * PCB.h
 *
 *  Created on: Aug 23, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "thread.h"
#include "PCBList.h"

class PCB{
public:
	unsigned sp;
	unsigned ss;
	unsigned bp;
	unsigned finished;
	int quantum;
	unsigned* stack;
	int size;
	int timeExceeded;
	Thread* myThread;
	static volatile PCB* running;
	enum Status {CREATED, READY, BLOCKED};
	volatile Status status;
	static void wrapper();
	PCB(Thread* th, StackSize stackSize, Time s);
	virtual ~PCB();
	int getID();
	static int getRunningID();
	static Thread* getThreadByID(ID id);
	void waitToComplete();
	PCBList waitList;
	static void ispis();

private:
	static int pid;
	int id;

};


#endif /* PCB_H_ */
