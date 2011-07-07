#ifndef CALCULATE_H_INCLUDED
#define CALCULATE_H_INCLUDED

#include "data.h"

int irbit1(unsigned long *iseed);
float ran3(long *idum);
int metrop(float de, float t);
float revcst(SCity* cities, int* iorder, int* n,int ncity);
void reverse(int ncity, int* iorder, int* n);
float trncst(SCity* cities,int* iorder, int* n,int ncity);
void trnspt(int* iorder, int ncity, int* n);
void anneal(SCity* cities,int* iorder,int ncity, bool opcja, bool zapis,std::string outFile);
double ALEN(int x1, int x2, int y1, int y2);
#endif // CALCULATE_H_INCLUDED
