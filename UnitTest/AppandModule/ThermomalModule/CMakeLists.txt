cmake_minimum_required(VERSION 3.10.0)

project(main)# 工程名

find_package(Threads REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /home/group36/pigpio-master/util)

find_package(pigpio REQUIRED)

include_directories(${PIGPIO_INCLUDE_DIRS}) #包含头文件目录


set(CMAKE_CXX_STANDARD 11) # use c++11 standard

# Test thermalModule
add_executable(${PROJECT_NAME}
              ${PROJECT_SOURCE_DIR}/taskQueue.hpp
              ${PROJECT_SOURCE_DIR}/app.cpp
              ${PROJECT_SOURCE_DIR}/threadPool.cpp
              ${PROJECT_SOURCE_DIR}/pwmctrl.cpp
              ${PROJECT_SOURCE_DIR}/heater.cpp
              ${PROJECT_SOURCE_DIR}/myds18b20.cpp
              ${PROJECT_SOURCE_DIR}/thermalModule.cpp
              ${PROJECT_SOURCE_DIR}/Test_thermalModule.cpp
              )

target_link_libraries(${PROJECT_NAME} pthread)

target_link_libraries(${PROJECT_NAME} pigpio)
