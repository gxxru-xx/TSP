#ifndef DATA_H_INCLUDED

#define DATA_H_INCLUDED

#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

struct SCity {
    std::string nazwa;
    int x;
	int y;
};


bool wybor (bool & opcja);
int sizeCities(std::string dataFile);
SCity* fillCities(std::string dataFile);
void printCities(SCity* cities, int ncity);
void saveCities(SCity* cities, int* iorder, int nsize, std::string outFile);


#endif // DATA_H_INCLUDED


