/*
 * kerSem.h
 *
 *  Created on: Sep 8, 2020
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_
#include "semaphor.h"
#include "PCBList.h";
#include "SemList.h"

extern SemList timeList;

class KernelSem{
public:
	PCBList blockedList;
	KernelSem(Semaphore* s, int val);
	Semaphore *mySemaphore;
	int val() const;
	int wait (Time maxTimeToWait);
	int signal(int n=0);
private:
	int value;
protected:
	void block(Time t);
	int unblock(int n);

};

#endif /* KERSEM_H_ */

