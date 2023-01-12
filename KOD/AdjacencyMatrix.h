#include <iostream>

using namespace std;

class AdjacencyMatrix{
    private:
        int **Matrix;
        int size;
        double time;
        bool dywer, neighborType;

    public:
        AdjacencyMatrix();
        ~AdjacencyMatrix();
        int** getMatrix();
        void choice();
        void choice2();
        int getSize();
        void setTime(double time);
        bool readMatrix(string name);
        void show();
        double getTime();
        void setDywer(bool temp);
        bool getDywer();
        void setNeighBorType(bool temp);
        bool getNeighborType();
        void generateMatrix(int mainSize);

};