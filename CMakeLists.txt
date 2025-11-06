cmake_minimum_required(VERSION 3.10)
project(my_loglib VERSION 1.0.0 LANGUAGES CXX)

# Include required CMake modules
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------    set compilation flags   ----------------

# basic flags for compilation and debugging
set(DEBUG_FLAGS -ggdb3 -fno-omit-frame-pointer)

# general warnings
set(WARNING_FLAGS -Wall -Wextra -Wpedantic)

# security flags
set(SECURITY_FLAGS -fstack-protector -pie -fPIE -Wformat=2 -Wformat-security)

# specific flags
set(CPP_SPECIFIC_FLAGS -Wnon-virtual-dtor -Woverloaded-virtual)

set(COMMON_CXX_FLAGS ${WARNING_FLAGS})

# ------------    specifying compilation options based on build type    ------------

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  add_compile_definitions(NO_LOG NDEBUG)
  set(COMPILATION_FLAGS ${COMMON_CXX_FLAGS} -O2 -DNDEBUG)
  message(STATUS "Building in Release mode")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(_DEBUG)
  set(COMPILATION_FLAGS ${COMMON_CXX_FLAGS} -O0 -g ${SECURITY_FLAGS} ${CPP_SPECIFIC_FLAGS})
  message(STATUS "Building in Debug mode")
endif()

# ------------------------------------------------------------

# Find source files
file(GLOB SRC_FILES "source/*.cpp")

# Create shared library
add_library(my_loglib SHARED ${SRC_FILES})
target_link_libraries(my_loglib m)  # -lm equivalent

# Set library properties
set_target_properties(my_loglib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    POSITION_INDEPENDENT_CODE ON
)

# Include directories (if you have headers)
target_include_directories(my_loglib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Create the test executable (equivalent to your LIB_RUN_NAME)
add_executable(loggingLib_test source/example.cpp)  # Assuming you have a main.cpp for testing
target_link_libraries(loggingLib_test my_loglib)

# Installation (modern, safe approach)
include(GNUInstallDirs)

install(TARGETS my_loglib
    EXPORT my_loglibTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES include/logLib.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export for use in parent projects (Option 3 approach)
install(EXPORT my_loglibTargets
    FILE my_loglibConfig.cmake
    NAMESPACE my_loglib::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/my_loglib
)

# Create a package configuration file
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/my_loglibConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/my_loglibConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/my_loglib
)

# 3. Устанавливаем оба файла
install(EXPORT my_loglibTargets
    FILE my_loglibTargets.cmake
    NAMESPACE my_loglib::
    DESTINATION lib/cmake/my_loglib
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/my_loglibConfig.cmake
    DESTINATION lib/cmake/my_loglib
)

# pkg-config support (optional but useful)
# configure_file(libmy_loglib.pc.in libmy_loglib.pc @ONLY)
# install(
#     FILES ${CMAKE_CURRENT_BINARY_DIR}/libmy_loglib.pc
#     DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
# )

# export(EXPORT my_loglibTargets
#     FILE "${CMAKE_CURRENT_BINARY_DIR}/my_loglibTargets.cmake"
#     NAMESPACE my_loglib::
# )
