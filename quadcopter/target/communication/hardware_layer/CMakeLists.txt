#####################################################################
# simple AVR library
#####################################################################
file(GLOB hardware_layer_src
    "*.c"
    "*.cpp")
if(BUILD_TYPE STREQUAL "TARGET")
    add_avr_library(
        avr_hardware_layer
    ${hardware_layer_src}
    )
else()
    add_library (
        pc-avr_hardware_layer
        ${hardware_layer_src}
    )
endif()
