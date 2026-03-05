cmake_minimum_required(VERSION 3.16)
project(HexEditorQt LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(HexEditorQt
    src/main.cpp
    src/MainWindow.cpp
    src/MainWindow.h
    src/filemanager.cpp
    src/converter.cpp
)

target_include_directories(HexEditorQt PRIVATE include src)

target_link_libraries(HexEditorQt PRIVATE Qt6::Widgets)