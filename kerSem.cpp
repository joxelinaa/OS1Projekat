/*
 * kerSem.cpp
 *
 *  Created on: Sep 8, 2020
 *      Author: OS1
 */
#include "kerSem.h"
#include "System.h"
#include "SCHEDULE.h"
#include "SemList.h"
#include "PCB.h"

SemList timeList;

KernelSem::KernelSem(Semaphore* s, int val){
	mySemaphore=s;
	value=val;
}

int KernelSem::val() const{
	return value;
}

int KernelSem::wait(Time maxTimeToWait){
	lock
	int res=1;
	if (--value<0){
		block(maxTimeToWait);
		if (PCB::running->timeExceeded==1) res=0;
	}

	unlock
	return res;
}

int KernelSem::signal(int n){
	lock
	int res=0;
	if (n<0)
		res=n;
	else{
		if (n==0) {
			if (value++<0) unblock(1);
		}
		else {
			if ((value+n)<0)
			    res=unblock(n);
			value+=n;
		}
	}
	unlock
	return res;
}

void KernelSem::block(Time t){
	//lock
	PCB::running->status=PCB::BLOCKED;
	if (t!=0) {
		//PCB::running->timeExceeded=0; //ne znam da li treba ovo?
		timeList.add((PCB*)PCB::running,t,this);
	}
	blockedList.add((PCB*)PCB::running);
	//unlock
	dispatch();
}

int KernelSem::unblock(int n){
//	lock
	int t=0;
	if (n>blockedList.getSize()) n=blockedList.getSize();
	blockedList.onFirst();
			while (n>0){
				blockedList.getCur()->status=PCB::READY;
				Scheduler::put(blockedList.getCur());
				timeList.deletePCB(blockedList.getCur());
				blockedList.deleteCur();
				n--; t++;
			}
	//unlock
	return t;
}

