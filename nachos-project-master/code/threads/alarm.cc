// alarm.cc
//	Routines to use a hardware timer device to provide a
//	software alarm clock.  For now, we just provide time-slicing.
//
//	Not completely implemented.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "alarm.h"
#include "main.h"

//----------------------------------------------------------------------
// Alarm::Alarm
//      Initialize a software alarm clock.  Start up a timer device
//
//      "doRandom" -- if true, arrange for the hardware interrupts to
//		occur at random, instead of fixed, intervals.
//----------------------------------------------------------------------

Alarm::Alarm(bool doRandom) { timer = new Timer(doRandom, this); sleepList = NULL; /*sleepList declared and initialised to NULL*/}

//----------------------------------------------------------------------
// Alarm::CallBack
//	Software interrupt handler for the timer device. The timer device is
//	set up to interrupt the CPU periodically (once every TimerTicks).
//	This routine is called each time there is a timer interrupt,
//	with interrupts disabled.
//
//	Note that instead of calling Yield() directly (which would
//	suspend the interrupt handler, not the interrupted thread
//	which is what we wanted to context switch), we set a flag
//	so that once the interrupt handler is done, it will appear as
//	if the interrupted thread called Yield at the point it is
//	was interrupted.
//
//	For now, just provide time-slicing.  Only need to time slice
//      if we're currently running something (in other words, not idle).
//----------------------------------------------------------------------

void Alarm::CallBack() {

    struct SleepInfo *currentSleep = sleepList;
    struct SleepInfo *prevSleep = NULL;
    while(currentSleep != NULL) {
        currentSleep->sleepTimeLeft--;
        if(currentSleep->sleepTimeLeft <= 0) {
            if(prevSleep == NULL) {
                sleepList = currentSleep->next;
            } else {
                prevSleep->next = currentSleep->next;
            }
            currentSleep->thread->setStatus(READY);
            kernel->scheduler->ReadyToRun(currentSleep->thread);
            struct SleepInfo *temp = currentSleep;
            currentSleep = currentSleep->next;
            free(temp);
        } else {
            prevSleep = currentSleep;
            currentSleep = currentSleep->next;
        }
    }

    Interrupt *interrupt = kernel->interrupt;
    MachineStatus status = interrupt->getStatus();

    if (status != IdleMode) {
        interrupt->YieldOnReturn();
    }
}

// void Alarm::WaitUntil(int x) {
//     int now = kernel->stats->totalTicks;

//     while (x > now) {
//         kernel->currentThread->Yield();
//         now = kernel->stats->totalTicks;
//     }
// }

void Alarm::WaitUntil(int x) {
    // int now = kernel->stats->totalTicks;

    // if (x > now) {
    //     struct SleepInfo *newSleep = new struct SleepInfo;
    //     newSleep->sleepTimeLeft = x - now;
    //     newSleep->thread = kernel->currentThread;
    //     newSleep->next = sleepList;
    //     sleepList = newSleep;
    //     kernel->interrupt->SetLevel(IntOff);
    //     kernel->currentThread->Sleep(false);
    //     kernel->interrupt->SetLevel(IntOn);
    // }

    struct SleepInfo *newSleep = (struct SleepInfo *)malloc(sizeof(struct SleepInfo));
    newSleep->sleepTimeLeft = x;
    newSleep->thread = kernel->currentThread;
    newSleep->next = sleepList;
    sleepList = newSleep;
}