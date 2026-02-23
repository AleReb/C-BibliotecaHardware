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

#include "SHT40.h"

SHT40::SHT40() : _wire(nullptr), _addr(0x44), _lastTemp(NAN), _lastHum(NAN) {
}

bool SHT40::begin(TwoWire *wire, uint8_t address) {
  _wire = wire;
  _addr = address;
  return _wire != nullptr;
}

float SHT40::readTemperatureC(bool forceMeasure) {
  float t, h;
  if (forceMeasure) {
    if (!measure(t, h)) return NAN;
    return t;
  }
  return _lastTemp;
}

float SHT40::readHumidityRH(bool forceMeasure) {
  float t, h;
  if (forceMeasure) {
    if (!measure(t, h)) return NAN;
    return h;
  }
  return _lastHum;
}

bool SHT40::measure(float &temperatureC, float &humidityRH) {
  if (_wire == nullptr) return false;

  // 发送高精度测量命令 0xFD
  _wire->beginTransmission(_addr);
  _wire->write(0xFD);
  if (_wire->endTransmission() != 0) return false;

  delay(10); // 转换时间 ~9ms

  const uint8_t expected = 6;
  if (_wire->requestFrom((int)_addr, (int)expected) != expected) return false;

  uint8_t data[6];
  for (uint8_t i = 0; i < expected; ++i) {
    data[i] = _wire->read();
  }

  if (!checkCrc(data[0], data[1], data[2])) return false;
  if (!checkCrc(data[3], data[4], data[5])) return false;

  uint16_t rawT = ((uint16_t)data[0] << 8) | data[1];
  uint16_t rawRH = ((uint16_t)data[3] << 8) | data[4];

  temperatureC = -45.0f + 175.0f * (rawT / 65535.0f);
  humidityRH = -6.0f + 125.0f * (rawRH / 65535.0f);
  humidityRH = constrain(humidityRH, 0.0f, 100.0f);

  _lastTemp = temperatureC;
  _lastHum = humidityRH;
  return true;
}

bool SHT40::checkCrc(uint8_t msb, uint8_t lsb, uint8_t crc) {
  uint8_t data[2] = {msb, lsb};
  uint8_t c = 0xFF;
  for (uint8_t i = 0; i < 2; ++i) {
    c ^= data[i];
    for (uint8_t bit = 0; bit < 8; ++bit) {
      c = (c & 0x80) ? (uint8_t)((c << 1) ^ 0x31) : (uint8_t)(c << 1);
    }
  }
  return c == crc;
}

