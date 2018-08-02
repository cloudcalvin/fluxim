#include "cons.h"
#include <stdio.h>
#include <stdlib.h>

Cons::Cons() {}
Cons::~Cons() {}

void Cons::set_consts()
{
    N = 5;
    Rn = 5;

	//Ic = calculate_Ic_from_lam();
	//C = calculate_cap_from_Bc();

    Ic = 72e-6;
    C = 5e-12;
    Bc = 2*PI*Ic*Rn*Rn*C / FLUX;
    lam = FLUX / (2*PI*Ic*MU*RHO);

    Vc = (Ic*Rn) / FLUX;
    VI = 1.0*Vc;

    alpha = 1.0/50.0;
    gam = (2*PI*alpha) / Bc;

    //alpha = (Bc*gam) / (2*M_PI);
	//Ic = (Bc * flux) / (2*M_PI*pow(Rn,2)*C);


    cout << "===================" << endl;
    cout << "Set variables:" << endl;
    cout << "===================" << endl;

    cout << "lam: " << lam << endl;
    cout << "Vc : " << Vc << endl;
    cout << "VI : " << VI << endl;
    cout << "Ic : " << Ic*1e+6 << " uA" << endl;
    cout << "flux : " << FLUX << endl;
    cout << "mu   : " << MU << endl;
    cout << "alpha: " << alpha << endl;
    cout << "N    : " << N << endl;
    cout << "Rn   : " << Rn << endl;
    cout << "C    : " << C << endl;
    cout << "Bc   : " << Bc << endl;
    cout << "gam: " << gam <<  endl;
}

double Cons::calculate_Ic_from_lam()
{
    lam = 1;
    double Ic = (lam*FLUX) / (2*PI*MU);
    return Ic;
}

double Cons::calculate_cap_from_Bc()
{
    Bc = 0.00001;
    double C = (Bc*FLUX) / (2*PI*Ic*Rn*Rn);
    return C;
}
    









