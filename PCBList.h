/*
 * PCBList.h
 *
 *  Created on: Sep 2, 2020
 *      Author: OS1
 */

#ifndef PCBLIST_H_
#define PCBLIST_H_

class PCB;

class PCBList{
	struct Elem{
		PCB* pcb;
		Elem* next;
		Elem(PCB* p,Elem *s=0){
			pcb=p; next=s;
		}};
		Elem *first, *last;
		Elem *cur,*prev;
		int n;
public:
		PCBList();
		virtual ~PCBList(); //mozda virtual?
		PCBList& add(PCB* p);
		PCBList& onFirst();
		PCBList& onNext();
		int isCur();
		PCB* getCur();
		PCBList& deleteCur();
		PCBList& deletePCB(PCB* p);
		int getSize();
};


#endif /* PCBLIST_H_ */
