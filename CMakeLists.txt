cmake_minimum_required(VERSION 3.10.0)

# set( CMAKE_CXX_COMPILER "D:/Softwares/C_Compile/mingw64/bin/g++.exe" )  

# set( CMAKE_C_COMPILER "D:/Softwares/C_Compile/mingw64/bin/gcc.exe" )  

project(main)# 工程名

find_package(Threads REQUIRED) # find thread lib # dynamic lib from /usr/lib/arm-linux-gnueabihf/lib/libpthread.so

#### include(${PROJECT_SOURCE_DIR}/pigpio/util/Findpigpio.cmake) # include Findpigpio.cmake to find pigpio library

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /home/group36/pigpio-master/util)

find_package(pigpio REQUIRED)

include_directories(${PIGPIO_INCLUDE_DIRS})

link_directories(${PIGPIO_INCLUDE_DIRS})

# find_library(WIRINGPI_LIBRARIES NAMES wiringPi)

#find_library(PIGPIO_LIBRARIES NAMES pigpio)

#find_library(pthread_lib)

include_directories(${PROJECT_SOURCE_DIR}/include) #包含头文件目录

# file(GLOB SOURCE "src/*.cpp" "main.cpp")# 源文件下所有的 cpp文件 和主程序

set(CMAKE_CXX_STANDARD 11) # use c++11 standard

#add_executable(main ${PROJECT_SOURCE_DIR}/src/myds18b20.cpp ${PROJECT_SOURCE_DIR}/samples/Test_DS18B20.cpp) # ${CMAKE_THREAD_LIBS_INIT}

add_executable(main ${PROJECT_SOURCE_DIR}/src/app.cpp ${PROJECT_SOURCE_DIR}/src/airpump.cpp ${PROJECT_SOURCE_DIR}/src/pwmctrl.cpp ${PROJECT_SOURCE_DIR}/samples/Test_airpump.cpp) # ${CMAKE_THREAD_LIBS_INIT}

# target_link_libraries(main ${WIRINGPI_LIBRARIES})

target_link_libraries(main pthread)

target_link_libraries(main ${PIGPIO_LIBRARIES})

# 需要执行的cpp才写在这里面 class这种不需要执行的cpp就不用写在这里面
