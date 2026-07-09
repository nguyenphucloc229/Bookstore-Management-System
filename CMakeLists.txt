cmake_minimum_required(VERSION 3.16)
project(BookstoreManagement VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
)

qt_add_executable(BookstoreManagement ${PROJECT_SOURCES})

target_include_directories(BookstoreManagement PRIVATE src)
target_link_libraries(BookstoreManagement PRIVATE Qt6::Widgets Qt6::Sql)
