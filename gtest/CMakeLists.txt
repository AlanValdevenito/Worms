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

# Agrega el nuevo archivo de prueba
add_executable(my_test my_test.cpp)

# Agrega las carpetas common, server y client al directorio de inclusión
target_include_directories(my_test PRIVATE ${CMAKE_SOURCE_DIR}/../common)
target_include_directories(my_test PRIVATE ${CMAKE_SOURCE_DIR}/../common/Dtos)
target_include_directories(my_test PRIVATE ${CMAKE_SOURCE_DIR}/../server)
target_include_directories(my_test PRIVATE ${CMAKE_SOURCE_DIR}/../client)

# Enlaza el nuevo archivo de prueba con Google Test
target_link_libraries(my_test gtest_main)

# Define el test
add_test(NAME MyTest COMMAND my_test)
