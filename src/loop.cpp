#include "loop.h"

Loop::Loop() {}
Loop::~Loop() {}

void Loop::set_to_zero(System &cSys)
{
    int loops = cSys.mCons.num_loops;
    int branches = cSys.mCons.num_branches;

    P_begin.zeros(branches);
    V_begin.zeros(branches);
    Im_begin.zeros(loops);
    P_diff.zeros(branches);
}

void Loop::loop_bias_current(System &cSys)
{
    Init cInit;

    vTime = cInit.get_time_array(cSys.mCons);
    vDc = cInit.get_dc_array();

    vPhase.zeros(vDc.size());
    vVoltage.zeros(vDc.size());
    vIm.zeros(vDc.size());

	cSys.mVec.r1.zeros(5);
	cSys.mVec.r2.zeros(5);

	set_to_zero(cSys);
    Response cResp;

    for (int i = 0; i < vDc.size(); i++) {
        dcValue = vDc(i);

        phase_sum = 0;
        voltage_sum = 0;
        current_sum = 0;
		count = 0;

		set_to_zero(cSys);
        loop_time(cSys, cResp, vTime);

		double Ic = cSys.mCons.Ic;
		double Rn = cSys.mCons.Rn;
		double N = cSys.mCons.N;

        vPhase(i) = phase_sum / (10*N);
        vVoltage(i) = voltage_sum * (1000*(Ic*Rn*N));
        vIm(i) = current_sum;
    }
}

void Loop::loop_time(System &cSys, Response &cResp, vec vTime)
{
	vec P_final;
	P_final.zeros(5);

	// Reset begin phase, voltage 
	// and current to zero for 
	// every new DC value.
	cResp.P = P_begin;
	cResp.V = V_begin;
	cResp.Im = Im_begin;

    for (int j = 0; j < vTime.size(); j++) {
        timeValue = vTime(j);

		double Idc = 4.8;
		//double Idc = dcValue;
        double VI  = cSys.mCons.VI;
        double Iac = 0.0*sin(2*M_PI*cSys.mCons.Vc*timeValue);
        double Ib  = Idc + Iac;

        create_bias_current_vector(cSys, Ib);
        cResp.circuit_values(cSys, dcValue);

		//phase_diff_at_time_t(cResp.P);
		voltage_at_time(cResp.V);
        current_at_time(cResp.Im);
    }
        
	phase_diff_at_time_t(cResp.P);
    //voltage_at_time(cResp.V);
    //current_at_time(cResp.Im);
}

void Loop::create_bias_current_vector(System &cSys, double Ib)
{
    int loops = cSys.mCons.num_loops;
	int branches = cSys.mCons.num_branches;

	mat Is(loops, 1);

	for (int i = 0; i < loops; i++) {
		Is(i,0) = Ib*cSys.mVec.k(i);
	}

    cSys.mMat.Is = Is;
}

void Loop::phase_diff_at_time_t(vec P_end)
{
    P_diff = P_end - P_begin;
    double sum = 0;
    for (int k = 0; k < P_diff.size(); k++)
        sum = sum + P_diff(k);
    phase_sum = phase_sum + sum;
}

void Loop::voltage_at_time(vec V)
{
    double sum = 0;
    for (int i = 0; i < V.size(); i++)
        sum = sum + V(i);
	voltage_sum = voltage_sum + sum;
}

void Loop::current_at_time(vec Im)
{
    double sum = 0;
    for (int i = 0; i < Im.size(); i++)
        sum = sum + Im(i);
    current_sum = current_sum + sum;
}













