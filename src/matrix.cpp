#include <armadillo>

#include "matrix.h"
#include "globals.h"
#include "read.h"

using namespace std;
using namespace arma;

Matrix::Matrix() {}
Matrix::~Matrix() {}

mat Matrix::C_matrix_create(vec P)
{
    mat C = {{cos(P(0)), 0, 0, 0, 0},
             {0, cos(P(1)), 0, 0, 0},
             {0, 0, cos(P(2)), 0, 0},
             {0, 0, 0, cos(P(3)), 0},
             {0, 0, 0, 0, cos(P(4))},
            };

    return C;
}

mat Matrix::B_matrix_create(Cons &cCons, vec f1, vec f2, vec f3)
{
    int branches = cCons.num_branches;

    mat B;

    B.insert_rows(0, f1);
    B.insert_rows(branches, f2);
    B.insert_rows(2*branches, f3);

    return B;
}

mat Matrix::A_matrix_create(Cons &cCons, vec P)
{
    mat A;
    int branches = cCons.num_branches;

    mat row1 = create_row_1(cCons);
    mat row2 = create_row_2(cCons, P);
    mat row3 = create_row_3(cCons);

    A.insert_rows(0, row1);
    A.insert_rows(branches, row2);
    A.insert_rows(2*branches, row3);

    return A;
}

mat Matrix::create_row_1(Cons &cCons)
{
    mat row1;
    mat zero_mat;

    int branches = cCons.num_branches;
    int loops = cCons.num_loops;
    
    zero_mat.zeros(branches, loops);

    double gam = cCons.gam;
    double Bc = cCons.Bc;

    row1.insert_cols(0, I);
    row1.insert_cols(branches, -gam*Bc*I);
    row1.insert_cols(2*branches, zero_mat);

    return row1;
}

mat Matrix::create_row_2(Cons &cCons, vec P)
{
    mat row2;
    mat C = C_matrix_create(P);

    int branches = cCons.num_branches;
    double gam = cCons.gam;

    row2.insert_cols(0, gam*C);
    row2.insert_cols(branches, I*(1 + gam));
    row2.insert_cols(2*branches, -gam*Mt);

    return row2;
}

mat Matrix::create_row_3(Cons &cCons)
{
    mat row3;
    mat zero_mat;

    int branches = cCons.num_branches;
    int loops = cCons.num_loops;

    zero_mat.zeros(loops, branches);

    double lam = cCons.lam;

    mat Lambda = L / (MU*RHO);

    row3.insert_cols(0, M);
    row3.insert_cols(branches, zero_mat);
    row3.insert_cols(2*branches, (1/lam)*Lambda);

    return row3;
}









