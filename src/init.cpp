#include "init.h"

Init::Init() {}
Init::~Init() {}

vec Init::get_time_array(Cons &cCons)
{
    double VI = cCons.VI;
    double Vc = cCons.Vc;

    double T = 1.0/Vc;
    double delta_t = 1.0/(Vc*100.0);
    int time_range = 50*T/delta_t;
    vec Time(time_range);

    for (int i = 0; i < time_range; i++)
        Time(i) =  delta_t*i;

    return Time;
}

vec Init::get_dc_array()
{
    int dc = 10;
    double delta_dc = 1.0/1.0;
    int dc_range = dc/delta_dc;
    vec Dc(dc_range);

    for (int i = 0; i < dc_range; i++) { 
		Dc(i) = -0.5*dc_range*delta_dc + delta_dc*i;
    }

    return Dc;
}
