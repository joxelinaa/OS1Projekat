/*
 * SemList.h
 *
 *  Created on: Sep 9, 2020
 *      Author: OS1
 */

#ifndef SEMLIST_H_
#define SEMLIST_H_
//#include "PCB.h"
class PCB;
class KernelSem;
//class PCBList;


class SemList{
	struct Elem{
		PCB* pcb;
		KernelSem* sem;
		int time;
		Elem* next;
		Elem(PCB* p, int t,KernelSem* s)
		{  pcb=p; time=t; sem=s; next=0;}
	};
	Elem *first;
	Elem *cur,*prev;
	int n;
public:
	SemList();
	~SemList();
	SemList& add(PCB* p, int t,KernelSem* s);
	SemList& deletePCB(PCB* p);
	int getSize();
	void update();

};

#endif /* SEMLIST_H_ */

