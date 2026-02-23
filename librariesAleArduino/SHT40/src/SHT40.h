#pragma once

#include <Arduino.h>
#include <Wire.h>

/**
 * SHT40 简易驱动库
 * 
 * 功能：
 * - IIC 由外部初始化（如 Wire.begin(SDA, SCL)）
 * - 通过 begin(TwoWire*, addr) 传入
 * - 提供读取温度/湿度接口
 * 
 * @author MR01Right
 */
class SHT40 {
public:
  SHT40();
  
  /**
   * 初始化传感器
   * @param wire I2C总线对象指针
   * @param address I2C地址，默认为0x44
   * @return 初始化成功返回true，失败返回false
   */
  bool begin(TwoWire *wire, uint8_t address = 0x44);

  /**
   * 读取温度值
   * @param forceMeasure 是否强制测量，true为强制测量，false返回上次测量值
   * @return 温度值（摄氏度），失败返回NAN
   */
  float readTemperatureC(bool forceMeasure = true);

  /**
   * 读取相对湿度值
   * @param forceMeasure 是否强制测量，true为强制测量，false返回上次测量值
   * @return 相对湿度值（%RH），失败返回NAN
   */
  float readHumidityRH(bool forceMeasure = true);

  /**
   * 同时测量温度和湿度
   * @param temperatureC 温度输出参数（摄氏度）
   * @param humidityRH 湿度输出参数（%RH）
   * @return 测量成功返回true，失败返回false
   */
  bool measure(float &temperatureC, float &humidityRH);

private:
  TwoWire *_wire;
  uint8_t _addr;
  float _lastTemp;
  float _lastHum;

  /**
   * CRC8校验
   * @param msb 高字节
   * @param lsb 低字节
   * @param crc CRC校验值
   * @return 校验通过返回true，失败返回false
   */
  bool checkCrc(uint8_t msb, uint8_t lsb, uint8_t crc);
};

