#####################################################################
# simple AVR library
#####################################################################
file(GLOB simulation_model_src
    "*.cpp"
    "*.hpp"
)
if(BUILD_TYPE STREQUAL "PC")
    add_library (
    simulation_model
    ${simulation_model_src}
    )   
endif()
