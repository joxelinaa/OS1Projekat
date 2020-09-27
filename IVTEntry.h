/*
 * IVTEntry.h
 *
 *  Created on: Sep 12, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "event.h"

typedef void interrupt (*InterruptRoutine)(...);

class IVTEntry{
	IVTNo myEntryNumber;
	friend class KernelEv;
	KernelEv* myEvent;
public:
	IVTEntry(IVTNo ivtNo, InterruptRoutine newRoutine);
	static IVTEntry* IVTable[256];
	InterruptRoutine myOldRoutine,myNewRoutine;
	KernelEv* getMyEvent();
	void signalEv();
	virtual ~IVTEntry();

};



#endif /* IVTENTRY_H_ */


