#include "response.h"

Response::Response() {}
Response::~Response() {}

void Response::circuit_values(System &cSys, double value) 
{
    theta_v_im_init(cSys);

    Residual cRes;
    cRes.compute_f1f2f3_residual(cSys, value);

    while ((cRes.f1_res >= EPSI) || (cRes.f2_res >= EPSI) || (cRes.f3_res >= EPSI)) {
        mat B = cSys.mMat.B_matrix_create(cSys.mCons, cRes.f1, cRes.f2, cRes.f3);
        mat A = cSys.mMat.A_matrix_create(cSys.mCons, cSys.mVec.P);
        mat x = solve(A, B);

        theta_v_im_update(cSys, x);
        cRes.compute_f1f2f3_residual(cSys, value);
    }

    P = cSys.mVec.P;
    V = cSys.mVec.V;
    Im = cSys.mVec.Im;
}

void Response::theta_v_im_init(System &cSys)
{
    int loops = cSys.mCons.num_loops;
    int branches = cSys.mCons.num_branches;

    cSys.mVec.P.zeros(branches);
    cSys.mVec.V.zeros(branches);
    cSys.mVec.Im.zeros(loops);

    cSys.mVec.r1 = P;
    cSys.mVec.r2 = V;
}

void Response::theta_v_im_update(System &cSys, vec x)
{
    vec x_vec = vectorise(x);

    int loops = cSys.mCons.num_loops;
    int branches = cSys.mCons.num_branches;

	vec P_delta  = x_vec.subvec(0, branches - 1);
	vec V_delta  = x_vec.subvec(branches, 2*branches - 1);
	vec Im_delta = x_vec.subvec(2*branches, 2*branches + loops - 1);

    cSys.mVec.P  = cSys.mVec.P + P_delta;
    cSys.mVec.V  = cSys.mVec.V + V_delta;
    cSys.mVec.Im = cSys.mVec.Im + Im_delta;;
}








