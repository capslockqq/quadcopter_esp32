#include "application_code.hpp"

Application_code::Application_code(const char *name, const char *id) :
Component(this, name, id)
,com_to_computer(this, "Com to PC", "ComPC")
,drone_controller("Drone controller", "DRONE")
,com_to_IMU(this, "Communication to IMU", "Com2IMU")
,op_bldc_voltage_set_point(this, "BLDC Voltage Set Point", "04")
,param_bldc_voltage_setpoint(this, "BLDC Voltage Setpoint", "05", 10.0)
{
}


void Application_code::Update() {
    static int result = 0;
    static int i = 0;
    drone_controller.Update();
    drone_controller.drone_pitch_controller.ip_setpoint.SetValue(result);
    drone_controller.drone_yaw_controller.ip_setpoint.SetValue(32);
    result = i*i;
    const char *test = "Hej med dig";
    com_to_computer.Update(test);
    i++;
    op_bldc_voltage_set_point.SetValue(param_bldc_voltage_setpoint.GetValue());
}
 