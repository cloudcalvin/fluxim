#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>

#include "read.h"
#include "loop.h"

using namespace std;

void write_voltage_current(System &cSys, Loop &mLoop);
void write_phase_voltage(Loop &mLoop);
void write_Im_bias_current(Loop &mLoop);

int main()
{
    System cSys;
    Matrix cMat;
    Vectors cVec;
    Read cRead;
    Cons cCons;
    Loop cLoop;

    cCons.num_loops = 4;
    cCons.num_branches = 5;

    cMat.M = {{-1, 1, 0, 0, 0},
              {0, -1, 1, 0, 0},
              {0, 0, -1, 1, 0},
              {0, 0, 0, -1, 1},
             };

    // M rows is num_loops
    // M cols is num_branches
    cMat.Mt = cMat.M.t();

    // Square matrix equal to 
    // num_branches
    cMat.I = {{1, 0, 0, 0, 0},
              {0, 1, 0, 0, 0},
              {0, 0, 1, 0, 0},
              {0, 0, 0, 1, 0},
              {0, 0, 0, 0, 1},
             };

    cMat.Lb = {{1e-12, 0e-14, 0e-14, 0e-14, 0e-14},
               {0e-14, 1e-12, 0e-14, 0e-14, 0e-14},
               {0e-14, 0e-14, 1e-12, 0e-14, 0e-14},
               {0e-14, 0e-14, 0e-14, 1e-12, 0e-14},
               {0e-14, 0e-14, 0e-14, 0e-14, 1e-12},
              };

    cCons.set_consts();

    cSys.add_matrix(cMat);
    cSys.add_vector(cVec);
    cSys.add_const(cCons);

    cRead.inductance_matrix(cSys);
    cLoop.loop_bias_current(cSys);

    write_voltage_current(cSys, cLoop);
    write_phase_voltage(cLoop);
    write_Im_bias_current(cLoop);

    return 0;
}

void write_voltage_current(System &cSys, Loop &mLoop)
{
    ofstream myfile;
    myfile.open ("vi.txt");
    myfile << "Writing this to a file.\n";

    double Ic = cSys.mCons.Ic;

    for (int i = 0; i < mLoop.vDc.size(); i++) {
        double Idc = mLoop.vDc(i) * cSys.mCons.Ic;
        myfile << mLoop.vDc(i)*Ic << " " << mLoop.vVoltage(i) << endl; 
    }

    myfile.close();
}

void write_phase_voltage(Loop &mLoop)
{
    ofstream myfile;
    myfile.open ("pv.txt");
    myfile << "Writing this to a file.\n";

    for (int i = 0; i < mLoop.vDc.size(); i++) {
        myfile << mLoop.vDc(i) << " " << mLoop.vPhase(i) << endl; 
    }

    myfile.close();
}

void write_Im_bias_current(Loop &mLoop)
{
    ofstream myfile;
    myfile.open ("im_bias.txt");
    myfile << "Writing this to a file.\n";

    for (int i = 0; i < mLoop.vDc.size(); i++) {
        myfile << mLoop.vDc(i) << " " << mLoop.vIm(i) << endl; 
    }

    myfile.close();
}













