#####################################################################
# simple AVR library
#####################################################################
file(GLOB simulation_quadcopter_src
    "*.cpp"
    "*.hpp"
)
if(BUILD_TYPE STREQUAL "PC")
    add_library (
    simulation_quadcopter
    ${simulation_quadcopter_src}
    )   
endif()
