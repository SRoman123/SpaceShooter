#include <iostream>
#include <Plansza.h>

using namespace std;

int main()
{
    Plansza p(10,10,EASY);
    p.wyswietl();
    p.ustawRakiete();
    p.cyklRakiet(p.SprawdzYPosLufy());
    p.wyswietl();
    p.cyklRakiet(p.SprawdzYPosLufy()-1);
    p.wyswietl();
}
