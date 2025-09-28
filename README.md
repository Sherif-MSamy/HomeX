# **8051 Load Control System with Bluetooth & Flame Detection**  

## **📌 Project Overview**  
This project implements a **secure load control system** using an **8051 microcontroller**, featuring:  
- **4 Load Control Channels** (P0.0–P0.3)  
- **Password Protection** (must authenticate before operation)  
- **Dual Control Interface** (Keypad + Bluetooth)  
- **Flame Sensor Emergency Shutdown** (auto-disables all loads on fire detection)  
- **LCD Display** (shows system status & load states)  

---

## **🛠 Hardware Components**  
- **8051 Microcontroller** (AT89C51/52)  
- **4x4 Matrix Keypad** (for manual input)  
- **HC-05 Bluetooth Module** (for wireless control)  
- **16x2 LCD (I2C)** (for status display)  
- **Flame Sensor** (connected to P3.3)  
- **Relays/LEDs** (for load simulation)  

---

## **📂 Code Structure**  

| File | Description |
|------|-------------|
| **`main.c`** | Core logic (password check, load control, flame detection) |
| **`keypad.c`** | Scans and decodes keypad inputs |
| **`lcd.c`** | Handles LCD display via I2C |
| **`uart.c`** | Manages Bluetooth communication (9600 baud) |
| **`password.c`** | Handles password authentication |
| **`delay.c`** | Provides delay functions |

---

## **🔧 Key Features**  

### **1. Password Protection**  
- Default password: **`1234`** (configurable in `password.h`)  
- Asterisks (`*`) displayed during input for security  
- Wrong password → "Incorrect!" message  

### **2. Load Control**  
- **Keypad Commands**:  
  - `1`–`4` → Toggle individual loads  
  - `5` → All ON  
  - `0` → All OFF  
- **Bluetooth Commands**: Same as keypad (send `0`–`5` via serial terminal)  

### **3. Flame Sensor Safety**  
- Triggers **emergency shutdown** (all loads OFF)  
- Displays **"WARNING! FIRE"** on LCD  
- Auto-resumes normal operation when flame is gone  

### **4. LCD Display**  
- Shows **real-time load states** (ON/OFF)  
- Displays system messages (e.g., "System Ready", "Incorrect Password")  

---

## **⚙️ Setup & Usage**  

### **1. Hardware Connections**  
| Component | 8051 Pin |
|-----------|----------|
| Keypad Rows | P1.0–P1.3 |
| Keypad Columns | P1.4–P1.7 |
| LCD (I2C) | SDA (P2.0), SCL (P2.1) |
| Bluetooth (UART) | TX (P3.1), RX (P3.0) |
| Flame Sensor | P3.3 |
| Loads (Relays/LEDs) | P0.0–P0.3 |

### **2. Software Flow**  
1. **System Initialization** → LCD shows "Initializing..."  
2. **Password Entry** → User must enter correct password  
3. **Main Loop** → Accepts keypad/Bluetooth commands + monitors flame sensor  
4. **Emergency Mode** → Flame detection forces shutdown  

---

## **🚀 Applications**  
✅ **Smart Home Automation**  
✅ **Industrial Load Management**  
✅ **Fire-Safe Electrical Control**  

---

## **📝 Notes**  
- **Baud Rate**: 9600 (for Bluetooth)  
- **Default Password**: `1234` (change in `password.h`)  
- **Flame Sensor**: Active HIGH (triggers on flame detection)  

---

## **🔗 Dependencies**  
- **Keil C51** (for compilations)  
- **Proteus** (for simulation)  

---

**🌟 A compact, secure, and flexible embedded system for remote & manual load control with safety features!** 🚀
