#pragma once
#include "../../component_framework/components/Component.hpp"
#include "../../component_framework/components/Input.hpp"
#include "../../component_framework/components/Output.hpp"

template <class T>
class PID_Controller : public Component {
public:
    PID_Controller(Component *, const char*, const char*, float max_limit, float min_limit);
    ComponentType type() {return output; }
    void Init();
    void Set_P_Gain(T p_gain);
    void Set_I_Gain(T i_gain);
    T    Get_P_Gain();
    T    Get_I_Gain();
    T    Calculate_Output(T error);
    void init(T p_gain, T i_gain);


    Input<T>  ip_error;
    Output<T> op_control_signal;

private:
    T _P_gain;
    T _I_gain;
    T _output;
    float _max_limit;
    float _min_limit;
};
template <class T>
PID_Controller<T>::PID_Controller(Component *parent, const char* name, const char* id, float max_limit, float min_limit) :
Component(parent, name, id)
,ip_error(this, "Control error", "01")
,op_control_signal(this, "Control signal", "02")
,_max_limit(max_limit)
,_min_limit(min_limit)
{
}
template <class T>
void PID_Controller<T>::Init() {
    ip_error.SetValue(0);
    op_control_signal.SetValue(0);
}
template <class T>
void PID_Controller<T>::Set_P_Gain(T p_gain) {
    _P_gain = p_gain;
}
template <class T>
void PID_Controller<T>::Set_I_Gain(T i_gain) {
    _I_gain = i_gain;
}
template <class T>
T PID_Controller<T>::Get_P_Gain() {
    return _P_gain;
}
template <class T>
T PID_Controller<T>::Get_I_Gain() {
    return _I_gain;
}

template <class T>
T PID_Controller<T>::Calculate_Output(T error) {
    _output = _P_gain*error;
    op_control_signal.SetValue(_output);
}

template <class T>
void PID_Controller<T>::init(T p_gain, T i_gain) {
    _P_gain = p_gain; 
    _I_gain = i_gain;
    _output = 0;
}