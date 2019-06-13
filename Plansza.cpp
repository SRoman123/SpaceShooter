#include "Plansza.h"
#include <iostream>

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
    plansza[yPos][xPos].jestRakieta = true;
}

void Plansza::strzelaj()
{
    int yPos=SprawdzYPosLufy();
    int xPos=SprawdzXPosLufy()+1;
    for(int i = SprawdzXPosLufy(); i>=0; --i)
    {
        plansza[yPos][i].jestRakieta = true;
        plansza[yPos][xPos].jestRakieta = false;
        xPos--;
    }
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
