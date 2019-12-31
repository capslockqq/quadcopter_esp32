#####################################################################
# simple AVR executable
#####################################################################
add_subdirectory(communication)
add_avr_executable(
   ${PRJ_NAME}
   main.cpp
   )


#####################################################################
# libraries to link to
#####################################################################
target_link_libraries(
   ${PRJ_NAME}-${AVR_MCU}.elf
   operators-${AVR_MCU}
   Free_RTOS_Tasks-${AVR_MCU}
   application_code-${AVR_MCU}
   application_code_control-${AVR_MCU}
   application_code_communication-${AVR_MCU}
   application_code_protocols-${AVR_MCU}
   avr_transport_layer-${AVR_MCU}
   Free_RTOS-${AVR_MCU}
   )