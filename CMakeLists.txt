cmake_minimum_required(VERSION 3.14)

project(test LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(test WIN32
  src/main.cpp
)

target_link_libraries(test Qt6::Core Qt6::Widgets Qt6::Gui)