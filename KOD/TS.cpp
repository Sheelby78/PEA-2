#include "TS.h"
#include "Timer.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <ctime>

using namespace std;

//konstruktor
TS::TS() {
	t = 0.0;
	critical_events = 0;
	tabuTime = 10;
	length = 0;
	best_length = 0;
}

//oblicza dlugosc danej sciezki
int TS::path_distance(const vector<int>& path, int** Matrix) {

	int dist = 0;
	for (int i = 0; i < path.size() - 1; i++) {
		dist += Matrix[path[i]][path[i + 1]];
	}
	return dist;
}

//dekrementacja ruchow tabu
void TS::updateTabuList() {

	for (int i = 0; i < tab.size(); i++) {
		tab[i].time--;
		if (tab[i].time == 0) {
			tab.erase(tab.begin() + i);
		}
	}
}


// glowna funkcja wykonujaca algorytm 
int TS::TSP(double max_iterations, int** Matrix, int mainSize, bool dywer, bool neighborType) {

	Timer test = *(new Timer());
	size = mainSize;
	vector<int> path;
	vector<int> best_path;


	for (int i = 0; i < size; i++) {
		path.push_back(i);
	}

	path.push_back(0);
	for (int i = 0; i < size; i++) randomSwap(path);

	best_path = path;
	best_length = path_distance(best_path, Matrix);

	test.start();
	while ((t / 1000000) < max_iterations) {

		if (neighborType) {
			path = findBestNeighbor(path, Matrix);
		}
		else {
			path = findBestNeighbor2(path, Matrix);
		}

		length = path_distance(path, Matrix);

		if (length < best_length) {
			best_path = path;
			best_length = length;
			critical_events = 0;
		}
		else {
			critical_events++;
			insert(bestChange[0], bestChange[1]);
		}

		if (dywer) {
			if (critical_events >= 10) {
				for (int i = 0; i < size; i++) {
					randomSwap(path);
				}
				length = path_distance(path, Matrix);
				critical_events = 0;
				tab.clear();
			}
		}

		updateTabuList();
		test.stop();
		t = test.timeCount();
	}
	return best_length;
}

//znajdowanie najlepszego sasiada metoda SWAP
vector<int> TS::findBestNeighbor(vector<int> temp, int** Matrix) {

	for (int i = 1; i < size - 2; i++) {
		for (int j = i + 1; j < size - 1; j++) {
			vector<int> temp2(temp);
			swap(temp2[i], temp2[j]);

			if ((!contains(i, j) && path_distance(temp2, Matrix) < path_distance(temp, Matrix)) || path_distance(temp2, Matrix) < (path_distance(temp, Matrix))) {
				temp = temp2;
				bestChange[0] = i;
				bestChange[1] = j;
			}
		}
	}
	return temp;
}

//znajdowanie najlepszego sasiada metoda INVERT
vector<int> TS::findBestNeighbor2(vector<int> temp, int** Matrix) {

	for (int i = 1; i < size - 2; i++) {
		for (int j = size - 1; j > i; j--) {
			vector<int> temp2(temp);

			if (i < j) {
				for (int z = i, x = j; z < x; z++, x--) {
					swap(temp[z], temp[x]);
				}
			}

			if ((!contains(i, j) && path_distance(temp2, Matrix) < path_distance(temp, Matrix)) || path_distance(temp2, Matrix) < (path_distance(temp, Matrix))) {
				temp = temp2;
				bestChange[0] = i;
				bestChange[1] = j;
			}
		}
	}

	return temp;
}

//sprawdzanie czy tabu zawiera podane elementy
bool TS::contains(int x, int y) {
	for (int i = 0; i < tab.size(); i++) {
		if (x == tab[i].x && y == tab[i].y || y == tab[i].x && x == tab[i].y) {
			return true;
		}
	}
	return false;
}

//dodawanie elemntu do tabu
void TS::insert(int x, int y) {
	if (contains(x, y)) {

	}
	else {
		tabu k;
		k.x = x;
		k.y = y;
		k.time = tabuTime;
		tab.push_back(k);
	}
}

// zamiana miejscami 2 losowych elementow danej sciezki
void TS::randomSwap(vector<int>& temp) {

	int randomCity = rand() % (size - 1) + 1;
	int randomCity2 = rand() % (size - 1) + 1;
	while (randomCity == randomCity2) randomCity2 = rand() % (size - 1) + 1;
	swap(temp[randomCity], temp[randomCity2]);
}