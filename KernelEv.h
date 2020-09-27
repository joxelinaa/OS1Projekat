/*
 * KernelEv.h
 *
 *  Created on: Sep 12, 2020
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_
#include "PCB.h"
#include "event.h"
#include "IVTEntry.h"

class KernelEv{
private:
	int value;
	PCB* myPCB;
	IVTEntry* entry;

public:
	KernelEv(IVTNo ivtNo);
	void wait();
	void signal();
	virtual ~KernelEv();
};


#endif /* KERNELEV_H_ */

