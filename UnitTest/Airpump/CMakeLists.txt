cmake_minimum_required(VERSION 3.10.0)

project(main)# 工程名

find_package(Threads REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /home/group36/pigpio-master/util) # help 'find_package' to find lib

find_package(pigpio REQUIRED)

include_directories(${PIGPIO_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include) #包含头文件目录

link_directories(${PIGPIO_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11) # use c++11 standard

# Test_waterpump
add_executable(${PROJECT_NAME} 
              ${PROJECT_SOURCE_DIR}/Test_airpump.cpp
              ${PROJECT_SOURCE_DIR}/pwmctrl.cpp
              ${PROJECT_SOURCE_DIR}/airpump.cpp
              )

target_link_libraries(${PROJECT_NAME} pthread)

target_link_libraries(${PROJECT_NAME} pigpio)
