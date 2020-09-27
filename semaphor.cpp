/*
 * semaphor.cpp
 *
 *  Created on: Sep 8, 2020
 *      Author: OS1
 */
#include "semaphor.h"
#include "kerSem.h"
#include "System.h"

Semaphore::Semaphore(int init){
	myImpl=new KernelSem(this, init);

}
int Semaphore::val() const {
	return myImpl->val();
}

int Semaphore::wait(Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);;
}

int Semaphore::signal(int n){
	return  myImpl->signal(n);
}

Semaphore::~Semaphore(){
	delete myImpl;
	myImpl=0;
}

