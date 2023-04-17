#  Intelligent Fish Tank

<div align="center">
<img src="assets\Tank.png" style="zoom:100%;" /> 
</div>


README Language: [English](./README.md) ｜ [中文](./README-zh.md)

>[Visit Instgram account](https://instagram.com/haagendazs85?igshid=YmMyMTA2M2Y=)  
>[Visit Youtube account](https://www.youtube.com/channel/UC8SZ1dN7v9y7iaWZyjrDwrA)

 # 1 Project description

Our smart fish tank project is a system with the Raspberry Pi 4B as the core controller. It mainly has functions such as temperature control, oxygen level maintenance and water flow rate adjustment. The user can check the temperature and set a target temperature range on the mobile phone, as well as control the amount of bubbles and the water flow rate. Our project is written in C++11, built using Cmake and runs on Raspbian GNU/Linux 11.

## 1.1 Project functions

### 1.1.1 Temperature control - settable range

Different species of fish require different water temperatures. This system uses a temperature sensor and a heater, both of which work together to control the temperature in the water around a set value. The user can set a target temperature range. During the operation of the system, the temperature sensor data is first read using a Raspberry Pi and the temperature data is compared with the set range. If the current temperature is below the set temperature range, the heater is controlled to heat the water, and the heating stops when the temperature is detected to reach the predetermined value. During the heating process, the temperature in the waters will always participate in the temperature regulation as a feedback value.

### 1.1.2 Dissolved oxygen maintenance - Adjustable speed air pump

The system uses a PWM regulated electronic switch control board to control the operating power of the air pump. The user can set the required operating gear.

### 1.1.3 Natural Environment Simulation - Adjustable Flow Rate Control

Life is about movement. A calm current is not at all attractive to fish. This system uses a PWM regulated electronic switch control board to control the operating power of the air pump. The user can set the desired working level, which makes the fish swimming posture more beautiful and feeding more convenient.

### 1.1.4 Mobile control

Everything mentioned above does not require the user to debug the Raspberry Pi or modify the parameters in the code, but rather use our mobile application designed on Flutter to conveniently transfer parameters by Bluetooth, set the holding range, heating power, bubble volume and water flow speed.

## 1-2 Project contributors

| Name         | Student ID |
| ------------ | ---------- |
| Haoshi Huang | 2635088H   |
| Xintong LIN  | 2824115L   |
| Hanwei Liang | 2669523L   |
| Chaoyi Yang  | 2724184Y   |

## 1-3 Project planning
> [GanttChart](.assets/GanttChart.xlsx)  
>[MEMORANDUM OF MEETING](.assets/meeting/) 

<div align="center">
<img src="assets\GanttChart.png" style="zoom:100%;" /> 
</div>
<p align="center">GanttChart</p>  

## 1-4 Test video

<div align="center">
<img src="assets\Test.gif" style="zoom:100%;" /> 
</div>

<p align="center">Test video</p>  

# 2 Software and hardware information

## 2.1 Systems and Controllers

The Raspberry Pi 4B is a miniature computer based on the ARM architecture. It uses the BCM2711 chip with integrated GPU and CPU from Broadcom, supports 4K resolution video output, up to 4GB of LPDDR4-3200 SDRAM memory, Gigabit Ethernet, dual-band WiFi, Bluetooth 5.0 and many other interfaces and protocols. It also has two Micro-HDMI ports, two USB 3.0 ports, two USB 2.0 ports, a 40-pin GPIO port, a 2-pin power connector and more.

<div align="center">
<img src="assets\RaspberryPi4B.jpg" style="zoom:50%;" /> 
</div>

<p align="center">Raspberry Pi 4B</p>  

#### 2.1.1 Host side

OS: Raspbian GNU/Linux 11 (bullseye-armlf)

Hardware configuration: Raspberry Pi 4B (Broadcom BCM2711), Quad core Cortex-A72 (ARM v8) 64-bit

Programming language related:

- Development tool: Visual Studio Code 1.76.0
- Compiler version: g++ 10.2.1 (Raspbian 10.2.1-6+rpi1) 
- CMAKE version: cmake 3.18.4
- Coding specification: Google C++ coding specification

Dependency libraries:

- C++ Standard Template Library (STL)

- pigpio v79

  

### 2.1.2 Client

Hardware configuration: Hisilicon Kirin 710F (4.0 GB)

Operating system: HarmonyOs 2.0.0

Programming language related:

- Programming language: Dart 2.17
- Development tools: Android Studio 2022.2.1.18 for Windows
- Software development kit: commandlinetools-9477386 for Windows
- Front-end framework: Flutter 3.0



## 2.2 Power supply

At the same power level, higher voltages result in lower currents, while lower voltages result in higher currents, which can lead to more serious heating, and after considering safety and the power requirements of other system components, we decided to use a 24V heater for heating.

A constant voltage DC power supply called the DT-NT24V was chosen to supply the heater, which converts 230V AC to 24V low voltage DC. It is a compact power supply with a honeycomb heat sink design, a translucent cover to protect the terminals, overvoltage, overheat, overcurrent and short circuit protection, low current output, low voltage ripple and low noise operation. It can deliver up to 6.25 amps and can reach 150 watts of power.

<div align="center">
<img src="assets\PowerSupply.png" style="zoom:50%;" /> 
</div> 
<p align="center">Power supply</p>  

## 2.3 Voltage converters

We use a DC-DC buck based on the LM2596S regulator design, where the output voltage can be adjusted via an external divider resistor over a range of 1.23V to 37V when the input voltage is 4.0V to 40V. At the same time, the output current is 2 Amps (normally stable) and a maximum of 3 Amps, which is sufficient to drive many electronic devices. It can achieve a conversion efficiency of 92% with an output ripple of less than 30mV, a switching frequency of 150KHz and an operating temperature of -45 to 85 degrees Celsius. To improve the stability of the system, we equip each system with a separate power supply.

<div align="center">
<img src="assets\VoltageConvertor.png" style="zoom:70%;" /> 
</div>
<p align="center">LM2596S Voltage converters</p>  

## 2.4 PWM regulation electronic switch control board

PWM (Pulse Width Modulation) is a technology that is widely used in electronics and communications. It adjusts the RMS value of a signal or power supply by controlling the width of the pulse waveform (i.e. the duration of the pulse). In a PWM signal, the ratio of the pulse width (duty cycle) is proportional to the analogue signal or output voltage being represented. The duty cycle is the ratio of the time occupied by the high state to the entire cycle time during a complete PWM cycle. The duty cycle typically ranges from 0% (all low) to 100% (all high). We use PWM technology to achieve control of heaters, air pumps and water pumps. By adjusting the duty cycle of the PWM signal, we can precisely control the speed and torque of the motor.

We use this PWM regulated electronic switch control board to regulate 5V-36V DC, using DC between 3.3V-20V for triggering, continuous current up to 15A and power up to 400W with good heat dissipation. this PWM regulated electronic switch control board uses double MOS parallel active output, with low internal resistance and high power, supporting PWM signals with frequencies between 0 - 20KHZ.

<div align="center">
<img src="assets\MotorControl.png" style="zoom:100%;" /> 
</div>
<p align="center">PWM regulation electronic switch control board</p>  

## 2.5 Air pump

Air pumps play an important role in fish tanks by producing air bubbles that transport oxygen from the air to the tank water. When the bubbles burst, oxygen is released into the water, thus providing sufficient oxygen for the fish. Adequate oxygen is vital for the growth, metabolism and survival of fish. The air bubbles produced by the air pump circulate the water as they rise. The circulation of water helps to distribute nutrients, waste and oxygen in the water evenly throughout the tank, making it a more pleasant environment for fish. The oxygen provided by the air pump helps the growth of beneficial bacteria. These bacteria break down toxic substances such as ammonia and nitrites in fish excreta and convert them into harmless nitrates. This helps to maintain stable water quality in the tank and provides a healthy living environment for the fish.

This air pump weighs about 150g, uses a booster electric ceramic motor, is powered by a 5V power supply, consumes about 1W and has a maximum flow rate of 210L/H. It has a stable oxygen supply, low heat generation and low noise.

We have set up five speed levels, including off, through PWM, so that the user can select the desired speed level on the mobile.

 <div align="center">
<img src="assets\AirPump.png" style="zoom:50%;" /> 
</div>
<p align="center">Air pump</p>  

## 2.6 Water pump

The water pump circulates the water, which helps the oxygen, nutrients and waste in the water to be evenly distributed within the tank, thus providing a comfortable living environment for the fish. The water pump transports waste from the water to the filter, increasing the efficiency of the filter and helping to maintain water quality. The water flow generated by the pump helps to simulate the water flow in a natural environment, creating a good ecological balance in the fish tank. This is important for the growth and reproduction of fish and the stability of the entire fish tank ecosystem. The water flow generated by the pump can drive decorative objects in the tank, such as simulated water plants and fountains, adding a dynamic and aesthetic effect to the tank.

The pump is 38mm long, 38mm wide, 29mm high, weighs about 125g and is driven by DC power from 4.5V~12V. The water flow can reach 100~350L/H and the power can reach 0.5~5W. It can work quietly at a sound level below 40db and is attached to the surface of the fish tank by suction cups.

We implement a graded speed regulation for the pump via PWM, setting five speed levels including off, and the user can select the desired speed level on the mobile.

  <div align="center">
<img src="assets\WaterPump.jpg" style="zoom:60%;" /> 
</div>
<p align="center">Water pump</p>  

## 2.7 Immersion resistance heater

The immersion resistance heater is a device that uses the principle of resistance heating to heat water. It is mainly composed of resistance heating elements, housing, temperature controller and insulating material and other parts. In the heater, the resistance heating element is the core component, which converts electrical energy into heat energy, thus realising the heating of the water. At the same time, the resistance heating element is in direct contact with the water, and the heat transfer efficiency is high, so the heating speed is faster. When the current passes through the resistance heating element, the current generates Joule heat due to the resistance of the resistance element. This heat is transferred to the water, causing the water temperature to rise. By adjusting the duty cycle of the PWM signal, the amount of heat generated by the heating element can be controlled and thus the water temperature can be controlled.

The heaters we use can operate at 24 V and can reach a maximum power of 140 Watts.

  <div align="center">
<img src="assets\Heater.png" style="zoom:50%;" /> 
</div>
<p align="center">Immersion resistance heater</p>  

## 2.8 temperature sensor

The DS18B20 is a digital temperature sensor capable of measuring temperatures in the range -55°C to +125°C. The DS18B20 is capable of measuring temperatures in the range -10°C to +85°C with an accuracy of ±0.5°C. It converts the measured temperature value into a digital signal for digital applications such as microcontrollers. It converts the measured temperature value into a digital signal that can be read and processed by digital devices such as microcontrollers. The DS18B20 communicates with the microcontroller using a single data line (1-Wire protocol), simplifying wiring and reducing hardware costs.

  <div align="center">
<img src="assets\TemperatureSensor.png" style="zoom:30%;" /> 
</div>
<p align="center">DS18B20 Temperature sensor</p>  

Also, as the DS18B20 uses a single bus for data transmission, a pull-up resistor needs to be connected to the data line in order to ensure a stable and reliable level on the data line for data transmission. The pull-up resistor connects the data line to a positive power supply to ensure that the data line is at a high level. When a low level signal is to be sent, the level on the data line will be pulled down and, due to the pull-up resistor, the current on the data line will be very low, thus enabling a low level signal to be sent. In addition, pull-up resistors prevent electromagnetic interference and electrical noise on the data line, improving the reliability of data transmission.

  <div align="center">
<img src="assets\WiringDiagram-temperaturesensor.jpg" style="zoom:30%;" /> 
</div>
<p align="center">DS18B20 Temperature sensor wiring diagram</p>  

## 2.9 Connector

In terms of connectivity, for testing purposes we used a 2-pin JST plug, a connector widely used in a variety of electronic devices and electrical applications, which is small, lightweight, easy to plug and unplug and stable. It is also designed with locking clips and unidirectional slots so that the plug is not prone to accidental loosening and at the same time there is no reverse power connection. For the wire, we have used mainly 22AWG gauge wire, which can pass a maximum current of 5-7 amps. Two wires of this size are used for the connection of the heating element, taking into account the power and operating voltage of the heating element and in order to reduce heat and improve stability.

  <div align="center">
<img src="assets\JST .jpg" style="zoom:30%;" /> 
</div>
<p align="center">JST Connector</p>  

## 2.10 Port allocation

   <div align="center">
<img src="assets\WiringDiagram-Raspberry4bPinOut.png" style="zoom:50%;" /> 
</div>
<p align="center">Raspberry Pi 4B Pin out</p>  

   <div align="center">
<img src="assets\InterfaceAssignment.png" style="zoom:50%;" /> 
</div>
<p align="center">Raspberry Pi 4B Port allocation</p>  

Bluetooth modules using serial communication require the TX and RX ports, while DS18B20s using the W1 bus for communication require the GPIO4 port (default W1 port) for communication.

> **Remarks:**
> GPIO4 is normally the default W1 port and other ports on the Raspberry Pi can be used to connect 1-Wire devices by configuring them as W1 ports.
> To configure other ports as W1 ports, you can do the following:
>
> 1. Open the /boot/config.txt file using a text editor
> 2. Add at the end of the document: dtoverlay=w1-gpio,gpiopin=<W1 pin number>
> 3. Save and close the file and reboot the Raspberry Pi
>    Note that in "dtoverlay=w1-gpio,gpiopin=<W1 pin number>", there should be no spaces in the ",", otherwise the configuration will be invalid

## 2.11 Schematic and physical drawings

The power supply is connected to 230V AC and outputs 24V DC, after a second voltage conversion to obtain the required 5V or 3.3V.

The PWM regulated electronic switch control board has an input connected to the voltage converter and an output connected to the load. The PWM port on the console is connected to the GPIO port of the Raspberry Pi and GND is connected to the GND of the Raspberry Pi.

   <div align="center">
<img src="assets\WiringDiagram1.png" style="zoom:80%;" /> 
</div>
<p align="center">Schematic</p> 

   <div align="center">
<img src="assets\WiringDiagram2.png" style="zoom:80%;" /> 
</div>
<p align="center">Sample wiring diagram</p> 

 <div align="center">
<img src="assets\WiringDiagram3.jpg" style="zoom:80%;" /> 
</div>
<p align="center">Physical wiring diagram</p> 

# 3 System development

## 3.1 Software architecture diagram

 <div align="center">
<img src="assets\Class diagram.jpg" style="zoom:100%;" /> 
</div>

<p align="center">Class diagram</p> 

Application (App)

- ThreadPool

- Bluetooth

- ThermalModule

  - Heater
  - Thermometer

- Pump Module

  - Air pump

  - Waterpump

## 3.2 软件架构先不动

### 3.2.1 `Airpump`类：

这个类用于控制一个空气泵，它继承了`PwmController`类。`Airpump`类的主要功能是通过改变占空比（duty cycle）来控制空气泵的启动和停止。

- 构造函数：有两个构造函数，一个接受引脚编号，另一个接受引脚编号和频率。
- 析构函数：在类对象销毁时，如果空气泵正在运行，则停止空气泵。
- `set()`函数：设置空气泵的占空比，并启动PWM。
- `stop()`函数：停止空气泵。

### 3.2.2 `App`类：

这个类用于初始化和运行整个应用程序。它包含了一个线程池（`ThreadPool`），蓝牙（`Bluetooth`），热控模块（`ThermalModule`）和泵控模块（`PumpModule`）。

- 构造函数：初始化线程池、蓝牙、热控模块和泵控模块。
- `run()`函数：将模块任务添加到线程池，并使主线程进入睡眠状态。
- `isRunning()`函数：检查应用程序是否正在运行。
- 析构函数：在类对象销毁时，停止所有设备并终止`pigpio`库。
- `AddModuleTasks()`函数：将各个模块的任务添加到线程池。

### 3.2.3 `Heater`类的主要功能和方法如下：

- 构造函数：有两个构造函数，一个接受引脚编号，另一个接受引脚编号和频率。

- 析构函数：在类对象销毁时，如果加热器正在运行，则停止加热器。

- `setMinMaxLimit(int min, int max)`：设置加热器的最小和最大温度限制。

- `ConditionalOnOff(const std::vector<double> &tempers)`：根据传入的温度数组计算平均温度，根据平均温度和预设的最小最大温度限制，有条件地调用`autoTurnOn`和`autoTurnOff`方法。

- `autoTurnOn(int average)`：自动打开加热器，设置相应的PWM占空比。

- `autoTurnOff(int average)`：自动关闭加热器，将PWM占空比设为0。

- `set(char lvl)`：设置加热器的PWM占空比并启动PWM。

- `stop()`：停止加热器。

`Heater`类的目的是根据温度传感器的读数自动控制加热器的开启和关闭，以保持温度在设定的范围内。这种控制策略可能适用于诸如恒温器、热水器等需要维持恒定温度的设备。

### 3.2.4 `PumpModule` 类: 

`PumpModule `类是用来管理空气泵和水泵的。在`PumpModule`的构造函数中，它初始化了一个空气泵和一个水泵对象。析构函数会在销毁对象时停止这两个泵。`registerBluetooth() `函数将蓝牙对象与水泵和空气泵关联。`registerHeaterFromThermalModule() `函数将热量器对象从 `ThermalModule `中注册到蓝牙对象中。`executeCmdControl() `函数根据蓝牙命令队列来控制水泵和空气泵。`stop() `函数会停止水泵和空气泵。

### 3.2.5 `PwmController` 类:

 PwmController 类是用来控制 GPIO 的 PWM 信号的。在 `PwmController` 的构造函数中，根据传入的引脚和频率，设置了引脚模式、PWM 频率和范围。析构函数会在销毁对象时关闭 PWM。`setPwmLvl() `函数根据传入的级别设置 PWM 占空比。`isRunning() `函数返回 PWM 控制器是否正在运行。

### 3.2.6 `ThermalModule` 类: 

`ThermalModule` 类用于管理加热器和温度计。在 ThermalModule 的构造函数中，初始化了一个加热器和一个温度计对象，并将加热器注册到温度计中。析构函数会在销毁对象时停止相关设备。`registerBluetooth() `函数将蓝牙对象与 `ThermalModule` 关联。`executeAutoControlHeater() `函数通过温度计自动控制加热器。stop() 函数会停止所有相关设备。

### 3.2.7 `Thermometer` 类: 

`Thermometer `类是用来读取 DS18B20 温度计的。在 `Thermometer `的构造函数中，调用` FindTempDevices() `函数查找并记录温度计设备文件。析构函数会在销毁对象时停止` Thermometer`。`registerHeater() `函数将加热器对象与温度计关联。`AutoControlHeater()`函数会不断读取温度数据，并根据温度数据自动控制加热器。`FindTempDevices() `函数会在设备目录中查找并记录温度计设备文件。

### 3.2.8 `ThreadPool` 类：

创建一个线程池，可以处理多线程任务。

- `ThreadPool(int numThreads)`：构造函数，创建指定数量的线程。
- `~ThreadPool()`：析构函数，停止线程池。
- `start(int numThreads)`：启动指定数量的线程。
- `stop()`：停止线程池。
- `AddTask(const Task &task)`：将任务添加到任务队列。
- `AddTask(Task &&task)`：将任务以右值引用的形式添加到任务队列。
- `RunTask()`：运行任务队列中的任务。
- `stopThreads()`：停止所有线程并清除线程池中的对象。

### 3.2.9 `Waterpump `类

#### 3.2.9.1头文件引用

```
cppCopy code#include <pigpio.h>
#include <iostream>
#include "config.h"
#include "waterpump.h"
```

这部分代码引入了所需的头文件，包括 `pigpio.h`（用于操作树莓派的GPIO接口），`iostream`（用于输入输出操作，如输出错误信息），`config.h`（包含项目配置信息）和 `waterpump.h`（包含 `Waterpump` 类的声明）。

#### 3.2.9.2 构造函数

```
cppCopy code
Waterpump::Waterpump(unsigned int pin) : PwmController(pin) {}
```

这是一个构造函数，接受一个无符号整数参数 `pin`，并调用基类 `PwmController` 的构造函数。这个构造函数将使用默认的频率初始化水泵。

```
cppCopy codeWaterpump::Waterpump(unsigned int pin, unsigned int freq)
  : PwmController(pin, freq) {}
```

这是另一个构造函数，接受两个无符号整数参数 `pin` 和 `freq`，并调用基类 `PwmController` 的构造函数。这个构造函数允许指定水泵的频率。

#### 3.2.9.3 析构函数：

```
cppCopy codeWaterpump::~Waterpump() {
  if (running_) {
		this->stop(); 
	}
}
```

析构函数在 `Waterpump` 类的对象被销毁时调用。如果水泵正在运行，析构函数将调用 `stop()` 方法停止水泵。

#### 3.2.9.4 `set()` 方法：

```
cppCopy codevoid Waterpump::set(char lvl) {
  // set pwm level
  setPwmLvl(lvl);
  // Starts PWM on the GPIO
  int ret = gpioPWM(kPin_, dutycycle_);
  if (ret != 0) {
    std::cerr << TAG_WATERPUMP
              << "failed to set dutycycle: " << dutycycle_
              << " on gpio: " << kPin_ << " with err code: " << ret
              << std::endl;
  }
}
```

`set()` 方法用于设置水泵的占空比（PWM水平）。首先调用 `setPwmLvl()` 方法设置占空比，然后调用 `gpioPWM()` 函数启动GPIO上的PWM。如果启动失败，将输出错误信息。



## 3.3 Structure of the system

- src (source) folder: this folder contains all the source code files for the project

- build folder: this folder is mainly used to store intermediate files generated during the compilation process

- include folder: this folder contains the project's header files (.h and .hpp files), which define the interfaces, data structures, constants, etc. for each class in the project

- samples folder: This folder contains sample code that demonstrates how to use the classes and functions in the project.



## 3.4 Flutter mobile development

### 3.4.1 Introduction to Flutter and the main features of the Dart language

Flutter is a user interface toolkit developed by Google for building high-performance, cross-platform mobile applications. It uses the Dart programming language as its main development language.

Dart is an object-oriented, class-based programming language developed by Google for building Flutter applications. dart has a modern syntax, a high-performance virtual machine and JIT (just-in-time) compiler, and built-in tools and libraries for building responsive, concurrent and asynchronous applications.

Flutter allows for highly customisable user interfaces through its self-drawing engine and runs on multiple platforms such as iOS, Android, web and desktop. It offers rich UI controls, built-in Material Design and Cupertino design styles, and powerful animation and visual effects support, enabling developers to build visually appealing and highly interactive mobile applications.

As the primary development language for Flutter, Dart has the following features:

Static typing: Dart is a statically typed language that catches many type errors at compile time, providing better code reliability and error detection.

JIT and AOT compilation: Dart supports both just-in-time (JIT) and ahead-of-time (AOT) compilation modes, allowing developers to optimise for different development and release phases.

Asynchronous programming: Dart has built-in support for the asynchronous programming model, using the async and await keywords to handle asynchronous operations such as network requests, file I/O, etc., making it easier and more efficient to handle asynchronous tasks.

Built-in tools and libraries: Dart provides a rich set of built-in tools and libraries, including collections, asynchronous programming, file I/O, JSON serialisation and more, making it easy for developers to perform everyday development tasks.

Rich Ecosystem: Dart has a rich ecosystem with many third-party libraries and plugins that help developers speed up development and implement more features.

In short, the combination of Flutter and Dart makes it easy for developers to build high-performance, cross-platform mobile apps and have a productive development experience throughout the development process.

### 3.4.2 Introduction to the main code


The main page contains functions for temperature, air pump and water pump control. It includes input fields for setting and displaying temperature values, buttons to confirm the settings and a display of the current operating mode. The code also makes use of the GetX library for status management and includes custom input widgets for text fields.

```
 class CommonBleUtils {
 static Future<void> send(BleDevice? bleDevice, int cmd,

  [List<int>? params, bool isWithout = true]) async {
  if (bleDevice == null) return;
  params ??= [];

  params.insert(0, cmd);
  params.insert(0, 0);
  List<int> buffer = [];
  for (var element in params) {
  buffer.addAll(AsciiEncoder().convert(element.toString()));
}
```

This code is a collection of utility functions for handling Bluetooth Low Energy (BLE) communication in a Flutter application. It includes functions for sending BLE commands to BLE devices, encrypting and decrypting data, and defining constants for command codes and motor numbers. the CommonBleUtils class has a static function send for sending BLE commands with optional parameters and encryption, and a static function decrypt for decrypting BLE communication data. the CmdConst class defines constants for the public key, header, command code and motor number used in the BLE communication.
We use the BLE (Bluetooth Low Energy) protocol to transmit plaintext data.

### 3.4.3 About handling byte data

emptyStringToReplace(String content): Replaces spaces in a string with hyphens.
calculateAdd8Bit(List<int> buffer): Calculates the sum of the byte data in a list and takes the lower 8 bits.
int2Bytes(int source, {Type type = Type.WORD}): converts an integer to a list of byte data, optionally of type BYTE, WORD, DWORD or STRING.
bytes2Int(List<int> list): Converts a list of byte data to an integer.
toInt16(List<int> list, {int index = 0}): Converts two bytes of a list of byte data to a 16-bit integer.
toInt32(List<int> list, {int index = 0}): Converts four bytes of a list of byte data into a 32-bit integer.
toInt64(List<int> list, {int index = 0}): Convert 8 bytes of a byte data list to a 64-bit integer.
createUint8ListFromHexString(String hex): Creates a Uint8List of byte data from a hexadecimal string.
formatBytesAsHexString(Uint8List bytes): formats a Uint8List of byte data into a hexadecimal string.

```
import 'package:flutter_water_tank/utils/ble.mode.dart';

List<BleModel> bleModels = [
 BleModel(
  id: 5,
  modelName: 'FISHTANK',
  uuidDiscover: "ffe0",
  uuidCmd: "ffe0",
  uuidWrite: "ffe2",
  uuidRead: "ffe1",
 )
];
```

The BleModel class may be defined in a separate file called ble.mode.dart and imported using an import statement at the beginning of the code snippet. It is expected that the BleModel class will have the following properties:

id: an integer representing the ID of the Bluetooth module.
modelName: a string representing the name of the Bluetooth module.
uuidDiscover: A string representing the UUID of the discovered Bluetooth module.
uuidCmd: A string representing the UUID of the command sent to the Bluetooth module.
uuidWrite: A string representing the UUID of the command sent to the Bluetooth module: A string representing the UUID of the data written to the Bluetooth module.
uuidRead: A string representing the UUID of the data to be read from the Bluetooth module.
In the bleModels list, there is a BleModel object defined with ID 5, modelName 'FISHTANK', uuidDiscover as 'fe0', uuidCmd as 'fe0', uuidWrite as 'fe2' and uuidRead as 'fe1'. This object represents a registered Bluetooth module with these attributes. There are likely to be other BleModel objects in the bleModels list, representing other registered Bluetooth modules in the application.

### 3.4.4 Interface and commissioning

 <div align="center">
<img src="assets\flutter\Data received by the C++ backend.jpg" style="zoom:30%;" /> 
</div>

<p align="center">Data received by the C++ backend</p> 

 <div align="center">
<img src="assets\flutter\Data received by the serial debugging Assistant.jpg" style="zoom:30%;" /> 
</div>

<p align="center">Data received by the serial debugging Assistant</p> 

 <div align="center">
<img src="assets\flutter\output in flutter.jpg" style="zoom:30%;" /> 
</div>

<p align="center">output in flutter</p> 

 <div align="center">
<img src="assets\flutter\bluetooth search and connection.jpg" style="zoom:50%;" /> 
</div>

<p align="center">bluetooth search and connection</p> 

 <div align="center">
<img src="assets\flutter\UI and wrong input.jpg" style="zoom:50%;" /> 
</div>

<p align="center">UI and wrong input</p> 







 

 

 

 

 

 

 

 

 