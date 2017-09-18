#include "Neural_Network.h"

using namespace std;

Neural_Network::Neural_Network()
{
    //ctor
    vector<double> tempvec;
    for(unsigned int i=0; i<inputLayerSize; ++i){
        for(unsigned int j=0; j<hiddenLayerSize; ++j){
            tempvec.push_back((double) rand() / (RAND_MAX));
        }
        W1.push_back(tempvec);
        tempvec.clear();
    }
    for(unsigned int i=0; i<hiddenLayerSize; ++i){
        for(unsigned int j=0; j<outputLayerSize; ++j){
            tempvec.push_back((double) rand() / (RAND_MAX));
        }
        W2.push_back(tempvec);
        tempvec.clear();
    }
}

vector< vector<double> > Neural_Network::normalize(vector< vector<double> > mat)
{
    double m_value=0, temp;
    for(unsigned int i=0; i<mat.size(); ++i){
        temp = *max_element(mat.at(i).begin(), mat.at(i).end());
        if(temp > m_value){
            m_value = temp;
        }
    }
    for(unsigned int i=0; i<mat.size(); ++i){
        for(unsigned int j=0; j<mat.at(i).size(); ++j){
            mat.at(i).at(j) = mat.at(i).at(j) / m_value;
        }
    }
    return mat;
}

vector< vector<double> > Neural_Network::normalize(vector< vector<double> > mat, double m_value)
{
    for(unsigned int i=0; i<mat.size(); ++i){
        for(unsigned int j=0; j<mat.at(i).size(); ++j){
            mat.at(i).at(j) = mat.at(i).at(j) / m_value;
        }
    }
    return mat;
}

double Neural_Network::sigmoid(double z)
{
    return (double) 1/(1+exp(-z));
}

vector< vector<double> > Neural_Network::sigmoid(vector< vector<double> > mat)
{
    for(unsigned int i=0; i<mat.size(); ++i){
        for(unsigned int j=0; j<mat.at(i).size(); ++j){
            mat.at(i).at(j) = sigmoid(mat.at(i).at(j));
        }
    }
    return mat;
}

double Neural_Network::sigmoidPrime(double z)
{
    return (double) exp(-z)/pow(1+exp(-z), 2);
}

vector< vector<double> > Neural_Network::sigmoidPrime(vector< vector<double> > mat)
{
    for(unsigned int i=0; i<mat.size(); ++i){
        for(unsigned int j=0; j<mat.at(i).size(); ++j){
            mat.at(i).at(j) = sigmoidPrime(mat.at(i).at(j));
        }
    }
    return mat;
}

vector< vector<double> > Neural_Network::propagate(vector< vector<double> > inputs)
{
    a1 = inputs;
    z2 = M.mult(inputs, W1);
    a2 = sigmoid(z2);
    z3 = M.mult(a2, W2);
    std::vector< std::vector<double> > yhat = sigmoid(z3);
    return yhat;
}

double Neural_Network::cost(vector< vector<double> > X, vector< vector<double> > y)
{
    vector< vector<double> > yhat = propagate(X);
    double J = 0;
    for(unsigned int i=0; i<yhat.size(); ++i){
        for(unsigned int j=0; j<yhat.at(i).size(); ++j){
            try{
                J += 0.5*pow(yhat.at(i).at(j) - y.at(i).at(j), 2);
            }catch(int e){
                cerr << "Error in computing cost function!" << endl;
            }
        }
    }
    return J;
}

vector< vector<double> > Neural_Network::costPrimeW1(vector< vector<double> > X, vector< vector<double> > y)
{
    vector< vector<double> > yhat = propagate(X);
    vector< vector<double> > delta3 = M.scalar_mult(M.mult(-1, M.sub(y, yhat)), sigmoidPrime(z3));
    vector< vector<double> > dJdW1 = M.scalar_mult(M.mult(M.mult(M.transpose(X), delta3), M.transpose(W2)), sigmoidPrime(z2));
    return dJdW1;
}

vector< vector<double> > Neural_Network::costPrimeW2(vector< vector<double> > X, vector< vector<double> > y)
{
    vector< vector<double> > yhat = propagate(X);
    vector< vector<double> > delta3 = M.scalar_mult(M.mult(-1, M.sub(y, yhat)), sigmoidPrime(z3));
    vector< vector<double> > dJdW2 = M.mult(M.transpose(a2), delta3);
    return dJdW2;
}

vector< vector< vector<double> > > Neural_Network::costPrime(vector< vector<double> > X, vector< vector<double> > y)
{
    vector< vector<double> > yhat = propagate(X);
    vector< vector<double> > delta3 = M.scalar_mult(M.mult(-1, M.sub(y, yhat)), sigmoidPrime(z3));
    vector< vector<double> > dJdW1 = M.scalar_mult(M.mult(M.mult(M.transpose(X), delta3), M.transpose(W2)), sigmoidPrime(z2));
    vector< vector<double> > dJdW2 = M.mult(M.transpose(a2), delta3);
    vector< vector< vector<double> > > wrapper = {dJdW1, dJdW2};
    return wrapper;
}

std::vector< std::vector<double> > Neural_Network::numeric_costPrimeW1(vector< vector<double> > X, vector< vector<double> > y)
{
    std::vector< std::vector<double> > wrapper;
    std::vector<double> temp;
    double epsilon = 0.0000001;
    double cost0 = cost(X, y);
    for(unsigned int i=0; i<W1.size(); ++i){
        for(unsigned int j=0; j<W1.at(i).size(); ++j){
            W1.at(i).at(j) += epsilon;
            temp.push_back((cost(X, y) - cost0)/epsilon);
            W1.at(i).at(j) -= epsilon;
        }
        wrapper.push_back(temp);
        temp.clear();
    }
    return wrapper;
}

std::vector< std::vector<double> > Neural_Network::numeric_costPrimeW2(vector< vector<double> > X, vector< vector<double> > y)
{
    std::vector< std::vector<double> > wrapper;
    std::vector<double> temp;
    double epsilon = 0.0000001;
    double cost0 = cost(X, y);
    for(unsigned int i=0; i<W2.size(); ++i){
        for(unsigned int j=0; j<W2.at(i).size(); ++j){
            W2.at(i).at(j) += epsilon;
            temp.push_back((cost(X, y) - cost0)/epsilon);
            W2.at(i).at(j) -= epsilon;
        }
        wrapper.push_back(temp);
        temp.clear();
    }
    return wrapper;
}

void Neural_Network::change_W1(vector< vector<double> > dJdW1)
{
    W1 = M.sub(W1, M.mult(step_factor, dJdW1));
}

void Neural_Network::change_W2(vector< vector<double> > dJdW2)
{
    W2 = M.sub(W2, M.mult(step_factor, dJdW2));
}

void Neural_Network::set_step(double step)
{
    step_factor = step;
}

void Neural_Network::train(vector< vector<double> > X, vector< vector<double> > y)
{
    vector< vector< vector<double> > > wrapper = costPrime(X, y);
    change_W1(wrapper.at(0));
    change_W2(wrapper.at(1));
}

Neural_Network::~Neural_Network()
{
    //dtor
}
