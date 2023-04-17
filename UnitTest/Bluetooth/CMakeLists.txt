cmake_minimum_required(VERSION 3.10.0)

project(main)# 工程名

find_package(Threads REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /home/group36/pigpio-master/util)

find_package(pigpio REQUIRED)

include_directories(${PIGPIO_INCLUDE_DIRS}) #包含头文件目录


set(CMAKE_CXX_STANDARD 11) # use c++11 standard

# Test bluetooth
add_executable(${PROJECT_NAME}
              ${PROJECT_SOURCE_DIR}/bluetooth.cpp
              ${PROJECT_SOURCE_DIR}/Test_bluetooth.cpp
              )

target_link_libraries(${PROJECT_NAME} pthread)

target_link_libraries(${PROJECT_NAME} pigpio)
