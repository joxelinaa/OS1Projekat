/*
 * prepEntr.h
 *
 *  Created on: Sep 12, 2020
 *      Author: OS1
 */

#ifndef PREPENTR_H_
#define PREPENTR_H_

#include "IVTEntry.h"


#define PREPAREENTRY(No, flag)\
void interrupt intr##No(...);\
IVTEntry newEntry##No(No, intr##No);\
void interrupt intr##No(...){\
	(IVTEntry::IVTable[##No])->signalEv();\
	if (flag)\
	newEntry##No.myOldRoutine();\
	dispatch();\
}\



#endif /* PREPENTR_H_ */

