# IntelligentFishTank-raspberry4b-group36
This project aimed to design an **Intelligent Fish Tank** controlled by Raspberry Pi 4b in real-time. 
It mainly includes the following six module functions: temperature detection, oxygen detection, water quality detection, auto feeder, flow control, brilliant lights.
# 智能鱼缸-树莓派4b-36组
该项目旨在设计一个由树莓派4b实时控制的**智能鱼缸**。
它主要包括以下六个模块功能：水温控制、含氧量控制、定量投喂、水质维持、水流速调节、灯光效果。

## 1，水温控制
元件：温度传感器，带有驱动的加热器
逻辑：io口采集温度传感器数据，与设定值比较，使用差值进行PWM调控，控制加热器
算法：采集可用滤波，控制可用PID
指示功能：加热时亮红灯，达到设定温度为绿灯，（长时间未达到设定温度进行警报）

## 2，含氧量控制
元件：水溶氧传感器，带有驱动的气泵
逻辑：io口采集水溶氧传感器数据，与设定值比较，使用差值进行PWM调控，控制气泵
算法：采集可用滤波，控制可用PID
指示功能：（含氧量长时间过低进行警报）

## 3，定量投喂
元件：舵机，光电断路传感器
逻辑：控制舵机旋转量控制投食量，光电断路传感器检测余粮
算法：机械结构

## 4，水质维持
元件：浑浊度传感器
逻辑：io口采集水溶氧浑浊度传感器数据，作为水泵控制的参考变量
算法：采集可用滤波
（长时间未达到设定温度进行警报）

## 5，水流速调节
元件：水流速传感器，带有驱动的水泵
逻辑：io口采集水流速传感器数据，与设定值比较，使用差值进行PWM调控，控制水泵
算法：采集可用滤波

## 6，灯光效果
元件：LED

1，温度，含氧量，水质传感器读数，2，控制驱动调节功率，控制舵机
