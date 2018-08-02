#ifndef RESPONSE_H
#define RESPONSE_H

#include <armadillo>
#include "system.h"
#include "residual.h"

using namespace arma;

class Response
{
    public:
        vec P;
        vec V;
        vec Im;

        Response();
        ~Response();

        void circuit_values(System &cSys, double value) ;
        void theta_v_im_init(System &cSys);
        void theta_v_im_update(System &cSys, vec x);
};

#endif
