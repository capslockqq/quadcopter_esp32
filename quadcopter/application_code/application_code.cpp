#include "application_code.hpp"

Application_code::Application_code(const char *name, const char *id) :
Component(this, name, id)
,drone_controller("Drone controller", "DRONE")
 ,op_bldc_voltage_set_point(this, "BLDC Voltage Set Point", "04")
,param_bldc_voltage_setpoint(this, "BLDC Voltage Setpoint", "05", 10.0)
{
}


void Application_code::Update() {
    drone_controller.Update();
    printf("Hello from application\n");
}
 