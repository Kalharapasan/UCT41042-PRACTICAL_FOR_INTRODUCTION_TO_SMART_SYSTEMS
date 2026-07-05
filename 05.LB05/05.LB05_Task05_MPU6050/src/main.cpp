#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  Serial.println("\nMPU6050 (3-Axis Accelerometer + Gyroscope + Temperature) ");
  Wire.begin();
  mpu.initialize();
}

void loop() {

  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  // Read Accelerometer and Gyroscope values
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  Serial.println("Accelerometer");

  Serial.print("X: ");
  Serial.print(ax);

  Serial.print("  Y: ");
  Serial.print(ay);

  Serial.print("  Z: ");
  Serial.println(az);

  Serial.println("Gyroscope");

  Serial.print("X: ");
  Serial.print(gx);

  Serial.print("  Y: ");
  Serial.print(gy);

  Serial.print("  Z: ");
  Serial.println(gz);

  Serial.println();

  delay(1000);
}