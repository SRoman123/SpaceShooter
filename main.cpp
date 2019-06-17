#include <iostream>
#include <Plansza.h>
#include <time.h>
#include <cstdlib>

using namespace std;

int main()
{
    srand(time(nullptr));
    Plansza p(10,10,EASY);
    p.wyswietl();
    p.cyklRakiet(p.SprawdzYPosLufy());
    p.wyswietl();
    p.cyklRakiet(p.SprawdzYPosLufy()-1);
    p.cyklRakiet(p.SprawdzYPosLufy());
    p.wyswietl();
}
