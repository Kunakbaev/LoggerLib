cmake_minimum_required(VERSION 3.10)
project(my_loglib VERSION 1.0.0 LANGUAGES CXX)

# Include required CMake modules
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler warnings (equivalent to your extensive warning flags)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wchar-subscripts -Wconditionally-supported -Wconversion")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat-security -Wformat-signedness -Wformat=2 -Winline")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-overflow=2 -Wsuggest-attribute=noreturn")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-old-style-cast -Wno-varargs -Wstack-protector")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcheck-new -fsized-deallocation -fstack-protector")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=vla")

# Debug-specific flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_DEBUG -ggdb3 -O0 -pie -fPIE")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNDEBUG")
endif()

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
