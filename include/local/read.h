#ifndef READ_H
#define READ_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "system.h"

using namespace std;

class Read
{
    public:
        Read();
        ~Read();

        void inductance_matrix(System &cSys);
        void create_coupling_vector(System &cSys);
        void update_L_matrix(System &cSys);
        void split_line(System &cSys, string line, int numLine);
};

#endif
