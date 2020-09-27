/*
 * PCB.cpp
 *
 *  Created on: Aug 23, 2020
 *      Author: OS1
 */
#ifndef PCB_CPP_
#define PCB_CPP_

#include "PCB.h"
#include <dos.h>
#include <stdio.h>
#include "SCHEDULE.H"
#include "System.h"

int PCB::pid=-1;
volatile PCB* PCB::running=0;
/*volatile*/ PCBList listOfPCBs; //volatile jer ce se menjati i u prekidnim rutinama mozda?,proveri

void PCB::wrapper(){
	PCB::running->myThread->run();
	PCB* tmp;
	lock
	while (PCB::running->waitList.getSize()>0){
		PCB::running->waitList.onFirst();
		tmp=running->waitList.getCur();
		if (tmp!=0){
			lock
			tmp->status=PCB::READY;
			if (!tmp->finished){
			Scheduler::put(tmp);}
			PCB::running->waitList.deleteCur();
			unlock
		}
	}
	PCB::running->finished=1;
	unlock
	dispatch();

}


PCB::PCB(Thread* th, StackSize stackSize, Time s)
{
	myThread=th;
	quantum=s;
	finished=0;
	status=PCB::CREATED;
	id=pid++;
	timeExceeded=0;
#ifndef BCC_BLOCK_IGNORE
	listOfPCBs.add(this);
#endif
	size=stackSize/sizeof(unsigned);
	if(stackSize >= 65536)
		size = 65536/sizeof(unsigned);
	else if (stackSize<256)//proveri donje ogranicenje
		size=256/sizeof(unsigned);
	//mozda treba lock?
	stack=new unsigned[size];
	//setovanje I flega u pocetnom PSW-u za nit
	stack[size - 1] = 0x200;
#ifndef BCC_BLOCK_IGNORE
	//postavljanje adrese funkcije koju ce nit da izvrsava(PC)
	stack[size - 2] = FP_SEG(&(PCB::wrapper));
	stack[size - 3] = FP_OFF(&(PCB::wrapper));

	this->sp = FP_OFF(stack + size - 12);//-12 jer imamo -3 od gore i jos se cuva
	this->ss = FP_SEG(stack + size - 12);//ax,bx,cx,dx,es,ds,si,di,bp
	this->bp = FP_OFF(stack + size - 12);
#endif

}

PCB::~PCB(){
	if (stack!=0) {
		delete[] stack;
		stack=0; //da li ovo sme,mozda je greska tu? 5.9.2020.
	}
	listOfPCBs.deletePCB(this);//DODALA SAM 12.9.2020 proveri jel ovo ok??

}

int PCB::getID(){
	return id;
}

int PCB::getRunningID(){
	return PCB::running->id;
}

Thread* PCB::getThreadByID(ID id){

#ifndef BCC_BLOCK_IGNORE
	lock
	for (listOfPCBs.onFirst();listOfPCBs.isCur();listOfPCBs.onNext())
		if ((listOfPCBs.getCur()->id)==id)
			{
			unlock
			return listOfPCBs.getCur()->myThread;}
	unlock
#endif
	return 0;
}



void PCB::waitToComplete(){
#ifndef BCC_BLOCK_IGNORE
	lock
	if (finished) {
		unlock
		return;}
	if (this==PCB::running) {
		unlock
		return;}
	if (status==PCB::CREATED) {
		unlock
		return;}
	if (this==System::idle->myPCB) {
		unlock
		return; }
	PCB::running->status=PCB::BLOCKED;
	waitList.add((PCB*)PCB::running);
	unlock
#endif
	dispatch();

}

void PCB::ispis(){
	for (listOfPCBs.onFirst();listOfPCBs.isCur();listOfPCBs.onNext()){
			printf("Nit  :%d\n",listOfPCBs.getCur()->getID());
		}
}


#endif

