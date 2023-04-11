// 导入 Wire 库，用于与 I2C 设备通信
#include <Wire.h>
// #include <wiringPiI2C.h>
// 导入 VEML7700 库，用于操作 VEML7700 光传感器
#include <VEML7700.h>

// 创建 VEML7700 对象
VEML7700 als;

// 设置函数，初始化硬件和串口通信
void setup()
{
  Serial.begin(9600); // 初始化串口通信，波特率为 9600
  als.begin();        // 初始化 VEML7700 光传感器
}

// 主循环，用于不断读取光照强度
void loop()
{
  float lux; // 声明一个浮点型变量，用于存储光照强度值

  als.setGain(VEML7700::ALS_GAIN_d8); // 设置 VEML7700 的增益

  // 下面的代码段分别以不同的积分时间测量光照强度，并通过串口输出
  for (int integrationTime = VEML7700::ALS_INTEGRATION_25ms; integrationTime <= VEML7700::ALS_INTEGRATION_800ms; integrationTime *= 2) {
    als.setPower(0); // 关闭传感器
    als.setIntegrationTime(static_cast<VEML7700::als_integration_time_t>(integrationTime)); // 设置积分时间
    als.setPower(1); // 打开传感器
    als.sampleDelay(); // 等待传感器采样完成
    als.getALSLux(lux); // 获取光照强度值
    Serial.print(lux); // 通过串口输出光照强度值
    Serial.print(" "); // 通过串口输出一个空格
  }

  als.getAutoALSLux(lux); // 获取自动模式下的光照强度值
  Serial.println(lux); // 通过串口输出自动模式下的光照强度值

  delay(200); // 延时 200 毫秒
}

