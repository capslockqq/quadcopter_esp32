#pragma once
#include "../../component_framework/components/Component.hpp"
#include "../../component_framework/components/Input.hpp"
#include "../../component_framework/components/Output.hpp"


class Drone_stabilize_Controller : public Component {
public:
    Drone_stabilize_Controller(const char* name, const char* id);
    ~Drone_stabilize_Controller(){};
    void Update();
    void Init();

};