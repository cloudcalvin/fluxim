#include "system.h"

System::System() {}
System::~System() {}

void System::add_matrix(Matrix &mat)
{
    mMat = mat;
}

void System::add_vector(Vectors &vect)
{
    mVec = vect;
}

void System::add_const(Cons &cons) 
{
    mCons = cons;
}
