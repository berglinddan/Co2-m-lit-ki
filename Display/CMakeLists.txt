add_library(Display INTERFACE)

target_sources(Display INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/Display.cpp
)

target_include_directories(Display INTERFACE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(Display INTERFACE)