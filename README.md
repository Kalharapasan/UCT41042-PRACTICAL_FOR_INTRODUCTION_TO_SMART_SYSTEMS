# UCT41042 - Practical for Introduction to Smart Systems

This repository contains laboratory work and assignment implementations for the module UCT41042 (Introduction to Smart Systems).

## Overview

The work is organized by lab number and task, mainly using:

- ESP32 and common IoT/sensor modules
- PlatformIO project structure (`platformio.ini`, `src`, `include`, `lib`, `test`)
- Wokwi simulation files (`diagram.json`, `wokwi.toml`)
- Arduino-style sketches in selected early exercises

## Repository Layout

Top-level folders:

- `00.Lab Work/` - Day-by-day lab session snapshots and supportive material
- `01.LB01/` - LB01 tasks (Wi-Fi and connectivity foundation)
- `02.LB02/` - LB02 exercises
- `03.LB03/` - LB03 sensor-focused tasks
- `04.LB04/` - LB04 input/output component tasks
- `05.LB05/` - LB05 task set (sensor and module integrations)

Key examples from the structure:

- `03.LB03/01.LB03_Task01_HC-SR04_Ultrasonic_Distance_Sensor/`
- `03.LB03/02.LB03_Task02_DHT22/`
- `04.LB04/14.LB04_Task14_LCD_16x2/`
- `04.LB04/15.LB04_Task15_LCD_16x2_I2C/`
- `05.LB05/11.LB05_Task11_MFRC522/`

## Typical Project Structure

Most PlatformIO tasks follow this layout:

```text
TaskFolder/
|- diagram.json
|- platformio.ini
|- wokwi.toml
|- include/
|- lib/
|- src/
|  \- main.cpp
\- test/
```

## Tooling

- VS Code
- PlatformIO extension
- Arduino IDE (optional for `.ino` sketches)
- Wokwi simulator

## How to Run a Task

### PlatformIO task

1. Open the specific task folder in VS Code.
2. Build:

```bash
pio run
```

3. Upload (if hardware is connected):

```bash
pio run -t upload
```

4. Open serial monitor:

```bash
pio device monitor
```

### Wokwi simulation

1. Open a task that contains `diagram.json` and `wokwi.toml`.
2. Start simulation via Wokwi integration (web or extension flow).
3. Observe serial output and sensor behavior.

### Arduino sketch task

1. Open the `.ino` file in Arduino IDE.
2. Configure board/port.
3. Upload or run in simulation where available.

## Lab Coverage Summary

- LB01: Wi-Fi basics and ESP32 onboarding
- LB02: Follow-up exercises and foundational patterns
- LB03: Sensor integration (HC-SR04, DHT22, DS18B20, BMP180, MPU6050, PIR, LDR, NTC, MQ2, HX711, MFRC522)
- LB04: Input/output components (buttons, switches, potentiometer, encoder, joystick, keypad, IR, LEDs, buzzer, servo, stepper, relay, LCD, matrix, seven-segment)
- LB05: Advanced task set continuing core sensor/module integrations

## Course Information

- Course code: UCT41042
- Module: Practical for Introduction to Smart Systems
- Academic period: Fourth Year, First Semester

## Notes

- Project and folder names intentionally retain original lab naming for traceability.
- Some folders may contain alternate drafts or variants from in-lab work.
- For day-specific context, check `00.Lab Work/`.
