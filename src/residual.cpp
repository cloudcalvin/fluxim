#include "residual.h"

Residual::Residual() {}
Residual::~Residual() {}

void Residual::compute_f1(System &cSys, double value)
{
    double alpha = cSys.mCons.alpha;

    vec P = cSys.mVec.P;
    vec V = cSys.mVec.V;
    vec r1 = cSys.mVec.r1;

    f1 = -P + 2*M_PI*alpha*V + r1;
}

void Residual::compute_f2(System &cSys, double value)
{
    mat Mt = cSys.mMat.Mt;
    mat Is = cSys.mMat.Is;

    vec P = cSys.mVec.P;
    vec V = cSys.mVec.V;
    vec Im = cSys.mVec.Im;
    vec r2 = cSys.mVec.r2;

    double gam = cSys.mCons.gam;

	f2 = -V + gam*(Mt*Im - sin(P) - V + Mt*Is) + r2;
	//f2 = -V + gam*(Mt*Im - sin(P) - V + Is) + r2;
	//f2 = -V + gam*(Mt*Im - sin(P) - V) + r2;
}

void Residual::compute_f3(System &cSys, double value)
{
	double B = 1;

    // The size is the number of loops
    // This is the amount of flux saved
    mat n = colvec({{0}, {0}, {0}, {0}});
	//mat f = colvec({{0}, {0}, {0}, {0}});
	mat f = colvec({{B*value}, {B*value}, {B*value}, {B*value}});

    mat Mt = cSys.mMat.Mt;
    mat M = cSys.mMat.M;
    mat Is = cSys.mMat.Is;
    mat L = cSys.mMat.L;
    mat Lb = cSys.mMat.Lb;
    vec k = cSys.mVec.k;

    double lam = cSys.mCons.lam;

    mat Lambda = L / (MU*RHO);
    mat Lambda_b = Lb / (MU*RHO);

    vec P  = cSys.mVec.P;
    vec Im = cSys.mVec.Im;

	//f3 = -(M*P + (1/lam)*(Lambda*Im + M*Lambda_b*Is) - 2*M_PI*(n-f));
	f3 = -(M*P + (1/lam)*(Lambda*Im) - 2*M_PI*(n-f));
	//f3 = -(M*P + (1/lam)*(Lambda*Im + Lambda*Is) - 2*M_PI*(n-f));
}

double Residual::compute_residual(vec fx) 
{
    double residual = 0.0;
    for (int i = 0; i < fx.size(); i++) 
		residual = residual + fx(i)*fx(i);
	residual = sqrtf(residual);
    return residual;
}

void Residual::compute_f1f2f3_residual(System &cSys, double value)
{
    compute_f1(cSys, value);
    compute_f2(cSys, value);
    compute_f3(cSys, value);

    f1_res = compute_residual(f1);
    f2_res = compute_residual(f2);
    f3_res = compute_residual(f3);

	//cout << f1_res << " " << f2_res << " " << f3_res << endl;
}








