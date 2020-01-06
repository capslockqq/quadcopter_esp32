#####################################################################
# simple AVR library
#####################################################################

file(GLOB control_src
    "*.c"
    "*.cpp")
if (${ESP_PLATFORM})
idf_component_register(SRCS 
${control_src}
INCLUDE_DIRS ".")
endif()

if(${AVR})
    add_avr_library(
    application_code_control
    ${control_src}
    )
    endif()

if(${PC})
    add_library (
        application_code_control
        ${control_src}
    )
    endif()
