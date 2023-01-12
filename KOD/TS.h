#include <iostream>
#include <vector>

using namespace std;

class TS{
    struct tabu{
        int x;
        int y;
        int time;
    };

    private:
	    int size, critical_events, length, best_length, tabuTime;
        int bestChange[2];
        vector<tabu> tab;
        double t;

    public:
        TS();
        bool contains(int x, int y);
        void insert(int x, int y);
        int path_distance(const vector<int>& path, int** Matrix);
        vector<int> findBestNeighbor(vector<int> order, int** Matrix);
        vector<int> findBestNeighbor2(vector<int> order, int** Matrix);
        void updateTabuList();
        void randomSwap(vector<int> &order);
        int TSP( double max_iterations, int** mainMatrix, int mainSize, bool dywer, bool neighborType);
};