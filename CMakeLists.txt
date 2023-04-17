cmake_minimum_required(VERSION 3.10.0)

project(main)

find_package(Threads REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /home/group36/pigpio-master/util)

find_package(pigpio REQUIRED)

include_directories(${PIGPIO_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)

link_directories(${PIGPIO_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME}
              ${PROJECT_SOURCE_DIR}/main.cpp
              ${PROJECT_SOURCE_DIR}/src/app.cpp
              ${PROJECT_SOURCE_DIR}/include/taskQueue.hpp
              ${PROJECT_SOURCE_DIR}/src/threadPool.cpp
              ${PROJECT_SOURCE_DIR}/src/bluetooth.cpp
              ${PROJECT_SOURCE_DIR}/src/pwmctrl.cpp
              ${PROJECT_SOURCE_DIR}/src/heater.cpp
              ${PROJECT_SOURCE_DIR}/src/airpump.cpp
              ${PROJECT_SOURCE_DIR}/src/waterpump.cpp
              ${PROJECT_SOURCE_DIR}/src/pumpModule.cpp
              ${PROJECT_SOURCE_DIR}/src/thermometer.cpp
              ${PROJECT_SOURCE_DIR}/src/module.cpp
              ${PROJECT_SOURCE_DIR}/src/thermalModule.cpp
              )

target_link_libraries(${PROJECT_NAME} pthread)

target_link_libraries(${PROJECT_NAME} pigpio)

target_link_libraries(${PROJECT_NAME} atomic)