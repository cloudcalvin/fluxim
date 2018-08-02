#ifndef MATRIX_H
#define MATRIX_H

#include <armadillo>
#include "globals.h"
#include "cons.h"

using namespace arma;
using namespace std;

class Matrix
{
    public:
        mat M, Mt, L;
        mat I, Lb, Is;

        Matrix();
        ~Matrix();

        mat C_matrix_create(vec P);
        mat B_matrix_create(Cons &cCons, vec f1, vec f2, vec f3);
        mat A_matrix_create(Cons &cCons, vec P);

        mat create_row_1(Cons &cCons);
        mat create_row_2(Cons &cCons, vec P);
        mat create_row_3(Cons &cCons);
};

#endif 







