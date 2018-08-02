#ifndef CONS_H
#define CONS_H

#include "globals.h"
#include <iostream>

using namespace std;

class Cons 
{
    public:
        int num_branches;
        int num_loops;

        double alpha, N;
        double Rn, C, Bc;

        double Ic, lam, gam;
        double Vc, VI;

        Cons();
        ~Cons();

        void set_consts();
		double calculate_Ic_from_lam();
		double calculate_cap_from_Bc();
};

#endif
