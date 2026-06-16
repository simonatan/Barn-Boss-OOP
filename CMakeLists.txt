cmake_minimum_required(VERSION 4.1)
project(oop_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(models engine services utils)

file(GLOB MODELS_SRC   models/*.cpp)
file(GLOB ENGINE_SRC   engine/*.cpp)
file(GLOB SERVICES_SRC services/*.cpp)
file(GLOB UTILS_SRC    utils/*.cpp)

add_executable(oop_project src/main.cpp
        ${MODELS_SRC}
        ${ENGINE_SRC}
        ${SERVICES_SRC}
        ${UTILS_SRC}
)