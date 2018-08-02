#ifndef VECTORS_H
#define VECTORS_H

#include <armadillo>

using namespace arma;

class Vectors
{
    public:
        vec P, V, Im;
        vec r1, r2, k;

        Vectors();
        ~Vectors();
};

#endif 
