/*
 * Idle.h
 *
 *  Created on: Sep 4, 2020
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_
#include "Thread.h"
#include <stdio.h>

class Idle:public Thread{
public:
	Idle():Thread(){}
	void run();
	PCB* getIdlePCB();
};


#endif /* IDLE_H_ */
