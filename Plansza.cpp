#include <Plansza.h>
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
    plansza[yPos][xPos].jestLufa = false;
    plansza[yPos][xPos-1].jestLufa = true;
    plansza[yPos+1][xPos+1].jestLufa = false;
    plansza[yPos+1][xPos-2].jestLufa = true;
}

void Plansza::ruchP()
{
    int xPos = SprawdzXPosLufy();
    int yPos = SprawdzYPosLufy();
    plansza[yPos][xPos].jestLufa = false;
    plansza[yPos][xPos+1].jestLufa = true;
    plansza[yPos+1][xPos-1].jestLufa = false;
    plansza[yPos+1][xPos+2].jestLufa = true;
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
}


