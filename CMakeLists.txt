cmake_minimum_required (VERSION 3.8)


project ("Nemo")


set( CMAKE_CXX_STANDARD 20 )

add_executable ( nemo "main.cpp"  "gui/src/screen.cpp" "gui/include/screen.h")

add_subdirectory(nes)
add_subdirectory(dependencies)
target_link_libraries(nemo NES Logger )
