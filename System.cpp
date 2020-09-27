/*
 * System.cpp
 *
 *  Created on: Aug 22, 2020
 *      Author: OS1
 */
#include "System.h"
#include "SCHEDULE.h"
#include "kerSem.h"
#include "thread.h"


unsigned oldTimerOFF, oldTimerSEG;
unsigned tsp,tss,tbp;
volatile int cntr=100;
volatile int context_switch_on_demand=0;

Idle* System::idle=0;
Thread* System::mainThread=0;

void interrupt timer(...){
	if(!context_switch_on_demand) {cntr--;
	timeList.update();
	tick(); }
	if (cntr==0 || context_switch_on_demand){
		asm{
			mov tsp,sp
			mov tss,ss
			mov tbp,bp
		}
		PCB::running->sp=tsp;
		PCB::running->ss=tss;
		PCB::running->bp=tbp;

		//SCHEDULER
		if (!PCB::running->finished && PCB::running->status==PCB::READY && PCB::running!=System::idle->getIdlePCB())
			Scheduler::put((PCB*)PCB::running);
		PCB::running=Scheduler::get();

		if (PCB::running==0)
			PCB::running=System::idle->getIdlePCB();

		tsp=PCB::running->sp;
		tss=PCB::running->ss;
		tbp=PCB::running->bp;

		cntr=PCB::running->quantum;
		if (cntr==0) cntr=-1; //na taj nacin nikad nece biti ispunjen uslov da je isteklo vreme(stiglo do nule)
		asm{
			mov sp,tsp
			mov ss,tss
			mov bp,tbp
		}
	}
	if (!context_switch_on_demand) asm int 60h;
	context_switch_on_demand=0;
}





void dispatch(){
#ifndef BCC_BLOCK_IGNORE
	lock
	context_switch_on_demand=1;
	timer();
	unlock
#endif
}

 void System::inic(){
	// postavlja novu prekidnu rutinu
#ifndef BCC_BLOCK_IGNORE
		asm{
			cli
			push es
			push ax

			mov ax,0
			mov es,ax // es = 0

			// pamti staru rutinu
			mov ax, word ptr es:0022h
			mov word ptr oldTimerSEG, ax
			mov ax, word ptr es:0020h
			mov word ptr oldTimerOFF, ax

			// postavlja novu rutinu
			mov word ptr es:0022h, seg timer //timer
			mov word ptr es:0020h, offset timer

			// postavlja staru rutinu na int 60h
			mov ax, oldTimerSEG
			mov word ptr es:0182h, ax
			mov ax, oldTimerOFF
			mov word ptr es:0180h, ax

			pop ax
			pop es
			sti
		}
#endif
}

void System::restore(){
#ifndef BCC_BLOCK_IGNORE
	asm {
			cli
			push es
			push ax

			mov ax,0
			mov es,ax

			mov ax, word ptr oldTimerSEG
			mov word ptr es:0022h, ax
			mov ax, word ptr oldTimerOFF
			mov word ptr es:0020h, ax

			pop ax
			pop es
			sti
		}
#endif
}

void System::startMain(){
#ifndef BCC_BLOCK_IGNORE
	lock
	System::inic();
	idle=new Idle();
	idle->myPCB->status=PCB::READY;
	mainThread=new Thread();
	PCB::running=(volatile PCB*)mainThread->myPCB;
//	mainThread->start();
	mainThread->myPCB->status=PCB::READY;
	//idle->start();
	unlock
#endif
}

void System::endMain(){
#ifndef BCC_BLOCK_IGNORE
	lock
	System::restore();
	delete idle;
	delete mainThread;
	unlock
#endif
}
