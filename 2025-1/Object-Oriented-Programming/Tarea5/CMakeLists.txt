cmake_minimum_required(VERSION 3.10)
project(SistemaFinanciero)

set(CMAKE_CXX_STANDARD 11)

add_executable(sistema_financiero
        main.cpp
        Usuario.cpp
        TablaHash.cpp
)

