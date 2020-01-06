#pragma once
#include "../../component_framework/components/Component.hpp"
#include "../../component_framework/components/Input.hpp"
#include "../../component_framework/components/Output.hpp"
#include "drone_stabilze_controller.hpp"
#include "test_controller.hpp"
class Drone_Control : public Component {
public:
    Drone_Control(const char * name, const char *id);
    ~Drone_Control(){};
    void Update();

    test_controller drone_yaw_controller;
     

    Parameter<double>          param_hover_setpoint;
};