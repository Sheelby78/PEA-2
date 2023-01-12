#include "SA.h"
#include "Timer.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <limits.h>

#define M_E        2.71828182845904523536

using namespace std;

//konstruktor
SA::SA(){
	t = 0.0;
	t_min = 0;
	t_cool = 0.999999;
	length1 = 0;
	length2 = 0;
}

//obliczanie dlugosci danej sciezki
int SA::path_distance(const vector<int>& path2, int** Matrix) {
  int dist = 0;
  for (int i = 0; i < path2.size() - 1; i++) {
    dist += Matrix[path2[i]][path2[i+1]];
  }
  return dist;
}

//glowna funkcja wykonujaca algorytm 
int SA::TSP(double max_iterations, int** Matrix, int mainSize, bool neighborType) {

	Timer test = *(new Timer());
	vector<int> path1;
	vector<int> path2;
	size = mainSize;


	for(int i = 0; i < size; i++){
		path1.push_back(i);
		
	}

	path1.push_back(0);
	for (int i = 0; i < 100; i++) randomSwap(path1);
	length1 = path_distance(path1, Matrix);
	solution = length1;


		double delta, delta_max = 0;

		for (int i = 0; i < size; i++){

			vector<int> permut1 (path1);
			vector<int> permut2 (path1);

			for (int j = 0; j < size; j++){
				randomSwap(permut1);
				randomSwap(permut2);
			}
			delta = abs(path_distance(permut1, Matrix) - path_distance(permut2, Matrix));

			if (delta > delta_max){
				delta_max = delta;
			}
		}

		t_curr = delta_max;
		
		test.start();
		while (t_curr > t_min && (t/1000000)<max_iterations) {

			path2 = path1;
			
			if(neighborType){
				randomSwap(path2);
			} else {
				randomInvert(path2);
			}

			length2 = path_distance(path2, Matrix);

			if (length2 < length1 || probability(length1, length2, t_curr)){
				length1 = length2;
				path1 = path2;

				if(solution > length1){
					solution = length1;
				}
			} 

			t_curr *= t_cool;

			test.stop();
			t = test.timeCount();
		}

	return solution;
}

//zamienia 2 losowe elemty w danej scieze 
void SA::randomSwap(vector<int> &temp){

	int randomCity = rand() % (size- 1) + 1;
	int randomCity2 = rand() % (size - 1) + 1;
	while (randomCity == randomCity2) randomCity2 = rand() % (size - 1) + 1;
	swap(temp[randomCity], temp[randomCity2]);
}

//zamienia kolejnosc elementow w losowym przedziale danej sciezki
void SA::randomInvert(vector<int> &temp){

	int randomCity = rand() % (size- 1) + 1;
	int randomCity2 = rand() % (size - 1) + 1;
	while (randomCity == randomCity2) randomCity2 = rand() % (size - 1) + 1;

	if(randomCity < randomCity2){
		while (randomCity < randomCity2){
			swap(temp[randomCity], temp[randomCity2]);
			randomCity++;
			randomCity2--;
		}
	} else {
		while (randomCity2 < randomCity){
			swap(temp[randomCity2], temp[randomCity]);
			randomCity2++;
			randomCity--;
		}
	}
}

//sprawdza prawdopodobiestwo z losowa wartoscia
bool SA::probability(int value1, int value2, double temperature) {

	double p = pow(M_E, ((-1 * ((long long)value2 - (long long)value1)) / temperature));
	double r = (double)rand() / RAND_MAX;
	return (r < p);
}