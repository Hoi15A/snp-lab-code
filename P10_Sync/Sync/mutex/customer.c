/*******************************************************************************
* File:     customer.c
* Purpose:  customer thread
* Course:   bsy
* Author:   M. Thaler, 2011
* Revision: 5/2012
* Version:  v.fs20
*******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <pthread.h>

#include "commonDefs.h"
#include "mrand.h"

#define FATAL(M) do {perror(M); return EXIT_FAILURE;} while(0);

//*****************************************************************************

void *customer(void* data) {
    float  ranNum;
    int    i;
    rand_t randnum;
    
    cData *cD = (cData *) data;
    

    rand_seed(&randnum, 0); 

    // put coin and select coffee
    for (i = 0; i < ITERATIONS; i++) {
        ranNum = rand_float(&randnum);
        if (pthread_mutex_lock(&(cD->lock)) != 0) FATAL("Lock failed");
        cD->coinCount      += 1;
        if (ranNum < 0.5)
            cD->selCount1 += 1;
        else
            cD->selCount2 += 1;
        if (pthread_mutex_unlock(&(cD->lock)) != 0) FATAL("Unlock failed");
    }
    
    pthread_exit(0);  
}

//*****************************************************************************

/*
4.1 d)
    Kann man nicht wissen da der scheduler bestimmt wann welcher thread (kunde) arbeiten (bestellen) kann.
*/