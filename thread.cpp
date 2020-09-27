/*
 * thread.cpp
 *
 *  Created on: Aug 23, 2020
 *      Author: OS1
 */

#include "thread.h"
#include "SCHEDULE.H"
#include "PCB.h"
#include "System.h"

Thread::Thread(StackSize stackSize, Time timeSlice){
	myPCB=new PCB(this, stackSize, timeSlice);
}

ID Thread::getId(){
	return (ID)myPCB->getID();
}


ID Thread::getRunningId(){
	return PCB::getRunningID();
}


Thread* Thread::getThreadById(ID id){
	return PCB::getThreadByID(id);
}


void Thread::waitToComplete(){
	myPCB->waitToComplete();
}


void Thread::start(){
#ifndef BCC_BLOCK_IGNORE
	lock
	if(myPCB->status == PCB::CREATED){
		myPCB->status = PCB::READY;
		Scheduler::put(myPCB);
	}
	unlock
#endif
}

Thread::~Thread(){
	waitToComplete();
#ifndef BCC_BLOCK_IGNORE
	lock
	if (myPCB!=0)
		delete myPCB;
	myPCB=0; //5.9.2020. mozda je ovo greska?
	unlock
#endif
}

void Thread::ispisi(){
	PCB::ispis();
}

PCB* Thread::getMyPCB(){
	return myPCB;
}



