#ifndef CTIME_H
#define CTIME_H

#include "processing.h"
#include "matriz.h"
#include "cTime.h"
// Marcar tempo costuma ser um pouco diferente em Windows e Linux. Embaixo eu usei diretivas de compilacao -
// os #ifdef, #else e #endif. Eles verificam se voce esta tentando compilar em Windows ou nao. Se for em
// Windows, o compilador vai considerar so o codigo dentro do #ifdef _WIN32 e ignorar o codigo no #else.
// Se nao for Windows, o compilador vai ignorar o codigo dentro de #ifdef _WIN32 e usar somente o codigo
// dentro do #else
#ifdef _WIN32
#include <time.h>
#else
#include <sys/times.h>
#include <sys/unistd.h>
#endif
	float getTime();
	

#endif