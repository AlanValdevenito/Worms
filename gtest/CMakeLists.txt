cmake_minimum_required(VERSION 3.13)

project(googletest-distribution)
set(GOOGLETEST_VERSION 1.14.0)

if(NOT CYGWIN AND NOT MSYS AND NOT ${CMAKE_SYSTEM_NAME} STREQUAL QNX)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

enable_testing()

include(CMakeDependentOption)
include(GNUInstallDirs)

# Note that googlemock target already builds googletest.
option(BUILD_GMOCK "Builds the googlemock subproject" ON)
option(INSTALL_GTEST "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" ON)
option(GTEST_HAS_ABSL "Use Abseil and RE2. Requires Abseil and RE2 to be separately added to the build." OFF)

if(BUILD_GMOCK)
  add_subdirectory( googlemock )
else()
  add_subdirectory( googletest )
endif()

file(GLOB TEST *.cpp *.$(extension))

file(GLOB COMMON_SOURCES ../common/*.cpp *.$(extension))
file(GLOB COMMON_HEADERS ../common/*.h)

file(GLOB DTO_SOURCES ../common/Dtos/*.cpp *.$(extension))
file(GLOB DTO_HEADERS ../common/Dtos/*.h)

file(GLOB CLIENT_SOURCES ../client/client_protocol.cpp *.$(extension))
file(GLOB CLIENT_HEADERS ../client/Client_protocol.h)

list(APPEND TEST ${DTO_HEADERS} ${COMMON_HEADERS} ${CLIENT_HEADERS} ${DTO_SOURCES} ${COMMON_SOURCES} ${CLIENT_SOURCES})

# Agrega el nuevo archivo de prueba
# add_executable(my_test my_test.cpp)
add_executable(my_test ${TEST})

# Enlaza el nuevo archivo de prueba con Google Test
target_link_libraries(my_test gtest_main)

# Define el test
add_test(NAME MyTest COMMAND my_test)
