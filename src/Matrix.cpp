#include "Matrix.h"

using namespace std;

Matrix::Matrix()
{
    //ctor
}

Matrix::~Matrix()
{
    //dtor
}

void Matrix::printmat(std::vector< std::vector<double> > mat)
{
    for (unsigned int k=0; k<mat.size(); k++)
    {
        cout<<endl;
        for (unsigned int i=0; i<mat[k].size(); i++)
        {
            cout<<mat[k][i];
            cout<<" ";
        }
    }
    cout<<endl<<endl;
}

double Matrix::dot(std::vector< double > vec1, std::vector< double > vec2)
{
    double num = 0;
    if (!(vec1.size()==vec2.size()))
    {
        cerr<<"Vectors cannot be dot multiplied."<<endl;
        return num;
    }
    for (unsigned int i=0; i<vec1.size(); i++)
    {
        num = num+(vec1[i]*vec2[i]);
    }
    return num;
}

double Matrix::det(std::vector< std::vector<double> > mat)
{
    double tempdet, findet, posval, total=0;
    std::vector< std::vector<double> > tempmat;
    if (mat.size() <= 0 || mat[0].size() <= 0 || !(mat.size()==mat[0].size()) || mat.size() == 0)
    {
        cerr<<"Cannot find determinant."<<endl;
        return 0;
    }else if(mat.size() == 1){
        return mat[0][0];
    }

    for (unsigned int i=0; i<mat[0].size(); i++)
    {
        posval = mat[0][i];
        tempmat = mat;
        if (mat.size() == 2)
        {
            tempdet = (tempmat[0][0]*tempmat[1][1])-(tempmat[0][1]*tempmat[1][0]);
            return tempdet;
        }
        else
        {
            for (unsigned int k=0; k<mat.size(); k++)
                {
                    tempmat[k].erase(tempmat[k].begin()+i);
                }
            tempmat.erase(tempmat.begin());
            findet = posval*Matrix::det(tempmat);
            if ((i%2==1))
            {
                findet *= -1;
            }
            total+= findet;
        }
    }
    return total;
}

std::vector< std::vector<double> > Matrix::round(std::vector< std::vector<double> > mat)
{
    for (unsigned int i=0; i<mat.size(); i++)
    {
        for (unsigned int k=0; k<mat[i].size(); k++)
        {
            mat[i][k] = floor(mat[i][k]*100+0.5)/100;
        }
    }
    return mat;
}

std::vector< std::vector<double> > Matrix::cross(std::vector< std::vector<double> > vec1, std::vector< std::vector<double> > vec2)
{
    std::vector< double > vec;
    std::vector< std::vector<double> > mat;
    if (vec1.size()==1 && vec2.size()==1 && vec1[0].size()==3)
    {
        vec.push_back((vec1[0][1]*vec2[0][2])-(vec1[0][2]*vec2[0][1]));
        vec.push_back(-1*((vec1[0][0]*vec2[0][2])-(vec1[0][2]*vec2[0][0])));
        vec.push_back((vec1[0][0]*vec2[0][1])-(vec1[0][1]*vec2[0][0]));
        mat.push_back(vec);
    }
    else
    {
        cerr<<"Cannot find cross product of vectors."<<endl;
    }
    return mat;
}

std::vector< std::vector<double> > Matrix::invert(std::vector< std::vector<double> > mat)
{
    double vecratio, divideratio;
    int iterate = 0;
    std::vector< std::vector<double> > ident;
    std::vector<double> tempvec, origvec, identvec, origdent, subvector;
    if (!(mat.size()==mat[0].size()))
    {
        cerr<<"Cannot invert matrix."<<endl;
        return ident;
    }
    else if(mat.size() <= 1)
    {
        return mat;
    }
    else if (Matrix::det(mat)==0)
    {
        cerr<<"Matrix inversion undefined."<<endl;
        return ident;
    }
    for (unsigned int i=0; i<mat.size(); i++)
    {
        tempvec.clear();
        for (unsigned int k=0; k<mat[0].size(); k++)
        {
            if (i==k)
            {
                tempvec.push_back(1);
            }
            else
            {
                tempvec.push_back(0);
            }
        }
        ident.push_back(tempvec);
    }

    for (unsigned int i=0; i<mat.size(); i++)
    {
        tempvec.clear();
        iterate = 1;
        origvec = mat[i];
        origdent = ident[i];
        while (mat[i][i]==0)
        {
            tempvec = mat[i+iterate];
            identvec = ident[i+iterate];
            mat[i] = tempvec;
            ident[i] = identvec;
            mat[i+iterate] = origvec;
            ident[i+iterate] = origdent;
            iterate++;
        }
        divideratio = mat[i][i];
        for (unsigned int k=0; k<mat[0].size(); k++)
        {
            mat[i][k] = mat[i][k]/divideratio;
            ident[i][k] = ident[i][k]/divideratio;
        }
        for (unsigned int j=0; j<mat.size(); j++)
        {
            if (!(j==i))
            {
                tempvec.clear();
                vecratio = mat[j][i];
                for (unsigned int l=0; l<mat[0].size(); l++)
                {
                    mat[j][l] -= vecratio*mat[i][l];
                    ident[j][l] -= vecratio*ident[i][l];
                }
            }
        }
    }
    return ident;
}

std::vector< std::vector<double> > Matrix::transpose(std::vector< std::vector<double> > mat)
{
    std::vector<double> vec;
    std::vector< std::vector<double> > tempmat;
    for (unsigned int i=0; i<mat[0].size(); i++)
    {
        vec.clear();
        for (unsigned int k=0; k<mat.size(); k++)
        {
            vec.push_back(mat[k][i]);
        }
        tempmat.push_back(vec);
    }
    return tempmat;
}

std::vector< std::vector<double> > Matrix::add(std::vector< std::vector<double> > mat1, std::vector< std::vector<double> > mat2)
{
    std::vector<double> vec;
    std::vector< std::vector<double> > tempmat1;
    for (unsigned int i=0; i<mat1.size(); ++i)
    {
        for (unsigned int j=0; j<mat1.at(i).size(); j++)
        {
            try{
                vec.push_back(mat1.at(i).at(j) + mat2.at(i).at(j));
            }catch(int e){
                cerr << "Error in matrix addition!" << endl;
                return tempmat1;
            }
        }
        tempmat1.push_back(vec);
        vec.clear();
    }
    return tempmat1;
}

std::vector< std::vector<double> > Matrix::sub(std::vector< std::vector<double> > mat1, std::vector< std::vector<double> > mat2)
{
    std::vector<double> vec;
    std::vector< std::vector<double> > tempmat1;
    for (unsigned int i=0; i<mat1.size(); ++i)
    {
        for (unsigned int j=0; j<mat1.at(i).size(); j++)
        {
            try{
                vec.push_back(mat1.at(i).at(j) - mat2.at(i).at(j));
            }catch(int e){
                cerr << "Error in matrix subtraction!" << endl;
                return tempmat1;
            }
        }
        tempmat1.push_back(vec);
        vec.clear();
    }
    return tempmat1;
}

std::vector< std::vector<double> > Matrix::mult(std::vector< std::vector<double> > mat1, std::vector< std::vector<double> > mat2)
{
    std::vector<double> vec1, vec2;
    std::vector< std::vector<double> > tempmat1;
    if (!(mat1[0].size()==mat2.size()))
    {
        cerr<<"Matrix can not be multiplied"<<endl;
        std::vector< std::vector<double> > vec;
        return vec;
    }
    for (unsigned int i=0; i<mat1.size(); i++)
    {
        vec2.clear();
        for (unsigned int k=0; k<mat2[0].size(); k++)
        {
            vec1.clear();
            for (unsigned int j=0; j<mat2.size(); j++)
            {
                vec1.push_back(mat2[j][k]);
            }
            vec2.push_back(Matrix::dot(mat1[i], vec1));
        }
        tempmat1.push_back(vec2);
    }
    return tempmat1;
}

std::vector< std::vector<double> > Matrix::mult(double num1, std::vector< std::vector<double> > mat)
{
    std::vector<double> vec;
    std::vector< std::vector<double> > tempmat1;
    if (mat.size() <= 0 || mat[0].size() <= 0)
    {
        cerr<<"Matrix can not be multiplied"<<endl;
        std::vector< std::vector<double> > vec;
        return vec;
    }
    for (unsigned int k=0; k<mat.size(); k++)
    {
        vec.clear();
        for (unsigned int j=0; j<mat[0].size(); j++)
        {
            vec.push_back(num1 * mat[k][j]);
        }
        tempmat1.push_back(vec);
    }
    return tempmat1;
}

std::vector< std::vector<double> > Matrix::scalar_mult(std::vector< std::vector<double> > mat1, std::vector< std::vector<double> > mat2)
{
    for(unsigned int i=0; i<mat1.size(); ++i){
        for(unsigned int j=0; j<mat1.at(i).size(); ++j){
            try{
                mat1.at(i).at(j) *= mat2.at(i).at(j);
            }catch(int e){
                cerr << "Error in matrix scalar multiplication!" << endl;
                vector< vector<double> > n;
                return n;
            }
        }
    }
    return mat1;
}
