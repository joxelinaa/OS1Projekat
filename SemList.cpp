/*
 * SemList.cpp
 *
 *  Created on: Sep 9, 2020
 *      Author: OS1
 */
#include "SemList.h"
#include <stdio.h>
#include "System.h"
#include "SCHEDULE.h"
#include "kerSem.h"

SemList::SemList(){
	first=prev=cur=0;
	n=0;
}

SemList::~SemList(){
	while(first){
		Elem* old=first;
		first=first->next;
		delete old;
	}
	cur=prev=0;
	n=0;
}

int SemList::getSize(){
	return n;
}

SemList& SemList::add(PCB* p, int t,KernelSem* s){
	lock
	cur=first;
	prev=0;
	if (!first) {
		first = new Elem(p, t, s);
		n++;
		unlock
		return *this;
	}
	while(cur){
		prev=cur;
		cur=cur->next;
	}
	Elem* tmp = new Elem(p, t, s);
	prev->next = tmp;
	tmp->next = cur;
	n++;
	unlock
	return *this;
}

void SemList::update(){
	lock
	prev=0;
	cur=first;
	while (cur){
		cur->time--;
		if (cur->time==0){
			cur->pcb->timeExceeded=1;
			cur->sem->blockedList.deletePCB(cur->pcb);
			cur->pcb->status=PCB::READY;
			Scheduler::put(cur->pcb);
			Elem* old=cur;
			cur=cur->next;
			(!prev ? first : prev->next)=cur;
			old->next=0;
			delete old;
			n--;
		} else{
			prev=cur; cur=cur->next;
		}
	}
	unlock
}


SemList& SemList::deletePCB(PCB* p){
	lock
	prev=0;
	cur=first;
	while (cur){
		if (cur->pcb!=p){
			prev=cur;
			cur=cur->next;
		} else{
			Elem* old=cur;
			cur=cur->next;
			if(!prev) first=cur;
			else prev->next=cur;
			old->next=0;
			delete old;
			n--;
		}
	}
	unlock
	return *this;

}
