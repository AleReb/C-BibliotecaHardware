# SHT40 Arduino 库

用于 SHT40 数字温湿度传感器的 Arduino 库。

## 简介

本库为 Sensirion 的 SHT40 数字温湿度传感器提供了易于使用的接口。SHT40 是一款高精度、低功耗的传感器，通过 I2C 进行通信。

## 特性

- 简单直观的 API
- 高精度温度和湿度读数
- I2C 通信支持
- CRC8 校验和验证，确保数据完整性
- 缓存读数，避免不必要的测量

## 安装

1. 下载库的 ZIP 文件
2. 在 Arduino IDE 中，转到 项目 > 加载库 > 添加 .ZIP 库...
3. 选择下载的 ZIP 文件
4. 库将被安装

或者，您可以将此仓库克隆到 Arduino 库文件夹中：

```
cd <Arduino 库文件夹>
git clone https://github.com/MR01Right/SHT40.git
```

## 硬件要求

- Arduino 开发板（Uno、Nano、ESP32 等）
- SHT40 传感器模块
- I2C 连接（SDA、SCL）

## 接线

将 SHT40 传感器连接到 Arduino：

- VCC → 3.3V 或 5V（请检查传感器规格）
- GND → GND
- SDA → SDA（或 Arduino Uno 上的 A4）
- SCL → SCL（或 Arduino Uno 上的 A5）

**注意：** 某些开发板可能需要在 SDA 和 SCL 线上添加上拉电阻（通常为 4.7kΩ）。

## 使用方法

### 基础示例

```cpp
#include <Wire.h>
#include <SHT40.h>

SHT40 sht40;

void setup() {
  Serial.begin(9600);
  Wire.begin();  // 初始化 I2C
  
  if (!sht40.begin(&Wire)) {
    Serial.println("SHT40 初始化失败！");
    while(1);
  }
  Serial.println("SHT40 初始化成功");
}

void loop() {
  float temperature = sht40.readTemperatureC();
  float humidity = sht40.readHumidityRH();
  
  Serial.print("温度: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  Serial.print("湿度: ");
  Serial.print(humidity);
  Serial.println(" %RH");
  
  delay(2000);
}
```

### 高级示例

```cpp
#include <Wire.h>
#include <SHT40.h>

SHT40 sht40;

void setup() {
  Serial.begin(9600);
  Wire.begin();  // 初始化 I2C
  
  // 使用自定义 I2C 地址初始化（默认为 0x44）
  sht40.begin(&Wire, 0x44);
}

void loop() {
  float temp, hum;
  
  if (sht40.measure(temp, hum)) {
    Serial.print("温度: ");
    Serial.print(temp);
    Serial.println(" °C");
    
    Serial.print("湿度: ");
    Serial.print(hum);
    Serial.println(" %RH");
  } else {
    Serial.println("测量失败！");
  }
  
  delay(2000);
}
```

## API 参考

### `SHT40()`
构造函数。创建一个新的 SHT40 实例。

### `bool begin(TwoWire *wire, uint8_t address = 0x44)`
初始化传感器。
- **参数：**
  - `wire`: TwoWire (I2C) 对象的指针
  - `address`: I2C 地址（默认：0x44）
- **返回：** 初始化成功返回 `true`，否则返回 `false`

### `float readTemperatureC(bool forceMeasure = true)`
读取温度值（摄氏度）。
- **参数：**
  - `forceMeasure`: 如果为 `true`，执行新的测量。如果为 `false`，返回上次缓存的值。
- **返回：** 温度值（摄氏度），测量失败返回 `NAN`

### `float readHumidityRH(bool forceMeasure = true)`
读取相对湿度值。
- **参数：**
  - `forceMeasure`: 如果为 `true`，执行新的测量。如果为 `false`，返回上次缓存的值。
- **返回：** 相对湿度值（%RH），测量失败返回 `NAN`

### `bool measure(float &temperatureC, float &humidityRH)`
同时测量温度和湿度。
- **参数：**
  - `temperatureC`: 存储温度值的引用
  - `humidityRH`: 存储湿度值的引用
- **返回：** 测量成功返回 `true`，否则返回 `false`

## 技术规格

- **温度范围：** -40°C 至 +125°C
- **温度精度：** ±0.2°C（典型值）
- **湿度范围：** 0% 至 100% RH
- **湿度精度：** ±1.5% RH（典型值）
- **I2C 地址：** 0x44（默认）
- **供电电压：** 2.3V 至 5.5V

## 许可证

本库采用 MIT 许可证发布。

## 作者

MR01Right

## 贡献

欢迎贡献！请随时提交 Pull Request。

## 支持

如有问题、疑问或贡献，请访问 [GitHub 仓库](https://github.com/MR01Right/SHT40)。

