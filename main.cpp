#include <iostream>
#include <Matrix.h>
#include <Neural_Network.h>

using namespace std;

int main()
{
    Neural_Network NN;
    Matrix M;
    //sample input data
    vector< vector<double> > X = {{3, 5}, {5, 1}, {10, 2}};
    vector< vector<double> > y = {{75}, {82}, {93}};
    X = NN.normalize(X, 24);
    y = NN.normalize(y, 100);
    cout << "Estimates with no training: ";
    M.printmat(NN.propagate(X));
    cout << "Cost with no training: " << NN.cost(X, y) << endl << endl;
    for(int i=0; i<40000; ++i){
        NN.train(X, y);
    }
    cout << "Estimates with training: ";
    M.printmat(NN.propagate(X));
    cout << "Cost with training: " << NN.cost(X, y) << endl << endl;
    return 0;
}
