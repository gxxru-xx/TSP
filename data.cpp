#include "data.h"

bool wybor (bool & opcja)
{
    char znak='0';
    std::cin>>znak;
    if(znak=='1')
    {
        opcja=true;
    }
    else
        opcja=false;
    return opcja;
}


int sizeCities(std::string dataFile)
{
    std::ifstream inFile;
    int nsize=0;
    inFile.open(dataFile.c_str());
    if(inFile.good())
    {
        std::string sprawdz;
        inFile>>sprawdz;

        if(sprawdz=="Liczba_miast:")
        {
            inFile>>nsize;
            inFile.close();
            return nsize;
        }
        else
        {
            std::cerr<<"Plik ma zły format i nie może zostać odczytany. Spróbuj jeszcze raz. "<<std::endl;
            inFile.close();
            return 0;
        }
    }
    else
    {
        std::cerr<<"Błąd odczytu pliku."<<std::endl;
        return 0;
    }

}
SCity* fillCities(std::string dataFile)
{
    std::ifstream inFile;
    inFile.open(dataFile.c_str());
    if(inFile.good())
    {
        std::string smietnik;
        inFile>>smietnik;
        SCity tmp;
        tmp.nazwa='0';
        tmp.x=tmp.y=-1;
        int nsize;
        inFile>>nsize;
        SCity *cities=new SCity [nsize+1];
        int i=1;
        do
        {
            inFile>> smietnik;

            if(smietnik=="Nazwa:")
            {
                inFile>>tmp.nazwa;
            }
            else
            {
                std::cerr<<"Plik ma zły format i nie może zostać odczytany. Spróbuj jeszcze raz. "<<std::endl;
                inFile.close();
                return 0;
            }
            inFile>> smietnik;

            if(smietnik=="X:")
            {
                inFile>>tmp.x;
            }
            else
            {
                std::cerr<<"Plik ma zły format i nie może zostać odczytany. Spróbuj jeszcze raz. "<<std::endl;
                inFile.close();
                return 0;
            }
            inFile>> smietnik;

            if(smietnik=="Y:")
            {
                inFile>>tmp.y;
            }
            else
            {
                std::cerr<<"Plik ma zły format i nie może zostać odczytany. Spróbuj jeszcze raz. "<<std::endl;
                inFile.close();
                return 0;
            }

            cities[i]=tmp;
            i++;
        }
        while (i<=nsize);
        inFile.close();
        return cities;
    }
    else
    {
        std::cerr<<"Błąd odczytu pliku.";
        return 0;
    }
}

void printCities(SCity* cities,int ncity)
{
    for (int i=1; i<=ncity; i++)
    {
        std::cout<<"Numer: "<<i<<"\t"<<"Nazwa: "<<cities[i].nazwa<<"\t"<<"X: "<<cities[i].x<<"\t"<<"Y: "<<cities[i].y<<std::endl;
    }
}

void saveCities(SCity* cities, int* iorder, int nsize, std::string outFile)
{
    std::ofstream dataFile;
    dataFile.open(outFile.c_str());
    dataFile<<"Liczba_miast: "<<nsize<<std::endl;
    for (int i=1; i<=nsize; i++)
        dataFile<<"Nazwa: "<<cities[iorder[i]].nazwa<<"\t"<<"X: "<<cities[iorder[i]].x<<"\t"<<"Y: "<<cities[iorder[i]].y<<std::endl;
    dataFile.close();
}
