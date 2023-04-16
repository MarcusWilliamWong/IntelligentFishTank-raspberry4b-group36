cmake_minimum_required(VERSION 3.10.0)

# set( CMAKE_CXX_COMPILER "D:/Softwares/C_Compile/mingw64/bin/g++.exe" )  

# set( CMAKE_C_COMPILER "D:/Softwares/C_Compile/mingw64/bin/gcc.exe" )  

project(main)# 工程名

find_package(Threads REQUIRED) # find thread lib # dynamic lib from /usr/lib/arm-linux-gnueabihf/lib/libpthread.so

# find_package(WiringPi REQUIRED)  #find wiringpi

# include_directories(${WIRINGPI_INCLUDE_DIRS}) # include wiringpi header

#### include(${PROJECT_SOURCE_DIR}/pigpio/util/Findpigpio.cmake) # include Findpigpio.cmake to find pigpio library

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /home/group36/pigpio-master/util) # help 'find_package' to find lib

find_package(pigpio REQUIRED)

include_directories(${PIGPIO_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include) #包含头文件目录

link_directories(${PIGPIO_INCLUDE_DIRS})

# find_library(WIRINGPI_LIBRARIES NAMES wiringPi)

#find_library(PIGPIO_LIBRARIES NAMES pigpio)

#find_library(pthread_lib)

# include_directories(${PROJECT_SOURCE_DIR}/include) 

# file(GLOB SOURCE "src/*.cpp" "main.cpp")# 源文件下所有的 cpp文件 和主程序

set(CMAKE_CXX_STANDARD 11) # use c++11 standard

#add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/myds18b20.cpp ${PROJECT_SOURCE_DIR}/samples/Test_DS18B20.cpp) # ${CMAKE_THREAD_LIBS_INIT}


# Test_threadPool
# add_executable(${PROJECT_NAME} 
#               ${PROJECT_SOURCE_DIR}/include/taskQueue.hpp
#               ${PROJECT_SOURCE_DIR}/src/threadPool.cpp
#               ${PROJECT_SOURCE_DIR}/samples/Test_threadPool.cpp
#               )

# Test thermalModule
# add_executable(${PROJECT_NAME}
#               ${PROJECT_SOURCE_DIR}/include/taskQueue.hpp
#               ${PROJECT_SOURCE_DIR}/src/app.cpp
#               ${PROJECT_SOURCE_DIR}/src/threadPool.cpp
#               ${PROJECT_SOURCE_DIR}/src/pwmctrl.cpp
#               ${PROJECT_SOURCE_DIR}/src/heater.cpp
#               ${PROJECT_SOURCE_DIR}/src/myds18b20.cpp
#               ${PROJECT_SOURCE_DIR}/src/thermalModule.cpp
#               ${PROJECT_SOURCE_DIR}/samples/Test_thermalModule.cpp
#               )

# Test bluetooth
# add_executable(${PROJECT_NAME}
#               ${PROJECT_SOURCE_DIR}/src/bluetooth.cpp
#               ${PROJECT_SOURCE_DIR}/samples/Test_bluetooth.cpp
#               )

# add_executable(${PROJECT_NAME}
#               ${PROJECT_SOURCE_DIR}/samples/Test_VEML7700.cpp
#               ${PROJECT_SOURCE_DIR}/src/VEML7700.cpp
#               )

# Test app->runBluetooth
# add_executable(${PROJECT_NAME}
#               ${PROJECT_SOURCE_DIR}/include/taskQueue.hpp
#               ${PROJECT_SOURCE_DIR}/src/app.cpp
#               ${PROJECT_SOURCE_DIR}/src/threadPool.cpp
#               ${PROJECT_SOURCE_DIR}/src/pwmctrl.cpp
#               ${PROJECT_SOURCE_DIR}/src/waterpump.cpp
#               # ${PROJECT_SOURCE_DIR}/src/heater.cpp
#               # ${PROJECT_SOURCE_DIR}/src/myds18b20.cpp
#               # ${PROJECT_SOURCE_DIR}/src/thermalModule.cpp
#               # ${PROJECT_SOURCE_DIR}/samples/Test_thermalModule.cpp
#               ${PROJECT_SOURCE_DIR}/src/bluetooth.cpp
#               ${PROJECT_SOURCE_DIR}/samples/Test_app_runBluetooth.cpp
#               )

# message(${PROJECT_SOURCE_DIR})
# add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/samples/Test_pigpio.cpp)

# Test_airpump
# add_executable(${PROJECT_NAME} 
#               ${PROJECT_SOURCE_DIR}/samples/Test_airpump.cpp
#               ${PROJECT_SOURCE_DIR}/src/pwmctrl.cpp
#               ${PROJECT_SOURCE_DIR}/src/airpump.cpp
#               )

# Test_waterpump
add_executable(${PROJECT_NAME} 
              ${PROJECT_SOURCE_DIR}/samples/Test_waterpump.cpp
              ${PROJECT_SOURCE_DIR}/src/pwmctrl.cpp
              ${PROJECT_SOURCE_DIR}/src/waterpump.cpp
              )


# Test_myds18b20
# add_executable(${PROJECT_NAME} 
#               ${PROJECT_SOURCE_DIR}/samples/Test_DS18B20.cpp 
#               ${PROJECT_SOURCE_DIR}/src/myds18b20.cpp
#               ${PROJECT_SOURCE_DIR}/src/heater.cpp
#               ${PROJECT_SOURCE_DIR}/src/pwmctrl.cpp)

# Test_heater.cpp
# add_executable(${PROJECT_NAME} 
#               ${PROJECT_SOURCE_DIR}/samples/Test_heater.cpp 
#               ${PROJECT_SOURCE_DIR}/src/heater.cpp
#               ${PROJECT_SOURCE_DIR}/src/pwmctrl.cpp
#               )

# VEML7700_Gain
# add_executable(${PROJECT_NAME} 
#               ${PROJECT_SOURCE_DIR}/include/taskQueue.hpp
#               ${PROJECT_SOURCE_DIR}/src/threadPool.cpp
#               ${PROJECT_SOURCE_DIR}/samples/Test_threadPool.cpp
#               )

# target_link_libraries(${PROJECT_NAME} ${WIRINGPI_LIBRARIES})

target_link_libraries(${PROJECT_NAME} pthread)

target_link_libraries(${PROJECT_NAME} pigpio)

# target_link_libraries(${PROJECT_NAME} wiringPi)

# message(STATUS ${PIGPIO_LIBRARIES})

# target_link_libraries(${PROJECT_NAME} ${WIRINGPI_LIBRARIES})

# 需要执行的cpp才写在这里面 class这种不需要执行的cpp就不用写在这里面
