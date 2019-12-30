#include "drone_stabilze_controller.hpp"

const char* INPUT_MEASUREMENT[] = {"Roll measurement", "Pitch measurement", "Yaw measurement"} ;
const char* INPUT_SETPOINT[] = {"Roll Setpoint", "Pitch Setpoint", "Yaw Setpoint"} ;

Drone_stabilize_Controller::Drone_stabilize_Controller(Component *parent, const char* name, const char* id, INPUT_NAME_INDEX index, float max, float min) :
Component(parent, name, id)
,PID_controller(this, "PID Controller", "PID", max, min)
,ip_measurement(this, INPUT_MEASUREMENT[index], "MEAS")
,ip_setpoint(this, INPUT_SETPOINT[index], "SP")
,op_test(this, "SOME NAME", "OK")
,op_test2(this, "SOME NAME2", "OK2")
,op_output(this, "Output", "01")
,param_test(this, "Some param", "02", 1.0)
{
    PID_controller.Set_P_Gain(1.0);
}

Drone_stabilize_Controller::~Drone_stabilize_Controller() {
    
}

void Drone_stabilize_Controller::Init() {
    ip_measurement.SetValue(0.0);
    ip_setpoint.SetValue(0.0);
    op_test.SetValue(false);
    op_output.SetValue(5.0);
}

void Drone_stabilize_Controller::Update() {
    op_test.SetValue(1);
    PID_controller.Calculate_Output(ip_setpoint.GetValue() - ip_measurement.GetValue());
    op_output.SetValue(param_test.GetValue());
}
