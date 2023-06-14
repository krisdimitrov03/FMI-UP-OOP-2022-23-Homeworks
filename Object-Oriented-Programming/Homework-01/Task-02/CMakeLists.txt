cmake_minimum_required(VERSION 3.24)
project(HWTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(HWTest main.cpp
        constants.h
        DateTime.cpp
        DateTime.h
        main-02.cpp
        main-02.h
        Role.h
        TextFile.cpp
        TextFile.h
        TextFilesManager.cpp
        TextFilesManager.h
        Outside_Resources/Date.h
        Outside_Resources/Date.cpp
        Outside_Resources/Time.cpp
        Outside_Resources/Time.h Operations.h)
