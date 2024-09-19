# Curtainator-9000: Automated Curtain Opener

## Overview

The **Curtainator-9000** is an automated curtain opening system that allows users to wake up naturally by gradually letting in sunlight. It uses a combination of a light sensor, Wi-Fi microcontroller, and motor to detect the morning light and open the curtains smoothly. This project is designed for busy professionals who want a refreshing start to their day by waking up with natural light.

## Use Case Scenario

**Sarah**, a 28-year-old Marketing Director, leads a busy professional life with morning meetings. Appreciating an invigorating start to her day, she seeks a solution that allows her to wake up naturally for a more energetic morning routine.  
By using the **Curtainator-9000**, she can set the time for her curtains to open early in the morning. Additionally, the device detects the increasing sunlight and begins to open the curtains slowly, allowing natural light to gently enter her room.

---

## Components Used

- **NodeMCU ESP8266**: Wi-Fi microcontroller to handle communication and logic.
- **Adafruit TSL2591**: Digital light sensor to detect ambient sunlight levels.
- **Piezo Buzzer**: Passive piezoelectric buzzer for optional sound notifications.
- **16x2 LCD Display**: Displays messages or sensor data for user interaction.
- **18650 Batteries**: Rechargeable batteries for portability and power.
- **MB-102 Breadboard**: Used to connect all components and facilitate prototyping.
- **Battery Shield**: Manages battery charging and protection for safe operation.
- **DC Motor**: Drives the movement of the curtains.

---

## Features

- **Light Sensing**: Automatically detects sunlight levels and adjusts the curtain opening speed.
- **Manual Scheduling**: Users can set a specific time to open the curtains.
- **LCD Display**: Displays real-time data, settings, and status of the system.
- **Portability**: Powered by rechargeable 18650 batteries for standalone operation.
- **Wi-Fi Enabled**: Future-proofing for potential IoT integration or remote control.

---

## Conceptual Architecture

### Graphical showcase of our device's architecture:
![image](https://github.com/user-attachments/assets/a51b31e9-73b3-4cc7-beaa-8b4e9466fe79)

---

## Phone Application MIT App Inventor

### Phone application first look:
![image](https://github.com/user-attachments/assets/81bc32df-45c9-4ef3-98d9-bb8308ae7e91)

### Code behind the application:
![image](https://github.com/user-attachments/assets/1863d3ab-50ca-4951-9df2-177bab044c62)

---

## Prospects for Improvement

- **I2C LCD Adapter**: Simplifies wiring and improves the aesthetics by reducing the number of wires required for the display.
- **Chassis (Enclosure)**: A proper casing to conceal wiring, protect components, and enhance the overall appearance of the Curtainator.
- **Wheel Mechanism**: Complete the design by adding wheels for better movement and curtain handling.
- **Multi-Device Network**: Integration of multiple Curtainator devices across the home, allowing for coordinated curtain control between different rooms or windows.

---

## Current Limitations

### LCD Display
- **Connection Issues**: There are potential connection problems without using an I2C adapter.
  
### Light Sensor Sensitivity
- **Stability**: The sensor's connection can sometimes be unstable, leading to delays or inaccurate readings.

### Architecture
- **Wiring**: The current design involves many wires, making it difficult to manage and decreasing the overall aesthetics.  
- **Wheel Mechanism**: Lack of a functional wheel reduces the complete functionality of the curtain-opening mechanism.  
- **No Chassis**: The absence of a proper enclosure results in exposed components, which affects both the protection and appearance of the device.

---

## How to Use

1. **Power the Device**: Ensure the 18650 batteries are charged and inserted into the battery shield.
2. **Set Time/Mode**: Using the interface provided by the LCD display, set the desired time or enable automatic light-sensing mode.
3. **Position the Device**: Attach the motor to the curtains and position the light sensor where it can detect incoming sunlight.
4. **Run**: The device will automatically detect sunlight and begin to open the curtains, or it will follow the manual schedule if set.

---

## How to Improve This Project

- **Use of I2C Adapters**: Implement I2C adapters to reduce wiring complexity and improve connection stability for the LCD.
- **Design a Chassis**: Build a custom enclosure to hide the wires and protect the components.
- **Add a Wheel Mechanism**: For full automation, a wheel mechanism can be added to assist the motor in moving the curtains efficiently.
- **Expand to a Network**: Add support for multiple Curtainator-9000 devices to create a synchronized curtain-opening system for multiple windows or rooms.

---

## Video Showcase

Video showcasing the use of our Android application working with the device: https://youtu.be/Pw0lTUnGxVo
