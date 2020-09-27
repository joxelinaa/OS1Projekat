/*
 * System.h
 *
 *  Created on: Aug 22, 2020
 *      Author: OS1
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_
#include <dos.h>
#include "Idle.h"
#include "PCB.h"

class Thread;
class PCB; //ovo je mozda bio problem(delete idle nervni slom)
void tick();
#define lock asm{pushf;cli;}

#define unlock asm popf

class System {
public:
	static void inic();
	static void restore();
	static void startMain();
	static void endMain();
    static Idle* idle;
    static Thread* mainThread;
};


#endif /* SYSTEM_H_ */

