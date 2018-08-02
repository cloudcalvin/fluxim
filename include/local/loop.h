#ifndef LOOP_H
#define LOOP_H

#include "system.h"
#include "response.h"
#include "init.h"

class Loop 
{
    private:
        int count;
    public:
        double dcValue;
        double timeValue;
        double phase_sum;
        double voltage_sum;
        double current_sum;

        vec P_diff, vTime, vDc;
        vec vPhase, vVoltage, vIm;
        vec P_begin, V_begin, Im_begin;

        Loop();
        ~Loop();

        void voltage_at_time(vec V);
        void current_at_time(vec Im);
        void set_to_zero(System &cSys);
        void loop_bias_current(System &cSys);
        void phase_diff_at_time_t(vec P_end);
        void loop_time(System &cSys, Response &cResp, vec time);
        void create_bias_current_vector(System &cSys, double Ib);
};

#endif
