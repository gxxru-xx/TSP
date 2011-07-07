#include "calculate.h"



int irbit1(unsigned long *iseed)
{
    unsigned long newbit;

    newbit =  (*iseed >> 17) & 1
              ^ (*iseed >> 4) & 1
              ^ (*iseed >> 1) & 1
              ^ (*iseed & 1);
    *iseed=(*iseed << 1) | newbit;
    return (int) newbit;
}




#define MBIG 1000000000
#define MSEED 161803398
#define MZ 0
#define FAC (1.0/MBIG)

float ran3(long *idum)
{
    static int inext,inextp;
    static long ma[56];
    static int iff=0;
    long mj,mk;
    int i,ii,k;

    if (*idum < 0 || iff == 0)
    {
        iff=1;
        mj=MSEED-(*idum < 0 ? -*idum : *idum);
        mj %= MBIG;
        ma[55]=mj;
        mk=1;
        for (i=1; i<=54; i++)
        {
            ii=(21*i) % 55;
            ma[ii]=mk;
            mk=mj-mk;
            if (mk < MZ) mk += MBIG;
            mj=ma[ii];
        }
        for (k=1; k<=4; k++)
            for (i=1; i<=55; i++)
            {
                ma[i] -= ma[1+(i+30) % 55];
                if (ma[i] < MZ) ma[i] += MBIG;
            }
        inext=0;
        inextp=31;
        *idum=1;
    }
    if (++inext == 56) inext=1;
    if (++inextp == 56) inextp=1;
    mj=ma[inext]-ma[inextp];
    if (mj < MZ) mj += MBIG;
    ma[inext]=mj;
    return mj*FAC;
}
#undef MBIG
#undef MSEED
#undef MZ
#undef FAC



int metrop(float de, float t)
{

    static long gljdum=1;

    return de < 0.0 || ran3(&gljdum) < exp(-de/t);
}




double ALEN(int x1, int x2, int y1, int y2)
{
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}



#define TFACTR 0.9
#define TFACTR 0.9


void anneal(SCity* cities,int* iorder,int ncity, bool opcja, bool zapis,std::string outFile)
{

    int ans,nover,nlimit;
    int i,j,k,nsucc,nn,idec;
    static int n[7];
    long *idum=new long;
    unsigned long *iseed=new unsigned long;
    double path,de,t;


    nover=100*ncity;
    nlimit=10*ncity;
    path=0.0;
    t=0.5;
    std::ofstream dataFile;
    if (opcja&&zapis)
    {

        dataFile.open(outFile.c_str());
    }
    if(ncity>3)
    {
        for (i=1; i<ncity; i++)
        {

            path += ALEN(cities[i].x,cities[i+1].x,cities[i].y,cities[i+1].y);
        }

        path += ALEN(cities[ncity].x,cities[1].x,cities[ncity].y,cities[1].y);


        *idum = -1;
        *iseed=111;
        for (j=0; j<100; j++)
        {
            nsucc=0;
            for (k=0; k<nover; k++)
            {
                do
                {
                    n[1]=1+(int) (ncity*ran3(idum));
                    n[2]=1+(int) ((ncity-1)*ran3(idum));
                    if (n[2] >= n[1]) ++n[2];
                    nn=1+((n[1]-n[2]+ncity-1) % ncity);
                }
                while (nn<3);
                idec=irbit1(iseed);
                if (idec == 0)
                {
                    n[3]=n[2]+(int) (abs(nn-2)*ran3(idum))+1;
                    n[3]=1+((n[3]-1) % ncity);
                    de=trncst(cities,iorder,n,ncity);
                    ans=metrop(de,t);
                    if (ans)
                    {
                        ++nsucc;
                        path += de;
                        trnspt(iorder,ncity,n);
                    }
                }
                else
                {
                    de=revcst(cities, iorder,n,ncity);
                    ans=metrop(de,t);
                    if (ans)
                    {
                        ++nsucc;
                        path += de;
                        reverse(ncity,iorder,n);
                    }
                }
                if (nsucc >= nlimit) break;
            }

            if (opcja)
            {
                std::cout<<"Kolejno odwiedzane miasta to: "<<std::endl;
                for(int i=1; i<=ncity; i++)
                    std::cout<<i<<". "<<cities[iorder[i]].nazwa<<std::endl;
                std::cout<<         //"T =",t,
                         "Długość trasy = "<<path<<std::endl;
                std::cout<<"Ilość zmian zakończonych sukcesem: "<<nsucc<<std::endl;
                std::cout<<"-------------------------------------------------------------------------"<<std::endl;
            }

            if (opcja&&zapis)
            {
                dataFile<<"Kolejno odwiedzane miasta to: "<<std::endl;
                for(int i=1; i<=ncity; i++)
                    dataFile<<i<<". "<<cities[iorder[i]].nazwa<<std::endl;
                dataFile<<         //"T =",t,
                "Długość trasy = "<<path<<std::endl;
                dataFile<<"Ilość zmian zakończonych sukcesem: "<<nsucc<<std::endl;
                dataFile<<"-------------------------------------------------------------------------"<<std::endl;
            }


            t *= TFACTR;
            if (nsucc == 0) return;
        }
    }

    else
    {

        if(ncity==1)
            std::cout<<"Podałeś tylko jedno miasto, nie ma co liczyć.";
        else
        {
            if(ncity==2)
            {
                std::cout<<"Kolejno odwiedzane miasta to: "<<std::endl;
                for(int i=1; i<=ncity; i++)
                {
                    std::cout<<i<<". "<<cities[iorder[i]].nazwa<<std::endl;
                }
                std::cout<<"Długość trasy ="<<2*ALEN(cities[1].x,cities[2].x,cities[1].y,cities[2].y)<<std::endl;
                if (opcja&&zapis)
                {
                    dataFile<<"Kolejno odwiedzane miasta to: "<<std::endl;
                    for(int i=1; i<=ncity; i++)
                        dataFile<<i<<". "<<cities[iorder[i]].nazwa<<std::endl;
                    dataFile<<"Długość trasy ="<<2*ALEN(cities[1].x,cities[2].x,cities[1].y,cities[2].y)<<std::endl;
                }
            }
            else
            {
                std::cout<<"Kolejno odwiedzane miasta to: "<<std::endl;
                for(int i=1; i<=ncity; i++)
                {
                    std::cout<<i<<". "<<cities[iorder[i]].nazwa<<std::endl;
                }
                if (opcja&&zapis)
                {
                    dataFile<<"Kolejno odwiedzane miasta to: "<<std::endl;
                    for(int i=1; i<=ncity; i++)
                        dataFile<<i<<". "<<cities[iorder[i]].nazwa<<std::endl;
                    dataFile<<"Długość trasy ="<<ALEN(cities[1].x,cities[2].x,cities[1].y,cities[2].y)+ALEN(cities[2].x,cities[3].x,cities[2].y,cities[3].y)+ALEN(cities[1].x,cities[3].x,cities[1].y,cities[3].y)<<std::endl;      //"T =",t,}
                }
                std::cout<<"Długość trasy ="<<ALEN(cities[1].x,cities[2].x,cities[1].y,cities[2].y)+ALEN(cities[2].x,cities[3].x,cities[2].y,cities[3].y)+ALEN(cities[1].x,cities[3].x,cities[1].y,cities[3].y);
            }
        }


    };

    if (opcja&&zapis)
    {
        dataFile.close();
    }
    delete idum;
    delete iseed;

}
#undef TFACTR




float revcst(SCity* cities, int* iorder, int* n, int ncity)
{
    float xx[5],yy[5],de;
    int j,ii;

    n[3]=1 + ((n[1]+ncity-2) % ncity);
    n[4]=1 + (n[2] % ncity);
    for (j=1; j<=4; j++)
    {
        ii=iorder[n[j]];
        xx[j]=cities[ii].x;
        yy[j]=cities[ii].y;
    }
    de = -ALEN(xx[1],xx[3],yy[1],yy[3]);
    de -= ALEN(xx[2],xx[4],yy[2],yy[4]);
    de += ALEN(xx[1],xx[4],yy[1],yy[4]);
    de += ALEN(xx[2],xx[3],yy[2],yy[3]);
    return de;
}


void reverse(int ncity,int* iorder,  int* n)
{
    int nn,j,k,l,itmp;

    nn=(1+((n[2]-n[1]+ncity) % ncity))/2;
    for (j=1; j<=nn; j++)
    {
        k=1 + ((n[1]+j-2) % ncity);
        l=1 + ((n[2]-j+ncity) % ncity);
        itmp=iorder[k];
        iorder[k]=iorder[l];
        iorder[l]=itmp;
    }
}






float trncst(SCity* cities,int* iorder, int* n,int ncity)
{
    float xx[7],yy[7],de;
    int j,ii;

    n[4]=1 + (n[3] % ncity);
    n[5]=1 + ((n[1]+ncity-2) % ncity);
    n[6]=1 + (n[2] % ncity);
    for (j=1; j<=6; j++)
    {
        ii=iorder[n[j]];
        xx[j]=cities[ii].x;
        yy[j]=cities[ii].y;
    }
    de = -ALEN(xx[2],xx[6],yy[2],yy[6]);
    de -= ALEN(xx[1],xx[5],yy[1],yy[5]);
    de -= ALEN(xx[3],xx[4],yy[3],yy[4]);
    de += ALEN(xx[1],xx[3],yy[1],yy[3]);
    de += ALEN(xx[2],xx[4],yy[2],yy[4]);
    de += ALEN(xx[5],xx[6],yy[5],yy[6]);
    return de;
}












void trnspt(int* iorder, int ncity, int* n)
{
    int m1,m2,m3,nn,j,jj,*jorder;

    jorder=new int[ncity+1];
    m1=1 + ((n[2]-n[1]+ncity) % ncity);
    m2=1 + ((n[5]-n[4]+ncity) % ncity);
    m3=1 + ((n[3]-n[6]+ncity) % ncity);
    nn=1;
    for (j=1; j<=m1; j++)
    {
        jj=1 + ((j+n[1]-2) % ncity);
        jorder[nn++]=iorder[jj];
    }
    if (m2>0)
    {
        for (j=1; j<=m2; j++)
        {
            jj=1+((j+n[4]-2) % ncity);
            jorder[nn++]=iorder[jj];
        }
    }
    if (m3>0)
    {
        for (j=1; j<=m3; j++)
        {
            jj=1 + ((j+n[6]-2) % ncity);
            jorder[nn++]=iorder[jj];
        }
    }
    for (j=1; j<=ncity; j++)
        iorder[j]=jorder[j];
    delete []jorder;
}
