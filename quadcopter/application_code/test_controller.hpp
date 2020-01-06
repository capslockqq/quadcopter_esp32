#pragma once

#include "../../component_framework/components/Component.hpp"
#include <stdio.h>
class test_controller : public Component
{
private:
    /* data */
public:
    test_controller(Component *, const char*, const char*);
    ~test_controller(){};
    void Update();
};