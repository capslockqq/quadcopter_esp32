#pragma once
#include "../../component_framework/components/Component.hpp"
#include "../../component_framework/components/Input.hpp"
#include "../../component_framework/components/Output.hpp"
#include "PID_Controller.hpp"
enum INPUT_NAME_INDEX {
    ROLL,
    PITCH,
    YAW
};

class Drone_stabilize_Controller : public Component {
public:
    Drone_stabilize_Controller(Component *parent, const char* name, const char* id, INPUT_NAME_INDEX index, float max, float min);
    virtual ~Drone_stabilize_Controller();
    void Update();
    void Init();
    PID_Controller<float>  PID_controller;
    Input<float>    ip_measurement;
    Input<float>    ip_setpoint;
    Output<bool>    op_test;
    Output<bool>    op_test2;
    Output<double>     op_output;
    Parameter<double>  param_test;
};