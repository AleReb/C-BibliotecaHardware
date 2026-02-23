/*
  SHT40 Basic Example
  
  This example demonstrates how to use the SHT40 library
  to read temperature and humidity values.
  
  Author: MR01Right
*/

#include <Wire.h>
#include <SHT40.h>

// For ESP32, define your I2C pins here
// #define SDA_PIN 21
// #define SCL_PIN 22

SHT40 sht40;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  
  Serial.println("SHT40 Basic Example");
  Serial.println("===================");
  
  // Initialize I2C
  // For ESP32:
  // Wire.begin(SDA_PIN, SCL_PIN);
  // For Arduino Uno/Nano:
  Wire.begin();
  
  // Initialize SHT40 sensor
  if (!sht40.begin(&Wire)) {
    Serial.println("SHT40 initialization failed!");
    Serial.println("Please check your wiring and I2C connections.");
    while(1) {
      delay(1000);
    }
  }
  
  Serial.println("SHT40 initialized successfully");
  Serial.println();
}

void loop() {
  // Read temperature
  float temperature = sht40.readTemperatureC();
  
  // Read humidity
  float humidity = sht40.readHumidityRH();
  
  // Check if readings are valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from SHT40 sensor!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %RH");
  }
  
  Serial.println("---");
  delay(2000); // Wait 2 seconds before next reading
}

