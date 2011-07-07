#include "draw.h"
//modul rysowania operuje tylko na pierwszej cwiartce i w zakresie x:<0;38> y:<0;37>
int mapsize( SCity *cities, int ncity)
{
    int rozmiarx,rozmiary;
    rozmiarx=rozmiary=0;
    for (int i=1; i<=ncity; i++)
    {
        if(rozmiarx<abs(cities[i].x))
        {
            rozmiarx=abs(cities[i].x);
        }
        if(rozmiary<abs(cities[i].y))
        {
            rozmiary=abs(cities[i].y);
        }


    }
    if(rozmiarx>rozmiary)
        return 2*rozmiarx;
    else return 2*rozmiary;

}
void clearmap(int rozmiar, char **map)
{
//czyscimy mape
    for(int i=0; i<rozmiar; i++)
    {
        for(int j=0; j<2*rozmiar; j++)
        {
            map[i][j]=' ';
        }
    }
}

void borderdrawing(int rozmiar, char **map)
{
//jeszcze ramka, żeby było estetycznie :D do tego oski jeszcze
    for (int i=1; i<2*rozmiar-1; i++)
    {
        map[0][i]=map[rozmiar-1][i]='_';
        map[int(rozmiar/2)][i]='-';
        map[int((i+1)/2)][0]=map[int((i+1)/2)][2*rozmiar-1]=map[int((i+1)/2)][rozmiar]='|';
    }

}

void pathdrawing (int rozmiar, char **map,SCity *cities, int* iorder, int ncity)
{

//algorytm rysowania linii Bresenhama ;]
    int dx,dy,sx,sy;
    double err,e2;
    SCity mem;
    mem.x=cities[iorder[1]].x;
    mem.y=cities[iorder[1]].y;      //zapamietujemy wspolrzedne pierwszego punktu bo zostaja pozniej zmienione

    for (int i=1; i<ncity; i++)
    {


        dx = abs(cities[iorder[i+1]].x-cities[iorder[i]].x);
        dy = abs(cities[iorder[i+1]].y-cities[iorder[i]].y);
        if (cities[iorder[i]].x < cities[iorder[i+1]].x)
        {
            sx = 1;
        }
        else
        {
            sx = -1;
        }
        if (cities[iorder[i]].y < cities[iorder[i+1]].y)
        {
            sy = 1;
        }
        else
        {
            sy = -1;
        }

        err = dx-dy;

        while(((cities[iorder[i]].x != (cities[iorder[i+1]].x)) || (cities[iorder[i]].y != cities[iorder[i+1]].y)))
        {
            map[rozmiar/2- (cities[iorder[i]].y)][rozmiar+2*(cities[iorder[i]].x)] ='*';
            e2 = 2*err;
            if (e2 > -dy)
            {
                err = err - dy;
                cities[iorder[i]].x  = cities[iorder[i]].x  + sx;
            }

            if (e2 <  dx)
            {
                err = err + dx;
                cities[iorder[i]].y  = cities[iorder[i]].y  + sy;
            }

        }
    }

//ostatnia linia
    {
        dx = abs(mem.x-cities[iorder[ncity]].x);
        dy = abs(mem.y-cities[iorder[ncity]].y);
        if (cities[iorder[ncity]].x < mem.x)
        {
            sx = 1;
        }
        else
        {
            sx = -1;
        }
        if (cities[iorder[ncity]].y < mem.y)
        {
            sy = 1;
        }
        else
        {
            sy = -1;
        }

        err = dx-dy;

        while(((cities[iorder[ncity]].x != mem.x) || (cities[iorder[ncity]].y != mem.y)))
        {
            map[rozmiar/2-(cities[iorder[ncity]].y)][rozmiar+2*(cities[iorder[ncity]].x)]='*';
            e2 = 2*err;
            if (e2 > -dy)
            {
                err = err - dy;
                cities[iorder[ncity]].x  = cities[iorder[ncity]].x  + sx;
            }

            if (e2 <  dx)
            {
                err = err + dx;
                cities[iorder[ncity]].y= cities[iorder[ncity]].y  + sy;
            }

        }
    }

    //zaznaczamy miasta X

    for (int i=1; i<=ncity; i++)
    {
        map[rozmiar/2- (cities[iorder[i]].y)][rozmiar+2*(cities[iorder[i]].x)] = 'X';
    }

}

void displaymap(int rozmiar, char **map)
{

//no i wyświetlamy
    for(int i=0; i<rozmiar; i++)
    {
        for(int j=0; j<2*rozmiar; j++)
        {
            std::cout<<map[i][j];
        }
        std::cout<<std::endl;
    }
}

void drawing2(SCity *cities, int* iorder, int ncity, bool opcja, std::string outFile)
{
    const int maxsize=102;
    bool opcja1;
    char **map;
    int rozmiar=mapsize(cities,ncity)+4;
    int skala=1;
    //zakladam ze akurat szerokosc konsoli to cos kolo tego
    if(rozmiar>maxsize-1)
    {

        map=new char *[maxsize];
        for (int i=0; i<maxsize; i++)
            map[i]=new char[2*maxsize];

        //skalowanie
        for (int i=1; i<=ncity; i++)
        {
            cities[i].y = ((maxsize-2)/double(rozmiar))*(cities[i].y);
            cities[i].x = ((maxsize-2)/double(rozmiar))*(cities[i].x);
        }
        skala=double(rozmiar)/(maxsize-2);
        std::cout<<"Skala przedstawionego rysunku to 1:"<<skala<<std::endl;
        rozmiar=maxsize;

        opcja1=true;
    }
    else
    {
        map=new char *[rozmiar];
        for (int i=0; i<rozmiar; i++)
            map[i]=new char[2*rozmiar];
        opcja1=false;
        std::cout<<"Skala przedstawionego rysunku to 1:1"<<std::endl;
    }

//printCities(cities,ncity); w ramach sprawdzenia czy zmienily sie wspolrzedne

    clearmap(rozmiar,map);
    borderdrawing(rozmiar, map);
    pathdrawing (rozmiar, map,cities, iorder, ncity);
    displaymap(rozmiar, map);



//dopisanie mapy do pliku
    if(opcja!=0)
    {
        std::ofstream dataFile;
        dataFile.open(outFile.c_str(), std::ios::app);
        dataFile<<"Skala przedstawionego rysunku to 1:"<<skala<<std::endl;

        for(int i=0; i<rozmiar; i++)
        {
            for(int j=0; j<2*rozmiar; j++)
            {
                dataFile<<map[i][j];
            }
            dataFile<<std::endl;
        }

        dataFile.close();
    }


    if(opcja1)
    {

        for (int i=0; i<maxsize; i++)
        {
            delete [] map[i];
        }
        delete []map;
    }
    else
    {
        for (int i=0; i<rozmiar; i++)
        {
            delete [] map[i];
        }
        delete []map;
    }
}


