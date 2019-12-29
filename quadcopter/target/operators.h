#pragma once
#include <stddef.h>
#include <stdlib.h>

__extension__ typedef int __guard __attribute__((mode(__DI__)));

extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release(__guard *);
extern "C" void __cxa_guard_abort(__guard *);


extern "C" void __cxa_pure_virtual(void);
void * operator new(unsigned int size);
void operator delete(void * ptr);