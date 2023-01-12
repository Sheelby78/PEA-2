#include <iostream>
#include <vector>

using namespace std;

class SA{

    private:
	    int size, length2, length1, solution;
        double t_min, t_cool, t_curr, t;

    public:
        SA();
        int path_distance(const vector<int>& path, int** Matrix);
        void randomSwap(vector<int> &order);
        void randomInvert(vector<int> &temp);
        bool probability(int length, int length1, double temperature);
        int TSP( double max_iterations, int** mainMatrix, int mainSize, bool neighborType);
};