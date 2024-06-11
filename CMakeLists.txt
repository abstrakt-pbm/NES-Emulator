cmake_minimum_required (VERSION 3.8)


project ("Nemo")

set( SFML_DIR "dependencies/SFML/lib/cmake/SFML" )
set(SFML_STATIC_LIBRARIES TRUE)
add_executable (main "main.cpp")

add_subdirectory(nes)
find_package(SFML REQUIRED COMPONENTS window)
target_link_libraries(main NES sfml-window )