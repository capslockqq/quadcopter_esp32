#include "BLDC.hpp"

BLDC::BLDC(Component *parent, const char *name, const char *id) : 
Component(parent, name, id), param_time_constant(this, "BLDC Tau", "01", 0.1)
, param_KV(this, "BLDC KV", "02", 1200), op_rpm(this, "Rotations per minute", "03")
, ip_input_voltage(this, "Input voltage", "04")
, m_previous_rpm(0.0)
{
}

void BLDC::init()
{
    op_rpm.SetValue(0.0);
}

void BLDC::update()
{
    double tau = 0.01 / (0.01 + param_time_constant.GetValue());
    rpms[0] = (1 - tau) * rpms[1] + (tau * ip_input_voltage.GetValue());
    op_rpm.SetValue(rpms[0]);
    rpms[1] = rpms[0];
}