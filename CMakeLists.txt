cmake_minimum_required (VERSION 3.8)


project ("NES-Emulator")


set( CMAKE_CXX_STANDARD 20 )

add_executable ( nes_emulator "main.cpp" )

add_subdirectory(nes)
add_subdirectory(dependencies)
target_link_libraries(nes_emulator NES )
