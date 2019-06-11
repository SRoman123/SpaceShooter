#ifndef PLANSZA_H
#define PLANSZA_H

enum GameMode  { DEBUG, EASY, NORMAL, HARD };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };

enum Kierunek { LEWO, PRAWO };

struct Pole
{
    bool jestObcy;
    bool jestRakieta;
    bool jestStatek;
    bool jestLufa;
};

class Plansza
{
    Pole plansza[100][100];
    int wysokosc;
    int szerokosc;
    GameMode gameMode;
    GameState gameState;
    Kierunek kier;
    public:
        Plansza(int szeroksc, int wysokosc, GameMode gameMode);
        int getWysokosc();
        int getSzerokosc();
        GameMode getGameMode();
        GameState getGameState();
        Kierunek getKierunek();
        int SprawdzXPosLufy();
        int SprawdzYPosLufy();
        bool sprawdzZakres(int x, int y);
        Kierunek zmienKier(Kierunek k);
        void ruchL();
        void ruchP();

        void wyswietl();

};

#endif // PLANSZA_H
