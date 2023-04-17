#  Intelligent Fish Tank

<div align="center">
<img src="assets\OpenReportTank.jpg" style="zoom:100%;" /> 
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

| Name         | Student ID | Role |
| ------------ | ---------- | ---- |
| Haoshi Huang |            |      |
| Xintong LIN  | 2824115L   |      |
| Hanwei Liang | 2669523L   |      |
|              |            |      |

## 1-3 Project planning

> [GanttChart](.assets/GanttChart.xlsx)

<div align="center">
<img src="assets\GanttChart.png" style="zoom:100%;" /> 
</div>
<p align="center">GanttChart</p>  

## 1-4 测试视频

## ！！在这里放最后测试视频



# 2 Software and hardware information

## 2.1 Systems and Controllers

The Raspberry Pi 4B is a miniature computer based on the ARM architecture. It uses the BCM2711 chip with integrated GPU and CPU from Broadcom, supports 4K resolution video output, up to 4GB of LPDDR4-3200 SDRAM memory, Gigabit Ethernet, dual-band WiFi, Bluetooth 5.0 and many other interfaces and protocols. It also has two Micro-HDMI ports, two USB 3.0 ports, two USB 2.0 ports, a 40-pin GPIO port, a 2-pin power connector and more.

## ！！黄老板写点软件版本信息

<div align="center">
<img src="assets\RaspberryPi4B.jpg" style="zoom:50%;" /> 
</div>

<p align="center">Raspberry Pi 4B</p>  



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

<p align="center">气泵</p>  

## 2.6 Water pump

The water pump circulates the water, which helps the oxygen, nutrients and waste in the water to be evenly distributed within the tank, thus providing a comfortable living environment for the fish. The water pump transports waste from the water to the filter, increasing the efficiency of the filter and helping to maintain water quality. The water flow generated by the pump helps to simulate the water flow in a natural environment, creating a good ecological balance in the fish tank. This is important for the growth and reproduction of fish and the stability of the entire fish tank ecosystem. The water flow generated by the pump can drive decorative objects in the tank, such as simulated water plants and fountains, adding a dynamic and aesthetic effect to the tank.

The pump is 38mm long, 38mm wide, 29mm high, weighs about 125g and is driven by DC power from 4.5V~12V. The water flow can reach 100~350L/H and the power can reach 0.5~5W. It can work quietly at a sound level below 40db and is attached to the surface of the fish tank by suction cups.

We implement a graded speed regulation for the pump via PWM, setting five speed levels including off, and the user can select the desired speed level on the mobile.

  <div align="center">
<img src="assets\WaterPump.jpg" style="zoom:60%;" /> 
</div>

<p align="center">水泵</p>  

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
<img src="assets\InterfaceAssignment-zh.png" style="zoom:50%;" /> 
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

Application (App)

- ThreadPool

- Bluetooth

- ThermalModule

  - Heater
  - Thermometer

- Pump Module

  - Air pump

  - Waterpump

## 3.2 软件架构

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

#### 3.2.9.5 `stop()` 方法：



#### 3.2.9.6 水泵类的声明：




## 3.3 系统的结构

- src (source) 文件夹：这个文件夹包含项目的所有源代码文件

- build 文件夹：这个文件夹主要用于存放编译过程中生成的中间文件

- include 文件夹：这个文件夹包含项目的头文件（.h 和 .hpp 文件），这些头文件定义了项目中各个类的接口、数据结构和常量等

- samples 文件夹：这个文件夹包含一些示例代码，用于演示如何使用项目中的各个类和功能。

## 这里来点图？



## 3.4 Flutter手机端开发

### 3.4.1 Flutter简介及Dart语言主要特点

Flutter是一个由谷歌开发的用户界面工具包，用于构建高性能、跨平台的移动应用程序。它使用Dart编程语言作为其主要开发语言。

Dart是谷歌为构建Flutter应用程序而开发的一种面向对象、基于类的编程语言。Dart有现代的语法，有高性能的虚拟机和JIT（即时）编译器，以及内置的工具和库，用于构建响应式、并发式和异步的应用程序。

Flutter允许通过其自绘引擎实现高度可定制的用户界面，并可在多个平台上运行，如iOS、Android、Web和桌面。它提供丰富的UI控件，内置Material Design和Cupertino设计风格，以及强大的动画和视觉效果支持，使开发者能够构建视觉上有吸引力和高度互动的移动应用。

作为Flutter的主要开发语言，Dart具有以下特点：

静态类型化： Dart是一种静态类型的语言，在编译时捕获许多类型错误，提供更好的代码可靠性和错误检测。

JIT和AOT编译： Dart支持即时编译（JIT）和超前编译（AOT）模式，允许开发者为不同的开发和发布阶段进行优化。

异步编程： Dart内置支持异步编程模型，使用async和await关键字来处理异步操作，如网络请求、文件I/O等，使处理异步任务更加简洁和高效。

内置工具和库： Dart提供了丰富的内置工具和库，包括集合、异步编程、文件I/O、JSON序列化等，方便开发者执行日常开发任务。

丰富的生态系统： Dart有一个丰富的生态系统，有许多第三方库和插件，可以帮助开发者加快开发速度，实现更多的功能。

总之，Flutter和Dart的结合使开发者能够轻松构建高性能、跨平台的移动应用，并在整个开发过程中拥有高效的开发体验。

### 3.4.2 主要代码简介


主页包含温度、气泵和水泵控制的功能，它包括设置和显示温度值的输入字段，确认设置的按钮，以及当前操作模式的显示。该代码还利用GetX库进行状态管理，并包括文本字段的自定义输入部件。

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

这段代码是在Flutter应用程序中处理蓝牙低能量（BLE）通信的实用函数的集合。它包括向BLE设备发送BLE命令，加密和解密数据，以及定义命令代码和电机号码的常数的函数。CommonBleUtils类有一个静态函数send，用于发送带可选参数和加密的BLE命令，还有一个静态函数decrypt，用于解密BLE通知数据。CmdConst类定义了BLE通信中使用的公钥、标头、命令代码和电机号码的常量。
我们使用BLE（蓝牙低能量）协议来传输明文数据。

### 3.4.3 关于处理字节数据

emptyStringToReplace(String content)： 将字符串中的空格替换为连字符。
calculateAdd8Bit(List<int> buffer)： 计算一个列表中的字节数据的总和，并取低8位。
int2Bytes(int source, {Type type = Type.WORD})： 将一个整数转换为一个字节数据的列表，可选的转换类型为BYTE、WORD、DWORD或STRING。
bytes2Int(List<int> list)： 将一个字节数据列表转换为一个整数。
toInt16(List<int> list, {int index = 0})： 将字节数据列表中的两个字节转换为16位整数。
toInt32(List<int> list, {int index = 0})： 将字节数据列表中的四个字节转换为32位整数。
toInt64(List<int> list, {int index = 0})： 将字节数据列表中的8个字节转换为64位整数。
createUint8ListFromHexString(String hex)： 从十六进制字符串创建一个字节数据的Uint8List。
formatBytesAsHexString(Uint8List bytes)： 将一个字节数据的Uint8List格式化为十六进制字符串。

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

BleModel类可能被定义在一个单独的文件中，名为ble.mode.dart，并在代码片段的开头使用导入语句导入。预计BleModel类将有以下属性：

id： 一个整数，代表蓝牙模块的ID。
modelName： 一个字符串，代表蓝牙模块的名称。
uuidDiscover： 一个字符串，代表发现蓝牙模块的UUID。
uuidCmd： 代表向蓝牙模块发送命令的UUID的字符串。
uuidWrite: 代表向蓝牙模块发送命令的UUID字符串： 一个字符串，代表向蓝牙模块写入数据的UUID。
uuidRead： 一个字符串，代表从蓝牙模块读取数据的UUID。
在bleModels列表中，有一个定义的BleModel对象，ID为5，modelName为'FISHTANK'，uuidDiscover为 "ffe0"，uuidCmd为 "ffe0"，uuidWrite为 "ffe2 "和uuidRead为 "ffe1"。这个对象代表一个具有这些属性的注册蓝牙模块。在bleModels列表中很可能还有其他的BleModel对象，代表应用程序中的其他注册蓝牙模块。

# 4 单元测试

## 4.1 





# 5 问题与总结





 

 

 

 

 

 

 

 

 