#include "../../component_framework/components/Component.hpp"
#include "../../component_framework/components/Output.hpp"

class BLDC : Component
{
public:
    BLDC(Component *, const char *, const char *);
    virtual ~BLDC(){};

    void init();
    void update();

    Parameter<double> param_time_constant;
    Parameter<double> param_KV;

    Input<double>     ip_input_voltage;
    Output<double>    op_rpm;  

private:
    double m_previous_rpm;
    double rpms[2] = {0, 0};

};