
#pragma once
#include "../../component_framework/components/Component.hpp"
#include "../../component_framework/components/Output.hpp"
#include "../../freertos_distro/FreeRTOS_tasks/Application_interfaces.hpp"
#include "BLDC.hpp"

enum POSITION : int {
    X = 0,
    Y = 1,
    Z = 2
};

class quadcopter_model : public I_application_simulation, public Component {
public:
    quadcopter_model(const char*, const char*);
    void init();
    void Update();

    BLDC brushless_dc_motor_1;
    BLDC brushless_dc_motor_2;
    BLDC brushless_dc_motor_3;
    BLDC brushless_dc_motor_4;

    Output<double> *op_position      [3];
    Output<double> *op_velocity      [3];
    Output<double> *op_acceleration  [3];
    


};