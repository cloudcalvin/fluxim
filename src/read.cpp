#include <math.h>

#include "read.h"
#include "globals.h"

Read::Read() {}
Read::~Read() {}

void Read::inductance_matrix(System &cSys)
{
    int numLine = 0;
    int loops = cSys.mCons.num_loops;

    string line;
    ifstream myfile ("../tests/L_dc.txt");

    cSys.mMat.L.resize(loops + 1, loops + 1);

    if (myfile.is_open()) {
        while ( getline (myfile,line) ) {
            if (line[0] == ' ') {
                split_line(cSys, line, numLine);
                numLine++;
            }
        }

        myfile.close();
    } else 
        cout << "Unable to open file"; 

    create_coupling_vector(cSys);
    update_L_matrix(cSys);

    cSys.mMat.L.print("L:");
}

void Read::create_coupling_vector(System &cSys)
{
    cSys.mVec.k.resize(cSys.mCons.num_loops);

	double Is = 7.189145089;

    cSys.mVec.k(0) = -2.196737118/Is;
    cSys.mVec.k(1) = 2.1672301946/Is;
    cSys.mVec.k(2) = 1.1355636683/Is;
    cSys.mVec.k(3) = 0.6568423816/Is;

	//cSys.mVec.k(0) = 0.5;
	//cSys.mVec.k(1) = 0.5;
	//cSys.mVec.k(2) = 0.5;
	//cSys.mVec.k(3) = 0.5;
	
    cSys.mVec.k.print("k:");
    cout << endl;
}

//void Read::create_coupling_vector(System &cSys)
//{
    //cSys.mVec.k.resize(cSys.mCons.num_loops);

    //for (int i = 1; i < cSys.mCons.num_loops + 1; i++) {
        //double L1 = 0;
        //double Ls = 0;
        //double M = 0;

        //L1 = cSys.mMat.L(i,i); 
        //Ls = cSys.mMat.L(0,0);
        //M  = cSys.mMat.L(0,i);

		//cSys.mVec.k(i-1) = abs(M / (sqrt(L1*Ls)));
    //} 

    //cSys.mVec.k.print("k:");
    //cout << endl;
//}

// Update the L matrix by removing the 
// first col and first row.
void Read::update_L_matrix(System &cSys)
{
    cSys.mMat.L.shed_row(0);
    cSys.mMat.L.shed_col(0);
}

void Read::split_line(System &cSys, string line, int numLine)
{
    int count = 0;

    string str(line);
    string buf;
    stringstream ss(str);

    vector<string> tokens;

    while (ss >> buf)
        tokens.push_back(buf);

    for (vector<string>::const_iterator i = tokens.begin(); i != tokens.end(); ++i) {
        string word = *i;

        if (word.compare("+0j") != 0) {
            double inductance = atof(word.c_str());
            cSys.mMat.L(numLine, count) = inductance;
            count++;
        }
    }
}








