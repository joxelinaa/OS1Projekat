/*
 * KernelEv.cpp
 *
 *  Created on: Sep 12, 2020
 *      Author: OS1
 */

#include "KernelEv.h"
#include "IVTEntry.h"
#include "System.h"
#include "SCHEDULE.H"

KernelEv::KernelEv(IVTNo ivtNo){
	if (PCB::running!=System::idle)
	myPCB=(PCB*)PCB::running;
	value=0;
	IVTEntry::IVTable[ivtNo]->myEvent = this;
	entry= IVTEntry::IVTable[ivtNo];
}

KernelEv::~KernelEv(){
	myPCB=0;
	entry->myEvent=0;
}

void KernelEv::signal(){
	lock
	if (value==0){
		myPCB->status=PCB::READY;
		Scheduler::put(myPCB);
		value=1;
	}
	unlock
}

void KernelEv::wait(){
	lock
	if (PCB::running!=myPCB){
		unlock
		return;}
	if (value==0){
		myPCB->status=PCB::BLOCKED;
		dispatch();
	} else if(value==1) value=0;
	unlock
}

