# SHT40 Arduino Library

Arduino library for the SHT40 digital temperature and humidity sensor.

## Description

This library provides an easy-to-use interface for the SHT40 digital temperature and humidity sensor from Sensirion. The SHT40 is a high-precision, low-power sensor that communicates via I2C.

## Features

- Simple and intuitive API
- High precision temperature and humidity readings
- I2C communication support
- CRC8 checksum verification for data integrity
- Cached readings to avoid unnecessary measurements

## Installation

1. Download the library as a ZIP file
2. In the Arduino IDE, go to Sketch > Include Library > Add .ZIP Library...
3. Select the downloaded ZIP file
4. The library will be installed

Alternatively, you can clone this repository into your Arduino libraries folder:

```
cd <Arduino libraries folder>
git clone https://github.com/MR01Right/SHT40.git
```

## Hardware Requirements

- Arduino board (Uno, Nano, ESP32, etc.)
- SHT40 sensor module
- I2C connections (SDA, SCL)

## Wiring

Connect the SHT40 sensor to your Arduino:

- VCC → 3.3V or 5V (check sensor specifications)
- GND → GND
- SDA → SDA (or A4 on Arduino Uno)
- SCL → SCL (or A5 on Arduino Uno)

**Note:** Some boards may require pull-up resistors (typically 4.7kΩ) on SDA and SCL lines.

## Usage

### Basic Example

```cpp
#include <Wire.h>
#include <SHT40.h>

SHT40 sht40;

void setup() {
  Serial.begin(9600);
  Wire.begin();  // Initialize I2C
  
  if (!sht40.begin(&Wire)) {
    Serial.println("SHT40 initialization failed!");
    while(1);
  }
  Serial.println("SHT40 initialized successfully");
}

void loop() {
  float temperature = sht40.readTemperatureC();
  float humidity = sht40.readHumidityRH();
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %RH");
  
  delay(2000);
}
```

### Advanced Example

```cpp
#include <Wire.h>
#include <SHT40.h>

SHT40 sht40;

void setup() {
  Serial.begin(9600);
  Wire.begin();  // Initialize I2C
  
  // Initialize with custom I2C address (default is 0x44)
  sht40.begin(&Wire, 0x44);
}

void loop() {
  float temp, hum;
  
  if (sht40.measure(temp, hum)) {
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" °C");
    
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.println(" %RH");
  } else {
    Serial.println("Measurement failed!");
  }
  
  delay(2000);
}
```

## API Reference

### `SHT40()`
Constructor. Creates a new SHT40 instance.

### `bool begin(TwoWire *wire, uint8_t address = 0x44)`
Initializes the sensor.
- **Parameters:**
  - `wire`: Pointer to the TwoWire (I2C) object
  - `address`: I2C address (default: 0x44)
- **Returns:** `true` if initialization successful, `false` otherwise

### `float readTemperatureC(bool forceMeasure = true)`
Reads the temperature in Celsius.
- **Parameters:**
  - `forceMeasure`: If `true`, performs a new measurement. If `false`, returns the last cached value.
- **Returns:** Temperature in Celsius, or `NAN` if measurement failed

### `float readHumidityRH(bool forceMeasure = true)`
Reads the relative humidity.
- **Parameters:**
  - `forceMeasure`: If `true`, performs a new measurement. If `false`, returns the last cached value.
- **Returns:** Relative humidity in %RH, or `NAN` if measurement failed

### `bool measure(float &temperatureC, float &humidityRH)`
Performs a simultaneous measurement of temperature and humidity.
- **Parameters:**
  - `temperatureC`: Reference to store the temperature value
  - `humidityRH`: Reference to store the humidity value
- **Returns:** `true` if measurement successful, `false` otherwise

## Specifications

- **Temperature Range:** -40°C to +125°C
- **Temperature Accuracy:** ±0.2°C (typical)
- **Humidity Range:** 0% to 100% RH
- **Humidity Accuracy:** ±1.5% RH (typical)
- **I2C Address:** 0x44 (default)
- **Supply Voltage:** 2.3V to 5.5V

## License

This library is released under the MIT License.

## Author

MR01Right

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## Support

For issues, questions, or contributions, please visit the [GitHub repository](https://github.com/MR01Right/SHT40).

