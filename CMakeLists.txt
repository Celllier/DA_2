cmake_minimum_required(VERSION 3.30)
project(DA_2)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(DA_2 main.cpp
        include/Menu.h
        include/InputHandler.h
        src/InputHandler.cpp
        src/Menu.cpp
        include/RequestProcessor.h
        src/RequestProcessor.cpp
        src/Algorithms.cpp
        include/Algorithms.h
        include/Utils.h
        src/Utils.cpp
)
