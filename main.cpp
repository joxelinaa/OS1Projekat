/*
 * main.cpp
 *
 *  Created on: Aug 22, 2020
 *      Author: OS1
 */

#include <iostream.h>
#include "System.h"


extern int userMain (int argc, char* argv[]);


int main(int argc, char* argv[]){
	System::startMain();
	int ret = userMain(argc,argv);
    System::endMain();
	return ret;
}

