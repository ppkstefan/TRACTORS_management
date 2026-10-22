cmake_minimum_required(VERSION 3.16)
project(TRACTOARE)

# Setăm standardul C++ la 17
set(CMAKE_CXX_STANDARD 17)

# Activăm compilatoarele specifice Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# IMPORTANT: Calea către Qt trebuie setată ÎNAINTE de find_package
set(CMAKE_PREFIX_PATH "C:/Qt/6.11.0/mingw_64")

# Căutăm pachetul Qt6
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

# Includem folderele
include_directories(DOMAIN)
include_directories(GUI)
include_directories(REPOSITORY)
include_directories(SERVICE)

# Creăm executabilul (Nume cu litere mari)
add_executable(TRACTOARE
        DOMAIN/Tractor.cpp
        DOMAIN/Tractor.h
        GUI/TractorGUI.cpp
        GUI/TractorGUI.h
        GUI/TractorTableModel.cpp
        GUI/TractorTableModel.h
        GUI/WheelsWidget.h
        REPOSITORY/TractorRepo.cpp
        REPOSITORY/TractorRepo.h
        SERVICE/TractorService.cpp
        SERVICE/TractorService.h
        main.cpp)

# Legăm bibliotecile de executabil (Folosim exact același nume: TRACTOARE)
target_link_libraries(TRACTOARE PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)