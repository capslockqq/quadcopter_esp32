#include "drone_control.hpp"

Drone_Control::Drone_Control(const char* name, const char* id) :
 Component(this, name, id)
,drone_yaw_controller(this, "Drone Yaw Controller"  , "YAW")

,param_hover_setpoint(this   , "Hover Setpoint",         "HoverSP", 0.5)
{
}

void Drone_Control::Update() {
    drone_yaw_controller.Update();
}