cmake_minimum_required(VERSION 3.12)

project(xlib-example)

include_directories(${PROJECT_SOURCE_DIR}/gui/)
include_directories(${PROJECT_SOURCE_DIR}/)

FILE(GLOB GUI
    ${PROJECT_SOURCE_DIR}/gui/*
)

add_executable(${PROJECT_NAME} ${GUI} main.cpp)

target_link_libraries(${PROJECT_NAME} X11)
