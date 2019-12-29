#####################################################################
# simple AVR library
#####################################################################
file(GLOB transport_layer_src
    "*.hh"
    "*.h"
    "*.cc"
    "*.cpp")
if(BUILD_TYPE STREQUAL "TARGET")
    add_avr_library(
        avr_transport_layer
    ${transport_layer_src}
    )
else()
    add_library (
        avr_transport_layer
        ${transport_layer_src}
    )
endif()
