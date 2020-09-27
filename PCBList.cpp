/*
 * PCBList.cpp
 *
 *  Created on: Sep 2, 2020
 *      Author: OS1
 */
#ifndef PCBLIST_CPP_
#define PCBLIST_CPP_

#include "PCBList.h"
#include <stdio.h>
#include "System.h"

PCBList::PCBList(){
	first=last=cur=prev=0;
	n=0;
}

PCBList::~PCBList(){
	while(first){
		Elem* old=first;
		first=first->next;
		delete old;
	}
	last=cur=prev=0;
	n=0;
}

PCBList& PCBList::add(PCB* p){
	last=(!first? first:last->next)=new Elem(p);
	n++;
    return *this;
}

PCBList& PCBList::onFirst(){
	cur=first; prev=0;
	return *this;
}

PCBList& PCBList::onNext(){
	prev=cur;
	if (cur) cur=cur->next;
	return *this;
}

int PCBList::isCur(){
	return cur!=0;
}

PCB* PCBList::getCur(){
	if (!cur) {
		lock
		printf("Tekuci ne postoji");
		unlock
	}
	return cur->pcb;
}

PCBList& PCBList::deleteCur(){
	if (!cur) {
		lock
		printf("Tekuci je nullptr");
		unlock
	}
	else{
	Elem* old=cur;
	cur=cur->next;
	(!prev? first:prev->next)=cur;
	if (!cur) last=prev;
	old->next=0;//nzm jel treba ovo
	delete old;
	n--;
	}
	return *this;
}

int PCBList::getSize(){
	return n;
}

PCBList& PCBList::deletePCB(PCB* p){

	cur=first;
	prev=0;
	while (cur){
		if (cur->pcb!=p){
			prev=cur;
			cur=cur->next;
		}
		else{
			Elem* old=cur;
			cur=cur->next;
			if (!prev) first=cur;
			else prev->next=cur;
			if (old==last) last=prev;
			old->next=0;
			delete old;
			n--;
		}
	}
}


#endif

