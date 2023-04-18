add_library(SCD42 INTERFACE)

target_sources(SCD42 INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/SCD42.cpp
)

target_include_directories(SCD42 INTERFACE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(SCD42 INTERFACE hardware_i2c)