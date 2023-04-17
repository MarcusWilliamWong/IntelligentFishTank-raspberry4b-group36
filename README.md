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

## 1.2 Project contributors

| Name         | Student ID |
| ------------ | ---------- |
| Haoshi Huang | 2635088H   |
| Xintong LIN  | 2824115L   |
| Hanwei Liang | 2669523L   |
| Chaoyi Yang  | 2724184Y   |

## 1.3 Project planning
> [GanttChart](.assets/GanttChart.xlsx)  
>[MEMORANDUM OF MEETING](.assets/meeting/) 

<div align="center">
<img src="assets\GanttChart.png" style="zoom:100%;" /> 
</div>
<p align="center">GanttChart</p>  

## 1.4 Test video

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

## 3.1 Software class diagram

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

## 3.2 Software class description and architecture

### 3.2.1 The `ThreadPool` class and the `TaskQueue` template class

Create a thread pool that can handle multi-threaded tasks that will act as objects in the `App` class, using the producer-consumer design pattern. The Bluetooth command execution task is in the consumer and the Bluetooth fetch command task belongs to the producer. The task is executed asynchronously and a synchronous queue is used to store the instructions, ensuring the security of the shared data.

- `ThreadPool(int numThreads)`: constructor that creates the specified number of threads.
- `~ThreadPool()`: destructor, stops the pool of threads.
- `start(int numThreads)`: constructor to start the specified number of threads.
- `stop()`: stops the pool of threads.
- `AddTask(const Task &task)`: Adds a task to the task queue.
- `AddTask(Task &&task)`: adds the task to the task queue as a right-valued reference.
- `RunTask()`: Runs the task in the task queue.
- `stopThreads()`: stops all threads and clears the thread pool of objects.

### 3.2.2 `PwmController` class

The PWM module controls the power output of devices such as the heater, water pump, and air pump in the project. The coding process for controlling the output power of the PWM signal to these devices is consistent: assigning the device interface, setting the PWM signal frequency and duty cycle control range, and finally outputting the PWM signal to the GPIO as power output based on the relative ratio of the duty cycle to the control range. By declaring the data members as protected, it is convenient for derived classes to use them.

Data member：

- `kPin_`： GPIO pin number of the corresponding device

- `kRange_`：Corresponding control accuracy

-  `freq_`：PWM signal frequency

-  `dutycycle_`： Current absolute duty cycle of the device

-  `running_`：Device operating state

Function Member：

- Constructor: Deleted the default constructor and copy constructor. Initializes based on the passed pin or pin and frequency. Delegation constructor method is used to initialize the single-pin constructor method.
- `set()`：Set and start the PWM signal corresponding to the relative duty ratio on the device port
- `stop()`：Shutdown device actively
- `isRunning() `function: Return the running status of the PWM controller
- `setPwmLvl() `function: Set the PWM duty cycle according to the incoming level
- Destructor: Will actively clear the PWM signal before destroying the object

### 3.2.3 `Heater` class 

This class inherits from the `PwmController` class and is used to control a heater. The main function of the `Heater` class is to control the starting and stopping of the heater by changing the duty cycle data. This class belongs to the callback function class, which executes the opening and closing of the heater when events meet corresponding conditions. There are mainly two events: one is the temperature measurement event based on the `Thermometer` class, which belongs to automatic control; the other is the instruction acquisition event based on the `Bluetooth` class. When a message instruction is captured, if it belongs to the type of adjusting the heater, active temperature control is carried out.

Data member：

- `minLimit_`：upper temperature limit
- `maxLimit_`：Lower temperature limit
- `needOn_`：Flag indicating the need to turn on the heater
- `needOff_`：Flag indicating the need to turn off the heater

Function member：

- Constructor: inherited from the `PwmController` class.

- Destructor: stops the heater if it's running before the object is destroyed.

- `setMinMaxLimit(int min, int max)`：Set the minimum and maximum temperature limits for the heater.

- `ConditionalOnOff(const std::vector<double> &)`：Calculate the average temperature based on the incoming temperature array, and conditionally call the `autoTurnOn` and `autoTurnOff` methods based on the average temperature and the preset minimum and maximum temperature limits.

- `autoTurnOn(int average)`：Automatically turn on the heater and set the corresponding PWM duty cycle.

- `autoTurnOff(int average)`：Automatically turn off the heater and set the PWM duty cycle to 0.

- `set(char lvl)`：Set the PWM duty cycle of the heater and start the PWM.

- `stop()`：Stop the heater.


The purpose of the `Heater` class is to automatically control the opening and closing of the heater based on the readings from a temperature sensor, in order to maintain the temperature within a set range. This control strategy may be suitable for devices such as thermostats, water heaters, and other equipment that requires maintaining a constant temperature.

### 3.2.4 `Airpump` Class and  `Waterpump ` Class

Both classes, Airpump and Heater, inherit from the `PwmController` class and are used to control an air pump. The main function of the `Airpump` class is to control the start and stop of the air pump by changing the duty cycle. Both classes serve as callback function classes, controlling the operation of the component based on Bluetooth command events.

### 3.2.5 `Thermometer` Class

The `Thermometer` class is used to read DS18B20 temperature sensors. In the constructor of `Thermometer`, the `FindTempDevices()` function is called to search for and record the temperature sensor device files. The destructor will stop the `Thermometer` when the object is destroyed. The `registerHeater()` function associates the heater object with the thermometer. The `AutoControlHeater()` function constantly reads temperature data and automatically controls the heater based on the temperature data. The `FindTempDevices()` function searches and records temperature sensor device files in the device directory.


### 3.2.6 `ThermalModule` Class 

The `ThermalModule` class is used to manage heater objects and thermometer objects. The declaration of the `ThermalModule` includes a smart pointer to a heater and a smart pointer to a thermometer, and registers the heater with the thermometer. The `registerBluetooth()` function associates the Bluetooth object with the `ThermalModule`. The `executeAutoControlHeater()` function automatically controls the heater based on the thermometer, and this task is added as a callback task in the `App` class and added to the thread pool object. The `stop()` function stops all related devices, and the destructor stops the related devices when the object is destroyed.

### 3.2.7 `PumpModule` Class

The `PumpModule` class is used to manage the air pump and water pump. In the constructor of `PumpModule`, it initializes an air pump and a water pump object. The destructor stops these two pumps when the object is destroyed. The `registerBluetooth()` function associates the Bluetooth object with the water pump and air pump. The `registerHeaterFromThermalModule()` function registers the heater object from the `ThermalModule` with the Bluetooth object. The `executeCmdControl()` function controls the water pump and air pump based on the Bluetooth command queue. The `stop()` function stops the water pump and air pump.

### 3.2.8 `App` Class
This class is used to initialize and run the entire application. It includes a thread pool (`ThreadPool`), Bluetooth (`Bluetooth`), thermal control module (`ThermalModule`), and pump control module (`PumpModule`).

- Constructor: initializes the thread pool, Bluetooth, thermal control module, and pump control module.
- `run()` function: adds module tasks to the thread pool and puts the main thread to sleep.
- `isRunning()` function: checks whether the application is running.
- Destructor: stops all devices and terminates the `pigpio` library when the class object is destroyed.
- `AddModuleTasks()` function: adds tasks for each module to the thread pool.

## 3.3 Project document structure

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

# 4 At this point,  the Intelligent Fish Tank is complete, thank you all!





 

 

 

 

 

 

 

 

 