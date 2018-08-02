#ifndef SYSTEM_H
#define SYSTEM_H

#include "vectors.h"
#include "matrix.h"
#include "cons.h"

class System 
{
    public:
        Matrix mMat;
        Vectors mVec;
        Cons mCons;

        System();
        ~System();

        void add_matrix(Matrix &mat);
        void add_vector(Vectors &vect);
        void add_const(Cons &cons);
};

#endif
