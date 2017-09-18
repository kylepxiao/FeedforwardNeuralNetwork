#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <vector>
#include <string>
#include <cmath>


class Matrix
{
    public:
        Matrix();
        void printmat(std::vector< std::vector<double> >);
        double det(std::vector< std::vector<double> >);
        double dot(std::vector<double>, std::vector<double>);
        std::vector< std::vector<double> > round(std::vector< std::vector<double> >);
        std::vector< std::vector<double> > cross(std::vector< std::vector<double> >, std::vector< std::vector<double> >);
        std::vector< std::vector<double> > invert(std::vector< std::vector<double> >);
        std::vector< std::vector<double> > transpose(std::vector< std::vector<double> >);
        std::vector< std::vector<double> > add(std::vector< std::vector<double> >, std::vector< std::vector<double> >);
        std::vector< std::vector<double> > sub(std::vector< std::vector<double> >, std::vector< std::vector<double> >);
        std::vector< std::vector<double> > mult(std::vector< std::vector<double> >, std::vector< std::vector<double> >);
        std::vector< std::vector<double> > mult(double, std::vector< std::vector<double> >);
        std::vector< std::vector<double> > scalar_mult(std::vector< std::vector<double> >, std::vector< std::vector<double> >);
        virtual ~Matrix();

    protected:

    private:
};

#endif // MATRIX_H
