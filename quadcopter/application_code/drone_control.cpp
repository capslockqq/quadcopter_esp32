#include "drone_control.hpp"

Drone_Control::Drone_Control(const char* name, const char* id) :
 Component(this, name, id)
,drone_yaw_controller(  this  , "Drone Yaw Controller"  , "YAW", INPUT_NAME_INDEX::YAW, 100, 0)
,drone_pitch_controller(this  , "Drone Pitch Controller", "PITCH", INPUT_NAME_INDEX::PITCH, 100, 0)
,drone_roll_controller( this  , "Drone Roll Controller" , "ROLL", INPUT_NAME_INDEX::ROLL, 100, 0)
,param_hover_setpoint(this   , "Hover Setpoint",         "HoverSP", 0.5)
{
}

Drone_Control::~Drone_Control() {
}

void Drone_Control::Update() {
    drone_yaw_controller.Update();
    drone_pitch_controller.Update();
    drone_roll_controller.Update();
}