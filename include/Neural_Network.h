#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H
#include <random>
#include <algorithm>
#include <Matrix.h>


class Neural_Network
{
    public:
        Neural_Network();
        virtual ~Neural_Network();
        std::vector< std::vector<double> > normalize(std::vector< std::vector<double> >);
        std::vector< std::vector<double> > normalize(std::vector< std::vector<double> >, double);
        double sigmoid(double);
        std::vector< std::vector<double> > sigmoid(std::vector< std::vector<double> >);
        double sigmoidPrime(double);
        std::vector< std::vector<double> > sigmoidPrime(std::vector< std::vector<double> >);
        std::vector< std::vector<double> > propagate(std::vector< std::vector<double> >);
        double cost(std::vector< std::vector<double> >, std::vector< std::vector<double> >);
        std::vector< std::vector<double> > costPrimeW1(std::vector< std::vector<double> >, std::vector< std::vector<double> >);
        std::vector< std::vector<double> > costPrimeW2(std::vector< std::vector<double> >, std::vector< std::vector<double> >);
        std::vector<std::vector< std::vector<double> >> costPrime(std::vector< std::vector<double> >, std::vector< std::vector<double> >);
        std::vector< std::vector<double> > numeric_costPrimeW1(std::vector< std::vector<double> >, std::vector< std::vector<double> >);
        std::vector< std::vector<double> > numeric_costPrimeW2(std::vector< std::vector<double> >, std::vector< std::vector<double> >);
        void change_W1(std::vector< std::vector<double> >);
        void change_W2(std::vector< std::vector<double> >);
        void set_step(double);
        void train(std::vector< std::vector<double> >, std::vector< std::vector<double> >);
    protected:

    private:
        const unsigned int inputLayerSize = 2;
        const unsigned int hiddenLayerSize = 3;
        const unsigned int outputLayerSize = 1;

        std::vector< std::vector<double> > a1;
        std::vector< std::vector<double> > W1;
        std::vector< std::vector<double> > z2;
        std::vector< std::vector<double> > a2;
        std::vector< std::vector<double> > W2;
        std::vector< std::vector<double> > z3;

        double step_factor = 3;

        Matrix M;
};

#endif // NEURAL_NETWORK_H
