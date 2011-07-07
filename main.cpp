#include "draw.h"
#include "calculate.h"









int main()
{
    char opcja1='0';
    bool opcja2, opcja3,opcja4=NULL;
    /*opcja1-wprowadzanie danych
    opcja2-zapisywanie danych
    opcja3-wyniki szczegolowe
    opcja4-powrot do menu glownego
    */
    std::string outFile;
    while(!opcja4)
    {
        int nsize=0;
        std::cout<<"Wybierz opcję: "<<std::endl<<"1. Wprowadzanie danych z klawiatury"<<std::endl<<"2. Wprowadzanie danych z pliku"<<std::endl<<"3. Wyjście"<<std::endl;
        std::cin>>opcja1;
        SCity *cities;
        if (opcja1=='1')
        {
            std::cout<<"Wybrałeś wprowadzanie z klawiatury, podaj zatem liczbę miast: ";
            std::cin>>nsize;
            if(nsize>0)
            {
                cities=new SCity [nsize+1];
            }
            else
            {
                system("clear");
                std::cout<<"Podałeś błędną liczbę miast. Spróbuj jeszcze raz."<<std::endl;
                continue;
            }
            std::cout<<"Teraz podawaj po kolei:"<<std::endl;
            for (int i=1; i<=nsize; i++)
            {
                std::cout<<"Nazwa miasta nr "<<i<<"\t";
                std::cin >>cities[i].nazwa;
                std::cout<<"X: "<<"\t";
                std::cin >>cities[i].x;
                std::cout<<"Y: "<<"\t";
                std::cin >>cities[i].y;
            }

        }

        else if (opcja1=='2')
        {
            std::string dataFile;
            std::cout<<"Podaj nazwę pliku zawierającego dane na temat współrzędnych miast"<<std::endl;
            std::cin>>dataFile;
            nsize=sizeCities(dataFile);
            if(nsize>0)
            {
                if(fillCities(dataFile)!=0)
                {
                    cities=fillCities(dataFile);
                }
                else continue;

            }

            else continue;
        }
        else if (opcja1=='3')
        {
            std::cout<<"Dziękujemy za skorzystanie z programu."<<std::endl;
            return 0;
        }
        else
        {
            system("clear");
            std::cout<<"Podałeś nieznaną opcję. Spróbuj jeszcze raz."<<std::endl;;
            continue;
        }
        int *iorder=new int [nsize+1];
        for (int i=0; i<=nsize; i++)
            iorder[i]=i;
        std::cout<<"Wybierz format wyświetlania (zapisu) wyników: "<<std::endl<<"1. Szczegółowy "<<std::endl<<"2. Tylko wynik końcowy"<<std::endl;
        opcja3=wybor(opcja3);
        std::cout<<"Czy chcesz zapisać otrzymane dane wyjściowe do pliku? TAK (1) NIE (0)";
        opcja2=wybor(opcja2);
        if(opcja2)
        {

            std::cout<<"Podaj nazwę pliku, do którego mają zostać zapisane dane: ";
            std::cin>>outFile;
        }




        std::cout<<std::endl<<"Dziękuję, Twoje miasta to: "<<std::endl;


        printCities(cities,nsize);
        std::cout<<std::endl;


        anneal(cities, iorder, nsize, opcja3 , opcja2,outFile);
        double path=0.0;
        if(!opcja3&&nsize>3)
        {
            for (int j=1; j<nsize; j++)
            {
                path += ALEN(cities[iorder[j]].x,cities[iorder[j+1]].x,cities[iorder[j]].y,cities[iorder[j+1]].y);
            }

            path += ALEN(cities[iorder[nsize]].x,cities[iorder[1]].x,cities[iorder[nsize]].y,cities[iorder[1]].y);
            std::cout<<"Kolejno odwiedzane miasta to: "<<std::endl;
            for(int i=1; i<=nsize; i++)
            {
                std::cout<<i<<". "<<cities[iorder[i]].nazwa<<std::endl;
            }
            std::cout<< "Długość trasy = "<<path<<std::endl;
        };

        if(!opcja3&&opcja2)
        {
            saveCities(cities,iorder,nsize,outFile);
            std::cout<<std::endl<<std::endl;
        }
        std::cout<<std::endl<<std::endl;


        // drawing(cities, iorder, nsize);
        drawing2(cities, iorder, nsize,opcja2,outFile);
        std::cout<<std::endl<<"Co chcesz teraz zrobić?"<<std::endl<<"1. Zakończyć działanie programu"<<std::endl<<"2. Wyczyścić ekran i kontynuować pracę z programem"<<std::endl;
        opcja4=wybor(opcja4);
        if(opcja4)
        {
            std::cout<<"Dziękujemy za skorzystanie z programu."<<std::endl;
            return 0;
        }
        else system("clear");
        delete []iorder;
    }
    return 0;
}
