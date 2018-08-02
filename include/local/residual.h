#ifndef RESIDUAL_H
#define RESIDUAL_H

#include <armadillo>
#include "system.h"

using namespace arma;

class Residual
{
    public:
        vec f1, f2, f3;
        double f1_res, f2_res, f3_res; 

        Residual();
       ~Residual();

        void compute_f1(System &cSys, double value);
        void compute_f2(System &cSys, double value);
        void compute_f3(System &cSys, double value);

        double compute_residual(vec fx);
        void compute_f1f2f3_residual(System &cSys, double value);
};

#endif
