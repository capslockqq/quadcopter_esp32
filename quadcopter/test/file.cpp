#include "file.hpp"

Application_code::Application_code(const char *name, const char *id) :
Component(this, name, id)
,op_bldc_voltage_set_point(this, "BLDC Voltage Set Point", "04")
,param_bldc_voltage_setpoint(this, "BLDC Voltage Setpoint", "05", 10.0)
{
}


void Application_code::Update() {
    static int result = 0;
    static int i = 0;
    result = i*i;
    const char *test = "Hej med dig";
    i++;
    op_bldc_voltage_set_point.SetValue(param_bldc_voltage_setpoint.GetValue());
}
 