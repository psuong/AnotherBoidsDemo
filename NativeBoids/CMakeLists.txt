# CMakeList.txt : CMake project for NativeBoids, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("NativeBoids")

add_compile_definitions(DEBUG_EXPORTS)
add_compile_definitions(BOID_EXPORTS)

# Add source to this project's library.
add_library(NativeBoids SHARED "NativeBoids.cpp" "NativeBoids.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET NativeBoids PROPERTY CXX_STANDARD 17)
endif()

# TODO: Add tests and install targets if needed.
