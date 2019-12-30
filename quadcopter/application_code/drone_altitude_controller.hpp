#pragma once
#include "../../component_framework/components/Component.hpp"
#include "../../component_framework/components/Input.hpp"
#include "../../component_framework/components/Output.hpp"

class Drone_Altitude_Controller : public Component {
public:
    Drone_Altitude_Controller(Component *parent, const char* name, const char* id);
    virtual ~Drone_Altitude_Controller();
    void Update();
};