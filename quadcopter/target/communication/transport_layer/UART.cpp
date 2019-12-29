#include "UART.hpp"

UART::UART(Component *parent, const char* name, const char *id) :
I_Serial_Communication(parent, name, id)
{
}

void UART::Update(const char * data) {
    this->op_data.SetValue(data);
    Send_Data();
}

void UART::Send_Data() {
    int i = 0;
	while(this->op_data.GetValue()[i] != '\0') {
		while ( !( UCSR0A & (1<<UDRE0)));
        /* Put data into buffer, sends the data */
        UDR0 = this->op_data.GetValue()[i];
		i++;
	}
}

void UART::Receive_Data() {

}
