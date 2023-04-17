#  智能鱼缸

<div align="center">
<img src="assets\Tank.png" style="zoom:90%;" /> 
</div>



README Language: [English](./README.md) ｜ [中文](./README-zh.md)

>[访问Instgram账号](https://instagram.com/haagendazs85?igshid=YmMyMTA2M2Y=)  
>[访问Youtube账号](https://www.youtube.com/channel/UC8SZ1dN7v9y7iaWZyjrDwrA)

 # 1 项目简介

我们的智能鱼缸项目是以树莓派4B为核心控制器的系统。它主要具有温度控制，含氧量维持，水流速调节等功能。用户可以在手机端查看温度并设定目标温度区间，还可以控制气泡多少和水流速度。我们的项目主要使用C++11进行编写，使用Cmake构建项目，运行在Raspbian GNU/Linux 11系统上。

## 1.1 项目功能

### 1.1.1 温度控制-可设定范围

不同种类的鱼需要不同的水温，本系统使用了温度传感器和加热器，两者配合工作，将水域内温度控制在设定值附近。用户可以设定目标温度范围。在系统运行过程中，首先使用Raspberry Pi读取温度传感器数据，将温度数据与设定范围比较，如果当前温度低于设定温度范围，则控制加热器进行加热，当检测到温度达到预定值时停止加热。在加热的过程中，水域内温度将始终作为反馈值参与温度调节。

### 1.1.2 溶解氧维持-可调速气泵

鱼的活动需要氧气，当鱼缸里有很多鱼时这非常重要，本系统使用了PWM调节电子开关控制板来控制气泵的运行功率。用户可以设定需要的工作档位。

### 1.1.3 自然环境模拟-可调节流速控制

生命在于运动。平静的水流对鱼完全没有吸引力。本系统使用了PWM调节电子开关控制板来控制气泵的运行功率，用户可以设定需要的工作档位，这使得鱼的游动姿态更美观，进食更方便。

### 1.1.4 移动端控制

以上所提到的一切都无需用户调试树莓派或修改代码中的参数，而是使用我们基于Flutter设计的移动端应用来便捷的蓝牙传输参数，设置保温范围，加热功率，气泡量以及水流速度。

## 1.2 项目贡献者

| Name         | Student ID |
| ------------ | ---------- |
| Haoshi Huang | 2635088H   |
| Xintong LIN  | 2824115L   |
| Hanwei Liang | 2669523L   |
| Chaoyi Yang  | 2724184Y   |

## 1.3 项目规划
> [甘特图](.assets/GanttChart.xlsx)  
>[会议记录](.assets/meeting/) 

<div align="center">
<img src="assets\GanttChart.png" style="zoom:100%;" /> 
</div>

<p align="center">甘特图</p>  

## 1.4 测试视频

手机通过蓝牙发送控制指令，包括开启和关断，调节速度等，系统可以迅速作出反应。

<div align="center">
<img src="assets\Test.gif" style="zoom:100%;" /> 
</div>

<p align="center">测试视频</p>  

# 2 软硬件信息

## 2.1 系统与控制器

Raspberry Pi 4B是一款基于ARM架构的微型电脑。它采用了由博通公司出品的、集成了GPU和CPU的BCM2711芯片，支持4K分辨率视频输出，最大支持4GB LPDDR4-3200 SDRAM内存，支持Gigabit以太网、双频WiFi、蓝牙5.0等多种接口和协议。它还有两个Micro-HDMI接口、两个USB3.0接口、两个USB2.0接口、一个40针GPIO接口、一个2针电源接口等。

<div align="center">
<img src="assets\RaspberryPi4B.jpg" style="zoom:50%;" /> 
</div>

<p align="center">Raspberry Pi 4B</p>  

#### 2.1.1 主机端

操作系统：Raspbian GNU/Linux 11 (bullseye-armlf)

硬件配置：Raspberry Pi 4B(Broadcom BCM2711), Quad core Cortex-A72 (ARM v8) 64-bit

程序语言相关：

- 开发工具：Visual Studio Code 1.76.0
- 编译器版本：g++ 10.2.1 (Raspbian 10.2.1-6+rpi1) 
- CMAKE 版本：cmake 3.18.4
- 编码规范：Google C++编码规范

依赖库：

- C++ Standard Template Library (STL)

- pigpio v79


### 2.1.2 客户端

硬件配置：Hisilicon Kirin 710F (4.0 GB)

操作系统：HarmonyOs 2.0.0

程序语言相关：

- 编程语言：Dart 2.17

- 开发工具：Android Studio 2022.2.1.18 for Windows

- 软件开发工具包：commandlinetools-9477386 for Windows

- 前端框架：Flutter 3.0


## 2.2 电源

在同功率下，高电压会带来较低的电流，而低电压会带来更大的电流，这会导致发热更为严重，综合考虑了安全性与系统其他部件的用电需求后，我们决定使用24V加热器进行加热。

我们选用了一款名为DT-NT24V的恒压直流电源进行供电，它可以将 230V的交流电转换为24V的低压直流电。这是一款设计紧凑的电源，有蜂窝状散热设计，有半透明盖板对接线端子进行保护，可提供过压、过热、过流和短路保护，可以进行小电流输出，电压波纹小，运行噪音低。它可以提供最高6.25安培的电流，功率可以达到150瓦特。

<div align="center">
<img src="assets\PowerSupply.png" style="zoom:50%;" /> 
</div> 

<p align="center">电源</p>  

## 2.3 电压转换器

我们使用了一款基于LM2596S稳压器设计的DC-DC降压器，当输入电压为4.0V 至 40V时，输出电压可以通过外部分压电阻进行调整，范围为 1.23V 至 37V。同时，输出电流为2安培（正常稳定）和最大3安培，足以驱动许多电子设备。它的转换效率可以达到92%，输出纹波在30mV以下，开关频率150KHz，工作温度-45至85摄氏度。为了提高系统的稳定性，我们为每一个系统都配备了独立的电源。

<div align="center">
<img src="assets\VoltageConvertor.png" style="zoom:70%;" /> 
</div>

<p align="center">LM2596S 电压转换器</p>  

## 2.4 PWM调节电子开关控制板

PWM（Pulse Width Modulation）是一种广泛应用于电子和通信领域的技术。它通过控制脉冲波形的宽度（即脉冲的持续时间）来调整信号或电源的有效值。在PWM信号中，脉冲宽度的比例（占空比，duty cycle）与所表示的模拟信号或输出电压成正比。占空比是指在一个完整的PWM周期内，高电平状态所占的时间与整个周期时间的比例。占空比的范围通常在0%（全低电平）到100%（全高电平）之间。我们利用PWM技术，实现了对加热器，气泵与水泵的控制，通过调整PWM信号的占空比，可以精确控制电机的速度和扭矩。

我们使用的这款PWM调节电子开关控制板可以对5V-36V的直流电进行调控，使用3.3V-20V之间的直流电进行触发，在散热良好的情况下连续电流最高可达15A，功率可达400W。这款PWM调节电子开关控制板采用双MOS并联有源输出，具有低内阻，高功率的特点，支持频率在0--20KHZ之间的PWM信号。

<div align="center">
<img src="assets\MotorControl.png" style="zoom:100%;" /> 
</div>

<p align="center">PWM调节电子开关控制板</p>  

## 2.5 气泵

气泵在鱼缸中扮演着重要的角色，气泵通过产生气泡，将空气中的氧气输送到鱼缸水中。当气泡破裂时，氧气释放到水中，从而为鱼类提供充足的氧气。足够的氧气对于鱼类的生长、新陈代谢和生存至关重要。气泵产生的气泡在上升过程中，可以带动水流产生循环。水流的循环有助于水中的营养物质、废物和氧气在鱼缸内均匀分布，使鱼类生活环境更加舒适。气泵提供的氧气有助于有益细菌的生长。这些细菌可以分解鱼类排泄物中的氨、亚硝酸盐等有毒物质，将其转化为无害的硝酸盐。这有助于维持鱼缸水质的稳定，为鱼类提供一个健康的生活环境。

这款气泵重约150g，采用增压电陶瓷电机，使用5V电源进行供电，功耗约为1W，最大流量为210L/H。具有供氧稳定，发热低，噪音低的特点。

我们通过PWM对气泵实现分级调速，设置了包含关闭在内的五个速度级别，用户可以在移动端选择需要的速度级别。

 <div align="center">
<img src="assets\AirPump.png" style="zoom:50%;" /> 
</div>

<p align="center">气泵</p>  

## 2.6 水泵

水泵可以推动水流循环，这有助于水中的氧气、营养物质和废物在鱼缸内均匀分布，从而为鱼类提供一个舒适的生活环境。水泵可以将水中的废物输送到过滤器，提高过滤器的工作效率，帮助维持水质。水泵产生的水流可以帮助模拟自然环境中的水流，使鱼缸形成一个良好的生态平衡。这对于鱼类的生长、繁殖以及整个鱼缸生态系统的稳定非常重要。水泵产生的水流可以带动鱼缸中的装饰物，如仿真水草、喷泉等，为鱼缸增添动感和美观效果。

这款水泵长38毫米，宽38毫米，高29毫米，重约125g，使用4.5V~12V的直流电进行驱动，水流量可以达到100~350L/H，功率可达0.5~5W。它可以在40db以下的声级下安静地工作，通过吸盘吸附在鱼缸表面上。

我们通过PWM对水泵实现分级调速，设置了包含关闭在内的五个速度级别，用户可以在移动端选择需要的速度级别。

  <div align="center">
<img src="assets\WaterPump.jpg" style="zoom:60%;" /> 
</div>

<p align="center">水泵</p>  

## 2.7 浸入式电阻式加热器

浸入式电阻式加热器是一种利用电阻发热的原理来加热水的设备。它主要由电阻发热元件、外壳、温度控制器和绝缘材料等部分组成。在加热器中，电阻发热元件是核心部件，它将电能转化为热能，从而实现对水的加热，同时，电阻发热元件直接与水接触，热量传递效率较高，因此加热速度较快。当电流通过电阻发热元件时，由于电阻元件的电阻作用，电流会产生焦耳热。这种热量会被传递到水中，使水温升高。通过调整PWM信号的占空比，可以控制加热元件产生的热量，从而实现对水温的控制。

我们采用的加热器可以工作在24V的电压下，并且最大功率可以达到140瓦特。

  <div align="center">
<img src="assets\Heater.png" style="zoom:50%;" /> 
</div>

<p align="center">浸入式电阻式加热器</p>  

## 2.8 温度传感器

DS18B20 是一款能够在 -55°C 至 +125°C 的范围内测量温度的数字温度传感器。当温度在 -10°C 至 +85°C 范围内时，DS18B20 的测量精度可达到 ±0.5°C。它可以将测量到的温度值转换为数字信号，便于微控制器等数字设备读取和处理。输出数据为 9 位至 12 位可编程分辨率的数字信号。DS18B20 使用一根数据线（1-Wire 协议）与微控制器进行通信，可以简化接线和减少硬件成本。

  <div align="center">
<img src="assets\TemperatureSensor.png" style="zoom:30%;" /> 
</div>

<p align="center">DS18B20温度传感器</p>  

同时，由于DS18B20采用单总线数据传输，为了确保数据线上的电平稳定和可靠地进行数据传输，需要在数据线上连接一个上拉电阻。上拉电阻将数据线连接到正电源上，以确保数据线处于高电平状态。当要发送低电平信号时，数据线上的电平将被拉低，并且由于上拉电阻的存在，数据线上的电流将非常小，从而实现了低电平信号的发送。此外，上拉电阻还可以防止数据线上的电磁干扰和电气噪声，提高数据传输的可靠性。

  <div align="center">
<img src="assets\WiringDiagram-temperaturesensor.jpg" style="zoom:30%;" /> 
</div>

<p align="center">DS18B20温度传感器接线</p>  

## 2.9 连接件

在连接性方面，为了方便测试，我们使用了2针的JST 插头，这是一种广泛应用于各种电子设备和电气应用的连接器，具有小巧轻便、插拔方便和稳定性好的优点，同时设计有锁扣与单向插槽，因此该插头不容易意外松脱，同时不会出现电源接反的情况。在线材上，我们主要使用了规格为22AWG的线材，最大电流可以通过5-7安培。考虑到加热元件的功率与运行电压，并且为了降低发热以及提高稳定性，因此我们在加热元件的连接上使用了两根此规格的线材。

  <div align="center">
<img src="assets\JST .jpg" style="zoom:30%;" /> 
</div>

<p align="center">JST 插头</p>  

## 2.10 端口分配

   <div align="center">
<img src="assets\WiringDiagram-Raspberry4bPinOut.png" style="zoom:50%;" /> 
</div>

<p align="center">Raspberry Pi 4B接口</p>  

   <div align="center">
<img src="assets\InterfaceAssignment-zh.png" style="zoom:50%;" /> 
</div>
<p align="center">Raspberry Pi 4B端口分配</p>  

使用串行通讯的蓝牙模块需要使用TX和RX端口，同时使用W1总线进行通讯的DS18B20需要使用GPIO4端口（默认W1端口）进行通讯。

> **备注：**
> GPIO4通常是默认的W1端口，而树莓派的其他端口也可以通过配置为W1端口而用于连接1-Wire设备。
>如果要将其他端口配置为W1端口，可以进行以下操作：
>1. 使用文本编辑器打开/boot/config.txt文件
>2. 在文档最后添加：dtoverlay=w1-gpio,gpiopin=<W1引脚号>
>3. 保存并关闭文件，重新启动树莓派
>需要注意的是在“dtoverlay=w1-gpio,gpiopin=<W1引脚号>”中，“,”不应有空格，不然配置会无效

## 2.11 原理图与实物图

电源连接230V交流电，输出24V直流电，在经过第二次电压转换后获得需要的5V或3.3V电压。

PWM调节电子开关控制板的输入端连接电压转换器，输出端连接负载，控制端的PWM端口连接树莓派的GPIO端口，GND与树莓派的GND相连。

   <div align="center">
<img src="assets\WiringDiagram1.png" style="zoom:80%;" /> 
</div>

<p align="center">原理图</p> 

   <div align="center">
<img src="assets\WiringDiagram2.png" style="zoom:80%;" /> 
</div>

<p align="center">模拟接线图</p> 

 <div align="center">
<img src="assets\WiringDiagram3.jpg" style="zoom:80%;" /> 
</div>

<p align="center">实物接线图</p> 

# 3 系统开发

## 3.1 软件类图

 <div align="center">
<img src="assets\Class diagram.jpg" style="zoom:100%;" /> 
</div>

<p align="center">类图</p> 

应用程序（App）

- 线程池（ThreadPool）

- 蓝牙（Bluetooth）

- 热控模块（ThermalModule）

  - 加热器（Heater）
  - 温度计（Thermometer）

- 泵控模块（PumpModule）

  - 空气泵（Airpump）

  - 水泵（Waterpump）

## 3.2 软件架构

### 3.2.1 `ThreadPool` 类 与 `TaskQueue` 模板类

创建一个线程池，可以处理多线程任务，将作为`App`类中的对象，使用了生产者-消费者的设计模式。蓝牙指令执行任务处于消费者，蓝牙获取指令任务属于生产者。异步执行任务，使用了同步队列存储指令，保证了共享数据的安全。

- `ThreadPool(int numThreads)`：构造函数，创建指定数量的线程。
- `~ThreadPool()`：析构函数，停止线程池。
- `start(int numThreads)`：启动指定数量的线程。
- `stop()`：停止线程池。
- `AddTask(const Task &task)`：将任务添加到任务队列。
- `AddTask(Task &&task)`：将任务以右值引用的形式添加到任务队列。
- `RunTask()`：运行任务队列中的任务。
- `stopThreads()`：停止所有线程并清除线程池中的对象。

### 3.2.2 `PwmController` 类

因为项目中的加热器，水泵，气泵，都是由 PWM 模块控制的，在编码上 PWM 信号控制器件输出功率的执行流程是一致的：分配器件接口，设置 PWM 信号频率和占空比控制范围，最后按照占空比与控制范围的相对比值作为输出功率输出 PWM 信号到 GPIO 上。将数据成员声明为受保护权限，方便派生类使用。

数据成员：

- `kPin_`： 对应器件的 GPIO 引脚号

- `kRange_`：对应控制精度

- `freq_`：表示 PWM 信号频率

- `dutycycle_`： 表示器件当前的绝对占空比

- `running_`：表示器件运行状态

函数成员：

- 构造函数：删除了默认构造函数和拷贝构造函数。根据传入的引脚或者引脚和频率来初始化。使用了委托构造函数的方法初始化单引脚构造方法
- `set()`：设置并对器件端口启动对应相对占空比 的 PWM 信号
- `stop()`： 用于主动关闭器件
- `isRunning() `函数返回 PWM 控制器运行状态
- `setPwmLvl() `函数根据传入的级别设置 PWM 占空比
- 析构函数：会在销毁对象前主动清零 PWM 信号

### 3.2.3 `Heater`类

该类继承了`PwmController`类，用于控制一个加热器。`Heater` 类的主要功能是通过改变数据占空比来控制空气泵的启动和停止。该类属于回调函数类，当事件满足对应条件，执行加热器的开启与关闭。事件主要有两个：一是基于 `Thermometer` 类的温度测量事件，这属于自动控制；二是基于 `Bluetooth` 类获取指令事件，当有消息指令被捕获，如果是属于调整加热器的指令类型，即进行主动控温。

数据成员：

- `minLimit_`：温度上限
- `maxLimit_`：温度下限
- `needOn_`：需要开启加热器的标志位
- `needOff_`：需要关闭叫热情的标志位

函数成员：

- 构造函数：继承于 `PwmController` 类

- 析构函数：在类对象销毁前，如果加热器正在运行，则停止加热器。

- `setMinMaxLimit(int min, int max)`：设置加热器的最小和最大温度限制。

- `ConditionalOnOff(const std::vector<double> &)`：根据传入的温度数组计算平均温度，根据平均温度和预设的最小最大温度限制，有条件地调用`autoTurnOn`和`autoTurnOff`方法。

- `autoTurnOn(int average)`：自动打开加热器，设置相应的PWM占空比。

- `autoTurnOff(int average)`：自动关闭加热器，将PWM占空比设为0。

- `set(char lvl)`：设置加热器的PWM占空比并启动PWM。

- `stop()`：停止加热器。

`Heater`类的目的是根据温度传感器的读数自动控制加热器的开启和关闭，以保持温度在设定的范围内。这种控制策略可能适用于诸如恒温器、热水器等需要维持恒定温度的设备。

### 3.2.4 `Airpump`类 与 `Waterpump `类

均继承`PwmController`类，用于控制一个空气泵和一个水泵。主要功能是通过改变占空比来控制空气泵和水泵的启动和停止。这两类均作为回调函数类，根据蓝牙指令事件控制器件运行。

### 3.2.5 `Thermometer` 类

`Thermometer `类是用来读取 DS18B20 温度计的。在 `Thermometer `的构造函数中，调用` FindTempDevices() `函数查找并记录温度计设备文件。析构函数会在销毁对象时停止` Thermometer`。`registerHeater() `函数将加热器对象与温度计关联。`AutoControlHeater()`函数会不断读取温度数据，并根据温度数据自动控制加热器。`FindTempDevices() `函数会在设备目录中查找并记录温度计设备文件。

### 3.2.6 `ThermalModule` 类

`ThermalModule` 类用于管理加热器对象和温度计对象。在 `ThermalModule` 的声明中包含指向一个加热器的智能指针和一个指向温度计的智能指针，并将加热器注册到温度计中。`registerBluetooth() `函数将蓝牙对象与 `ThermalModule` 关联。`executeAutoControlHeater() `函数通过温度计自动控制加热器，该任务将在`App`类中作为回调任务，放进线程池对象中。stop() 函数会停止所有相关设备。最后析构函数会在销毁对象时停止相关设备。

### 3.2.7 `PumpModule` 类

`PumpModule `类是用来管理空气泵和水泵的。在`PumpModule`的构造函数中，它初始化了一个空气泵和一个水泵对象。析构函数会在销毁对象时停止这两个泵。`registerBluetooth() `函数将蓝牙对象与水泵和空气泵关联。`registerHeaterFromThermalModule() `函数将热量器对象从 `ThermalModule `中注册到蓝牙对象中。`executeCmdControl() `函数根据蓝牙命令队列来控制水泵和空气泵。`stop() `函数会停止水泵和空气泵。

### 3.2.8 `App`类

这个类用于初始化和运行整个应用程序。它包含了一个线程池（`ThreadPool`），蓝牙（`Bluetooth`），热控模块（`ThermalModule`）和泵控模块（`PumpModule`）。

- 构造函数：初始化线程池、蓝牙、热控模块和泵控模块。
- `run()`函数：将模块任务添加到线程池，并使主线程进入睡眠状态。
- `isRunning()`函数：检查应用程序是否正在运行。
- 析构函数：在类对象销毁时，停止所有设备并终止`pigpio`库。
- `AddModuleTasks()`函数：将各个模块的任务添加到线程池。


## 3.3 工程文件结构

- src 文件夹：该文件夹包含项目的所有源代码文件

- build 文件夹：该文件夹主要用于存放编译过程中生成的中间文件

- include 文件夹：该文件夹包含项目的头文件（.h 和 .hpp 文件），这些头文件定义了项目中各个类的接口、数据结构和常量等

- samples 文件夹：该文件夹包含一些示例代码，用于演示如何使用项目中的各个类和功能。

  

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

### 3.4.4 界面与调试

 <div align="center">
<img src="assets\flutter\Data received by the C++ backend.jpg" style="zoom:30%;" /> 
</div>

<p align="center">C++后端接收的数据</p> 

 <div align="center">
<img src="assets\flutter\Data received by the serial debugging Assistant.jpg" style="zoom:30%;" /> 
</div>

<p align="center">串行调试助手接收的数据</p> 

 <div align="center">
<img src="assets\flutter\output in flutter.jpg" style="zoom:30%;" /> 
</div>

<p align="center">flutter输出</p> 

 <div align="center">
<img src="assets\flutter\bluetooth search and connection.jpg" style="zoom:50%;" /> 
</div>

<p align="center">蓝牙查找与连接</p> 

 <div align="center">
<img src="assets\flutter\UI and wrong input.jpg" style="zoom:50%;" /> 
</div>

<p align="center">UI和错误的输出</p> 

# 4 至此，Intelligent Fish Tank完成，感谢大家！







 

 

 

 

 

 

 

 

 