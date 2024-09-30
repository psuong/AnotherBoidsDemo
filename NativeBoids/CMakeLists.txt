cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (NativeBoids)

find_package(fmt CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Catch2 REQUIRED)

add_compile_definitions(DEBUG_EXPORTS)
add_compile_definitions(BOID_EXPORTS)

set(SOURCE_DIR "src")
set(HEADERS_DIR "headers")

file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")
file(GLOB HEADERS "${HEADERS_DIR}/*.h")

# Add source to this project's library.
# add_library(NativeBoids SHARED 
#     "headers/native_boids.h"
#     "headers/simple_logger.h"
#     "headers/entity.h"
#     "headers/fixed_buffer.h"
#     "src/native_boids.cpp"
#     "src/simple_logger.cpp"
#     "src/fixed_buffer.cpp")

add_library(NativeBoids SHARED ${SOURCES} ${HEADERS})

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET NativeBoids PROPERTY CXX_STANDARD 17)
endif()

enable_testing()
add_executable(tests "tests/main.cpp")

# TODO: Add tests and install targets if needed.
target_link_libraries(NativeBoids PRIVATE fmt::fmt)
target_link_libraries(NativeBoids PRIVATE glm::glm)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

add_test(NAME MyTests COMMAND tests)
