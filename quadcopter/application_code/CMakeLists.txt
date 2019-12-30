#####################################################################
# simple AVR library
#####################################################################
file(GLOB control_src
    "*.hh"
    "*.hpp"
    "*.cc"
    "*.cpp")
if(BUILD_TYPE STREQUAL "TARGET")
    add_avr_library(
    application_code_control
    ${control_src}
    )
else()
    add_library (
        application_code_control
        ${control_src}
    )
endif()
