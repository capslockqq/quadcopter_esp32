#pragma once
#include "../../operators.h"
#include "../../../application_code/communication/transport_layer/I_Serial_Communication.hpp" 
#include "../../../application_code/components/Input.hpp"
#include <avr/io.h>
class UART : public I_Serial_Communication<const char *, UART> {
public:
    UART(Component *parent, const char* name, const char *id);
    ~UART(){};
    void Update(const char * data);

private:
    void Send_Data();
    void Receive_Data();
    
    
};