#include "drone_stabilze_controller.hpp"

const char* INPUT_MEASUREMENT[] = {"Roll measurement", "Pitch measurement", "Yaw measurement"} ;
const char* INPUT_SETPOINT[] = {"Roll Setpoint", "Pitch Setpoint", "Yaw Setpoint"} ;

Drone_stabilize_Controller::Drone_stabilize_Controller(const char* name, const char* id) :
Component(this, name, id)

{
}

void Drone_stabilize_Controller::Init() {

}

void Drone_stabilize_Controller::Update() {

}
