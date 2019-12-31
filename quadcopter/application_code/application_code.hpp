#pragma once
#include "../../component_framework/components/Component.hpp"
#include "../../component_framework/communication/transport_layer/I_Serial_Communication.hpp"
#include "drone_control.hpp"
#include "../../component_framework/components/Parameter.hpp"
#ifdef TARGET
#include "../../component_framework/operators.h"
#include <avr/io.h>
#include "../target/communication/transport_layer/UART.hpp"

#define COM_TO_PC UART
#define COM_TO_IMU UART

#endif

#ifdef PC

#include <chrono>
#include <ctime>
#include <math.h>
#include "../../component_framework/communication/transport_layer/UART_fake.hpp"
#include "../../component_framework/communication/transport_layer/I2C_fake.hpp"


#include <stdio.h>
#include <iostream>
#define COM_TO_IMU I2C_fake
#define COM_TO_PC  UART_fake

#endif
#include "../../freertos_distro/FreeRTOS_tasks/Application_interfaces.hpp"
class Application_code : public I_application_code, public Component {
public:
    Application_code(const char* name, const char * id);
    virtual ~Application_code(){};
    void Update();
    I_Serial_Communication<const char *, COM_TO_PC>     com_to_computer;
    I_Serial_Communication<const char *, COM_TO_IMU>    com_to_IMU;
    Drone_Control drone_controller;
    Output<double>          op_bldc_voltage_set_point;
    Parameter<double>       param_bldc_voltage_setpoint;
private:
    
};