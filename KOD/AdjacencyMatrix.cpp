#include "AdjacencyMatrix.h"
#include <fstream>

//konstruktor
AdjacencyMatrix::AdjacencyMatrix(){
    dywer = true;
    time = 5;
    size = 0;
    neighborType = true;
}

//destruktor
AdjacencyMatrix::~AdjacencyMatrix(){
    for (int i = 0; i < size; i++){
        delete[] Matrix[i];
    }
    delete[] Matrix;
    size = 0;
}

//wczytywanie danych z pliku tesktowego
bool AdjacencyMatrix::readMatrix(string name){

    string name3 = ".txt";
	ifstream read(name + name3);

	if (!read.good()){
		return false;
	}

	read >> size;
    Matrix = new int *[size];

	for (int i = 0; i < size; i++){
		Matrix[i] = new int[size];
	}

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
            read >> Matrix[i][j];
        }
	}
    
    read.close();
    return true;
}

//zwracanie wielkosci macierzy
int AdjacencyMatrix::getSize(){

    return size;
}

//zwracanie macierzy
int** AdjacencyMatrix::getMatrix(){

    return Matrix;
}

//zwracanie czy dywersyfikacja jest wlaczona
bool AdjacencyMatrix::getDywer(){
    return dywer;
}

//ustawianie dywersyfikacji
void AdjacencyMatrix::setDywer(bool temp){
    this->dywer = temp;
}

//zwracanie typu sasiedztwa
bool AdjacencyMatrix::getNeighborType(){
    return neighborType;
}

//ustawianie typu sasiedztwa
void AdjacencyMatrix::setNeighBorType(bool temp){
    this->neighborType = temp;
}

//zwracanie ustwionego czasu wykonywania algorymu
double AdjacencyMatrix::getTime(){
    return time;
}

//ustawianie czasu wykonywania algorytmu
void AdjacencyMatrix::setTime(double time){
    this->time = time;
}

// wyswietlanie stany dywersyfikacji
void AdjacencyMatrix::choice(){
    if(dywer){
        cout << "WLACZONA" << endl;
    } else {
        cout << "WYLACZONA" << endl;
    }
}

//wyswietlanie aktualnego typu sasiedztwa
void AdjacencyMatrix::choice2(){
    if(neighborType){
        cout << "SWAP" << endl;
    } else {
        cout << "INVERT" << endl;
    }
}

//wyswietlanie zawartosci macierzy
void AdjacencyMatrix::show(){
    cout<<endl;
    for(int i=0;i<size;i++){
        cout<<"{";
        for(int j=0;j<size;j++){
            if(j==size-1){
                cout<<Matrix[i][j];
                continue;
            }
            cout<<Matrix[i][j]<<", ";
        }
        cout<<"}"<<endl;
    }
}

//automatyczne generowanie macierzy
void AdjacencyMatrix::generateMatrix(int mainSize){

    size = mainSize;
    Matrix = new int *[size];

	for (int i = 0; i < size; i++){
		Matrix[i] = new int[size];

        for(int j=0; j<size; j++){
            if(j==i){
                Matrix[i][j]=0;
                continue;
            }
            Matrix[i][j] = 1 + (rand() % (100));
        }
    }
}
