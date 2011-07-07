#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED


#include "data.h"

int mapsize( SCity *cities, int ncity);
void clearmap(int rozmiar, char **map);
void borderdrawing(int rozmiar, char **map);
void pathdrawing (int rozmiar, char **map,SCity *cities, int* iorder, int ncity);
void displaymap(int rozmiar, char **map);
void drawing2(SCity *cities, int* iorder, int ncity, bool opcja, std::string outFile);

#endif // DRAW_H_INCLUDED

