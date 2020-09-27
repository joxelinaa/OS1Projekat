/*
 * IVTEntry.cpp
 *
 *  Created on: Sep 12, 2020
 *      Author: OS1
 */

#include <dos.h>
#include "IVTEntry.h"
#include "System.h"
#include "KernelEv.h"

IVTEntry* IVTEntry::IVTable[256]={0};

IVTEntry::IVTEntry(IVTNo number, InterruptRoutine newRoutine){
	myEvent=0;
	myEntryNumber=number;
	myOldRoutine=0;
	myNewRoutine=newRoutine;
	IVTable[number]=this;
	lock
	this->myOldRoutine = getvect(number);
	setvect(number, newRoutine);
	unlock
}

IVTEntry::~IVTEntry(){
	lock
	setvect(myEntryNumber,myOldRoutine);
	unlock
	myOldRoutine = 0;
	myNewRoutine = 0;
	myEvent = 0;
	IVTable[myEntryNumber] = 0;
}

KernelEv* IVTEntry::getMyEvent(){
	return myEvent;
}

void IVTEntry::signalEv(){
	myEvent->signal();
}


