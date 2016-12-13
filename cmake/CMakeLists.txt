cmake_minimum_required (VERSION 2.6)
project(hello)

set(APPNAME hello)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

add_executable(${APPNAME} main.cpp)
find_program(OBJCOPY objcopy)
# debug
if(CMAKE_COMPILER_IS_GNUCC)
if(${CMAKE_BUILD_TYPE} MATCHES Debug)
message(STATUS "Will make separate debug symbols in *.debug")
add_custom_command(TARGET ${APPNAME} POST_BUILD
COMMAND ${OBJCOPY} --only-keep-debug $<TARGET_FILE:${APPNAME}> $<TARGET_FILE:${APPNAME}>.debug
COMMAND ${OBJCOPY} --strip-debug $<TARGET_FILE:${APPNAME}>
COMMAND ${OBJCOPY} --add-gnu-debuglink=$<TARGET_FILE_NAME:${APPNAME}>.debug $<TARGET_FILE:${APPNAME}>
)
endif()
endif()
