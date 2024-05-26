# CMakeList.txt : CMake project for Nemo, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Nemo")

# Add source to this project's executable.
add_executable (Nemo "Nemo.cpp"  "Hardware/Processing-Units/include/cpu.h" "Hardware/Processing-Units/include/ppu.h" "Hardware/Processing-Units/include/apu.h" "Hardware/Processing-Units/src/cpu.cpp" "Hardware/Processing-Units/src/ppu.cpp" "Hardware/Processing-Units/src/apu.cpp" "Hardware/Processing-Units/include/cpu-op-codes.h" "Hardware/Processing-Units/include/bus.h" "Hardware/Processing-Units/src/bus.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Nemo PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
