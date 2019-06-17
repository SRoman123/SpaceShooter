#include "Plansza.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>

Plansza::Plansza(int szeroksc, int wysokosc, GameMode gameMode)
{
    this->szerokosc=szeroksc;
    this->wysokosc=wysokosc;
    this->gameMode=gameMode;
    gameState=RUNNING;
    kier=LEWO;
    for(int i = 0; i<wysokosc; ++i)
    {
        for(int j = 0; j<szerokosc; ++j)
        {
            plansza[i][j].jestObcy = false;
            plansza[i][j].jestRakieta = false;
            plansza[i][j].jestStatek = false;
        }
    }
    plansza[wysokosc-1][szeroksc/2].jestStatek = true;
    plansza[wysokosc-1][(szeroksc/2)-1].jestStatek = true;
    plansza[wysokosc-1][(szeroksc/2)+1].jestStatek = true;
    plansza[wysokosc-2][szeroksc/2].jestLufa = true;
    ustawObcych();
}

int Plansza::getWysokosc()
{
    return wysokosc;
}

int Plansza::getSzerokosc()
{
    return szerokosc;
}

GameMode Plansza::getGameMode()
{
    return gameMode;
}

GameState Plansza::getGameState()
{
    return gameState;
}

Kierunek Plansza::getKierunek()
{
    return kier;
}

bool Plansza::sprawdzZakres(int x, int y)
{
    if(x < 0 || x > (szerokosc-1) || y < 0 || y > (wysokosc-1))
        return false;
    return true;
}

Kierunek Plansza::zmienKier(Kierunek k)
{
    switch(k)
    {
    case LEWO:
        kier = LEWO;
        break;
    case PRAWO:
        kier = PRAWO;
        break;
    }
    return kier;
}

int Plansza::SprawdzXPosLufy()
{
    int x;
    for(int i = 0; i<szerokosc; ++i)
    {
        if(plansza[wysokosc-2][i].jestLufa)
        {
            x=i;
            break;
        }
    }
    return x;
}

int Plansza::SprawdzYPosLufy()
{
    return wysokosc-2;
}



void Plansza::ruchL()
{
    int xPos = SprawdzXPosLufy();
    int yPos = SprawdzYPosLufy();
    if(!sprawdzZakres(xPos-1,yPos))
        return;
    plansza[yPos][xPos].jestLufa = false;
    plansza[yPos][xPos-1].jestLufa = true;
    plansza[yPos+1][xPos+1].jestStatek = false;
    plansza[yPos+1][xPos-2].jestStatek = true;
}

void Plansza::ruchP()
{
    int xPos = SprawdzXPosLufy();
    int yPos = SprawdzYPosLufy();
    if(!sprawdzZakres(xPos+1,yPos))
        return;
    plansza[yPos][xPos].jestLufa = false;
    plansza[yPos][xPos+1].jestLufa = true;
    plansza[yPos+1][xPos-1].jestStatek = false;
    plansza[yPos+1][xPos+2].jestStatek = true;
}

void Plansza::ustawRakiete()
{
    int yPos=SprawdzYPosLufy();
    int xPos=SprawdzXPosLufy();
    if(xPos < 0 || xPos >= szerokosc || yPos < 0 || yPos >= wysokosc)
        return;
    plansza[yPos][xPos].jestRakieta = true;
}

int Plansza::znajdzRakiet(int y)
{
    int x = -1;
    for(int i = 0; i < szerokosc; ++i)
    {
        if(plansza[y][i].jestRakieta)
        {
            x = i;
            break;
        }
    }
    return x;
}

void Plansza::przesunRakiet(int y)
{
    if(y < 0 || y >= wysokosc)
        return;
    int x = znajdzRakiet(y);
    if(x < 0 || x >= szerokosc)
        return;
    if(y == 0)
        return;
    plansza[y-1][x].jestRakieta = true;
}

void Plansza::usunRakiet(int y)
{
    if(y < 0 || y >= wysokosc)
        return;
    int x = znajdzRakiet(y);
    if(x < 0 || x >= szerokosc)
        return;
    plansza[y][x].jestRakieta = false;
}
void Plansza::cyklRakiet(int y)
{
    if(y == SprawdzYPosLufy())
        ustawRakiete();
    przesunRakiet(y);
    usunRakiet(y);
}

void Plansza::ustawObcych()
{
    int n;
    int x;
    if(gameMode == EASY)
    {
        n = 2*szerokosc/5;
        for(int i = 0; i < n; ++i)
        {
            x = rand() % szerokosc;
            plansza[0][x].jestObcy = true;
        }
    }
    if(gameMode == NORMAL)
    {
        n = 3*szerokosc/5;
        for(int i = 0; i < n; ++i)
        {
            x = rand() % szerokosc;
            plansza[0][x].jestObcy = true;
        }
    }
    if(gameMode == HARD)
    {
        n = 4*szerokosc/5;
        for(int i = 0; i < n; ++i)
        {
            x = rand() % szerokosc;
            plansza[0][x].jestObcy = true;
        }
    }
    if(gameMode == DEBUG)
    {
        //n = 2*5/szerokosc;
//        for(int i = 0; i < n; ++i)
//        {
//            x = rand() % szerokosc;
//            plansza[0][x].jestObcy = true;
//        }
        plansza[0][1].jestObcy = true;
        plansza[0][5].jestObcy = true;
        plansza[0][9].jestObcy = true;
    }
}

void Plansza::przesunObcych(int y)
{
    if(y >= wysokosc || y < 0)
        return;
    if(y == wysokosc -1)
    {
        gameState = FINISHED_LOSS;
        return;
    }
    for(int i = 0; i < szerokosc; ++i)
    {
        if(plansza[y][i].jestObcy)
            plansza[y+1][i].jestObcy = true;
    }
}

void Plansza::usunObcych(int y)
{
    if(y >= wysokosc || y < 0)
        return;
    for(int i = 0; i < szerokosc; ++i)
    {
        if(plansza[y][i].jestObcy)
            plansza[y][i].jestObcy = false;
    }
}

void Plansza::cyklObcych(int y)
{
    //ustawObcych();
    przesunObcych(y);
    usunObcych(y);
    if(y == 0)
        ustawObcych();
}

void Plansza::zrobZderzenie(int y, int x)
{
    if(x < 0 || x >= szerokosc || y < 0 || y >= wysokosc)
        return;
    plansza[y][x].jestObcy = false;
    plansza[y][x].jestRakieta = false;
}

void Plansza::zderzenie(int y)
{
    int x = znajdzRakiet(y);
    if(x < 0 || x >= szerokosc || y < 0 || y >= wysokosc)
        return;
    if(plansza[y][x].jestObcy && plansza[y][x].jestRakieta)
        zrobZderzenie(y,x);
}

int Plansza::zliczObcych()
{
    int liczbaObcyh = 0;
    for(int i = 0; i < wysokosc; ++i)
    {
        for(int j = 0; j < szerokosc; ++j)
        {
            if(plansza[i][j].jestObcy)
                liczbaObcyh++;
        }
    }
    return liczbaObcyh;
}

void Plansza::wyswietl()
{
    for(int i = 0; i<wysokosc; ++i)
    {
        std::cout<<std::endl;
        for(int j = 0; j<szerokosc; ++j)
        {
            std::cout<<'[';
            if(!plansza[i][j].jestObcy && !plansza[i][j].jestRakieta && !plansza[i][j].jestStatek && !plansza[i][j].jestLufa)
                std::cout<<'.';
            if(plansza[i][j].jestObcy)
                std::cout<<'O';
            if(plansza[i][j].jestRakieta)
                std::cout<<'^';
            if(plansza[i][j].jestStatek)
                std::cout<<'S';
            if(plansza[i][j].jestLufa)
                std::cout<<'L';
            std::cout<<']';
        }
        //std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
