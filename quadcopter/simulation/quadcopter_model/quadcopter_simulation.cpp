#include "quadcopter_simulation.hpp"

quadcopter_model::quadcopter_model(const char* name, const char* id) : 
Component(this, name, id)
,brushless_dc_motor_1(this, "Brushless DC 1", "01")
,brushless_dc_motor_2(this, "Brushless DC 2", "02")
,brushless_dc_motor_3(this, "Brushless DC 3", "03")
,brushless_dc_motor_4(this, "Brushless DC 4", "04")
{
    op_position[POSITION::X]        =  new Output<double>(this, "X Position", "05");
    op_position[POSITION::Y]        =  new Output<double>(this, "Y Position", "06");
    op_position[POSITION::Z]        =  new Output<double>(this, "Z Position", "07");

    op_velocity[POSITION::X]        =  new Output<double>(this, "X Velocity", "08");
    op_velocity[POSITION::Y]        =  new Output<double>(this, "Y Velocity", "09");
    op_velocity[POSITION::Z]        =  new Output<double>(this, "Z Velocity", "10");

    op_acceleration[POSITION::X]    =  new Output<double>(this, "X Acceleration", "11");
    op_acceleration[POSITION::Y]    =  new Output<double>(this, "Y Acceleration", "12");
    op_acceleration[POSITION::Z]    =  new Output<double>(this, "Z Acceleration", "13");
}
    
void quadcopter_model::init() {

}

void quadcopter_model::Update() {
    brushless_dc_motor_1.update();
    brushless_dc_motor_2.update();
    brushless_dc_motor_3.update();
    brushless_dc_motor_4.update();  
}
