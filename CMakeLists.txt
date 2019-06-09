cmake_minimum_required(VERSION 3.14)
project(library_management)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTORCC ON)


find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Sql REQUIRED)

set(SOURCES main.cpp Content.cpp
        Login.cpp BookQuery.cpp CardManagement.cpp Borrow.cpp
        Return.cpp Book.cpp DBOperation.cpp)
set(HEADERS Content.h Login.h MQListWidget.h
        BookQuery.h DBOperation.h CardManagement.h ReadOnlyDelegate.h
        Borrow.h Return.h Book.h)
#set(UI)
#set(RESOURCES)

add_executable(library_management
        ${SOURCES} ${HEADERS} ${UI} ${RESOURCES})

target_link_libraries(library_management
        Qt5::Core
        Qt5::Gui
        Qt5::Sql
        Qt5::Widgets
        )
