
# Gesture Controlled Mouse

An interactive system that allows a user to control the computer cursor using hand gestures, interfaced via an ESP32/Arduino and a Python bridge.

## 🚀 How it Works
1. **Hardware:** The sensors detect movement and send data to the microcontroller, push button switches are used to get the right and left click
2. **Communication:** Data is sent via Serial communication to a PC.
3. **Software:** A Python script parses the data and moves the system cursor.

## 🛠️ Tech Stack
* **Language:** C++ (Arduino), Python
* **Hardware:** ESP32, MPU6050, Push button switches
* **Python Libraries:** `pySerial`, `pyautogui`

## 📂 Project Structure
* `source/`: Contains the firmware and Python scripts.
* `assets/`: Contains circuit diagrams and block diagrams.
