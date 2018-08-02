#ifndef INIT_H
#define INIT_H

#include <armadillo>
#include "cons.h"

using namespace arma;

class Init 
{
    public:
        Init();
        ~Init();

        vec get_time_array(Cons &cCons);
        vec get_dc_array();
};

#endif
