#include <iostream>
#include <chrono>
#include <thread>
#include "AdjacencyMatrix.h"
#include "SA.h"
#include "TS.h"
#include "Timer.h"

using namespace std;

void AlgorithmMenu(AdjacencyMatrix mat);

//Głowne menu programu
int main(int, char**) {

    AdjacencyMatrix mat = *(new AdjacencyMatrix());
    srand(time(NULL));
    bool koniec = false;
    char wybor;

    system("cls");

    while (!koniec) {

        system("cls");
        cout << " ============MENU============ " << endl;
        cout << "-----------------------------" << endl;
        cout << "-----------------------------" << endl;
        cout << "1.  Wczytaj dane z pliku" << endl;
        cout << "2.  Automatyczne generowanie grafu" << endl;
        cout << "x.  Zamkniecie programu " << endl;
        cout << "-----------------------------" << endl;
        cout << "-----------------------------" << endl;
        cout << "Wybor: ";
        cin >> wybor;

        switch (wybor) {
        case '1': {
            cout << "Podaj nazwe pliku do wczytania danych: ";
            string name;
            cin >> name;
            if (!mat.readMatrix(name)) {
                cout << endl << "Blad odczytu pliku" << endl;
            }
            else {
                cout << endl << "Pomyslnie wczytano plik" << endl;
                system("cls");
                AlgorithmMenu(mat);
            }

            break;
        }
        case '2': {
            cout << "Podaj liczbe wierzcholkow: ";
            int N;
            cin >> N;
            mat.generateMatrix(N);
            cout << endl << "Pomyslnie wygenerowano graf" << endl;
            system("cls");
            AlgorithmMenu(mat);
            break;
        }
        case 'x':;	koniec = true; break;
        default: {
            cout << endl << "POMYLKA!" << endl;
            break;
        }
        }
    }
}

//Menu wyboru algorytmu i ustawiania roznych zmiennych 
void AlgorithmMenu(AdjacencyMatrix mat) {
    Timer test = *(new Timer());
    bool koniec = false;
    char wybor;

    while (!koniec) {
        cout << " ============MENU============ " << endl;
        cout << "-----------------------------" << endl;
        cout << "-----------------------------" << endl;
        cout << "Ustawiony czas wykonywania algorytmow: " << mat.getTime() << " Sekund" << endl;
        cout << "Definicja sasiedztwa: "; mat.choice2();
        cout << "Dywersyfikacja dla Tabu Search (TS) jest: "; mat.choice();
        cout << "-----------------------------" << endl;
        cout << "-----------------------------" << endl;
        cout << "1.  Tabu Search (TS)" << endl;
        cout << "2.  Symulowane wyzarzanie (SA)" << endl;
        cout << "3.  Wyswietl graf" << endl;
        cout << "4.  Ustaw czas wykonywania" << endl;
        cout << "5.  Wlacz / Wylacz dywersyfikacje w Tabu Serach (TS)" << endl;
        cout << "6.  Wybierz definicje sasiedztwa" << endl;
        cout << "x.  Powrot" << endl;
        cout << "-----------------------------" << endl;
        cout << "-----------------------------" << endl;
        cout << "Wybor: ";
        cin >> wybor;


        switch (wybor) {
        case '1': {
            system("cls");
            TS ts = *(new TS());
            cout << "TABU SEARCH (TS)" << endl << endl;
            test.start();
            cout << "=====> " << ts.TSP(mat.getTime(), mat.getMatrix(), mat.getSize(), mat.getDywer(), mat.getNeighborType()) << " <=====" << endl;
            test.stop();
            cout << endl;
            cout << test.timeCount() / 1000000 << " Seconds";
            cout << endl << endl;
            break;
        }
        case '2': {
            system("cls");
            SA sa = *(new SA());
            cout << "SYMULOWANE WYZARZANIE (SA)" << endl << endl;
            test.start();
            cout << "=====> " << sa.TSP(mat.getTime(), mat.getMatrix(), mat.getSize(), mat.getNeighborType()) << " <=====" << endl;
            test.stop();
            cout << endl;
            cout << test.timeCount() / 1000000 << " Seconds";
            cout << endl << endl;
            break;
        }
        case '3': {
            system("cls");
            mat.show();
            cout << endl << endl;
            break;
        }
        case '4': {
            system("cls");
            cout << "Podaj czas wykonywania algorytmu w sekundach: ";
            double n;
            cin >> n;
            mat.setTime(n);
            system("cls");
            break;
        }
        case '5': {
            system("cls");
            if (mat.getDywer()) {
                cout << "Dywersywikacja dla Tabu Search zostala wylaczona";
                mat.setDywer(false);
            }
            else {
                cout << "Dywersywikacja dla Tabu Search zostala wlaczona";
                mat.setDywer(true);
            }
            cout << endl << endl;
            break;
        }
        case '6': {
            system("cls");
            char wybor2;
            cout << "Wybierz typ sasiedztwa: " << endl;
            cout << "1.  SWAP" << endl;
            cout << "2.  INVERT" << endl;
            cout << "Wybor: ";
            cin >> wybor2;

            if (wybor2 == '1') {
                system("cls");
                cout << "Wybrano typ sasiedztwa: SWAP";
                mat.setNeighBorType(true);
            }
            else if (wybor2 == '2') {
                system("cls");
                cout << "Wybrano typ sasiedztwa: INVERT";
                mat.setNeighBorType(false);
            }
            else {
                system("cls");
                cout << "POMYLKA!";
            }
            cout << endl << endl;
            break;
        }
        case 'x':;	koniec = true; break;
        default: {
            cout << endl << "POMYLKA!" << endl;
            break;
        }
        }
    }
}
