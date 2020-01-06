#include "test_controller.hpp"

test_controller::test_controller(Component *parent,const char* name, const char* id) :
Component(parent, name, id)
{
}

void test_controller::Update() {
    printf("Hello from test_control() \n");
}

