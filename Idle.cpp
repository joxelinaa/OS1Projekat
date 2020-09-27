/*
 * Idle.cpp

 *
 *  Created on: Sep 4, 2020
 *      Author: OS1
 */


#include "Idle.h"
#include <stdio.h>
#include "System.h"

void Idle::run(){


	while(1){}
}
PCB* Idle::getIdlePCB(){
	return getMyPCB();
}



